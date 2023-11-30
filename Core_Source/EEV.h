
/********************************************************************
 FileName:     	EEV.h
 Processors:		32 bit embedded Micro or 32 bit Windows Running PC
 Complier:  	Microchip PIC32 ; Panasonic MN103S ; .net Framework 3.5 CLI Select only One!!
 Company:	Arcelik-LG Klima AS  http://www.arcelik-lg.com.tr/
 Author :     ilker yagci
File Description:
		Expansion Valve Final Position Determining Algorithms
 Change History:
  Rev   Date         Description
  1.0   05.04.2012   Initial release
  1.1   20.11.2012   EEV Target Td Calculation parameters Moved to lookup tables for 5 models
 *********************************************************************/

#ifdef MANAGED_DOTNET_COMPILER
namespace ACIT_Stack{ // additional line for C++ debugging
#endif

unsigned int GetMinMax_Pulse(unsigned int MinMax){
		unsigned int  i=0;
		unsigned int *p = &MinMax_Pulses[0];
	switch(AirCon.SubMode){
		default:
		case DEFROST_0: case DEFROST_1: case DEFROST_2:case DEFROST_3:case DEFROST_4:case DEFROST_5:case DEFROST_6:case DEFROST_7:case DEFROST_8:
		case COOL_DELAY:
      	case COOL: i =  (AirCon.Model*MINMAXPAIR);  //Model = MODEL-1;     // keep in mind MODEL is 1,2,3,4 for other tables we
       		break;
		case HEAT_DELAY:
		case HEAT:i =  (AirCon.Model*MINMAXPAIR+10);  // have to use at this table starting from 0 to 3
			break;
	}
	if(MinMax == MIN)return p[i];
	if(MinMax == MAX)return p[i+1];
	return 0xFF; // error not any condition like this
}
void GetEev_Cycle_Time(unsigned char i, unsigned int EEVStep){
			EEV.Timer = EEV_StartTable[i*2];
	//	#if (defined MANAGED_DOTNET_COMPILER || defined MICROCHIP_COMPILER)
				EEV.Final.CycleTargetPulse =  (unsigned int)((float) EEV_StartTable[i*2+1] / 10 *(float) EEVStep) ;
	//	#endif
	//	#if (defined PANASONIC_COMPILER)
	//			EEV.Final.CycleTargetPulse =  (unsigned int)( EEV_StartTable[i*2+1] / 10 * EEVStep) ;
	//	#endif
			switch(EEV.CycleMode){
				case EEV_FIRST_START_INIT:
				case EEV_FIRST_START1:
				case EEV_FIRST_START2:
				case EEV_FIRST_START3:
				case EEV_FIRST_START4:
				case EEV_FIRST_START5:
				case EEV_FIRST_START6: EEV.Start.MinPulse = 0; EEV.Start.MaxPulse = GetMinMax_Pulse(MAX);
							break;
				case EEV_SEC_START_INIT:
				case EEV_SEC_START1:
				case EEV_SEC_START2:EEV.Start.MinPulse = GetMinMax_Pulse(MIN); EEV.Start.MaxPulse = GetMinMax_Pulse(MAX);
				default: break;
			}
			if( EEV.Final.CycleTargetPulse < EEV.Start.MinPulse) EEV.Final.CycleTargetPulse = EEV.Start.MinPulse;
			if( EEV.Final.CycleTargetPulse > EEV.Start.MaxPulse) EEV.Final.CycleTargetPulse = EEV.Start.MaxPulse;

			EEV.CycleMode++;

	}
void EEV_Cycle(void){
	EEV.FixedMode = EEV_STOP;
   Calculate_EEV_Start_Initial();
   Calculate_SuperHeat_Initial_Td();
	switch(EEV.CycleMode){
		case EEV_STOP: 	break;
		case EEV_FIRST_START_INIT:  //	ui_target_pulse_temp[0] = MW_eev_startup_control(gc_mode_syst,t_preheat_time,th_outdoor_air,th_indoor_air[0],t_start_frq,th_indoor_midpipe[0],th_outdoor_midpipe,th_dpipe_inv,ui_eev_pulse_trc[0],0,ui_target_pulse_temp[0]);
								    EEV.Start.PulseRead1 = EEV.Start.StepPulse;// get the pulse to use at first 120 sec
									 GetEev_Cycle_Time(0,EEV.Start.PulseRead1); //synchronize to compressor
							break;
		case EEV_FIRST_START1:	if(!EEV.Timer) GetEev_Cycle_Time(1,EEV.Start.PulseRead1);
				break;
		case EEV_FIRST_START2:	if(!EEV.Timer)		GetEev_Cycle_Time(2,EEV.Start.PulseRead1);
				break;
		case EEV_FIRST_START3:	if(!EEV.Timer)	GetEev_Cycle_Time(3, EEV.Start.PulseRead1);
				break;
		case EEV_FIRST_START4:	if(!EEV.Timer) GetEev_Cycle_Time(4,EEV.Start.PulseRead1); //load 10 sec last
				break;
		case EEV_FIRST_START5:	if(!EEV.Timer)	GetEev_Cycle_Time(5,EEV.Start.PulseRead1); // 50 timeout  //load 70 sec
				break;
		case EEV_FIRST_START6:	if(!EEV.Timer)  EEV.CycleMode++;	// 70 timeout
				break;
  		case EEV_SEC_START_INIT:	EEV.Start.PulseRead2 = EEV.Start.StepPulse; // get the pulse to use at second 120 sec
									GetEev_Cycle_Time(6,EEV.Start.PulseRead2); // get 120 1 timeout
				break;
		case EEV_SEC_START1:
								if(!EEV.Timer) {
									EEV.Start.PulseRead3 = EEV.Start.StepPulse;// get the pulse to use at third 120 sec
									GetEev_Cycle_Time(7,EEV.Start.PulseRead3); // get 120 1 timeout
								}
				break;
		case EEV_SEC_START2:	if(!EEV.Timer) EEV.CycleMode++;		// 240 total  timeout
				break;
		case EEV_CONST_PREP:
									EEV.Timer = EEV_SAMPLE_TIME;
									EEV.Steady.FinalPulse = EEV.Final.CycleTargetPulse;   // at the end let constant control start with the last one
									EEV.Steady.PreviousFinalPulse = EEV.Steady.FinalPulse ;   // at the end let constant control start with the last one

											// in order to set next PI parameters equal them  we will use same erro loop so dont let the first time to take care ripple
									Motor.Basic.PreviousFrequency = Motor.Basic.Frequency;
									EEV.CycleMode++;
				break;
		case EEV_CONSTANT:
					if(Temperature.Discharge > Temperature.EmergencyDischarge)  { //95C really 950
					//	EEV_Emergency_Open(); // 	this  is cancelled and not being used at LG s code  so disabled
					//	break;
					}
					if(EEV.Timer )break; //wait for 90 sec sampling	 to finalize
					EEV.Timer= EEV_SAMPLE_TIME;
					SuperHeat_Compensation_Check();
					Determine_SuperHeat_Basic_Td();
					Determine_SuperHeat_Final_Td();

					Calculate_EEV_Steady_Initial(); //
					Get_Outdoor_Compensated_Add_Pulse();
					Determine_EEV_Steady_Final();
			break;
		default:
		break;
	}
}
void Calculate_EEV_Start_Initial(void){ // MW_eev_start_base_calc
		unsigned char i;
		float Freq=(float)Motor.Final.TargetFrequency;
		float OutAir= (float)Temperature.OutAir / REALTEMPFACTOR;// /REALTEMPFACTOR
		float InAir= (float)Temperature.InAir / REALTEMPFACTOR ;// /REALTEMPFACTOR
		float Fixed;
	//OutAir /= REALTEMPFACTOR;
	//InAir /= REALTEMPFACTOR;  EEV_Initial_Table
	switch(AirCon.SubMode){
 		case COOL :
 				i = 4;
				if(Temperature.OutAir /REALTEMPFACTOR >=(EEV_Initial_Table[AirCon.Model+(i+1)*MAX_MODEL]))
						OutAir = EEV_Initial_Table[AirCon.Model+i*MAX_MODEL] * (OutAir - (EEV_Initial_Table[AirCon.Model+(i+1)*MAX_MODEL]));
				else    OutAir = EEV_Initial_Table[AirCon.Model+i*MAX_MODEL] * ((EEV_Initial_Table[AirCon.Model+(i+1)*MAX_MODEL] - OutAir) );
				i=0;
		break;
		case HEAT :
				i = 10;
				OutAir = EEV_Initial_Table[AirCon.Model+i*MAX_MODEL] * ((EEV_Initial_Table[AirCon.Model+(i+1)*MAX_MODEL] - OutAir));
				i=6;
			break;
		default: EEV.Start.InitialTd = 0;return;
	}
	Fixed = EEV_Initial_Table[AirCon.Model+i*MAX_MODEL];
	i++;
	Freq *= EEV_Initial_Table[AirCon.Model+i*MAX_MODEL];
	i++;
	InAir = EEV_Initial_Table[AirCon.Model+i*MAX_MODEL]   * (EEV_Initial_Table[AirCon.Model+(i+1)*MAX_MODEL] - InAir) ;

	if ( (Fixed + OutAir + InAir + Freq) < 0) EEV.Start.InitialTd  = 0;
	else  EEV.Start.InitialTd = (unsigned int ) ( Fixed + OutAir + InAir + Freq);
	if (EEV.Start.InitialTd > GetMinMax_Pulse(MAX)) EEV.Start.InitialTd = GetMinMax_Pulse(MAX) ;

	EEV_InitCompensation_Check();
	EEV.Start.FinalTd  = EEV.Start.InitialTd + EEV.Start.TotalCompensation; // comp pas gectik bir onceki fonk a koy
	// check for min max limits
	if ( EEV.Start.FinalTd < 0 ) EEV.Start.FinalTd = 0;
	if (EEV.Start.FinalTd > GetMinMax_Pulse(MAX)) EEV.Start.FinalTd = GetMinMax_Pulse(MAX) ;
	EEV.Start.StepPulse = EEV.Start.FinalTd;
}

//////////////////////////////////////////////////////		SUPERHEAT / TARGET DISCHARGE   FUNCTIONS OF EEV CONTROL ////////////////////////////////////////////////////////////////////////
void Calculate_SuperHeat_Initial_Td(void){  // MW_eev_superheat_base
	unsigned char i;
 	float Freq=(float)Motor.Final.TargetFrequency;
  	float OutMid= (float)Temperature.OutMidPipe;//
  	float InMid= (float)Temperature.InMidPipe;// /
  	float Disch= (float)Temperature.Discharge;// /
  	float OutAir= (float)Temperature.OutAir;// /REALTEMPFACTOR
	float Fixed;
  	OutMid /= REALTEMPFACTOR;
  	InMid /= REALTEMPFACTOR;
  	Disch /= REALTEMPFACTOR;
  	OutAir /= REALTEMPFACTOR;
   	switch(AirCon.SubMode){
   	case COOL : case COOL_DELAY :
   		i= 0;
  		Fixed = S_Heat_Initial_Table[AirCon.Model+i*MAX_MODEL];  // same for coolin & heating
		i++;   								//	1
		Freq = (Freq * S_Heat_Initial_Table[AirCon.Model+i*MAX_MODEL]) + S_Heat_Initial_Table[AirCon.Model+(i+1)*MAX_MODEL]; // does not exist at heating
		i+=2;        						//	3								4
		InMid = S_Heat_Initial_Table[AirCon.Model+i*MAX_MODEL]   *  (S_Heat_Initial_Table[AirCon.Model+(i+1)*MAX_MODEL] -  InMid);// const 2 at heat Outmid
		i+=2;
		OutMid = S_Heat_Initial_Table[AirCon.Model+i*MAX_MODEL]  *  (OutMid- S_Heat_Initial_Table[AirCon.Model+(i+1)*MAX_MODEL]); //const1 different at heat inmid
		i+=2;
		Disch = S_Heat_Initial_Table[AirCon.Model+i*MAX_MODEL]   *  (Disch - OutAir);  // heat and cool same  const 3

   	break;
  	case HEAT :case HEAT_DELAY :
  		i= 8;
  		Fixed = S_Heat_Initial_Table[AirCon.Model+i*MAX_MODEL];  // same for coolin & heating
		i++;        //	9
		//Freq =  S_Heat_Initial_Table[AirCon.Model+i*MAX_MODEL]   *  (Freq - S_Heat_Initial_Table[AirCon.Model+(i+1)*MAX_MODEL]); // does not exist at heating
		Freq = 0;
		i+=2;						//	11								12
		OutMid = S_Heat_Initial_Table[AirCon.Model+i*MAX_MODEL]   *  (S_Heat_Initial_Table[AirCon.Model+(i+1)*MAX_MODEL] -  OutMid);// const 2 at heat Outmid
		i+=2;						// 13								14
		InMid = S_Heat_Initial_Table[AirCon.Model+i*MAX_MODEL]  *  (InMid- S_Heat_Initial_Table[AirCon.Model+(i+1)*MAX_MODEL]); //const1 different at heat inmid
		i+=2;
		Disch = S_Heat_Initial_Table[AirCon.Model+i*MAX_MODEL]   *  (Disch - OutAir);  // heat and cool same  const 3

  	break;
  	default:EEV.SuperHeat.InitialTd = 0; break;// get mantissa neglect exponiental will also get absreturn;
  	}

  	if ( (Fixed + InMid + OutMid + Disch + Freq ) < 0) EEV.SuperHeat.InitialTd   = 0;
	else  EEV.SuperHeat.InitialTd  = (unsigned int ) ( Fixed + InMid + OutMid + Disch + Freq );

}
void Determine_SuperHeat_Basic_Td(void){
	EEV.SuperHeat.BasicTargetTd  = EEV.SuperHeat.InitialTd;
	if((EEV.SuperHeat.BasicTargetTd + EEV.SuperHeat.CompensationTd) < 0) EEV.SuperHeat.BasicTargetTd = 0;  // negative
	else EEV.SuperHeat.BasicTargetTd += (unsigned int)EEV.SuperHeat.CompensationTd;                                     // positive
}

void Determine_SuperHeat_Final_Td(void){
			EEV.SuperHeat.MaxTd = Temperature.EmergencyDischarge/REALTEMPFACTOR - SuperHeatMinMaxCoefficients[1];
			switch(AirCon.SubMode){
						case COOL:
									if((Temperature.OutMidPipe / REALTEMPFACTOR + SuperHeatMinMaxCoefficients[0])<0)EEV.SuperHeat.MinTd  = 0;
									else EEV.SuperHeat.MinTd = Temperature.OutMidPipe / REALTEMPFACTOR + SuperHeatMinMaxCoefficients[0];
						break;
						case HEAT:
									if((Temperature.InMidPipe / REALTEMPFACTOR + SuperHeatMinMaxCoefficients[0])<0)EEV.SuperHeat.MinTd  = 0;
									else EEV.SuperHeat.MinTd = Temperature.InMidPipe / REALTEMPFACTOR + SuperHeatMinMaxCoefficients[0];
						default: break;
			}
		EEV.SuperHeat.FinalTargetTd = EEV.SuperHeat.BasicTargetTd ;
		if((short)EEV.SuperHeat.FinalTargetTd <= EEV.SuperHeat.MinTd) EEV.SuperHeat.FinalTargetTd  = EEV.SuperHeat.MinTd;
		if((short)EEV.SuperHeat.FinalTargetTd >= EEV.SuperHeat.MaxTd) EEV.SuperHeat.FinalTargetTd  = EEV.SuperHeat.MaxTd;
}
///////////////////////////////////////////////////////		STEADY STATE FUNCTIONS OF EEV CONTROL ////////////////////////////////////////////////////////////////////////
void Calculate_EEV_Steady_Initial(void){
		signed char *p;  unsigned char ColumnIndex; unsigned char LineIndex;
		PI.error.SuperHeat = (signed char)(EEV.SuperHeat.FinalTargetTd  - Temperature.Discharge/REALTEMPFACTOR); // target(u char) - current(signed short)
		PI.errord.SuperHeat = PI.error0.SuperHeat - PI.error.SuperHeat;
		p = &FuzzyTable[0] ;
		for (ColumnIndex = 1; ColumnIndex < 15; ColumnIndex++)  {				// 6  is table width 1 is first line
				if (PI.errord.SuperHeat >= p[ColumnIndex]) break;          	// 10 is coefficient to mach table
		}
		 for (LineIndex = 1; LineIndex < 15; LineIndex++){                	//10  is table height 1 is first column
				if (PI.error.SuperHeat >= p[LineIndex * 16]) break;           // 10 is coefficient to match table 6
		}																						// is table width
		EEV.SuperHeat.FuzzyPulse= p[ColumnIndex + LineIndex * 16];          // 6  is table width
		PI.error0.SuperHeat = PI.error.SuperHeat;
}
void Get_Outdoor_Compensated_Add_Pulse(void){
		short Threshold_Temp = -40;
		#if (defined MANAGED_DOTNET_COMPILER || defined MICROCHIP_COMPILER)
				#define COEFFICIENT 0.8f
		#endif
		#if (defined PANASONIC_COMPILER)
				#define COEFFICIENT 1
		#endif
		if(Temperature.OutAir <= -Threshold_Temp) EEV.SuperHeat.CompensationPulse  = (unsigned char)(COEFFICIENT * EEV.SuperHeat.FuzzyPulse);
		if(Temperature.OutAir > -Threshold_Temp)  EEV.SuperHeat.CompensationPulse  =(unsigned char)( COEFFICIENT * EEV.SuperHeat.FuzzyPulse);
 }
void Determine_EEV_Steady_Final(void){
		#if (defined MANAGED_DOTNET_COMPILER || defined MICROCHIP_COMPILER)
				#define COEFFICIENTX 0.9f
		#endif
		#if (defined PANASONIC_COMPILER)
				#define COEFFICIENTX 1
		#endif
		signed char Temp=0;  // EEV.Steady.AdditionalPulse
		PI.error.EEVFrequency = Motor.Basic.Frequency - Motor.Basic.PreviousFrequency;
		PI.error.EEVStartPulse = EEV.Start.FinalTd - EEV.Start.PreviousFinalPulse;
		Temp = EEV.SuperHeat.CompensationPulse;
		if (abs(PI.error.EEVFrequency) >= 10 ) { // error more then 10 check compressor errors
				// here later I have to add one more function to check reliability limits exceeded of 0,6,9,10 :(
				Temp =(signed int)  (COEFFICIENTX * PI.error.EEVStartPulse);
				PI.error.EEVStartPulse2Gain  = (signed char)  (COEFFICIENTX * PI.error.EEVStartPulse);
		 }
		else	PI.error.EEVStartPulse2Gain = 0;
		if (Temp >= 0)	EEV.Steady.FinalPulse = EEV.Steady.PreviousFinalPulse + Temp;
		else{
				if( ((signed int)EEV.Steady.PreviousFinalPulse + Temp)<= 0) EEV.Steady.FinalPulse = 0;
				else							EEV.Steady.FinalPulse = EEV.Steady.PreviousFinalPulse + Temp;
		}
		if( EEV.Steady.FinalPulse > GetMinMax_Pulse(MAX)) EEV.Steady.FinalPulse  = GetMinMax_Pulse(MAX);
		if(EEV.Steady.FinalPulse < GetMinMax_Pulse(MIN)) EEV.Steady.FinalPulse  = GetMinMax_Pulse(MIN);

		EEV.Steady.PreviousFinalPulse       = EEV.Steady.FinalPulse;
		EEV.Start.PreviousFinalPulse        =  EEV.Start.FinalTd;
		Motor.Basic.PreviousFrequency = Motor.Basic.Frequency;
		EEV.Final.CycleTargetPulse = EEV.Steady.FinalPulse ;
}
void EEV_Emergency_Open(void){
	//EEV.Basic.TargetPulse = 0;
	//EEV.Final.TargetPulse 0;
}
unsigned char  EEV_PowerUp(void){
	unsigned char i ;
	if(EEV.EEVPowerupFlag)return ON;
	//close
	for(i=0;  i<10   ; i++  ){
		if(EEV_PowerUp_Table[i*2+1] >= EEV.Powerup) {
			//TimerUc.EEV = 0;
			EEV.Final.CycleTargetPulse = EEV_PowerUp_Table[i*2]*10;
				//return  EEVPowerupFlag;//EEV_PowerUp_Table[11]
						break;
		}
	}
	if(EEV.Powerup > EEV_PowerUp_Table[19] ){
			EEV.EEVPowerupFlag = ON;
			EEV_Stop();
			return ON;
	}
	else return OFF;
}
void EEV_Stop(void){
		EEV.CycleMode  = EEV_STOP;
		EEV.Timer =0;
		EEV.Final.CycleTargetPulse  = 450; // max open leave
}
void 	EEV_Fixed(void){
		EEV.CycleMode = EEV_STOP;	 // set cycle 0 ;
		switch(EEV.FixedMode){
					case EEV_STOP :			         break;
					case EEV_COP:					break;
					case EEV_PREHEAT:				  break;
					case EEV_TEST:					break;
					case EEV_LQC:					break;
					case EEV_DEFROST1:				  break;
					case EEV_DEFROST2:				  break;
					case EEV_DEFROST3:				  break;
					case EEV_DEFROST4:				  break;
					case EEV_DEFROST5:				  break;
					case EEV_DEFROST6:				  break;
					default:						break;
		}
}

void EEV_Defrost(void){
	unsigned int Max;
	unsigned int Min;
//	unsigned int temp;
	Max = GetMinMax_Pulse(MAX);
	Min = GetMinMax_Pulse(MIN);

	switch(AirCon.SubMode){
		case DEFROST_0:
				//	EEV.Defrost.BeforeThrottle = EEV.Final.CycleTargetPulse; //kis // eskiyi kaydet
				//	EEV.Defrost.Throttle = 5 * ( Motor.Final.TargetFrequency / 10) ;
				EEV.Defrost.Throttle = EEV.Final.CycleTargetPulse - (5 * ( Motor.Final.TargetFrequency / 10));
			break;
		case DEFROST_1:
				// at this step compressor frequency is 0
			break;
		case DEFROST_2:
				EEV.Final.CycleTargetPulse = EEV.Defrost.Throttle;
		break;//koru
		case DEFROST_3: break; // koru
		case DEFROST_4: // bekleme acikligi = (kisilan + eskisi)/2  ortala  // lg defrost3_1 adimi
				EEV.Final.CycleTargetPulse = (EEV.Defrost.Throttle + Defrost_TimeComponent[4*DEF_TABLE_WIDTH+2])/2; // OP_defrost_03_eev_pulse ==75*4
			break;
		case DEFROST_5: // eskinin %120 sini uygula   lg defrost3_2 adimi
				//EEV.Final.CycleTargetPulse = EEV.Defrost.BeforeThrottle + ((EEV.Defrost.BeforeThrottle/10)*2);
				EEV.Final.CycleTargetPulse = Defrost_TimeComponent[5*DEF_TABLE_WIDTH+2];
				break;
		case DEFROST_6: break;  // devam
		case DEFROST_7: //  GetMinMax_Pulse(MAX); uygula
				EEV.Final.CycleTargetPulse = Max;
				break;
		case DEFROST_8: // koru cikis zaten
				EEV.CycleMode = EEV_STOP;
		default : break;
	}

	if( EEV.Final.CycleTargetPulse < Min) EEV.Final.CycleTargetPulse = Min;
	if( EEV.Final.CycleTargetPulse > Max) EEV.Final.CycleTargetPulse = Max;
	EEV.CycleMode = EEV_DEFROST ;
}


void EEV_Handle(void){
//	if(EEVPowerupFlag == OFF){EEV_PowerUp();return;}
	if(!EEV_PowerUp())return;
	switch(AirCon.MainMode){
		case StopM: EEV_Stop(); //	EEV.CycleMode = EEV_CONSTANT;EEV.Steady.FinalPulse = 200;EEV.Steady.PreviousFinalPulse = 200; // EEV_Stop();   Test
			break;
		case CycleM:
			break;
		case SeerM:
			break;
		case CopM: 	  EEV.FixedMode = EEV_COP;	EEV_Fixed();
			break;
		case PreheatM:	 EEV.FixedMode = EEV_PREHEAT;		EEV_Fixed();
			break;
		case LqcM:	 EEV.FixedMode = EEV_LQC;		EEV_Fixed();
			break;
		case TestM:  EEV.FixedMode = EEV_TEST;	EEV_Fixed();
			break;
		default:break;
	}
	switch(AirCon.SubMode){
		case STANDBYE : EEV_Stop();
			break;
		case COOL:
		case HEAT:
			if(Motor.Cycle.OperatingMode != COMP_STOP){ // if compressor is on and at the same time eev non operational start it immidiately
				if(Motor.Cycle.OperatingMode >= COMP_FIRST_START2) {
							if( EEV.CycleMode == EEV_STOP)	EEV.CycleMode = EEV_FIRST_START_INIT;
							EEV_Cycle();
				} // if compressor is on do it
			}
			else EEV_Stop();
			break;
			case DEFROST_0:
			case DEFROST_1:
			case DEFROST_2:
			case DEFROST_3:
			case DEFROST_4:
			case DEFROST_5:
			case DEFROST_6:
			case DEFROST_7:
			case DEFROST_8:
				EEV_Defrost();
			break;
		default:break;
	}
}

#ifdef MANAGED_DOTNET_COMPILER
}
#endif
