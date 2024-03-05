#ifndef __AD7794_H__
#define __AD7794_H__

#include <stdint.h>

/*--------Defines for Comm Reg--------*/
//Chosen bits are 1's
#define Comm_WEN    0x80
#define Comm_RW     0x40
#define Comm_CREAD  0x4
#define Comm_Zero   0x3


#define Comm_Reg    0x0
#define Stat_Reg    0x0
#define Mode_Reg    0x1
#define Conf_Reg    0x2
#define Data_Reg    0x3
#define ID_Reg      0x4
#define IO_Reg      0x5
#define Offset_Reg  0x6
#define Full_Reg    0x7
/*------------------------------------*/

/*--------Defines for Stat Reg--------*/
//Chosen bits are 1's
#define Stat_RDY    0x80
#define Stat_ERR    0x40
#define Stat_NOREF  0x20
#define Stat_CH     0x3
/*------------------------------------*/

/*--------Defines for Mode Reg--------*/
//Chosen bits are 1's
//Total
#define Mode_Zero   0xF20
#define Mode_Mode   0xE000
#define Mode_PSW    0x1000
#define Mode_CLK    0xC0
#define Mode_Chop_DIS   0x10
#define Mode_Filter 0xF
//------
//Mode
#define Mode_Cont_Conv   0x0
#define Mode_Single_Conv 0x2000
#define Mode_Idle_Mode   0x4000
#define Mode_Power_Down  0x6000
#define Mode_Zero_Calib  0x8000
#define Mode_Full_Calib  0xA000
//------
//CLK
#define Mode_IN_64       0x0
#define Mode_IN_64_CLK   0x40
#define Mode_EX_64       0x80
#define Mode_EX_64_DIV2  0xC0
//Rating
#define Mode_Rate        0xF
#define Mode_Rate_None    0x0
#define Mode_Rate_500Hz  0x1
#define Mode_Rate_250Hz  0x2
#define Mode_Rate_125Hz  0x3
#define Mode_Rate_65Hz   0x4
#define Mode_Rate_50Hz   0x5
#define Mode_Rate_41Hz   0x6
#define Mode_Rate_33Hz   0x7
#define Mode_Rate_19Hz_90dB  0x8
#define Mode_Rate_16Hz_84dB  0x9
#define Mode_Rate_16Hz_70dB  0xA
#define Mode_Rate_12Hz_67dB  0xB
#define Mode_Rate_10Hz_69dB  0xC
#define Mode_Rate_8Hz_73dB   0xD
#define Mode_Rate_6Hz_74dB   0xE
#define Mode_Rate_4Hz_79dB   0xF
//------
/*------------------------------------*/

/*--------Defines for Conf Reg--------*/
//Chosen bits are 1's
//Zero bits
#define Conf_Zero       0x800
//Bias Voltage
#define Conf_Vbias      0xC000
#define Conf_VB_DIS     0x0
#define Conf_VB_AIN1    0x4000
#define Conf_VB_AIN2    0x8000
#define Conf_VB_AIN3    0xC000
//------------
//Butout Current
#define Conf_BO         0x2000
//Unipolar/Bipolar  
#define Conf_UB         0x1000
//Gain Select Bits
#define Conf_Gains      0x700
#define Conf_G1         0x0
#define Conf_G2         0x100
#define Conf_G4         0x200
#define Conf_G8         0x300
#define Conf_G16        0x400
#define Conf_G32        0x500
#define Conf_G64        0x600
#define Conf_G128       0x700
//-------------
//Reference Select
#define Conf_Ref        0xC0
#define Conf_Ext_R1     0x0
#define Conf_Ext_R2     0x40
#define Conf_Int        0x80
//------------
//Reference detection
#define Conf_Ref_Det    0x20
//Buffered mode
#define Conf_Buf        0x10
//Channel Select
#define Conf_Channles   0xF
#define Conf_Ch_AIN1    0x0
#define Conf_Ch_AIN2    0x1
#define Conf_Ch_AIN3    0x2
#define Conf_Ch_AIN4    0x3
#define Conf_Ch_AIN5    0x4
#define Conf_Ch_AIN6    0x5
#define Conf_Ch_Temp    0x6
#define Conf_Ch_VDD     0x7
#define Conf_Ch_AIN1_M   0x8
//-----------------
/*------------------------------------*/

/*--------Defines for IO Reg--------*/
//Zero bits
#define IO_Zero         0x80
//IO enable AIN6
#define IO_IOEN         0x40
//IODAT P2/P1
#define IO_IODAT_P2     0x20
#define IO_IODAT_P1     0x10
//Direction of Current sources
#define IO_IEXCDIR      0xC
#define IO_IEX1IOUT1_IEX2IOUT2  0x0
#define IO_IEX1IOUT2_IEX2IOUT1  0x4
#define IO_IOUT1        0x8
#define IO_IOUT2        0xC
//--------------------------
//Current sourse enable
#define IO_IEXCEN_Dis     0x0
#define IO_IEXCEN_10uA    0x1
#define IO_IEXCEN_200uA   0x2
#define IO_IEXCEN_1mA     0x3   
//--------------------------
/*------------------------------------*/

uint32_t Read_8bit(uint8_t REG);
uint32_t Read_16bit(uint8_t REG);
uint32_t Read_24bit(uint8_t REG);

void Write_8bit(uint8_t REG, uint8_t Data);
void Write_16bit(uint8_t REG, uint16_t Data);
void Write_24bit(uint8_t REG, uint32_t Data);

void PSW_ON();

void AD7794_Init(void);
void Read_All_Regs(void);
uint32_t AD7794_Single_Conversion(uint8_t Channel);
#endif /*__ AD7794_H__ */