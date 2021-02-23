/*
 * LCD32.cpp
 *
 *  Created on: 23 févr. 2021
 *      Author: pierr
 */

#include <Lib/LCD32.h>


#define DELAY_MS(x)        __delay_cycles((long) x* 1000)
#define DELAY_US(x)        __delay_cycles((long) x)
#define CLEAR              0x01
#define LOWNIB(x)          LCD_PORT_OUT = (LCD_PORT_OUT & 0xF0) + (x & 0x0F)
/**
 * Constructor
 */
LCD32::LCD32()
{
    // wait for 100 mS
    DELAY_MS(100);
    // set port output
    LCD_PORT_DIR = LCD_PIN_EN + LCD_PIN_RS + LCD_PIN_DATA;
    // start LCD
    LCD_PORT_OUT = 0x03;

    // Send 0x03 3 times at 5ms then 100 us
    TriggerEN();
    // --> wait for 5 mS
    DELAY_MS(5);

    TriggerEN();
    // --> wait for 5 mS
    DELAY_MS(5);

    TriggerEN();
    // --> wait for 5 mS
    DELAY_MS(5);

    // Switch to 4-bit mode
    LCD_PORT_OUT = 0x02;
    TriggerEN();
    // --> wait for 5 mS
    DELAY_MS(5);

    // 4-bit, 2 line, 5x8
    WriteCmd(0x28);
    // Instruction Flow
    WriteCmd(0x08);
    // Clear LCD
    WriteCmd(0x01);
    // Auto-Increment
    WriteCmd(0x06);
    // Display On, No blink
    WriteCmd(0x0C);
}

/**
 * Public methods
 */
void LCD32::DisplayText(const char* text,int x,int y)
{
    int i;
    if(x < 16)
    {
        // Set LCD for first line write
        x |= 0x80;
        switch(y)
        {
        // Set LCD for second line write
        case 1:
            x |= 0x40;
            break;
        // Set LCD for first line write reverse
        case 2:
            x |= 0x60;
            break;
        // Set LCD for second line write reverse
        case 3:
            x |= 0x20;
            break;
        }
        WriteCmd(x);
    }
    i = 0;
    while(text[i] != '\0')
    {
        WriteData(text[i]);
        i++;
    }
}

void LCD32::DisplayInteger(int val,int x,int y)
{
    char numberString[16];
    // Convert the integer to character string
    sprintf(numberString, "%d",val);
    DisplayText(numberString, x, y);
}

void LCD32::Clear(void)
{
    WriteCmd(CLEAR);
}
/**
 * Private methods
 */
void LCD32::TriggerEN(void)
{
    LCD_PORT_OUT |= LCD_PIN_EN;
    LCD_PORT_OUT &= ~LCD_PIN_EN;
}

void LCD32::WriteCmd(unsigned char cmd)
{
    // Set RS to Data
    LCD_PORT_OUT &= ~LCD_PIN_RS;
    // Upper nibble
    LOWNIB(cmd >> 4);
    TriggerEN();
    // Lower nibble
    LOWNIB(cmd);
    TriggerEN();
    // wait for 5 mS
    DELAY_MS(50);
}

void LCD32::WriteData(unsigned char data)
{
    // Set RS to Data
    LCD_PORT_OUT |= LCD_PIN_RS;
    // Upper nibble
    LOWNIB(data >> 4);
    TriggerEN();
    // Lower nibble
    LOWNIB(data);
    TriggerEN();
    // wait for 1000 µS
    DELAY_US(1000);

}
