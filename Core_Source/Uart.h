





void WriteString(const char *string){
    while(*string != '\0'){
        while(!UARTTransmitterIsReady(UART2));
		UARTSendDataByte(UART2, *string);
        string++;
        while(!UARTTransmissionHasCompleted(UART2));
    }
}
const unsigned char CharacterArray[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

void UART2PutChar( char ch ){
	while(!UARTTransmitterIsReady(UART2));
    U2TXREG = ch;
    #if !defined(__PIC32MX__)
        Nop();m
        Nop();
    #endif
    //while(U2STAbits.TRMT == 0);
    while(!UARTTransmissionHasCompleted(UART2));
}
void PutiIntData2Uart2(unsigned int toPrint){

    unsigned int printVar;
    printVar = toPrint;

    printVar = (toPrint>>12) & 0x0F;
    UART2PutChar( CharacterArray[printVar] );

    printVar = (toPrint>>8) & 0x0F;
    UART2PutChar( CharacterArray[printVar] );

    printVar = (toPrint>>4) & 0x0F;
    UART2PutChar( CharacterArray[printVar] );

    printVar = toPrint & 0x0F;
    UART2PutChar( CharacterArray[printVar] );
}
void UART1PutChar( char ch ){
	while(!UARTTransmitterIsReady(UART1));
    U1TXREG = ch;
    #if !defined(__PIC32MX__)
        Nop();m
        Nop();
    #endif
    //while(U2STAbits.TRMT == 0);
    while(!UARTTransmissionHasCompleted(UART1));
}
void PutiIntData2Uart1(unsigned int toPrint){

    unsigned int printVar;
    printVar = toPrint;

    printVar = (toPrint>>12) & 0x0F;
    UART1PutChar( CharacterArray[printVar] );

    printVar = (toPrint>>8) & 0x0F;
    UART1PutChar( CharacterArray[printVar] );

    printVar = (toPrint>>4) & 0x0F;
    UART1PutChar( CharacterArray[printVar] );

    printVar = toPrint & 0x0F;
    UART1PutChar( CharacterArray[printVar] );
}


void PutCharacter(const char character){
        while(!UARTTransmitterIsReady(UART2));
        UARTSendDataByte(UART2, character);
        while(!UARTTransmissionHasCompleted(UART2));
}
void PutCharacter1(const char character){
        while(!UARTTransmitterIsReady(UART1));
        UARTSendDataByte(UART1, character);
        while(!UARTTransmissionHasCompleted(UART1));
}

void Initialize_Uart_Interrupt_Common(void){
	//#if defined (__32MX460F512L__) || defined (__32MX360F512L__) || defined (__32MX795F512L__)
	#define GetSystemClock() (80000000L)
	//#elif defined (__32MX220F032D__) || defined (__32MX250F128D__)
	//#define GetSystemClock() (40000000L)
	//#endif
	#define	GetPeripheralClock()		(GetSystemClock()/(1 << OSCCONbits.PBDIV))
	#define	GetInstructionClock()		(GetSystemClock())

	SYSTEMConfig(GetSystemClock(), SYS_CFG_WAIT_STATES | SYS_CFG_PCACHE);

}


void Initialize_Uart2_Interrupt(void){


//	mPORTFClearBits(BIT_5); 		// Turn off RF5 on startup. U2TX RF5
    PORTClearBits(IOPORT_F, BIT_5 | BIT_6);
//	PORTSetPinsDigitalOut(IOPORT_F, BIT_5 | BIT_1);
	PORTSetPinsDigitalOut(IOPORT_F, BIT_5);
//	mPORTFSetPinsDigitalOut(BIT_5);	// Make RF5 as output.      U2TX RF5/ U1TX RF8 / U1RX RF2


	// could also use mPORTDSetPinsDigitalIn(BIT_6 | BIT_7);
   // PORTSetPinsDigitalIn(IOPORT_D, BIT_6 | BIT_7);

	// Explorer-16 uses UART2 to connect to the PC.
	// This initialization assumes 36MHz Fpb clock. If it changes,
	// you will have to modify baud rate initializer.
    UARTConfigure(UART2, UART_ENABLE_PINS_TX_RX_ONLY);
    UARTSetFifoMode(UART2, UART_INTERRUPT_ON_TX_NOT_FULL | UART_INTERRUPT_ON_RX_NOT_EMPTY);
    UARTSetLineControl(UART2, UART_DATA_SIZE_8_BITS | UART_PARITY_NONE | UART_STOP_BITS_1);
	//#define DESIRED_BAUDRATE    	(9600)      //The desired BaudRate
    UARTSetDataRate(UART2, GetPeripheralClock(), 9600); //The desired BaudRate
    UARTEnable(UART2, UART_ENABLE_FLAGS(UART_PERIPHERAL | UART_RX | UART_TX));

	// Configure UART2 RX Interrupt
	INTEnable(INT_SOURCE_UART_RX(UART2), INT_ENABLED);
    INTSetVectorPriority(INT_VECTOR_UART(UART2), INT_PRIORITY_LEVEL_2);
    INTSetVectorSubPriority(INT_VECTOR_UART(UART2), INT_SUB_PRIORITY_LEVEL_0);
	INTEnableSystemMultiVectoredInt();
}
void Initialize_Uart1_Interrupt(void){


//	mPORTFClearBits(BIT_5); 		// Turn off RF5 on startup. U2TX RF5
    PORTClearBits(IOPORT_F, BIT_8 | BIT_2);
//	PORTSetPinsDigitalOut(IOPORT_F, BIT_5 | BIT_1);
	PORTSetPinsDigitalOut(IOPORT_F, BIT_8);
//	mPORTFSetPinsDigitalOut(BIT_5);	// Make RF5 as output.      U2TX RF5/ U1TX RF8 / U1RX RF2


	// could also use mPORTDSetPinsDigitalIn(BIT_6 | BIT_7);
   // PORTSetPinsDigitalIn(IOPORT_D, BIT_6 | BIT_7);

	// Explorer-16 uses UART2 to connect to the PC.
	// This initialization assumes 36MHz Fpb clock. If it changes,
	// you will have to modify baud rate initializer.
    UARTConfigure(UART1, UART_ENABLE_PINS_TX_RX_ONLY);
    UARTSetFifoMode(UART1, UART_INTERRUPT_ON_TX_NOT_FULL | UART_INTERRUPT_ON_RX_NOT_EMPTY);
    UARTSetLineControl(UART1, UART_DATA_SIZE_8_BITS | UART_PARITY_NONE | UART_STOP_BITS_1);
	//#define DESIRED_BAUDRATE_1    	(9600)      //The desired BaudRate
    UARTSetDataRate(UART1, GetPeripheralClock(), 9600); //The desired BaudRate
    UARTEnable(UART1, UART_ENABLE_FLAGS(UART_PERIPHERAL | UART_RX | UART_TX));

	// Configure UART2 RX Interrupt
	INTEnable(INT_SOURCE_UART_RX(UART1), INT_ENABLED);
    INTSetVectorPriority(INT_VECTOR_UART(UART1), INT_PRIORITY_LEVEL_2);
    INTSetVectorSubPriority(INT_VECTOR_UART(UART1), INT_SUB_PRIORITY_LEVEL_1);
	INTEnableSystemMultiVectoredInt();
}
unsigned char Preamble_DataCounter;
unsigned int TempData;
void GetUartData4Outdoor(unsigned char data){

	switch (Preamble_DataCounter){
		case 0:
			if (data == 0XA0) Preamble_DataCounter++;
			else Preamble_DataCounter = 0;
		    break;
		case 1:
			if (data == 0XA0)	Preamble_DataCounter++;
			else Preamble_DataCounter = 0;
			break;
		case 2:
			if (data == 0XA0)	Preamble_DataCounter++;
			else Preamble_DataCounter == 0;
			break;
		case 3:
			if (data == 0XA0)	Preamble_DataCounter++;
			else Preamble_DataCounter = 0;
			break;
		case 4:
			TempData = data << 8;
			Preamble_DataCounter++;
			break;
		case 5:
			TempData += data ;
			Temperature.Discharge =  TempData;
			Preamble_DataCounter++;
			break;
		case 6:
			TempData = data << 8;
			Preamble_DataCounter++;
			break;
		case 7:
			TempData += data ;
			Temperature.OutMidPipe =  TempData;
			Preamble_DataCounter++;
			break;
		case 8:
			TempData = data << 8;
			Preamble_DataCounter++;
			break;
		case 9:
			TempData += data ;
			Temperature.OutAir =  TempData;
			Preamble_DataCounter = 0;
			break;

		default:
			Preamble_DataCounter = 0;
			break;
	}

}
unsigned char Preamble_In_DataCounter;
unsigned int TempDataIn;
void GetUartData4Indoor(unsigned char data){

	switch (Preamble_In_DataCounter){
		case 0:
			if (data == 0XA0) Preamble_In_DataCounter++;
			else Preamble_In_DataCounter = 0;
		    break;
		case 1:
			if (data == 0XA0)	Preamble_In_DataCounter++;
			else Preamble_In_DataCounter = 0;
			break;
		case 2:
			if (data == 0XA0)	Preamble_In_DataCounter++;
			else Preamble_In_DataCounter == 0;
			break;
		case 3:
			if (data == 0XA0)	Preamble_In_DataCounter++;
			else Preamble_In_DataCounter = 0;
			break;
		case 4:
			TempDataIn = data << 8;
			Preamble_In_DataCounter++;
			break;
		case 5:
			TempDataIn += data ;
			Temperature.InAir =  TempDataIn;
			Preamble_In_DataCounter++;
			break;
		case 6:
			TempDataIn = data << 8;
			Preamble_In_DataCounter++;
			break;
		case 7:
			TempDataIn += data ;
			Temperature.InMidPipe =  TempDataIn;
			Preamble_In_DataCounter = 0;
			break;
		default:
			Preamble_In_DataCounter = 0;
			break;
	}

}
void __ISR(_UART2_VECTOR, ipl2) IntUart2Handler(void){
	unsigned char data;
	// Is this an RX interrupt?
	if(INTGetFlag(INT_SOURCE_UART_RX(UART2))){
		// Clear the RX interrupt Fla
		data = UARTGetDataByte(UART2);
		INTClearFlag(INT_SOURCE_UART_RX(UART2));
         if(U2STAbits.OERR == 1){
             U2STAbits.OERR = 0;
			 Preamble_DataCounter == 0;
         }
         GetUartData4Outdoor(data);
		// Echo what we just received.

	//	PutCharacter(UARTGetDataByte(UART2));
		// Toggle LED to indicate UART activity
//			mLED_3_Toggle();
			mLED_3_Toggle();
	//		mLED_3_Toggle();
	//	mPORTFToggleBits(BIT_5); // ahhh
	}
	// We don't care about TX interrupt
//	if ( INTGetFlag(INT_SOURCE_UART_TX(UART2)) ){
//		INTClearFlag(INT_SOURCE_UART_TX(UART2));
//	}
}

void __ISR(_UART1_VECTOR, ipl2) IntUart1Handler(void){
	unsigned char data;
	// Is this an RX interrupt?
	if(INTGetFlag(INT_SOURCE_UART_RX(UART1))){
		// Clear the RX interrupt Fla
		data = UARTGetDataByte(UART1);
		INTClearFlag(INT_SOURCE_UART_RX(UART1));
         if(U1STAbits.OERR == 1){
             U1STAbits.OERR = 0;
         }
		// Echo what we just received.

	//	PutCharacter(UARTGetDataByte(UART2));
		// Toggle LED to indicate UART activity
			GetUartData4Indoor(data);
			mLED_3_Toggle();
		//	mLED_3_Toggle();
	//		mLED_3_Toggle();
	//	mPORTFToggleBits(BIT_5); // ahhh
	}
	// We don't care about TX interrupt
//	if ( INTGetFlag(INT_SOURCE_UART_TX(UART2)) ){
//		INTClearFlag(INT_SOURCE_UART_TX(UART2));
//	}
}