
/********************************************************************
 FileName:     	Errors.h
 Processors:		32 bit embedded Micro or 32 bit Windows Running PC
 Complier:  	Microchip PIC32 ; Panasonic MN103S ; .net Framework 3.5 CLI Select only One!!
 Company:	Arcelik-LG Klima AS  http://www.arcelik-lg.com.tr/
 Author :     ilker yagci
File Description:
		Error Determining Algorithms , not being used yet, needed when a hardware is connected
 Change History:
  Rev   Date         Description
  1.0   05.04.2012   Initial release

 *********************************************************************/
#ifdef MANAGED_DOTNET_COMPILER
namespace ACIT_Stack{ // additional line for C++ debugging
#endif

unsigned char ErrorTable[] ={
					// Error No   SetResetInterval(min)   Count         Final error Timeout (min)
							60,				3,				 1,				60,
							21,				3,				10,				60,
							22,				3,				10,				60,
							23,				3,				10,				60,
							24,				3,				10,				60,
							25,				3,				 1,				60,
							26,				3,				10,				60,
							27,				3,				10,				60,
							28,				3,				10,				60,
							29,				3,				10,				60,
							32,				3,				10,				60,
							40,				3,				10,				60,
							41,				3,				 1,				60,
							44,				3,				 1,				60,
							45,				3, 				 1,				60,
							46,				3,		 		 1,				60,
							48,				3,				 1,				60,
							51,				3,				 1,				60,
							53,				3,				 1,				60,
							61,				3,				10,				60,
							62,				3,				10,				60,
							65,				3,				 1,				60,
							67,				3,				10,				60,
							70,				3,				10,				60,
							73,				3,				10,				60};

void Error_Handle(void){
		switch(AirCon.SubMode){
			default:
			case STANDBYE :case COOL_DELAY:case HEAT_DELAY:return;
					break;
			case HEAT:	case COOL:	case DEFROST_0: case DEFROST_1: case DEFROST_2:case DEFROST_3:case DEFROST_4:case DEFROST_5:
			case DEFROST_6:case DEFROST_7:case DEFROST_8: // goon
					break;
	}

	switch(Error.Compressor) {
		case 0: break;
		default: ErrorPosition();if(Error.Comp_Enabled == OFF) Error.Comp_Enabled = ON;
		break;

	}
	switch(Error.PFC) {
		case 0: break;
		default: ErrorPosition();if(Error.PFC_Enabled == OFF)  Error.PFC_Enabled = ON;
		break;

	}
	switch(Error.OutdoorUnit) {
		case 0: break;
		default: ErrorPosition();if(Error.OU_Enabled == OFF)  Error.OU_Enabled = ON;
		break;

	}
	switch(Error.IndoorUnit) {
		case 0: break;
		default: ErrorPosition();if(Error.IU_Enabled == OFF)  Error.IU_Enabled = ON;
		break;

	}
}
void ErrorPosition(void){
		switch(AirCon.SubMode){
			default:
			case STANDBYE :
					break;
			case COOL:	AirCon.SubMode = COOL_DELAY;AirCon.Timer.Defrost = 0;	AirCon.Timer.TotalHeating=0;
						AirCon.Timer.HeatDelay = START_DELAY;     AirCon.Timer.CoolDelay = START_DELAY;
					break;
			case HEAT:	AirCon.SubMode = HEAT_DELAY; AirCon.Timer.TotalHeating=0;
						AirCon.Timer.HeatDelay = START_DELAY;     AirCon.Timer.CoolDelay = START_DELAY;
					break;
			case COOL_DELAY:
					break;
			case HEAT_DELAY:
					break;
			case DEFROST_0: case DEFROST_1: case DEFROST_2:case DEFROST_3:case DEFROST_4:case DEFROST_5:case DEFROST_6:case DEFROST_7:case DEFROST_8:
					AirCon.SubMode = HEAT_DELAY;AirCon.Timer.TotalHeating=0;
					AirCon.Timer.HeatDelay = START_DELAY;     AirCon.Timer.CoolDelay = START_DELAY;
					break;
		}

}
void Errorclear(void){
	//if(Error.Comp_Enabled == OFF) Error.Comp_Enabled = OFF;
	//if(Error.PFC_Enabled == OFF)  Error.PFC_Enabled = ON
	//if(Error.OU_Enabled == OFF)  Error.OU_Enabled = ON
	//if(Error.IU_Enabled == OFF)  Error.IU_Enabled = ON
}



#ifdef MANAGED_DOTNET_COMPILER
}
#endif
