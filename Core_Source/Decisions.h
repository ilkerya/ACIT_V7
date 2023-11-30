
/********************************************************************
 FileName:     	Decisions.h
 Processors:		32 bit embedded Micro or 32 bit Windows Running PC
 Complier:  	Microchip PIC32 ; Panasonic MN103S ; .net Framework 3.5 CLI Select only One!!
 Company:	Arcelik-LG Klima AS  http://www.arcelik-lg.com.tr/
 Author :     ilker yagci
File Description:
		Final Defrost, COP Mode & PreHeat Decision Algorithms
 Change History:
  Rev   Date         Description
  1.0   05.04.2012   Initial release

 *********************************************************************/
#ifdef MANAGED_DOTNET_COMPILER
namespace ACIT_Stack{ // additional line for C++ debugging
#endif

void Defrost_AverageTemp_Conversion(void){
		switch(Defrost_Average.Counter){
			case 60:
			case 120:
			case 180:
			case 240:   Defrost_Average.Sample++;
					Defrost_Average.OutAirTemp      += Temperature.OutAir;
					Defrost_Average.OutMidAirTemp += Temperature.OutMidPipe;
					break;
			case 0:   Defrost_Average.Sample=0;
				Defrost_Average.OutAirTemp += Temperature.OutAir;
				Defrost_Average.AverageOutAir = Defrost_Average.OutAirTemp  / 5;
				Defrost_Average.OutAirTemp = 0;
				Defrost_Average.OutMidAirTemp += Temperature.OutMidPipe;
				Defrost_Average.AverageMidPipe = Defrost_Average.OutMidAirTemp  / 5;
				Defrost_Average.OutMidAirTemp = 0;
				Defrost_Average.AvConversionDone = ON;
				break;
			default:break;
		}
}
void Clear_Def_Decision_Datas(void){
				AirCon.Timer.Defrost  = 0;            // as well as defrost timer
				Defrost_Average.Counter = 0;
				Defrost_Average.Sample = 0;
				Defrost_Average.OutAirTemp = 0;
				Defrost_Average.OutMidAirTemp = 0;
				Defrost_Average.AverageOutAir = 0;
				Defrost_Average.AverageMidPipe = 0;
				Defrost_Average.AvConversionDone = OFF;

}
//unsigned char GetLineNo_FromBasicTable1(signed short Temperature, signed short *p,unsigned char Row, unsigned char Elements){
//	unsigned char  i;
//	for(i=0; i<Elements; i++){
//			if(Temperature  >= p[i*2+Row]) return i;
//	}
//	return 0;
//}
//unsigned char GetLineNo_FromBasicTable2(signed short Temperature, signed short *p,unsigned char Row, unsigned char Elements){
//	unsigned char  i;
//	for(i=0; i<Elements; i++){
//			if(Temperature  > p[i*2+Row]) return i;
//	}
//	return Elements;
//}
/************************  Defrost_RS_8_1_1_1 FUNCTION **********************/
void Defrost_RS_8_1_1_1_TemperatureCheck(struct Defrost_Handle *p, signed short* p2 ){
	unsigned char  i;
	//	p->Line1 = GetLineNo_FromBasicTable1(Temperature.OutAir,       p2 , 0, 5); // /REALTEMPFACTOR
	for(i=0; i<5; i++){
		if(Temperature.OutAir  >= p2[i*2]){ p->Line1 =  i;break;}
	}
	p->Line2  = 0;
	for(i=5; i>0; i--){
		if(Temperature.OutMidPipe  < p2[i*2+1]) {p->Line2 =  i;break;}
	}
		if(p->Line2 - p->Line1 == 1) p->Match_Temperature1 = ON;
		else p->Match_Temperature1 = OFF;
		p->Match_Temperature2 = ON; //
}
/*********************************  Defrost_RS_8_1_1_2  FUNCTION  *************************************/
void Defrost_RS_8_1_1_2_TemperatureCheck(struct Defrost_Handle *p, signed short* p2 ){
	   unsigned char  i;
		#define DEFROST_MIN_COND_OFFSET 0
		//signed char* p2 = &Defrost_RS_8_1_1_2[0] ; //Column must be 1 or 2 // 3 is table width
		for(i=0; i<5; i++){
			// p->Line1 = i;
			if(Temperature.OutAir >=  p2[i*2]){ p->Line1 =  i;break;}
		}
		 p->Line2 =  p->Line1;//+100;
		switch( p->Line1){
				case 0: p->Calculated_Result =																						p2[1]  ;      break;
				case 1: p->Calculated_Result =  (p2[3]  - p2[1] ) *1 *  (Temperature.OutAir + 0)  / - 50  + p2[1] * 1 ;break; // -19+15( -20/-5)-15 =
				case 2: p->Calculated_Result =  (p2[5]  - p2[3] ) *1 * (Temperature.OutAir + 50) / - 50  + p2[3] * 1 ;  break;
				case 3: p->Calculated_Result=   (p2[7]  - p2[5] ) *1 * (Temperature.OutAir + 100) / -50 + p2[5] * 1 ;  break;
				case 4: p->Calculated_Result =  (p2[7]  - p2[5] ) *1 * (Temperature.OutAir + 150) / -50 + p2[5] * 1 ;  break;
				default:break;
		}

		if(Temperature.OutMidPipe   <= (p->Calculated_Result + DEFROST_MIN_COND_OFFSET)) p->Match_Temperature1 = ON;
		else p->Match_Temperature1 = OFF;
		p->Match_Temperature2 = ON; //
}//
/************************  Defrost_RS_8_1_1_3 FUNCTION // will call 2 times with different structures**********************/
void Defrost_RS_8_1_1_3_TemperatureCheck(struct Defrost_Handle *p, signed short* p2, signed short Compare_Temperature){
	if (Compare_Temperature  <= p2[0]) p->Match_Temperature1 = ON;
	else p->Match_Temperature1 = OFF;
//	if(Defrost_Average.AvConversionDone){
	//	if(Temperature.OutMidPipe - Defrost_Average.AverageMidPipe >=  p2[1]) p->Match_Temperature2 = ON;
	//	else p->Match_Temperature2 = OFF;
		if(Defrost_Average.AverageMidPipe  - Temperature.OutMidPipe >=  p2[1]) p->Match_Temperature2 = ON;
		else p->Match_Temperature2 = OFF;
//	}

}//LLOC 5
/*********************************  Defrost_RS_8_1_1_4  FUNCTION **************************************/
void Defrost_RS_8_1_1_4_TemperatureCheck(struct Defrost_Handle *p, signed short* p2 ){
	 unsigned char  i;
	if (Defrost_Average.AverageOutAir  >= p2[4]) p->Match_Temperature1 = OFF;
	else p->Match_Temperature1 = ON;

	for(i=0; i<2; i++){
		if(Defrost_Average.AverageOutAir  >= p2[i*2]){ p->Line1 =  i;break;}
	}
	for(i=0; i<2; i++){
		if(Temperature.OutMidPipe  >= p2[i*2+1]) {p->Line2 =  i;break;}
	}

	if(p->Line1 == p->Line2) p->Match_Temperature2 = ON;
	else p->Match_Temperature2 = OFF;
	// here timing chenges so later when time check consider Line position and load timeout value according to Line2
} // LLOC 7
/*********************************  Defrost_RS_8_1_1_5  FUNCTION **************************************/
void Defrost_RS_8_1_1_5_Func(void){
		//return NULL; // OFF
}

	#if (defined MICROCHIP_COMPILER || defined MANAGED_DOTNET_COMPILER)
void Defrost_Final_Check(struct Defrost_Handle *p,  unsigned char No){				// call  1 second interval
     BOOL *p2 = &Defrost_Decision_Configuration_Table[0];
		#endif
//		#ifdef MICROCHIP_COMPILER
//void Defrost_Final_Check(struct Defrost_Handle *p,  unsigned char No){				// call  1 second interval
 //    BOOL *p2 = &Defrost_Decision_Configuration_Table[0];


//		#endif
		#ifdef PANASONIC_COMPILER
void Defrost_Final_Check(struct Defrost_Handle *p,  unsigned char No){				// call  1 second interval
     unsigned char *p2 = &Defrost_Decision_Configuration_Table[0];
    	#endif

	if(!p->MainCounter){
		p->Match_Timeout =ON;
		if(!p->MaintenanceCounter)p->Match_Maintenance =ON;
	}
	//          Clear  Maintenance Timer Match if any temparature mismatch occurs // means unstable condition
	if(!(p->Match_Temperature1)   ||   !(p->Match_Temperature2)){
		p->Match_Maintenance =OFF;
		p->MaintenanceCounter = Const_Defrost_Table[No*2];  // if any mismatch occurs at temperature reload timer
	}
	// if both main timeout and Maintenance Timeout occured then check if we have to wait conversion from configuration table
	if( p->Match_Timeout &&  p->Match_Maintenance) {
		if(p2[No]) {   // adc_wait enabled from configuration
			if(Defrost_Average.AvConversionDone)p->FinalMatch = ON ;
			else p->FinalMatch = OFF ;
		}
		else p->FinalMatch = ON ;
	}
	else p->FinalMatch = OFF ;
	// if MAtch is ok and relevant defrost function enabled start defrost
	if(p->FinalMatch  ) {
			if(p2[No+5])if(p->Enabled)	AirCon.SubMode = DEFROST_0; // then start defrost if enabled
	}

}

	// Below Function cheks if timeout occured from Const_Defrost_Table column2 for each step if
	//timeout occured then calls the function
			// function returns 1 if defrost is sensed otherwise returns 0 to the Mem_Defrost_Table column 1
void Defrost_Decision(void){
	if(AirCon.Timer.TotalHeating < 900){
		Defrost8111.MainCounter   = Const_Defrost_Table[1];
		Defrost8112.MainCounter   = Const_Defrost_Table[3];
		Defrost8113_1.MainCounter = Const_Defrost_Table[5];
		Defrost8113_2.MainCounter = Const_Defrost_Table[7];
		Defrost8114.MainCounter   = Const_Defrost_Table[9];
		return;
	}
	unsigned char i;
      Defrost_RS_8_1_1_1_TemperatureCheck(&Defrost8111,     &Defrost_RS_8_1_1_1[0] );
	  Defrost_RS_8_1_1_2_TemperatureCheck(&Defrost8112,     &Defrost_RS_8_1_1_2[0] );
	  Defrost_RS_8_1_1_3_TemperatureCheck(&Defrost8113_1, 	&Defrost_RS_8_1_1_3_1[0],  Defrost_Average.AverageOutAir );
	  Defrost_RS_8_1_1_3_TemperatureCheck(&Defrost8113_2, 	&Defrost_RS_8_1_1_3_2[0] , Temperature.OutMidPipe);
	  Defrost_RS_8_1_1_4_TemperatureCheck(&Defrost8114,     &Defrost_RS_8_1_1_4[0] );

			// Below Functions will check only time  matchs and according to all matches will give final defrost decision

	if(Motor.Cycle.OperatingMode !=  COMP_PI_MODE) return;
	for(i=0; i < 6; i++){
		switch(i){
			case 0:  Defrost_Final_Check(&Defrost8111 ,     i  );   break;
			case 1:  Defrost_Final_Check(&Defrost8112 ,     i  );     break;
			case 2:  Defrost_Final_Check(&Defrost8113_1 ,  i );     break;
			case 3:  Defrost_Final_Check(&Defrost8113_2 ,  i  );    break;
			case 4:  Defrost_Final_Check(&Defrost8114 ,     i  );    break;
			case 5:  if(AirCon.SubMode == HEAT){
								Defrost8115.FinalMatch = ON;        // manuel mode
								if(Defrost8115.Enabled)	AirCon.SubMode = DEFROST_0;
					 }
				break;
			default:break;
		}
	}
}

/************************   SEER/HSPF Defrost_Decision **********************/
void SeerDefrost_Decision(void){
	unsigned int i = 5;   // last line seed defrostline
	unsigned char* p =  &Mem_Defrost_Table[0] ; //

//	if(!AirCon.Conf.SeerCycleToggle){
//		AirCon.Conf.SeerCycleToggle = 1;
//		Finalize_Defrost_Operation();
			// started from other mode do one time job her
//	}
	if(Const_Defrost_Table[i*2+1] < AirCon.Timer.TotalHeating) return;
	AirCon.SubMode = DEFROST_1;
	// Maintenance Check No need starts only with time
	if(p[i*3]){
		p[i*3+1]++;
		if(p[i*3+1] > Const_Defrost_Table[i*2]){
			p[i*3+1] = 0;

			AirCon.SubMode = DEFROST_1;   // start defrost
			Clear_Def_Decision_Datas();

		}
	}
	else p[i*3+1]= 0;
}

////////////////////////////////////PREHEAT SUPPLY DECISION////////////////////////////////////////////////////////

void  Preheat_Decision(void){}


////////////////////////////////////COP DECISION///////////////////////////////////////////////////////////////////
void  Cop_Decision(void){
//	 if(!Check_Input_Voltage_Limits4_COP())	return;		// calculate input voltage to be in limits
	 if(AirCon.Timer.COP < 1800)return;				// 30 min reached?

//	 return;

	 if(Motor.Cycle.OperatingMode != COMP_PI_MODE)return; // do it only when compressor is stable after start mode

}

#ifdef MANAGED_DOTNET_COMPILER
}
#endif


