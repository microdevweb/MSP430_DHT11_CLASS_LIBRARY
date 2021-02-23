/*
 * LCD32.h
 *
 *  Created on: 23 févr. 2021
 *      Author: pierr
 */

#ifndef LIB_LCD32_H_
#define LIB_LCD32_H_

#include <msp430.h>
#include <string.h>
#include <stdio.h>

class LCD32
{
    #define LCD_PIN_EN         BIT4
    #define LCD_PIN_RS         BIT5
    #define LCD_PIN_DATA       0x0F

    #define LCD_PORT_DIR       P2DIR
    #define LCD_PORT_OUT       P2OUT
public:

    LCD32();
    void DisplayText(const char* text,int x,int y);
    void DisplayInteger(int val,int x,int y);
    void Clear(void);
private:
    void TriggerEN(void);
    void WriteCmd(unsigned char cmd);
    void WriteData(unsigned char data);
};

#endif /* LIB_LCD32_H_ */
