
/********************************************************************
 FileName:     	Structures.h
 Processors:		32 bit embedded Micro or 32 bit Windows Running PC
 Complier:  	Microchip PIC32 ; Panasonic MN103S ; .net Framework 3.5 CLI Select only One!!
 Company:	Arcelik-LG Klima AS  http://www.arcelik-lg.com.tr/
 Author :     ilker yagci
File Description:
		All Variables. All stored as structure in order to keep consistency between  C and C++. Also to get advantage for intellisense
		while developing with .net code!!
 Change History:
  Rev   Date         Description
  1.0   05.04.2012   Initial release
 *********************************************************************/

#ifdef MANAGED_DOTNET_COMPILER
namespace ACIT_Stack{ // additional line for C++ debugging
#endif
 //////////////////////////////////////////////////////////////  CONTROL PI   //////1////////////////////////////////////////////////////////////////

struct {
	struct {
		signed char CompStart;
		signed char CompStep;
		signed char Remote;
		signed char SuperHeat;
		signed char SuperHeatFrequency;
		signed char EEVFrequency;
		signed char EEVStartPulse;
		signed char EEVStartPulse2Gain;
	}error;
	struct {
		signed char CompStep;
		signed char SuperHeat;
	}error0;
	struct {
		signed char CompStep;
		signed char SuperHeat;
	}errord;
}PI;

 //////////////////////////////////////////////////////////////  INDOOR   //////////////////////////////////////////////////////////////////////
struct IndoorCommand{
	unsigned char Seer;
	unsigned char SleepMode;
	unsigned char  SetTemperature_Cooling;
	unsigned char  SetTemperature_Heating;
	unsigned char  SetTemperature_Auto;
	struct {
		BOOL Enabled;
		BOOL On;
		unsigned char Mode;
		BOOL GUI;
	}SwingDikey;	// IndoorCommand.SwingDikey.Enabled IndoorCommand.SwingYatay.GUI
	struct {
		BOOL Enabled;
		BOOL On;
		unsigned char Mode;
		unsigned char Jet;
		BOOL GUI;
	}SwingYatay;
	struct {
		BOOL Enabled;
		BOOL On;
		BOOL GUI;
	}UpButton;
	struct {
		BOOL Enabled;
		BOOL On;
		BOOL GUI;
	}DownButton;
	struct {
		unsigned int RemotePressTimer;
		unsigned int RemotePressFlash;
		BOOL RemoteFlashOn;
		BOOL RemotePressed;
	}GUIHelp;
	struct {
		BOOL Enabled;
		BOOL On;
		BOOL GUI;
		unsigned char  Timer; // only to help update GUI
	}RoomTemp;
	struct {
		BOOL Enabled;
		BOOL On;
		BOOL  GUI; // only to help update GUI
	}AClean;
	struct {
		BOOL Enabled;
		BOOL On;
		BOOL  GUI; // only to help update GUI
	}ESaving;
	struct {
		BOOL Enabled;
		BOOL On;
		BOOL  GUI; // only to help update GUI
	}Jet;
	struct {
		BOOL Enabled;
		BOOL On;
		BOOL  GUI; // only to help update GUI
	}Plasma;
	struct {
		unsigned char Case;
		unsigned char PrevCase;
		BOOL  OnOff_Enabled;
		BOOL  OnOff;
		BOOL  Enabled;
		BOOL  GUI; // only to help update GUI    IndoorCommand.Mode.GUI
	}Mode;
	struct {
		unsigned char Plasma;
		unsigned char Cool;
		unsigned char Auto;
		unsigned char DeHum;
		unsigned char Heat;
		unsigned char FanMode; //11
		unsigned char Final; //11
		BOOL  Enabled;
		BOOL  GUI; // only to help update GUI
	}FanRate;
	struct {
		BOOL  On;
		BOOL  EnableShort;
		BOOL  EnableLong;
		unsigned int TimerLong;
		unsigned int TimerShort; //11
	}ThermalCut;
}IndoorCommand;  // IndoorCommand.ThermalCut.TimerLong


 //////////////////////////////////////////////////////////////  COMPRESSOR   //////////////////////////////////////////////////////////////////////
struct {
		union{
				unsigned int Start;
		}Adress;
	struct{
		unsigned char TargetStep ;
		unsigned char ActualStep;
		unsigned char OperatingMode;
	}Cycle;
	struct{
		signed char Step1;
		signed char Step2;
		signed char Calculated;
		unsigned char OperatingMode;
	}Start;
	struct{
		signed char Compensation;
		signed char Remote;
		signed char FinalStep;
	}Stable;
	struct{
		unsigned char TargetStep ;
		unsigned char ActualStep;
		unsigned char TargetFrequency ; // for seer mode seer mode uses frequency ??
		unsigned char StartFrequency;
	}Defrost;
	struct{
		unsigned char MaxStep ;
		unsigned char MinStep;
	}Reliability;
	struct{
		unsigned char MaxStep ;
		unsigned char MinStep;
		//unsigned char Step;
		unsigned char TargetStep ;
		unsigned char Frequency;
		unsigned char PreviousFrequency;
	}Basic;
	struct{
		unsigned char MaxStep ;
		unsigned char MinStep;
	}Temporary;
	struct{
		unsigned char ConvertedFrequency;
		unsigned char TargetStep ;
		unsigned char TargetFrequency;
		unsigned char MaxFrequency;
		unsigned char MinFrequency;
	}Initial;
	struct{
		unsigned char Frequency;
		unsigned char PreviousFrequency;
	}OilSupply;          // Motor.OilSupply.Frequency
	struct{
		unsigned char TargetStep ;
		unsigned char TargetFrequency;
	}Previous;
	struct{
		unsigned char TargetFrequency;
	}Preheat;
	struct{
		unsigned char TargetFrequency;
	}LQC;
	struct{
		unsigned char TargetFrequency;
	}Test;
	struct{
		unsigned char TargetFrequency;
	}COP;
	struct{
		unsigned int TargetFrequency;
	}SEER;
	struct{
		unsigned char TargetStep ;
		unsigned char ActualStep;
		unsigned char TargetFrequency;  // end of cycle
		unsigned char ActualFrequency ;
	}Final;
	struct{
		unsigned int Step; // usef for Compressor
		unsigned int FFT;
		unsigned int TotOpTime;
		unsigned int OilSupply;
	}Timer;
}Motor;  // Motor.Timer.OilSupply

 //////////////////////////////////////////////////////////////  EEV   //////////////////////////////////////////////////////////////////////
struct EEV{
	unsigned int Timer;
	unsigned char CycleMode;
	unsigned char FixedMode;
	unsigned int Powerup;
//	#if (defined MICROCHIP_COMPILER || defined MANAGED_DOTNET_COMPILER)
			BOOL  EEVPowerupFlag;
//	#endif
//	#if (defined PANASONIC_COMPILER )
//		   unsigned EEVPowerupFlag :1;
//    #endif

    struct {
		unsigned int BeforeThrottle;
		unsigned int Throttle; 	//	EEV.Final.CycleTargetPulse  EEV.Defrost.BeforeThrottle
	}Defrost;
	struct {
		unsigned int InitialTd;
		signed short TotalCompensation;
		unsigned int BasicPulse;
		unsigned int FinalTd;
		unsigned int PreviousFinalPulse;
		unsigned int StepPulse;
		unsigned int PulseRead1;
		unsigned int PulseRead2;
		unsigned int PulseRead3;
		unsigned int MaxPulse;
		unsigned int MinPulse;
	}Start;
	struct {
		signed short InitialTd;
		signed short CompensationTd;
		signed short  BasicTargetTd;
		unsigned int SignOfCompensationTd;
		unsigned int FinalTargetTd;
		signed char FuzzyPulse;
		signed char CompensationPulse;
		unsigned int TargetPulse;
		signed short  MinTd;            // this can be negative however we will take into account of abs value
		signed short   MaxTd;
		unsigned char SampleTime;
	}SuperHeat;
	struct {
		unsigned int AdditionalPulse;
		unsigned int FinalPulse;
		unsigned int PreviousFinalPulse;
	}Steady;
	struct {
		unsigned int TargetPulse;
		unsigned int CycleTargetPulse; 	//	EEV.Final.CycleTargetPulse
	}Final;
}EEV;

 //////////////////////////////////////////////////////////////  FAN   //////////////////////////////////////////////////////////////////////
struct Fan {
		unsigned int 	Timer;
		signed char Compensation[8];//0-7  Tc_InitStep[5];
		signed char TotalCompensation;
		unsigned char InitStep;
		signed char BasicStep;
		unsigned char MaxStep;
		unsigned char MinStep;
		unsigned char TargetStep;
		unsigned char DefrostStep;
		unsigned char FinalStep;
		unsigned int FinalRpm;
		unsigned int SoftStopTimer;
		short Td0;
		short Td1;
		short Td2;
		short Td3;
		short Td4;
		short Tc0;
		short Tc1;
		short Tc2;
		short Tc3;
		short Tc4;
		unsigned char ManuelMode;  // Auto // Manuel Step 1 -- 13 // default 0 as Auto
		#if( defined MICROCHIP_COMPILER || defined MANAGED_DOTNET_COMPILER)
				BOOL TcLatch;
				BOOL Tc_EmgLatch;
				BOOL TMidLatch;
				BOOL  Td_EmgLatch;
		#endif
		#if ( defined PANASONIC_COMPILER )
		   		unsigned TcLatch :1;
		   		unsigned Tc_EmgLatch :1;
		   		unsigned TMidLatch :1;
		   		unsigned Td_EmgLatch :1;
    	#endif
	struct Indoor {
		unsigned char DefrostStep;
		unsigned char FinalStep;
		unsigned int FinalRpm;
		BOOL HotStart;
	}Indoor;
}Fan;				// Fan.Indoor.FinalStep   Fan.Indoor.FinalRpm  Fan.Indoor.HotStart
struct Relays{
	unsigned char  Valve4Way;
    unsigned char OnOff;
}Relays;
struct Error{
	unsigned char  Compressor; // Error.Compressor
    unsigned char  PFC;// 			Error.PFC
    unsigned char  OutdoorUnit;//  Error.OutdoorUnit
    unsigned char  IndoorUnit;//   Error.IndoorUnit
	BOOL Comp_Enabled;
    BOOL PFC_Enabled;
	BOOL OU_Enabled;
	BOOL IU_Enabled;
}Error;

union DD{
/*	struct Deneme{
		signed short a;			//Tair(OD) // Outdoor (Inlet)(Air) Temperature
		signed short b;		// Tmid(OD) Out. Intermediate (Pipe) Temperature
		signed short c ;	// Td
	}Deneme;
	signed short c ;	// Td
*/
//	struct Error;
//	signed short f;
}DD;


 //////////////////////////////////////////////////////////////  TEMPERATURES    //////////////////////////////////////////////////////////////////////
struct Temperature{
	signed short OutAir;			//Tair(OD) // Outdoor (Inlet)(Air) Temperature
	signed short OutMidPipe;		// Tmid(OD) Out. Intermediate (Pipe) Temperature
	signed short Discharge ;	// Td
	signed short InAir;
	signed short InMidPipe;
	signed short InSet;      // Remote Control set temperature           sizeof(Temperature.InSet)  offsetof(struct  Temperature, InSet)
	signed short InSetPrevious;
	signed short EmergencyDischarge ;	// Td
	signed short HeatSink ;//
	signed short CondenserPrevious;
	signed short DischargePrevious;
	signed short ThermalCut;
}Temperature;
//  ALL TEMPERATURE VALUES ARE HOLD AS MULTIPLIED WITH 10 AT STRUCT IN ORDER TO BE CONSISTENCT AND AVOIDING FROM FRACTIONAL NUMBERS 25C IS 250 AT THE STRUCT!!

//////////////////////////////////////////////////////////////  HARDWARE INPUTS    //////////////////////////////////////////////////////////////////////
struct Hardware{
	unsigned char  Valve4Way;
    unsigned char OnOff;
	unsigned int InpCurrent ;		// Input Current Sensor
	unsigned int  InpVoltage;			//Tair(OD) // Outdoor (Inlet)(Air) Temperature  Hardware
	unsigned int  DCVoltage;		// Tmid(OD) Out. Intermediate (Pipe) Temperature
	unsigned int EEVPulse ;		// Input Current Sensor
	unsigned int  CompressorFreq;			//Tair(OD) // Outdoor (Inlet)(Air) Temperature
	unsigned int  OutFanFreq;		// Tmid(OD) Out. Intermediate (Pipe) Temperature
	unsigned int CompCurrent;	//Motor_Current Phase1
}Hardware;

struct CommunicationUART{
	unsigned int OutdoorError;
	unsigned char OutdoorState;
	unsigned int IndoorError;
	unsigned char IndoorState;
}CommunicationUART;  //Communication.OutdoorError

 //////////////////////////////////////////////////////////////  AIRCON OPERATION MODES   //////////////////////////////////////////////////////////////////////
struct AirCon {
	unsigned char MainMode ;// Cycle // Seer // Preheat // Off // Test_Mode // LQC // stop / Cop //
	unsigned char SubMode;		//  // Cooling // Heating // Defost1 - 6
	unsigned char MainModePrevious;	//Previous Modes//
	unsigned char SubModePrevious;	//Previous Steps/
	unsigned char AuxiliaryFunction;  // now only for OilSupply
	unsigned char OilSupplySubMode;
	unsigned char ExtraMode;
	struct{
	      unsigned ToggleCycle :1;
	      unsigned ToggleSeer :1;
		  unsigned SeerCycle:1;
		  unsigned SeerCycleToggle:1;
	}Conf;
	unsigned char Model;// 1 						// 1-2-3-4  DEFINE MODELS PREPROCESSOR FUNCTIONS
	unsigned int COP;
	struct{
		unsigned int HeatDelay; // timer for switching between cool to heat r vice versa AirCon.Timer.HeatDelay
		unsigned int CoolDelay; // timer for switching between cool to heat r vice versa
	//	unsigned int Delay3Min; // timer for switching between cool to heat r vice versa
		unsigned int TotalHeating;   //
		unsigned int Preheat;
		unsigned int COP;
		unsigned int Defrost ;      // Defrost timing
	}Timer;
}AirCon;  //AirCon.Timer.Defrost

 //////////////////////////////////////////////////////////////  RELIABILITY   //////////////////////////////////////////////////////////////////////
struct Reliability {
	unsigned short Steps[16];        // 14. step is Align Step .. // 15. step is defrost step
	unsigned short SortedSteps[14];
	unsigned short SortedStepsNo[14];
	unsigned char StepIndex[14];       // indicates the line , row number of related reliability function
	signed short EEVStart[6];
	signed short SuperHeat[8];
	unsigned char MinStep[5]; // actual calculated min // 1. Align // 2. defrost mode // 3. outdoor low // tc protection
	unsigned char MinStepOutLow[2]; // array  for min step outdoor air for  cooling and heating cool = 0 heat = 1
	unsigned char MinIndex[2];
//	#if (defined MICROCHIP_COMPILER || defined MANAGED_DOTNET_COMPILER )
		BOOL PowUpMaxEnable[14];    //  unsigned char Reliability.MinStep[5]
		BOOL MaxEnable[14];              //  Reliability.Enable
		BOOL PowUpMinEnable[14];    //
		BOOL MinEnable[2];
//	#endif
/*	#ifdef PANASONIC_COMPILER
		unsigned char PowUpMaxEnable[14];    //
		unsigned char MaxEnable[14];              //  Reliability.Enable
		unsigned char PowUpMinEnable[14];    //
		unsigned char MinEnable[2];
    #endif
*/
}Reliability;

//	#ifdef MANAGED_DOTNET_COMPILER
	//	#define BOOL bool
//		BOOL PowUpMinEnableee[14];    //

//    #endif

struct Reliability_Ram{
		unsigned char PrevZone;
		unsigned char Zone;
		unsigned char Counter;
		unsigned char Timeout;
		unsigned char Hysteresiz[2];  // T0 Hyst T1 Hytst
		signed char   Zone_Limits[5];// { T3 T1 T0}; ////  T3 T1 T0 RAM MEM TABLE
}Reliability_Ram;

struct Reliability_Ram Tc_Hold;
struct Reliability_Ram HS;
struct Reliability_Ram Te_Hold;
struct Reliability_Ram Td_Hold;
struct Reliability_Ram Dew_Hold;

//////////////////////////////////////////////////////////////  TIMERS  //////////////////////////////////////////////////////////////////////
struct Timer{
	unsigned int DefrostEscape; // in defrost for sensor escape continue
	unsigned int DefRemain;
	unsigned int Condenser_DisError;
	unsigned int 	DewReliability;
	unsigned int InpVoltage;
}TimerUc;
//////////////////////////////////////////////////////////////  DEFROST  DECISION //////////////////////////////////////////////////////////////////////
struct Defrost_Average{
	signed short AverageMidPipe;
	signed short AverageOutAir;
	signed short OutAirTemp;		// temporary hold for temperature 32767 / 400 = 819 max sample is 819 for max 40C
	signed short OutMidAirTemp;
	unsigned int  Sample;
	unsigned int Counter;
	#if  ( defined MANAGED_DOTNET_COMPILER  || defined MICROCHIP_COMPILER)
		BOOL  AvConversionDone;
	#endif
	#if ( defined PANASONIC_COMPILER )
		unsigned  AvConversionDone:1;
	#endif

}Defrost_Average;

struct Defrost_Handle{
		unsigned int StartAdress;
		signed short Calculated_Result;
		signed char  Line1;
		signed char  Line2;
		unsigned int  MainCounter;
		unsigned int MaintenanceCounter;

	#if (defined MICROCHIP_COMPILER || defined MANAGED_DOTNET_COMPILER )
		BOOL  Match_Temperature1;   //  1
		BOOL  Match_Temperature2;   //  2
		BOOL  Match_Timeout;            //  3
		BOOL  Match_Maintenance;     //  4
		BOOL  FinalMatch;                  //  6
		BOOL  Enabled;                       //  7
	#endif
	#if (defined PANASONIC_COMPILER )
		unsigned  Match_Temperature1:1;
		unsigned  Match_Temperature2:1;
		unsigned  Match_Timeout:1;
		unsigned  Match_Maintenance:1;
		unsigned  FinalMatch:1;
		unsigned  Enabled:1;

	#endif
} Defrost_Handle;  // Defrost8111.MainCounter  if(Defrost8111.FinalMatch & Defrost8111.Enabled)

struct Defrost_Handle Defrost8111;
struct Defrost_Handle Defrost8112;
struct Defrost_Handle Defrost8113_1;
struct Defrost_Handle Defrost8113_2;
struct Defrost_Handle Defrost8114;
struct Defrost_Handle Defrost8115;    // defrost manuel

 //////////////////////////////////////////////////////////////  DENEM Structure i PI   //////////////////////////////////////////////////////////////////////
struct {
	struct {
		signed char CompStart;
		signed char CompStep;
		signed char Remote;
		signed char SuperHeat;
		signed char SuperHeatFrequency;
		signed char EEVFrequency;
		signed char EEVStartPulse;
		signed char EEVStartPulse2Gain;
	}error;
	struct {
		signed char CompStep;
		signed char SuperHeat;
	}error0;
	struct {
		signed char CompStep;
		signed char SuperHeat;
	}errord;
}TargetStruct;
//#define VERSION_NO 11111

struct { // begin adres XXXXXXXX
		unsigned int Version; //0 //offset				// upon any update Version will update slaves will check version anytime if doesnt have updated will cause error
		unsigned int MapSize;//4								 // pointer size in PC is 4 bytes we will put in order to avoid character to occupy 4 bytes
		unsigned char* AirCon_Adr;	//8						// adress of the AirCon_Adr class
		unsigned char* IndoorCommand_Adr;//12
		unsigned char* Motor_Adr;//16
		unsigned char* EEV_Adr;//20
		unsigned char* Fan_Adr;//24
		unsigned char* Temperature_Adr;//28            // PC holds data as 4 byte wide !!//28
		unsigned char* Reliability_Adr;//32
		unsigned char* Defrost_Average_Adr;//36
		unsigned char* Hardware_Adr;//40
		unsigned char* PI_Adr;//44
		//  Reliability Functions Adress
		unsigned char* Tc_Hold_Adr;//48
		unsigned char* HS_Adr;//52
		unsigned char* Te_Hold_Adr;//56
		unsigned char* Td_Hold_Adr;//60
		unsigned char* Dew_Hold_Adr;//64
		//  Defrost Decision Functions Adress
		unsigned char* Defrost8111_Adr;//68
		unsigned char* Defrost8112_Adr;//72
		unsigned char* Defrost8113_1_Adr;//76
		unsigned char* Defrost8113_2_Adr;//80
		unsigned char* Defrost8114_Adr;//84
		unsigned char* Defrost8115_Adr; // 88 if
		unsigned char* Compile_Info_Adr; //92  // 5C

		unsigned char AirCon_Size;		//				 // total size of AirCon_Adr class    // to read all data start t oread from the start adress until end of the size
		unsigned char IndoorCommand_Size;
		unsigned char Motor_Size;
		unsigned char EEV_Size;
		unsigned char Fan_Size;
		unsigned char Temperature_Size;
		unsigned char Reliability_Size;
		unsigned char Defrost_Average_Size;
		unsigned char Hardware_Size;
		unsigned char PI_Size;
		//  Reliability Functions Size
		unsigned char Tc_Hold_Size;
		unsigned char HS_Size;
		unsigned char Te_Hold_Size;
		unsigned char Td_Hold_Size;
		unsigned char Dew_Hold_Size;
		//  Defrost Decision Functions Size
		unsigned char Defrost8111_Size;
		unsigned char Defrost8112_Size;
		unsigned char Defrost8113_1_Size;
		unsigned char Defrost8113_2_Size;
		unsigned char Defrost8114_Size;
		unsigned char Defrost8115_Size;
		unsigned char Compile_Info_Size; //
}MemoryMap;


	unsigned char Date[12] = __DATE__; // "Mmm dd yyyy"
	unsigned char Time[9] = __TIME__; // "hh:mm:ss"
struct{
	unsigned char Second;
	unsigned char Minute;
	unsigned char Hour;
	unsigned int Year;
	unsigned char Date;
	unsigned char Month[3];
}Compile_Info;  // Compile_Info.Minute


#ifdef   MANAGED_DOTNET_COMPILER

//const
    const char File1_Name[13] =  "Compressor.h";  // T0 Hyst T1 Hytst
	const  char File1_Time[12] =  __TIME__;  // T0 Hyst T1 Hytst
	const 	char File1_Date[12] =  __DATE__;  // T0 Hyst T1 Hytst
	const int File1_Line =  __LINE__;  // T0 Hyst T1 Hytst
//	String^ F_Naeme="";
//	const  char File1_Path[24] =  __FILE__;  // T0 Hyst T1 Hytst
//	const  char File1_Name[13] =  "Compressor.h";  // T0 Hyst T1 Hytst


const struct{
		//const  char fer[12] =  __DATE__;  // T0 Hyst T1 Hytst
		 char fer[12];// =  __DATE__;  // T0 Hyst T1 Hytst

		}FileInfo;

//	FileInfo.fer[] = __DATE__;
#endif

#ifdef MANAGED_DOTNET_COMPILER
}
#endif
