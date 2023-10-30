/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.76
        Device            :  PIC18F46K42
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "mcc_generated_files/mcc.h"

// Definitions from tutorial
#define MV_HIGH_RANGE_FLOAT     -3.684
#define MV_HIGH_RANGE_FIXED     3684    //-3.684
#define MV_FIXED_DIVIDER        1000    //Factor of 1000
#define ADC_RES_MINUS_ONE       4095    //2^12-1=4095

#define READ_TSHR2              FLASH_ReadWord(0x003F002C)
#define READ_FVRA2X             FLASH_ReadWord(0x003F0032)

unsigned char reverse(unsigned char b) {
   b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
   b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
   b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
   return b;
}

adc_result_t adcc_read_average(adcc_channel_t channel)
{
    ADCC_GetSingleConversion(channel);
    return ADCC_GetFilterValue();
}
/*
                         Main application
 */
void main(void)
{
    SYSTEM_Initialize();
    adc_result_t adc_dia = FLASH_ReadWord(0x003F002C);
    uint16_t     fvra2x  = FLASH_ReadWord(0x003F0032);
    TBLPTRU=0; // fix side effect of FLASH_ReadWord()
    float mv_float = MV_HIGH_RANGE_FLOAT;
    uint32_t mv_fixed = MV_HIGH_RANGE_FIXED;
        __delay_ms(200);
        __delay_ms(200);
        __delay_ms(200);
        __delay_ms(200);
        __delay_ms(200);    
    printf("Calibration %i\r\n",adc_dia);
    printf("FVR value %i\r\n",fvra2x);
    
    while (1)
    {
        adc_result_t fvr_meas = adcc_read_average(channel_FVR_Buffer1);
        adc_result_t adc_meas = adcc_read_average(channel_Temp);
        // Equation to implement:
        // float t_meas = 90 + (((adc_meas - adc_dia) * fvra2x)/(4095 * mv));
        // 4095 = 2^n-1, where n = 12 (adc resolution)

        int32_t num_fixed = (int32_t)(adc_meas - adc_dia) * fvra2x * MV_FIXED_DIVIDER;
        int32_t den_fixed = (int32_t)(ADC_RES_MINUS_ONE * mv_fixed) / MV_FIXED_DIVIDER;
        int32_t t_meas_fixed = (int32_t)90 * MV_FIXED_DIVIDER - num_fixed/den_fixed;
 

        uint8_t t_meas = t_meas_fixed/ MV_FIXED_DIVIDER;
        uint8_t t_deci = (t_meas_fixed/ (MV_FIXED_DIVIDER/10))%10;
//        uint8_t t_bcd = (t_meas % 10) + (t_meas/10)*0x10;
        printf("FVR %i ADC %i Temperature %i.%i\r\n",fvr_meas,adc_meas,t_meas,t_deci);
        LATD=t_meas;
        __delay_ms(200);
        __delay_ms(200);
        __delay_ms(200);
        __delay_ms(200);
        __delay_ms(200);    
    }
}
/**
 End of File
*/