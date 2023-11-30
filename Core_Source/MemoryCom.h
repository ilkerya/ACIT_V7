
/********************************************************************
 FileName:     	MemoryCom.h
 Processors:		32 bit embedded Micro or 32 bit Windows Running PC
 Complier:  	Microchip PIC32 ; Panasonic MN103S ; .net Framework 3.5 CLI Select only One!!
 Company:	Arcelik-LG Klima AS  http://www.arcelik-lg.com.tr/
 Author :     ilker yagci
File Description:
		Memory Sharing  Algorithms for additional hardware. MemoryMap_Update() function holds beginning adress and total size of the relevant
		structure. The same file must be shared by all harware in order to keep consistency so version check ic included at the beginning to avoid
		usage of different versions.
 Change History:
  Rev   Date         Description
  1.0   05.04.2012   Initial release

 *********************************************************************/
#ifdef MANAGED_DOTNET_COMPILER
namespace ACIT_Stack{ // additional line for C++ debugging
#endif
/////////////////////////////////////// MEMORY MAP MODEL ////////////////////////////////////////

/*
#define READ_DATA  110 // 'n'
#define READ_MAPDATA  111 // 'o'
#define READ_TOTALMAP  112 // 'p'

#define WRITE_DATA  113 // 'q'
#define WRITE_MAPDATA  114 // 'r'
#define WRITE_TOTALMAP  115 // 's'
*/

unsigned char GetMemoryData(unsigned char* Adr){
				return *Adr; // returns the contents of  Adr pointer
			//	return CommunicationData //
}
void MemoryMap_Update(void){            // this map includes
				unsigned char i ;

				MemoryMap.Version = VERSION_NO;
				MemoryMap.MapSize = (unsigned int)sizeof(MemoryMap);

				MemoryMap.AirCon_Adr = (unsigned char*)&AirCon;
				MemoryMap.AirCon_Size = (unsigned char)sizeof(AirCon);

				MemoryMap.IndoorCommand_Adr = (unsigned char*)&IndoorCommand;
				MemoryMap.IndoorCommand_Size = (unsigned char)sizeof(IndoorCommand);

				MemoryMap.Motor_Adr = (unsigned char*)&Motor;
				MemoryMap.Motor_Size = (unsigned char)sizeof(Motor);

				MemoryMap.EEV_Adr = (unsigned char*)&EEV;
				MemoryMap.EEV_Size = (unsigned char)sizeof(EEV);

				MemoryMap.Fan_Adr = (unsigned char*)&Fan;
				MemoryMap.Fan_Size = (unsigned char)sizeof(Fan);

				MemoryMap.Temperature_Adr = (unsigned char*)&Temperature;
				MemoryMap.Temperature_Size = (unsigned char)sizeof(Temperature);

				MemoryMap.Reliability_Adr = (unsigned char*)&Reliability;
				MemoryMap.Reliability_Size = (unsigned char)sizeof(Reliability);

				MemoryMap.Defrost_Average_Adr = (unsigned char*)&Defrost_Average;
				MemoryMap.Defrost_Average_Size = (unsigned char)sizeof(Defrost_Average);

				MemoryMap.Hardware_Adr = (unsigned char*)&Hardware;
				MemoryMap.Hardware_Size = sizeof(Hardware);

				MemoryMap.PI_Adr = (unsigned char*)&PI;
				MemoryMap.PI_Size = (unsigned char)sizeof(PI);  //10
		//  Reliability Functions
				MemoryMap.Tc_Hold_Adr = (unsigned char*)&Tc_Hold	;
				MemoryMap.Tc_Hold_Size = (unsigned char)sizeof(Tc_Hold);
				MemoryMap.HS_Adr = (unsigned char*)&HS	;
				MemoryMap.HS_Size = (unsigned char)sizeof(HS);
				MemoryMap.Te_Hold_Adr = (unsigned char*)&Te_Hold	;
				MemoryMap.Te_Hold_Size = (unsigned char)sizeof(Te_Hold);
				MemoryMap.Td_Hold_Adr = (unsigned char*)&Td_Hold	;
				MemoryMap.Td_Hold_Size = (unsigned char)sizeof(Td_Hold);
				MemoryMap.Dew_Hold_Adr = (unsigned char*)&Dew_Hold	;
				MemoryMap.Dew_Hold_Size = (unsigned char)sizeof(Dew_Hold); //5
		//  Defrost Decision Functions
				MemoryMap.Defrost8111_Adr = (unsigned char*)&Defrost8111	;
				MemoryMap.Defrost8111_Size = (unsigned char)sizeof(Defrost8111);
				MemoryMap.Defrost8112_Adr = (unsigned char*)&Defrost8112	;
				MemoryMap.Defrost8112_Size = (unsigned char)sizeof(Defrost8112);
				MemoryMap.Defrost8113_1_Adr = (unsigned char*)&Defrost8113_1	;
				MemoryMap.Defrost8113_1_Size = (unsigned char)sizeof(Defrost8113_1);
				MemoryMap.Defrost8113_2_Adr = (unsigned char*)&Defrost8113_2	;
				MemoryMap.Defrost8113_2_Size = (unsigned char)sizeof(Defrost8113_2);
				MemoryMap.Defrost8114_Adr = (unsigned char*)&Defrost8114;
				MemoryMap.Defrost8114_Size = (unsigned char)sizeof(Defrost8114);
				MemoryMap.Defrost8115_Adr = (unsigned char*)&Defrost8115;
				MemoryMap.Defrost8115_Size = (unsigned char)sizeof(Defrost8115); //6

				MemoryMap.Compile_Info_Adr = (unsigned char*)&Compile_Info;
				MemoryMap.Compile_Info_Size = (unsigned char)sizeof(Compile_Info); //6
				/*
				// alternative to use buffer obsolute!
				unsigned char* pt[100];  // buffer of 100 array  quite big to handle
				unsigned char* ps[100];  // buffer of 100 array
				for(unsigned char i = 0; i  < MemoryMap.PI_Size;i++ ){
					pt[i] = (unsigned char*)(&TargetStruct)+i;
					ps[i] = MemoryMap.PI_Adr+i;  // MemoryMap.PI_Adr
				   *pt[i] = *ps[i];
				}
				*/
/*				for(unsigned char i = 0; i  < MemoryMap.PI_Size;i++ ){
						*((unsigned char*)(&TargetStruct)+i) = *(MemoryMap.PI_Adr+i);// copy memory to memory
				}
				for(unsigned char i = 0; i  < MemoryMap.PI_Size;i++ ){
						*((unsigned char*)(&PI)+i) = *(MemoryMap.PI_Adr+i);// copy memory
				}
*/
				for(i = 0; i  < MemoryMap.PI_Size;i++ ){
					//	copy data (content adress)  gathered by communicating then copy to content of the pointer which points to target struct until full size
					*((unsigned char*)(&PI)+i) = GetMemoryData(MemoryMap.PI_Adr+i);// write back data ti itself  which is pointed from table to
				}
				for( i = 0; i  < MemoryMap.PI_Size;i++ ){
					//	copy data (content adress)  gathered by communicating then copy to content of the pointer which points to target struct until full size
					*((unsigned char*)(&TargetStruct)+i) = GetMemoryData(MemoryMap.PI_Adr+i);// copy memory target = source // get source by communication
				}
}
void Update_Compiler_Info(){
 	Compile_Info.Month[0] = Date[0];
 	Compile_Info.Month[1] = Date[1];
 	Compile_Info.Month[2] = Date[2];
	Compile_Info.Date = (Date[4]-48)*10 + (Date[5]-48);
 	Compile_Info.Year = (Date[7]-48)*1000 + (Date[8]-48)*100 + (Date[9]-48)*10 + (Date[10]-48) ;
  	Compile_Info.Hour =   (Time[0]-48)*10 + (Time[1]-48);
  	Compile_Info.Minute = (Time[3]-48)*10 + (Time[4]-48);
  	Compile_Info.Second = (Time[6]-48)*10 + (Time[7]-48);
}


/** V A R I A B L E S ********************************************************/
#define NUMBER_DATA_PC2MICRO_SEND 14

#define READ_COMMAND_PC2MICRO_SEND 2
#define READ_BUFFER_SIZE 64
enum {
USB_DATA_00, USB_DATA_01, USB_DATA_02, USB_DATA_03, USB_DATA_04, USB_DATA_05, USB_DATA_06, USB_DATA_07, USB_DATA_08, USB_DATA_09,
USB_DATA_10, USB_DATA_11, USB_DATA_12, USB_DATA_13, USB_DATA_14, USB_DATA_15, USB_DATA_16, USB_DATA_17, USB_DATA_18, USB_DATA_19,
USB_DATA_20, USB_DATA_21, USB_DATA_22, USB_DATA_23, USB_DATA_24, USB_DATA_25, USB_DATA_26, USB_DATA_27, USB_DATA_28, USB_DATA_29,
USB_DATA_30, USB_DATA_31, USB_DATA_32, USB_DATA_33, USB_DATA_34, USB_DATA_35, USB_DATA_36, USB_DATA_37, USB_DATA_38, USB_DATA_39,
USB_DATA_40, USB_DATA_41, USB_DATA_42, USB_DATA_43, USB_DATA_44, USB_DATA_45, USB_DATA_46, USB_DATA_47, USB_DATA_48, USB_DATA_49,
USB_DATA_50, USB_DATA_51, NUMBER_DATA_MICRO2PC_SEND
};

//unsigned char USB_In_Buffer[64];
unsigned char USB_Micro_Receive_Buffer[READ_BUFFER_SIZE];

//enum {OUTDEG, SQRT_OUTDEG,
//UPLOAD_BW, SQRT_UPLOAD_BW};



BOOL stringPrinted;
volatile BOOL buttonPressed;
volatile char  buttonCount;

int shift = 0;
int NumberOfLines = 24;


#define READ_DATA 187
#define READ_MAP  123
#define READ_TOTALMAP  2

#define WRITE_DATA  199
#define WRITE_MAP   145
#define WRITE_TOTALMAP  3

#define READ_DATA_FRAME  34
#define WRITE_DATA_FRAME 81

#define ACK_ERR_FRAME 21

#define UNKOWN 0

#define  ACKNOWLEDGE 0xAAAA

struct{
	unsigned char Command;// 8 bits 	 host sends ->f
	struct{
		unsigned int Adress;// 32 bit    	 host sends ->
		unsigned short Count; // 16 bit      host counts
		unsigned short CRC; // 16 bit    	<- host sends/receives ->
		unsigned int Data;// 32 bit	    	<- host receives
		unsigned short Error; //16 bit  <- host sends/receives ->
	}Read;
	struct{
		unsigned int Adress;// 32 bit			host sends ->
		unsigned short Count; // 16 bit			host counts
		unsigned short CRC; // 16 bit			host sends ->
		unsigned int Data;// 32 bit				host sends ->
		unsigned short Error; //16 bit   <- host receives
	}Write;
	unsigned int Counter;
}Protocole;


#ifdef MANAGED_DOTNET_COMPILER
}
#endif

