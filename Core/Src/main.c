#include "main.h"
#include "ApplicationCode.h"
void SystemClock_Config(void);
void SystemClockOverride(void);

int main(void)
{

  HAL_Init();

  SystemClockOverride();

  ApplicationInit(); // Initializes the LCD functionality


  HAL_Delay(500);

  static STMPE811_TouchData StaticTouchData;
  while (1)
    {
	    int PB = 0; //personal best score
        Game_Select();  // START page
        addSchedulerEvent(PLAY_EVENT_MASK);

        uint32_t eventToRun = getScheduledEvents();  // Retrieve the currently scheduled events
        while(1){
            eventToRun = getScheduledEvents();  // Refresh the event status after handling the previous events
            if(eventToRun & PLAY_EVENT_MASK){
            	InitializeGrid();
				int currentShapeIndex[4][4];
				int currentX, currentY;
				int timeloop = HAL_GetTick();
				int starttime = HAL_GetTick();
				int score = 0;
				int single = 0;
				int doubles = 0;
				int triple = 0;
				int tetris = 0;
				SpawnTetrimino(currentShapeIndex, &currentX, &currentY);
				PrintGrid();
				while(1){
					eventToRun = getScheduledEvents();
					if (returnTouchStateAndLocation(&StaticTouchData) == STMPE811_State_Pressed) {
						// Check touch coordinates for button presses
						if (StaticTouchData.x <= 150) {
							// right
							addSchedulerEvent(RIGHT_EVENT_MASK);
						}else{
							//left
							addSchedulerEvent(LEFT_EVENT_MASK);
						}
					}
					if(BTN_Pressed()){
						addSchedulerEvent(ROTATE_EVENT_MASK);
					}

					if(eventToRun & ROTATE_EVENT_MASK && !BTN_Pressed()){
						RotateTetrimino(currentShapeIndex, currentX, currentY);
						removeSchedulerEvent(ROTATE_EVENT_MASK);
		            }
					if(eventToRun & RIGHT_EVENT_MASK){
						MoveTetrimino(currentShapeIndex, &currentX, &currentY, 1);
						removeSchedulerEvent(RIGHT_EVENT_MASK);
					}
					if(eventToRun & LEFT_EVENT_MASK){
						MoveTetrimino(currentShapeIndex, &currentX, &currentY, -1);
						removeSchedulerEvent(LEFT_EVENT_MASK);
					}
					// Handle user input for moving and rotating the Tetrimino
					if(HAL_GetTick()-timeloop > FALL_TIME){
						timeloop = HAL_GetTick();
						// Move the Tetrimino down
						if(!MoveTetrimino(currentShapeIndex, &currentX, &currentY, 0)){
							// If it can't move down, place it and check for lines
							ClearLines(&score, &single, &doubles, &triple, &tetris);
							// Spawn a new Tetrimino
							if(!SpawnTetrimino(currentShapeIndex, &currentX, &currentY)){
								addSchedulerEvent(RESULTS_EVENT_MASK);
								break;
							}
						}
					}
					PrintGrid();
				}
				eventToRun = getScheduledEvents();
				if(eventToRun & RESULTS_EVENT_MASK){
					if(score > PB){
						PB = score;
					}
					Game_Select_2(score, (HAL_GetTick()-starttime) / 1000, single, doubles, triple, tetris, PB);
					removeSchedulerEvent(RESULTS_EVENT_MASK);
				}
            }
            // Handle the results and play again logic

        }
    }
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 50;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV8;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV4;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

void SystemClockOverride(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;

  __HAL_RCC_PWR_CLK_ENABLE();

  // __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1); // not needed, power scaling consumption for when not running at max freq.

  /* Enable HSE Osc and activate PLL with HSE source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);
}


void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}



