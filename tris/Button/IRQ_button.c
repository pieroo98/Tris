#include "button.h"

extern int down, down1,down2,facile,difficile;

void EINT0_IRQHandler (void)	  	/* INT0														 */
{
	down2=1;	//reset game
	NVIC_DisableIRQ(EINT0_IRQn);		/* disable Button interrupts			 */
	LPC_PINCON->PINSEL4    &= ~(1 << 20);     /* GPIO pin selection */
	LPC_SC->EXTINT &= (1 << 0);     /* clear pending interrupt         */
}


void EINT1_IRQHandler (void)	  	/* KEY1														 */
{
	if(facile==0){
		down = 1;		//start game
		NVIC_DisableIRQ(EINT1_IRQn);		/* disable Button interrupts			 */
		LPC_PINCON->PINSEL4    &= ~(1 << 22);     /* GPIO pin selection */
		facile=1;
		difficile = -1;
	}
	LPC_SC->EXTINT &= (1 << 1);     /* clear pending interrupt         */
}

void EINT2_IRQHandler (void)	  	/* KEY2														 */
{
	if(difficile==0){
		down1=1;		//start game
		NVIC_DisableIRQ(EINT2_IRQn);		/* disable Button interrupts			 */
		LPC_PINCON->PINSEL4    &= ~(1 << 24);     /* GPIO pin selection */
		difficile = 1;
		facile = -1;	
		}
  LPC_SC->EXTINT &= (1 << 2);     /* clear pending interrupt         */    
}


