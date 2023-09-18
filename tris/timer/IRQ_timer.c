/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_timer.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    timer.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "timer.h"

extern char score[10],finish[10],score2[10],vittoria[10],endgame[20],Reverse[12],testo[100];
extern int matrice[3][3],pos_x,pos_y,pareggio,giocatore,facile, difficile;

void TIMER0_IRQHandler (void)
{
	int a=-1 , b=-1;
  if (LPC_TIM0->IR & 01)
	{
		pos_x = pos_y = -1;
		if(getDisplayPoint(&display, Read_Ads7846(), &matrix )){
			if(display.x>38 && display.x<85){
				if(display.y>74 && display.y<121){//in alto a sx
					pos_x=pos_y=0;
				}
				else if(display.y>127 && display.y<170){//centro a sx
					pos_x=1;
					pos_y=0;
				}
				else if(display.y>177 && display.y<224){//in basso a sx
					pos_x=2;
					pos_y=0;
				}
			}
			else if(display.x>92 && display.x<148){
				if(display.y>74 && display.y<121){//in alto al centro
					pos_x=0;
					pos_y=1;
				}
				else if(display.y>127 && display.y<170){//centro
					pos_x=1;
					pos_y=1;
				}
				else if(display.y>177 && display.y<224){//in basso al centro
					pos_x=2;
					pos_y=1;
				}
			}
			else if(display.x>156 && display.x<200){
				if(display.y>74 && display.y<121){//in alto a dx
					pos_x=0;
					pos_y=2;
				}
				else if(display.y>127 && display.y<170){//centro a dx
					pos_x=1;
					pos_y=2;
				}
				else if(display.y>177 && display.y<224){//in basso a dx
					pos_x=pos_y=2;
				}
			}
		}
		calcola_coord(pos_x,pos_y,&a,&b);
		if(((a>=59 && a<=178) &&(b>=97 && b<=202)) && matrice[pos_x][pos_y]==1){
			stampa_X(a,b);
			matrice[pos_x][pos_y]=3;
			if(check_vittoria()==1){
				disable_timer(0);
				GUI_Text(10, 160, (uint8_t *) score, Black, Black,0);
				a = atoi(score);
				a++;
				//stampare YOU WIN e YOU LOSE capovolto
				sprintf(score,"%d",a);
				Reverse_word(finish);
				GUI_Text(10, 160, (uint8_t *) score, White, Black,0);
				GUI_Text(88, 270, (uint8_t *) vittoria, Red, Black,0);
				GUI_Text(88, 50, (uint8_t *) Reverse, Red, Black,1);
				giocatore = 1;
			}
			if(difficile ==1 && giocatore!=1)
				mossa_avversaria(&pos_x,&pos_y);
			if(facile ==1 && giocatore !=1)
				mossa_avversaria_easy(&pos_x,&pos_y);
			if((matrice[pos_x][pos_y]==1 &&(pos_x!=-1 && pos_y!=-1)) && giocatore!=1){
				calcola_coord(pos_x,pos_y,&a,&b);
				if((a!=-1 && b!=-1) && matrice[pos_x][pos_y]==1){
					stampa_O(a,b);
					matrice[pos_x][pos_y]=5;
					if(check_vittoria()==2){
						disable_timer(0);
						GUI_Text(230, 176, (uint8_t *) score2, Black, Black,1);
						a = atoi(score2);
						a++;
						sprintf(score2,"%d",a);
						Reverse_word(vittoria);
						GUI_Text(230, 176, (uint8_t *) score2, White, Black,1);
						GUI_Text(88, 270, (uint8_t *) finish, Red, Black,0);
						GUI_Text(88, 50, (uint8_t *) Reverse, Red, Black,1);
						giocatore = 2;
					}
					else if(check_pareggio()==0){
						disable_timer(0);
						pareggio=1;
						GUI_Text(44, 50, (uint8_t *) endgame, Red, Black,0);
					}
				}
			}
			else if((pos_x == -1 && pos_y == -1) && giocatore!=1){
				disable_timer(0);
				pareggio=1;
				GUI_Text(44, 50, (uint8_t *) endgame, Red, Black,0);
			}
		}
		
		LPC_TIM0->IR = 1;			
	}
	else if(LPC_TIM0->IR & 02)
  {
		LPC_TIM0->IR =  2 ;			
	}
	else if(LPC_TIM0->IR & 4)
  {
		LPC_TIM0->IR =  4 ;	
	}
	else if(LPC_TIM0->IR & 8)
  {
		LPC_TIM0->IR =  8 ;
	}
  return;
}

void TIMER1_IRQHandler (void)
{
	static int i=0;
  if (LPC_TIM1->IR & 01)
	{
		
		TouchPanel_Calibrate2(i);
		i++;
		if(i==3){
			setCalibrationMatrix( &DisplaySample[0],&ScreenSample[0],&matrix ) ;  
			disable_timer(1);
			GUI_Text(10,10, (unsigned char*) "Touch crosshair to calibrate",Black,Black,0); 
			GUI_Text(7,240,(uint8_t *) testo, Yellow, Black,0);
		}
		LPC_TIM1->IR = 1;			
	}
	else if(LPC_TIM1->IR & 02)
  {
		LPC_TIM1->IR =  2 ;			
	}
	else if(LPC_TIM1->IR & 4)
  {
		LPC_TIM1->IR =  4 ;			
	}
	else if(LPC_TIM1->IR & 8)
  {
		LPC_TIM1->IR =  8 ;	
	}
  return;
}

void TIMER2_IRQHandler (void)
{
	if (LPC_TIM2->IR & 01)
	{
		LPC_TIM2->IR = 1;			
	}
	else if(LPC_TIM2->IR & 02)
  {
		LPC_TIM2->IR =  2 ;	
	}
	else if(LPC_TIM2->IR & 4)
  {
		LPC_TIM2->IR =  4 ;
	}
	else if(LPC_TIM2->IR & 8)
  {
		LPC_TIM2->IR =  8 ;
	}
  return;
}

void TIMER3_IRQHandler (void)
{
	if (LPC_TIM3->IR & 01)
	{
		LPC_TIM3->IR = 1;	
	}
	else if(LPC_TIM3->IR & 02)
  {
		LPC_TIM3->IR =  2 ;
	}
	else if(LPC_TIM3->IR & 4)
  {
	 
		LPC_TIM3->IR =  4 ;
	}
	else if(LPC_TIM3->IR & 8)
  {
		LPC_TIM3->IR =  8 ;
	}
  return;
}

void calcola_coord(int pos_x, int pos_y, int *x, int *y){
	if((pos_x>=0 && pos_y>=0) &&(pos_x<=2 && pos_y<=2)){
		if(pos_x==0 && pos_y ==0){
			*x=59;
			*y=97;
		}
		else if(pos_x==0 && pos_y==1){
			*x=120;
			*y=97;
		}
		else if(pos_x==1 && pos_y==1){
			*x=120;
			*y=148;
		}
		else if(pos_x==0 && pos_y==2){
			*x=178;
			*y=97;
		}
		else if(pos_x==1 && pos_y==0){
			*x=59;
			*y=148;
		}
		else if(pos_x==1 && pos_y==2){
			*x=178;
			*y=148;
		}
		else if(pos_x==2 && pos_y==0){
			*x=59;
			*y=202;
		}
		else if(pos_x==2 && pos_y==1){
			*x=120;
			*y=202;
		}
		else if(pos_x==2 && pos_y==2){
			*x=178;
			*y=202;
		}
	}
	else{
		*x=*y=-1;
	}
}

int check_vittoria(){
	int i,j,tmp=1;
	for(i=0;i<3;i++){
		tmp=1;
		for(j=0;j<3;j++){
			tmp = tmp*matrice[i][j];
		}
		if(tmp==27)
			return 1;
		else if(tmp ==125)
			return 2;
	}
	
	for(i=0;i<3;i++){
		tmp=1;
		for(j=0;j<3;j++){
			tmp = tmp*matrice[j][i];
		}
		if(tmp==27)
			return 1;
		else if(tmp ==125)
			return 2;
	}
	
	tmp = matrice[0][0]*matrice[1][1]*matrice[2][2];
	if(tmp==27)
		return 1;
	else if(tmp==125)
		return 2;
	tmp = matrice[2][0]*matrice[1][1]*matrice[0][2];
	if(tmp==27)
		return 1;
	else if(tmp==125)
		return 2;
	return 0;
}

int check_pareggio(){
	int i ,j,count=0;
	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			if(matrice[i][j]==1)
				count++;
		}
	}
	return count;
}

void Reverse_word(char *stringa){
	int i, lun;
	lun = strlen(stringa);
	for(i=0;i<lun;i++)
		Reverse[i] = stringa[lun -i -1];
	Reverse[i]='\0';
}
/******************************************************************************
**                            End Of File
******************************************************************************/
