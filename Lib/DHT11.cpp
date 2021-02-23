/*
 * DHT11.cpp
 *
 *  Created on: 23 févr. 2021
 *      Author: pierr
 */

#include <Lib/DHT11.h>
/**
 * Constructor
 */
DHT11::DHT11()
{
    // isn't busy at this time
    mIsBusy = false;
}
/**
 * Public methods
 */
bool DHT11::Read(void)
{
    int i;
    if (!Start())
        return false;

    // read 5 bytes
    for(i = 0;i <5;i++)
    {
        mData[i] = readByte();
    }
    if(mData[4] = (mData[0] +mData[1] + mData[2] + mData[3]))
    {
        mIsBusy = false;
        return true;
    }
    mIsBusy = false;
    return false;
}

unsigned char DHT11::getHumidityInteger(void)
{
    return mData[0];
}

unsigned char DHT11::getHumidityDecimal(void)
{
    return mData[1];
}

unsigned char DHT11::getTemperatureInteger(void)
{
    return mData[2];
}

unsigned char DHT11::getTemperatureDecimal(void)
{
    return mData[3];
}

bool DHT11::isBusy(void)
{
    return mIsBusy;
}
/**
 * Private methods
 */
bool DHT11::Start(void)
{
    unsigned char elapsedTime = 0;
    mIsBusy = true;
    // --> wait for 1 s
    //__delay_cycles(1000000);
    // --> set data pin as output
    DHT_PORT_DIR |= DHT_PORT_DATA_PIN;
    // --> turn data pin to low
    DHT_PORT_OUT &= ~DHT_PORT_DATA_PIN;
    // --> wait for 20ms
    __delay_cycles(20000);
    // --> turn data pin to high
    DHT_PORT_OUT |= DHT_PORT_DATA_PIN;
    // --> wait for 20µs
    __delay_cycles(20);
    // --> turn data pin to low
    DHT_PORT_OUT &= ~DHT_PORT_DATA_PIN;
    // --> set data pin as input
    DHT_PORT_DIR &= ~DHT_PORT_DATA_PIN;
    // --> check if signal low during 80µs
    elapsedTime = 0;
    do
    {
        elapsedTime++;
    }
    while ((DHT_PORT_IN & DHT_PORT_DATA_PIN) == 0);
    if (elapsedTime > 10)
        return false;
    // --> check if signal high during 80µs
    elapsedTime = 0;
    do
    {
        elapsedTime++;
    }
    while ((DHT_PORT_IN & DHT_PORT_DATA_PIN) == DHT_PORT_DATA_PIN);
    if (elapsedTime > 10)
        return false;

    return true;
}

unsigned char DHT11::readByte(void)
{
    unsigned char byte = 0;
    unsigned char i;
    unsigned char elapsedTime = 0;
    for(i=8;i>0;i--)
    {
        // skip the lower 50µS part
        while((DHT_PORT_IN & DHT_PORT_DATA_PIN) == 0);
        elapsedTime = 0;
        do
        {
            elapsedTime ++;
        // wait for signal turn low from high
        }while((DHT_PORT_IN & DHT_PORT_DATA_PIN) == DHT_PORT_DATA_PIN);
        if(elapsedTime > 5)
        {
            byte |= 1 << (i-1);
        }
    }
    return byte;
}
