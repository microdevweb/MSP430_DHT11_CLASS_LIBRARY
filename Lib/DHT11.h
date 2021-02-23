/*
 * DHT11.h
 *
 *  Created on: 23 févr. 2021
 *      Author: pierr
 */

#ifndef LIB_DHT11_H_
#define LIB_DHT11_H_

#include <msp430.h>

class DHT11
{

    #define DHT_PORT_DIR        P1DIR
    #define DHT_PORT_OUT        P1OUT
    #define DHT_PORT_IN         P1IN
    #define DHT_PORT_DATA_PIN   BIT5
public:
    DHT11();
    bool Read(void);
    unsigned char getHumidityInteger(void);
    unsigned char getHumidityDecimal(void);
    unsigned char getTemperatureInteger(void);
    unsigned char getTemperatureDecimal(void);
    bool isBusy(void);
private:
    bool Start(void);
    unsigned char readByte(void);

    unsigned char mData[5];
    bool mIsBusy;
};

#endif /* LIB_DHT11_H_ */
