#ifndef _ADC_H_
#define _ADC_H_

#include "lpc17xx.h"
#include "../GLCD/GLCD.h"
#include <time.h>
#include <stdlib.h>

/* lib_adc.c */
extern void ADC_init (void);
extern void ADC_start_conversion (void);

/* IRQ_adc.c */
extern void ADC_IRQHandler(void);

#endif
