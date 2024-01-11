
#define AAC_Magenetometer_I2c_Bus_ADDR 0x20

#define OFFSET_X_REG_L_M_REG_ADDR 0x5
#define OFFSET_X_REG_H_M_REG_ADDR 0x6
#define OFFSET_Y_REG_L_M_REG_ADDR 0x7
#define OFFSET_Y_REG_H_M_REG_ADDR 0x8
#define OFFSET_Z_REG_L_M_REG_ADDR 0x9
#define OFFSET_Z_REG_H_M_REG_ADDR 0xA

#define CTRL_REG_1 	0x20
#define CTRL_REG_2 	0x21
#define CTRL_REG_3 	0x22
#define CTRL_REG_4 	0x23
#define CTRL_REG_5 	0x24

#define STATUS_REG 	0x27

#define OUT_X_L_REG 	0x28
#define OUT_X_H_REG 	0x29
#define OUT_Y_L_REG 	0x2A
#define OUT_Y_H_REG 	0x2B
#define OUT_Z_L_REG 	0x2C
#define OUT_Z_H_REG 	0x2D

#define TEMP_OUT_L_REG 	0x2E
#define TEMP_OUT_H_REG 	0x2F

#define INT_CFG_REG 	0x30
#define INT_SRC_REG 	0x31
#define INT_THS_L_REG 	0x32
#define INT_THS_H_REG 	0x33

//magnetometer Data Rate 
#define DATARATE_0_625_Hz 	0
#define DATARATE_1_25_Hz 	1
#define DATARATE_2_5_Hz 	2
#define DATARATE_5_Hz 		3
#define DATARATE_10_Hz 		4
#define DATARATE_20_Hz 		5
#define DATARATE_40_Hz 		6
#define DATARATE_80_Hz 		7
#define DATARATE_155_Hz 	8
#define DATARATE_300_Hz 	9
#define DATARATE_560_Hz		10
#define DATARATE_1000_Hz	11	

//Full Scale Configuration Values
 
#define FS_4_Gauss 			0
#define FS_8_Gauss 			1
#define FS_12_Gauss 		2
#define FS_16_Gauss 		3

//Read Axis Data

#define Read_XAxis_Data 	0
#define Read_YAxis_Data 	1
#define Read_ZAxis_Data 	2

#define Magnetometer_INT_EN 	1
#define Magnetometer_INT_DIS 	0
