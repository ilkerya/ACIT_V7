/* typedef  volatile union {
  volatile struct{
	       unsigned bit0 :1;
	       unsigned bit1 :1;
	       unsigned bit2 :1;
	       unsigned bit3 :1;
	       unsigned bit4 :1;
	       unsigned bit5 :1;
	       unsigned bit6 :1;
	       unsigned bit7 :1;
	} bits ;
	volatile unsigned char allbits  ;
} VARIABLE ;

VARIABLE CRCALL = 0;
#define CRC_0 			CRCALL.bits.bit0
#define CRC_1 			CRCALL.bits.bit1
#define CRC_2 			CRCALL.bits.bit2
#define CRC_3 			CRCALL.bits.bit3
#define CRC_4 			CRCALL.bits.bit4
#define CRC_5 			CRCALL.bits.bit5
#define CRC_6 			CRCALL.bits.bit6
#define CRC_7			CRCALL.bits.bit7
#define CRC_Chk			CRCALL.allbits
*/
 unsigned int CommACIT_Timeout;  // USB data receive timeout from ACIT for PIC32


unsigned int CalculateCrc(unsigned int Data1 ,unsigned int Data2,unsigned int Data3){
   unsigned int i;
   //volatile unsigned char k,i,t;
   i = Data1 ^ 0XAAAA;
   i ^= Data2;
   i ^= Data3;
	return i;
}


//short* ADRES; // same size with Temperatures
//unsigned int TEMP;


/*

void GetAdress4Host(unsigned char *Buffer){
	switch(Protocole.Command){
		case READ_DATA: case READ_MAP: case READ_TOTALMAP:
						Protocole.Read.Adress =   Buffer[0] << 24; //MSB
						Protocole.Read.Adress +=  Buffer[1] << 16;
						Protocole.Read.Adress +=  Buffer[2] << 8;
						Protocole.Read.Adress +=  Buffer[3];		//LSB
							//	Protocole.Read.Adress = (unsigned int) &MemoryMap.Temperature_Adr;
						switch(Protocole.Read.Adress){
							case ((unsigned int)&MemoryMap.Temperature_Adr - (unsigned int)&MemoryMap):
							//	ADRES = (unsigned int*)&Temperature;	// ok calisiyor
							//	TEMP  = (unsigned int)*MemoryMap.Temperature_Adr;	// ok calisiyor
							//	ADRES = (unsigned int*)&MemoryMap.Temperature_Adr;	// ok calisiyor

							//	TEMP  = (unsigned int)*MemoryMap.Temperature_Adr;	// ok calisiyor
								Protocole.Read.Adress  = (unsigned int)*MemoryMap.Temperature_Adr;	// ok calisiyor
								Protocole.Read.Adress = 234;

								ADRES = (short*)&Temperature.OutAir;  // ok
							//	ADRES = (short*)&MemoryMap.Temperature_Adr;  // olmadi struct adresi ve ilk eleman adresi farkli maalesef
							//	Protocole.Read.Adress = *ADRES;



							//	ADRES  = (unsigned int*)(&MemoryMap);	// ok calisiyor
							//	ADRES += 28;
							//	ADRES = (unsigned int*)*ADRES;
							//	TEMP = *((unsigned int*)*ADRES);;
							//	ADRES = (unsigned int*)(&MemoryMap);
							//	ADRES += 28;
							//	ADRES = (unsigned int)&ADRES;

							//	ADRES = (unsigned int*)(&MemoryMap+28);
							//	ADRES =(unsigned int*)((unsigned int)*(&MemoryMap+28));

							//	Protocole.Read.Adress = *((unsigned int*)(&MemoryMap+28));
								break;
							case ((int)&MemoryMap.Compile_Info_Adr - (int)&MemoryMap):
								ADRES = (short*)&Compile_Info;	// ok calisiyor
							break;


							default:ADRES = (short*)&MemoryMap;	// ok calisiyor
							break;
						}

		case WRITE_DATA:case WRITE_MAP:case WRITE_TOTALMAP:
						Protocole.Write.Adress =   Buffer[0] << 24; //MSB
						Protocole.Write.Adress +=  Buffer[1] << 16;
						Protocole.Write.Adress +=  Buffer[2] << 8;
						Protocole.Write.Adress +=  Buffer[3];		//LSB

					break;
		case UNKOWN:
		default: 	break;

	}

}
*/	//	ADRES = (unsigned int*)&Temperature;
//	Protocole.Read.Adress = (int)&MemoryMap + Protocole.Read.Adress;
//	switch(Protocole.Read.Adress){
//		case 28 : ADRES = (unsigned int*)&Temperature;
//		default: ADRES = (unsigned int*)&Motor;
	//	Protocole.Read.Adress =  (int)&MemoryMap.Temperature_Adr - (int)&MemoryMap; // Compile_Info_Ad
	//	Protocole.Read.Adress =  Protocole.Read.Adress + (int)&MemoryMap; // Compile_Info_Ad
	//	Protocole.Read.Adress = (int) (Protocole.Read.Adress + (int)&MemoryMap); // Compile_Info_Ad

	//	ADRES =  (int*)(*((int*)&MemoryMap+ 28));
//	}

/*
void GetCount4Host(unsigned char *Buffer){
	switch(Protocole.Command){
		case READ_DATA: case READ_MAP: case READ_TOTALMAP:
			Protocole.Read.Count =  Buffer[0] << 8;
			Protocole.Read.Count += Buffer[1];
			break;
		case WRITE_DATA:case WRITE_MAP:case WRITE_TOTALMAP:
			Protocole.Write.Count =  Buffer[0] << 8;
			Protocole.Write.Count += Buffer[1];
			break;
		default: 	break;
	}
}
void GetCRC4Host(unsigned char *Buffer){
	switch(Protocole.Command){
		case READ_DATA: case READ_MAP: case READ_TOTALMAP:
			Protocole.Read.CRC  = Buffer[0] << 8; //MSB
			Protocole.Read.CRC += Buffer[1];
			break;
		case WRITE_DATA:case WRITE_MAP:case WRITE_TOTALMAP:
			Protocole.Write.CRC  = Buffer[0] << 8; //MSB
			Protocole.Write.CRC += Buffer[1];
			break;
		default: 	break;
	}
}
*/
void WriteData2Host(unsigned char *Buffer){ // directly send back adr else than data PC ye yazma
//	int *ADR;
//	ADR = (unsigned int) &MemoryMap;// + Protocole.Read.Adress;
//	ADR += Protocole.Read.Adress;
//	Protocole.Read.Adress = MemoryMap.Version;
//	Protocole.Read.Adress = MemoryMap.Temperature_Size;
//	Protocole.Read.Adress = *MemoryMap.Temperature_Adr;
//	unsigned char Date[] = __DATE__;
//	unsigned char Time[] = __TIME__;
//	Protocole.Read.Adress = __LINE__;
//	Protocole.Read.Adress = Time[0] - 48;
//	Protocole.Read.Adress = Compile_Info.Minute;
//	Protocole.Read.Adress = (int)&MemoryMap.Compile_Info_Adr - (int)&MemoryMap;
//	Protocole.Read.Adress = (int)&MemoryMap - ;
//	Protocole.Read.Adress = ADR;
/*
	Protocole.Read.Adress = *ADRES;
//	Protocole.Read.Adress = *ADRES;
//	Protocole.Read.Adress = TEMP;
	Buffer[0]  = Protocole.Read.Adress >> 24;
	Buffer[1]  = Protocole.Read.Adress >> 16;
	Buffer[2]  = Protocole.Read.Adress >> 8;
	Buffer[3]  = Protocole.Read.Adress ;
//	Protocole.Read.Adress++;
	ADRES ++;
*/
/*
	ADR = (int*) Protocole.Read.Adress;
	//(int*)ADR;
	Buffer[0]  = (*ADR) >> 24;
	Buffer[1]  = *ADR >> 16;
	Buffer[2]  = *ADR >> 8;
	Buffer[3]  = *ADR ;
*/
//	ADR = (unsigned int)Protocole.Read.Adress;
//  Buffer[0]  = (*ADRES) >> 24;
////Buffer[1]  = (*ADRES) >> 16;
//	Buffer[2]  = (*ADRES) >> 8;
//	Buffer[3]  = (*ADRES) ;

//	ADRES++;
//	TEMP++;

//	Protocole.Read.Data =	*MemoryMap;// +  Protocole.Read.Adress);
//	Protocole.Read.Data =	 *((unsigned int*)Protocole.Read.Adress +(unsigned int*) MemoryMap);
//	ADR =	 *((unsigned int*)Protocole.Read.Adress + &MemoryMap.Version);
//	ADR = ((unsigned int*)&MemoryMap +  Protocole.Read.Adress);

//	Buffer[0]  = Protocole.Read.Data >> 24;
//	Buffer[1]  = Protocole.Read.Data >> 16;
//	Buffer[2]  = Protocole.Read.Data >> 8;
//	Buffer[3]  = Protocole.Read.Data ;
//	Protocole.Read.Adress++;



//	NumberOfLines = __LINE__ ;

}
/*
void 	WriteCRC2Host(unsigned char *Buffer){	// 4 //5 crc
	Buffer[0]  =   Protocole.Read.CRC >> 8;
	Buffer[1]  =   Protocole.Read.CRC;
}
void ReadData4Host(unsigned char *Buffer){
	if(Protocole.Read.Count){
		Protocole.Read.Data =  Buffer[0] << 24; //MSB
		Protocole.Read.Data += Buffer[1] << 16;
		Protocole.Read.Data += Buffer[2] << 8;
		Protocole.Read.Data += Buffer[3];
		Protocole.Read.Count--;
	}
	else Protocole.Command = UNKOWN; // reset commandif counter timeout
}
BOOL CRC_Verify(unsigned int Data, unsigned short CRC){

	Protocole.Read.Error = 45;
	return 1; // CORRECT
//	return 0;//   WRONG
}
void Send_Ack(unsigned char *Buffer){
		Buffer[0]  = 33;
		Buffer[1]  = 44;
}
*/
void GetCommand4Host(unsigned char *Buffer){
	switch(Buffer[0]){
		case READ_DATA:  	Protocole.Command = READ_DATA; 		break;
		case READ_MAP:  	Protocole.Command = READ_MAP; 		break;
		case READ_TOTALMAP: Protocole.Command = READ_TOTALMAP;  break;
		case WRITE_DATA:  	Protocole.Command = WRITE_DATA; 	break;
		case WRITE_MAP:  	Protocole.Command = WRITE_MAP; 		break;
		case WRITE_TOTALMAP:Protocole.Command = WRITE_TOTALMAP; break;
		default: Protocole.Command = UNKOWN; 	break;
	}
}
void Send_Data2PC(){
	unsigned char i;unsigned int CRC;
	unsigned char p[NUMBER_DATA_MICRO2PC_SEND];

	p[USB_DATA_00]  = 	Temperature.OutAir >> 8;
	p[USB_DATA_01]  = 	Temperature.OutAir;
	p[USB_DATA_02]  = 	Temperature.OutMidPipe >> 8;
	p[USB_DATA_03]  = 	Temperature.OutMidPipe;
	p[USB_DATA_04]  = 	Temperature.Discharge >> 8;
	p[USB_DATA_05]  = 	Temperature.Discharge;

	p[USB_DATA_06]  = 	Temperature.InAir >> 8;
	p[USB_DATA_07]  = 	Temperature.InAir;
	p[USB_DATA_08]  = 	Temperature.InMidPipe >> 8;
	p[USB_DATA_09]  = 	Temperature.InMidPipe;

	p[USB_DATA_10]  = 	Temperature.InSet >> 8;
	p[USB_DATA_11]  = 	Temperature.InSet;
	p[USB_DATA_12]  = 	Temperature.HeatSink >> 8;
	p[USB_DATA_13]  = 	Temperature.HeatSink;
	p[USB_DATA_14]  = 	Hardware.DCVoltage >> 8;
	p[USB_DATA_15]  = 	Hardware.DCVoltage;

	p[USB_DATA_16]  = 	Hardware.InpCurrent >> 8;
	p[USB_DATA_17]  = 	Hardware.InpCurrent;
	p[USB_DATA_18]  = 	Hardware.InpVoltage >> 8;
	p[USB_DATA_19]  = 	Hardware.InpVoltage;
	p[USB_DATA_20]  = 	Hardware.EEVPulse >> 8;
	p[USB_DATA_21]  = 	Hardware.EEVPulse;
	p[USB_DATA_22]  = 	Hardware.OutFanFreq >> 8;
	p[USB_DATA_23]  = 	Hardware.OutFanFreq;
	p[USB_DATA_24]  = 	Hardware.CompressorFreq;

	p[USB_DATA_25]  = 	Hardware.CompCurrent >> 8;
	p[USB_DATA_26]  = 	Hardware.CompCurrent;

	p[USB_DATA_27]  = 	Relays.OnOff;
	p[USB_DATA_28]  = 	Relays.Valve4Way;
	p[USB_DATA_29]  = 	Error.Compressor;
	p[USB_DATA_30]  = 	Error.PFC;
	p[USB_DATA_31]  = 	Error.OutdoorUnit;
	p[USB_DATA_32]  = 	Error.IndoorUnit;

	p[USB_DATA_33]  = Time[0]- '0';
	p[USB_DATA_34]  = Time[1]- '0';
	p[USB_DATA_35]  = Time[3]- '0';
	p[USB_DATA_36]  = Time[4]- '0';
	p[USB_DATA_37]  = Time[6]- '0';
	p[USB_DATA_38]  = Time[7]- '0';

	p[USB_DATA_39]  = Date[0]; // 3 karakter ay bilgisi
	p[USB_DATA_40]  = Date[1];
	p[USB_DATA_41]  = Date[2];

	p[USB_DATA_42]  = Date[4]- '0'; // 2 karakter gun
	p[USB_DATA_43]  = Date[5]- '0';

	p[USB_DATA_44]  = Date[9]- '0';   // 2012 sadece 12 ve 13 digitini gonder
	p[USB_DATA_45]  = Date[10]- '0';


	CommunicationUART.OutdoorError =  248;
	CommunicationUART.OutdoorState = 0XF0;
	CommunicationUART.IndoorError =  1248;
	CommunicationUART.IndoorState = 0X00;


	p[USB_DATA_46]  = (CommunicationUART.OutdoorError >> 8) +  CommunicationUART.OutdoorState;
	p[USB_DATA_47]  = CommunicationUART.OutdoorError;

	p[USB_DATA_48]  = (CommunicationUART.IndoorError >> 8) +  CommunicationUART.IndoorState;
	p[USB_DATA_49]  = CommunicationUART.IndoorError;


	CRC = 0XA0A0;
	for(i=0; i< USB_DATA_50; i++){
		CRC ^=  p[i];
	}
	p[USB_DATA_50]  = 	CRC >> 8;
	p[USB_DATA_51]  = 	CRC; // NUMBER_DATA_MICRO2PC_SEND+2

	putUSBUSART(p,NUMBER_DATA_MICRO2PC_SEND); // including 0. and 1. USB preamble chars


}
void Execute_Command_Frame(void){ // USB Data read from PC at Communication
	GetCommand4Host(&USB_Micro_Receive_Buffer[0]);

		switch(Protocole.Command){
			case READ_DATA: case READ_MAP: case READ_TOTALMAP:  Protocole.Command = READ_DATA_FRAME;  break;
			case WRITE_DATA:case WRITE_MAP:case WRITE_TOTALMAP: Protocole.Command = WRITE_DATA_FRAME;  break;
			case UNKOWN:
			default: 	break;
		}


}
/*  Main Communication Function called From The Main */
void Communication(void){ // data received from pc
	unsigned char  i;
	unsigned int CRC_Calculated;unsigned int Crc;
	unsigned char  *p = &USB_Micro_Receive_Buffer[0];

	switch(Protocole.Command){
		case READ_DATA_FRAME:  	// write to host data

				Send_Data2PC();
				Protocole.Command = UNKOWN;

			break;
		case WRITE_DATA_FRAME:  // read data from host

				CRC_Calculated  = 0XA0A0;
				for( i=0; i< 11; i++){
							CRC_Calculated ^=  p[i];
				}
				Crc =( p[11]*256 + p[12]);

				if(Crc != CRC_Calculated){

						//ErrorRate ++ ;
						//if (ErrorRate > 1000)ErrorRate = 1000;
				}
				else{
					CommACIT_Timeout = 0;

					Relays.Valve4Way 			 = p[1];
					Motor.Final.TargetFrequency =  p[2] ;
					EEV.Final.CycleTargetPulse  = p[3]*256  + p[4] ;
					Fan.FinalRpm 				= p[5]*256 + p[6] ;
					Fan.Indoor.FinalRpm 		= p[7]*256 + p[8] ;			// 3.4.2013 ek
					IndoorCommand.SwingYatay.Mode 		= p[9];
					IndoorCommand.SwingDikey.Mode 		= p[10];
				}

			Protocole.Command = UNKOWN;
			break;
		//case ACK_ERR_FRAME:
		//	break;
		default: Protocole.Command = UNKOWN;
	//		Execute_Command_Frame();

			break;
	}
}

/*
void Communication(void){
	unsigned char  i;
	unsigned int CRC_Calculated;unsigned int Crc;
	unsigned char  *p = &USB_Micro_Receive_Buffer[0];

	switch(Protocole.Command){
		case READ_DATA_FRAME:  	// write to host data

				Send_Data2PC();
				Protocole.Command = UNKOWN;

			break;
		case WRITE_DATA_FRAME:  // read data from host

				CRC_Calculated  = 0XA0A0;
				for( i=0; i< 7; i++){
							CRC_Calculated ^=  p[i];
				}
				Crc =( p[7]*256 + p[8]);

				if(Crc != CRC_Calculated){
						//ErrorRate ++ ;
						//if (ErrorRate > 1000)ErrorRate = 1000;
				}
				else{
					Relays.Valve4Way 			 = p[1];
					Motor.Final.TargetFrequency =  p[2] ;
					EEV.Final.CycleTargetPulse  = p[3]*256  + p[4] ;
					Fan.FinalRpm 				= p[5]*256 + p[6] ;
					Fan.Indoor.FinalRpm 		= p[7]*256 + p[8] ;			// 3.4.2013 ek
				}

			Protocole.Command = UNKOWN;
			break;
		//case ACK_ERR_FRAME:
		//	break;
		default: Protocole.Command = UNKOWN;
	//		Execute_Command_Frame();

			break;
	}
}

*/
