/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_RIT.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    RIT.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "RIT.h"

/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

extern char score[10],finish[10],score2[10],vittoria[10],testo[100],endgame[20],Reverse[12];
extern int down, down1, down2, facile,difficile, matrice[3][3],pareggio,giocatore,disegna;

void RIT_IRQHandler (void)
{
	char tasto1[20]={"mod hard OK"}, tasto0[20]={"mod easy OK"};
	int i, j,pos_x,pos_y;
	if(down2!=0){
		if(((LPC_GPIO2->FIOPIN & (1<<10)) == 0)){  //INT0
			down2++;
			switch(down2){
				case 2:
					if(difficile==1){
						GUI_Text(76,295,(uint8_t *) tasto1, Black, Black,0);
					}
					if(facile == 1){
						GUI_Text(76,295,(uint8_t *) tasto0, Black, Black,0);
					}
					facile = difficile = 0;
					if(pareggio==1)
						GUI_Text(44, 50, (uint8_t *) endgame, Black, Black,0);
					if(giocatore == 2){
						GUI_Text(88, 270, (uint8_t *) finish, Black, Black,0);
						GUI_Text(88, 50, (uint8_t *) Reverse, Black, Black,1);
					}
					else if(giocatore ==1){
						GUI_Text(88, 270, (uint8_t *) vittoria, Black, Black,0);
						GUI_Text(88, 50, (uint8_t *) Reverse, Black, Black,1);
					}
					giocatore= 0;
					for(i=0;i<3;i++){
						for(j=0;j<3;j++){
							if(matrice[i][j]!=1){
								if(matrice[i][j]==3){
									calcola_coord(i,j,&pos_x,&pos_y);
									cancella_X(pos_x,pos_y);
								}
								else if(matrice[i][j]==5){
									calcola_coord(i,j,&pos_x,&pos_y);
									cancella_O(pos_x,pos_y);
								}
								matrice[i][j]=1;
							}
						}
					}
					GUI_Text(7,240,(uint8_t *) testo, Yellow, Black,0);
					pos_x = pos_y = -1;
					reset_timer(0);
					break;
				default:
					break;
			}
		}
		else {
			down2=0;
			NVIC_EnableIRQ(EINT0_IRQn);							 
			LPC_PINCON->PINSEL4    |= (1 << 20);     
		}
	}
	if(down!=0){
		if(((LPC_GPIO2->FIOPIN & (1<<11)) == 0)){  //KEY 1
			down++;
			switch(down){
				case 2:
					if(disegna==0){
						start();
						disegna =1;
					}
					GUI_Text(7,240,(uint8_t *) testo, Black, Black,0);
					GUI_Text(76,295,(uint8_t *) tasto0, White, Black,0);
					enable_timer(0);
					pos_x = pos_y = -1;
					break;
				default:
					break;
			}
		}
		else {
			down=0;			
			NVIC_EnableIRQ(EINT1_IRQn);							 
			LPC_PINCON->PINSEL4    |= (1 << 22);     
		}
	}
	
	if(down1!=0){
		if(((LPC_GPIO2->FIOPIN & (1<<12)) == 0)){  //KEY 2
			down1++;
			switch(down1++){			
				case 2:
					if(disegna==0){
						start();
						disegna =1;
					}
					GUI_Text(7,240,(uint8_t *) testo, Black, Black,0);
					GUI_Text(76,295,(uint8_t *) tasto1, White, Black,0);
					enable_timer(0);
					pos_x = pos_y = -1;
					break;
				default:
					break;
			}
		}
		else {	
			down1=0;
			NVIC_EnableIRQ(EINT2_IRQn);							 
			LPC_PINCON->PINSEL4    |= (1 << 24);  
		}
	}		
  LPC_RIT->RICTRL |= 0x1;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
