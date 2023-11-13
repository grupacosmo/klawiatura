/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "usb_device.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
enum ModifiersCodes{
  NO_MOD = 0x00,
  MOD_LCTRL = 0x01,
  MOD_LSHIFT = 0x02,
  MOD_LALT = 0x04,
  MOD_LMETA = 0x08, // key with Windows logo
  MOD_RCTRL = 0x10,
  MOD_RSHIFT = 0x20,
  MOD_RALT = 0x40
};
enum KeyCodes {
  NO_KEY = 0x00,
  KEY_A = 0x04,
  KEY_B = 0x05,
  KEY_C = 0x06,
  KEY_D = 0x07,
  KEY_E = 0x08,
  KEY_F = 0x09,
  KEY_G = 0x0A,
  KEY_H = 0x0B,
  KEY_I = 0x0C,
  KEY_J = 0x0D,
  KEY_K = 0x0E,
  KEY_L = 0x0F,
  KEY_M = 0x10,
  KEY_N = 0x11,
  KEY_O = 0x12,
  KEY_P = 0x13,
  KEY_Q = 0x14,
  KEY_R = 0x15,
  KEY_S = 0x16,
  KEY_T = 0x17,
  KEY_U = 0x18,
  KEY_V = 0x19,
  KEY_W = 0x1A,
  KEY_X = 0x1B,
  KEY_Y = 0x1C,
  KEY_Z = 0x1D,
  KEY_1 = 0x1E, // 1 and !
  KEY_2 = 0x1F, // 2 and @
  KEY_3 = 0x20, // 3 and #
  KEY_4 = 0x21, // 4 and $
  KEY_5 = 0x22, // 5 and %
  KEY_6 = 0x23, // 6 and ^
  KEY_7 = 0x24, // 7 and &
  KEY_8 = 0x25, // 8 and *
  KEY_9 = 0x26, // 9 and (
  KEY_0 = 0x27, // 0 and )
  KEY_ENTER = 0x28,
  KEY_ESC = 0x29,
  KEY_BACKSPACE = 0x2A,
  KEY_TAB = 0x2B,
  KEY_SPACE = 0x2C,
  KEY_MINUS = 0x2D, // - and _
  KEY_EQ = 0x2E, // = and +
  KEY_LBRACE = 0x2F, // [ anf {
  KEY_RBRACE = 0x30, // ] and }
  KEY_BACKSLASH = 0x31, // \ and |
  KEY_SEMICOLON = 0x33, // ; and :
  KEY_APOSTROPHE = 0x34, // ' and "
  KEY_COMMA = 0x36, // , and <
  KEY_DOT = 0x37, // . and >
  KEY_SLASH = 0x38, // / and ?
  KEY_CAPSLOCK = 0x39,
  KEY_SCROLLOCK = 0x47,
  KEY_PAUSE = 0x48,
  KEY_INSERT = 0x49,
  KEY_HOME = 0x4A
};

/* USER CODE BEGIN PV */
int debugInt = 0;
extern USBD_HandleTypeDef hUsbDeviceFS;

typedef struct
{
	uint8_t MODIFIER;  // alt, ctrl etc.
	uint8_t RESERVED;
	uint8_t KEYCODES[6]; // up to 6 keys
}subKeyBoard;

subKeyBoard keyBoardHIDsub;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */
static void keyboardHIDsub_Init(void){
  keyBoardHIDsub.MODIFIER = NO_MOD;
  keyBoardHIDsub.RESERVED = 0x00;
  for(int i = 0; i < 6; i++){
      keyBoardHIDsub.KEYCODES[i] = NO_KEY;
  }
}
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
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
  MX_USB_DEVICE_Init();
  /* USER CODE BEGIN 2 */
  keyboardHIDsub_Init();
  int i;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    for(i = 0; i < 6; i++){
      keyBoardHIDsub.KEYCODES[i] = NO_KEY; // clear
    }
    
    i = 0;
    if(HAL_GPIO_ReadPin(BUTTON_A_GPIO_Port, BUTTON_A_Pin) == GPIO_PIN_RESET){
        keyBoardHIDsub.KEYCODES[i]=KEY_A;  // Press A key
        i++;
        debugInt = 4;
    }
    if(HAL_GPIO_ReadPin(BUTTON_B_GPIO_Port, BUTTON_B_Pin) == GPIO_PIN_RESET){
      keyBoardHIDsub.KEYCODES[i]=KEY_B;
      i++;
      debugInt = 5;
    }
    if(HAL_GPIO_ReadPin(BUTTON_C_GPIO_Port, BUTTON_C_Pin) == GPIO_PIN_RESET){
      keyBoardHIDsub.KEYCODES[i]=KEY_C;
      debugInt = 6;
    }
    else{
      debugInt = 8;
    }
    USBD_HID_SendReport(&hUsbDeviceFS,&keyBoardHIDsub,sizeof(keyBoardHIDsub));
    HAL_Delay(50);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI48;
  RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI48;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB;
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_HSI48;

  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin : BUTTON_B_Pin */
  GPIO_InitStruct.Pin = BUTTON_B_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(BUTTON_B_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : BUTTON_A_Pin */
  GPIO_InitStruct.Pin = BUTTON_A_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(BUTTON_A_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : BUTTON_C_Pin */
  GPIO_InitStruct.Pin = BUTTON_C_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(BUTTON_C_GPIO_Port, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
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
