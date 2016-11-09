/*
	Copyright (c) 2016 Konstantin.  All right reserved.

	This library is free software; you can redistribute it and/or
	modify it under the terms of the GNU Lesser General Public
	License as published by the Free Software Foundation; either
	version 2.1 of the License, or (at your option) any later version.

	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
	See the GNU Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public
	License along with this library; if not, write to the Free Software
	Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "Arduino.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * System Core Clock is at 8MHz (8MHz/1/1/1) at Reset.
 * It is switched to 48MHz in the Reset Handler (startup.c)
 */
uint32_t SystemCoreClock=8000000ul ;

/*
void calibrateADC()
{
	volatile uint32_t valeur = 0;

	for(int i = 0; i < 5; ++i)
	{
	ADC->SWTRIG.bit.START = 1;
	while( ADC->INTFLAG.bit.RESRDY == 0 || ADC->STATUS.bit.SYNCBUSY == 1 )
	{
		// Waiting for a complete conversion and complete synchronization
	}

	valeur += ADC->RESULT.bit.RESULT;
	}

	valeur = valeur/5;
}*/

/*
 * MKL27 board initialization
 *
 * Good to know:
 *   - At reset, ResetHandler did the system clock configuration. Core is 
 *   -   running at 48MHz.
 *   - Watchdog is disabled by default, unless someone plays with NVM User page
 */
void init( void )
{
	uint32_t ul ;

//moved to reset_handler in cortex handlers .c
	//   // Set Systick to 1ms interval, common to all Cortex-M variants
	//   if ( SysTick_Config( SystemCoreClock / 1000 ) )
	//   {
	//   // Capture error
	//   while ( 1 ) ;
	//   }
	
	//   SIM->SOPT2=0x15440060u; // All clk sources set to 48MHZ USB set to internal 
							//   // 48 clockout is 1khz rtc_clockout is 1Hz  
	//   //SIM SOPT4,5,7 dont need changing from default..not using any fancy options

	//   SIM->SCGC4=0xF0DC10F0u; //enable all 
	//   SIM->SCGC5=0x80303F83u; //enable all 
	//   SIM->SCGC6=0x2F840003u; //enable all 
	//   SIM->SCGC7=0x00000100u; //enable all... DMA 
	
	
	
	// Clock PORT for Digital I/O
//	PM->APBBMASK.reg |= PM_APBBMASK_PORT ;
//
//	// Clock EIC for I/O interrupts
//	PM->APBAMASK.reg |= PM_APBAMASK_EIC ;
	
	//   // Clock SERCOM for Serial
	//   PM->APBCMASK.reg |= PM_APBCMASK_SERCOM0 | PM_APBCMASK_SERCOM1 | PM_APBCMASK_SERCOM2 | PM_APBCMASK_SERCOM3 | PM_APBCMASK_SERCOM4 | PM_APBCMASK_SERCOM5 ;

	//   // Clock TC/TCC for Pulse and Analog
	//   PM->APBCMASK.reg |= PM_APBCMASK_TCC0 | PM_APBCMASK_TCC1 | PM_APBCMASK_TCC2 | PM_APBCMASK_TC3 | PM_APBCMASK_TC4 | PM_APBCMASK_TC5 ;

	 //   //Clock ADC/DAC for Analog
	 //   PM->APBCMASK.reg |= PM_APBCMASK_ADC | PM_APBCMASK_DAC ;

	// Setup all pins (digital and analog) in INPUT mode (default is nothing)
	for ( ul = 0 ; ul < NUM_DIGITAL_PINS; ul++ )
	{
		pinMode( ul, INPUT ) ;
	}
	
	//Initialize Analog Controller
	//Calibration process in cortex_handlers.c maybe overkill

	ADC0->CFG1 = 0x58;//6MHz ADCK long sample 10bit conv
	ADC0->CFG2 = 0x02;//10 total ADCK ticks
	ADC0->SC2  = 0x01;// sets alt ref for VREF to VSSA/VDDA rather than PTE30 
	ADC0->SC3  = 0x04;// sets averaging to 4 
	
	//since we made a 32 pin version of the chip, disable VREFOUT so A1 can be used.
	//   VREF->SC=0x00;
	//   CMP0->CR1=0x00;
}

#ifdef __cplusplus
}
#endif
