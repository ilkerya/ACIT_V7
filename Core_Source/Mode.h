
/********************************************************************
 FileName:     	Mode.h
 Processors:		32 bit embedded Micro or 32 bit Windows Running PC
 Complier:  	Microchip PIC32 ; Panasonic MN103S ; .net Framework 3.5 CLI Select only One!!
 Company:	Arcelik-LG Klima AS  http://www.arcelik-lg.com.tr/
 Author :     ilker yagci
File Description:
		Main loop; interrupt timing loop; Indoor & Remote Commands handling; thermal cut functions,
 Change History:
  Rev   Date         Description
  1.0   05.04.2012   Initial release
*********************************************************************/
#ifdef MANAGED_DOTNET_COMPILER
namespace ACIT_Stack{ // additional line for C++ debugging
#endif

void  Preheat_Operation(void){}


		//	Timer.ThermalCut = THCUT_LONG_TIME;

void  Cop_Operation(void){}


unsigned int Check_Input_Voltage_Limits4_COP(void){
	return 0; // fail  input voltage is bad
//	return 1; // succesfull input voltage is ok
}
void Reset_For_Standbye(void){
	Motor.Cycle.OperatingMode = COMP_STOP; // let the motor start from  initialize keep in mind that relevant funtion will be called when it has to so no need to set 0
//	TimerUc.CompressorInitDelay = 0; //   compressor delay
	Fan.TcLatch = OFF;
	//EEV_Stop();
}

void Indoor_Stop_Command(void){
		AirCon.SubModePrevious  = AirCon.SubMode; AirCon.SubMode =  STANDBYE;
		if( AirCon.MainMode == CycleM)AirCon.MainMode =  StopM;
		AirCon.ExtraMode = 0;
}
void AutoChangeSelect(void){
				if((Temperature.InSet - Temperature.InAir  -  Auto_Compensation_Table[0]) <= 0) {
						 AirCon.SubModePrevious  = AirCon.SubMode;AirCon.SubMode =  COOL_DELAY;	AirCon.MainMode =   CycleM;
						  Auto_Correction = Auto_Compensation_Table[0] ;
				}
				else {
					if((Temperature.InAir - Temperature.InSet  +  Auto_Compensation_Table[1]) <= 0) {
						 AirCon.SubModePrevious  = AirCon.SubMode;AirCon.SubMode =  HEAT_DELAY;	AirCon.MainMode =   CycleM;
						  Auto_Correction = Auto_Compensation_Table[1] ;
					}
					//else AirCon.SubMode = STANDBYE;
				}
}
void SubCheckIndoor(void){
	switch( IndoorCommand.Mode.Case){
		case REMOTE_OFF :		Indoor_Stop_Command();break;
		case REMOTE_COOL :	 AirCon.SubModePrevious  = AirCon.SubMode; AirCon.SubMode = COOL_DELAY;  AirCon.MainMode =   CycleM;
					AirCon.ExtraMode = 0;
		 		break;
		case REMOTE_AUTOCHNG:// AirCon.SubModePrevious  = AirCon.SubMode; AirCon.MainMode =   CycleM;
			// cooling
		/*	if(AirCon.SubMode != COOL_DELAY ){
				if(AirCon.SubMode != COOL )
					AirCon.SubMode =  COOL_DELAY;
					AirCon.ExtraMode = AUTOCHNG_COOL;
			}
		*/	AirCon.ExtraMode = AUTOCHNG_COOL;
			// heating
		//	AirCon.ExtraMode = AUTOCHNG_HEAT; AirCon.SubMode =  HEAT_DELAY;
		break;
 		case REMOTE_DEHUMIDIF://  AirCon.SubModePrevious  = AirCon.SubMode;AirCon.SubMode =  COOL_DELAY;	AirCon.MainMode =   CycleM;
								AirCon.ExtraMode = AUTOCHNG_DEHUM;
 					break;
 		case REMOTE_HEAT:		AirCon.SubModePrevious  = AirCon.SubMode;AirCon.SubMode =  HEAT_DELAY;  AirCon.MainMode =   CycleM;
								AirCon.ExtraMode = 0;
 				break;
 		case REMOTE_FAN_SPEED:  AirCon.SubModePrevious  = AirCon.SubMode; AirCon.SubMode = STANDBYE;    AirCon.MainMode =   CycleM; AirCon.ExtraMode = 0;
		default : break;
	}
}
void Check_Indoor_Commands(void){
		/* if(IndoorCommand.Mode.Case == REMOTE_AUTOCHNG){
			switch(AirCon.SubMode){
				case COOL_DELAY: case COOL:
							Auto_Correction = Auto_Compensation_Table[0];
						break;
				case HEAT_DELAY:case HEAT:case DEFROST_0: case DEFROST_1: case DEFROST_2:case DEFROST_3:
								case DEFROST_4:case DEFROST_5:case DEFROST_6:case DEFROST_7:case DEFROST_8:
							Auto_Correction = Auto_Compensation_Table[1];
						break;
				default:  Auto_Correction = 0;
			}
			//AutoChangeSelect();
			return;
		}
		*/
		switch(AirCon.SubMode){
			case STANDBYE:	SubCheckIndoor();
					break;
			case COOL_DELAY: 	if ( IndoorCommand.Mode.Case != REMOTE_COOL) SubCheckIndoor();
					break;
			case HEAT_DELAY: 	if ( IndoorCommand.Mode.Case != REMOTE_HEAT) SubCheckIndoor();
				break;
			case COOL:			if ( IndoorCommand.Mode.Case != REMOTE_COOL) SubCheckIndoor();
					break;
			case HEAT:			if ( IndoorCommand.Mode.Case != REMOTE_HEAT) SubCheckIndoor();
					break;
			case DEFROST_0: case DEFROST_1: case DEFROST_2:case DEFROST_3:case DEFROST_4:case DEFROST_5:case DEFROST_6:case DEFROST_7:case DEFROST_8:
					if ( IndoorCommand.Mode.Case != REMOTE_HEAT) SubCheckIndoor();
			default:break;
		}
}

void Mode_Handle(void){ // decision of modes stop/heat/cool/ defost..  cycle/seer/copp/oilsupply/test/lqc  .....//  Function or code
	// AirCon.SubModePrevious   = AirCon.SubMode;  // 17.3.2013
	// check for any mode change by user
	if (AirCon.MainModePrevious   != AirCon.MainMode){ // some change
				Reset_For_Standbye();
	}
	switch(AirCon.MainMode){
			case StopM:	 AirCon.SubMode = STANDBYE;  Check_Indoor_Commands();
					break;
		case CycleM:    Check_Indoor_Commands();
					break;
		case SeerM:	   Check_Indoor_Commands();
					break;
		case CopM: 		Cop_Operation();			// will enter by outdoor decision
					break;
		case PreheatM:  Preheat_Operation();AirCon.SubMode = STANDBYE; Check_Indoor_Commands();
					break;
		case LqcM:	AirCon.SubMode = STANDBYE;
					break;
		case TestM: AirCon.SubMode = STANDBYE;
					break;
		default:break;
	}
	switch(AirCon.SubMode){
		case STANDBYE :   Reset_For_Standbye();				// will enter by indoor command	/ any error /
			break;
		case COOL:  //AirCon.PressureEqual = COOL;
					switch(AirCon.MainMode){
						case CycleM:
						case SeerM:
						case CopM:
						default:break;
				}
			break;
		case HEAT://AirCon.PressureEqual = HEAT;
	//			if(AirCon.DelayMode == StandbyeM)break;// on delay not the time to work
					switch(AirCon.MainMode){
						case CycleM:
						break;
						case SeerM:
						case CopM:
						break;
				}
			break;
		case COOL_DELAY:  break;
		case HEAT_DELAY:  break;

		case DEFROST_0: case DEFROST_1: case DEFROST_2:case DEFROST_3:case DEFROST_4:case DEFROST_5:case DEFROST_6:case DEFROST_7:case DEFROST_8:
		default:break;
	}
	AirCon.MainModePrevious = AirCon.MainMode;
	//AirCon.SubModePrevious   = AirCon.SubMode;
}
void Decision_Handle(void){ // decision of modes stop/heat/cool/ defost..  cycle/seer/copp/oilsupply/test/lqc  .....//  Function or code
	switch(AirCon.MainMode){
		case StopM:	 //Preheat_Decision();
			break;
		case CycleM:
		case SeerM:
		case CopM:
		case PreheatM:
		case LqcM:
		case TestM:
		default:break;
	}
	switch(AirCon.SubMode){
		case STANDBYE :
			break;
		case COOL:
				switch(AirCon.MainMode){
					case CycleM:  Cop_Decision();break;
					case SeerM:
					case CopM:
						default:break;
				}
			break;
		case HEAT:
				switch(AirCon.MainMode){
						case CycleM:  Cop_Decision(); Defrost_Decision();break;
						case SeerM:	//SeerDefrost_Decision();break;
						case CopM:
						break;
				}
			break;
			case DEFROST_0: case DEFROST_1: case DEFROST_2:case DEFROST_3:case DEFROST_4:case DEFROST_5:case DEFROST_6:case DEFROST_7:case DEFROST_8:
		default:break;
	}
}




void Thermal_Cut_Disable(void){
		IndoorCommand.ThermalCut.TimerShort = ThermalCut_Table[1]*10; // 10 sec
		IndoorCommand.ThermalCut.TimerLong = ThermalCut_Table[3]*10;  //180 sec
			switch(AirCon.SubMode){
				case COOL_DELAY:  break;
				case HEAT_DELAY:  break;
				default :IndoorCommand.ThermalCut.On = OFF;break;
			}
}

void Thermal_Cut_Check(void){
	//	if(PI.error.CompStep < ThermalCut_Table[0]) {    // -5  -0.5 error  //   10 sec  error 0.5 alti ise yavasca kapat daha uzun timer
			if(PI.error.CompStep > (-1 * ThermalCut_Table[0])) IndoorCommand.ThermalCut.TimerShort = ThermalCut_Table[1]*10;
	//	}

	//	if(PI.error.CompStep < ThermalCut_Table[2]) {    // -20  -2 error // error coksa -2 alti ise hizli timer ile hizlica kapat
			if(PI.error.CompStep > (-1 * ThermalCut_Table[2])) 	IndoorCommand.ThermalCut.TimerLong = ThermalCut_Table[3]*10;//TimerShort
			//else IndoorCommand.ThermalCut.TimerShort = 0;
	//	}

	//	if( Motor.Cycle.OperatingMode == COMP_PI_MODE){
				if(!IndoorCommand.ThermalCut.TimerLong) if(IndoorCommand.ThermalCut.EnableLong) IndoorCommand.ThermalCut.On = ON;else IndoorCommand.ThermalCut.On = OFF;
				if(!IndoorCommand.ThermalCut.TimerShort) if(IndoorCommand.ThermalCut.EnableShort) IndoorCommand.ThermalCut.On = ON;else IndoorCommand.ThermalCut.On = OFF;
	//	}
	//	else{
	//		TimerUc.ThermalShortCut = ThermalCut_Table[1]*10;
	//		TimerUc.ThermalLongCut = ThermalCut_Table[3]*10;
	//	}

		if(IndoorCommand.ThermalCut.On){
			EEV_Stop();
			switch(AirCon.SubMode){
				case COOL: AirCon.SubMode = COOL_DELAY; AirCon.Timer.CoolDelay = 180; break;
				case HEAT: AirCon.SubMode = HEAT_DELAY; AirCon.Timer.HeatDelay = 180; break;
				default :break;
			}
		}
}
void  Defrost_Start(void){
	// startup load from configuration table to struct
	struct Defrost_Handle *p;  unsigned char j;
	for( j=0; j<5; j++){
		switch(j){
			case 0: p = &Defrost8111;	break;
			case 1: p = &Defrost8112;	break;
			case 2: p = &Defrost8113_1;	break;
			case 3: p = &Defrost8113_2;	break;
			case 4: p = &Defrost8114;	;break;
		}
//		if(Defrost_Decision_Configuration_Table[j+5]) p->Enabled = ON; else p->Enabled = OFF; //GUI ile elle yapiyoruz
	}
	p->MainCounter = Const_Defrost_Table[j*2+1];
	p->MaintenanceCounter = Const_Defrost_Table[j*2];
	Defrost_Average.Counter = 300;
}


void ACIT_Main_Initialize(void){
		unsigned char  i = 0;
		Reliability_Fill_Default();
		Defrost_Start();

		Motor.Timer.TotOpTime = 0;
//		AirCon.Timer.Delay3Min = QUICKSTART_DELAY;

		EEV.SuperHeat.SampleTime = 4;
		EEV.Final.CycleTargetPulse = 0;
		EEV.EEVPowerupFlag = OFF;
		Temperature.EmergencyDischarge = 950; // 95C
		AirCon.MainMode = StopM;
		AirCon.SubMode = STANDBYE;
		AirCon.SubModePrevious = STANDBYE;
		Motor.Cycle.OperatingMode = COMP_STOP;
		EEV.CycleMode =  EEV_STOP;
		EEV.FixedMode = EEV_STOP;

		AirCon.Timer.HeatDelay = QUICKSTART_DELAY;
		AirCon.Timer.CoolDelay = QUICKSTART_DELAY;

//		IndoorCommand.FanRate = INDOOR_DEFAULT_FAN_RATE;  // default
		EEV.Powerup = 0;
		EEV.Timer = 0;
		Motor.Basic.Frequency = 0;
		AirCon.Model = 4;
		Fan.Indoor.HotStart = 0;
		Fan.ManuelMode = FANRPM_AUTO; // As auto
		// enable reliability functions
		for(i =0; i<14;i++){
				Reliability.PowUpMaxEnable[i] =ON;
		}
		for(i =0; i<2;i++){
				Reliability.PowUpMinEnable[i] =ON;
		}


		// default fan rates
		IndoorCommand.FanRate.Plasma = INDOOR_FANRATE_1;
		IndoorCommand.FanRate.Cool = INDOOR_FANRATE_5;
		IndoorCommand.FanRate.Auto = INDOOR_FANRATE_5;
		IndoorCommand.FanRate.DeHum = INDOOR_FANRATE_1;
		IndoorCommand.FanRate.Heat  = INDOOR_FANRATE_5;
		IndoorCommand.FanRate.FanMode = INDOOR_FANRATE_5;
		IndoorCommand.FanRate.Final = IndoorCommand.FanRate.FanMode;

	//	MemoryMap.Struct1 = &PI.StartAdress;
		//MemoryMap.Struct1 = &PI;
	//	offsetof(struct  Temperature, OutAir);
}
void ACIT_Main_Loop(void){
		EEV_Handle();            // Find EEV Pulse according to cycle mode and target and actual motor frequency
		Mode_Handle();
		Decision_Handle();
		Compressor_Handle();
		Indoor_Comand_Execute();
		Fan_Handle();
		Relay_Handle();
		MemoryMap_Update();
		Update_Compiler_Info();
		Error_Handle();
}

void ACIT_Interrupt_Time(void){    // 1 sec interval
//		unsigned char i;
	if(AirCon.Timer.COP < 65535)AirCon.Timer.COP++;                     // COP MODE decision
	if(AirCon.Timer.Preheat < 65535)AirCon.Timer.Preheat++;         // Preheat
  	if(TimerUc.Condenser_DisError < 65535)TimerUc.Condenser_DisError++;         //
	if(Fan.Timer)Fan.Timer--;
	if(Fan.SoftStopTimer)Fan.SoftStopTimer--; //Fan.SoftStopTimer--;
		// Timer Template For Total Heating Timer ////////////
	switch(AirCon.MainMode){
		case StopM:		AirCon.Timer.TotalHeating=0; //AirCon.Timer.Delay3Min = START_DELAY;
			break;
		case CycleM:   //do not modify TotalHeating
			break;
		case SeerM:	   //do not modify TotalHeating
			break;
		case CopM: 	    //Timer.TotalHeating do not modify
		case PreheatM:
		case LqcM:
		case TestM:		AirCon.Timer.TotalHeating=0;
			break;
		default:break;
	}



	switch(AirCon.SubMode){
		case STANDBYE :        AirCon.Timer.Defrost = 0; //AirCon.Timer.Delay3Min = START_DELAY;
					//			if(AirCon.Timer.Delay3Min > FASTSTART_DELAY)AirCon.Timer.Delay3Min--;         //  break; //18.03.2013
					//			else {    }
								if(AirCon.Timer.HeatDelay> FASTSTART_DELAY)AirCon.Timer.HeatDelay--;         //  break;
								if(AirCon.Timer.CoolDelay> FASTSTART_DELAY)AirCon.Timer.CoolDelay--;         //  break;
								AirCon.Timer.TotalHeating = 0;

						break;
		case COOL:	AirCon.Timer.Defrost = 0;	AirCon.Timer.TotalHeating=0; /* AirCon.Timer.Delay3Min = START_DELAY; */Cycle_Timers();
					AirCon.Timer.HeatDelay = START_DELAY;
					AirCon.Timer.CoolDelay = QUICKSTART_DELAY;
						break;
		case HEAT:	if(AirCon.AuxiliaryFunction != OilSupplyM)	AirCon.Timer.TotalHeating++; // at oilsupply neglect or not???
										Defrost_AverageTemp_Conversion(); /* AirCon.Timer.Delay3Min = START_DELAY; */ Cycle_Timers(); // QUICKSTART_DELAY
										AirCon.Timer.Defrost = 0;
										AirCon.Timer.CoolDelay = START_DELAY;
										AirCon.Timer.HeatDelay = QUICKSTART_DELAY;

						break;
		case COOL_DELAY:  	AirCon.Timer.Defrost = 0;AirCon.Timer.TotalHeating=0;
										//if(AirCon.Timer.Delay3Min)AirCon.Timer.Delay3Min--;         //  break;
										//else {  AirCon.SubModePrevious   = AirCon.SubMode; AirCon.SubMode = COOL;  }
										if(AirCon.Timer.HeatDelay > QUICKSTART_DELAY )AirCon.Timer.HeatDelay--;

										if(AirCon.Timer.CoolDelay)AirCon.Timer.CoolDelay--;
										else {  AirCon.SubModePrevious   = AirCon.SubMode; AirCon.SubMode = COOL;  }
							//			AirCon.Timer.Delay3Min = AirCon.Timer.CoolDelay; //18.03.2013

							break;
		case HEAT_DELAY:
										//if(AirCon.Timer.Delay3Min)AirCon.Timer.Delay3Min--;         //  break;
										//else  {  AirCon.SubModePrevious   = AirCon.SubMode;  AirCon.SubMode = HEAT;}
										if(AirCon.Timer.CoolDelay > QUICKSTART_DELAY )AirCon.Timer.CoolDelay--;

										if(AirCon.Timer.HeatDelay)AirCon.Timer.HeatDelay--;
										else  {  AirCon.SubModePrevious   = AirCon.SubMode;  AirCon.SubMode = HEAT;}
								//		AirCon.Timer.Delay3Min = AirCon.Timer.HeatDelay; //18.03.2013

							break;
		case DEFROST_0: case DEFROST_1: case DEFROST_2:case DEFROST_3:case DEFROST_4:case DEFROST_5:case DEFROST_6:case DEFROST_7:case DEFROST_8:
			Defrost_Operation_Handle();AirCon.Timer.TotalHeating=0;
							//AirCon.Timer.Delay3Min = QUICKSTART_DELAY;  //17.03.2013
									AirCon.Timer.TotalHeating=0;
									if(AirCon.Timer.Defrost)AirCon.Timer.Defrost--;	//if(TimerUc.Defrost < 65535)TimerUc.Defrost++; //          // DEFROST MODE  timer
									if(AirCon.Timer.Defrost == 0){
											AirCon.SubModePrevious = AirCon.SubMode; // store existing mode as previous
											AirCon.SubMode++; // switch to  next step
									}

							//		Defrost_SensorEscape_Time_Handle();
							//		Defrost_Operation_Handle();
							//		Def_Escape_RemainAdd();
					//		break;
		//case DEFROST_6:
				//AirCon.SubModePrevious = AirCon.SubMode; // store existing mode as previous means defost end
				//AirCon.SubMode = HEAT; // return to heating
				//Motor.Cycle.OperatingMode = COMP_FIRST_START1_INIT; // let the motor initialize
			break;
		default:break;
	}
	if(IndoorCommand.RoomTemp.On){
		if(IndoorCommand.RoomTemp.Timer)IndoorCommand.RoomTemp.Timer--;
		else {
			IndoorCommand.RoomTemp.On = OFF;
			IndoorCommand.RoomTemp.GUI = ON;

			IndoorCommand.RoomTemp.Timer = ROOM_TEMPERATURE_TIMER;
		}		//IndoorCommand.RoomTemp.GUI = ON;
	}
}
void Cycle_Timers (void){
	unsigned char i;
	struct Defrost_Handle *p;
	// COMPRESSOR  START & REGULAR MODES TIMING //////

	if(Motor.Timer.Step)Motor.Timer.Step --;
	if(Motor.Timer.TotOpTime < 60000)Motor.Timer.TotOpTime++;         //
	if(Motor.Timer.FFT) Motor.Timer.FFT--;					//// CYCLE HEAT/COOL MODE
	if(Motor.Cycle.OperatingMode == COMP_PI_MODE) if(Motor.Timer.OilSupply)Motor.Timer.OilSupply--;         // OIL SUPPLY MODE decision

	if(EEV.Timer)EEV.Timer --;

	if(IndoorCommand.ThermalCut.TimerLong)IndoorCommand.ThermalCut.TimerLong--;
	if(IndoorCommand.ThermalCut.TimerShort)IndoorCommand.ThermalCut.TimerShort--;


/*
						if(IndoorCommand.GUIHelp.OnOffTimer) IndoorCommand.GUIHelp.OnOffTimer --;
						else{
								if(IndoorCommand.GUIHelp.OnOffFlash){
								   IndoorCommand.GUIHelp.OnOffFlash--;
								   IndoorCommand.GUIHelp.OnOffTimer= 3;
								   IndoorCommand.Mode.GUI = true;
								}
						}
*/
/*
		if(IndoorCommand.GUIHelp.RemotePressTimer){
			IndoorCommand.GUIHelp.RemotePressTimer--;


		}
		else {
			IndoorCommand.Mode.GUI = true;
			IndoorCommand.GUIHelp.RemotePressed= OFF;
		}
	*/

	//	if(IndoorCommand.GUIHelp.OnOffTimer == 1)  IndoorCommand.Mode.GUI = true;


	// GROUP1 BELOW TIMERS CAN BE SAME BECAUSE THEY ARE USED AT DIFFERENT MODES !  ////// LEAVE AS IT IS FOR DEBUGGING PC MODE

	if(TimerUc.DewReliability < 65535)TimerUc.DewReliability++;         //
	// GROUP2 BELOW TIMERS CAN BE SAME BECAUSE THEY ARE USED AT DIFFERENT MODES !  ///// LEAVE AS IT IS FOR DEBUGGING PC MODE




	if(TimerUc.InpVoltage)	TimerUc.InpVoltage--;
//	if(TimerUc.CompressorInitDelay < 65535)TimerUc.CompressorInitDelay++;         //
		// Reliability Function check timers
	if(Td_Hold.Counter) Td_Hold.Counter--;
	if(Te_Hold.Counter) Te_Hold.Counter--;
	if(Tc_Hold.Counter) Tc_Hold.Counter--;
	if(Dew_Hold.Counter) Dew_Hold.Counter--;
	if(HS.Counter < 255)       HS.Counter++;
		// defrost timing
	if (AirCon.Timer.TotalHeating >= 900){
		for( i=0; i< 5;i++){
				switch(i){
						case 0 : p = &Defrost8111;break;
						case 1 : p = &Defrost8112;break;
						case 2 : p = &Defrost8113_1;break;
						case 3 : p = &Defrost8113_2;break;
						case 4 : p = &Defrost8114;break;
				}
				if(AirCon.SubMode == HEAT ){ // gerkesiz baska durum yok zati
						if(p->MainCounter)p->MainCounter--;
						else {
								if(p->MaintenanceCounter)p->MaintenanceCounter--;
						}
				}
				else { // load default values if not at heating
					p->MainCounter = Const_Defrost_Table[i*2+1];
					p->MaintenanceCounter = Const_Defrost_Table[i*2];
					Defrost_Average.Counter = 300;
					if(p== &Defrost8114)	if(p->Line1 == 1)p->MainCounter =  Const_Defrost_Table[11]; // exception load timer
				}
		}
		if( AirCon.SubMode == HEAT) {
				if(Defrost_Average.Counter)Defrost_Average.Counter--;    	// timer for defrost average call every 1 second
				else Defrost_Average.Counter=300;
		}
	}
	else {
				AirCon.Timer.Defrost  = 0;            // as well as defrost timer
				Defrost_Average.Counter = 0;
				Defrost_Average.Sample = 0;
				Defrost_Average.OutAirTemp = 0;
				Defrost_Average.OutMidAirTemp = 0;
				Defrost_Average.AverageOutAir = 0;
				Defrost_Average.AverageMidPipe = 0;
				Defrost_Average.AvConversionDone = OFF;
				//Clear_Def_Decision_Datas();
				/*
				for( i=0; i< 5;i++){
					p->MainCounter = Const_Defrost_Table[i*2+1];
					p->MaintenanceCounter = Const_Defrost_Table[i*2];
					Defrost_Average.Counter = 300;
					if(p== &Defrost8114)	if(p->Line1 == 1)p->MainCounter =  Const_Defrost_Table[11]; // exception load timer
				}
				*/
				Defrost_Average.Counter = 300;


	}
}

#define COOLING_MINSET  18
#define COOLING_HIGHSET  30
#define HEATING_MINSET  16
#define HEATING_HIGHSET  30
#define AUTOCHNGE_MINSET  16
#define AUTOCHNGE_HIGHSET  30

void Indoor_Mode_SwingDikey(void){
	if(IndoorCommand.SwingDikey.Enabled == OFF)return;
	IndoorCommand.SwingDikey.Enabled = OFF;

	if(IndoorCommand.Mode.Case == REMOTE_OFF){
		if(IndoorCommand.Plasma.On == OFF) return;
	}
	IndoorCommand.SwingDikey.Mode++;
	if(IndoorCommand.SwingDikey.Mode > 8) IndoorCommand.SwingDikey.Mode = 0;
	IndoorCommand.SwingDikey.GUI = ON;
}
void Indoor_Mode_SwingYatay(void){
	if(IndoorCommand.SwingYatay.Enabled == OFF)return;
	IndoorCommand.SwingYatay.Enabled = OFF;

	if(IndoorCommand.Mode.Case == REMOTE_OFF){
		if(IndoorCommand.Plasma.On == OFF) return;
	}
	IndoorCommand.SwingYatay.Mode++;
	if(IndoorCommand.SwingYatay.Mode > 7) IndoorCommand.SwingYatay.Mode = 0;
	IndoorCommand.SwingYatay.GUI = ON;
}
void Indoor_Mode_SwingCheck(void){
	if(IndoorCommand.Mode.Case != REMOTE_OFF){
		IndoorCommand.SwingYatay.On = ON;
		IndoorCommand.SwingDikey.On = ON;
		return;
	}
	if(IndoorCommand.Plasma.On != ON){
			IndoorCommand.SwingYatay.On = OFF;
			IndoorCommand.SwingDikey.On = OFF;
			return;
	}
	IndoorCommand.SwingYatay.On = ON;
	IndoorCommand.SwingDikey.On = ON;
}


void Indoor_Mode_UpButton(void){
	if(IndoorCommand.UpButton.Enabled == OFF)return;
	IndoorCommand.UpButton.Enabled = OFF;

	if(IndoorCommand.Mode.Case ==  REMOTE_OFF)  return;
		if(IndoorCommand.Jet.On == ON){
			IndoorCommand.Jet.On = OFF;
			return;
		}
	if(IndoorCommand.RoomTemp.On){
			IndoorCommand.RoomTemp.On = OFF;
			IndoorCommand.Mode.GUI = ON;
			IndoorCommand.RoomTemp.GUI = ON;
			return;
	}
	switch(IndoorCommand.Mode.Case){
			case REMOTE_COOL : IndoorCommand.SetTemperature_Cooling++;
						break;
			case REMOTE_HEAT : IndoorCommand.SetTemperature_Heating++;
					 break;
			case REMOTE_AUTOCHNG: IndoorCommand.SetTemperature_Auto++;
			default:break;
	}
	IndoorCommand.UpButton.GUI = ON;
}


void Indoor_Mode_DownButton(void){
	if(IndoorCommand.DownButton.Enabled == OFF)return;
	IndoorCommand.DownButton.Enabled = OFF;


	if(IndoorCommand.Mode.Case ==  REMOTE_OFF)  return;
	if(IndoorCommand.Jet.On == ON){
		IndoorCommand.Jet.On = OFF;
		return;
	}
	if(IndoorCommand.RoomTemp.On){
		IndoorCommand.RoomTemp.On = OFF;
		IndoorCommand.Mode.GUI = ON;
		IndoorCommand.RoomTemp.GUI = ON;
		//IndoorCommand.DownButton.GUI = ON;
		return;
	}
	switch(IndoorCommand.Mode.Case){
		case REMOTE_COOL : IndoorCommand.SetTemperature_Cooling--;
					break;
		case REMOTE_HEAT : IndoorCommand.SetTemperature_Heating--;
				 break;
 			case REMOTE_AUTOCHNG: IndoorCommand.SetTemperature_Auto--;
		default:break;
	}

	IndoorCommand.DownButton.GUI = ON;
}



void Indoor_Mode_ESaving(void){
	if(IndoorCommand.ESaving.Enabled == OFF)return;
	IndoorCommand.ESaving.Enabled = OFF;

	switch(IndoorCommand.Mode.Case){
			case REMOTE_OFF:


			break;
			case REMOTE_AUTOCHNG:case REMOTE_FAN_SPEED:		case REMOTE_COOL : case REMOTE_DEHUMIDIF :case REMOTE_HEAT :
					IndoorCommand.ESaving.On = !IndoorCommand.ESaving.On;
				 break;
			 default:break;
	}
	IndoorCommand.ESaving.GUI = ON;
}
void Indoor_Mode_AClean(void){
	if(IndoorCommand.AClean.Enabled == OFF)return;
	IndoorCommand.AClean.Enabled = OFF;
	IndoorCommand.AClean.On = !IndoorCommand.AClean.On;
	IndoorCommand.AClean.GUI = ON;
}
void Indoor_Mode_RoomTempShow(void){
	if(IndoorCommand.RoomTemp.Enabled == OFF)return;
	IndoorCommand.RoomTemp.Enabled = OFF;
	IndoorCommand.RoomTemp.Timer = ROOM_TEMPERATURE_TIMER;
	IndoorCommand.RoomTemp.On = ON;
	IndoorCommand.RoomTemp.GUI = ON;
}

void Indoor_Mode_Jet(void){
	if(IndoorCommand.Jet.Enabled == OFF)return;
	IndoorCommand.Jet.Enabled = OFF;
	if(!IndoorCommand.Jet.On){
		switch(IndoorCommand.Mode.Case){
			case REMOTE_OFF:case REMOTE_AUTOCHNG:case REMOTE_FAN_SPEED:
						//IndoorCommand.Jet.On = OFF;
					break;
			case REMOTE_DEHUMIDIF :
					// sonra burayi on yapmak ve ardindan sogutmata almak gerek henuz kodu bilmiyorum
				break;

			 case REMOTE_COOL :
					 IndoorCommand.SetTemperature_Cooling = COOLING_MINSET;
					 IndoorCommand.FanRate.Cool = INDOOR_FANRATE_5;
					 IndoorCommand.Jet.On = ON;
					 IndoorCommand.SwingYatay.Jet = IndoorCommand.SwingYatay.Mode;
					 IndoorCommand.SwingYatay.Mode = 0;
					 Indoor_Mode_SwingCheck();
					 IndoorCommand.SwingYatay.GUI = ON;
					break;
			case REMOTE_HEAT :
					 	IndoorCommand.SetTemperature_Heating = HEATING_HIGHSET;
					 IndoorCommand.FanRate.Heat = INDOOR_FANRATE_5;
					 IndoorCommand.Jet.On = ON;
					 IndoorCommand.SwingYatay.Jet = IndoorCommand.SwingYatay.Mode;
					 IndoorCommand.SwingYatay.Mode = 0;
					 Indoor_Mode_SwingCheck();
					 IndoorCommand.SwingYatay.GUI = ON;
				 break;
			 default:break;
		}
	}
	else  IndoorCommand.Jet.On = OFF;
	IndoorCommand.Jet.GUI = ON;
}

void Indoor_Mode_Set(void){
	if(IndoorCommand.Mode.Enabled == OFF)return;
	IndoorCommand.Mode.Enabled = OFF;
	if(IndoorCommand.RoomTemp.On){
		IndoorCommand.RoomTemp.On = OFF;
		IndoorCommand.Mode.GUI = ON;
		IndoorCommand.RoomTemp.GUI = ON;
		return;
	}
	IndoorCommand.Jet.On = OFF;
	if(IndoorCommand.Plasma.On == ON)  {
			if(IndoorCommand.Mode.OnOff == OFF) {
				IndoorCommand.Mode.OnOff = ON;
			//IndoorCommand.Plasma.On = OFF;
	//		IndoorCommand.Mode.OnOff_Enabled  = ON; // trig on of button
			IndoorCommand.Mode.GUI = ON;
					if (IndoorCommand.Mode.PrevCase) IndoorCommand.Mode.Case = IndoorCommand.Mode.PrevCase; // if prev not stop then load prev one
				  else IndoorCommand.Mode.Case = REMOTE_COOL ; // default one if started from
			return;
		}
	}
	if( IndoorCommand.Mode.Case){
		IndoorCommand.Mode.Case++;
		if( IndoorCommand.Mode.Case > REMOTE_FAN_SPEED) IndoorCommand.Mode.Case = REMOTE_COOL;
		IndoorCommand.Mode.PrevCase = IndoorCommand.Mode.Case; // store previous
	}
	if( IndoorCommand.SwingYatay.Mode  != 7) IndoorCommand.SwingYatay.Mode = 0;
	IndoorCommand.SwingYatay.GUI = ON;
	IndoorCommand.Mode.GUI = ON;
	IndoorCommand.RoomTemp.GUI = ON;
	IndoorCommand.ESaving.GUI = ON;
}


void Indoor_Onff_Set(void){
	if(IndoorCommand.Mode.OnOff_Enabled == OFF)return;
	IndoorCommand.Mode.OnOff_Enabled  = OFF;
	IndoorCommand.Jet.On = OFF;

	IndoorCommand.ESaving.On = OFF;

	//IndoorCommand.RoomTemp.Timer = OFF;
	IndoorCommand.RoomTemp.On = OFF;
	// IndoorCommand.RoomTemp.GUI = ON;




	if (IndoorCommand.Plasma.On == ON){// plasma aciksa
		IndoorCommand.FanRate.Plasma = INDOOR_FANRATE_1;
		IndoorCommand.Plasma.GUI = true;
		IndoorCommand.Plasma.On = OFF; // kapaniyorsa palzmayida kapa
			Indoor_Mode_SwingCheck();
			IndoorCommand.SwingYatay.GUI = ON;
			IndoorCommand.SwingDikey.GUI = ON;
		if(IndoorCommand.Mode.OnOff){
			//IndoorCommand.Plasma.On = OFF; // kapaniyorsa palzmayida kapa
		}
		else{
			//IndoorCommand.Plasma.On = OFF; // aciliyorsa plazmayi kapa ve acilisi bir sonraki tusa birak ertele
			return;
		}
	}

	IndoorCommand.Mode.OnOff =! IndoorCommand.Mode.OnOff;





	if( IndoorCommand.Mode.Case) { // set to stop if any other selected
		IndoorCommand.Mode.PrevCase = IndoorCommand.Mode.Case; // store previous
		IndoorCommand.Mode.Case = REMOTE_OFF;
		IndoorCommand.Plasma.On = OFF;
		//this->pictureBox_Remote_AmbTemp->Visible = false;
	}
	else {
		//this->pictureBox_Remote_AmbTemp->Visible = true;
		if (IndoorCommand.Mode.PrevCase) IndoorCommand.Mode.Case = IndoorCommand.Mode.PrevCase; // if prev not stop then load prev one
		else  IndoorCommand.Mode.Case = REMOTE_COOL ; // default one if started from

	}
	Indoor_Mode_SwingCheck();
	IndoorCommand.SwingYatay.GUI = ON;
	IndoorCommand.SwingDikey.GUI = ON;

	IndoorCommand.Mode.GUI = ON;
	IndoorCommand.RoomTemp.GUI = ON;
	IndoorCommand.ESaving.GUI = ON;

 }

void IndoorFanUpdate(void){

	if(IndoorCommand.FanRate.Enabled == OFF)return;
	IndoorCommand.FanRate.Enabled = OFF;
		// fan speed tusuna bir kere basildiginda bir kere cagir yeter
		switch(IndoorCommand.Mode.Case){
			case REMOTE_OFF:
				if (IndoorCommand.Plasma.On){
					IndoorCommand.FanRate.Plasma++;
					if( IndoorCommand.FanRate.Plasma > INDOOR_FANRATE_SWING) IndoorCommand.FanRate.Plasma = INDOOR_FANRATE_1;
				}
				else 	IndoorCommand.FanRate.Final = INDOOR_FANRATE_0 ;
				break;
			 case REMOTE_COOL :
					IndoorCommand.FanRate.Cool++;
					if( IndoorCommand.FanRate.Cool > INDOOR_FANRATE_SWING) IndoorCommand.FanRate.Cool = INDOOR_FANRATE_1;
				break;
 		 	case REMOTE_AUTOCHNG:
						IndoorCommand.FanRate.Auto++;
					if( IndoorCommand.FanRate.Auto > INDOOR_FANRATE_SWING) IndoorCommand.FanRate.Auto = INDOOR_FANRATE_1;
				break;
			case REMOTE_DEHUMIDIF :
						IndoorCommand.FanRate.DeHum++;
					if( IndoorCommand.FanRate.DeHum > INDOOR_FANRATE_SWING) IndoorCommand.FanRate.DeHum = INDOOR_FANRATE_1;
				break;
			case REMOTE_HEAT :
						IndoorCommand.FanRate.Heat++;
					if( IndoorCommand.FanRate.Heat > INDOOR_FANRATE_SWING) IndoorCommand.FanRate.Heat = INDOOR_FANRATE_1;
				 break;
			case REMOTE_FAN_SPEED:
						IndoorCommand.FanRate.FanMode++;
					if( IndoorCommand.FanRate.FanMode > INDOOR_FANRATE_SWING) IndoorCommand.FanRate.FanMode = INDOOR_FANRATE_1;
			 default:break;
		}
		IndoorCommand.FanRate.GUI = ON;
 }

void IndoorPlasmaUpdate(void){

 	if(IndoorCommand.Plasma.Enabled == ON){
		IndoorCommand.Plasma.Enabled = OFF;
		IndoorCommand.Plasma.On =!IndoorCommand.Plasma.On;
		IndoorCommand.Plasma.GUI = ON;
	}
	Indoor_Mode_SwingCheck();
	//IndoorCommand.Mode.GUI = ON;
	IndoorCommand.SwingYatay.GUI = ON;
	IndoorCommand.SwingDikey.GUI = ON;
	/*
	if(IndoorCommand.Plasma.On){
		IndoorCommand.SwingYatay.On = ON;
		IndoorCommand.SwingDikey.On = ON;
		IndoorCommand.Mode.GUI = ON;
	}
	*/
}


void Indoor_Comand_Execute(void){
	Indoor_Mode_Set();
	IndoorFanUpdate();
	Indoor_Onff_Set();
	IndoorPlasmaUpdate();
	Indoor_Mode_Jet();
	Indoor_Mode_ESaving();
	Indoor_Mode_AClean();
	Indoor_Mode_RoomTempShow();
	Indoor_Mode_DownButton();
	Indoor_Mode_UpButton();
	Indoor_Mode_SwingDikey();
	Indoor_Mode_SwingYatay();
		switch(IndoorCommand.Mode.Case){
			case REMOTE_OFF:
					if (IndoorCommand.Plasma.On)IndoorCommand.FanRate.Final =  IndoorCommand.FanRate.Plasma;
					else  						IndoorCommand.FanRate.Final = INDOOR_FANRATE_0 ;
				break;
			 case REMOTE_COOL :
					if(IndoorCommand.SetTemperature_Cooling < COOLING_MINSET) 	IndoorCommand.SetTemperature_Cooling = COOLING_MINSET;
					if(IndoorCommand.SetTemperature_Cooling > COOLING_HIGHSET) 	IndoorCommand.SetTemperature_Cooling = COOLING_HIGHSET;
					Temperature.InSet = IndoorCommand.SetTemperature_Cooling*10 ;
					IndoorCommand.FanRate.Final = IndoorCommand.FanRate.Cool ;
				break;
 		 	case REMOTE_AUTOCHNG:
					if(IndoorCommand.SetTemperature_Auto > AUTOCHNGE_HIGHSET) 	IndoorCommand.SetTemperature_Auto = AUTOCHNGE_HIGHSET;
					if(IndoorCommand.SetTemperature_Auto < AUTOCHNGE_MINSET) 	IndoorCommand.SetTemperature_Auto = AUTOCHNGE_MINSET;
					Temperature.InSet = IndoorCommand.SetTemperature_Auto*10;
					IndoorCommand.FanRate.Final = IndoorCommand.FanRate.Auto ;
				break;
			case REMOTE_DEHUMIDIF :

					IndoorCommand.FanRate.Final = IndoorCommand.FanRate.DeHum ;
				break;
			case REMOTE_HEAT :
					if(IndoorCommand.SetTemperature_Heating < HEATING_MINSET) 	IndoorCommand.SetTemperature_Heating = HEATING_MINSET;
					if(IndoorCommand.SetTemperature_Heating > HEATING_HIGHSET) 	IndoorCommand.SetTemperature_Heating = HEATING_HIGHSET;
					Temperature.InSet = IndoorCommand.SetTemperature_Heating*10;
					IndoorCommand.FanRate.Final = IndoorCommand.FanRate.Heat ;
				 break;
			case REMOTE_FAN_SPEED:
					IndoorCommand.FanRate.Final = IndoorCommand.FanRate.FanMode ;
			 default:break;
		}




}



#ifdef MANAGED_DOTNET_COMPILER
}
#endif



