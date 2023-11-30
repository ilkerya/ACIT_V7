
/********************************************************************
 FileName:     	Defrost.h
 Processors:		32 bit embedded Micro or 32 bit Windows Running PC
 Complier:  	Microchip PIC32 ; Panasonic MN103S ; .net Framework 3.5 CLI Select only One!!
 Company:	Arcelik-LG Klima AS  http://www.arcelik-lg.com.tr/
 Author :     ilker yagci
File Description:
		Defrost Mode Operation Algorithms
 Change History:
  Rev   Date         Description
  1.0   05.04.2012   Initial release

 *********************************************************************/
#ifdef MANAGED_DOTNET_COMPILER
namespace ACIT_Stack{ // additional line for C++ debugging
#endif
void Prepare_Defrost_EscapeTimers(void){
		unsigned char i;
		for(i=0; i < 6; i++){
			Defrost_EscapeTimers[i]  = Defrost_Escape[i*4+2];
		}
}

void Finalize_Defrost_Comp_Operation(void){
		unsigned int i;
		for(i=0;i<=15;i++){
			Ram_Temperature_Average[i] = 0;
		}
		Defrost8111.FinalMatch    = OFF;
		Defrost8112.FinalMatch    = OFF;
		Defrost8113_1.FinalMatch    = OFF;
		Defrost8113_2.FinalMatch    = OFF;
		Defrost8114.FinalMatch      = OFF;


		Defrost8111.Match_Timeout    = OFF;
		Defrost8112.Match_Timeout    = OFF;
		Defrost8113_1.Match_Timeout    = OFF;
		Defrost8113_2.Match_Timeout    = OFF;
		Defrost8114.Match_Timeout      = OFF;


		Defrost8111.Match_Maintenance    = OFF;
		Defrost8112.Match_Maintenance    = OFF;
		Defrost8113_1.Match_Maintenance    = OFF;
		Defrost8113_2.Match_Maintenance    = OFF;
		Defrost8114.Match_Maintenance      = OFF;

		Defrost8111.Match_Temperature1    = OFF;
		Defrost8112.Match_Temperature1    = OFF;
		Defrost8113_1.Match_Temperature1    = OFF;
		Defrost8113_2.Match_Temperature1    = OFF;
		Defrost8114.Match_Temperature1      = OFF;

		Defrost8111.Match_Temperature2    = OFF;
		Defrost8112.Match_Temperature2    = OFF;
		Defrost8113_1.Match_Temperature2    = OFF;
		Defrost8113_2.Match_Temperature2    = OFF;
		Defrost8114.Match_Temperature2      = OFF;


		AirCon.SubModePrevious = AirCon.SubMode; // store existing mode as previous means defost end
		AirCon.SubMode = HEAT; // return to heating
		Motor.Cycle.OperatingMode = COMP_FIRST_START1_INIT; // let the motor initialize
		Fan.Indoor.HotStart = ON;
		Defrost_Start();
}
void CompStep_Defrost_Update(unsigned char Line){
		AirCon.Timer.Defrost     = Defrost_TimeComponent[Line*DEF_TABLE_WIDTH]; //



		if(Defrost_TimeComponent[Line*DEF_TABLE_WIDTH+1] != 64) Motor.Defrost.TargetStep = Defrost_TimeComponent[Line*DEF_TABLE_WIDTH+1];
		else 													Motor.Defrost.TargetStep = 0 ;
																//Motor.Defrost.TargetStep = Motor.Final.TargetStep ;
		if(Defrost_TimeComponent[Line*DEF_TABLE_WIDTH+3] != 64) Fan.DefrostStep           = Defrost_TimeComponent[Line*DEF_TABLE_WIDTH+3];
		else 													Fan.DefrostStep           = Fan.FinalStep;
		if(Defrost_TimeComponent[Line*DEF_TABLE_WIDTH+4] != 64) Fan.Indoor.DefrostStep    = Defrost_TimeComponent[Line*DEF_TABLE_WIDTH+4];
		else													Fan.Indoor.DefrostStep    = Fan.Indoor.FinalStep;
	//	AirCon.SubModePrevious = AirCon.SubMode; // store existing mode as previous
	//	AirCon.SubMode++; // switch to  next step
}
void EEVPulse_Defrost_Update(unsigned char Line){
			Line = 0;
}

void Defrost_Operation_Handle(void){
	unsigned char flag_first_heat_operation=0;//unsigned char  i;// 	unsigned char  Line;
	if(AirCon.Timer.Defrost) return; // be sure enter once whenever time out occurs.
					// load next step time value before switching to the next step run below expresion one time while switching to next step;
	switch(AirCon.SubMode){
		case DEFROST_0:
				/*
			//	if(Defrost_CompOnTable[0] == ON){
					if (!(Motor.Final.ActualStep == Defrost_CompOnTable[1] || Motor.Final.ActualStep == Defrost_CompOnTable[2] || Motor.Final.ActualStep ==
							MinMax_Steps[(AirCon.Model)*MINMAXPAIR+MINMAXTOTCOL])) CompStep_Defrost_Update(DEF_TABLE_STEP0+1); 			//on mode
				}
			//	else	CompStep_Defrost_Update(LINEDEFSTEP1);  // off mode   // load 2. defrost step values
				Prepare_Defrost_EscapeTimers();
				*/
				CompStep_Defrost_Update(0);
			break; //
		case DEFROST_1:	//if(Defrost_CompOnTable[0] == ON)
			CompStep_Defrost_Update(1);//Line = LINEDEFSTEP2+1;			//on mode
										//	else CompStep_Defrost_Update(LINEDEFSTEP2);				// off mode   // load 2. defrost step values
			break; //
		case DEFROST_2:	CompStep_Defrost_Update(2);  // first 1 min	  // load 3.1 defrost step values
			break; //
		case DEFROST_3:
					CompStep_Defrost_Update(3);
		/*
			switch(AirCon.MainMode){   // load 3.2 defrost step values
				case SeerM: CompStep_Defrost_Update(LINEDEFSTEP3+3);
																			//Defrost_GetFinalCompres_SeerFrequency(i);
					break;
				case CycleM:


					if(flag_first_heat_operation==0){  // flag_first_heat_operation ?
						flag_first_heat_operation = 1;
						CompStep_Defrost_Update(LINEDEFSTEP3+2);
					}
					else  CompStep_Defrost_Update(LINEDEFSTEP3+1);//Line = LINEDEFSTEP3+1; // 15 MIN

				default:
					*/
			break;
		case DEFROST_4:	// if (TimerUc.DefRemain) 	Update_Defrost_Values(LINEDEFSTEP4); 	 // 10 sec
											//		AirCon.Timer.Defrost = Defrost_TimeStep_Table[LINEDEFSTEP4*DEFTOTCOL]; //
												//	Motor.Defrost.TargetStep = Defrost_TimeStep_Table[Line*DEFTOTCOL+COLUMN2];
													// do not load target step
											//		AirCon.SubModePrevious = AirCon.SubMode; // store existing mode as previous
											//		AirCon.SubMode++; // switch to  next step
				CompStep_Defrost_Update(4);
			// sadece defrost 3.1 de (60 dk) eger defrost escape sensor uygun ise 4.1 e atlanir. 4.1 deki sure ise 10 sn.
			//ancak bu bolumde  3.1 deki kalan sureyi dikkate alarak3.1 deki ayni adimi devam ettirmek gerekiyor. mesela 55 sn
			// gecti 60-55= 5 sn kaldi o zaman 10sn ilk 5 sn si 3.1 deki adima devam
			// kalan surede 4.1 deki adim devam edecek kalan sure 10 sn cok ise tum adim 3.1 deki gibi aynen olacak.
			//  bir anlamda ne olursa olsun en az  10 sn boyunca 3.1 deki adima mutlak devam ettir anlamina geliyor.


			break; //
		case DEFROST_5:	CompStep_Defrost_Update(5); // 10 sec		 // load 4_2. defrost step values
			break; //
		case DEFROST_6:	CompStep_Defrost_Update(6);//
			break; //
		case DEFROST_7:		CompStep_Defrost_Update(7); //Line = 15; // 6. step;
			break; //
		case DEFROST_8:	Finalize_Defrost_Comp_Operation();
		default: 						break; //
		}
}
void Def_Escape_RemainAdd(void){
	/*
		if(AirCon.SubMode != DEFROST_4_1) return;
		if (TimerUc.DefRemain == 0)Motor.Defrost.TargetStep = Defrost_TimeStep_Table[LINEDEFSTEP4+1*DEFTOTCOL+COLUMN2]; // 19
		else										Motor.Defrost.TargetStep = Defrost_TimeStep_Table[(LINEDEFSTEP4)*DEFTOTCOL+COLUMN2];
		if(TimerUc.DefRemain) TimerUc.DefRemain--;  // call every 1 sec after above function
		*/
}

void Defrost_SensorEscape_Time_Handle(void){ // call 1 second
	// timer will be available only at modes defined from the table if none match then load escape timer with default value
	unsigned char i; unsigned char *p  = &Defrost_EscapeTimers[0];
	for(i=0; i < 6; i++){
		if(AirCon.SubMode == Defrost_Escape[i*4] ){//  defrost sensor escape condition
			if(Temperature.OutMidPipe >=  Defrost_Escape[i*4+1]) { ;//TimerUc.DefrostEscape = 0; //TimerUc.DefrostEscape--; //
																		//if temperature more then the one from table decrease timer
						if(p[i])	p[i]--;
			}
			else {  p[i]  = Defrost_Escape[i*4+2]; TimerUc.DefRemain = 0; }//  load with default value
			if(( AirCon.Timer.Defrost != 0 ) && (p[i] == 0 ) ) {  // TimerUc.DefrostEscape
					TimerUc.DefRemain = AirCon.Timer.Defrost; // now we will use escape timer as
					Prepare_Defrost_EscapeTimers();
					AirCon.Timer.Defrost = 0;  // reset timer in order to let timer function to switch to next step
					AirCon.SubMode =  Defrost_Escape[i*4+3]; // switch to  mode indicated at table
			}
		}
	}
	//TimerUc.DefRemain = 333;
}

void Defrost_GetFinalCompres_Step(unsigned char Line){
	//Motor.Defrost.TargetStep = Defrost_TimeStep_Table[Line*DEFTOTCOL+COLUMN2];
	Line =0;
}
void Defrost_GetFinalCompres_SeerFrequency(unsigned int Line){
//	Motor.SEER.TargetFrequency = Defrost_TimeStep_Table[(Line+1)*DEFTOTCOL+COLUMN2];	// frequencies are 1 step ahead of seer cycle
}

/*
void Defrost_Comp_Step4(void){
	unsigned int i=0;
	return;
	// first 10 sec
	if(TimerUc.Defrost <= Defrost_TimeStep_Table[LINEDEFSTEP4]){
		if(TimerUc.DefrostEscape <= Defrost_TimeStep_Table[LINEDEFSTEP3]){ // from 3rd step did we came from sensor escape?
																			//if yes take into account or remaining timer
				Motor.Defrost.TargetStep = Defrost_TimeStep_Table[LINEDEFSTEP3+1];	// load variables of 3rd step until the remaining time
		}
		else{
			switch(AirCon.MainMode){
				case SeerM: i =LINEDEFSTEP4+2 ; // 3. line is seer mode line
						     Defrost_GetFinalCompres_SeerFrequency(i);
					break;
				case CycleM:i = LINEDEFSTEP4+1;
				default:
					break;
			}
			Defrost_GetFinalCompres_Step(i);
		}
	}
	else {
		i = LINEDEFSTEP4+4;
		Defrost_GetFinalCompres_Step(i);
		Defrost_Step_Timeout_Check(i);
	}
}
*/

void Defrost_Escape_Detection(void){
/*	unsigned int j;unsigned int i;
	unsigned char* p = &Defrost_Escape[0];
	return;
	switch(AirCon.SubMode){
		case StandbyeM:
		case CoolingM:
		case HeatingM:
		case DefMStep1:
		//case DefMStep4:  at this step d0 not clear timer will be used as referance
		case DefMStep5:
		case DefMStep6: // not any action
				TimerUc.DefrostEscape = 0;
				return;
		case DefMStep2: j = 0; // first line if step2
				break;
		case DefMStep3: j = 2; // first line if step3
				break;
	}
	for(i=j;i<j+2; i++){
		if(Temperature.OutMidPipe >= (signed short)p[i*3]){
			if(TimerUc.DefrostEscape >= p[i*3+1]){
				TimerUc.Defrost = 0; // prepare for step change
				AirCon.SubModePrevious = AirCon.SubMode; // store existing mode as previous means defost end
				AirCon.SubMode = p[i*3+2];// get next mode 2->3 // 3->4
				if(AirCon.SubMode == DefMStep3)TimerUc.DefrostEscape = 0; // clear at  defrost 3. step as
												// do not clear at 4. step timer will be used as referance at 4. th step
			}
		}
		if(Temperature.OutMidPipe <  p[i*3]) TimerUc.DefrostEscape = 0;
	}
	*/
}
#ifdef MANAGED_DOTNET_COMPILER
}
#endif
