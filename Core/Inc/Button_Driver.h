#ifndef INC_BUTTON_DRIVER_H_
#define INC_BUTTON_DRIVER_H_

#include <stdint.h>
#include <stdbool.h>
#include "LCD_Driver.h"


#define BTN_PORT 		GPIOA 		// Define the GPIO port for the button
#define BTN_PIN 		GPIO_PIN_0 	// Define the GPIO pin for the button
#define BTN_PRESSED 		1 		// Define the value indicating the button is pressed
#define BTN_NOT_PRESSED		0 		// Define the value indicating the button is not pressed

// Function prototypes
void BTN_Initalize(); // Initialize the button

void BTN_ClockEnable(); // Enable clock for the button GPIO port

void BTN_ClockDisable(); // Disable clock for the button GPIO port

bool BTN_Pressed(); // Check if the button is pressed

void BTN_Init_Interrupt(); // Initialize button interrupt

#endif /* INC_BUTTON_DRIVER_H_ */
