//#include "LED.h"
#include "main.h"

void imp(void)				//useless
{
	uint8_t a,b,c;
	a = 8,b = 10, c = 100;
	a = b+c,c = c <<0,b=-a,c=c+c-a;
}
//void LED_Act(uint8_t flag)
//{
//	if(flag == 0)
//	{
//			/*LED MOD 1 -- Key Light*/
//		// BT_A -> BT_A_LED_PIN
//		HAL_GPIO_WritePin(GPIOA, BT_A_LED_PIN, 
//			HAL_GPIO_ReadPin(GPIOA, BT_A_Pin) == GPIO_PIN_RESET ? GPIO_PIN_SET : GPIO_PIN_RESET);

//		// 按钮2 -> BT_B_LED_PIN
//		HAL_GPIO_WritePin(GPIOA, BT_B_LED_PIN, 
//			HAL_GPIO_ReadPin(GPIOA, BT_B_Pin) == GPIO_PIN_RESET ? GPIO_PIN_SET : GPIO_PIN_RESET);

//		// 按钮3 -> BT_C_LED_PIN
//		HAL_GPIO_WritePin(GPIOA, BT_C_LED_PIN, 
//			HAL_GPIO_ReadPin(GPIOA, BT_C_Pin) == GPIO_PIN_RESET ? GPIO_PIN_SET : GPIO_PIN_RESET);

//		// 按钮4 -> BT_D_LED_PIN
//		HAL_GPIO_WritePin(GPIOA, BT_D_LED_PIN, 
//			HAL_GPIO_ReadPin(GPIOA, BT_D_Pin) == GPIO_PIN_RESET ? GPIO_PIN_SET : GPIO_PIN_RESET);

//		// 按钮5 -> FX_L_LED_PIN
//		HAL_GPIO_WritePin(GPIOA, FX_L_LED_PIN, 
//			HAL_GPIO_ReadPin(GPIOA, FX_L_Pin) == GPIO_PIN_RESET ? GPIO_PIN_SET : GPIO_PIN_RESET);

//		// 按钮6 -> START_LED_PIN
//		HAL_GPIO_WritePin(GPIOB, START_LED_PIN, 
//			HAL_GPIO_ReadPin(GPIOB, START_Pin) == GPIO_PIN_RESET ? GPIO_PIN_SET : GPIO_PIN_RESET);

//		// 按钮7 -> FX_R_LED_PIN
//		HAL_GPIO_WritePin(GPIOB, FX_R_LED_PIN, 
//			HAL_GPIO_ReadPin(GPIOB, FX_R_Pin) == GPIO_PIN_RESET ? GPIO_PIN_SET : GPIO_PIN_RESET);
//			
//		// 按钮8 -> LED_MOD_LED_PIN
//		HAL_GPIO_WritePin(GPIOB, LED_MOD_LED_PIN, 
//			HAL_GPIO_ReadPin(GPIOB, LED_MOD_LED_PIN) == GPIO_PIN_RESET ? GPIO_PIN_SET : GPIO_PIN_RESET);
//			
//		// 按钮9 -> LED7
//		//HAL_GPIO_WritePin(GPIOB, FX_R_LED_PIN, 
//			//HAL_GPIO_ReadPin(GPIOB, FX_R_Pin) == GPIO_PIN_RESET ? GPIO_PIN_SET : GPIO_PIN_RESET);

//	}
//	else if(flag == 1)
//	{
//		/*LED MOD 2 -- Normal Light*/
//		HAL_GPIO_WritePin(GPIOA, BT_A_LED_PIN|BT_B_LED_PIN
//						|BT_C_LED_PIN|BT_D_LED_PIN, GPIO_PIN_SET);
//		//HAL_GPIO_WritePin(GPIOB, )
//		
//		
//	}
//	else if(flag == 2)
//	{
//		/*LED MOD 3 -- OFF*/
//		HAL_GPIO_WritePin(GPIOA, BT_A_LED_PIN|BT_B_LED_PIN
//						|BT_C_LED_PIN|BT_D_LED_PIN, GPIO_PIN_RESET);
//	}
//	
//}
