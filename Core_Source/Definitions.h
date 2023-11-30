
/********************************************************************
 FileName:     	Definitions.h
 Processors:		32 bit embedded Micro or 32 bit Windows Running PC
 Complier:  	Microchip PIC32 ; Panasonic MN103S ; .net Framework 3.5 CLI Select only One!!
 Company:	Arcelik-LG Klima AS  http://www.arcelik-lg.com.tr/
 Author :     ilker yagci
File Description:
		Preprocessor definitions
 Change History:
  Rev   Date         Description
  1.0   05.04.2012   Initial release
  1.1   10.10.2012   GUI panels defintion Add
 *********************************************************************/

// http://www.embedded.com/design/prototyping-and-development/4024941/Learn-a-new-trick-with-the-offsetof--macro
#define offsetof(s,memb) (size_t)(unsigned int)&(((s *)0)->memb) // return value of a struct member is uint
	// offsetof(struct  Temperature, InSet)


#define INDOOR_FANRATE_0 0
#define INDOOR_FANRATE_1 1
#define INDOOR_FANRATE_2 2
#define INDOOR_FANRATE_3 3
#define INDOOR_FANRATE_4 4
#define INDOOR_FANRATE_5 5
#define INDOOR_FANRATE_SWING 6

#define INDOOR_DEFAULT_FAN_RATE 5

// above definitions add time 10.10.2012 v 1.1

// GENERAL
//#define NULL 0
#define ON 1
#define OFF 0

// MIN MAX PULSE AND STEP
#define MIN 32
#define MAX 64

// RELIABILITY DEFINITIONS

#define OUTD_RELIB_MAX 5
#define INP_VOLTAGE_MAX 7
#define SLEEP_RELIB_MAX 9


#define FALLTABLE_CORRECTION 10
#define  RISETABLE_CORRECTION  1   //

#define  RISING  0   //
#define  FALLING  1   //

#define ACTUAL_MIN  0
#define ALIGN_MIN  1
#define DEFR_MIN  2
#define OUT_MIN  3
#define TC_MIN  4
#define ALIGN_MAX  14
#define DEFR_MAX  15

#define NEGATIVE 0xFF
#define POSITIVE 0x00

#define UNDEFINED 0
// TIMER CONSTANTS ///
#define START_DELAY  180    // 3 MIN TIMER
#define QUICKSTART_DELAY  10    // 10 SEC TIMER
#define FASTSTART_DELAY   5

#define COMP_SAMPLE_TIME  90
#define EEV_SAMPLE_TIME  60
#define FAN_SAMPLE_TIME  120

//#IndoorCommand.Mode
#define REMOTE_OFF 0  // 18-30
#define REMOTE_COOL 1  // 18-30
#define REMOTE_AUTOCHNG 2
#define REMOTE_DEHUMIDIF  3
#define REMOTE_HEAT 4      // 16-30
#define REMOTE_FAN_SPEED 5

// AirCon.MainMode
#define StopM  0
#define CycleM 1
#define SeerM  2
#define PreheatM 3    // fixed frequency only align
#define LqcM       4			// fixed frequency
#define TestM      5			// fixed frequency
#define CopM       6 // fixed frequency

// AirCon.SubMode
#define STANDBYE		 0
#define COOL   			 1  //
#define HEAT				 2
#define COOL_DELAY   3  //
#define HEAT_DELAY   4
#define DEFROST_0	 5  // fixed step
#define DEFROST_1	 6  // fixed step
#define DEFROST_2	 7  // fixed step
#define DEFROST_3	 8  // fixed step
#define DEFROST_4	 9  // fixed step
#define DEFROST_5	 10  // fixed step
#define DEFROST_6	 11  // fixed step
#define DEFROST_7	 12  // fixed step
#define DEFROST_8	 13  // fixed step
//#define DEFROST_5			12  // fixed step
//#define DEFROST_6			13  // // fixed step

#define AUTOCHNG_COOL	 0  // fixed step
#define AUTOCHNG_HEAT	 1  // fixed step
#define AUTOCHNG_DEHUM	 2  // fixed step


// AirCon.AuxiliaryFunction
#define DefaultM 0  // fixed frequency
#define OilSupplyM 1  // fixed frequency

//Motor.Cycle.OperatingMode
#define COMP_STOP  0
#define COMP_FIRST_START1_INIT 1
#define COMP_FIRST_START1 2
#define COMP_FIRST_START2_INIT 3
#define COMP_FIRST_START2 4
#define COMP_SEC_START_INIT 5
#define COMP_SEC_START 6
#define COMP_PI_MODE_INIT 7
#define COMP_PI_MODE  8
#define COMP_CONSTANT_MODE  9

// EEV.CycleMode
#define  EEV_STOP                        0
#define  EEV_FIRST_START_INIT 1
#define  EEV_FIRST_START1        2
#define  EEV_FIRST_START2        3
#define  EEV_FIRST_START3        4
#define  EEV_FIRST_START4        5
#define  EEV_FIRST_START5        6
#define  EEV_FIRST_START6        7
#define  EEV_SEC_START_INIT       8
#define  EEV_SEC_START1           9
#define  EEV_SEC_START2          10
#define  EEV_CONST_PREP          11
#define  EEV_CONSTANT            12
#define  EEV_DEFROST			13

	// EEV.FixedMode
//#define  EEV_STOP              0
#define  EEV_COP				1
#define  EEV_PREHEAT       2
#define  EEV_TEST               3
#define  EEV_LQC                  4
#define  EEV_DEFROST1       5
#define  EEV_DEFROST2       6
#define  EEV_DEFROST3       7
#define  EEV_DEFROST4       8
#define  EEV_DEFROST5       9
#define  EEV_DEFROST6       10


// EEVReliability_Check and  SuperHeatReliability_Check
#define EEV_START 0
#define EEV_STABLE 1



#define VALVE4_COOL  0
#define VALVE4_HEAT  1

#define LINE1   0
#define LINE2   1
#define LINE3   2
#define LINE4   3
#define LINE5   4
#define LINE6   5
#define LINE7   6
#define LINE8   7
#define LINE9   8
#define LINE10  9
#define LINE11  10
#define LINE12  11
#define LINE13  12
#define LINE14  13
#define LINE15  14

#define COLUMN1
#define COLUMN2 1

///   DEFROST  MODE
#define DEF_TABLE_STEP0  0
#define DEF_TABLE_STEP1  2
#define DEF_TABLE_STEP2  4
#define DEF_TABLE_STEP3_1  6
#define DEF_TABLE_STEP3_2  8
#define DEF_TABLE_STEP4_1  10
#define DEF_TABLE_STEP4_2  12
#define DEF_TABLE_STEP5    14
#define DEF_TABLE_WIDTH  5

#define   MAX_MODEL 5
#define   WIDTH  6
#define   TEMP_COLUMN 1
#define   TEMP_LINE  1

#define INDOORNUMBER 1


#define MINMAXTOTCOL  8
#define MINMAXPAIR  2

//#define EEV_EMERGENCY_LIMIT 950 // 95 C



#define  REALTEMPFACTOR 10

#define OUTAIR       0
#define OUTMIDPIPE   1
#define DISCHARGE    2
#define INAIR        3
#define INMIDPIPE    4



#define DEFCONFWIDTH 5
#define TEMPMATCH1_LINE 1
#define TEMPMATCH2_LINE 2

#define RELAY_HEATING  0XF0
#define RELAY_COOLING 0X0F

#define  FANRPM_AUTO 14 // others from 0-13



#define ROOM_TEMPERATURE_TIMER 5


