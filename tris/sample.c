/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               main.c
** Descriptions:            The GLCD application function
**
**--------------------------------------------------------------------------------------------------------
** Created by:              AVRman
** Created date:            2010-11-7
** Version:                 v1.0
** Descriptions:            The original version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:             Paolo Bernardi
** Modified date:           03/01/2020
** Version:                 v2.0
** Descriptions:            basic program for LCD and Touch Panel teaching
**
*********************************************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "LPC17xx.h"
#include "GLCD/GLCD.h"
#include "timer/timer.h"
#include "RIT/RIT.h"
#include "Button/button.h"
#include "TouchPanel/TouchPanel.h"

#define SIMULATOR 1

#ifdef SIMULATOR
extern uint8_t ScaleFlag; // <- ScaleFlag needs to visible in order for the emulator to find the symbol (can be placed also inside system_LPC17xx.h but since it is RO, it needs more work)
#endif

volatile char score[10] = {"0"},finish[10] = {"YOU LOSE"},vittoria[10]={"YOU WIN"},score2[10]={"0"},Reverse[12];
volatile char testo[100]={"key1 -> easy key2 -> hard"},endgame[20]={"press int0 to reset"};

volatile int  down=0, down1=0, down2=0, facile=0,difficile=0, matrice[3][3],pos_x=-1,pos_y=-1,pareggio=0,giocatore=0,disegna=0;
int i, j;

int main(void)
{
  SystemInit();  												/* System Initialization (i.e., PLL)  */
  LCD_Initialization();
	for(i=0;i<3;i++){
		for(j=0;j<3;j++)
			matrice[i][j]=1;}

	BUTTON_init();
	init_RIT(0x4C4B40);									/* RIT Initialization 50 msec					*/
	enable_RIT();													/* RIT enabled												*/
	TP_Init();
	LCD_Clear(Black);
  GUI_Text(10,10, (unsigned char*) "Touch crosshair to calibrate",0xffff,Black,0); 
	init_timer(1,0,0,3,0x7D7840);		//1 s timer 1
	enable_timer(1);			
	//TouchPanel_Calibrate2(0);
	//init_timer(0,0,0,3,0x1AB3F0);				//70 ms screen
	init_timer(0,0,0,3,0x4C4B40);				//0.2 s screen
	//enable_timer(0);
	//GUI_Text(10,10, (unsigned char*) "Touch crosshair to calibrate",Black,Black,0); 

	
	LPC_SC->PCON |= 0x1;									/* power-down	mode										*/
	LPC_SC->PCON &= ~(0x2);				
	//GUI_Text(7,240,(uint8_t *) testo, Yellow, Black,0);
	//start();
	
  while (1)	
  {
		__ASM("wfi");
  }
}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
