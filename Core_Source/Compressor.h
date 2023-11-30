
/********************************************************************
 FileName:     	Compressor.h
 Processors:		32 bit embedded Micro or 32 bit Windows Running PC
 Complier:  	Microchip PIC32 ; Panasonic MN103S ; .net Framework 3.5 CLI Select only One!!
 Company:	Arcelik-LG Klima AS  http://www.arcelik-lg.com.tr/
 Author :     ilker yagci
File Description:
		Final Compressor Frequency Generator Algorithm
 Change History:
  Rev   Date         Description
  1.0   05.04.2012   Initial release

 *********************************************************************/
#ifdef MANAGED_DOTNET_COMPILER
namespace ACIT_Stack{ // additional line for C++ debugging
#endif
void Determine_Offset_Error(void){
	switch(AirCon.SubMode){
			case STANDBYE:	default:		Auto_Correction = 0; // for cooling
					break;
			case COOL_DELAY: case COOL:
					Auto_Correction = Cooling_Compensation_Table[AirCon.Model]; // for cooling
					break;
			case HEAT_DELAY: case HEAT:	case DEFROST_0: case DEFROST_1: case DEFROST_2:case DEFROST_3:case DEFROST_4:
			case DEFROST_5:case DEFROST_6:case DEFROST_7:case DEFROST_8:
					Auto_Correction = Heating_Compensation_Table[AirCon.Model];
			break;
		}
/*		switch(AirCon.ExtraMode){
			case AUTOCHNG_DEHUM : Auto_Correction = Cooling_Compensation_Table[AirCon.Model];
			break;
			case AUTOCHNG_COOL : Auto_Correction = Auto_Compensation_Table[0] ;
			break;
			case AUTOCHNG_HEAT : Auto_Correction = Auto_Compensation_Table[1] ;
			break;
			default:
			break;
		}
*/

}
unsigned char GetMinMax_Step(unsigned char MinMax){
	 unsigned char i=0;
	 unsigned char *p =  &MinMax_Steps[0];
	switch(AirCon.SubMode){

				case DEFROST_0: case DEFROST_1: case DEFROST_2:case DEFROST_3:case DEFROST_4:case DEFROST_5:case DEFROST_6:case DEFROST_7:case DEFROST_8:
 									i =  (AirCon.Model*MINMAXPAIR+20);  //Model = MODEL-1;     // keep in mind MODEL is 1,2,3,4 for other tables we
       								break;
       						default:
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
void Sort_Reliable_Array(void){
	unsigned short Temp; unsigned char i; unsigned char k;unsigned char n=14;//unsigned char l=14;
	unsigned short *p1 = &Reliability.SortedSteps[0];
	unsigned short *p2 = &Reliability.SortedStepsNo[0];
	//Reliability.SortedStepsNo[]= {0,1,2,3,4,5,6,7,8,9,10,11,12,13};
			for(i=0;i<14;i++){
				if(Reliability.MaxEnable[i])  p1[i] = Reliability.Steps[i];   // if enabled get Step data
				else							   p1[i] = GetMinMax_Step(MAX);                      // if not get max value
				if( (AirCon.SubMode == HEAT_DELAY)  ||   (AirCon.SubMode == COOL_DELAY) ){
							p1[i] = GetMinMax_Step(MAX);
							Reliability.Steps[i] = GetMinMax_Step(MAX);
				}
				p2[i] = i+1;
			}
			for(k=0;k<13;k++){
					for(i=0;i<n-1;i++){
							if( p1[i] >p1[i+1]){
									Temp = p1[i+1];
									p1[i+1] = p1[i];
									p1[i] = Temp;
									Temp = p2[i+1];
									p2[i+1] = p2[i];
									p2[i] = Temp;
							}
					}
				n--;
			}
}
void Determine_Initial_Frequency(void){
	//Motor.Reliability.MaxStep = GetMinMax(Step ,MAX); // starting default values
	switch(AirCon.SubMode){
		case COOL:
		case HEAT:
			Sort_Reliable_Array();
			if(Motor.Cycle.OperatingMode == COMP_FIRST_START1) Motor.Reliability.MaxStep = (unsigned char)Reliability.Steps[ALIGN_MAX]; //Reliability.MaxStepAlign;
			else 	Motor.Reliability.MaxStep = (unsigned char)Reliability.SortedSteps[0]; // get the lowest value

			Motor.Reliability.MinStep = Reliability.MinStep[ACTUAL_MIN]; // get the current low value
			if( Motor.Reliability.MinStep> Motor.Reliability.MaxStep) Motor.Reliability.MaxStep = Motor.Reliability.MinStep;

	 		Motor.Final.TargetStep = Motor.Basic.TargetStep;

			if(Motor.Final.TargetStep > Motor.Reliability.MaxStep) Motor.Final.TargetStep = Motor.Reliability.MaxStep;
			if(Motor.Final.TargetStep < Motor.Reliability.MinStep) Motor.Final.TargetStep = Motor.Reliability.MinStep;
    	//	Motor.Initial.TargetFrequency = GetFrequency_From_StepFrequencyTable(Motor.Final.TargetStep);
    		Motor.Defrost.TargetStep = Motor.Final.TargetStep; // be ready for first defrost step
    		break;

		case DEFROST_0: case DEFROST_1: case DEFROST_2:case DEFROST_3:case DEFROST_4:case DEFROST_5:case DEFROST_6:case DEFROST_7:case DEFROST_8:
				Motor.Basic.TargetStep = Motor.Defrost.TargetStep;
				Motor.Final.TargetStep = Motor.Basic.TargetStep;
			break;
		 case STANDBYE :case COOL_DELAY:case HEAT_DELAY:
		 default:
				Motor.Final.TargetStep = 0;
			break;
	}
	Motor.Initial.TargetFrequency = GetFrequency_From_StepFrequencyTable(Motor.Final.TargetStep);

}

////////////////////////////////////OIL SUPPLY DECISION///////////////////////////////////////////////////////////////////////////////////////////////////////

void Determine_Oil_Supply(void){
			//RS 10.2	Oil feeding operation			// disable at defrost /  seer / cop /
	if(Motor.Cycle.OperatingMode != COMP_PI_MODE){
			Motor.OilSupply.Frequency = Motor.Initial.TargetFrequency;
			return;
	}
	switch(AirCon.OilSupplySubMode){
		case 0:
			if(Motor.Initial.TargetFrequency > Oil_SupplyTable[1]) {// less then 25 Hz?
					Motor.Timer.OilSupply = Oil_SupplyTable[0];//  if less then 1800 sec  then load timer with default value
			}
			Motor.OilSupply.Frequency = Motor.Initial.TargetFrequency;
			Motor.OilSupply.PreviousFrequency = Motor.Initial.TargetFrequency;
			//AirCon.AuxiliaryFunction = DefaultM;
			if(Motor.Timer.OilSupply==0){ // timeout ??
				   AirCon.AuxiliaryFunction = OilSupplyM;
					Motor.OilSupply.Frequency = Oil_SupplyTable[3];  // 30Hz    //  ===  Motor.OilSupply.Frequency  - Motor.Initial.TargetFrequency ;
					Motor.Timer.OilSupply      = Oil_SupplyTable[2]; // load new timer
					AirCon.OilSupplySubMode++;
			}
			break;
		case 1:
			if(Motor.Timer.OilSupply==0){
					Motor.OilSupply.Frequency = Motor.OilSupply.PreviousFrequency; // load prev frequency
				//	Motor.Initial.TargetFrequency  = Motor.OilSupply.PreviousFrequency; // load prev frequency
					Motor.Timer.OilSupply = Oil_SupplyTable[0]; // load prev timer as well
					AirCon.OilSupplySubMode=0;
					AirCon.AuxiliaryFunction = DefaultM;
			}
			break;
		default:
			break;
	}
}
void Determine_FinalCycle_Frequency(void){
		Motor.Initial.MinFrequency = GetFrequency_From_StepFrequencyTable(GetMinMax_Step(MIN));//GetFrequency_From_StepFrequencyTable(GetMinMax(Step ,MIN));
		Motor.Initial.MaxFrequency = GetFrequency_From_StepFrequencyTable(GetMinMax_Step(MAX));
		Motor.Basic.Frequency = Motor.OilSupply.Frequency; // from this or new 30Hz?
		if(Motor.Basic.Frequency < Motor.Initial.MinFrequency)Motor.Basic.Frequency = Motor.Initial.MinFrequency;
		if(Motor.Basic.Frequency > Motor.Initial.MaxFrequency)Motor.Basic.Frequency = Motor.Initial.MaxFrequency;
		Motor.Final.TargetFrequency = Motor.Basic.Frequency;
}
void Compressor_Stop(void){
		Motor.Initial.TargetFrequency = 0;
		Motor.Basic.Frequency = 0;
		Motor.OilSupply.Frequency =0;
		Motor.Final.TargetFrequency = 0;
		Motor.Cycle.OperatingMode = COMP_STOP;
}

void Compressor_Handle(void){ // decision of modes stop/heat/cool/ defost..  cycle/seer/copp/oilsupply/test/lqc  .....//  Function or code
	Determine_Offset_Error();
	Determine_Initial_Frequency();//16.03.2013 te kaldirildi
	Determine_FinalCycle_Frequency();
	Determine_Basic_TargetStep();
	Calculate_Start_Step();
	Determine_Oil_Supply();
	Reliability_Fill_Default(); // operates only at delay modes
	//Reliability_Check(); //16.03.2013 te kaldirildi
	switch(AirCon.MainMode){
		case StopM:	 Compressor_Stop();
			break;
		case CycleM:
			break;
		case SeerM:
			break;
		case CopM:
			break;
		case PreheatM:
			break;
		case LqcM:
			break;
		case TestM:
			break;
		default:break;
	}
	switch(AirCon.SubMode){
		case STANDBYE :   Reset_For_Standbye();				// will enter by indoor command	/ any error /
									 Compressor_Stop();
			break;
		case COOL_DELAY:
		case HEAT_DELAY:  Compressor_Stop();  break;
		case COOL:
				Reliability_Check();   // //16.03.2013 te eklendi
				switch(AirCon.MainMode){
					case CycleM:
					case SeerM:
					case CopM: 	 Compressor_Cycle();
					default:break;
				}
			break;
		case HEAT:
					Reliability_Check();   // //16.03.2013 te eklendi
					switch(AirCon.MainMode){
						case CycleM:// Defrost_MaintenanceCheck();
						case SeerM:
						case CopM: 	Compressor_Cycle();
						break;
					}

			break;
	//	case DEFROST_1: //Defrost_Comp_Step1();		// will enter by outdoor at heating decision
	//		break;
		default:break;
	}
	#ifdef MANAGED_DOTNET_COMPILER /*  File info to Pass GUI */
	//  String^  Filetime ;
	//char[24]  fer;



//	const 	char 	File1_Date[12] =  __DATE__;  // T0 Hyst T1 Hytst
//	const  char File1_Time[12] =  __TIME__;  // T0 Hyst T1 Hytst
//	const  char File1_Path[24] =  __FILE__;  // T0 Hyst T1 Hytst
//	const  char File1_Name[13] =  "Compressor.h";  // T0 Hyst T1 Hytst
//	int File1_Line =  __LINE__;  // T0 Hyst T1 Hytst



	//const  char File1_Path[12] =  __FILE__;  // T0 Hyst T1 Hytst
	//fer = __DATE__;
//	  "ddddddddbdh"  =__DATE__;
//	   Filetime = __DATE__;
//	   String ^ strC;

	#endif
}
 unsigned char  GetFrequency_From_StepFrequencyTable(unsigned char i){
	return Table_Step2Frequency[(i-1)*MAX_MODEL+(AirCon.Model)];
 }

void  Calculate_Start_Step(void){
	signed char *p1;signed char *p2;signed char  LineIndex=0;signed short error_temp;//unsigned char i;
	unsigned int  Tempint;
	Compile_Info.Month[0] = Date[0];
            switch(AirCon.SubMode){
            	case COOL:					// cooling   c# compatibility
				//	error_temp = Temperature.InAir - Temperature.InSet  + Cooling_Compensation_Table[AirCon.Model] +Auto_Correction ;
					error_temp =  Temperature.InAir - Temperature.InSet+Auto_Correction;
                	p1 = &Cooling_PControl_Table[0]; 		// pass adress of Heating Table to referance adress
                	p2 = &Cooling_Outdoor_TempCorFactor[0];  // pass adress of Heating Table to referance adress
                	break;
				case HEAT:  					// heating  c# compatibility
			//		error_temp =  Temperature.InSet - Temperature.InAir  + Heating_Compensation_Table[AirCon.Model]+ Auto_Correction;
					error_temp =  Temperature.InSet - Temperature.InAir  +  Auto_Correction;
    	            p1 = &Heating_PControl_Table[0]; 		// pass adress of Heating Table to referance adress
    	            p2 = &Heating_Outdoor_TempCorFactor[0]; // pass adress of Heating Table to referance adress
    	        	break;
					default: PI.error.CompStep=0; return;
            }
			// check min max limit use signed short temp value in order to not loose data -128 +127 limit
			if(error_temp > 100)  error_temp = 100; // max
			 if(error_temp < -100)error_temp = -100; // min

			 PI.error.CompStep  = (signed char)error_temp; ///  5.02.2012 modofied
			PI.error.CompStart =  PI.error.CompStep;

			for(LineIndex=0; LineIndex<6; LineIndex++){
                if((PI.error.CompStart/10)  >= p1[LineIndex * WIDTH])break; // find index at Table 4.3 or Table 4.4
			}
			Motor.Start.Calculated= p1[AirCon.Model +TEMP_COLUMN+ (LineIndex * WIDTH) ];// read from Table 4.3 or Table 4.4 and get Step target

			for(LineIndex=0; LineIndex<6; LineIndex++){			// find index at Table 4.5 or Table 4.6
                if ((Temperature.OutAir/REALTEMPFACTOR) < p2[LineIndex * WIDTH]) break;  // get correction coefficients from outdoor air
			}														// read from Table 4.5 or Table 4.6 and get outdoor coeffcients

			Tempint= (p2[AirCon.Model+TEMP_COLUMN + (LineIndex * WIDTH) ] * Motor.Start.Calculated)/10;
			Motor.Start.Calculated   = (signed char) Tempint ;  // multiply coefficient found from Table 4.5 or 4.6 datas are multiplied by 10
 }
// This is the heating and cooling operation with PI control loops
void Compressor_Cycle(void){  //DetermineCompressorStep
	unsigned char i;//signed char  LineIndex=0;//signed char *p2;signed char *p1;
	if(Motor.Cycle.OperatingMode ==  COMP_STOP)  Motor.Cycle.OperatingMode = COMP_FIRST_START1_INIT; // if is called means we have to start with first step for future use
	switch(Motor.Cycle.OperatingMode){    // compressor start steps
		case COMP_STOP : break;
		case COMP_FIRST_START1_INIT :  	//initial step to wait alignment of compressor just wait do nothing calcualte initial step
				i = 4;  // get align time
				Motor.Timer.Step = Starting_Operation_Table[AirCon.Model+i*MAX_MODEL];       //Table 4.8 ;  // take into account for BLDC motor alignment time estimate a timer value at least 2 sec
				i =2;
				Motor.Start.Step1 = Starting_Operation_Table[AirCon.Model + i*MAX_MODEL];    //8   //Table 4.8  get data

				Motor.Timer.OilSupply = Oil_SupplyTable[0];//  if less then 1800 sec  then load timer with default value
				Reliability.MinStep[1] = Motor.Start.Step1;
				if( Motor.Start.Step1  < Reliability.MinStep[0] ) Reliability.MinStep[1] = Reliability.MinStep[0] ; // if calculated min step is bigger then table value get the bigegst as min
				Reliability.Steps[ALIGN_MAX] = Motor.Start.Step1;
				Motor.Cycle.OperatingMode++;
			break;
		case COMP_FIRST_START1 :       // first compressor starting step to load time and step parameters to perform action comp f 4 way valve
				if(!Motor.Timer.Step)	Motor.Cycle.OperatingMode++;  // ALIGN WAIT MODE
			break;
		case COMP_FIRST_START2_INIT :       // first compressor starting step to load time and step parameters to perform action comp f 4 way valve
				i =0;
				Motor.Timer.Step =    Starting_Operation_Table[AirCon.Model+i*MAX_MODEL];       //Table 4.8
		        i=2;
				Motor.Start.Step1 = Starting_Operation_Table[AirCon.Model + i*MAX_MODEL];    //8   //Table 4.8  get data
				Motor.Cycle.OperatingMode++;
			break;
		case COMP_FIRST_START2 :       // first compressor starting step to load time and step parameters to perform action comp f 4 way valve
				if(!Motor.Timer.Step)	Motor.Cycle.OperatingMode++;  // FIRST mode
			break;
		case COMP_SEC_START_INIT:       // second compressor starting step to load time and step parameters to perform action
				i =1;
			   Motor.Timer.Step   = Starting_Operation_Table[AirCon.Model + i*MAX_MODEL];// Select f by reliabilty and other  SET TIMER
										//	if(Motor.Start.Calculated < Starting_Operation_Table[AirCon.Model + i*MAX_MODEL]) Motor.Start.Step2= Motor.Start.Calculated;
				 i =3;
			if(Motor.Start.Calculated < Starting_Operation_Table[AirCon.Model + i*MAX_MODEL]) Motor.Start.Step2= Motor.Start.Calculated;
			else                                 Motor.Start.Step2 = Starting_Operation_Table[AirCon.Model + i*MAX_MODEL];    //8   //Table 4.8  get data	get max

				Motor.Cycle.OperatingMode++;
			break;																	// table data use table data
		case COMP_SEC_START :       // first compressor starting step to load time and step parameters to perform action comp f 4 way valve
				if(!Motor.Timer.Step)	Motor.Cycle.OperatingMode++;  // second mode
			break;
		case COMP_PI_MODE_INIT:       // step still timer going on; if timeout perform next step
         //   TimerUc.FFT =0; // start ffd control for next time
				Motor.Timer.Step  = COMP_SAMPLE_TIME;
				Motor.Cycle.OperatingMode++;
				Temperature.InSetPrevious = Temperature.InSet; // prepare pid
			break;
		case COMP_PI_MODE:
				if(!Motor.Timer.Step){ ; //90 sec sampling
							Motor.Timer.Step=COMP_SAMPLE_TIME;
							if( Sense_Remote_Change() == 0 ){
										Find_PI_CompensationStep(); // PI step;
							}
				}

			break;
		case COMP_CONSTANT_MODE:	// FFT
				if(!Motor.Timer.Step){ ; //90 sec sampling should be equal or more then PI sample timer
						if(!Motor.Timer.FFT){
									if( Sense_Remote_Change() == 0 ){
											Motor.Cycle.OperatingMode = COMP_PI_MODE;
											Motor.Timer.Step = COMP_SAMPLE_TIME; // return to PI step
											PI.error.Remote = 0;
											Motor.Stable.Remote = 0;
								}
						}
				}
				break;
		default:break;
	}

}

signed char  Sense_Remote_Change(void){
	signed char *p; //signed char  LineIndex=0;signed char  ColumnIndex=0;

		switch(AirCon.SubMode){
      		 case COOL:
			  		PI.error.Remote = ( Temperature.InSetPrevious - Temperature.InSet )/REALTEMPFACTOR; //PI.error.Remote  22C
			  									//oldu - 25 C idi stepi artir cool icin e+  ise fark ta + // e_ ise step farki-
       			break;
			case HEAT:
			  		PI.error.Remote = (Temperature.InSet - Temperature.InSetPrevious)/REALTEMPFACTOR; //PI.error.Remote  22C
			  									//oldu - 25 C idi stepi artir heat  icin e+  ise fark ta + // e- ise step farki-
				break;
			 default: return 0; break;
		}
		p = &Common_Remote_Correction_Table[0];
		Motor.Stable.Remote = GetRemoteData(p);
		if(Motor.Stable.Remote){
			Motor.Timer.FFT = p[AirCon.Model+1];				// 1 is first colum it is used for temperature sample time
			Motor.Cycle.OperatingMode = COMP_CONSTANT_MODE;
		}
		Motor.Stable.FinalStep += Motor.Stable.Remote;
		Temperature.InSetPrevious = Temperature.InSet;
		return Motor.Stable.Remote; // if there isnt any change return 0 , if any return data
}

signed char GetRemoteData(signed char *p){
	unsigned char i;
		 for(i=1;i<3;i++){
				if(PI.error.Remote >= p[i*WIDTH])return p[AirCon.Model+TEMP_COLUMN + (i*WIDTH)];// p[6]   p[7]
		}
		for(i=4;i>2;i--){
				if(PI.error.Remote <= p[i*WIDTH])return p[AirCon.Model+TEMP_COLUMN + (i*WIDTH)];// p[18]   p[19]
		}
		return 0;
}

 void Find_PI_CompensationStep(void){
		 signed char *p; signed char  ColumnIndex=0; signed short error_temp;signed char  LineIndex=0;
			 switch(AirCon.SubMode){
      				 case COOL:										// cooling c# compitable
							//	error_temp =  (Temperature.InAir - Temperature.InSet)+ Cooling_Compensation_Table[AirCon.Model]+Auto_Correction; ;///REALTEMPFACTOR;;
								error_temp =  (Temperature.InAir - Temperature.InSet)+Auto_Correction; ;///REALTEMPFACTOR;;
	      					break;
					 case HEAT:  										// heating c# compitable
							//	error_temp =  (Temperature.InSet - Temperature.InAir)+ Heating_Compensation_Table[AirCon.Model]+Auto_Correction;///REALTEMPFACTOR
								error_temp =  (Temperature.InSet - Temperature.InAir)+Auto_Correction;///REALTEMPFACTOR
					default:  break;
			 }
	   p = &Common_PI_Correction_Table[0] ;
	// check min max limit use signed short temp value in order to not loose data -128 +127 limit
	  if(error_temp > 100)error_temp = 100; // max
	  if(error_temp < -100)error_temp = -100; // min
	  PI.error.CompStep = (signed char)error_temp;

      PI.errord.CompStep = (PI.error0.CompStep - PI.error.CompStep);

      for (ColumnIndex = 1; ColumnIndex < 5; ColumnIndex++)  {				// 6  is table width 1 is first line
            if ((PI.errord.CompStep*REALTEMPFACTOR ) <= p[ColumnIndex]) break;          	// 10 is coefficient to mach table //
            									//before it was <= but does not result doesn not fit with RS table  but with original code
	  }
      for (LineIndex = 1; LineIndex < 9; LineIndex++){                	//10  is table height 1 is first column
            if ((PI.error.CompStep ) >= p[LineIndex * 6]) break;           // 10 is coefficient to match table 6
      }
	Motor.Stable.Compensation = p[ColumnIndex + LineIndex * 6];          // 6  is table width
	Motor.Stable.FinalStep += Motor.Stable.Compensation;
	PI.error0.CompStep = PI.error.CompStep;			// update prev error at the end of sample time
}
 void Determine_Basic_TargetStep(void) {
		switch(AirCon.SubMode){
			case COOL:
			case HEAT:
				if(Motor.Cycle.OperatingMode != COMP_PI_MODE )Thermal_Cut_Disable();
				else									Thermal_Cut_Check();
					switch(Motor.Cycle.OperatingMode){    // compressor start steps
							case COMP_STOP :  	  Motor.Basic.TargetStep = 0;Thermal_Cut_Disable(); break;
							case COMP_FIRST_START1_INIT :
							case COMP_FIRST_START1 :    Motor.Basic.TargetStep = Motor.Start.Step1;	 break;
							case COMP_FIRST_START2_INIT :
							case COMP_FIRST_START2 :    Motor.Basic.TargetStep = Motor.Start.Step1;	break;
							case COMP_SEC_START_INIT:
							case COMP_SEC_START :   Motor.Basic.TargetStep = Motor.Start.Step2; break;
							case COMP_PI_MODE_INIT:  Motor.Stable.FinalStep = Motor.Start.Step2;
										Motor.Stable.Compensation =0;
										Motor.Stable.Remote = 0;
									//	PI.error.CompStep = 0;           // 5.02.2012 modified
										PI.error0.CompStep = PI.error.CompStep;
										Temperature.InSetPrevious = Temperature.InSet;
							break;
						case COMP_PI_MODE:
									if(Motor.Stable.FinalStep < GetMinMax_Step(MIN))Motor.Stable.FinalStep = GetMinMax_Step(MIN);
									if(Motor.Stable.FinalStep > GetMinMax_Step(MAX))Motor.Stable.FinalStep = GetMinMax_Step(MAX);
									Motor.Basic.TargetStep = Motor.Stable.FinalStep;

							break;
						case COMP_CONSTANT_MODE:
									if(Motor.Stable.FinalStep < GetMinMax_Step(MIN))Motor.Stable.FinalStep = GetMinMax_Step(MIN);
									if(Motor.Stable.FinalStep > GetMinMax_Step(MAX))Motor.Stable.FinalStep = GetMinMax_Step(MAX);
									Motor.Basic.TargetStep = Motor.Stable.FinalStep;
						default:break;
					}
					break;
			default:
			case STANDBYE :
			case COOL_DELAY:
			case HEAT_DELAY:  	Motor.Basic.TargetStep = 0;Thermal_Cut_Disable();
					break;
			case DEFROST_0:
					//	Motor.Defrost.TargetStep = Motor.Stable.FinalStep;

			case DEFROST_1: case DEFROST_2:case DEFROST_3:case DEFROST_4:case DEFROST_5:case DEFROST_6:case DEFROST_7:case DEFROST_8:

												Motor.Basic.TargetStep = Motor.Defrost.TargetStep;
												Thermal_Cut_Disable();
					break;
		}
 }

#ifdef MANAGED_DOTNET_COMPILER
}
#endif