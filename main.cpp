#include <msp430.h> 
#include "DHT11.h"
#include "LCD32.h"

#define GREEN_LED   BIT6
#define TICK        BIT1
#define BUTTON      BIT3

/**
 * main.c
 */
void main(void)
{
	DHT11 dht = DHT11();
	LCD32 lcd = LCD32();
    WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	// clock frequency initiation
	BCSCTL1 = CALBC1_1MHZ;
	DCOCTL = CALDCO_1MHZ;
	// GPIO initiation
	// --> output
	P1DIR |= GREEN_LED | TICK;
	P1OUT = 0x00;
	// --> input
	P1REN |= BUTTON; // enable resistor
	P1OUT |= BUTTON;

	// main loop
	lcd.DisplayText("Welcome on board", 0, 0);
    while (1)
    {
        if ((P1IN & BUTTON) == 0x00 && ! dht.isBusy())
        {
            P1OUT |= GREEN_LED; // Turn on the led
            if(dht.Read())
            {
                lcd.Clear();
                lcd.DisplayText("Temp : ", 0, 0);
                lcd.DisplayInteger(dht.getTemperatureInteger(), 8, 0);
                lcd.DisplayText(".", 11, 0);
                lcd.DisplayInteger(dht.getTemperatureDecimal(), 12, 0);
                lcd.DisplayText("C", 15, 0);

                lcd.DisplayText("Humi : ", 0, 1);
                lcd.DisplayInteger(dht.getHumidityInteger(), 8, 1);
                lcd.DisplayText(".", 11, 1);
                lcd.DisplayInteger(dht.getHumidityDecimal(), 12, 1);
                lcd.DisplayText("%", 15, 1);
            }
            P1OUT &= ~GREEN_LED; // Turn off the led
        }
    }
}
