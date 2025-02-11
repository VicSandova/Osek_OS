#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "RGB_ticks.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define BOARD_LED_R_GPIO     	BOARD_LED_RED_GPIO
#define BOARD_LED_R_GPIO_PIN 	BOARD_LED_RED_PIN

#define BOARD_LED_B_GPIO     	BOARD_LED_BLUE_GPIO
#define BOARD_LED_B_GPIO_PIN 	BOARD_LED_BLUE_PIN

#define BOARD_LED_G_GPIO     	BOARD_LED_GREEN_GPIO
#define BOARD_LED_G_GPIO_PIN 	BOARD_LED_GREEN_PIN

#define GPIO_C ((GPIO_Type *)(0x400FF080u))
#define GPIO_A ((GPIO_Type *)(0x400FF000u))
#define GPIO_E ((GPIO_Type *)(0x400FF100u))

#define RED		9u
#define	BLUE	11u
#define	GREEN	6u

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
volatile uint32_t g_systickCounter;

/*******************************************************************************
 * Code
 ******************************************************************************/
void RGB_ticks_Init(){
    /* Board pin init */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
}
void SysTick_Handler(void)
{
    if (g_systickCounter != 0U)
    {
        g_systickCounter--;
    }
}
void Led_Red(){
	GPIO_PortClear(	GPIO_C, 1u << RED  );
	GPIO_PortSet  ( GPIO_A, 1u << BLUE );
	GPIO_PortSet  (	GPIO_E, 1u << GREEN);
}
void Led_Blue(){
	GPIO_PortSet  (	GPIO_C, 1u << RED  );
	GPIO_PortClear( GPIO_A, 1u << BLUE );
	GPIO_PortSet  (	GPIO_E, 1u << GREEN);
}
void Led_Green(){
	GPIO_PortSet  (	GPIO_C, 1u << RED  );
	GPIO_PortSet  ( GPIO_A, 1u << BLUE );
	GPIO_PortClear(	GPIO_E, 1u << GREEN);
}
void Led_Off(){
	GPIO_PortSet  (	GPIO_C, 1u << RED  );
	GPIO_PortSet  ( GPIO_A, 1u << BLUE );
	GPIO_PortSet  (	GPIO_E, 1u << GREEN);
}
void Led_White(){
	GPIO_PortClear(	GPIO_C, 1u << RED  );
	GPIO_PortClear( GPIO_A, 1u << BLUE );
	GPIO_PortClear(	GPIO_E, 1u << GREEN);
}

void SysTick_DelayTicks(uint32_t n)
{
	if (SysTick_Config(SystemCoreClock / 1000U)) { while (1){ } }
	g_systickCounter = n;
    while (g_systickCounter != 0U)
    {
    }

}
