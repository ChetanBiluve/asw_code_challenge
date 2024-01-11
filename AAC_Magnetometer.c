/*******************************************************************************
* -- This file contains confidential and proprietary information.              *
* -- (C)Copyright - Chetan Biluve.                            *
********************************************************************************
*-- Project            :                                            		   *
*-- Component          :                                                 	   *   
*-- File               : AAC_Magnetometer.c                            		   *                
*-- Author             : Chetan Biluve                                         *
*-- Version            : Initial Version                                       *
*-- Date               : 03-JAN-2024					                       *
*-- Status             : Development                                           *
*-- Abstract           :           *
*--                                                                            *
*-- Modification History                                                       *
*------------------------------------------------------------------------------*
*Date        | By            | Version       | Change Description              *
*------------------------------------------------------------------------------*
*03-Jan-2024  | Chetan Biluve| 1.0			 | Initial Version                 *
*------------------------------------------------------------------------------*/

/*********************** Header Includes ***********************/
#include "stdio.h"
#include "AAC_Magnetometer.h"
#include "i2c.h"

/*********************** Global Variables ***********************/
//Get the full-scale configuration
uint8_t Get_full_Scale_configuration(uint8_t *Full_Scale_config_Value)
{
	uint8_t I2C_Read_Buffer[2];
	//uint8_t Full_Scale_config_Value;
	
	//Retrieving the Device's Full Scale Configuration
	if (i2c_read(AAC_Magenetometer_I2c_Bus_ADDR, CTRL_REG_2, 1, I2C_Read_Buffer))
		return STATUS_ERROR;
		
	*Full_Scale_config_Value = (I2C_Read_Buffer[0] >> 5) & 0x3;
	
	return STATUS_OK;
}

//set the output data rate
status_t Set_MagnetoMeter_Output_Data_Rate(uint8_t Device_Output_Data_Rate)
{
	uint8_t I2C_Write_Buffer[2];
	uint8_t OM_Value;
	
	if (Device_Output_Data_Rate < 8)
	{
		//Inserting the Device Data Rate to Config reg
		I2C_Write_Buffer[0] = (Device_Output_Data_Rate << 2) & 0x1C;
	
	} else if ((Device_Output_Data_Rate >=8) && (Device_Output_Data_Rate =< 11))
	{
		//Setting the FAST_ODR Bit to ONE
		I2C_Read_Buffer[0] = 0x2;

		switch (Device_Output_Data_Rate) {	
		case 8:
				OM_Value = 0x3;
				break;
		case 9:
				OM_Value = 0x2;
				break;
		case 10:
				OM_Value = 0x1;
				break;
		case 11:
				OM_Value = 0x0;
				break;
		default:
		}
		
		//Inserting the OPerative Mode Values
		I2C_Write_Buffer[0] = I2C_Read_Buffer[0] | ((OM_Value << 5) & 0x60);
	} else 
		return STATUS_ERROR;	
	
	return i2c_write(AAC_Magenetometer_I2c_Bus_ADDR, CTRL_REG_1, 1, I2C_Write_Buffer);
}


//Get  the output data rate
status_t get_MagnetoMeter_Output_Data_Rate(uint8_t *Magentometer_Data_Rate)
{
	uint8_t I2C_Read_Buffer[2];
	uint8_t OM_Value, Fast_odr_Value, Output_Data_Rate_Config_Value, Magentometer_Data_Rate;
	
	//REading  the Output Data Rate Value
	if (i2c_read(AAC_Magenetometer_I2c_Bus_ADDR, CTRL_REG_1,1,I2C_Read_Buffer))
		return STATUS_ERROR;
		
	Fast_odr_Value = (I2C_Read_Buffer[0] >> 1) & 0x1;
	
	if (!Fast_odr_Value)
	{		
		Output_Data_Rate_Config_Value = (I2C_Read_Buffer[0] >> 2) & 0x7;
		*Magentometer_Data_Rate =  Output_Data_Rate_Config_Value;
		
	} else {
		
		//Getting the OM Value
		OM_Value = (I2C_Read_Buffer[0] >> 5) & 0x3;

		switch (OM_Value)
		{	
		case 0:
				*Magentometer_Data_Rate = 11;
				break;
		case 1:
				*Magentometer_Data_Rate = 10;
				break;
		case 2:
				*Magentometer_Data_Rate = 9;
				break;
		case 3:
				*Magentometer_Data_Rate = 8;
				break;
		default:
		}		
	return STATUS_OK;
}
//Enable or disable the device’s interrupt pin
/******************************************************************************
* Function Name: void Enable_disable_INT_Pin (uint8_t INT_EN_DIS)
* Arguments	:
*      Input Arguments      : NULL
*      Output Arguments     : NULL
* Return Value	: void
* Description	: Function to Enable or Disable INT PIN
******************************************************************************/

status_t Enable_disable_INT_Pin (uint8_t INT_EN_DIS)
{ 
	uint8_t I2C_Read_Buffer[2];
	uint8_t I2C_Write_Buffer[2];
	
	if (INT_EN_DIS == Magnetometer_INT_EN) 
	{
		//Enabling the INT PIN
		//REading  INterupt configuration
		if (i2c_read(AAC_Magenetometer_I2c_Bus_ADDR, INT_CFG_REG, 1, I2C_Read_Buffer))
				return STATUS_ERROR;
		
		I2C_Write_Buffer[0] = I2C_Read_Buffer[0] | 0x1;
		
		if (i2c_write(AAC_Magenetometer_I2c_Bus_ADDR, INT_CFG_REG, 1, I2C_Write_Buffer))
			return STATUS_ERROR;
		
		printf ("\n\r INT PIN Is Enabled on the Device");
			
	} else if ((INT_EN_DIS == Magnetometer_INT_DIS))
		//Disabling the INT PIN
		//REading  INterupt configuration
		
		if (i2c_read(AAC_Magenetometer_I2c_Bus_ADDR, INT_CFG_REG, 1, I2C_Read_Buffer))
			return STATUS_ERROR;
			
		I2C_Write_Buffer[0] = I2C_Read_Buffer[0] & 0xFE;
		
		if (i2c_write(AAC_Magenetometer_I2c_Bus_ADDR, INT_CFG_REG, 1, I2C_Write_Buffer))
			return STATUS_ERROR;
			
		printf ("\n\r INT PIN Is DISABLED on the Device");	
		
	} else {
		printf ("\n\r INT ENABLE DISABLE FUNCTION IS CALLED WITH WRONG PARAMETER. ALLOWED VALUES ARE 1/0 ONLY");
		return STATUS_ERROR;
	}	I
	
	return STATUS_OK;
}

//Read the output data of a specific axis
status_t Read_Axis_Data ( uint8_t Axis_Type, uint16_t* Axis_Data)
{
	uint8_t I2C_Read_Buffer[2];
	
	uint8_t Axis_REg_Val;
	
	switch (Axis_Type){	
	case 0:
		Axis_REg_Val = OUT_X_L_REG;	break;
	
	case 1:
		Axis_REg_Val = OUT_Y_L_REG;	break;
	
	case 2:
		Axis_REg_Val = OUT_Z_L_REG;	break;
		
	default:
		printf ("\n\r Wrong Axis Input Value; Allowed Values are: 0-X Axis; 1-Y Axis; 2-Z Axis;");
		return STATUS_ERROR;
	}
	
			//REading  Output Data of X AXIS 
	if (i2c_read(AAC_Magenetometer_I2c_Bus_ADDR, Axis_REg_Val, 2, I2C_Read_Buffer))
				return STATUS_ERROR;
			
	*Axis_Data =  ((I2C_Read_Buffer[1]<<8)|I2C_Read_Buffer[0]));
	
	return STATUS_OK;
}	



uint8_t main() {
	
	uint8_t  Magnetometer_Full_Scale_Configuration;
	uint8_t  Magnetometer_Date_Rate;
	uint16_t Axis_Data
	
//Get the full-scale configuration
	if (Get_full_Scale_configuration(&Magnetometer_Full_Scale_Configuration))print
		printf ("\n\r ERROR: Not able to Read Magnetometer Device");

	switch (Magnetometer_Full_Scale_Configuration) {
		case 0: printf ("\n\r Device Full configuration Value is - ±4 gauss"); break;
		case 1: printf ("\n\r Device Full configuration Value is - ±8 gauss"); break;
		case 2: printf ("\n\r Device Full configuration Value is - ±12 gauss"); break;
		case 3: printf ("\n\r Device Full configuration Value is - ±16 gauss"); break;
		default: 
	}
//Get and set the output data rate	
	if (Set_MagnetoMeter_Output_Data_Rate (DATARATE_560_Hz))
		printf ("\n\r ERROR: Not able to Set Magentometer_Data_Rate");
	else 
		printf ("\n\r INFO: Magnetometer DAta rate is set to - DATARATE_560_Hz");
	
	
	if (get_MagnetoMeter_Output_Data_Rate (&Magnetometer_Date_Rate))
		printf ("\n\r ERROR: Not able to Get Magentometer_Data_Rate");
	
	//Decode the data Rate and Print here
//Enable or disable the interrupt pin

	if (Enable_disable_INT_Pin (Magnetometer_INT_EN))
		printf ("\n\r ERROR: Not able to Enable Magnetometer Interrupt PIN");	
	
	if (Enable_disable_INT_Pin (Magnetometer_INT_DIS))
		printf ("\n\r ERROR: Not able to Disable  Magnetometer Interrupt PIN");


//Read the output data of a specified axis
	if (Read_Axis_Data ( Read_XAxis_Data, &Axis_Data))
		printf ("\n\r ERROR: Not able to Read X Axis Data from MangetoMeter");
	printf ("\n\r Magnetometer  X-AXIS data in 2's Complement - 0x%X", Axis_Data);
	
	if (Read_Axis_Data ( Read_YAxis_Data, &Axis_Data))
		printf ("\n\r ERROR: Not able to Read Y Axis Data from MangetoMeter");
	printf ("\n\r Magnetometer  Y-AXIS data in 2's Complement - 0x%X", Axis_Data);

	if (Read_Axis_Data ( Read_ZAxis_Data, &Axis_Data))
		printf ("\n\r ERROR: Not able to Read Z Axis Data from MangetoMeter");
	printf ("\n\r Magnetometer  Z-AXIS data in 2's Complement - 0x%X", Axis_Data);
	
    return 0;
}