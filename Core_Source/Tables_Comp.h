
/********************************************************************
 FileName:     	Tables_Comp.h
 Processors:		32 bit embedded Micro or 32 bit Windows Running PC
 Complier:  	Microchip PIC32 ; Panasonic MN103S ; .net Framework 3.5 CLI Select only One!!
 Company:	Arcelik-LG Klima AS  http://www.arcelik-lg.com.tr/
 Author :     ilker yagci
File Description:
		Compressor Related Lookup Tables. These tables have the parameters that can be used while determining compressor frequency,
		so all are used for input  for functions at  compressor.h and Reliability.h.
		They are all stored at volatile memory not at flash. Later with the help of preprocessor memory type must be defined
 Change History:
  Rev   Date         Description
  1.0   05.04.2012   Initial release
 *********************************************************************/
//04_AS-W126B4W0_110307_F24E.xls SB Chassis
#ifdef MANAGED_DOTNET_COMPILER
namespace ACIT_Stack{ // additional line for C++ debugging
#endif

signed char   Cooling_PControl_Table[]= { //sb sase ok
6,		11,     10,      8,       11,  	16,//     DeltaTemperature_Cooling >= 6  step/temperature  // temperatures are real
5,		10,     10,      8,       11,  	16, // 6 < DeltaTemperature_Cooling >= 5
4,		9,      9,      7,       10,  	16, // 5 < DeltaTemperature_Cooling >= 4
3,		 6,      6,      6,        6,  	13, // 4 < DeltaTemperature_Cooling >= 3
2,       5,      5,      5,        5,	12, // 3 < DeltaTemperature_Cooling >= 2
1,       4,      4,      4,        4,	11, // 2 < DeltaTemperature_Cooling >= 1
127,     3,      3,      3,        3,  	 9};// 1 < DeltaTemperature_Cooling  < 1
									                   //   AS-     BS-     BS-      BS-
//Table 4 5 Cooling outdoor temp correction fact.//                                               35*32 = 1120 bits = 140 bytes     step/temperature  // temperatures are multiplied with 10
signed char   Cooling_Outdoor_TempCorFactor[] =   {  //sb sase ok ayni
0,     5,    5,     5,     5,      5, //   Outdoor_Temperature < 0							// else then first column
10,    5,    5,     5,     5,      5, //   Outdoor_Temperature < 10 real val are
23,   10,   10,    10,    10,     10, //   Outdoor_Temperature < 23 divided by10
30,   10,   10,    10,    10,     10, //   Outdoor_Temperature < 30   5 is 0.5
40,   10,   10,    10,    10,     10, //   Outdoor_Temperature < 40   10 is 1
46,   10,   10,    10,    10,     10, //   Outdoor_Temperature < 46
127,   6,    6,     6,     6,	   6};//   Outdoor_Temperature >= 46
									           //   AS-     BS-     BS-      BS-
//Table 4 4						    	      //W126BRU,Q096B4A2,Q096BSA0'Q126BSA0   35*32 = 1120 bits = 140 bytes    step/temperature  // temperatures are real
signed char   Heating_PControl_Table[] = {  //sb sase ok
10,  12,    0,     0,        0,		23, //     DeltaTemperature_Heating >= 10
8,   11,    0,     0,        0,		22, // 10 < DeltaTemperature_Heating >= 8
6,   10,    0,     0,        0,		21, // 8 < DeltaTemperature_Heating >= 6
4,   7,     0,     0,        0,		15, // 6 < DeltaTemperature_Heating >= 4
2,   5,     0,     0,        0,		12, // 4 < DeltaTemperature_Heating >= 2
1,   4,     0,     0,        0,		11, // 2 < DeltaTemperature_Heating >= 1
127, 3,     0,     0,        0,		 9};// 1 < DeltaTemperature_Heating
									                   //   AS-     BS-     BS-      BS-
//Table 4 6 Heating outdoor temp correction fact.       //W126BRU,Q096B4A2,Q096BSA0'Q126BSA0    35*32 = 1120 bits = 140 bytes   step/temperature  // temperatures are multiplied with 10
signed char   Heating_Outdoor_TempCorFactor[] = { //sb sase ok
-7,     13,     0,     0,       0,       13, //  Outdoor_Temperature < -7 7							// else then first column
-2,     12,     0,     0,       0,       12, //  Outdoor_Temperature < -2
 4,     11,     0,     0,       0,       11, //  Outdoor_Temperature < 4
10,     10,     0,     0,       0,       10, //  Outdoor_Temperature < 10
21,      6,     0,     0,       0,        4, //  Outdoor_Temperature < 21
27,      2,     0,     0,       0,        4, //  Outdoor_Temperature < 27
127,     2,     0,     0,       0,        2};//  Outdoor_Temperature >= 27
 /////////////////////////////////////////////////////RS DOCUMENT Table 4.9	////60*32 = 1920 bits = 240bytes ///////
																		 //  Pull data according to error  and error_d . first line errord , first column error
/*
signed char Cooling_PI_Correction_Table[] = {
  0,    -5,    0,     5,   10,    11,//   first line errord// first    temperature/temperature  // temperatures are multiplied with 10
 25,    3,    2,    2,     2,     1,//         2.5 < error               // first line and first column temperatures are only multiplied with 10
 20,    2,    2,    1,     1,     1,//     1.5 < error <= 2
 15,    2,    1,    1,     0,    -1,//       1 < error <= 1.5
 10,    1,    1,    0,    -1,    -1,//    0.5 < error <= 1
  5,     1,    0,   -1,    -2,    -2,//     0 < error <= 0.5
  0,     0,   -1,   -1,    -2,    -2,//  -0.5 < error <= 0
 -5,     0,   -1,   -1,    -2,    -2,//     -1< error <= -0.5
-10,   -1,   -1,   -2,    -2,    -3,//  -1.5 < error <= -1
-99,   -1,   -2,   -2,    -3,    -3};//        error<= -
*/
signed char Common_PI_Correction_Table[] = {
  0,    -5,    0,     5,   10,    11,//   first line errord// first    temperature/temperature  // temperatures are multiplied with 10
 20,    3,    2,    2,     2,     1,//         2.5 < error               // first line and first column temperatures are only multiplied with 10
 15,    2,    2,    1,     1,     1,//     1.5 < error <= 2
10,    2,    1,    1,     0,    -1,//       1 < error <= 1.5
 5,     1,    1,    0,    -1,    -1,//    0.5 < error <= 1
 0,     1,    0,   -1,    -2,    -2,//     0 < error <= 0.5
-5,     0,   -1,   -1,    -2,    -2,//  -0.5 < error <= 0
 -10,   0,   -1,   -1,    -2,    -2,//     -1< error <= -0.5
-15,   -1,   -1,   -2,    -2,    -3,//  -1.5 < error <= -1
-99,   -1,   -2,   -2,    -3,    -3};//        error<= -


signed char Cooling_PI_Correction_Table[] = {
  0,    -5,    0,     5,   10,    11,//   first line errord// first    temperature/temperature  // temperatures are multiplied with 10
 20,    3,    2,    2,     2,     1,//         2.5 < error               // first line and first column temperatures are only multiplied with 10
 15,    2,    2,    1,     1,     1,//     1.5 < error <= 2
10,    2,    1,    1,     0,    -1,//       1 < error <= 1.5
 5,     1,    1,    0,    -1,    -1,//    0.5 < error <= 1
 0,     1,    0,   -1,    -2,    -2,//     0 < error <= 0.5
-5,     0,   -1,   -1,    -2,    -2,//  -0.5 < error <= 0
 -10,   0,   -1,   -1,    -2,    -2,//     -1< error <= -0.5
-15,   -1,   -1,   -2,    -2,    -3,//  -1.5 < error <= -1
-99,   -1,   -2,   -2,    -3,    -3};//        error<= -


/////////////////////////////////////////////////////RS DOCUMENT Table 4.11	////60*32 = 1920 bits = 240bytes ///////
                                                //  error //        error_d
signed char Heating_PI_Correction_Table[] = {
0,    -5,    0,    5,    10,   11,//   first line errord// first
25,    3,    2,    2,    1,    2,//   2.5 < error                  // first line and first column temperatures are only multiplied with 10
20,    3,    2,    2,    1,    2,//     2 < error <= 2.5
15,    2,    2,    1,    0,   -2,//   1.5 < error <= 2
10,    2,    1,    1,    0,   -1,//     1 < error <= 1.5
5,     2,    1,    0,   -1,   -1,//   0.5 < error <= 1
0,     1,    1,    0,   -1,   -1,//     0 < error <= 0.5
-5,    1,    1,   -1,   -1,   -2,//   -0.5< error <= 0
-10,   2,    0,   -1,   -1,   -2,//    -1 < error <= -0.5
-99,   0,    0,   -1,   -2,   -2};//        error <= -1

  /*   	{3,	2,	2,	2,	1},
     	{2,	2,	1,	1,	1},
     	{2,	1,	1,	0,	-1},
     	{1,	1,	0,	-1,	-1},
     	{1,	0,	-1,	-2,	-2},
     	{0,	-1,	-1,	-2,	-2},      heating original
     	{0,	-1,	-1,	-2,	-2},
     	{-1,-1,	-2,	-2,	-3},
     	{-1,-2,	-2,	-3,	-3}
*/
/////////////////////////////////////////////////////RS DOCUMENT Table 4.10	////60*32 = 1920 bits = 240bytes ///////
                                    //    ^C               MODELS
                                    //    ^C     1         2       3        4
 /*signed char Cooling_Remote_Correction_Table[] = {     -128,   90,      91,     92,      93, //  constant time control cycle time [usec]
																					 -5,     2,       2,      2,       2, // Frequency step Correction (K) line7
																					 -4,     1,       1,      1,       1, // Frequency step Correction (K) line7
																					 -3,     1,       1,      1,       1, // Frequency step Correction (h) line5
																					 -2,     0,       0,      0,       0, // Frequency step Correction (j) line5
																					 -1,     0,       0,      0,       0, // Frequency step Correction (j) line5
																					  0,     0,       0,      0,       0, // Frequency step Correction (i) line4
																					  1,     0,       0,      0,       0, // Frequency step Correction (i) line4
													                                  2,     0,       0,      0,       0, // Frequency step Correction (i) line4
										                                			  3,     0,       0,      0,       0, // Frequency step Correction (i) line4
												                                	  4,     1,       0,      0,       0, // Frequency step Correction (h) line4
											                                		  5,     2,       0,      0,       0}; // Frequency step Correction (g) line3
 */																											// error = actual - prev temp/ if minus then user increased temp at cool tendency to reduce frequency
			/*																								// if error plus means user decreased tempearature then tendency to increase step we need more cool
 signed char Cooling_Remote_Correction_Table[] = {
90,   90,     91,      92,		 90,       93, //  constant time control cycle time [usec]
4,      2,      2,       2,       2,		2, // Frequency step Correction (K) line7
2,      1,      1,       1,       1,        1, // Frequency step Correction (j) line5
-2,    -1,     -1,      -1,      -1,       -1, // Frequency step Correction (i) line4  at cooling set temperature increased so decrease step
-4,    -2,     -2,      -2,      -2,      -2}; // Frequency step Correction (h) line4
/////////////////////////////////////////////////////RS DOCUMENT Table 4.12	////60*32 = 1920 bits = 240bytes ///////
																						// error = actual - prev temp / if minus then user increased temp at heating  tendency to increase  frequency
																								// if error plus means user decreased temperature then tendency to decrese step we need less heating
signed char Heating_Remote_Correction_Table[] ={
90,    90,    90,     90,      90,      90,//  constant time control cycle time [usec]  // error / step
-4,     -2,     -2,     -2,      -2,      -2, // Frequency step Correction (K) line7
-2,     -1,     -1,     -1,      -1,      -1, // Frequency step Correction (K) line7
2,     1,      1,      1,       1,       1, // Frequency step Correction (h) line5  at cooling set temperature increased so increase  step too
4,     2,      2,      2,       2,       2}; // Frequency step Correction (j) line5
*/

// All Below Tables are model dependant !!!

signed char Common_Remote_Correction_Table[] ={ // SB sase ok ayni
90,    90,    90,     90,      90,     90,//  constant time control cycle time [usec]  // error / step
4,      2,      2,      2,     2,      2, // Frequency step Correction (j) line5
2,      1,      1,      1,     1,      1, // Frequency step Correction (h) line5  at cooling set temperature increased so increase  step too
-2,    -1,    -1,     -1,     -1,      -1, // Frequency step Correction (K) line7
-4,    -2,    -2,     -2,     -2,      -2}; // Frequency step Correction (K) line7

 	                    //Table 4.7			        1        2       3       4          5
 	                     //     min,max  min,max  min,max  min,max   	////60*8 = 480 bites = 60bytes ///////
//   AS-     BS-     BS-      BS-
//Table 4 2								//W126BRU,Q096B4A2,Q096BSA0'Q126BSA0
/*
unsigned char Model_1[]  = { "SB_Reference"};
unsigned char Model_2[]  = { "Q096B4A2000"};
unsigned char Model_3[]  = { "Q096BSA0000"};
unsigned char Model_4[]  = { "Q126BSA00000"};
unsigned char Model_5[]  = { "ASUW128MMF0"};
unsigned char Model_6[]  = { "NONE -ERROR'"};
*/

signed char  Cooling_Compensation_Table[] = {  5,    5,       5,       5,    5}; // Temperature Compensation Table   SB sase ok
signed char  Heating_Compensation_Table[] = {  30,   0,       0,       0,   30}; // Temperature Compensation Table   SB sase ok
signed char  Auto_Compensation_Table[] =    {  -5,  20};
signed char Auto_Correction= 0;
//Table 4 3							        //W126BRU,Q096B4A2,Q096BSA0'Q126BSA0  35*32 = 1120 bits = 140 bytes
        								                         	    //   AS-     BS-     BS-      BS-
// Table 4.8 used for starting operation      //W126BRU,Q096B4A2,Q096BSA0'Q126BSA0    16*32 = 512 bits = 64 bytes
unsigned char   Starting_Operation_Table[] = {  // consider first 10 sec align  SB sase ok
110,   110,     110,     110,     110,     //  CompressorStage1_[sec] a;option
120,   120,     120,     120,     120,     //  CompressorStage2_[sec] b;option
 3,     3,       3,       3,       8,      //  CompressorStayingStep1_[step] c;option
 8,     8,       7,       7,      15,  //  CompressorStayingStep2_[step] d;opti
10,    10,      10,      10,      10};    // align time 10 sec

unsigned char MinMax_Steps[30] = {
1,12,     1,10,    1,8,    1,11,  1,16,   //COOLING  sb sase ok
3,16,     3,20,    3,20,   3,20,  3,25,   //HEATING
0,16,     0,15,    0,14,   0,13,  0,12};   //Defrost

 unsigned char Table_Step2Frequency[25*5] = { // Sb sase ok
//M1 M2  M3  M4  M5            //M1 = AS-W126BRU0  // FIND THE STEP BY HELP OF ' MODEL' CONST  MODEL s are 1 2 3 4
 25, 25, 25, 25, 10,//1				//M2 = BS-Q096B4A2
 30, 30, 30, 30, 15,//2				//M3 = BS-Q096BSA0            =   Table_Step2Frequency[i*MAX_MODEL+(AirCon.Model)];
 39, 39, 39, 39, 20,//3				//M4 = BS-Q126BSA0
 44, 44, 44, 44, 23,//4
 49, 49, 49, 49, 26,//5
 53, 53, 53, 53, 29,//6
 58, 58, 58, 58, 32,//7
 63, 63, 63, 61, 35,//8
 67, 67, 67, 63, 38,//9
 72, 69, 69, 67, 41,//10
 77, 77, 77, 69, 44,//11
 82, 82, 82, 82, 48,//12
 87, 87, 87, 87, 52,//13
 92, 92, 92, 92, 55,//14
 97, 97, 97, 97, 58,//15
 100,100,100,100, 62,//16
104,104,104,104, 66,//17
107,107,107,107, 69,//18
255,200,255,255, 72,//19
255,200,255,255, 75,//20
255,200,255,255, 79,//21
255,200,255,255, 82,//22
255,200,255,255, 85,//23
255,200,255,255, 88,//24
255,200,255,255, 92};// 25
#define  BIGGEST_FREQUENCY 24
#define  SMALLEST_FREQUENCY 0

#ifdef MANAGED_DOTNET_COMPILER
}
#endif


