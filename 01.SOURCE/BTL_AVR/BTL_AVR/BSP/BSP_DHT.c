/*
 * BSP_DHT.c
 *
 * Created: 9/18/2026 2:44:04 PM
 *  Author: HP
 */ 
#include "BSP_DHT.h"
#include "BOARD.h"
#include <avr/io.h>
#include <util/delay.h>


/*
 * DHT DATA = OUTPUT, MCU ?i?u khi?n DATA
 */
static void DHT_SetOutput(void)
{
    DHT_DDR |= (1 << DHT_DATA_PIN);
}


/*
 * DHT DATA = INPUT, DHT11 g?i d? li?u v? cho MCU
 */
static void DHT_SetInput(void)
{
    DHT_DDR &= ~(1 << DHT_DATA_PIN);
}


/*
 * Set DATA = LOW
 */
static void DHT_WriteLow(void)
{
    DHT_PORT &= ~(1 << DHT_DATA_PIN);
}


/*
 * Set DATA = HIGH
 */
static void DHT_WriteHigh(void)
{
    DHT_PORT |= (1 << DHT_DATA_PIN);
}


/*
 * Read DATA pin, check data dang low/high
 */
static uint8_t DHT_ReadPin(void)
{
    return (DHT_PIN & (1 << DHT_DATA_PIN)) != 0;
}


/*
 * Ch? DATA ??t t?i m?c mong mu?n.
 *
 * level:
 *      0 -> ch? LOW
 *      1 -> ch? HIGH
 *
 * timeout:
 *      s? vòng l?p t?i ?a
 *
 * return:
 *      1 = thành công
 *      0 = timeout
 */
static uint8_t DHT_WaitForLevel(uint8_t level,
                                uint16_t timeout)
{
    while (DHT_ReadPin() != level)
    {
        if (timeout == 0)
        {
            return 0;
        }

        timeout--;

        _delay_us(1);
    }

    return 1;
}

//START SIGNAL

/*
 * MCU g?i START signal cho DHT11.
 *
 * Sequence:
 *
 * DATA LOW  >= 18 ms
 * DATA HIGH ~ 20-40 us
 * DATA INPUT
 *
 * return:
 *      1 = ?ã g?i START
 */
static uint8_t DHT_SendStart(void)
{
    /* MCU ?i?u khi?n DATA */
    DHT_SetOutput();

    /* START: kéo DATA LOW */
    DHT_WriteLow();

    /* DHT11 yêu c?u LOW ít nh?t 18 ms */
    _delay_ms(20);

    /* Nh? DATA lên HIGH */
    DHT_WriteHigh();

    /* Gi? HIGH kho?ng 30 us */
    _delay_us(30);

    /* Nh? bus cho DHT11 */
    DHT_SetInput();

    return 1;
}

//CHECK DHT11 RESPONSE
static uint8_t DHT_CheckResponse(void)
{
    uint16_t low_time = 0;
    uint16_t high_time = 0;

	//Ch? DHT11 kéo data low
    if (!DHT_WaitForLevel(0, 150))
    {
        return 0;
    }

	//DHT11 response low = 80us

    while (!DHT_ReadPin())
    {
        if (low_time >= 120)
        {
            return 0;
        }

        low_time++;

        _delay_us(1);
    }

	//check response có l?i ko
    if ((low_time < 50) || (low_time > 120))
    {
        return 0;
    }

	//DHT11 response high = 80us

    while (DHT_ReadPin())
    {
        if (high_time >= 120)
        {
            return 0;
        }

        high_time++;

        _delay_us(1);
    }

	//check response có l?i ko

    if ((high_time < 50) || (high_time > 120))
    {
        return 0;
    }

	//Response h?p l?
    return 1;
}

//DHT11 response thành công, readbit
static uint8_t DHT_ReadBit(uint8_t *bit)
{
    uint16_t time = 0;

	//Low start
    if (!DHT_WaitForLevel(0, 100))
    {
        return 0;
    }

    if (!DHT_WaitForLevel(1, 150))
    {
        return 0;
    }

	//?o tgian high
    while (DHT_ReadPin())
    {
        if (time >= 100)
        {
            return 0;
        }

        time++;

        _delay_us(1);
    }

	/* bit 0 = 26-28us
	bit 1 = 70us */
	
    if (time > 50)
    {
        *bit = 1;
    }
    else
    {
        *bit = 0;
    }

    return 1;
}

//read 1 byte
static uint8_t DHT_ReadByte(uint8_t *data)
{
    uint8_t i;
    uint8_t bit;

    *data = 0;

    for (i = 0; i < 8; i++)
    {
        if (!DHT_ReadBit(&bit))
        {
            return 0;
        }

		//dich bit ?ã ??c sang trái
        *data <<= 1;

		//g?n bit ?ã ??c vào bit lowest
        *data |= bit;
    }

    return 1;
}


void BSP_DHT_Init(void)
{
	//DATA: input
    DHT_SetInput();

	//Tro keo len
    DHT_PORT |= (1 << DHT_DATA_PIN);
}

//read function
uint8_t BSP_DHT_Read(uint8_t *humidity,
                     uint8_t *temperature)
{
    uint8_t data[5];

    uint8_t i;

    uint8_t checksum;

	//send start
    if (!DHT_SendStart())
    {
        return 0;
    }

	//check response
    if (!DHT_CheckResponse())
    {
        return 0;
    }


    /* ??c 40 bit
     * data[0] = humidity integer
     * data[1] = humidity decimal
     * data[2] = temperature integer
     * data[3] = temperature decimal
     * data[4] = checksum */

    for (i = 0; i < 5; i++)
    {
        if (!DHT_ReadByte(&data[i]))
        {
            return 0;
        }
    }

	//check sum

    checksum = data[0]
             + data[1]
             + data[2]
             + data[3];


    if (checksum != data[4])
    {
        return 0;
    }

	//return data

    *humidity = data[0];

    *temperature = data[2];


    return 1;
}