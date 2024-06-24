/* USER CODE BEGIN Header */


// if Chinese character cant be displayed, use notepad++


/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "crc.h"
#include "dma2d.h"
#include "quadspi.h"
#include "usart.h"
#include "gpio.h"
#include "fmc.h"
#include "app_x-cube-ai.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include "stm32h747i_discovery.h"
#include "stm32h747i_discovery_lcd.h"
#include "stm32h747i_discovery_sdram.h"
#include "stm32h747i_discovery_bus.h"
#include "stm32h747i_discovery_ts.h"
#include "stm32_lcd.h"
#include "ai_datatypes_defines.h"
#include "ai_platform.h"
#include "network.h"
#include "network_data.h"
#include "otm8009a.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
#define LCD_FRAME_BUFFER        0xD0000000

extern LTDC_HandleTypeDef hlcd_ltdc;
static DMA2D_HandleTypeDef   hdma2d;
extern DSI_HandleTypeDef hlcd_dsi;
DSI_VidCfgTypeDef hdsivideo_handle;
DSI_CmdCfgTypeDef CmdCfg;
DSI_LPCmdTypeDef LPCmd;
DSI_PLLInitTypeDef dsiPllInit;
static RCC_PeriphCLKInitTypeDef  PeriphClkInitStruct;
OTM8009A_Object_t *pObj;

TS_Init_t *hTS;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

#ifndef HSEM_ID_0
#define HSEM_ID_0 (0U) /* HW semaphore 0*/
#endif

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
#define VSYNC               1 
#define VBP                 1 
#define VFP                 1
#define VACT                480
#define HSYNC               1
#define HBP                 1
#define HFP                 1
#define HACT                800

#define LAYER0_ADDRESS               (LCD_FB_START_ADDRESS)

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint8_t My_String[60];
TS_State_t  TS_State = {0};

AI_ALIGNED(4) ai_u8 in_data[AI_NETWORK_IN_1_SIZE_BYTES];  //4字节对齐
AI_ALIGNED(4) ai_float out_data[AI_NETWORK_OUT_1_SIZE_BYTES];

ai_u8 temp_in[28][28] = {0};

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE BEGIN PFP */
static void CopyBuffer(uint32_t *pSrc, 
                           uint32_t *pDst, 
                           uint16_t x, 
                           uint16_t y, 
                           uint16_t xsize, 
                           uint16_t ysize);
static uint8_t LCD_Init(void);
void LTDC_Init(void);

static void LCD_LayertInit(uint16_t LayerIndex, uint32_t Address);
static int32_t DSI_IO_Write(uint16_t ChannelNbr, uint16_t Reg, uint8_t *pData, uint16_t Size);
static int32_t DSI_IO_Read(uint16_t ChannelNbr, uint16_t Reg, uint8_t *pData, uint16_t Size);
int32_t LCD_GetXSize(uint32_t Instance, uint32_t *XSize);
int32_t LCD_GetYSize(uint32_t Instance, uint32_t *YSize);
void LCD_MspInit(void);

static void LCD_BriefDisplay(void);

const LCD_UTILS_Drv_t LCD_UTIL_Driver =
{
  BSP_LCD_DrawBitmap,
  BSP_LCD_FillRGBRect,
  BSP_LCD_DrawHLine,
  BSP_LCD_DrawVLine,
  BSP_LCD_FillRect,
  BSP_LCD_ReadPixel,
  BSP_LCD_WritePixel,
  LCD_GetXSize,
  LCD_GetYSize,
  BSP_LCD_SetActiveLayer,
  BSP_LCD_GetPixelFormat
};

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/***********************/
//encoding ANSI
/***********************/

//参考https://www.cnblogs.com/birdBull/p/15697213.html
//这段代码的作用是在不用MicroLib的情况下重定向printf到串口输出

#pragma import(__use_no_semihosting)  
void _sys_exit(int x)  
{  
x = x;  
}  
struct __FILE  
{  
int handle;  
/* Whatever you require here. If the only file you are using is */  
/* standard output using printf() for debugging, no file handling */  
/* is required. */  
};  
FILE __stdout; 

void _ttywrch(int ch)
{
	ch = ch;
}
/*fputc*/
uint8_t ch;
int fputc(int c, FILE * f)
{
    ch=c;
    HAL_UART_Transmit(&huart1,&ch,1,1000);
    return c;
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */
	char Tx_buf[50];
  int Tx_buf_len = 0;
  /* USER CODE END 1 */
/* USER CODE BEGIN Boot_Mode_Sequence_0 */
  int32_t timeout;
/* USER CODE END Boot_Mode_Sequence_0 */

  /* Enable the CPU Cache */

  /* Enable I-Cache---------------------------------------------------------*/
  SCB_EnableICache();

  /* Enable D-Cache---------------------------------------------------------*/
  SCB_EnableDCache();

/* USER CODE BEGIN Boot_Mode_Sequence_1 */
  /* Wait until CPU2 boots and enters in stop mode or timeout*/
  timeout = 0xFFFF;
  while((__HAL_RCC_GET_FLAG(RCC_FLAG_D2CKRDY) != RESET) && (timeout-- > 0));
  if ( timeout < 0 )
  {
  Error_Handler();
  }
/* USER CODE END Boot_Mode_Sequence_1 */
  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();
/* USER CODE BEGIN Boot_Mode_Sequence_2 */
/* When system initialization is finished, Cortex-M7 will release Cortex-M4 by means of
HSEM notification */
/*HW semaphore Clock enable*/
__HAL_RCC_HSEM_CLK_ENABLE();
/*Take HSEM */
HAL_HSEM_FastTake(HSEM_ID_0);
/*Release HSEM in order to notify the CPU2(CM4)*/
HAL_HSEM_Release(HSEM_ID_0,0);
/* wait until CPU2 wakes up from stop mode */
timeout = 0xFFFF;
while((__HAL_RCC_GET_FLAG(RCC_FLAG_D2CKRDY) == RESET) && (timeout-- > 0));
if ( timeout < 0 )
{
Error_Handler();
}
/* USER CODE END Boot_Mode_Sequence_2 */

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA2D_Init();
  MX_USART1_UART_Init();
  MX_FMC_Init();
  MX_QUADSPI_Init();
  MX_CRC_Init();
  MX_X_CUBE_AI_Init();
  /* USER CODE BEGIN 2 */
	/* Initialize used Leds */
  BSP_LED_Init(LED3);

  /* Initialize the SDRAM */
  BSP_SDRAM_Init(0);
  
  /* Initialize the LCD   */
  if( LCD_Init() != BSP_ERROR_NONE)
  {
    Error_Handler();
  } 
  
	/* Set the LCD Context */
  Lcd_Ctx[0].ActiveLayer = 0;
  Lcd_Ctx[0].PixelFormat = LCD_PIXEL_FORMAT_ARGB8888;
  Lcd_Ctx[0].BppFactor = 4; /* 4 Bytes Per Pixel for ARGB8888 */  
  Lcd_Ctx[0].XSize = 800;  
  Lcd_Ctx[0].YSize = 480;
  /* Disable DSI Wrapper in order to access and configure the LTDC */
  __HAL_DSI_WRAPPER_DISABLE(&hlcd_dsi);

  /* Initialize LTDC layer 0 iused for Hint */  
  LCD_LayertInit(0, LCD_FRAME_BUFFER); 
  UTIL_LCD_SetFuncDriver(&LCD_UTIL_Driver);
  
  /* Enable DSI Wrapper so DSI IP will drive the LTDC */
  __HAL_DSI_WRAPPER_ENABLE(&hlcd_dsi);  
    
  /* Display example brief   */
  LCD_BriefDisplay();
    
  /*Refresh the LCD display*/
  HAL_DSI_Refresh(&hlcd_dsi);  //更新完成后，产生中断，进入中断服务程序

	/* Touchscreen initialization */
	uint32_t ts_status = BSP_ERROR_NONE;
	uint32_t x_size, y_size;
	
	BSP_LCD_GetXSize(0, &x_size);
  BSP_LCD_GetYSize(0, &y_size);
  hTS->Width = x_size;
  hTS->Height = y_size;
  hTS->Orientation = TS_SWAP_XY | TS_SWAP_Y;
  hTS->Accuracy = 0;
	ts_status = BSP_TS_Init(0, hTS);
	printf("lcd test\r\n");
  if(ts_status == BSP_ERROR_NONE)
  {
    /* Display touch screen demo description */
		UTIL_LCD_FillRect(50, 150, 280, 280, UTIL_LCD_COLOR_BLACK);  //DrawArea

		UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_YELLOW);
		UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_ST_BROWN);
		UTIL_LCD_FillRect(400, 150, 150, 50, UTIL_LCD_COLOR_RED);   // ????
		UTIL_LCD_FillRect(405, 155, 140, 40, UTIL_LCD_COLOR_ST_BROWN);  // ????
		UTIL_LCD_DisplayStringAt(440,170,(uint8_t*) "CLEAR", LEFT_MODE);
		UTIL_LCD_FillRect(400, 250, 150, 50, UTIL_LCD_COLOR_RED);   // ????
		UTIL_LCD_FillRect(405, 255, 140, 40, UTIL_LCD_COLOR_ST_BROWN);  // ????
		UTIL_LCD_DisplayStringAt(430,270,(uint8_t*) "PREDICT", LEFT_MODE);
		HAL_DSI_Refresh(&hlcd_dsi);  //更新完成后，产生中断，进入中断服务程序
	}
	else
	{
		printf("%d\r\n",ts_status);
	}
	
	//AI part
	Tx_buf_len = sprintf(Tx_buf, "\r\n\r\nSTM32 X-Cube-AI test\r\n");
	HAL_UART_Transmit(&huart1, (uint8_t *)Tx_buf, Tx_buf_len, 100);

	ai_u8 activations[AI_NETWORK_DATA_ACTIVATIONS_SIZE+8192];//+8192是为了避免内存错误，详见课程报告
	
	 /* AI buffer IO handlers */
	ai_buffer *ai_input;
	ai_buffer *ai_output;

	ai_handle network = AI_HANDLE_NULL;

	ai_error err;
	ai_network_report report;

	/** @brief Initialize network */
	const ai_handle acts[] = { activations };

	err = ai_network_create_and_init(&network, acts, NULL);
	if (err.type != AI_ERROR_NONE) {
		Tx_buf_len = sprintf(Tx_buf, "Error: could not create NN instance\r\n");
		HAL_UART_Transmit(&huart1, (uint8_t *)Tx_buf, Tx_buf_len, 100);
		return -1;
	}
	else
	{
		Tx_buf_len = sprintf(Tx_buf, "success in create NN instance\r\n");
		HAL_UART_Transmit(&huart1, (uint8_t *)Tx_buf, Tx_buf_len, 100);
	}

	if (ai_network_get_report(network, &report) != true) {
		Tx_buf_len = sprintf(Tx_buf, "ai get report error\r\n");
		HAL_UART_Transmit(&huart1, (uint8_t *)Tx_buf, Tx_buf_len, 100);
	}
	
	Tx_buf_len = sprintf(Tx_buf, "Model name      : ");
	HAL_UART_Transmit(&huart1, (uint8_t *)Tx_buf, Tx_buf_len, 100);
	Tx_buf_len = sprintf(Tx_buf, report.model_name);
	HAL_UART_Transmit(&huart1, (uint8_t *)Tx_buf, Tx_buf_len, 100);
	
	//	Tx_buf_len = sprintf(Tx_buf, "\r\nModel signature : ");
	//	HAL_UART_Transmit(&huart1, (uint8_t *)Tx_buf, Tx_buf_len, 100);
	//	Tx_buf_len = sprintf(Tx_buf, report.model_signature);
	//	HAL_UART_Transmit(&huart1, (uint8_t *)Tx_buf, Tx_buf_len, 100);

	ai_input = &report.inputs[0];
	ai_output = &report.outputs[0];

	//link inputs and outputs to the model
	ai_input[0].data = AI_HANDLE_PTR(in_data);
	ai_output[0].data = AI_HANDLE_PTR(out_data);
	
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		ts_status = BSP_TS_GetState(0, &TS_State);
		if(TS_State.TouchDetected)
		{
			//for debugging
			//printf("touched\r\n");
			//printf("X=%d\r\n",TS_State.TouchX);
			//printf("Y=%d\r\n",TS_State.TouchY);
			
			ai_u8 temp_transfer[28][28]={0};
			
			//act==draw
			if(TS_State.TouchX > 50 && TS_State.TouchX < 330
				&&TS_State.TouchY > 150 && TS_State.TouchY < 430)
			{		
				//先用二维数组临时存一下
				int x = (TS_State.TouchX-50)/10;
				int y = (TS_State.TouchY-150)/10;
				temp_in[x][y]=(float)255;
				temp_in[x-1][y-1] = (float)127;
				temp_in[x][y-1] = (float)127;
				temp_in[x-1][y] = (float)127;
				
				UTIL_LCD_FillCircle(TS_State.TouchX,TS_State.TouchY,4, UTIL_LCD_COLOR_WHITE );
				HAL_DSI_Refresh(&hlcd_dsi);
				//printf("draw\r\n");
				
			}
			//act==clear
			else if(TS_State.TouchX > 400 && TS_State.TouchX < 550
				&&TS_State.TouchY > 150 && TS_State.TouchY < 200)
			{
				UTIL_LCD_FillRect(50, 150, 280, 280, UTIL_LCD_COLOR_BLACK);  //CLEAR
				for(int i=0;i<28;i++){
					for(int j=0;j<28;j++){
						temp_in[i][j] = 0;
						temp_transfer[i][j] = 0;
						in_data[i*28+j] = 0;//CLEAR
					}
				}

				UTIL_LCD_FillRect(400,380,300,30,UTIL_LCD_COLOR_ST_BLUE);
				//UTIL_LCD_DisplayStringAt(400,380,(uint8_t*)"                      ", LEFT_MODE);
				HAL_DSI_Refresh(&hlcd_dsi);
				printf("cleared\r\n");
			}
			else if(TS_State.TouchX>400&&TS_State.TouchX<550&&TS_State.TouchY>250&&TS_State.TouchY<300)
			{
				//PREDICT
				printf("predicting\r\n");
				for(int i=0;i<28;i++)
				{
					for(int j=0;j<28;j++)
					{
						temp_transfer[i][j] = temp_in[j][i];//转置一下
						//printf("%d  ",temp_in[j][i]);
					}
					//printf("\r\n");
				}
				for(int i=0;i<28;i++){
					for(int j=0;j<28;j++){
						in_data[i*28+j] = temp_transfer[i][j];//转一维数组
					}
				}	
				char my_result[10] = {0};
			
				ai_i32 n_batch;
				n_batch = ai_network_run(network, &ai_input[0], &ai_output[0]);
				if (n_batch != 1) {
					err = ai_network_get_error(network);
					Tx_buf_len = sprintf(Tx_buf,"ai run error %d, %d\r\n", err.type, err.code);
					HAL_UART_Transmit(&huart1, (uint8_t *)Tx_buf, Tx_buf_len, 100);

				return -1;
				} 
				
				Tx_buf_len = sprintf(Tx_buf,"\r\n prediction successful \r\n");
				HAL_UART_Transmit(&huart1, (uint8_t *)Tx_buf, Tx_buf_len, 100);
				
				float my_max = 0;
				int max_index = 0;
				//AI_NETWORK_OUT_1_SIZE == 36
				for (int i = 0; i < AI_NETWORK_OUT_1_SIZE; i++) {
					if(out_data[i] > my_max){			
						my_max = out_data[i];
						max_index = i;
					}
				}
				if(max_index<10)
					my_result[0] = '0' + (char)max_index;
				else
					my_result[0] = 'A' + (char)max_index;
			
				printf("%s",my_result);
				UTIL_LCD_SetFont(&Font24);
				UTIL_LCD_DisplayStringAt(400,380,(uint8_t*)"the result is: ", LEFT_MODE);
				UTIL_LCD_DisplayStringAt(650,380,(uint8_t*)my_result, LEFT_MODE);
				HAL_DSI_Refresh(&hlcd_dsi);
				HAL_Delay(1000);
			}				
		}
    /* USER CODE END WHILE */

	//MX_X_CUBE_AI_Process();
	
    /* USER CODE BEGIN 3 */
		//AI_Process必须注释掉
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

  /** Supply configuration update enable
  */
  HAL_PWREx_ConfigSupply(PWR_DIRECT_SMPS_SUPPLY);

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 2;
  RCC_OscInitStruct.PLL.PLLN = 64;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_3;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_D3PCLK1|RCC_CLOCKTYPE_D1PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
/**
  * @brief  Gets the LCD X size.
  * @param  Instance  LCD Instance
  * @param  XSize     LCD width
  * @retval BSP status
  */
int32_t LCD_GetXSize(uint32_t Instance, uint32_t *XSize)
{
  *XSize = Lcd_Ctx[0].XSize;
 
  return BSP_ERROR_NONE;
}

/**
  * @brief  Gets the LCD Y size.
  * @param  Instance  LCD Instance
  * @param  YSize     LCD Height
  * @retval BSP status
  */
int32_t LCD_GetYSize(uint32_t Instance, uint32_t *YSize)
{
  *YSize = Lcd_Ctx[0].YSize;
 
  return BSP_ERROR_NONE;
}
static uint8_t LCD_Init(void)
{
  DSI_PHY_TimerTypeDef  PhyTimings;
  OTM8009A_IO_t              IOCtx;
  static OTM8009A_Object_t   OTM8009AObj;
  static void                *Lcd_CompObj = NULL;
  
  /* Toggle Hardware Reset of the DSI LCD using
     its XRES signal (active low) */
  BSP_LCD_Reset(0);
  
  /* Call first MSP Initialize only in case of first initialization
  * This will set IP blocks LTDC, DSI and DMA2D
  * - out of reset
  * - clocked
  * - NVIC IRQ related to IP blocks enabled
  */
  LCD_MspInit();

  /* LCD clock configuration */
  /* LCD clock configuration */
  /* PLL3_VCO Input = HSE_VALUE/PLL3M = 5 Mhz */
  /* PLL3_VCO Output = PLL3_VCO Input * PLL3N = 800 Mhz */
  /* PLLLCDCLK = PLL3_VCO Output/PLL3R = 800/19 = 42 Mhz */
  /* LTDC clock frequency = PLLLCDCLK = 42 Mhz */
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_LTDC;
  PeriphClkInitStruct.PLL3.PLL3M = 5;    
  PeriphClkInitStruct.PLL3.PLL3N = 160;
  PeriphClkInitStruct.PLL3.PLL3FRACN = 0;
  PeriphClkInitStruct.PLL3.PLL3P = 2;
  PeriphClkInitStruct.PLL3.PLL3Q = 2;  
  PeriphClkInitStruct.PLL3.PLL3R = 19;
  PeriphClkInitStruct.PLL3.PLL3VCOSEL = RCC_PLL3VCOWIDE;
  PeriphClkInitStruct.PLL3.PLL3RGE = RCC_PLL3VCIRANGE_2;
  HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct);   
  
  /* Base address of DSI Host/Wrapper registers to be set before calling De-Init */
  hlcd_dsi.Instance = DSI;
  
  HAL_DSI_DeInit(&(hlcd_dsi));
  
  dsiPllInit.PLLNDIV  = 100;
  dsiPllInit.PLLIDF   = DSI_PLL_IN_DIV5;
  dsiPllInit.PLLODF  = DSI_PLL_OUT_DIV1;  

  hlcd_dsi.Init.NumberOfLanes = DSI_TWO_DATA_LANES;
  hlcd_dsi.Init.TXEscapeCkdiv = 0x4;
  
  
  HAL_DSI_Init(&(hlcd_dsi), &(dsiPllInit));
    
  /* Configure the DSI for Command mode */
  CmdCfg.VirtualChannelID      = 0;
  CmdCfg.HSPolarity            = DSI_HSYNC_ACTIVE_HIGH;
  CmdCfg.VSPolarity            = DSI_VSYNC_ACTIVE_HIGH;
  CmdCfg.DEPolarity            = DSI_DATA_ENABLE_ACTIVE_HIGH;
  CmdCfg.ColorCoding           = DSI_RGB888;
  CmdCfg.CommandSize           = HACT;
  CmdCfg.TearingEffectSource   = DSI_TE_DSILINK;
  CmdCfg.TearingEffectPolarity = DSI_TE_RISING_EDGE;
  CmdCfg.VSyncPol              = DSI_VSYNC_FALLING;
  CmdCfg.AutomaticRefresh      = DSI_AR_DISABLE;
  CmdCfg.TEAcknowledgeRequest  = DSI_TE_ACKNOWLEDGE_ENABLE;
  HAL_DSI_ConfigAdaptedCommandMode(&hlcd_dsi, &CmdCfg);
  
  LPCmd.LPGenShortWriteNoP    = DSI_LP_GSW0P_ENABLE;
  LPCmd.LPGenShortWriteOneP   = DSI_LP_GSW1P_ENABLE;
  LPCmd.LPGenShortWriteTwoP   = DSI_LP_GSW2P_ENABLE;
  LPCmd.LPGenShortReadNoP     = DSI_LP_GSR0P_ENABLE;
  LPCmd.LPGenShortReadOneP    = DSI_LP_GSR1P_ENABLE;
  LPCmd.LPGenShortReadTwoP    = DSI_LP_GSR2P_ENABLE;
  LPCmd.LPGenLongWrite        = DSI_LP_GLW_ENABLE;
  LPCmd.LPDcsShortWriteNoP    = DSI_LP_DSW0P_ENABLE;
  LPCmd.LPDcsShortWriteOneP   = DSI_LP_DSW1P_ENABLE;
  LPCmd.LPDcsShortReadNoP     = DSI_LP_DSR0P_ENABLE;
  LPCmd.LPDcsLongWrite        = DSI_LP_DLW_ENABLE;
  HAL_DSI_ConfigCommand(&hlcd_dsi, &LPCmd);

  /* Initialize LTDC */
  LTDC_Init();
  
  /* Start DSI */
  HAL_DSI_Start(&(hlcd_dsi));

  /* Configure DSI PHY HS2LP and LP2HS timings */
  PhyTimings.ClockLaneHS2LPTime = 35;
  PhyTimings.ClockLaneLP2HSTime = 35;
  PhyTimings.DataLaneHS2LPTime = 35;
  PhyTimings.DataLaneLP2HSTime = 35;
  PhyTimings.DataLaneMaxReadTime = 0;
  PhyTimings.StopWaitTime = 10;
  HAL_DSI_ConfigPhyTimer(&hlcd_dsi, &PhyTimings);   
    
  /* Initialize the OTM8009A LCD Display IC Driver (KoD LCD IC Driver) */
  IOCtx.Address     = 0;
  IOCtx.GetTick     = BSP_GetTick;
  IOCtx.WriteReg    = DSI_IO_Write;
  IOCtx.ReadReg     = DSI_IO_Read;
  OTM8009A_RegisterBusIO(&OTM8009AObj, &IOCtx);
  Lcd_CompObj=(&OTM8009AObj);
  OTM8009A_Init(Lcd_CompObj, OTM8009A_COLMOD_RGB888, LCD_ORIENTATION_LANDSCAPE);
  
  
  LPCmd.LPGenShortWriteNoP    = DSI_LP_GSW0P_DISABLE;
  LPCmd.LPGenShortWriteOneP   = DSI_LP_GSW1P_DISABLE;
  LPCmd.LPGenShortWriteTwoP   = DSI_LP_GSW2P_DISABLE;
  LPCmd.LPGenShortReadNoP     = DSI_LP_GSR0P_DISABLE;
  LPCmd.LPGenShortReadOneP    = DSI_LP_GSR1P_DISABLE;
  LPCmd.LPGenShortReadTwoP    = DSI_LP_GSR2P_DISABLE;
  LPCmd.LPGenLongWrite        = DSI_LP_GLW_DISABLE;
  LPCmd.LPDcsShortWriteNoP    = DSI_LP_DSW0P_DISABLE;
  LPCmd.LPDcsShortWriteOneP   = DSI_LP_DSW1P_DISABLE;
  LPCmd.LPDcsShortReadNoP     = DSI_LP_DSR0P_DISABLE;
  LPCmd.LPDcsLongWrite        = DSI_LP_DLW_DISABLE;
  HAL_DSI_ConfigCommand(&hlcd_dsi, &LPCmd);
  
  HAL_DSI_ConfigFlowControl(&hlcd_dsi, DSI_FLOW_CONTROL_BTA);
  HAL_DSI_ForceRXLowPower(&hlcd_dsi, ENABLE);  
  
  return BSP_ERROR_NONE;
}

/**
  * @brief  
  * @param  None
  * @retval None
  */
void LTDC_Init(void)
{
  /* DeInit */
  hlcd_ltdc.Instance = LTDC;
  HAL_LTDC_DeInit(&hlcd_ltdc);
  
  /* LTDC Config */
  /* Timing and polarity */
  hlcd_ltdc.Init.HorizontalSync = HSYNC;
  hlcd_ltdc.Init.VerticalSync = VSYNC;
  hlcd_ltdc.Init.AccumulatedHBP = HSYNC+HBP;
  hlcd_ltdc.Init.AccumulatedVBP = VSYNC+VBP;
  hlcd_ltdc.Init.AccumulatedActiveH = VSYNC+VBP+VACT;
  hlcd_ltdc.Init.AccumulatedActiveW = HSYNC+HBP+HACT;
  hlcd_ltdc.Init.TotalHeigh = VSYNC+VBP+VACT+VFP;
  hlcd_ltdc.Init.TotalWidth = HSYNC+HBP+HACT+HFP;
  
  /* background value */
  hlcd_ltdc.Init.Backcolor.Blue = 0;
  hlcd_ltdc.Init.Backcolor.Green = 0;
  hlcd_ltdc.Init.Backcolor.Red = 0;
  
  /* Polarity */
  hlcd_ltdc.Init.HSPolarity = LTDC_HSPOLARITY_AL;
  hlcd_ltdc.Init.VSPolarity = LTDC_VSPOLARITY_AL;
  hlcd_ltdc.Init.DEPolarity = LTDC_DEPOLARITY_AL;
  hlcd_ltdc.Init.PCPolarity = LTDC_PCPOLARITY_IPC;
  hlcd_ltdc.Instance = LTDC;

  HAL_LTDC_Init(&hlcd_ltdc);
}
/**
  * @brief  Initializes the LCD layers.
  * @param  LayerIndex: Layer foreground or background
  * @param  FB_Address: Layer frame buffer
  * @retval None
  */
static void LCD_LayertInit(uint16_t LayerIndex, uint32_t Address)
{
  LTDC_LayerCfgTypeDef  layercfg;

  /* Layer Init */
  layercfg.WindowX0 = 0;
  layercfg.WindowX1 = Lcd_Ctx[0].XSize ;
  layercfg.WindowY0 = 0;
  layercfg.WindowY1 = Lcd_Ctx[0].YSize; 
  layercfg.PixelFormat = LTDC_PIXEL_FORMAT_ARGB8888;
  layercfg.FBStartAdress = Address;
  layercfg.Alpha = 255;
  layercfg.Alpha0 = 0;
  layercfg.Backcolor.Blue = 0;
  layercfg.Backcolor.Green = 0;
  layercfg.Backcolor.Red = 0;
  layercfg.BlendingFactor1 = LTDC_BLENDING_FACTOR1_PAxCA;
  layercfg.BlendingFactor2 = LTDC_BLENDING_FACTOR2_PAxCA;
  layercfg.ImageWidth = Lcd_Ctx[0].XSize;
  layercfg.ImageHeight = Lcd_Ctx[0].YSize;
  
  HAL_LTDC_ConfigLayer(&hlcd_ltdc, &layercfg, LayerIndex); 
}

/**
  * @brief  DCS or Generic short/long write command
  * @param  ChannelNbr Virtual channel ID
  * @param  Reg Register to be written
  * @param  pData pointer to a buffer of data to be write
  * @param  Size To precise command to be used (short or long)
  * @retval BSP status
  */
static int32_t DSI_IO_Write(uint16_t ChannelNbr, uint16_t Reg, uint8_t *pData, uint16_t Size)
{
  int32_t ret = BSP_ERROR_NONE;

  if(Size <= 1U)
  {
    if(HAL_DSI_ShortWrite(&hlcd_dsi, ChannelNbr, DSI_DCS_SHORT_PKT_WRITE_P1, Reg, (uint32_t)pData[Size]) != HAL_OK)
    {
      ret = BSP_ERROR_BUS_FAILURE;
    }
  }
  else
  {
    if(HAL_DSI_LongWrite(&hlcd_dsi, ChannelNbr, DSI_DCS_LONG_PKT_WRITE, Size, (uint32_t)Reg, pData) != HAL_OK)
    {
      ret = BSP_ERROR_BUS_FAILURE;
    }
  }

  return ret;
}

/**
  * @brief  DCS or Generic read command
  * @param  ChannelNbr Virtual channel ID
  * @param  Reg Register to be read
  * @param  pData pointer to a buffer to store the payload of a read back operation.
  * @param  Size  Data size to be read (in byte).
  * @retval BSP status
  */
static int32_t DSI_IO_Read(uint16_t ChannelNbr, uint16_t Reg, uint8_t *pData, uint16_t Size)
{
  int32_t ret = BSP_ERROR_NONE;

  if(HAL_DSI_Read(&hlcd_dsi, ChannelNbr, pData, Size, DSI_DCS_SHORT_PKT_READ, Reg, pData) != HAL_OK)
  {
    ret = BSP_ERROR_BUS_FAILURE;
  }

  return ret;
}

void LCD_MspInit(void)
{
  /** @brief Enable the LTDC clock */
  __HAL_RCC_LTDC_CLK_ENABLE();

  /** @brief Toggle Sw reset of LTDC IP */
  __HAL_RCC_LTDC_FORCE_RESET();
  __HAL_RCC_LTDC_RELEASE_RESET();

  /** @brief Enable the DMA2D clock */
  __HAL_RCC_DMA2D_CLK_ENABLE();

  /** @brief Toggle Sw reset of DMA2D IP */
  __HAL_RCC_DMA2D_FORCE_RESET();
  __HAL_RCC_DMA2D_RELEASE_RESET();

  /** @brief Enable DSI Host and wrapper clocks */
  __HAL_RCC_DSI_CLK_ENABLE();

  /** @brief Soft Reset the DSI Host and wrapper */
  __HAL_RCC_DSI_FORCE_RESET();
  __HAL_RCC_DSI_RELEASE_RESET();

  /** @brief NVIC configuration for LTDC interrupt that is now enabled */
  HAL_NVIC_SetPriority(LTDC_IRQn, 9, 0xf);
  HAL_NVIC_EnableIRQ(LTDC_IRQn);

  /** @brief NVIC configuration for DMA2D interrupt that is now enabled */
  HAL_NVIC_SetPriority(DMA2D_IRQn, 9, 0xf);
  HAL_NVIC_EnableIRQ(DMA2D_IRQn);

  /** @brief NVIC configuration for DSI interrupt that is now enabled */
  HAL_NVIC_SetPriority(DSI_IRQn, 9, 0xf);
  HAL_NVIC_EnableIRQ(DSI_IRQn);
}
/**
  * @brief  Display Example description.
  * @param  None
  * @retval None
  */
static void LCD_BriefDisplay(void)
{
  UTIL_LCD_SetFont(&Font24);  
  UTIL_LCD_FillRect(0, 0, 800, 480, UTIL_LCD_COLOR_LIGHTMAGENTA);
	UTIL_LCD_FillRect(30, 30, 740, 420, UTIL_LCD_COLOR_ST_BLUE);
  UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_YELLOW);
  UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_ST_BLUE);
  UTIL_LCD_DisplayStringAt(0,50, (uint8_t *)"   This is the Cube-X-AI homework",CENTER_MODE);
	UTIL_LCD_DisplayStringAt(0,80, (uint8_t *)"   accomplished by Cheng Zhe alone",CENTER_MODE);
	
	UTIL_LCD_SetFont(&Font20);
	UTIL_LCD_DisplayStringAt(60,120, (uint8_t *)"Draw a number here!",LEFT_MODE);

}

/**
  * @brief  Converts a line to an ARGB8888 pixel format.
  * @param  pSrc: Pointer to source buffer
  * @param  pDst: Output color
  * @param  xSize: Buffer width
  * @param  ColorMode: Input color mode   
  * @retval None
  */
static void CopyBuffer(uint32_t *pSrc, uint32_t *pDst, uint16_t x, uint16_t y, uint16_t xsize, uint16_t ysize)
{   
   uint32_t destination = (uint32_t)pDst + (y * 800 + x) * 4;
  uint32_t source      = (uint32_t)pSrc;
  
  /*##-1- Configure the DMA2D Mode, Color Mode and output offset #############*/ 
  hdma2d.Init.Mode         = DMA2D_M2M;
  hdma2d.Init.ColorMode    = DMA2D_OUTPUT_ARGB8888;
  hdma2d.Init.OutputOffset = 800 - xsize;
  hdma2d.Init.AlphaInverted = DMA2D_REGULAR_ALPHA;  /* No Output Alpha Inversion*/  
  hdma2d.Init.RedBlueSwap   = DMA2D_RB_REGULAR;     /* No Output Red & Blue swap */   
  
  /*##-2- DMA2D Callbacks Configuration ######################################*/
  hdma2d.XferCpltCallback  = NULL;
  
  /*##-3- Foreground Configuration ###########################################*/
  hdma2d.LayerCfg[1].AlphaMode = DMA2D_NO_MODIF_ALPHA;
  hdma2d.LayerCfg[1].InputAlpha = 0xFF;
  hdma2d.LayerCfg[1].InputColorMode = DMA2D_INPUT_ARGB8888;
  hdma2d.LayerCfg[1].InputOffset = 0;
  hdma2d.LayerCfg[1].RedBlueSwap = DMA2D_RB_REGULAR; /* No ForeGround Red/Blue swap */
  hdma2d.LayerCfg[1].AlphaInverted = DMA2D_REGULAR_ALPHA; /* No ForeGround Alpha inversion */
  
  hdma2d.Instance          = DMA2D; 
   
  /* DMA2D Initialization */
  if(HAL_DMA2D_Init(&hdma2d) == HAL_OK) 
  {
    if(HAL_DMA2D_ConfigLayer(&hdma2d, 1) == HAL_OK) 
    {
      if (HAL_DMA2D_Start(&hdma2d, source, destination, xsize, ysize) == HAL_OK)
      {
        /* Polling For DMA transfer */  
        HAL_DMA2D_PollForTransfer(&hdma2d, 100);
      }
    }
  }   
}

/******************************************************************************/
/*                 STM32H7xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32h7xx.s).                                               */
/******************************************************************************/
/**
  * @brief  This function handles DSI Handler.
  * @param  None
  * @retval None
  */
void DSI_IRQHandler(void)
{
  HAL_DSI_IRQHandler(&hlcd_dsi);
}


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
