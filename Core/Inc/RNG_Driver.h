

#ifndef INC_RNG_DRIVER_H_
#define INC_RNG_DRIVER_H_

#include "LCD_Driver.h"
#include "Scheduler.h"


void RNG_Init(void);

uint32_t RNG_Generate(void);


#endif /* INC_RNG_DRIVER_H_ */
