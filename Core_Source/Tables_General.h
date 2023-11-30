
/********************************************************************
 FileName:     	Tables_General.h
 Processors:		32 bit embedded Micro or 32 bit Windows Running PC
 Complier:  	Microchip PIC32 ; Panasonic MN103S ; .net Framework 3.5 CLI Select only One!!
 Company:	Arcelik-LG Klima AS  http://www.arcelik-lg.com.tr/
 Author :     ilker yagci
File Description:
		EEV, Defrost, Fan Related Lookup Tables.
		so all are used for input  for functions at  EEV.h,  EEV_Comp.h, Defrost.h, Decision.h and Fan.h
		They are all stored at volatile memory not at flash. Later with the help of preprocessor memory type must be defined
 Change History:
  Rev   Date         Description
  1.0   05.04.2012   Initial release
 *********************************************************************/
//04_AS-W126B4W0_110307_F24E.xls SB Chassis
#ifdef MANAGED_DOTNET_COMPILER
namespace ACIT_Stack{ // additional line for C++ debugging
#endif

	///////////////// COMPRESSOR RELIABILITY TABLES//////////////////////////////////////

	// Below Table is a reference Table only it tells which variable to use from the the table like Zone_Table_Tc[]
	// for example Zone_Table_Tc you want to pull Timer3 Value first refer to this table and pull related line no
	//this line will be a refernece to pull data from it
	// At void Reliability_Check(void) you have to call related function at the same order as the table !!
#define CONF_WIDTH 9
unsigned char Zone_Configuration_Table[] ={  // 64 means absent others are offset adresses of each Table Data
//CoolX4 CoolX2 HeatX4 HeatX2 Hyst  Timer1  Timer2 Timer3	// Conf_Line
//															     zone 1       zone 2      zone 3       zone 4
	0,       1,        2,          3,          4,				6,			    4,			    7,				5,   // Tc       0        zone2 is not included as parameter at code so has no meaning
	0,       1,        0,          1,          2,				5,			    4,			    4,				3,   // Te       1                    // for next feature
	0,       1,        0,          1,          2,				5,				4,				4,				3,   // Td       2
	0,       1,        4,          5,         64,				3,			    4,				4, 			    6,   // Ct       3
	0,       1,        0,          1,          2,				3,				4,				5,				6,   // HS       4
	0,       1,        4,          5,         64,				3,			    4,				4, 			    6,   //?       5
	0,       1,        0,          1,          2,				3,				4,				5,				6,   // ?      6
	0,       1,        0,          1,          2,				3,				4,				5,				6,   // ?     7
    0,       1,        0,          1,         2,				5,				4,				4,				3};  // Dew     8


signed char Zone_Table_Tc[] ={  // FLASH MEM TABLE  OPTION TABLE direct pullup values //SB ok
//W126BRU,Q096B4A2,Q096BSA0'Q126BSA0  // MODEL
 63,	 64,	 63,	 64,  63,//  Tc T4 cooling			0
 59,	 60,	 59,	 60,  59, //  Tc T2 cooling          1
 63,	  0,	  0,	   0,  63,//  Tc T4 heating         2
 57,	  0,	  0,	   0,  57,//  Tc T2 heating         3
  1,     1,      1,      1,    1, // Tc Hysteresiz         4
  2,	  2,	  2,	   2,    2,  // Tc  Timer1 Fast Down Timer  5
  9,	  9,	  9,	   9,    9,  // Tc  Timer2 Slow Down Timer 6
  9,	  9,	  9,	   9,    9 }; // Tc  Timer3 Slow Up Timer    7

signed char Zone_Table_Te[] ={  // FLASH MEM TABLE //  OPTION TABLE direct pullup values  //SB ok
  1,	  0,	  0,	  0,	  0, // Te  T4
  5,	  4,	  4,	  4,	  2,//  Te  T2
  1,        1,     1,     1,      1, // Te Hysteresiz
  6,	  6,	  6,	  6,	  6, // Te  Timer1 Fast Down Timer
 12,	  6,	  6,	  6,	 12, // Te  Timer2 Slow Down Timer
 12,	 12,	 12,	 12,	 12, // Te  Timer3 Slow Up Timer 10* sec
  5,	  5,	  5,	  5,	  5}; // Te  Skip Time (min)

signed char Zone_Table_Dew[] ={  // FLASH MEM TABLE OPTION TABLE direct pullup values  //SB ok
 10,	 	10,	  	9,	 	 	9,	    	9, // Dew  T4
 14,	 	14,	   13,	 		13,			13,//  Dew  T2
  0,     	0,      0,      	0,      	0, // Dew Hysteresiz
  3,	  	3,	  	3,	  		3,	  		3, // Dew  Timer1 Fast Down Timer
  4,	  	4,	  	4,	  		4,	  		4, // Dew  Timer2 Slow Down Timer
  6,	  	6,	  	6,	  		6,	  		6, // Dew  Timer3 Slow Up Timer 10* sec
  5,	  	5,	  	5,	  		5,	  		5, // Dew  Skip Time (min)
  24,	 	24,	   24,	 		24,     	24, // Control 1   // min  OutAir icinde gecerli eev Comp
 31,	 	31,	   31,	 		31,     	31,// Control 2  // aslinda 31 di fakat 31.0 oluyor gercek sicaklik 31.9 olmsai lazim 32 ye tamamladim
 1,			1,		1,		   1,			1}; // Flow Rate // minstep for dew

signed char Zone_Table_Td[] ={  // FLASH MEM TABLE  OPTION TABLE direct pullup values  //SB ok
105,   105,	105,	95,   95, // Td  T4
 95,	95,	 95,	85,   85,// Td  T2
  3,     3,   3,     3,   3, // Td Hysteresiz
  2,	 2,	  2,	 2,	  2,  // Td  Timer1 Fast Down Timer
  6,	 6,	  6,	 6,	  6, // Td  Timer2 Slow Down Timer
 18,	18,	 18,	18,	 18}; //Td  Timer3 Slow Up Timer

unsigned char Sleeping_Max_Step[] ={
4,     4,    4,     4,  11,   //COOLING
4,     0,    0,     0,  14};   //HEATING

 signed char Outdoor_Cooling_TempLimit_Table[] = {  // OPTION TABLE direct pullup values SB sase ok
 0,   3,    3,    3,    3,   10, //   Outdoor_Temperature < 0							// else then first column
10,   3,    3,    3,    3,   10,  //   Outdoor_Temperature < 10 real val are
23,   4,    5,    5,    5,   12, //   Outdoor_Temperature < 23 divided by10
30,   10,   5,    7,    7,   16, //   Outdoor_Temperature < 30   5 is 0.5
40,   12,  10,   8,   11,   16, //   Outdoor_Temperature < 40   10 is 1
46,   8,   8,    7,    9,   16, //   Outdoor_Temperature < 46
127,  7,   7,    6,    7,   16};//   Outdoor_Temperature >= 46

 signed char Outdoor_Heating_TempLimit_Table[] = {  //SB sase ok
-7,   16,    10,    10,    10,   12, //   Outdoor_Temperature < 0		 					// else then first column
-2,   15,    10,    10,    10,   15,  //   Outdoor_Temperature < 10 real value are
 4,   13,    10,    10,    10,   17, //   Outdoor_Temperature < 23 divided by10
10,   11,   10,    10,    10,   19, //   Outdoor_Temperature < 30   5 is 0.5
21,   11,   10,    10,    10,   23, //   Outdoor_Temperature < 40   10 is 1
27,    5,    10,    10,    10,   25, //   Outdoor_Temperature < 46
127,  3,    10,    10,    10,   25};//   Outdoor_Temperature >= 46

signed char Zone_Table_HS[] ={  // FLASH MEM TABLE
 85, 	85,	 	85,		80,		85, // HS  T4
 95, 	95,	 	95,		90,		95, // HS  T2
 1,     1,      1,     	1,     1,  // HS Hysteresiz Amper multiplied by 10 0.5 0.3 ......
 3,		3,		3,		3,	  3,  // HS  Timer1				20  20 20 20
 6,		6,		6,		6,	  6,  // HS  Timer2
 6,		6,		6,		6,	  6}; // HS  Timer3           ALL SEC TIMERS ARE DIVIDED BY 10 AT THE TABLES !!

signed char Zone_Table_CT[] ={  // FLASH MEM TABLE
  75,75,	 62,	 60,	 60,//  CT I2 cooling <= 38C Outdoor Air Temperature							Index = 31
  90,90,	 70,	 68,	 68,//  CT I4 cooling <= 38C Outdoor Air Temperature
  70,70,	 62,	 60,	 60,//  CT I2 cooling  > 38C  Outdoor Air Temperature         7.0   6.2    6.0   6.0
  85,85,	 70,	 68,	 68,//  CT I4 cooling  > 38C  Outdoor Air Temperature  all temperatures at current prevent table is multiplied by 10 !!
  85,85,	  0,	  0,	  0,//  CT I2 heating <= 18C Outdoor Air Temperature								Index = 35
  10,10,	  0,	  0,	  0,//  CT I4 heating <= 18C Outdoor Air Temperature
  75,75,	  0,	  0,	  0,//  CT I2 heating  > 18C Outdoor Air Temperature
  90,90,	  0,	  0,	  0};//  CT I4 heating  > 18C Outdoor Air Temperature

short  MinHzLimCooling_OutLow[] = {
//temp C // freq        // Min step limitation for reliability for outdoor low RS 4.3.2.17
32767,     	   9,
280,	      10,
180,		  20,
100,		  25,
  0,		  30,
};
short MinHzLimHeating_OutLow[] = {
//OP_Tc_min_zonex  //  OP_Tc_zone1_min_hz   // Min step limitation for reliability for outdoor low  RS 4.3.2.18
//temp C // freq
 150,		   15,
  50,	       19,
 -50,		   20,
-100,		   21,
-150,		   23,
};
short  MinCondenserLimit[] = {
//OP_Tc_min_zonex  //  OP_Tc_zone1_min_hz // Min step limitation for condenser temperature low  RS 4.3.2.19
//temp C // freq
60,		  30,
55,		  20,
51,		  16,
47,	      14,
41,		   9,
};

unsigned char Inp_Volt_MaxLim[] ={
//cool  // heat
230,	230,		// standart voltage
 10,    10,			// standart voltage range
 0,      0,       	// coefficients
 5,      5,        // timeout timers
};


//////////////////////////////////////////////////////////////////  DEFROST TABLES /////////////////////////////////////////////////////////////
	#if (defined MICROCHIP_COMPILER || defined MANAGED_DOTNET_COMPILER )
		BOOL  Defrost_Decision_Configuration_Table[] ={
		#endif
	//#if (defined MICROCHIP_COMPILER)
	//	BOOL Defrost_Decision_Configuration_Table[] ={
	//	#endif
	#if (defined PANASONIC_COMPILER)
unsigned char Defrost_Decision_Configuration_Table[] ={
    	#endif
// Func1 Func2 Func3 Func4 Func5
       0,        0,        1,      1,         1,  //ADC WAIT
       1,        1,        1,      1,         1,  //Enabled for future feature load at startup later configure it by user interface
       1,        1,        1,      1,         1,  //Match_Temperature1
	   0,        0,        1,      1,         1};  //Match_Temperature2

signed short   Defrost_RS_8_1_1_1[12]= {    // table values are real temp values when using table values to be compared must be diveded to 10 !
  0,    32767,
 -50,    -240,
-100,    -250,
-150,    -260,
-32768, -300,
-32768, -350};
  signed short Defrost_RS_8_1_1_2[]= {   // table values are real temp values when using table values to be compared must be diveded to 10 !
  0,     -150,
 -50,    -190,
-100,    -230,
-150,    -270,
-32768, -32768};

signed short Defrost_RS_8_1_1_3_1[]= {   // table values are not real temp values multiplied with 10 !  when using table values must directly compared  !
// 	 escape temp  t_delta_T_deice_
-20,	60};			// first line is for defrost 8.1.1.3.1 function
signed short  Defrost_RS_8_1_1_3_2[]= {   // table values are not real temp values multiplied with 10 !  when using table values must directly compared  !
// 	 escape temp  t_delta_T_deice_
60,     50};          	// second  line is for defrost 8.1.1.3.2 function
signed short  Defrost_RS_8_1_1_4[] = {   // table values are real temp values when using table values to be compared must be diveded to 10 !
 40,   -50, // 2.  priority
-30,   -60,  // 1. priority   ROM
-20,   -20};
unsigned char  Defrost_RS_8_1_1_4_Time[] = {   // time values
180,  120};
/*  this array contains all defrost entry timeout values 1.column is for maintenance 2.for.column totalheating timeout
		ROM TABLE CONST	  //MAINTENANCE TIMEOUT,   CONTINIOUS TIMEOUT,  OP TIME [SEC]     */
unsigned int Const_Defrost_Table[] ={
180,            300, 	// Def_Chk_Step == 0  RS_8_1_1_1   600/60= 10min
180,            900, 	// Def_Chk_Step == 1  RS_8_1_1_2  1800/60= 30min
180,           1500, 	// Def_Chk_Step == 2  RS_8_1_1_3_1  1200/60= 20min  // 2400
180,           1500, 	// Def_Chk_Step == 2  RS_8_1_1_3_2  1200/60= 20min // 2400
//180,           7200, 	// Def_Chk_Step == 3  RS_8_1_1_4  7200/60= 120min  confusion with
180,           9900,	// Def_Chk_Step == 4  RS_8_1_1_5 10800/60= 180min /3 hours   RS table 120
180,           7200,	// Def_Chk_Step == 4  RS_8_1_1_5 10800/60= 180min /3 hours   RS table 120
180,           2100};	// Def_Chk_Step == 5  Seer Mode Check    2100/60= 35min
/* below array contains defrost entry timeout values 1.column is for maintenance 2.for.column totalheatting timeout
    		RAM TABLE	//DEFROST FLAG // MAINTENANCE TIMER, enable flags  		OP TIME [SEC]  RAM TABLE  */
unsigned char  Mem_Defrost_Table[]={
0,   		0,			24,  	 	// Def_Chk_Step == 0  RS_8_1_1_1
0,   		0,			24,     	// Def_Chk_Step == 1  RS_8_1_1_2
0,   		0,			24,     	// Def_Chk_Step == 2  RS_8_1_1_3
0,   		0,			0,     		// Def_Chk_Step == 3  RS_8_1_1_4
 0,   		0,			0,     		// Def_Chk_Step == 4  RS_8_1_1_4
0,   		0,			0};	    	// Def_Chk_Step == 5  Seer Mode Check
		// rom array            SAMPLE NO  SAMPLE INTERVAL(sec)
unsigned char Rom_Temperature_Average[]= {
5,		60,  			//OUTDOOR TEMPERATURE  RAM TABLE
5,		60} ; 	 		//OUTDOOR PIPE TEMPERATURE

		 // SAMPLING-MODULE//     SAMPLE   SAMPLE   SAMPLE     ADC       ADC   ADC-CONVERTED
		//ram array     	        // on/off   onoff-prev    TIMER    ENABLE   COUNTER   BUFFER   AVERAGE    FLAG
unsigned char  Ram_Temperature_Average[]=  {
0,    	  1,       0,        0,       0,	   0,	0,   	  0,   //OUTDOOR TEMPERATURE  RAM TABLE Temperature_Real.MidPipe
 0,   	  1,       0,        0,		0,    0,	0,		  0};   //OUTDOOR PIPE TEMPERATURE Temperature_Real.OutPipe
//on/off  onoff-prev
//0    0  stop no execution
//1    0  start command . perform one time job and set second column
//1    1  operating  go on operating
//0    1  stop command perform stop job an clear second column

unsigned int Defrost_TimeComponent[]= {
//time  comp    eev     out     ind
//(sec) step    pos     fan     fan
5,		64,		 0,		64,		64,	     // STEP0
5,		 0,		 0,		64,		64,	     // STEP1
10,		 3,		 0,		 0,		 0,	     // STEP2
5,		 3,		 0,		 0,		 0,	     // STEP3  // evaporator 25C ustunde 2 dak devam ederse 2 step atla yani 5. ye gec
60,		 5,		300,	 0,		 0,	     // STEP4
540,	10,	    300,	 0,		 0,	     // STEP5  //1.evaporator 40C ustune cikarsa birsonraki stepe atla / 2. %85 kuralina gore gecerse  sonraki sebe atla
20,	     0,		 0,		 13,	 0,	     // STEP6
20,	 	 0,		 0,		 13,	 1,      // STEP7
};   // STEP5 // cikis

/*
0,	  	70,        // STEP6   onemli deil



										  10,		  6,	     // STEP4  Defrost Mode first 10 sec cycle  mode step  for remain time from step3
											  10,		 13,	     // STEP4  Defrost Mode 2. 10 sec cycle  mode step
											  10,		 13,	     // STEP4  Defrost Mode first 10 sec seer  mode step
 											  10,		 70,        // STEP4 Defrost Mode 2. 10 sec seer mode frequencyDefrost Mode first 10 sec seer mode frequency
											  40,		  0,        // STEP4 Seer Mode  70 is frequency
									  20,		  0,	     // STEP5 compresor On mOde
									1,		  0};	     // STEP6 compresor On mOde
	*/

unsigned char Defrost_CompOnTable[]= {		ON,			// if 0 comp off mode if 0 comp. on mode
											5,  //5  OP_defrost_01_02_comp_step
											5};///OP_comp_startup_01_step  5 steps   MinMax_Steps[(MODEL-1)*MINMAXPAIR+MINMAXTOTCOL],

unsigned char Defrost_EscapeTimeTemperature[] = {//  temperature  timeout(sec)   switchtostep

		DEFROST_5,	100,	1,	DEFROST_6,		// defrost step2 -> DefMStep5 // step1 if temp more then 10C  and lasts 0 sec switch to defmode5 (immidiately !)
		DEFROST_5,	25,		2,	DEFROST_6,		// defrost step2 -> DefMStep5 // step2 if temp more then 25 and lasts 2 sec switch to defmode5
		DEFROST_6,	40,		1,	DEFROST_7,		// defrost step3_1 -> DefMStep4 // step1	if temp is more then 40 and lasts for more then 0 sec switch to def mode 4
		DEFROST_6,	20,		30,	DEFROST_7,		// defrost step3_1 -> DefMStep4 // step2
		DEFROST_6,	40,		1,	DEFROST_7,		// defrost step3_1 -> DefMStep4 // step1	if temp is more then 40 and lasts for more then 0 sec switch to def mode 4
		DEFROST_6,	20,		30,	DEFROST_7   };		// defrost step3 _1-> DefMStep4 // step2

unsigned char Defrost_Escape[] = {//  temperature  timeout(sec)   switchtostep

		DEFROST_3,	100,	1,	DEFROST_4,		// defrost step2 -> DefMStep5 // step1 if temp more then 10C  and lasts 0 sec switch to defmode5 (immidiately !)
		DEFROST_3,	25,		2,	DEFROST_4,		// defrost step2 -> DefMStep5 // step2 if temp more then 25 and lasts 2 sec switch to defmode5
		DEFROST_4,	40,		1,	DEFROST_5,		// defrost step3_1 -> DefMStep4 // step1	if temp is more then 40 and lasts for more then 0 sec switch to def mode 4
		DEFROST_4,	20,		30,	DEFROST_5,		// defrost step3_1 -> DefMStep4 // step2
		DEFROST_4,	40,		1,	DEFROST_5,		// defrost step3_1 -> DefMStep4 // step1	if temp is more then 40 and lasts for more then 0 sec switch to def mode 4
		DEFROST_4,	20,		30,	DEFROST_5   };		// defrost step3 _1-> DefMStep4 // step2

											// ***Attention at above table we define the prev step to switch  when ever timeout occurs algoritm loads next steps values and next step is executed!!
unsigned char  Defrost_EscapeTimers[6] = {//  temperature  timeout(sec)   switchtostep
0,0,0,0,0,0
};

///////////////////////////////////////////////////////////  EEV TABLES ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//	Line is error_check way is ->

signed char FuzzyTable[16*16] = {
// e
0,  10,  7,  5,  4,  3,  2,  1, -1, -2, -3, -4, -5, -7,-10, -128,// if( ed > table[i]) -> way to check  |/
20,	    -14,-14,-14,-14,-14,-14,-14,-12, -8, -8, -7, -5, -3, -2, -2,   //  FIRST LINE IS DIFFERENTIAL ERROR
15,     -14,-14,-13,-12,-12,-12,-12,-10, -7, -6, -6, -4, -2, -2,  0,  // FIRST COLUMN IS ERROR
11,	   -14,-13,-12,-12,-10,-10,-10, -8, -5, -5, -5, -3, -1,  0,  1,
 8,	    -14,-13,-12,-10, -8, -8, -8, -6, -3, -3, -3, -1,  0,  1,  2,
 5,	    -14,-13,-10, -8, -8, -6, -5, -4, -2, -2, -1,  0,  1,  2,  4,
 3,	    -12,-11, -8, -6, -6, -5, -3, -2, -1,  0,  0,  1,  2,  3,  5,
 2,	    -9,  -7, -5, -5, -5, -3, -2, -1,  0,  0,  1,  2,  3,  5,  6,
-2,	    -7,  -5, -4, -3, -2, -1,  0,  0,  0,  1,  2,  3,  4,  5,  7,
-3,	    -6,  -5, -3, -2, -1,  0,  0,  1,  2,  3,  5,  5,  5,  7,  9,
-5,	    -5,  -3, -2, -1,  0,  0,  1,  2,  3,  6,  8,  8, 10, 11, 12,
-8,	    -4,  -2, -1,  0,  1,  2,  2,  4,  5,  8, 10, 12, 12, 13, 14,
-11,    -2,  -1,  0,  1,  3,  3,  3,  6,  8, 10, 12, 12, 12, 13, 14,
-15,    -1,   0,  1,  3,  5,  5,  5,  8, 12, 12, 12, 12, 12, 13, 14,
-20,     0,   2,  2,  4,  6,  6,  7, 10, 12, 12, 12, 12, 13, 14, 14,
-128,    2,   2,  3,  5,  7,  8,  8, 12, 14, 14, 14, 14, 14, 14, 14};


float TargetTd_Coefficient_Table[8]={
//cool    /   heat
74.74f,  	49.03f,	// Ktd const  Ktd
 0.08f,  	 0.08f,	// Ki indoor
 0.08f,   	 0.08f, 	// Ko outdoor
 1.83f,      0.13f};	// Kf frequency


unsigned int MinMax_Pulses[] = {
60,400,  60,400,     60,400,     60,400,     60,400,   //COOLING   // cooling overload icin min pulse sb sase icin 80
60,400,  60,400,     60,400,     60,400,     60,400};   //HEATING

float  EEV_Initial_Table[] = { // SB sase ok
37.9f,  37.86f, 37.86f, 37.86f, 37.9f,	//0  COEFFSTRT_FIXED_COOL  37.86f    // ee2 232
1.78f,   1.78f,  1.78f,  1.78f,  1.78f, //1  COEFFSTRT_FREQ_COOL    1.78f,    // ee2 238
-3.91f, -3.91f, -3.91f, -3.91f, -3.91f, //2  COEFFSTRT_IN1_COOL    -3.91f,    // ee2 240 indoor
 27.0f, 27.0f,  27.0f,  27.0f,  27.0f,	//3  COEFFSTRT_IN2_COOL    27.0f,     // ?
1.91f,  1.91f,  1.91f,  1.91f,   1.91f,	//4  COEFFSTRT_OUT1_COOL    1.91f,   // ee2 242  outdoor
35.0f,  35.0f,  35.0f,  35.0f,  35.0f,	//5  COEFFSTRT_OUT2_COOL   35.0f,

55.9f, 55.19f, 55.19f,   55.19f, 55.9f, //6  COEFFSTRT_FIXED_HEAT 55.19f,   // ee2   252
1.14f,  1.14f,   1.14f,  1.14f,  1.14f, //7  COEFFSTRT_FREQ_HEAT   1.14f,   // ee2   258
1.47f,  1.47f,	 1.47f,	 1.47f,  1.47f,	//8  COEFFSTRT_IN1_HEAT    1.47f,   // ee2   260 indoor
20.0f, 20.0f,    20.0f,  20.0f,  20.0f,	//9  COEFFSTRT_IN2_HEAT    20.0f,
-4.23f,-3.04f,  -3.04f, -3.04f, -4.23f,	//10 COEFFSTRT_OUT1_HEAT  -3.04f,   // ee2   262  outdoor
7.0f,   7.0f,    7.0f,   7.0f,   7.0f};  //11 COEFFSTRT_OUT2_HEAT   7.0f,

float  S_Heat_Initial_Table[] = { // SB sase degerleri aptalca sanirim p-inverterde degerler islemciden aliniyor.
84.0f,  84.0f,  84.0f,  84.0f,  84.0f,  //0 COEFFSTABL_FIXED_COOL  84.0f  // ee2   279  Td Rate
0.08f,  0.08f,  0.08f,  0.08f,  0.08f,	//1 COEFFSTABL_FREQ1_COOL  0.08f  //ee2    290
-1.03f,-1.03f, -1.03f, -1.03f, -1.03f,  //2 COEFFSTABL_FREQ2_COOL  1.03f,   //ee2   292
0.78f,  0.78f,  0.78f,  0.78f,  0.78f, 	//3 COEFFSTABL_IN1_COOL    0.78f,   //ee2   286
13.0f,  13.0f,  13.0f,  13.0f,  13.0f,	//4 COEFFSTABL_IN2_COOL    13.0f,  // ee2   283 Te Rate  InMid
1.6f,   1.6f,   1.6f,   1.6f,    1.6f, 	//5 COEFFSTABL_OUT1_COOL    1.6f,  // ee2   284
48.0f,  48.0f,  48.0f,  48.0f,  48.0f, 	//6 COEFFSTABL_OUT2_COOL   48.0f,  // ee2   282  Tc Rate  OutMid
-0.08f,-0.08f,-0.08f, -0.08f,  -0.08f,		 //7 COEFFSTABL_DISCH_COOL -0.08f,  // ee2   288

75.0f,  75.0f, 75.0f,  75.0f,   75.0f,  //8 COEFFSTABL_FIXED_HEAT   				 Td Rate
0.0f,    0.0f,  0.0f,   0.0f, 	 0.0f, 	//9 COEFFSTABL_FREQ1_HEAT 0.0f,  // ee2  yok
0.0f,    0.0f,  0.0f,   0.0f,    0.0f, 	//10 COEFFSTABL_FREQ2_HEAT 1.0f,  // ee2 yok
0.60f,  0.60f, 0.60f,  0.60f,   0.60f, 	//11 COEFFSTABL_IN1_HEAT    0.60f,  // ee2
1.0f,    1.0f,  1.0f,   1.0f,    1.0f,	//12 COEFFSTABL_IN2_HEAT    1.0f,  // ee2   Te Rate
1.6f,    1.6f,  1.6f,   1.6f,    1.6f,	//13 COEFFSTABL_OUT1_HEAT    1.6f,  // ee2
47.0f,  47.0f, 47.0f,  47.0f,	47.0f,	//14 COEFFSTABL_OUT2_HEAT   47.0f,  // ee2 301  Tc Rate
-0.08f,-0.08f, -0.08f, -0.08f, -0.08f};	//15 COEFFSTABL_DISCH_HEAT  -0.08f,  // ee2  // isareti ayni  sogutma il




unsigned char SuperHeatMinMaxCoefficients[3]={13,3,95}; // sb sasede 12,5 degerler.

unsigned char EEV_PowerUp_Table[20] = { // GUI powerup
	35 ,     10, //
	22,		20,
	11,		30,//2
	0,		40,
	2 ,     50,//4
	11,		60,
	22,		70,// 6
	34,		80,
	46,		90,//8
	70,		100};

unsigned char EEV_StartTable[16] = {
	 10,		5,//1
	 10,		6,//2
	 10,		7,//3
	 10,		8,//4
	 10,		9, // 5
	 70,	   10, // 6
    120,	   10, //2. 1
    120,	   10}; //2 . 2

unsigned char  EEV_OpenLevel_Coefficient_Table2[6]={
//cool    /   heat
	27,       20,        // ki indoor
	35,       27,        // ko outdoordoor
    35,      7}; // TEMP algorithm change only applicable for cooling
///////////////////////////////////////////////////////		START UP / BASIC START PROCEDURE FUNCTIONS OF EEV CONTROL ////////////////////////////////////////////////////////////////////////
float EEV_OpenLevel_Coefficient_Table1[8]={
//cool    /   heat
37.86f,  	55.19f,	// Ktd const  Ktd
 1.78f,  	     1.14f,	// K  frequency
-3.91f,   	 1.47f, 	// K indoor
1.91f,       -3.04f};	// K outdoor

	 ////////////////////// ADDITIONAL TABLES

void Check_Cycle_SeerSwitch(void){}


signed char ThermalCut_Table[4] = {
// C  time sec
	5,    18,    //0.5C  THCUT_LONG_TIME
	20,  1};  // 2 C THCUT_SHORT_TIME
//unsigned char TorqueMaxTable[] ={ 8};

unsigned int Oil_SupplyTable[] = { //time (sec)  Hz
1800,	 25,  // 1800 sec 25Hz
5,          30}; // 5 sec   30 Hz

///////////////////////////////////////////////////////		FAN CONTROL TABLES ////////////////////////////////////////////////////////////////////////
/*
unsigned char  FanStep2RpmTable[14] = { //Attention multiply with 10 while using values // OPTION TABLE pullup values
0,
17,//1
21,//2
25,//3
30,//4
35,//5
40,//6
45,//7
50,//8
55,//9
61,//10
66,//11
71,//12
81};//13
*/
unsigned char  FanStep2RpmTable[14] = { //Attention multiply with 10 while using values // OPTION TABLE pullup values
0,
26,//1
32,//2  SB Chassis
39,//3
44,//4
48,//5
54,//6
62,//7
67,//8
73,//9
78,//10
83,//11
85,//12
100};//13
short  Fan_Err_CompTable[]  = {
25,  280, 1,
25,  180, 1,
};

unsigned int  Fan_Tc_Compensation_Threshold[]  = {
180	,	5,   360 // temperature outair if less then 18 decision for Tc Latch 5C if latch ok
};
/*
signed char  Fan_Tc_CompTable[]  = {
40	,	1, // temperature more  then 40C =1  less then 25C -1 for midpipe
25,    -1,// compensation step
6,      1,// Max Min for less then 5C outair
8,      1,// Max Min for more then  5C outair
};
*/
signed char  Fan_Tc_CompTable[]  = { //SB Chassis
30	,	1, // temperature more  then 40C =1  less then 25C -1 for midpipe
20,    -1,// compensation step
6,      1,// Max Min for less then 5C outair
8,      1,}; // Max Min for more then  5C outair

signed char Fan_CompOutAir_Cool[22] ={
45, 3,// 1,
41, 2,// 1, // rearranged to SB chassis
38, 1,// 0,
28, 0,// 0,
24, -2,//-1,
18, -4,//-2,
14, -6,// -3,
9, -7,//  -4,
2, -7,//  -6,
-5, -8,// -9,
-100, -10,};// -9,};
signed char Fan_CompOutAir_Heat[20] ={
26, -5,// -9,
22, -4,// -8,
18, -2,// -3,
14, -1,// -2,rearranged to SB chassis
12, 0,// -1,
4, 0,//   0,
0, 1,//   1,
-4, 1,//  1,
-8, 1,//  1,
-100, 1,};// 1,};
signed char Fan_MidHeat_Comp[] ={
	15, 7 , -2};
unsigned int  InddoorFanStep2RpmTable[7]  = {
0, // stop  mode
940,// 1  mode
1100,// 2  mode
1200,// 3  mode
1315,// 4  mode
1475,// 5  mode
1000,// swng mode
};
/*
unsigned int Defrost_TimeStep_Table[]= { //time(sec)    step
											  15,		 0,	     // STEP1 off mode
											  10,		 5,	     // STEP1 compresor On mOde
											  5,		 0,	     // STEP2 off mode
											  5,		 5,	     // STEP2 compresor On mOde
		        							  60,		 6,	     // STEP3_1 Cycle Mode Normal defrost first 60 sec
											  900,	 	13,	     // STEP3_2 Cycle Mode Normal Mode Heating 13 is cycle   15 min   960 = 900 + 60 sec(firts step)
 											  600,	 	13,        // STEP3  Cycle Mode Normal Mode After preheat process 13 is cycle  10 min
											  300,	 	13,        // STEP3   Seer Mode  defrost 13 is step            4 min   300 = 240 + 60 sec
											  300,	  	70,        // STEP3   Seer Mode  70 is frequency

									  		10,		  6,	     // STEP4  Defrost Mode first 10 sec cycle  mode step  for remain time from step3
											  10,		 13,	     // STEP4  Defrost Mode 2. 10 sec cycle  mode step
											  10,		 13,	     // STEP4  Defrost Mode first 10 sec seer  mode step
 											  10,		 70,        // STEP4 Defrost Mode 2. 10 sec seer mode frequencyDefrost Mode first 10 sec seer mode frequency
											  40,		  0,        // STEP4 Seer Mode  70 is frequency
									  			20,		  0,	     // STEP5 compresor On mOde
	*/

#ifdef MANAGED_DOTNET_COMPILER
}
#endif
