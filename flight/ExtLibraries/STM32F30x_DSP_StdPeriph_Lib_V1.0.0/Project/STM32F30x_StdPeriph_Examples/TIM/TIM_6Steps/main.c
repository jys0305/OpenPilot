/**
  ******************************************************************************
  * @file    TIM/TIM_6Steps/main.c  
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    23-October-2012
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2012 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/** @addtogroup STM32F30x_StdPeriph_Examples
  * @{
  */

/** @addtogroup TIM_6Steps
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void TIM_Config(void);
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (startup_stm32f30x.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32f30x.c file
     */ 

  /* SysTick Configuration */
  SysTickConfig();

  /* TIM1 Configuration */
  TIM_Config();
  
  /* Infinite loop */
  while (1)
  {
  }
}

/**
  * @brief  Configure the TIM1 .
  * @param  None
  * @retval None
  */
static void TIM_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;
  TIM_BDTRInitTypeDef TIM_BDTRInitStructure;
  
  /* GPIOA and GPIOB clocks enable */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA|RCC_AHBPeriph_GPIOB|RCC_AHBPeriph_GPIOC|RCC_AHBPeriph_GPIOE, ENABLE);

  /* TIM1 clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

  /* GPIO Configuration: Channel 1, 2, 1N, 2N, 3  and 3N as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_8 | GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; 
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
  GPIO_Init(GPIOE, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  /* Connect TIM pins to AF */
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_6);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_6);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_6);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource0, GPIO_AF_6);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource1, GPIO_AF_6);
  GPIO_PinAFConfig(GPIOE, GPIO_PinSource13, GPIO_AF_2);
  GPIO_PinAFConfig(GPIOC, GPIO_PinSource13, GPIO_AF_4);

  /* Enable the TIM1 Trigger and commutation interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = TIM1_TRG_COM_TIM17_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);   
  
    /*----------------------------------------------------------------------------
  The STM32F30x TIM1 peripheral offers the possibility to program in advance the 
  configuration for the next TIM1 outputs behaviour (step) and change the configuration
  of all the channels at the same time. This operation is possible when the COM 
  (commutation) event is used.
  The COM event can be generated by software by setting the COM bit in the TIM1_EGR
  register or by hardware (on TRC rising edge).
  In this example, a software COM event is generated each 100 ms: using the SysTick 
  interrupt.
  The TIM1 is configured in Timing Mode, each time a COM event occurs, a new TIM1 
  configuration will be set in advance.

  The following Table  describes the TIM1 Channels states:
              -----------------------------------------------
             | Step1 | Step2 | Step3 | Step4 | Step5 | Step6 |
   ----------------------------------------------------------
  |Channel1  |   1   |   0   |   0   |   0   |   0   |   1   |
   ----------------------------------------------------------
  |Channel1N |   0   |   0   |   1   |   1   |   0   |   0   |
   ----------------------------------------------------------
  |Channel2  |   0   |   0   |   0   |   1   |   1   |   0   |
   ----------------------------------------------------------
  |Channel2N |   1   |   1   |   0   |   0   |   0   |   0   |
   ----------------------------------------------------------
  |Channel3  |   0   |   1   |   1   |   0   |   0   |   0   |
   ----------------------------------------------------------
  |Channel3N |   0   |   0   |   0   |   0   |   1   |   1   |
   ----------------------------------------------------------
  ----------------------------------------------------------------------------*/

  /* Time Base configuration */
  TIM_TimeBaseStructure.TIM_Prescaler = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_Period = 4095;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;

  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

  /* Channel 1, 2 and 3 Configuration in PWM mode */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Timing;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 2047;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
  TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
  TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Set;

  TIM_OC1Init(TIM1, &TIM_OCInitStructure);

  TIM_OCInitStructure.TIM_Pulse = 1023;
  TIM_OC2Init(TIM1, &TIM_OCInitStructure);

  TIM_OCInitStructure.TIM_Pulse = 511;
  TIM_OC3Init(TIM1, &TIM_OCInitStructure);

  /* Automatic Output enable, Break, dead time and lock configuration*/
  TIM_BDTRInitStructure.TIM_OSSRState = TIM_OSSRState_Enable;
  TIM_BDTRInitStructure.TIM_OSSIState = TIM_OSSIState_Enable;
  TIM_BDTRInitStructure.TIM_LOCKLevel = TIM_LOCKLevel_OFF;
  TIM_BDTRInitStructure.TIM_DeadTime = 1;
  TIM_BDTRInitStructure.TIM_Break = TIM_Break_Enable;
  TIM_BDTRInitStructure.TIM_BreakPolarity = TIM_BreakPolarity_Low;
  TIM_BDTRInitStructure.TIM_AutomaticOutput = TIM_AutomaticOutput_Enable;

  TIM_BDTRConfig(TIM1, &TIM_BDTRInitStructure);

  TIM_CCPreloadControl(TIM1, ENABLE);

  TIM_ITConfig(TIM1, TIM_IT_COM, ENABLE);

  /* TIM1 counter enable */
  TIM_Cmd(TIM1, ENABLE);

  /* Main Output Enable */
  TIM_CtrlPWMOutputs(TIM1, ENABLE);

}

/**
  * @brief  Configures the SysTick.
  * @param  None
  * @retval None
  */
void SysTickConfig(void)
{
  /* Setup SysTick Timer for 100 msec interrupts  */
  if (SysTick_Config((SystemCoreClock) / 10))
  { 
    /* Capture error */ 
    while (1);
  }

  NVIC_SetPriority(SysTick_IRQn, 0x0);
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
