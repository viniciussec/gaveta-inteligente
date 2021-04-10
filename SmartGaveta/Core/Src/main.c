/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <string.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {
	/* USER CODE BEGIN 1 */

	/* USER CODE END 1 */

	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* USER CODE BEGIN Init */

	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClock_Config();

	/* USER CODE BEGIN SysInit */

	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	/* USER CODE BEGIN 2 */
	char nome_objeto[25];
	char objetos[16][25];
	char objetos_referência[16][GPIO_PinState];
	char entrada_pergunta = 'p';
	GPIO_PinState tensoes_teclado[4][4];

	int readBit(unsigned char x, int bit) {
		unsigned char mask = (0x01 << bit);
		if ((x & mask) == 0x00) {
			return 0;
		} else {
			return 1;
		}
	}

	void setABCD(int x) {
		HAL_GPIO_WritePin(GPIOB_BASE, GPIO_PIN_0, readBit(x, 0));
		HAL_GPIO_WritePin(GPIOB_BASE, GPIO_PIN_1, readBit(x, 1));
		HAL_GPIO_WritePin(GPIOB_BASE, GPIO_PIN_2, readBit(x, 2));
		HAL_GPIO_WritePin(GPIOB_BASE, GPIO_PIN_3, readBit(x, 3));
	}

	void setABteclado(int x) {
		HAL_GPIO_WritePin(GPIOA_BASE, GPIO_PIN_4, readBit(x, 0));
		HAL_GPIO_WritePin(GPIOA_BASE, GPIO_PIN_5, readBit(x, 1));
	}

	void guardar_objeto(char *x, int posx, int posy) {
		strcpy(objetos[x][y], x);
	}

	void retirar_objeto(int posx, int posy) {
		memset(objetos[x][y], 0, strlen(objetos[x][y]));
	}

	void encontrar_objeto(char *entrada) {
		int encontrou = 0;
		for (int i = 0; i < 16; i++) {
			if (strcmp(entrada, objetos[i]) == 0) {
				setABCD(i);
				HAL_GPIO_WritePin(GPIOB_BASE, GPIO_PIN_5, SET);
				HAL_Delay(100);
				HAL_GPIO_WritePin(GPIOB_BASE, GPIO_PIN_5, RESET);
				encontrou = 1;
			} else {
				setABCD(i);
				HAL_GPIO_WritePin(GPIOB_BASE, GPIO_PIN_4, SET);
				HAL_Delay(100);
				HAL_GPIO_WritePin(GPIOB_BASE, GPIO_PIN_4, RESET);
			}
		}

		if (encontrou == 0) {
			esperar_entrada(entrada);
		}
	}

	void esperar_entrada(String entrada) {
		//CORES: PB4, PB5, PB6
		entrada_pergunta = 'a';
		int i = 0;

		while (entrada_pergunta == 'a') {
			setABCD(i);
			HAL_GPIO_WritePin(GPIOB_BASE, GPIO_PIN_4, SET);
			HAL_GPIO_WritePin(GPIOB_BASE, GPIO_PIN_5, SET);
			HAL_Delay(100);
			HAL_GPIO_WritePin(GPIOB_BASE, GPIO_PIN_4, RESET);
			HAL_GPIO_WritePin(GPIOB_BASE, GPIO_PIN_5, RESET);
		}
		if (entrada_pergunta == 's') {
			mostrar_posicoes_disponiveis();
		} else {
			memset(nome_objeto, 0, strlen(nome_objeto));
			entrada_pergunta = 'p';
		}
	}

	void mostrar_posicoes_disponiveis() {
		HAL_GPIO_WritePin(GPIOA_BASE, GPIO_PIN_11, GPIO_PIN_SET);
		for (int i = 0; i < 4; i++) {
			setABteclado(i);
			for (int j = 0; j < 4; j++) {
				unit_16t pino = 0x01 << 7;
				int fechado = HAL_GPIO_ReadPin(GPIOA_BASE, pino << j);
				if (fechado == 1) {
					int numLED = 4 * i + j;
					HAL_GPIO_WritePin(GPIOB_BASE, GPIO_PIN_4, GPIO_PIN_SET);
					HAL_GPIO_WritePin(GPIOB_BASE, GPIO_PIN_5, GPIO_PIN_SET);
					setABCD(numLED);
					HAL_Delay(1000);
					HAL_GPIO_WritePin(GPIOB_BASE, GPIO_PIN_4, GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOB_BASE, GPIO_PIN_5, GPIO_PIN_RESET);
				}
			}
		}
		HAL_GPIO_WritePin(GPIOA_BASE, GPIO_PIN_11, GPIO_PIN_RESET);
	}

	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1) {
		//POSIÇÕES DA GAVETA
		for (int i = 0; i < 4; i++) {
			HAL_GPIO_WritePin(GPIOA_BASE, GPIO_PIN_11, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA_BASE, GPIO_PIN_12, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA_BASE, GPIO_PIN_13, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA_BASE, GPIO_PIN_14, GPIO_PIN_RESET);
			//HAL_GPIO_WritePin(GPIOA_BASE, PINO_ITERADO, GPIO_PIN_SET);

			if (HAL_GPIO_ReadPin(GPIOA_BASE, GPIO_PIN_17) == GPIO_PIN_SET) {

			}

			if (HAL_GPIO_ReadPin(GPIOA_BASE, GPIO_PIN_8) == GPIO_PIN_SET) {

			}

			if (HAL_GPIO_ReadPin(GPIOA_BASE, GPIO_PIN_9) == GPIO_PIN_SET) {

			}

			if (HAL_GPIO_ReadPin(GPIOA_BASE, GPIO_PIN_10) == GPIO_PIN_SET) {

			}

		}

		//POSIÇÕES DO TECLADO
		for (int i = 0; i < 4; i++) {
			HAL_GPIO_WritePin(GPIOA_BASE, GPIO_PIN_3, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA_BASE, GPIO_PIN_4, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA_BASE, GPIO_PIN_5, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA_BASE, GPIO_PIN_6, GPIO_PIN_RESET);
//			HAL_GPIO_WritePin(GPIOA_BASE, PINO_ITERADO, GPIO_PIN_SET);

			if (HAL_GPIO_ReadPin(GPIOA_BASE, GPIO_PIN_0) == GPIO_PIN_SET) {
				if (entrada_pergunta == 'p') {

					if (i == 3) {
						nome_objeto[strlen(nome_objeto) - 1] = '\0';
					}
				}

				if (i == 0 && entrada_pergunta == 'a') {
					entrada_pergunta = 's';
				}
			}
			if (HAL_GPIO_ReadPin(GPIOA_BASE, GPIO_PIN_1) == GPIO_PIN_SET) {

				if (i == 3) {
					nome_objeto[strlen(nome_objeto)] = ' ';
				}
				if (i == 0 && entrada_pergunta == 'a') {
					entrada_pergunta = 'p';
				}
			}
			if (HAL_GPIO_ReadPin(GPIOA_BASE, GPIO_PIN_2) == GPIO_PIN_SET) {

				if (i == 3) {
					encontrar_objeto(nome_objeto);
				}
			}
		}

		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */

	}
	/* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}
	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK) {
		Error_Handler();
	}
}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void) {
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_11,
			GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOB,
			GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4
					| GPIO_PIN_5 | GPIO_PIN_6, GPIO_PIN_RESET);

	/*Configure GPIO pins : PA0 PA1 PA2 PA7
	 PA8 PA9 PA10 */
	GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_7
			| GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/*Configure GPIO pins : PA3 PA4 PA5 PA11 */
	GPIO_InitStruct.Pin = GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_11;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/*Configure GPIO pins : PB0 PB1 PB2 PB3
	 PB4 PB5 PB6 */
	GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3
			| GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1) {
	}
	/* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
