
/********************************************************************
 FileName:     	Prototype.h
 Processors:		32 bit embedded Micro or 32 bit Windows Running PC
 Complier:  	Microchip PIC32 ; Panasonic MN103S ; .net Framework 3.5 CLI Select only One!!
 Company:	Arcelik-LG Klima AS  http://www.arcelik-lg.com.tr/
 Author :     ilker yagci
File Description:
		Prototypes of the functions
 Change History:
  Rev   Date         Description
  1.0   05.04.2012   Initial release
 *********************************************************************/

#ifdef MANAGED_DOTNET_COMPILER
namespace ACIT_Stack{ // additional line for C++ debugging
#endif

			void	Remote_Compensation(void);
			void	Update_StableFinal_Step(void);
			void    Find_CompensationStep(void);
			void    Determine_Basic_TargetStep(void);
void Reliability_Fill_Default(void);
void Indoor_Comand_Execute(void);
	void EEV_Stop(void);
	void Defrost_Operation_Handle(void);
// defrost.h
void Defrost_Decision(void);
void Defrost_AverageTemp_Conversion(void);
void Thermal_Cut_Check(void);
void Thermal_Cut_Disable(void);
signed char  Sense_Remote_Change(void);
signed char GetRemoteData(signed char *p);
 void Find_PI_CompensationStep(void);
void SeerDefrost_Decision(void);
//void Defrost_MaintenanceCheck(void);
void Finalize_Defrost_Operation(void);
void Defrost_Escape_Detection(void);
void Defrost_Step_Timeout_Check(unsigned int Line);
void Defrost_GetFinalCompres_SeerFrequency(unsigned int Line);
void Defrost_GetFinalCompres_Step(unsigned char Line);
void Error_Handle(void);
void ErrorPosition(void);

void  Calculate_Start_Step(void);
	void Stop(void);
	void Cooling(unsigned int Mode);
	void Heating(unsigned int Mode);
	//void Defrost_Comp_Step1(void);
	//void Defrost_Comp_Step2(void);
	//void Defrost_Comp_Step3(void);
	//void Defrost_Comp_Step4(void);
	//void Defrost_Comp_Step5(void);
void Finalize_Defrost_Comp_Operation(void);
void Def_Escape_RemainAdd(void);

void DefrostStep1_SubFunc(void);

void Mode_Handle(void);
void Compressor_Cycle(void);

void Check_Abnormal_Modes(void);

void Check_Cycle_SeerSwitch(void);

// Cycle.h
void DetermineTargetStepRegular(void);
void DetermineStepRemoteChange(void);


void DetermineCompressorStep(void);
void Int_Timer_1_Second(void);
void Frequeny_Determine(void);

void Check_HeatCoolDef_Switch(void);

void DriveMotor(void);
void Cycle_Timers (void);
void Finalize_OilSupply(void);

unsigned char GetMinMax_Step(unsigned char MinMax);
//unsigned int GetMinMax_Pulse(unsigned int  MinMax);

void OilSupply_Decision(void);

void  OilSupply_Operation(void);

void  Determine_Initial_Converted_Frequency(void);
void Determine_Basic_Target_Frequency(void);

void  Preheat_Decision(void);
void  Preheat_Operation(void);

void  Cop_Decision(void);

void  Cop_Operation(void);

void ResetCycleSeer_Modes(void);

void Drive_Compressor_Motor(void);

unsigned int Check_Input_Voltage_Limits4_COP(void);

void Init_Datas(void);

void EEV_Cycle(void);
void EEV_DefrostM_1(void);
void EEV_DefrostM_2(void);
void EEV_DefrostM_3(void);
void EEV_DefrostM_4(void);
void EEV_DefrostM_5(void);
void EEV_DefrostM_6(void);
void EEV_DefrostM_1(void);

void EEV_Cop(void);
void EEV_Lqc(void);
void EEV_Test(void);
void Reset_For_Standbye(void);

unsigned char  GetFrequency_From_StepFrequencyTable(unsigned char i);


void Get_Base_pulse(void);
void Get_Fuzzy_Pulse(void);
void Fuzzy_Control_EEV(void);
void Get_Additional_Pulse(void);
void Get_Outdoor_Compensated_Add_Pulse(void);

void EEV_Emergency_Open(void);

unsigned char  EEV_PowerUp(void);

void Calculate_SuperHeat_Initial_Td(void );
void Determine_SuperHeat_Temperature_Compensation(void );
void Determine_SuperHeat_Basic_Td(void);
void Determine_SuperHeat_Final_Td(void);

void  Basic_EEV_StartUp_Procedure(); // we found EEV.Initial.TargetPulse


void Calculate_EEV_Steady_Initial(void);
void Determine_EEV_Steady_Basic(void);
void Determine_EEV_Additional_Pulse(void);
void Determine_EEV_Steady_Final(void);

void	Calculate_EEV_Start_Initial(void); // we found EEV.Initial.TargetPulse
void	Determine_EEV_Start_Compensation(void);
void	Determine_EEV_Start_Basic(void);
void	Determine_EEV_Start_Final(void); // we found EEV.Start.FinalPulse

void Add_Hysteresiz(signed char*p, unsigned char Zone);

void SuperHeatReliability_Check(void);
void EEVReliability_Check(void);



///   EEV & SUPERHEAT COMPENSATION FUNCTION PROTOTYPES

signed char  Compressor_High_F_Compensation(unsigned char i,unsigned char Type);
signed char  Sleeping_Compensation(unsigned char i,unsigned char Type);
signed char  OutdoorFan_Strong_Wind_Compensation(unsigned char i,unsigned char Type);
signed char  IndoorFan_Weak_Wind_Compensation(unsigned char i,unsigned char Type);
signed char  Dewing_Compensation_Start (unsigned char i);
signed char  Dewing_Compensation_Stable(unsigned char i);


signed char  Hot_Start_Compensation(unsigned char i);						//
signed char  Cooling_Low_Compensation(unsigned char i);
signed char  Heating_Low_Compensation(unsigned char i);
signed char  Heating_High_Compensation(unsigned char i);

//unsigned short  Compressor_High_F_Compensation(unsigned char i,unsigned char SUPERHEAT);
//unsigned short  Sleeping_Compensation(unsigned char i,unsigned char SUPERHEAT);
//unsigned short  OutdoorFan_Strong_Wind_Compensation(unsigned char i,unsigned char SUPERHEAT);
//unsigned short  IndoorFan_Weak_Wind_Compensation(unsigned char i,unsigned char SUPERHEAT);
//unsigned short  Dewing_Compensation (unsigned char i,unsigned char SUPERHEAT);

signed char  SuperHeat_Low_Compensation(unsigned char i);
signed char  SuperHeat_High_Compensation(unsigned char i);
signed char  Suction_Freezing_Prevention_Limit(unsigned char i);

///   CYCLE STEP RELIBILITY  FUNCTION PROTOTYPES
void Reliability_Check(void);
void High_Pressure_Condenser_Rising_Prevention_Limit(unsigned char i);		// RS 4.3.2.4  Tc
void Evaporator_Freezing_Prevention_Limit(unsigned char i);		// RS 4.3.2.6  Te
void Compressor_DischargeTemp_Overheating_Limit(unsigned char i);		// RS 4.3.2.2  Td   //Heat_Sink_Overheating_Prevention_Limit  RS 4.3.2.3
void CT_Rising_Preventation_Limit(unsigned char i);                      //   RS 4.3.2.7	CT rising prevention limit
void Heat_Sink_Overheating_Prevention_Limit(unsigned char i);             //   RS 4.3.2.3   HS //
void Dewing_Preventation_Limit(unsigned char i);							// RS 4.3.2.11	Dewing prevention limit
void Outdoor_Temperature_Limit(unsigned char i);                      // RS 4.3.2.9	Outdoor temperature limit
void Suction_Overheating_Level_Rising_Prevention_Limit(unsigned char i);          // RS 4.3.2.8	Suction overheating level rising prevention limit
void Input_Voltage_Limit(void);						// RS 4.3.2.1	Input voltage limit
void Sleeping_Operation_Limit(unsigned char i);								// RS 4.3.2.10	Sleeping operation limit
void Dehumidifying_Operation_Limit(unsigned char i);					// RS 4.3.2.12	Dehumidifying operation limit
void Suction_Pipe_Freez_Prevention_Limit(unsigned char i);  // RS 4.3.2.16
void Economical_Cooling_Limit(unsigned char i); //  4.3.2.13	Economical cooling limit
void Non_Dehumidifying_Limit(unsigned char i);  //  4.3.2.14	Non-dehumidifying operation


void	Compressor_Handle(void);

void	EEV_Handle(void);            // Find EEV Pulse according to cycle mode and target and actual motor frequency
void	Relay_Handle(void);
void	Fan_Handle(void);

void Defrost_SensorEscape_Time_Handle(void);
void Defrost_Step_Time_Handle(void);

void Fan_Total_Compensation_Check(void);
void Fan_Handle(void);
void Fan_Init_Sutiation(void);
void  Fan_Tc_Decision(void);
signed char  Fan_Tc_Compensation(void);
void Fan_HeatSink_Compensation(void);
void Fan_Td_Compensation(void);			  //  tum fan kompanzasyonlari 0
signed char Fan_OutAir_Compensation(void);                    //  tum fan kompanzasyonlari 0
signed char Fan_Temperror_Compensation (void);            //   algoritmasi var bak  0 donuyor superheat ile algoritma ayni onda fazlaliklar var
signed char Fan_OutMidpipe1_Compensation(void);
signed char Fan_PowerHeat_Compensation(void);
signed char Fan_OutMidpipe2_Compensation(void);

#ifdef MANAGED_DOTNET_COMPILER
}
#endif

