
/********************************************************************
 FileName:     	EEV_Comp.h
 Processors:		32 bit embedded Micro or 32 bit Windows Running PC
 Complier:  	Microchip PIC32 ; Panasonic MN103S ; .net Framework 3.5 CLI Select only One!!
 Company:	Arcelik-LG Klima AS  http://www.arcelik-lg.com.tr/
 Author :     ilker yagci
File Description:
		Expansion Valve Compensation (Reliability) Algorithms
 Change History:
  Rev   Date         Description
  1.0   05.04.2012   Initial release

 *********************************************************************/
#ifdef MANAGED_DOTNET_COMPILER
namespace ACIT_Stack{ // additional line for C++ debugging
#endif

void EEV_InitCompensation_Check(void){
	unsigned char i;
	signed short *p = &Reliability.EEVStart[0];

	EEV.Start.TotalCompensation = 0;
	for(i=0; i < 6; i++){
		switch(i){   //
			case 0:  p[i] = Compressor_High_F_Compensation(i,EEV_START);break;		//  ikiside ayni 80 ustu +1
			case 1:  p[i] = Sleeping_Compensation(i,EEV_START);break;  //			// //  tum sleep  kompanzasyonlari 0
			case 2:  p[i] = OutdoorFan_Strong_Wind_Compensation(i,EEV_START);break;			  //  tum fan kompanzasyonlari 0
			case 3:  p[i] = IndoorFan_Weak_Wind_Compensation(i,EEV_START);break;                       //  tum fan kompanzasyonlari 0
			case 4:  p[i] = Dewing_Compensation_Start (i); break;            //   algoritmasi var bak  0 donuyor superheat ile algoritma ayni onda fazlaliklar var
			case 5:  p[i] = Hot_Start_Compensation(i);break;							//
			default:break;
		}
		EEV.Start.TotalCompensation += Reliability.EEVStart[i];
	}
}
void SuperHeat_Compensation_Check(void){
	unsigned char i;
	signed short *p = &Reliability.SuperHeat[0];

	EEV.SuperHeat.CompensationTd = 0;
	for(i=0; i < 8; i++){
		switch(i){   // returns difference pulse
			case 0:  p[i] = Compressor_High_F_Compensation(i,EEV_STABLE);break;		//    /  ikiside ayni 80 ustu +1
			case 1:  p[i] = Sleeping_Compensation(i,EEV_STABLE);break;  //			// // //  tum sleep  kompanzasyonlari 0
			case 2:  p[i] = OutdoorFan_Strong_Wind_Compensation(i,EEV_STABLE);break;			  //  tum fan kompanzasyonlari 0
			case 3:  p[i] = IndoorFan_Weak_Wind_Compensation(i,EEV_STABLE);break;                      //  tum fan kompanzasyonlari 0
			case 4:  p[i] = Dewing_Compensation_Stable (i); break;            //     -13 donuyor
			case 5:  p[i] = Cooling_Low_Compensation(i);break;	// out air 24C den dusukse -8 ekle
			case 6:  p[i] = Heating_Low_Compensation(i);break;	// out air-5C den dusukse 0 ekle 		 -1 yapalim
			case 7:  p[i] = Heating_High_Compensation(i);break;            //   sadece isitmada ve eev iknci baslangic adiminda ise ve kondenser 30C ustunde ise  0 donuyor
			default:break;
		}
		EEV.SuperHeat.CompensationTd += Reliability.SuperHeat[i];
	}
}

void Determine_SuperHeat_Temperature_Compensation(void){
	//unsigned int Temp = 0;  //unsigned int i; //signed short Temp2;
	//SuperHeatReliability_Check();
}

//Cooling Low Comp. (Tout Air)  //3
//Heating Low Comp.(Tout Air) //4
//dew //5


/*
//#define EEVTABLEWIDTH 2
signed char EEV_CompensationTable[]={ // common table
   //EEV           SUPERHEAT
   80,      1,       80,     1, //     Compressor_High_F_Compensation if more then 80 Hz add 1
   0,       0,        0,      0, //     Sleeping_Compensation
   0,       0,        0,      0, //OutdoorFan_Strong_Wind_Compensation
   0,       0,        0,      0, //IndoorFan_Weak_Wind_Compensation
   0,       0,        0,      0,	//Dewing_Compensation
   30,      1,       0,      0,	//Hot_Start_Compensation
};
*/
signed char EEV_StartCompensationTable[]={ // common table
   80,      1,        // 0    Compressor_High_F_Compensation if more then 80 Hz add 1
   0,       0,        //1     Sleeping_Compensation
   0,       0,         //2 OutdoorFan_Strong_Wind_Compensation
   20,       0,         //3 IndoorFan_Weak_Wind_Compensation  //Sb sasede 20 geliyor ama sonrasi step+1 mi -1 mi bilmiyoruz??
   0,       -1,       	//4 Dewing_Compensation
   30,      1,       	//5 Hot_Start_Compensation  InMidpipe
};
signed char EEV_StableCompensationTable[]={ // common table
   80,      1,        // 0    Compressor_High_F_Compensation if more then 80 Hz add 1
   0,       0,        // 1    Sleeping_Compensation
   0,       0,         //2 OutdoorFan_Strong_Wind_Compensation
   0,       0,         //3 IndoorFan_Weak_Wind_Compensation      SB saseye gore -2 var ama sinir ne??
   0,      -8,       	//4 Dewing_Compensation                   SB saseye gore modifiye
   24,      -4,       	//5 Cooling_Low_Compensation less  then   SB saseye gore modifiye
  -5,       -1,         //6 Heating_Low_Compensation less then
  21,        1,         //7 Heating_High_Compensation cond 1  OutAir
  25,        1,         //7 Heating_High_Compensation cond 2 InAir
};
/*
signed char EEV_DewCompensationTable[]={ // common table
// OutAir  InAir  Comp
     30,       0,       	-1,//Start
     24,       0,       -13,//Stable
};
*/
signed char  Dewing_Compensation_Stable (unsigned char i){	 // //  i=4
		signed char *p = &EEV_StableCompensationTable[0];   // first line;
		signed char *pdf = &Zone_Table_Dew[0] ;
		unsigned char k;
		if(AirCon.SubMode != COOL) return 0; // only if cooling
	// Check oudoor mins
		k = 7 ; // check mins
		if(Temperature.OutAir  < pdf[k*MAX_MODEL + AirCon.Model]  * REALTEMPFACTOR ) return 0;
		if(Temperature.InAir  < pdf[k*MAX_MODEL + AirCon.Model]  * REALTEMPFACTOR ) return 0;
		k = 8; // check maxs
		if(Temperature.OutAir  > pdf[k*MAX_MODEL + AirCon.Model]  * REALTEMPFACTOR ) return 0;
		if(Temperature.InAir  > pdf[k*MAX_MODEL + AirCon.Model]  * REALTEMPFACTOR ) return 0;
		return p[i*2+1]; // -1 // 0 // 1
}
signed char  Dewing_Compensation_Start  (unsigned char i){	 // //  i=4
		unsigned char k;
		signed char *p = &EEV_StartCompensationTable[0];
		signed char *pdf = &Zone_Table_Dew[0] ;


		if(AirCon.SubMode != COOL) return 0; // only if cooling
		// Check oudoor mins
		k = 7 ; // check mins
		if(Temperature.OutAir  < pdf[k*MAX_MODEL + AirCon.Model]  * REALTEMPFACTOR ) return 0;
		if(Temperature.InAir  < pdf[k*MAX_MODEL + AirCon.Model]  * REALTEMPFACTOR ) return 0;
		k = 8; // check maxs
		if(Temperature.OutAir  > pdf[k*MAX_MODEL + AirCon.Model]  * REALTEMPFACTOR ) return 0;
		if(Temperature.InAir  > pdf[k*MAX_MODEL + AirCon.Model]  * REALTEMPFACTOR ) return 0;
		return p[i*2+1]; // -1 // 0 // 1
}


signed char  Compressor_High_F_Compensation(unsigned char i,unsigned char Type){
	signed char *p ;
	if(Type == EEV_STABLE)  p = &EEV_StableCompensationTable[0];
	if(Type == EEV_START)  p = &EEV_StartCompensationTable[0];

	if(Motor.Basic.Frequency > p[i]) return p[i+1]; // -1 // 0 // 1 // over 80Hz return 1;
	else return 0;
}
signed char  Sleeping_Compensation(unsigned char i,unsigned char Type){
	signed char *p ;
	if(Type == EEV_STABLE)  p = &EEV_StableCompensationTable[0];
	if(Type == EEV_START)  p = &EEV_StartCompensationTable[0];

	if(!IndoorCommand.SleepMode)return 0;
	return p[i+1]; // -1 // 0 // 1
}
signed char  OutdoorFan_Strong_Wind_Compensation(unsigned char i,unsigned char Type){
	signed char *p ;
	if(Type == EEV_STABLE)  p = &EEV_StableCompensationTable[0];
	if(Type == EEV_START)  p = &EEV_StartCompensationTable[0];
	return p[i+1]; // -1 // 0 // 1
}
signed char  IndoorFan_Weak_Wind_Compensation(unsigned char i,unsigned char Type){
	signed char *p ;
	if(Type == EEV_STABLE)  p = &EEV_StableCompensationTable[0];
	if(Type == EEV_START)  p = &EEV_StartCompensationTable[0];
	return p[i+1]; // -1 // 0 // 1
}

signed char  Hot_Start_Compensation(unsigned char i){  // /  i=5
	signed char *p = &EEV_StartCompensationTable[0];
	if(AirCon.SubMode != HEAT) return 0;
	if( Temperature.InMidPipe > p[i*2] * REALTEMPFACTOR ){          // if inmid pipe more then 30C
		switch(EEV.CycleMode){
			case EEV_SEC_START_INIT:
			case EEV_SEC_START1:
			case EEV_SEC_START2:return p[i*2 +1];
			default : return 0;
		}
	}
	return 0;
}
signed char  Cooling_Low_Compensation(unsigned char i){ // //  i=5
	signed char *p = &EEV_StableCompensationTable[0];
	if(AirCon.SubMode != COOL)return 0;
	if(Temperature.OutAir  <= p[i*2] * REALTEMPFACTOR ) return p[i*2 +1];
		return 0;
}
signed char  Heating_Low_Compensation(unsigned char i){//  i=6
	signed char *p = &EEV_StableCompensationTable[0];
	if(AirCon.SubMode != HEAT)return 0;
	if(Temperature.OutAir  <= p[i*2] * REALTEMPFACTOR ) return p[i*2 +1];
	return 0;
}
//signed char Heating_High_CompensationTable[2]={
//OutAir  InAir     data
  //  21,        25   };  //     SuperHeat_High_Compensation
signed char  Heating_High_Compensation(unsigned char i){ // tested ok  i=7
	//signed char *p = &EEV_StableCompensationTable[0];
	//signed char *p2= &Heating_High_CompensationTable[0];
	signed char *p = &EEV_StableCompensationTable[0];
	if(AirCon.SubMode != HEAT)return 0;
	if((Temperature.OutAir >= p[i*2]* REALTEMPFACTOR ) & (Temperature.InAir >= p[( i+1)*2]* REALTEMPFACTOR))return p[i*2 +1];
	return 0;
}
signed char  Suction_Freezing_Prevention_Limit(unsigned char i){return i;}

#ifdef MANAGED_DOTNET_COMPILER
}
#endif
