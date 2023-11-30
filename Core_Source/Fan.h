
/********************************************************************
 FileName:     	Fan.h
 Processors:		32 bit embedded Micro or 32 bit Windows Running PC
 Complier:  	Microchip PIC32 ; Panasonic MN103S ; .net Framework 3.5 CLI Select only One!!
 Company:	Arcelik-LG Klima AS  http://www.arcelik-lg.com.tr/
 Author :     ilker yagci
File Description:
		Fan Final Rpm  Determining Algorithms
 Change History:
  Rev   Date         Description
  1.0   05.04.2012   Initial release

 *********************************************************************/
#ifdef MANAGED_DOTNET_COMPILER
namespace ACIT_Stack{ // additional line for C++ debugging
#endif

void Relay_Handle(void){ //
	switch(AirCon.SubMode){
		case STANDBYE :       break;
		case COOL:	Relays.Valve4Way = RELAY_COOLING;break;
		case HEAT:	Relays.Valve4Way = RELAY_HEATING;break;
		case COOL_DELAY:  //if( AirCon.Timer.Delay3Min < 5) Relays.Valve4Way = RELAY_COOLING;
							break;
		case HEAT_DELAY: //if( AirCon.Timer.Delay3Min < 5) Relays.Valve4Way = RELAY_HEATING; 	  // 10 sn kala al
							break;
		case DEFROST_0: case DEFROST_1: case DEFROST_2:case DEFROST_8:
					Relays.Valve4Way = RELAY_HEATING;	break;
				break;
		case DEFROST_3:case DEFROST_4:case DEFROST_5:case DEFROST_6:case DEFROST_7:
						Relays.Valve4Way = RELAY_COOLING;	break;
		default:break;
	}
}
void Fan_Cycle(void){
	//	signed char Temp = 0;// int i;
		Fan.InitStep = 12;
	if( !Fan.TcLatch){ // no latch
		Fan.MaxStep = 13;
		Fan.MinStep  = 1;
	}
		Fan_HeatSink_Compensation(); //			// //  tum sleep  kompanzasyonlari 0
		Fan_Td_Compensation();

	//Fan.BasicStep += (  Fan.Compensation[6] + Fan.Compensation[7]);//+ Fan.FinalStep;
	Fan.TargetStep = Fan.BasicStep;
	if( Fan.TargetStep < Fan.MinStep)Fan.TargetStep = Fan.MinStep;
	if( Fan.TargetStep > Fan.MaxStep)Fan.TargetStep = Fan.MaxStep;

	if( Fan.ManuelMode == FANRPM_AUTO){ // As auto

		Fan.FinalStep = Fan.TargetStep;
		if(Fan.FinalStep < Fan.Compensation[6]) Fan.FinalStep = Fan.Compensation[6];
		if(Fan.FinalStep < Fan.Compensation[7]) Fan.FinalStep = Fan.Compensation[7];
	}
	else Fan.FinalStep = Fan.ManuelMode;

		if(Fan.Timer)return;
		Fan_OutMidpipe1_Compensation();
		Fan.Timer = FAN_SAMPLE_TIME;
		Fan_Total_Compensation_Check();
		Fan_Tc_Decision();

		if( Fan.TcLatch){ //  latch Tc
			Fan.Compensation[5] = Fan_Tc_Compensation();
			Fan.BasicStep = Fan.InitStep +  Fan.Compensation[5];//+ Fan.FinalStep;
		}
		if( !Fan.TcLatch){ // no latch
			Fan.BasicStep = Fan.InitStep + Fan.TotalCompensation;
			if(Fan.BasicStep < Fan.Compensation[4]) Fan.BasicStep = Fan.Compensation[4];
		}

}

void Fan_Soft_Stop(void){
	if( Fan.FinalStep == 0)  return;
	if(Fan.SoftStopTimer == 0){
		Fan.FinalStep--;
		Fan.SoftStopTimer = 180/ (sizeof (FanStep2RpmTable)-2);
	}
}

void IndoorFan_Stop(void){
	Fan.Indoor.FinalStep = INDOOR_FANRATE_0;// stop
}
void IndoorFan_Cycle(void){
	/*
	unsigned char i;
	switch(IndoorCommand.FanRate){
		case FANRATE_SWING : i = 0 ;break;
		case FANRATE_0 : i = 0 ;break;
		case FANRATE_1 : i = 1 ;break;
		case FANRATE_2 : i = 2 ;break;
		case FANRATE_3 : i = 3 ;break;
		case FANRATE_4 : i = 4 ;break;
		case FANRATE_5 : i = 5 ;break;
		default: i = 5; break;
	}
	*/
	Fan.Indoor.FinalStep = IndoorCommand.FanRate.Final;
}

void Fan_Defrost(void){
	//Fan.DefrostStep = 5;
	Fan.FinalStep =		Fan.DefrostStep;
}
void IndoorFan_Defrost(void){
	//Fan.Indoor.DefrostStep = INDOOR_FANRATE_3;
	Fan.Indoor.FinalStep = Fan.Indoor.DefrostStep;
}

void Fan_Handle(void){ //
	switch(AirCon.SubMode){
		case STANDBYE : Fan_Soft_Stop();Fan.Indoor.FinalStep = INDOOR_FANRATE_0;// stop
							break;
		case COOL:
		case HEAT:	Fan_Cycle();        Fan.Indoor.FinalStep = IndoorCommand.FanRate.Final;
										Fan.Indoor.HotStart = OFF;
						break;
		case COOL_DELAY:
		case HEAT_DELAY: Fan_Soft_Stop();
					if(Fan.Indoor.HotStart) Fan.Indoor.FinalStep = INDOOR_FANRATE_1;// stop
					else 					Fan.Indoor.FinalStep = IndoorCommand.FanRate.Final;// sto
							break;
		case DEFROST_0:
						Fan.Indoor.FinalStep = IndoorCommand.FanRate.Final;
						Fan_Cycle();
			break;
		case DEFROST_1: case DEFROST_2:case DEFROST_3:case DEFROST_4:case DEFROST_5:case DEFROST_6:case DEFROST_7:case DEFROST_8:
						Fan.Indoor.FinalStep = Fan.Indoor.DefrostStep;
						Fan.FinalStep =		Fan.DefrostStep;
							break;
		default:break;
	}
	Fan.FinalRpm = FanStep2RpmTable[Fan.FinalStep] * 10;
	Fan.Indoor.FinalRpm = InddoorFanStep2RpmTable[Fan.Indoor.FinalStep] ;
	  // Fan.Indoor.FinalStep
}

void  Fan_Tc_Decision(void){ //2  call at the end of sample time
		if(AirCon.SubMode != COOL){
			Fan.TcLatch = OFF;
			return;
		}
		if(Temperature.OutAir < (short)Fan_Tc_Compensation_Threshold[0]) if( Motor.Timer.TotOpTime > Fan_Tc_Compensation_Threshold[2]) Fan.TcLatch = ON;
}

signed char  Fan_Tc_Compensation(void){ //2  call at the end of sample time
	if(Temperature.OutAir <= 50 ){
			Fan.MaxStep = Fan_Tc_CompTable[4];
			Fan.MinStep = Fan_Tc_CompTable[5];
	}
	else{
			Fan.MaxStep = Fan_Tc_CompTable[6];
			Fan.MinStep = Fan_Tc_CompTable[7];
	}
	if(Temperature.OutMidPipe >= Fan_Tc_CompTable[0]*10)return Fan_Tc_CompTable[1];
	if(Temperature.OutMidPipe <= Fan_Tc_CompTable[2]*10)return Fan_Tc_CompTable[3];
	return 0;
}
#define FAN_MAX_STEP 13

void  Fan_HeatSink_Compensation(void){ //0
	if(Temperature.HeatSink >= (Zone_Table_HS[AirCon.Model+1*MAX_MODEL])*10){
	//	Fan.MinStep  = FAN_MAX_STEP;
		Fan.Compensation[6] = FAN_MAX_STEP;
	}
//	else Fan.Compensation[6] = Fan.TargetStep;//Fan.FinalStep;
	else Fan.Compensation[6] = Fan.MinStep;              // 27.11.2012
}


signed char Fan_OutMidpipe2_Compensation(void){ //7
	if(Temperature.OutMidPipe >= Fan_MidHeat_Comp[0]*10) Fan.TMidLatch = ON;
	if(Temperature.OutMidPipe <= Fan_MidHeat_Comp[1]*10) Fan.TMidLatch = OFF;
		if(AirCon.SubMode != HEAT) return 0;
	if(Fan.TMidLatch) return Fan_MidHeat_Comp[2];
	else return 0;

}

signed char Fan_OutAir_Compensation(void){ //3
	signed char *p;signed char Temp;unsigned char MaxSize;//(sizeof(p)/2)
	unsigned int i;
	switch(AirCon.SubMode){
		case COOL: p = &Fan_CompOutAir_Cool[0]; MaxSize= 11;

			break;
		case HEAT:p = &Fan_CompOutAir_Heat[0]; MaxSize= 10;

			break;
		default : return 0;break;
	}
	for( i=0; i< MaxSize ;i++){
		if(Temperature.OutAir >= p[i*2]*10){Temp = p[i*2+1]; break;}
	}
	return Temp;
}

signed char Fan_Temperror_Compensation(void){ //4
	unsigned int i = 0;
	short *p = &Fan_Err_CompTable[0];
		signed char Temp = 0;
	switch(AirCon.SubMode){
		case COOL: i=0;
			if(PI.error.CompStep >=  p[i*3+0])
				if(Temperature.OutAir >= p[i*3+1]) Temp = (signed char)p[i*3+2];

			break;
		case HEAT: i=1;
				if(PI.error.CompStep >=  p[i*3+0])
					if(Temperature.OutAir <= p[i*3+1]) Temp = (signed char)p[i*3+2];
			break;
		default : return 0;break;
	}
	return Temp;
}
void  Fan_Td_Compensation(void){ //1



		Fan.Td4 = 	(Zone_Table_Td[AirCon.Model+0*MAX_MODEL])*10;
		Fan.Td2 = 	(Zone_Table_Td[AirCon.Model+1*MAX_MODEL])*10;
		Fan.Td0 = Fan.Td2 - (Fan.Td4 - Fan.Td2);
//	#if (defined MANAGED_NET_COMPILER || defined MICROCHIP_COMPILER)
		Fan.Td1 = Fan.Td2 - (Fan.Td4 - Fan.Td2)/2;
		Fan.Td3 = (short)((float)Fan.Td2 + (0.5f)*(float)(Fan.Td4 - Fan.Td2));
//	#endif
//	#if (defined PANASONIC_COMPILER)
//		Fan.Td1 = (short)(Fan.Td2 - (1/2)*(Fan.Td4 - Fan.Td2));
//		Fan.Td3 = (short)(Fan.Td2 + (1/2)*(Fan.Td4 - Fan.Td2));
//	#endif
		if(AirCon.MainMode != COOL){Fan.Compensation[7]  = Fan.TargetStep;Fan.Td_EmgLatch=OFF; return ;}

		if(Temperature.Discharge >= Fan.Td3) Fan.Td_EmgLatch = ON;
		if(Temperature.Discharge <= Fan.Td1)Fan.Td_EmgLatch = OFF;

		if(Fan.Td_EmgLatch) Fan.Compensation[7] = FAN_MAX_STEP;
	//	else Fan.Compensation[7] = Fan.TargetStep;//Fan.FinalStep;
		else Fan.Compensation[7] = Fan.MinStep;//27.11.2012;


}
signed char Fan_OutMidpipe1_Compensation(void){ //5

		Fan.Tc4 = 	(Zone_Table_Tc[AirCon.Model+0*MAX_MODEL])*10;
		Fan.Tc2 = 	(Zone_Table_Tc[AirCon.Model+1*MAX_MODEL])*10;
		Fan.Tc0 = Fan.Tc2 - (Fan.Tc4 - Fan.Tc2);
//	#if (defined MANAGED_NET_COMPILER || defined MICROCHIP_COMPILER)
		Fan.Tc1 = Fan.Tc2 - (Fan.Tc4 - Fan.Tc2)/2;
		Fan.Tc3 = (short)((float)Fan.Tc2 + (0.5f)*(float)(Fan.Tc4 - Fan.Tc2));


//	#endif
//	#if (defined PANASONIC_COMPILER)
//		Fan.Tc1 = (short)(Fan.Tc2 - (1/2)*(Fan.Tc4 - Fan.Tc2));
//		Fan.Tc3 = (short)(Fan.Tc2 + (1/2)*(Fan.Tc4 - Fan.Tc2));
//	#endif
		if(AirCon.MainMode != COOL){Fan.Tc_EmgLatch=OFF; return 0 ;}
		if(Temperature.OutMidPipe >= Fan.Tc3) Fan.Tc_EmgLatch = ON;
		if(Temperature.OutMidPipe <= Fan.Tc1)Fan.Tc_EmgLatch = OFF;

		if(Fan.Tc_EmgLatch) Fan.Compensation[4]  =  FAN_MAX_STEP;
		else Fan.Compensation[4] = Fan.InitStep + Fan.TotalCompensation;

		return 0;
}

signed char Fan_PowerHeat_Compensation(void){ //6
		if(AirCon.SubMode != HEAT)return 0;
		return 0; // non-functional code
}

void Fan_Total_Compensation_Check(void){
	signed char *p = &Fan.Compensation[0];
	unsigned char i;
	Fan.TotalCompensation = 0;
	for(i=0; i < 4; i++){
		switch(i){   //
			case 0:  p[i] = Fan_OutAir_Compensation();break;                       //  tum fan kompanzasyonlari 0
			case 1:  p[i] = Fan_Temperror_Compensation (); break;            //   algoritmasi var bak  0 donuyor superheat ile algoritma ayni onda fazlaliklar var
			case 2:  p[i] = Fan_OutMidpipe2_Compensation();break;
			case 3:  p[i] = Fan_PowerHeat_Compensation();break;
		//	case 4:  p[i] = Fan_OutMidpipe1_Compensation();break;
			default:break;
		}
		Fan.TotalCompensation +=  p[i];
	}
}
#ifdef MANAGED_DOTNET_COMPILER
}
#endif



