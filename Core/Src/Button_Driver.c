#include "Button_Driver.h"

GPIO_InitTypeDef BtnConfig = {0}; // Define a global variable for the GPIO handle configuration

// Initialize the button
void BTN_Initalize() {
    BtnConfig.Pin = BTN_PIN; // Set pin number for the button
    BtnConfig.Mode = GPIO_MODE_INPUT; // Set pin mode as input
    BTN_ClockEnable(); // Enable clock for the button GPIO port
    __NVIC_EnableIRQ(EXTI0_IRQn); // Enable interrupt for EXTI0
    HAL_GPIO_Init(BTN_PORT, &BtnConfig); // Initialize GPIO configuration for the button
}

// Enable clock for the button
void BTN_ClockEnable() {
	__HAL_RCC_GPIOA_CLK_ENABLE(); // Enable clock for GPIO port A
}

// Check if the button is pressed
bool BTN_Pressed() {
    uint8_t check = HAL_GPIO_ReadPin(BTN_PORT, BTN_PIN); // Read the state of the button pin
    if (check == BTN_PRESSED) { // If the button is pressed, return true
        return true;
    } else { // Otherwise, return false
        return false;
    }
}

// Initialize button with interrupt
void BTN_Init_Interrupt() {
    BtnConfig.Pin = BTN_PIN; // Set pin number for the button
    BtnConfig.Mode = GPIO_MODE_IT_RISING_FALLING; // Set pin mode as input
    BTN_ClockEnable(); // Enable clock for the button GPIO port
    __NVIC_EnableIRQ(EXTI0_IRQn); // Enable interrupt for EXTI0
    HAL_GPIO_Init(BTN_PORT, &BtnConfig); // Initialize GPIO configuration for the button
}

