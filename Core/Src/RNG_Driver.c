#include "RNG_Driver.h"

// Define a static variable to hold the configuration of the RNG.
static RNG_HandleTypeDef RNGConfig;

// Function to initialize the RNG hardware.
void RNG_Init(void){
    // Set the instance of the RNG.
    RNGConfig.Instance = RNG;

    // Enable the clock for the RNG hardware.
    __HAL_RCC_RNG_CLK_ENABLE();

    // Enable the RNG hardware.
    __HAL_RNG_ENABLE(&RNGConfig);

    // Initialize the RNG with the specified configuration.
    HAL_RNG_Init(&RNGConfig);
}

// Function to generate a random number.
uint32_t RNG_Generate(void){
    // Declare a variable to hold the random number.
    uint32_t RandomNumber;

    // Generate a random number and store it in the 'randomNumber' variable.
    HAL_RNG_GenerateRandomNumber(&RNGConfig, &RandomNumber);

    // Return the generated random number.
    return RandomNumber;
}
