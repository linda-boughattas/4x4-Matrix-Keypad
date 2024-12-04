#include "main.h"

/* Private variables ---------------------------------------------------------*/
const char gKeypad_Btn_Values[4][4] =  {  {'1', '2', '3', 'A'},
	                                          {'4', '5', '6', 'B'},
	                                          {'7', '8', '9', 'C'},
	                                          {'*', '0', '#', 'D'},
                                         };
volatile int gLine;
volatile int gColumn;
volatile int gKeyPressed=-1;

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
																				 
int main(void)
{
  HAL_Init();
  SystemClock_Config();
  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  while (1)
  {
		/* Set all rows to HIGH (sequentially) */
		gLine=0;
		HAL_GPIO_WritePin (GPIOB, GPIO_PIN_13, GPIO_PIN_RESET); 
		HAL_GPIO_WritePin (GPIOB, GPIO_PIN_1, GPIO_PIN_SET); 
		HAL_Delay (50);
		
		gLine=1;
		HAL_GPIO_WritePin (GPIOB, GPIO_PIN_1, GPIO_PIN_RESET); 
		HAL_GPIO_WritePin (GPIOB, GPIO_PIN_15, GPIO_PIN_SET); 
		HAL_Delay (50);
		
		gLine=2;
		HAL_GPIO_WritePin (GPIOB, GPIO_PIN_15, GPIO_PIN_RESET); 
		HAL_GPIO_WritePin (GPIOB, GPIO_PIN_14, GPIO_PIN_SET); 
		HAL_Delay (50);
		
		gLine=3;
		HAL_GPIO_WritePin (GPIOB, GPIO_PIN_14, GPIO_PIN_RESET); 
		HAL_GPIO_WritePin (GPIOB, GPIO_PIN_13, GPIO_PIN_SET); 
		HAL_Delay (50);
  }

}
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
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pins : PB1 PB13 PB14 PB15 */
  GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PB10 PB4 PB5 */
  GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_4|GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PA8 */
  GPIO_InitStruct.Pin = GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI4_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI4_IRQn);

  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
}

/* INTERRUPTIONS */
/* When a button is pressed, send an interrupt with the value of the pressed keypad button. */

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	UNUSED (GPIO_Pin);
	if (HAL_GPIO_ReadPin (GPIOA, GPIO_PIN_8))
	{gColumn=0;
	}
	if (HAL_GPIO_ReadPin (GPIOB, GPIO_PIN_10))
	{gColumn=1;
	}
	if (HAL_GPIO_ReadPin (GPIOB, GPIO_PIN_4))
	{gColumn=2;
	}
	if (HAL_GPIO_ReadPin (GPIOB, GPIO_PIN_5))
	{gColumn=3;
	}
	gKeyPressed=gKeypad_Btn_Values [gLine] [gColumn] ;
}

void Error_Handler(void)
{
  __disable_irq();
  while (1)
  {
  }

}

#ifdef  USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line)
{
}
#endif /* USE_FULL_ASSERT */
