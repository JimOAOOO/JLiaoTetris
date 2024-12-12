#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include <stdint.h>
#include "Button_Driver.h"

uint32_t getScheduledEvents();

void addSchedulerEvent(uint32_t event);

void removeSchedulerEvent(uint32_t event);

// This function clears all scheduled events, resetting the event state to zero or no events scheduled.
void clearSchedulerEvent();

#define PLAY_EVENT_MASK			(1 << 0)	// Bit mask for start playing
#define RESULTS_EVENT_MASK      (1 << 1)  	// Bit mask for handling results display or processing.
#define PLAY_AGAIN_EVENT_MASK   (1 << 2)  	// Bit mask for triggering a play again functionality.
#define ROTATE_EVENT_MASK   	(1 << 3)
#define RIGHT_EVENT_MASK   		(1 << 4)
#define LEFT_EVENT_MASK   		(1 << 5)

#endif /* INC_SCHEDULER_H_ */
