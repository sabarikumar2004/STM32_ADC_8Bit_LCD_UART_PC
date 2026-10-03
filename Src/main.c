#include <stdint.h>

#define RCC_BASE        0x40021000UL

#define RCC_APB2ENR     (*(volatile uint32_t *)(RCC_BASE + 0x18))

#define IOPAEN          (1 << 2)
#define IOPBEN          (1 << 3)
#define AFIOEN          (1 << 0)
#define ADC1EN          (1 << 9)
#define UART1EN         (1 << 14)


#define AFIO_BASE       0x40010000UL

#define AFIO_MAPR       (*(volatile uint32_t *)(AFIO_BASE + 0x04))


#define GPIOA_BASE      0x40010800UL

#define GPIOA_CRL       (*(volatile uint32_t *)(GPIOA_BASE + 0x00))
#define GPIOA_CRH       (*(volatile uint32_t *)(GPIOA_BASE + 0x04))
#define GPIOA_ODR       (*(volatile uint32_t *)(GPIOA_BASE + 0x0C))


#define GPIOB_BASE      0x40010C00UL

#define GPIOB_CRL       (*(volatile uint32_t *)(GPIOB_BASE + 0x00))
#define GPIOB_ODR       (*(volatile uint32_t *)(GPIOB_BASE + 0x0C))


#define ADC1_BASE       0x40012400UL

#define ADC1_SR         (*(volatile uint32_t *)(ADC1_BASE + 0x00))
#define ADC1_CR2        (*(volatile uint32_t *)(ADC1_BASE + 0x08))
#define ADC1_SMPR2      (*(volatile uint32_t *)(ADC1_BASE + 0x10))
#define ADC1_SQR1       (*(volatile uint32_t *)(ADC1_BASE + 0x2C))
#define ADC1_SQR3       (*(volatile uint32_t *)(ADC1_BASE + 0x34))
#define ADC1_DR         (*(volatile uint32_t *)(ADC1_BASE + 0x4C))


#define USART1_BASE     0x40013800UL

#define USART1_SR       (*(volatile uint32_t *)(USART1_BASE + 0x00))
#define USART1_DR       (*(volatile uint32_t *)(USART1_BASE + 0x04))
#define USART1_BRR      (*(volatile uint32_t *)(USART1_BASE + 0x08))
#define USART1_CR1      (*(volatile uint32_t *)(USART1_BASE + 0x0C))


#define LCD_RS          (1 << 3)
#define LCD_EN          (1 << 1)


void delay_ms(uint32_t ms)
{
    volatile uint32_t i;

    while (ms--)
    {
        for (i = 0; i < 8000; i++)
        {
            __asm volatile ("nop");
        }
    }
}


void LCD_Enable(void)
{
    GPIOB_ODR |= LCD_EN;

    delay_ms(2);

    GPIOB_ODR &= ~LCD_EN;

    delay_ms(2);
}


void LCD_Command(char cmd)
{
    GPIOB_ODR &= ~LCD_RS;

    GPIOA_ODR &= ~0xFF;

    GPIOA_ODR |= (uint8_t)cmd;

    LCD_Enable();
}


void LCD_Data(char data)
{
    GPIOB_ODR |= LCD_RS;

    GPIOA_ODR &= ~0xFF;

    GPIOA_ODR |= (uint8_t)data;

    LCD_Enable();
}


void LCD_String(char *str)
{
    while (*str)
    {
        LCD_Data(*str);

        str++;
    }
}


void LCD_Init(void)
{
    delay_ms(20);

    LCD_Command(0x30);

    delay_ms(5);

    LCD_Command(0x30);

    delay_ms(1);

    LCD_Command(0x30);

    delay_ms(1);

    LCD_Command(0x38);

    LCD_Command(0x0C);

    LCD_Command(0x01);

    delay_ms(2);

    LCD_Command(0x06);
}


void LCD_Sendfloat(float value)
{
    uint16_t integer_part;
    uint16_t decimal_part;

    integer_part = (uint16_t)value;

    decimal_part =
        (uint16_t)((value - integer_part) * 100);

    LCD_Data(integer_part + '0');

    LCD_Data('.');

    LCD_Data((decimal_part / 10) + '0');

    LCD_Data((decimal_part % 10) + '0');
}


void ADC_Init(void)
{
    GPIOB_CRL &= ~(0xF << 0);

    ADC1_SMPR2 &= ~(7 << 0);

    ADC1_SMPR2 |= (7 << 0);

    ADC1_SQR1 = 0;

    ADC1_SQR3 = 8;

    ADC1_CR2 |= (1 << 0);

    delay_ms(1);

    ADC1_CR2 |= (1 << 3);

    while (ADC1_CR2 & (1 << 3));

    ADC1_CR2 |= (1 << 2);

    while (ADC1_CR2 & (1 << 2));

    ADC1_CR2 &= ~(7 << 17);

    ADC1_CR2 |= (7 << 17);

    ADC1_CR2 |= (1 << 20);
}


float ADC_Read(void)
{
    uint16_t adc_value;

    ADC1_CR2 |= (1 << 22);

    while (!(ADC1_SR & (1 << 1)));

    adc_value = (uint16_t)ADC1_DR;

    return ((float)adc_value * 3.3f) / 4095.0f;
}


void UART_Init(void)
{
    GPIOA_CRH &= ~(0xF << 4);

    GPIOA_CRH |= (0xB << 4);

    USART1_BRR = 0x0341;

    USART1_CR1 |= (1 << 13);

    USART1_CR1 |= (1 << 3);
}


void UART_SendChar(char data)
{
    while (!(USART1_SR & (1 << 7)));

    USART1_DR = data;
}


void UART_SendString(char *str)
{
    while (*str)
    {
        UART_SendChar(*str);

        str++;
    }
}


void UART_Sendfloat(float value)
{
    uint16_t integer_part;
    uint16_t decimal_part;

    integer_part = (uint16_t)value;

    decimal_part =
        (uint16_t)((value - integer_part) * 100);

    UART_SendChar(integer_part + '0');

    UART_SendChar('.');

    UART_SendChar((decimal_part / 10) + '0');

    UART_SendChar((decimal_part % 10) + '0');
}


int main(void)
{
    float voltage;

    RCC_APB2ENR |= IOPAEN;

    RCC_APB2ENR |= IOPBEN;

    RCC_APB2ENR |= AFIOEN;

    AFIO_MAPR &= ~(7 << 24);

    AFIO_MAPR |= (2 << 24);


    GPIOA_CRL = 0x33333333;


    GPIOB_CRL &= ~0x0000FFFF;

    GPIOB_CRL |= 0x00003030;


    GPIOA_ODR = 0;

    GPIOB_ODR &= ~(LCD_RS | LCD_EN);


    RCC_APB2ENR |= ADC1EN;

    RCC_APB2ENR |= UART1EN;


    LCD_Init();

    ADC_Init();

    UART_Init();


    while (1)
    {
        voltage = ADC_Read();


        LCD_Command(0x80);

        LCD_String("ADC VOLTAGE:");


        LCD_Command(0xC0);

        LCD_Sendfloat(voltage);

        LCD_String(" V");


        UART_SendString("ADC Voltage: ");

        UART_Sendfloat(voltage);

        UART_SendString(" V\r\n");


        delay_ms(300);
    }
}
