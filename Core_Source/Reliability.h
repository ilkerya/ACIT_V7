
/********************************************************************
 FileName:     	Reliability.h
 Processors:		32 bit embedded Micro or 32 bit Windows Running PC
 Complier:  	Microchip PIC32 ; Panasonic MN103S ; .net Framework 3.5 CLI Select only One!!
 Company:	Arcelik-LG Klima AS  http://www.arcelik-lg.com.tr/
 Author :     ilker yagci
File Description:
		Compressor Reliability Functions
 Change History:
  Rev   Date         Description
  1.0   05.04.2012   Initial release
 *********************************************************************/

#ifdef MANAGED_DOTNET_COMPILER
namespace ACIT_Stack{ // additional line for C++ debugging
#endif

signed char Get_Step_Zone(struct Reliability_Ram *p1,signed char *p2,unsigned char *p3,unsigned char Conf_Line,signed short Temperature);

void Determine_Limits(struct Reliability_Ram *p1,signed char *p2,unsigned char *p3,unsigned char Conf_Line,unsigned char Lojic){
		switch(AirCon.SubMode){
			case COOL:
					p1->Zone_Limits[4] = p2[p3[0+Conf_Line*CONF_WIDTH]*MAX_MODEL+AirCon.Model]; // X4 FOR COOLING  Te4
					p1->Zone_Limits[2] = p2[p3[1+Conf_Line*CONF_WIDTH]*MAX_MODEL+AirCon.Model];  // x2 FOR COOLING Te2
			break;
		case HEAT:
					p1->Zone_Limits[4] = p2[p3[2+Conf_Line*CONF_WIDTH]*MAX_MODEL+AirCon.Model]; // X4 FOR COOLING  Te4
					p1->Zone_Limits[2] = p2[p3[3+Conf_Line*CONF_WIDTH]*MAX_MODEL+AirCon.Model];  // x2 FOR COOLING Te2
			break;
	}
		switch(Lojic){
			case RISING:
					p1->Zone_Limits[2] *= RISETABLE_CORRECTION;
					p1->Zone_Limits[4] *= RISETABLE_CORRECTION;
					break;
			case FALLING:
					p1->Zone_Limits[2] *= FALLTABLE_CORRECTION;
					p1->Zone_Limits[4] *= FALLTABLE_CORRECTION;
					break;
		}


	#if (defined MANAGED_DOTNET_COMPILER || defined MICROCHIP_COMPILER)
		p1->Zone_Limits[0] = (unsigned char)(p1->Zone_Limits[2] - ((float)      p1->Zone_Limits[4] - p1->Zone_Limits[2])); //T0 = T2 - (T4-T2)
		p1->Zone_Limits[1] = (unsigned char)(p1->Zone_Limits[2] - ((float)1/2)*(p1->Zone_Limits[4] - p1->Zone_Limits[2])); //T1 = T2 - (T4-T2)*1/2
		p1->Zone_Limits[3] = (unsigned char)(p1->Zone_Limits[2] + ((float)1/2)*(p1->Zone_Limits[4] - p1->Zone_Limits[2])); //T3 = T2 + (T4-T2)*1/2
	#endif
	#if (defined PANASONIC_COMPILER)
		p1->Zone_Limits[0] = (unsigned char)(p1->Zone_Limits[2] - (      p1->Zone_Limits[4] - p1->Zone_Limits[2])); //T0 = T2 - (T4-T2)
		p1->Zone_Limits[1] = (unsigned char)(p1->Zone_Limits[2] - (1/2)*(p1->Zone_Limits[4] - p1->Zone_Limits[2])); //T1 = T2 - (T4-T2)*1/2
		p1->Zone_Limits[3] = (unsigned char)(p1->Zone_Limits[2] + (1/2)*(p1->Zone_Limits[4] - p1->Zone_Limits[2])); //T3 = T2 + (T4-T2)*1/2
	#endif

}
void Determine_Hysteresiz(struct Reliability_Ram *p1,signed char*p2,unsigned char*p3,unsigned char Conf_Line,unsigned char Lojic){
		unsigned char i;
	if(p3[4+Conf_Line*CONF_WIDTH] == 64)return;  // no any hysteresiz
	for(i=0;i<2;i++){
		if(p1->Zone <= i) p1->Hysteresiz[i] = 0; // p[4-i] -= 0; // do not modify no hysteresiz   Zone is Reliability.Te.Zone
		else	          p1->Hysteresiz[i] = p2[p3[4+Conf_Line*CONF_WIDTH]*MAX_MODEL+AirCon.Model];
	}
		switch(Lojic){
			case RISING:
					p1->Hysteresiz[0]*=RISETABLE_CORRECTION;
					p1->Hysteresiz[1]*=RISETABLE_CORRECTION;
					p1->Zone_Limits[0] -=  p1->Hysteresiz[0];
					p1->Zone_Limits[1] -=  p1->Hysteresiz[1];
					break;
			case FALLING:
					p1->Hysteresiz[0]*=FALLTABLE_CORRECTION;
					p1->Hysteresiz[1]*=FALLTABLE_CORRECTION;
					p1->Zone_Limits[0] +=  p1->Hysteresiz[0];
					p1->Zone_Limits[1] +=  p1->Hysteresiz[1];
					break;
		}
}

void Determine_Zone_Time(struct Reliability_Ram *p1,signed char *p2,unsigned char *p3,unsigned char Conf_Line,signed short Temperature,unsigned char Lojic){
	// this function get parameter of Reliability array and returns offset to the related array index j is the array itself
	unsigned char i;
	switch(Lojic){
				case RISING:
					for(i=0;i<6 ;i++){
						if(Temperature < p1->Zone_Limits[i]){p1->Zone = i;break;}; // if smaller then To
						if(Temperature >= p1->Zone_Limits[4]){p1->Zone = 5;break;}; // if smaller then To
					}
					break;
				case FALLING:
					for(i=0;i<6 ;i++){
						if(Temperature >= p1->Zone_Limits[i]){p1->Zone = i;break;}; // if smaller then To
						if(Temperature < p1->Zone_Limits[4]){p1->Zone = 5;break;}; // if smaller then To
					}
					break;
	}
	switch(p1->Zone){
		case 0:	p1->Timeout = 60;break;// (unsigned char) p2[p3[5+Conf_Line*CONF_WIDTH]*MAX_MODEL+AirCon.Model] *10;break; // check if Timer2 is enabled if yes load from table value
		case 1:  p1->Timeout = (unsigned char) p2[p3[5+Conf_Line*CONF_WIDTH]*MAX_MODEL+AirCon.Model] *10; break;// check if Timer2 is enabled if yes load from table value  zone 1 timers
		case 2:	p1->Timeout =0; break; //p1->Timeout = (unsigned char) p2[p3[6+Conf_Line*CONF_WIDTH]*MAX_MODEL+AirCon.Model] *10;break; // check if Timer2 is enabled if yes load from table value
		case 3:  p1->Timeout = (unsigned char) p2[p3[7+Conf_Line*CONF_WIDTH]*MAX_MODEL+AirCon.Model] *10; break;// check if Timer2 is enabled if yes load from table value  zone 3 timers
		case 4:	p1->Timeout = (unsigned char) p2[p3[8+Conf_Line*CONF_WIDTH]*MAX_MODEL+AirCon.Model] *10; break;// check if Timer2 is enabled if yes load from table value  zone 4 timers
		case 5:	p1->Timeout = 0;break;
	}
	if(p1->Counter > p1->Timeout )p1->Counter = p1->Timeout;
	if(p1->PrevZone != p1->Zone) p1->Counter = p1->Timeout;
}
void Determine_New_Step(struct Reliability_Ram *p1,unsigned char Conf_Line){
	signed short k =  Reliability.Steps[Conf_Line];	// get previous step

	if  ( ! ((AirCon.SubMode == HEAT) ||   (AirCon.SubMode == COOL))  ) return; // if not at heating or cooling do not populate value

	switch(p1->Zone){
		case 0:		//k = GetMinMax_Step(MAX); // in order to set max first clear then set to max
		    if(!p1->Counter){ // switch to next step incline or decline modify limits according to hysteresiz
				p1->Counter = p1->Timeout;
				if(k < GetMinMax_Step(MAX))k ++;  // get default
			}
			break;
		case 1:
			if(!p1->Counter){ // switch to next step incline or decline modify limits according to hysteresiz
				p1->Counter = p1->Timeout;
				if(k < GetMinMax_Step(MAX))k ++;  // get default
			}
				break;
		case 2:	 //if(!p1->Counter )p1->Counter = p1->Timeout;
			break;
		case 3:
			if(!p1->Counter){ // switch to next step incline or decline modify limits according to hysteresiz
				p1->Counter = p1->Timeout;
				if(k) k --;
			}
			break;
		case 4:	if(!p1->Counter){ // switch to next step incline or decline modify limits according to hysteresiz
				p1->Counter = p1->Timeout;
				if(k) k --;
			}
				break;
		case 5:	 k =0; p1->Counter = 17;
			break;
	}
	Reliability.Steps[Conf_Line] = k;
	p1->PrevZone = p1->Zone;
}

    void Evaporator_Freezing_Prevention_Limit(unsigned char Conf_Line){ // 1  // inverse logic
    if(AirCon.SubMode != COOL) {Reliability.Steps[Conf_Line] = 	GetMinMax_Step( MAX); return;}
	//signed char i;
	struct Reliability_Ram* p1 = &Te_Hold; // holds ram struct datas to work on with the type of Reliability_Ram struct//
	signed char*			p2 = &Zone_Table_Te[0];              // holds parameters at flash for Te
	unsigned char*			p3 = &Zone_Configuration_Table[0];   // holds offset adresses common table //
	signed short	Temp = Temperature.InMidPipe/(REALTEMPFACTOR/FALLTABLE_CORRECTION);
	Determine_Limits(p1,p2,p3,Conf_Line,FALLING);  // lets find x4 and x2 depending on the function Td4 Td2 or Te4 Te2
	Determine_Hysteresiz(p1,p2,p3,Conf_Line,FALLING);		// different logic
	// now send adresse of tables and timer1 line information so that function can use timers and temperature that we want to compare
	Determine_Zone_Time(p1,p2,p3,Conf_Line,Temp,FALLING);  // // different logic

//	if(TimerUc.TotalCompOperation != 0 )return;
	if(Motor.Timer.TotOpTime <  (unsigned int)Zone_Table_Te[30+AirCon.Model]*60)return;
	Determine_New_Step(p1,Conf_Line);
}
	unsigned char Dewing_Decision(signed char *p2){
		unsigned char  i;
		//	if(AirCon.SubMode == HEAT) return 0;
			i = 7;
			if(Temperature.InAir/REALTEMPFACTOR <  p2[i*MAX_MODEL+AirCon.Model])  return 0;
			if(Temperature.OutAir/REALTEMPFACTOR <  p2[i*MAX_MODEL+AirCon.Model])  return 0;
		    i = 8;
			if(Temperature.InAir/REALTEMPFACTOR >  p2[i*MAX_MODEL+AirCon.Model] ) return 0;
			if(Temperature.OutAir/REALTEMPFACTOR >  p2[i*MAX_MODEL+AirCon.Model])  return 0;
		    i = 9;

			if(IndoorCommand.FanRate.Final >  p2[i*MAX_MODEL+AirCon.Model] ) { // only accapt 2,3 ,4, 5  // skip 1
				if(IndoorCommand.FanRate.Final != INDOOR_FANRATE_5) return 0;  // only accapt if, 5
			}
			return ON; // ok start // 1 5
	}
	void Dewing_Preventation_Limit(unsigned char Conf_Line){// 3     RS 4.3.2.11
	if(AirCon.SubMode != COOL) {Reliability.Steps[Conf_Line] = 	GetMinMax_Step( MAX); return;}
	if(Motor.Cycle.OperatingMode != COMP_PI_MODE ){Reliability.Steps[Conf_Line] = 	GetMinMax_Step( MAX); return;}

	struct Reliability_Ram *p1 = &Dew_Hold; // holds ram struct datas to work on with the type of Reliability_Ram struct//
	signed char*			p2 = &Zone_Table_Dew[0];              // holds parameters at flash for Te
	unsigned char*			p3 = &Zone_Configuration_Table[0];   // holds offset adresses common table //
	signed short	Temp = Temperature.InMidPipe/(REALTEMPFACTOR/RISETABLE_CORRECTION);
	Determine_Limits(p1,p2,p3,Conf_Line,RISING);  // lets find x4 and x2 depending on the function Td4 Td2 or Te4 Te2
	Determine_Zone_Time(p1,p2,p3,Conf_Line,Temp,FALLING);  // // different logic
	if(!Dewing_Decision(p2)) {
//		TimerUc.DewReliability= 0;
		Reliability.Steps[Conf_Line] = 	GetMinMax_Step( MAX);
		return;} // stop if decision not succesful yet
//	if(TimerUc.DewReliability < (unsigned int)p2[30+AirCon.Model]*60)  return;   //  60*5 = 300 sec
	Determine_New_Step(p1,Conf_Line);
}
    void High_Pressure_Condenser_Rising_Prevention_Limit(unsigned char Conf_Line){// 0 // ok checked
	struct Reliability_Ram *p1 = &Tc_Hold; // holds ram struct datas to work on with the type of Reliability_Ram struct//
	signed char*			p2 = &Zone_Table_Tc[0];              // holds parameters at flash for Te
	unsigned char*			p3 = &Zone_Configuration_Table[0];   // holds offset adresses common table //
	signed short	Temp = Temperature.OutMidPipe/(REALTEMPFACTOR/RISETABLE_CORRECTION); // default cooling
	if(AirCon.SubMode == HEAT) Temp = Temperature.InMidPipe/(REALTEMPFACTOR/RISETABLE_CORRECTION);
	Determine_Limits(p1,p2,p3,Conf_Line,RISING);  // lets find x4 and x2 depending on the function Td4 Td2 or Te4 Te2
	Determine_Hysteresiz(p1,p2,p3,Conf_Line,RISING);
	Determine_Zone_Time(p1,p2,p3,Conf_Line,Temp,RISING);  // // different logic
	Determine_New_Step(p1,Conf_Line);
}

void Compressor_DischargeTemp_Overheating_Limit(unsigned char Conf_Line){// 2     RS 4.3.2.2 	// ok checked
	struct Reliability_Ram *p1 = &Td_Hold; // holds ram struct datas to work on with the type of Reliability_Ram struct//
	signed char				*p2 = &Zone_Table_Td[0];              // holds parameters at flash for Te
	unsigned char			*p3 = &Zone_Configuration_Table[0];   // holds offset adresses common table //
	signed short	Temp = Temperature.Discharge/(REALTEMPFACTOR/RISETABLE_CORRECTION);
	Determine_Limits(p1,p2,p3,Conf_Line,RISING);  // lets find x4 and x2 depending on the function Td4 Td2 or Te4 Te2
	Determine_Hysteresiz(p1,p2,p3,Conf_Line,RISING);
	Determine_Zone_Time(p1,p2,p3,Conf_Line,Temp,RISING);  // // different logic
	Determine_New_Step(p1,Conf_Line);
}

void CT_Rising_Preventation_Limit(unsigned char Conf_Line){// 3     RS 4.3.2.7
			Conf_Line = 0;
}
void Heat_Sink_Overheating_Prevention_Limit(unsigned char Conf_Line){// 3     RS 4.3.2.3
			Conf_Line = 0;
}

void Outdoor_Temperature_Limit(unsigned char Conf_Line){
		signed char *p;unsigned char  LineIndex=0;
		switch(AirCon.SubMode){
			case COOL:	 case COOL_DELAY: p = &Outdoor_Cooling_TempLimit_Table[0];  // pass adress of Heating Table to referance adress
			break;
		case HEAT:	  case HEAT_DELAY:   p = &Outdoor_Heating_TempLimit_Table[0];  // pass adress of Heating Table to referance adress
			break;
		default : return;
		}
		for(LineIndex=0; LineIndex<6; LineIndex++){			// find index at Table 4.5 or Table 4.6
                if ((Temperature.OutAir/REALTEMPFACTOR)< p[LineIndex * WIDTH]) break;  // get correction coefficients from outdoor air
		}
	    Reliability.Steps[Conf_Line] = p[AirCon.Model+TEMP_COLUMN + (LineIndex * WIDTH) ] ;
		Reliability.StepIndex[Conf_Line] = LineIndex;
}

void Suction_Overheating_Level_Rising_Prevention_Limit(unsigned char i){i=0;}


void Input_Voltage_Limit(void){
///	unsigned char i;
	unsigned char *p = &Inp_Volt_MaxLim[0];
/*
	#if (defined MANAGED_DOTNET_COMPILER || defined MICROCHIP_COMPILER)
		float LOW_DELTA_STEP = 0.05f;
		float HIGH_DELTA_STEP = 0.05f;
		float Temp;
	#endif
	#if (defined PANASONIC_COMPILER)
		short  LOW_DELTA_STEP = 0;
		short HIGH_DELTA_STEP = 0;
		short Temp;
	#endif

		switch(AirCon.SubMode){
			default:
			case COOL:case COOL_DELAY: i = 0;break;
			case HEAT:case HEAT_DELAY: i = 1;break;
		}
	if(p[i] - p[2+i]> Hardware.InpVoltage){ // 220  den kucuk
			#if (defined MANAGED_DOTNET_COMPILER || defined MICROCHIP_COMPILER)
				Temp =  LOW_DELTA_STEP * (float)(p[i] - p[2+i] - Hardware.InpVoltage);
				Temp = (float) GetMinMax_Step(MAX) - Temp ;
			#endif
			#if (defined PANASONIC_COMPILER)
				Temp =  LOW_DELTA_STEP * (p[i] - p[2+i] - Hardware.InpVoltage);
				Temp = GetMinMax_Step(MAX) - Temp ;
			#endif
				if(!TimerUc.InpVoltage)  Reliability.Steps[INP_VOLTAGE_MAX] =  (unsigned char )Temp;
				if (Reliability.Steps[INP_VOLTAGE_MAX] < 1) Reliability.Steps[INP_VOLTAGE_MAX] = 1;
		//	return OFF;
	}
	else {
		if(p[i] + p[2+i]< Hardware.InpVoltage){ // 240 tan buyuk
			#if (defined MANAGED_DOTNET_COMPILER || defined MICROCHIP_COMPILER)
				Temp =  HIGH_DELTA_STEP * (float) (Hardware.InpVoltage - p[i] - p[2+i]);
				Temp = (float) GetMinMax_Step(MAX) - Temp ;
			#endif
			#if (defined PANASONIC_COMPILER)
				Temp =  HIGH_DELTA_STEP * (Hardware.InpVoltage - p[i] - p[2+i]);
				Temp =  GetMinMax_Step(MAX) - Temp ;
			#endif
				if(!TimerUc.InpVoltage)  Reliability.Steps[INP_VOLTAGE_MAX] = (unsigned char )Temp;
				if (Reliability.Steps[INP_VOLTAGE_MAX] < 1) Reliability.Steps[INP_VOLTAGE_MAX] = 1;
		}
		else{
			TimerUc.InpVoltage = p[6+i]; //
			Reliability.Steps[INP_VOLTAGE_MAX] = GetMinMax_Step(MAX);
		}
	}
*/
}

void Sleeping_Operation_Limit(unsigned char Conf_Line){
		unsigned char *p = &Sleeping_Max_Step[0];
		if(!IndoorCommand.SleepMode) {
			Reliability.Steps[Conf_Line] = GetMinMax_Step(MAX);// get default
			return;
		}
		switch(AirCon.SubMode){
			case COOL: case 	COOL_DELAY :  Reliability.Steps[Conf_Line] = p[AirCon.Model];
				break;
			case HEAT: case 	HEAT_DELAY :Reliability.Steps[Conf_Line] = p[AirCon.Model+5];
				break;
			default :Reliability.Steps[Conf_Line] = GetMinMax_Step(MAX);break;// get default ;
		}
}
void Dehumidifying_Operation_Limit(unsigned char i){i=0;}
void Suction_Pipe_Freez_Prevention_Limit(unsigned char i){i=0;}
void Economical_Cooling_Limit(unsigned char i){i=0;}
void Non_Dehumidifying_Limit(unsigned char i){i=0;}

void Reliability_Fill_Default(void){
	unsigned char i;
	switch(AirCon.SubMode){
		case 	COOL_DELAY :  case 	HEAT_DELAY :
				for(i=0; i < 14; i++){
						Reliability.Steps[i]  = GetMinMax_Step(MAX);
						Reliability.SortedStepsNo[i] = i;
				}
			break;
		default :break;// get default ;
	}
}

short MinStep_Sub(short *p, unsigned char Loop){
	unsigned char i;
	for(i=Loop; i !=0; i--){
		if( Temperature.OutAir <= p[i*2]) return i;
	}
	return 0;
}

void MinStep_Align(unsigned char index){
	if(Motor.Cycle.OperatingMode == COMP_FIRST_START1 ){}//Reliability.MinStep[index] =  Reliability.MinStepAlign; // compressor start steps
	else Reliability.MinStep[index] =  GetMinMax_Step( MAX);
}
void MinStep_Defrost(unsigned char index){
	switch(AirCon.SubMode){
		case DEFROST_0: case DEFROST_1: case DEFROST_2:case DEFROST_3:case DEFROST_4:case DEFROST_5:case DEFROST_6:case DEFROST_7:case DEFROST_8:
				Reliability.MinStep[index] =   GetMinMax_Step( MIN); break;
		default : Reliability.MinStep[index] =  222 ;break;
	}
}
void Calculate_Current_Min(void){
	if(Motor.Cycle.OperatingMode == COMP_FIRST_START1 ){
		Reliability.MinStep[ACTUAL_MIN] = Reliability.MinStep[ALIGN_MIN] ;
		return;
	}
	if(Reliability.MinStep[DEFR_MIN] != 222){
		Reliability.MinStep[ACTUAL_MIN] = Reliability.MinStep[DEFR_MIN] ;
		return;
	}
	//Reliability.MinStep[TC_MIN] = 0;  // buyugunu al  TC_MIN ve OUT_MIN le karsilastir
	if(Reliability.MinStep[TC_MIN]  > Reliability.MinStep[OUT_MIN])  Reliability.MinStep[ACTUAL_MIN] = Reliability.MinStep[TC_MIN];
	else																								  Reliability.MinStep[ACTUAL_MIN] = Reliability.MinStep[OUT_MIN];

}
void MaxStep_Align(void){
	if(Motor.Cycle.OperatingMode == COMP_FIRST_START1 ){}//Reliability.MinStep[index] =  Reliability.MinStepAlign; // compressor start steps
	else Reliability.Steps[ALIGN_MAX] =  GetMinMax_Step( MAX);

}
void MaxStep_Defrost(void){
	switch(AirCon.SubMode){
					case DEFROST_0: case DEFROST_1: case DEFROST_2:case DEFROST_3:case DEFROST_4:case DEFROST_5:case DEFROST_6:case DEFROST_7:case DEFROST_8:
					 Reliability.Steps[DEFR_MAX] =   GetMinMax_Step( MAX);
					 break;
		default : Reliability.Steps[DEFR_MAX] =  222 ;break;
	}
}
void MinStep_OutLow(unsigned char index){
	unsigned char i;unsigned char j_ind; short *p;
	switch(AirCon.SubMode){
		case COOL :
				j_ind = 0;
				p = &MinHzLimCooling_OutLow[0];
			break;
		case HEAT :
				j_ind = 1;
				p = &MinHzLimHeating_OutLow[0];
		break;
		default:return;
	}
	Reliability.MinIndex[0] = (unsigned char)MinStep_Sub(p, 4);
	for(i=0;i<=25;i++){
		if ( p[Reliability.MinIndex[0]*2+1] <=  Table_Step2Frequency[(i-1)*MAX_MODEL+(AirCon.Model)]) {
				Reliability.MinStepOutLow[j_ind] = i;
				break;
		}
	}

	if( Reliability.MinStepOutLow[0] > Reliability.MinStepOutLow[1]) 	Reliability.MinStep[index] = Reliability.MinStepOutLow[0];
	else																								Reliability.MinStep[index]  = Reliability.MinStepOutLow[1];
	//Reliability.MinStep[index] = Reliability.MinSortedSteps;
}

short MinStep_Subswert(short *p, short Temperature){
	unsigned char i;
	for(i=4; i !=0; i--){
		if( Temperature <= p[i*2]) return i;
	}
	return 0;
}
void MinStep_Condenser(unsigned char index){
		unsigned char i;short *p = &MinCondenserLimit[0];short Temp;
		switch(AirCon.SubMode){
			case COOL :
				Temp = Temperature.OutMidPipe;
					break;
			case HEAT :
				Temp = Temperature.InMidPipe;
					break;
			default:return;
		}
		Reliability.MinIndex[1]  = (unsigned char)MinStep_Subswert(p, Temp);
		for(i=0;i<=25;i++){
			if ( p[Reliability.MinIndex[1]*2+1]   <=   Table_Step2Frequency[(i-1)*MAX_MODEL+(AirCon.Model)]) {
					Reliability.MinStep[index] = i;
					break;
			}
		}
		//Reliability.MinStep[index]
}

void Reliability_Check(void){
	unsigned char i;
		for(i=0; i < 14; i++){
			switch(i){   //Table 4.13 RS Document
				case 0:  High_Pressure_Condenser_Rising_Prevention_Limit(i);break;		// RS 4.3.2.4  Tc
				case 1:  Evaporator_Freezing_Prevention_Limit(i);break;  //RS			// RS 4.3.2.6  Te
				case 2:  Compressor_DischargeTemp_Overheating_Limit(i);break;			// RS 4.3.2.2  Td   //Heat_Sink_Overheating_Prevention_Limit  RS 4.3.2.3
		//		case 3:  k = CT_Rising_Preventation_Limit(i);break;                       //   RS 4.3.2.7	CT rising prevention limit
		//		case 4:  k = Heat_Sink_Overheating_Prevention_Limit(i); break;            //   RS 4.3.2.3   HS //
				case 5:  Outdoor_Temperature_Limit(i);break;  //                        // RS 4.3.2.9	Outdoor temperature limit
		//		case 6:  k = Suction_Overheating_Level_Rising_Prevention_Limit(i);          // RS 4.3.2.8	Suction overheating level rising prevention limit
				case 7:  Input_Voltage_Limit();break;  //								// RS 4.3.2.1	Input voltage limit
				case 8:  Dewing_Preventation_Limit(i);break;							// RS 4.3.2.11	Dewing prevention limit
				case 9:  Sleeping_Operation_Limit(i);break;								// RS 4.3.2.10	Sleeping operation limit
		//		case 10: k = Dehumidifying_Operation_Limit(i);break;						// RS 4.3.2.12	Dehumidifying operation limit
		//		case 11: k = Suction_Pipe_Freez_Prevention_Limit(i); break;  // RS 4.3.2.16
		//		case 12: k = Economical_Cooling_Limit(i); break; //  4.3.2.13	Economical cooling limit
		//		case 13: k = Non_Dehumidifying_Limit(i); break; //  4.3.2.14	Non-dehumidifying operation
				case 14:		MaxStep_Align();		break;
				case 15:		MaxStep_Defrost();	break;
			default:break;
			}
		}
		for(i=0; i < 5; i++){
			switch(i){   //Table 4.13 RS Document
				case 0:  Calculate_Current_Min();  break; // total min calculated
				case 1:  MinStep_Align(i); break;
				case 2:  MinStep_Defrost(i) ; break;
				case 3:  MinStep_OutLow(i);break;  // outdoor low  RS 4.3.2.17  RS 4.3.2.19
				case 4:  MinStep_Condenser(i); break;
				default:break;
			}
		}
}

#ifdef MANAGED_DOTNET_COMPILER
}
#endif
