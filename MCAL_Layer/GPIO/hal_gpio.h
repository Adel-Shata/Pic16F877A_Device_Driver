/* 
 * File:   hal_gpio.h
 * Author: Adel Shata
 *
 * Created on August 4, 2026, 6:39 PM
 */

#ifndef HAL_GPIO_H
#define	HAL_GPIO_H

/*Section: Includes*/
#include "../proc/pic16f877a.h"
#include "../device_config.h"

/*Section: Macro Declarations*/

#define PORT_MAX_NUM         5
#define PORT_PIN_MAX_NUM     8

#define STD_LOW              0x00
#define STD_HIGH             0x01

#define STD_OFF              0x00
#define STD_ON               0x01

#define STD_IDLE             0x00
#define STD_ACTIVE           0x01

#define PORT_MASK            0xFF
#define BIT_MASK             0x01

#define GPIO_PORTA_VALID_PINS    6
#define GPIO_PORTB_VALID_PINS    8
#define GPIO_PORTC_VALID_PINS    8
#define GPIO_PORTD_VALID_PINS    8
#define GPIO_PORTE_VALID_PINS    3

/*Section: Macro Functions Declarations*/

#define SET_BIT( REG , BIT_NUM )                           ( (REG) |=  ( ( BIT_MASK ) << ( BIT_NUM ) ) )
#define CLEAR_BIT( REG , BIT_NUM )                         ( (REG) &= ~( ( BIT_MASK ) << ( BIT_NUM ) ) )
#define TOGGLE_BIT( REG , BIT_NUM )                        ( (REG) ^=  ( ( BIT_MASK ) << ( BIT_NUM ) ) )
#define READ_BIT( REG , BIT_NUM )                          (( ( ( REG ) >> ( BIT_NUM ) ) & ( BIT_MASK ) ))

#define SET_PORT( REG, GPIO_PORT_VALID_MASk )              ( (REG) |=  ( ( GPIO_PORT_VALID_MASk ) << ( 0 ) ) )
#define CLEAR_PORT( REG, GPIO_PORT_VALID_MASk )            ( (REG) &= ~( ( GPIO_PORT_VALID_MASk ) << ( 0 ) ) )
#define TOGGLE_PORT( REG, GPIO_PORT_VALID_MASk )           ( (REG) ^=  ( ( GPIO_PORT_VALID_MASk ) << ( 0 ) ) )

#define GPIO_PIN_CHECK_VALIDITY( VALID_PINS, PIN )         ( ( VALID_PINS ) & ( ( ( BIT_MASK ) << ( PIN ) ) ) )

/*Section: Data Type Declarations*/

// Primary data type declarations ???
typedef signed char          sint8;
typedef unsigned char        uint8;
typedef volatile sint8       vsint8;
typedef volatile uint8       vuint8;

typedef signed short         sint16;
typedef unsigned short       uint16;
typedef volatile sint16      vsint16;
typedef volatile uint16      vuint16;

typedef signed long          sint32;
typedef unsigned long        uint32;
typedef volatile sint32      vsint32;
typedef volatile uint32      vuint32;

typedef float                float32;
typedef volatile float       vfloat32;

// User data type declarations ???

typedef enum{
    E_NOT_OK = 0,
    E_OK
}std_return_type_t;

typedef enum{
    GPIO_LOW = 0,
    GPIO_HIGH
}logic_t;

typedef enum{
    GPIO_DIRECTION_OUTPUT = 0,
    GPIO_DIRECTION_INPUT
            
}direction_t;

typedef enum{
    GPIO_P0 = 0,
    GPIO_P1,
    GPIO_P2,
    GPIO_P3,
    GPIO_P4,
    GPIO_P5,
    GPIO_P6,
    GPIO_P7         
}pin_index_t;

typedef enum{
    PORTA_INDEX = 0,
    PORTB_INDEX,
    PORTC_INDEX,
    PORTD_INDEX,
    PORTE_INDEX
}port_index_t;

typedef struct{
    uint8 port          : 3; /*@ref : port_index_t*/
    uint8 pin           : 3; /*@ref : pin_index_t*/
    uint8 direction     : 1; /*@ref : direction_t*/
    uint8 logic         : 1; /*@ref : logic_t*/
}pin_config_t;

/*Section: Functions Declarations*/

// Pin configuration functions ???
std_return_type_t gpioPinInit(pin_config_t const *pinCfg);

std_return_type_t gpioPinDirInit( pin_config_t const *pinCfg, direction_t pinDir );

std_return_type_t gpioPinDirGet( pin_config_t const *pinCfg , direction_t *pinDir );

std_return_type_t gpioPinWrite( pin_config_t const *pinCfg , logic_t pinLogic );

std_return_type_t gpioPinRead( pin_config_t const *pinCfg , logic_t *pinLogic );

std_return_type_t gpioPinToggle( pin_config_t const *pinCfg );

// Porn configuration functions ???
std_return_type_t gpioPortDirInit( port_index_t port, uint8 portDir );

std_return_type_t gpioPortDirGet( port_index_t port, uint8 *portDir );

std_return_type_t gpioPortWrite( port_index_t port , uint8 portLogic );

std_return_type_t gpioPortRead( port_index_t port , uint8 *portLogic );

std_return_type_t gpioPortToggle( port_index_t port );

#endif	/* NEWFILE_H */

