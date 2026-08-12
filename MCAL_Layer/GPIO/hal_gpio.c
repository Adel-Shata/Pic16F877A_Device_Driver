/* 
 * File:   hal_gpio.c
 * Author: Adel Shata
 *
 * Created on August 4, 2026, 6:36 PM
 */
#include "hal_gpio.h"

/*Reference to data direction control register*/
static vuint8 *const portReg[] = { 
    &PORTA , 
    &PORTB , 
    &PORTC , 
    &PORTD , 
    &PORTE };

/*Reference to port register*/
static vuint8 *const trisReg[] = { 
    &TRISA , 
    &TRISB , 
    &TRISC , 
    &TRISD , 
    &TRISE };

static const uint8 gpioValidPinsMask[] = {
    0x3F, /* PORTA : 00111111 */
    0xFF, /* PORTB : 11111111 */ 
    0xFF, /* PORTC : 11111111 */ 
    0xFF, /* PORTD : 11111111 */ 
    0x07  /* PORTE : 00000111 */ 
};

/*Section: Functions Definition*/


/**
 * Initializing the bit 
 * @param  pinCfg
 * @return Status of the function
 *         (E_OK)     : Function has done properly
 *         (E_NOT_OK) : Function has not done properly
 */
std_return_type_t gpioPinInit(pin_config_t const *pinCfg){
    std_return_type_t returnFlag = E_OK;
    if( NULL == pinCfg )
        returnFlag = E_NOT_OK;
    else{
        returnFlag = gpioPinDirInit( pinCfg, pinCfg->direction );
        if( E_OK == returnFlag )
            returnFlag = gpioPinWrite( pinCfg, pinCfg->logic );
        else{/*NOTHING*/}
    }

    return returnFlag;
}


/**
 * Initializing th bit direction
 * @param pinCfg
 * @return Status of the function
 *         (E_OK)     : Function has done properly
 *         (E_NOT_OK) : Function has not done properly
 */
std_return_type_t gpioPinDirInit( pin_config_t const *pinCfg, direction_t pinDir ){
    std_return_type_t returnFlag = E_OK;
    
    // Checking if pinCfg, additionally if GPIO pin is valid according to the port
    if( ( NULL == pinCfg ) || 
            ( PORT_MAX_NUM <= pinCfg->port ) ||
            ( PORT_PIN_MAX_NUM <= pinCfg->pin ) ||
            ( 0 == GPIO_PIN_CHECK_VALIDITY( gpioValidPinsMask[ pinCfg->port ], pinCfg->pin )  ) )
        returnFlag = E_NOT_OK;
    else{
        switch(pinDir){
            case GPIO_DIRECTION_INPUT :
                SET_BIT( *trisReg[ pinCfg->port ], pinCfg->pin );
                break;
            case GPIO_DIRECTION_OUTPUT :
                CLEAR_BIT( *trisReg[ pinCfg->port ], pinCfg->pin );
                break;
            default:
                returnFlag = E_NOT_OK;
                break;
        };
    }
    return returnFlag;
}

/**
 * Reading the direction of the port
 * @param pinCfg
 * @param pinDir
 * @return Status of the function
 *         (E_OK)     : Function has done properly
 *         (E_NOT_OK) : Function has not done properly
 */
std_return_type_t gpioPinDirGet( pin_config_t const *pinCfg , direction_t *pinDir ){
    std_return_type_t returnFlag = E_OK;
    
    // Checking if pinCfg and pinDir are valid, additionally if GPIO pin is valid according to the port
    if( ( NULL == pinCfg ) || 
            ( NULL == pinDir ) ||
            ( PORT_MAX_NUM <= pinCfg->port ) ||
            ( PORT_PIN_MAX_NUM <= pinCfg->pin ) ||
            ( 0 == GPIO_PIN_CHECK_VALIDITY( gpioValidPinsMask[ pinCfg->port ], pinCfg->pin )  ) )
        returnFlag = E_NOT_OK;
    else
        *pinDir = ( direction_t )READ_BIT( *trisReg[ pinCfg->port ] , pinCfg->pin );
        
    return returnFlag;
}


/**
 * Writing the desired logic on the pin
 * @param pinCfg
 * @param pinLogic
 * @return Status of the function
 *         (E_OK)     : Function has done properly
 *         (E_NOT_OK) : Function has not done properly
 */
std_return_type_t gpioPinWrite( pin_config_t const *pinCfg , logic_t pinLogic ){
    std_return_type_t returnFlag = E_OK;
    
    // Checking if pinCfg and pinDir is valid, additionally if GPIO pin is valid according to the port
    if( ( NULL == pinCfg ) ||
            ( PORT_MAX_NUM <= pinCfg->port ) ||
            ( PORT_PIN_MAX_NUM <= pinCfg->pin ) ||
            ( 0 == GPIO_PIN_CHECK_VALIDITY( gpioValidPinsMask[ pinCfg->port ], pinCfg->pin )  ) )
        returnFlag = E_NOT_OK;
    else{
        switch(pinLogic){
            case GPIO_HIGH :
                SET_BIT( *portReg[ pinCfg->port ], pinCfg->pin );
                break;
            case GPIO_LOW :
                CLEAR_BIT( *portReg[ pinCfg->port ], pinCfg->pin );
                break;
            default:
                returnFlag = E_NOT_OK;
                break;
        };
    }
    return returnFlag;
}


/**
 * Reading the pin's logic
 * @param pinCfg
 * @param pinLogic
 * @return Status of the function
 *         (E_OK)     : Function has done properly
 *         (E_NOT_OK) : Function has not done properly
 */
std_return_type_t gpioPinRead( pin_config_t const *pinCfg , logic_t *pinLogic ){
    std_return_type_t returnFlag = E_OK;
    
    // Checking if pinCfg and pinDir are valid, additionally if GPIO pin is valid according to the port
    if( ( NULL == pinCfg ) || 
            ( NULL == pinLogic ) ||
            ( PORT_MAX_NUM  <= pinCfg->port ) ||
            ( PORT_PIN_MAX_NUM  <= pinCfg->pin ) ||
            ( 0 == GPIO_PIN_CHECK_VALIDITY( gpioValidPinsMask[ pinCfg->port ], pinCfg->pin )  ) )
        returnFlag = E_NOT_OK;
    else{
        *pinLogic = ( logic_t )READ_BIT( *portReg[ pinCfg->port ] , pinCfg->pin );
    }
    return returnFlag;
}


/**
 * Toggling the pin
 * @param pinCfg
 * @param pinLogic
 * @return Status of the function
 *         (E_OK)     : Function has done properly
 *         (E_NOT_OK) : Function has not done properly
 */
std_return_type_t gpioPinToggle( pin_config_t const *pinCfg ){
    std_return_type_t returnFlag = E_OK;
    
    // Checking if pinCfg is valid, additionally if GPIO pin is valid according to the port
    if( ( NULL == pinCfg ) || 
            ( PORT_MAX_NUM <= pinCfg->port ) ||
            ( PORT_PIN_MAX_NUM <= pinCfg->pin ) ||
            ( 0 == GPIO_PIN_CHECK_VALIDITY( gpioValidPinsMask[pinCfg->port], pinCfg->pin ) ) )
        returnFlag = E_NOT_OK;
    else
        TOGGLE_BIT( *portReg[pinCfg->port], pinCfg->pin );
     
    return returnFlag;
 }
 

/**
 * Initializing th port direction
 * @param pinCfg
 * @return Status of the function
 *         (E_OK)     : Function has done properly
 *         (E_NOT_OK) : Function has not done properly
 */
std_return_type_t gpioPortDirInit( port_index_t port, uint8 portDir ){
    std_return_type_t returnFlag = E_OK;
     
    if( ( PORT_MAX_NUM <= (uint8)port ) )
        returnFlag = E_NOT_OK;
    else{
        switch( portDir ){
            case GPIO_DIRECTION_OUTPUT :
                CLEAR_PORT( *trisReg[ port ], gpioValidPinsMask[ port ] );
                break;
            case GPIO_DIRECTION_INPUT :
                SET_PORT ( *trisReg[ port ], gpioValidPinsMask[ port ] );
                break;
            default :
                returnFlag = E_NOT_OK;
        };
    }
    return returnFlag;
}
 
 
/**
 * Reading the direction pf the port
 * @param pinCfg
 * @param pinDir
 * @return Status of the function
 *         (E_OK)     : Function has done properly
 *         (E_NOT_OK) : Function has not done properly
 */
std_return_type_t gpioPortDirGet( port_index_t port, uint8 *portDir ){
    std_return_type_t returnFlag = E_OK;
     
    if( ( PORT_MAX_NUM <=  (uint8)port ) ||
            ( NULL == portDir ))
        returnFlag = E_NOT_OK;
    else
        *portDir = ( *trisReg[ port ] & gpioValidPinsMask[ port ] );
    
    return returnFlag;
 }
 

/**
 * Writing the desired logic on the port
 * @param pinCfg
 * @param pinLogic
 * @return Status of the function
 *         (E_OK)     : Function has done properly
 *         (E_NOT_OK) : Function has not done properly
 */
std_return_type_t gpioPortWrite( port_index_t port , uint8 portLogic ){
    std_return_type_t returnFlag = E_OK;
    
    if( ( PORT_MAX_NUM <= (uint8)port ) )
        returnFlag = E_NOT_OK;
    /* Write only on the ports' GPIO pins */
    else
        *portReg[port] = ( ( portLogic & gpioValidPinsMask[ port ] ) | ( *portReg[port] & ( ~gpioValidPinsMask[ port ] ) ) );
    
    return returnFlag;
}


/**
 * Reading the port's logic
 * @param pinCfg
 * @param pinLogic
 * @return Status of the function
 *         (E_OK)     : Function has done properly
 *         (E_NOT_OK) : Function has not done properly
 */
std_return_type_t gpioPortRead( port_index_t port , uint8 *portLogic ){
    std_return_type_t returnFlag = E_OK;
     
    if( ( PORT_MAX_NUM <=  (uint8)port ) ||
            ( NULL == portLogic ))
        returnFlag = E_NOT_OK;
    else
        *portLogic = ( *portReg[port] & gpioValidPinsMask[port] );
    
    return returnFlag;
}


/**
 * Toggling the port
 * @param pinCfg
 * @param pinLogic
 * @return Status of the function
 *         (E_OK)     : Function has done properly
 *         (E_NOT_OK) : Function has not done properly
 */
std_return_type_t gpioPortToggle( port_index_t port ){
    std_return_type_t returnFlag = E_OK;
    
    if( ( PORT_MAX_NUM <= (uint8)port ) )
        returnFlag = E_NOT_OK;
    else
        TOGGLE_PORT( *portReg[ port ], gpioValidPinsMask[ port ] );

    return returnFlag;
}