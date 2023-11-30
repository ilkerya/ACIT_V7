

/********************************************************************
 FileName:     	Acit_GUI.h
 Processors:		32 bit embedded Micro or 32 bit Windows Running PC
 Compiler:  	 .net Framework 3.5 CLI Select only One!!
 Company:	Arcelik-LG Klima AS  http://www.arcelik-lg.com.tr/
 Author :     ilker yagci
File Description:
		All Variables. All stored as structure in order to keep consistency between  C and C++. Also to get advantage for intellisense
		while developing with .net code!!
 Change History:
  Rev   Date         Description
  1.0   05.04.2012   Initial release
 *********************************************************************/


namespace EEV_Sim{ // additional line for C++ debugging

	//static unsigned int Original_Log_File_post_add = 0;
	static  bool ScriptEnable[8] ={0,0,0,0,0,0,0,0};
	static unsigned int  ScriptOrder[8] ={88,88,88,88,88,88,88,88}; // last is

	static  short ScriptTemperatures[16] = {}; // i*x start // (i*2)+6 stop
	static  unsigned int  ScriptTimes[8] = {5,5,5,5,5,5,5,5}; // i*x start // (i*2)+6 stop
	//static bool	Script_Process_Enable;
	static	signed int 	Script_TimeInterval[8]= {5,5,5,5,5,5,5,5};
	static	signed int 	Script_TempInterval[8]= {5,5,5,5,5,5,5,5};

static struct GUISTRUCT{
		struct {
				unsigned int StartOf1;
				unsigned int StartOf2;
		} Reset;
		struct { // GUI.Reset.
			//bool ScriptEnable[8] ={0,0,0,0,0,0,0,0};
			bool	Script_Process_Enable;
			unsigned int ScriptOrdIndex;  // GUI.Script // GUI.Log
		} Script;  // Script.ScriptEnable[8] ={0,0,0,0,0,0,0,0};
		struct {
				unsigned int ComponentIndex;
				unsigned int ArrayMaxIndex;
				unsigned int TotalStartIndex;
				unsigned int ArrIndexer;
				float TrackPosition;
				float BandWidthMid;
				float Reminder;
				float Coefficient;
				unsigned int SnapDatastart;
		}Chart; //GUI.Chart.PositionOfTrack
		struct {
			unsigned char MainMode ;// Cycle // Seer // Preheat // Off // Test_Mode // LQC // stop / Cop //
			unsigned char SubMode;		//  // Cooling // Heating // Defost1 - 6
			unsigned char prev_OperatingMode;
			unsigned char Freq_erorr;
		}AirCon;
		struct {
			unsigned int Base1mSec;
			unsigned int Base10mSec;
			unsigned int Base50mSec;
			unsigned int Base100mSec;
			unsigned int Base1Sec;
			unsigned int Base2Sec;
			unsigned int Base10Sec;
			unsigned int Base100_Count;
			unsigned int Base15Minutes;
			bool Flag_Base10mSec;
			bool Flag_Base50mSec;
			bool Flag_Base100mSec;
			bool Flag_Base1Sec;
			bool Flag_Base2Sec;
			bool Flag_Base10Sec;
			bool Flag_Base15Minutes;
		}Timer;
		struct {
			int  Prev;
		}RealTime;
		struct {
			bool CurrentFreq;
			bool PreviousFreq;
		}Motor;
		struct {
			bool PreviousRpm;
			bool CurrentRpm;
		}Fan;
		struct {
			unsigned int  TargetTd;
		}EEV;
		struct {
			bool DataShift;
			bool USB_Conncetion_OK;
			unsigned int ErrorRate;
			unsigned int   CRC_Calculated ;
			unsigned int   CRC_Received;
		}USB;
		struct {
				bool Status;
				bool Error;
				unsigned int Counter;
				unsigned int  SampleCounter;
				unsigned int InitTime;
				unsigned int  FileCount;
				unsigned int Original_Log_File_post_add;
				bool LogChartDeleteEnable;
				int LogChartDeleteTimer;
		 		int LogStopCounter ;
		 		int Log_SampleTime ;
		 		int ChartSoftOffTimer;
		} Log;
		struct {
				bool One;
				bool Two;
				bool Three;
				bool Four;
				bool Five;
				bool Six;
				bool Seven;
				bool Eight;
		} Defrost;
		struct {
			 int Counter;
		 	 int AutomaticCounter;
		} Capture;
		struct {
				bool ExpandLeftPanel;
				bool ExpandRightPanel;
				bool Play;
				unsigned int Panel_Counter;
				bool SlidePlay;
				unsigned int SlideTimer;
				unsigned int FlashTimer;
				unsigned int FanTimer;
				bool  AnimationHelp;
				bool  Animation2Help;
				unsigned int Demo_Timer;
			}View;
		struct {
		//	bool Priority_High;
		//	bool Priority_Mid;
		//	bool Priority_Low;
			unsigned int Priority;
			bool Demo;
		}Access;
		struct {
			unsigned int Timer;
			unsigned int Flash;
		}OnOff;

	}GUI; 	//GUI.View.FlashTimer GUI.View.ExpandPanel GUI.OnOff.Timer   GUI.OnOff.Flash

		#define PASSWORD_DISABLED_FOR_LOCMACHINE 22
//#define DENIZ_HOCA_MODE 22

	#define GUI_DEFAULT_VALUE 123;
	#define  DEFAULT_PLAY 0  // 0 PLAY // 1 PAUSE

/*************** SCREEN CAPTURE  ****************/

	#define CAPTURE_COUNT   10   //  switch(GUI.View.Panel_Counter
	#define CAPTURE_MAXCOUNT   200   //  switch(GUI.View.Panel_Counter

/*************** CHARTS  ****************/

	#define BIG_ARRAYSIZE 2*60*1 // 90*60 = 5400 // 90 min for 1 sec 180 min for 2 sec array of chart data log
	#define SNAP_BANDWIDTH 60    // snap chart data for log
	#define  DEFROSTARRAYSIZE 1000
	#define PH_MAXWIDTH 8

/*************** LOG FILE  ****************/

	#define DEFAULT_LOGSAMPLE 2
	#define DEFAULT_LOGMAXHOUR 2700 // 2700 data for 1 sec sample 45 seconds// 2 sec sample 90 seconds // 10 sec sample 450 seconds or 7.30 hour


/*************** SCRIPT  ****************/

	#define INPVOL_COFF 1
	#define MAXVAR 8

/*************** USB  ****************/

	#define TEMP_BOUNCE 150 // 15c    X10 Temp  // FILTER 15c FOR BOUNCES AT COMMUNICATION

/*************** GUI FOR COMPRES.. PANEL   ****************/

	#define StepAnimation_X 10
	#define StepAnimation_Y 192

/*************** SECURITY LEVEL. PANEL   ****************/

	#define PRIORITY_FIRST 0
	#define PRIORITY_SECOND 2
	#define PRIORITY_THIRD 4
	#define PRIORITY_FOURTH 8

/*************** PANEL SELECTIONS  ****************/

	#define COMPRESSOR_PANEL 0   //  switch(GUI.View.Panel_Counter
	#define RELIABILITY_PANEL 1
	#define EEV_PANEL 2
	#define FAN_PANEL 3
	#define DEFROST_PANEL 4
	#define INDOOR_PANEL 5
	#define GRAPHICS_PANEL 6
	#define LOGGING_PANEL 7
	#define COMMUNICATION_PANEL 8
	#define ERROR_PANEL 9   //  switch(GUI.View.Panel_Counter
	#define OPMODE_PANEL 10
	#define SCRIPT_PANEL 11
	#define SECURITY_PANEL 44

	#define DEFAULT_START_PANEL 1
	#define MAXIMUM_PANEL 11  // MAX SECILEN PANEL ILE AYNI OLMALI

/*************** GUI COLOR SELECTION   ****************/

				#define TOOLBAR_DEFAULT_COLOR System::Drawing::Color::Black
				#define TOOLBAR_ACTIVE_COLOR System::Drawing::Color::Firebrick
				#define STANDBYE_COLOR System::Drawing::Color::LimeGreen
 				#define COOLDELAY_COLOR System::Drawing::Color::PaleTurquoise  // Honeydew
				#define COOLING_COLOR System::Drawing::Color::DarkTurquoise  //LightBlue
			 	#define HEATDELAY_COLOR System::Drawing::Color::LemonChiffon  // Honeydew
				#define HEATING_COLOR System::Drawing::Color::Gold // LemonChiffon
				#define DEFROST_COLOR System::Drawing::Color::Thistle

				#define COL_TEMP_INAIR System::Drawing::Color::DarkCyan
				#define COL_TEMP_INSET System::Drawing::Color::Magenta
				#define COL_TEMP_INPIPE System::Drawing::Color::OrangeRed
				#define COL_TEMP_DISCHARGE System::Drawing::Color::MediumPurple
				#define COL_TEMP_OUTPIPE System::Drawing::Color::SandyBrown
				#define COL_TEMP_OUTAIR System::Drawing::Color::Green
				#define COL_MOTOR_FREQ System::Drawing::Color::Black,2

				#define COL_EEV_PULSE System::Drawing::Color::Red,2
				#define COL_ERROR  System::Drawing::Color::Olive
				#define COL_FAN_RPM System::Drawing::Color::Orange
				#define COL_INDOORFAN_RPM System::Drawing::Color::Green

				#define COL_TEMP_HEATSINK System::Drawing::Color::Chocolate

				#define COL_INP_CURRENT  System::Drawing::Color::Goldenrod
				#define COL_INP_VOLT System::Drawing::Color::CornflowerBlue
				#define COL_COP System::Drawing::Color::SlateGray

				#define COL_MOTOR_FREQ4_TEXT System::Drawing::Color::PaleGoldenrod

				#define LOG_SAMPLE_DEACTIVE_COLOR System::Drawing::Color::Black
				#define LOG_SAMPLE_ACTIVE_COLOR    System::Drawing::Color::Firebrick

/*************** GUI PANEL DEFAULT POSITIONS AND SIZES   ****************/

	#define ACPICPANEL_X_START 0  // LEFT TOP
	#define ACPICPANEL_Y_START 26
	#define ACPICPANEL_SECURITY_X_START 350  // LEFT TOP
	#define ACPICPANEL_SECURITY_Y_START 206 // 226
	#define ACPICPANEL_WIDTH 199
	#define ACPICPANEL_HEIGHT 634  //614
																			#define REMOCONPANEL_WIDTH 195
																			#define REMOCONPANEL_HEIGHT 465
																			#define REMOCONPANEL_X_START 1404  // RIGHT TOP
																			#define REMOCONPANEL_Y_START 24
																			#define REMOCONPANEL_X_SECURITY_START 881  // RIGHT TOP
																			#define REMOCONPANEL_Y_SECURITY_START 324

							#define MIDPANEL_HEIGHT 1000 // MIDDLE PANEL
							#define MIDPANEL_WIDTH 1200
							#define MIDPANEL_X_START 200
												#define MIDPANEL_X_START_WIDE 0
							#define MIDPANEL_Y_START 28

	#define ANIMPANEL_X_START 0    // LEFT BOTTOM
	#define ANIMPANEL_Y_START 666
	#define ANIMPANEL_X_SECURITY_START 600    // LEFT BOTTOM
	#define ANIMPANEL_Y_SECURITY_START 666
	#define ANIMPANEL_WIDTH 199
	#define ANIMPANEL_HEIGHT 184 //143
																			#define REM_INFOPANEL_WIDTH 195
																			#define REM_INFOPANEL_HEIGHT 376
																			#define REM_INFOPANEL_X_START 1404  // RIGHT BOTTOM
																			#define REM_INFOPANEL_Y_START 490
																			#define REM_INFOPANEL_X_SECURITY_START 881  // RIGHT BOTTOM
																			#define REM_INFOPANEL_Y_SECURITY_START 490


	#define SECURITYPANEL_WIDTH 496
	#define SECURITYPANEL_HEIGHT 512
	#define SECURITYPANEL_X_START 576  // RIGHT TOP
	#define SECURITYPANEL_Y_START 64
	#define LOGCHART_DATASELECT_Y_START 712




}

