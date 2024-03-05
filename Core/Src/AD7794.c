#include "AD7794A.h"
#include "spi.h"
#include "usart.h"

#define reverse_bytes_16(num) ( ((num & 0x0000FF00) >> 8) | ((num & 0x000000FF) << 8) )
#define reverse_bytes_32(num) (  ((num & 0x00FF0000) >> 16) | ((num & 0x0000FF00)) | ((num & 0x000000FF) << 16) )

uint32_t Read_8bit(uint8_t REG)
{
    uint8_t TX_Data = Comm_RW + (REG << 3);
    uint32_t RX_Data = 0;
    HAL_SPI_Transmit(&hspi1, &TX_Data, 1, 1000);
    HAL_SPI_Receive(&hspi1, &RX_Data, 1, 1000);
    return RX_Data;
}

uint32_t Read_16bit(uint8_t REG)
{
    uint8_t TX_Data = Comm_RW + (REG << 3);
    uint32_t RX_Data = 0;
    HAL_SPI_Transmit(&hspi1, &TX_Data, 1, 1000);
    HAL_SPI_Receive(&hspi1, &RX_Data, 2, 1000);
    RX_Data = reverse_bytes_16(RX_Data);
    return RX_Data;
}

uint32_t Read_24bit(uint8_t REG)
{
    uint8_t TX_Data = Comm_RW + (REG << 3);
    uint32_t RX_Data = 0;
    HAL_SPI_Transmit(&hspi1, &TX_Data, 1, 1000);
    HAL_SPI_Receive(&hspi1, &RX_Data, 3, 1000);
    RX_Data = reverse_bytes_32(RX_Data);
    return RX_Data;
}

void Write_8bit(uint8_t REG, uint8_t Data)
{
    uint8_t TX_Data = (REG << 3);
    HAL_SPI_Transmit(&hspi1, &TX_Data, 1, 1000);
    HAL_SPI_Transmit(&hspi1, &Data, 1, 1000);
}

void Write_16bit(uint8_t REG, uint16_t Data)
{
    uint8_t TX_Data = (REG << 3);
    uint16_t RX_Data = reverse_bytes_16(Data);
    //Data = reverse_bytes_16(Data);
    HAL_SPI_Transmit(&hspi1, &TX_Data, 1, 1000);
    HAL_SPI_Transmit(&hspi1, &RX_Data, 2, 1000);
}

void Write_24bit(uint8_t REG, uint32_t Data)
{
    uint8_t TX_Data = (REG << 3);
    Data = reverse_bytes_24(Data);
    HAL_SPI_Transmit(&hspi1, &TX_Data, 1, 1000);
    HAL_SPI_Transmit(&hspi1, &Data, 3, 1000);
}


void Reg16_Set(uint8_t REG, uint16_t Bits, uint16_t Set, uint16_t *value)
{
    //int16_t value = 0;
    //value = Read_16bit(REG);
    *value &= ~Bits;
    *value |= Set;
    //Write_16bit(REG, value);
}

void Reg16_Reset(uint8_t REG, uint16_t Reset, uint16_t *value)
{
    //int16_t value = 0;
    //value = Read_16bit(REG);
    *value &= ~Reset;
    //Write_16bit(REG, value);
}

void Reg8_Set(uint8_t REG, uint16_t Bits, uint16_t Set, uint16_t *value)
{
    //int8_t value = 0;
    //value = Read_8bit(REG);
    *value &= ~Bits;
    *value |= Set;
    //Write_8bit(REG, value);
}

void Reg8_Reset(uint8_t REG, uint16_t Reset, uint16_t *value)
{
    //int8_t value = 0;
    //value = Read_8bit(REG);
    *value &= ~Reset;
    //Write_8bit(REG, value);
}

void AD7794_Init(void)
{
    
    char str[30];
    uint16_t Data;
    /*
    Data = Read_16bit(Mode_Reg);                            
    sprintf(str, "Mode: 0x%08x\n", Data);
    HAL_UART_Transmit(&huart1, str, strlen(str), 1000);
    */
    
   static uint16_t value_16;
   static uint8_t value_8;

    /*------Configuration Register Init------*/
    value_16 = Read_16bit(Conf_Reg);                                // New reg value
    Reg16_Set(Conf_Reg, Conf_Vbias, Conf_VB_DIS, &value_16);        // Bias voltage diable
    Reg16_Reset(Conf_Reg, Conf_BO, &value_16);                      // Butnout current disable
    Reg16_Reset(Conf_Reg, Conf_UB, &value_16);                      // Bipolar enable                
    Reg16_Reset(Conf_Reg, Conf_Zero, &value_16);                    // Disable zero bits
    Reg16_Set(Conf_Reg, Conf_Gains, Conf_G8, &value_16);            // Gain = 16
    Reg16_Set(Conf_Reg, Conf_Ref, Conf_Int, &value_16);             // Internal 1.17v ref
    //Reg16_Reset(Conf_Reg, Conf_Ref_Det, &value_16);               // Ref detection disable
    Reg16_Set(Conf_Reg, Conf_Ref_Det, Conf_Ref_Det, &value_16);     // Ref detection enable
    Reg16_Set(Conf_Reg, Conf_Buf, Conf_Buf, &value_16);             // Enable buffering mode
    Reg16_Set(Conf_Reg, Conf_Channles, Conf_Ch_AIN1, &value_16);    // Enable channle AIN1+/-
   //Reg16_Set(Conf_Reg, Conf_Channles, Conf_Ch_Temp, &value_16);   // Enable channle temp
    Write_16bit(Conf_Reg, value_16);                                // Write to reg


    //Data = Read_16bit(Conf_Reg);
    //sprintf(str, "Conf: 0x%08x\n\r", Data);                         
    //HAL_UART_Transmit(&huart1, str, strlen(str), 1000);
    /*---------------------------------------*/

    /*------IO Register Init------*/
    //value_16 = Read_16bit(Conf_Reg);                               // New reg value
    Reg8_Reset(IO_Reg, IO_Zero, &value_8);                        // Disable zero bits
    Reg8_Reset(IO_Reg, IO_IOEN, &value_8);                        // Enable analog AIN6
    Reg8_Reset(IO_Reg, IO_IEXCEN_Dis, &value_8);                  // Excitation currents disable
    Write_8bit(IO_Reg, value_8);                                //Write to reg
    Write_8bit(IO_Reg, value_8);                                //Write to reg
    /*----------------------------*/


    //Data = Read_16bit(Conf_Reg);
    //sprintf(str, "Conf: 0x%08x\n\r", Data);                         
    //HAL_UART_Transmit(&huart1, str, strlen(str), 1000);

    //HAL_Delay(1000);
}

uint32_t AD7794_Single_Conversion(uint8_t Channel)
{

    static uint16_t value_16;
    value_16 = 0;
    Reg16_Set(Conf_Reg, Conf_Vbias, Conf_VB_DIS, &value_16);        // Bias voltage diable
    Reg16_Reset(Conf_Reg, Conf_BO, &value_16);                      // Burnout current disable
    Reg16_Reset(Conf_Reg, Conf_UB, &value_16);                      // Bipolar enable                
    Reg16_Reset(Conf_Reg, Conf_Zero, &value_16);                    // Disable zero bits
    Reg16_Set(Conf_Reg, Conf_Gains, Conf_G8, &value_16);            // Gain = 16
    Reg16_Set(Conf_Reg, Conf_Ref, Conf_Int, &value_16);             // Internal 1.17v ref
    //Reg16_Reset(Conf_Reg, Conf_Ref_Det, &value_16);               // Ref detection disable
    Reg16_Set(Conf_Reg, Conf_Ref_Det, Conf_Ref_Det, &value_16);     // Ref detection enable
    Reg16_Set(Conf_Reg, Conf_Buf, Conf_Buf, &value_16);             // Enable buffering mode
    Reg16_Set(Conf_Reg, Conf_Channles, Channel, &value_16);    // Enable channle AIN1+/-
   //Reg16_Set(Conf_Reg, Conf_Channles, Conf_Ch_Temp, &value_16);   // Enable channle temp
    Write_16bit(Conf_Reg, value_16);                                // Write to reg

    value_16 = 0;
   
    Reg16_Set(Mode_Reg, Mode_Mode, Mode_Single_Conv, &value_16);
    Reg16_Set(Mode_Reg, Mode_PSW, Mode_PSW, &value_16);
    Reg16_Reset(Mode_Reg, Mode_Zero, &value_16);
    
    Reg16_Set(Mode_Reg, Mode_CLK, Mode_IN_64_CLK, &value_16);
    
    //Reg16_Reset(Mode_Reg, Mode_Chop_DIS, &value_16);
    Reg16_Set(Mode_Reg, Mode_Chop_DIS, Mode_Chop_DIS, &value_16);
    Reg16_Set(Mode_Reg, Mode_Rate, Mode_Rate_125Hz, &value_16);
    
    Write_16bit(Mode_Reg, value_16);

    while( (Read_8bit(Stat_Reg) & 0x80) != 0);
    return (Read_24bit(Data_Reg));
    

}

void Read_All_Regs(void)
{
    uint32_t Data;
    char str[32];

    Data = Read_8bit(Stat_Reg);
    sprintf(str, "Stat: 0x%08x\n\r", Data);                         
    HAL_UART_Transmit(&huart1, str, strlen(str), 1000);


    Data = Read_16bit(Mode_Reg);
    sprintf(str, "Mode: 0x%08x\n\r", Data);                         
    HAL_UART_Transmit(&huart1, str, strlen(str), 1000);

    Data = Read_16bit(Conf_Reg);
    sprintf(str, "Conf: 0x%08x\n\r", Data);                         
    HAL_UART_Transmit(&huart1, str, strlen(str), 1000);

    Data = Read_24bit(Data_Reg);
    sprintf(str, "Data: 0x%08x\n\r", Data);                         
    HAL_UART_Transmit(&huart1, str, strlen(str), 1000);

    Data = Read_8bit(ID_Reg);
    sprintf(str, "ID: 0x%08x\n\r", Data);                         
    HAL_UART_Transmit(&huart1, str, strlen(str), 1000);

    Data = Read_8bit(IO_Reg);
    sprintf(str, "IO: 0x%08x\n\r", Data);                         
    HAL_UART_Transmit(&huart1, str, strlen(str), 1000);

    Data = Read_24bit(Offset_Reg);
    sprintf(str, "Offset: 0x%08x\n\r", Data);                         
    HAL_UART_Transmit(&huart1, str, strlen(str), 1000);

    Data = Read_24bit(Full_Reg);
    sprintf(str, "Full: 0x%08x\n\r", Data);                         
    HAL_UART_Transmit(&huart1, str, strlen(str), 1000);
}