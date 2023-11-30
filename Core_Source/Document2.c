

			//	unsigned int S;
//			Form_EEV^ F = gcnew Form_EEV();
		//	F->MdiParent = this;
	//		F->MdiParent = this;
	//		Form^ F2 = this->ActiveMdiChild;

		//	if( != NULL)
		//	F2->Text = "ddd";
//		Form^  Form_EEV = this->ActiveMdiChild;
	//	F->textBox_MaxSuperHeat->Text = "55";
//		F->Activate();

	//	if(tempChild != NULL){


static String^ nl  =  Environment::NewLine;

private: System::Void toolStripMenuItem1_Click(System::Object^  sender, System::EventArgs^  e) {
		//	 this->toolStripMenuItem1->Text = "yardim" ;
		//	 this->toolStripMenuItem1->Container =

			//		F->textBox1->Text = "sds" ;
					//F->label1->Text = "AA";
				//	F->setter("H");
			// alttatki gecici devre disi
					Abt^ F = gcnew Abt;
			//		F->Visible = true;
					F->ShowDialog();
			//		this->notifyIcon1->Text = "vvvvvvvvv";
				//	Application::Run(gcnew About());
			//		F->MdiParent = this;
					//			//		this->Activate();
				//					F->label_denemeAbout->Text = "sss";
	//	About^ F = gcnew About();
	//	F->Show();

  // Form2* newMDIChild = new Form2();
    // Tells our new child window
    // what is our parent window.
   // newMDIChild->MdiParent = this;
	//	F->MdiParent = this;
	//	F->MdiChildren = this;

    // Shows the new form.
    // Don't confuse this with ShowDialog!
   // newMDIChild->Show();
	//	F->label_denemeAbout->Text = " ";

	//  textBox_MaxSuperHeat
//		F->label_denemeAbout->Text = "ss";

   //   this->helpLabel1->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
  //    this->helpLabel->Location = System::Drawing::Point( 8, 80 );
   //   this->helpLabel->Size = System::Drawing::Size( 272, 72 );
   //   this->helpLabel->Text = "Click the Help button in the title bar, then click a control to see a Help tooltip for the control.  Click on a control and press F1 to invoke the Help system with a sample Help file.";
//			  this->helpProvider1->SetShowHelp( this->textBox_help, true );
//			 this->helpProvider1->SetHelpString( this->textBox_help, "Enter the zip code here." );
		//	 this->helpProvider1->SetShowHelp( this->textBox_help, true);
		 }

this->textBox_Remote_PicTable->BackColor= PanelColour_State();


this->label_ACPIC_In_Air->ForeColor = PanelColour_State();
this->label_ACPIC_In_Evap->ForeColor = PanelColour_State();


this->label_ACPIC_In_Evap->Text = "Evaporator Temp." // sogutma
this->label_ACPIC_Out_cond->Text = "Condenser Temp." // sogutma

Environment::UserName

Environment::MachineName // LG_ILKER
		 if( (Environment::MachineName  ==  "LG_ILKER") ||    (Environment::MachineName  ==  "A00070040") ){
				Security_Mode = false;
		 }

this->label_ACPIC_In_Evap->Text = "Condenser Temp." // isitma
this->label_ACPIC_Out_cond->Text = "Evaporator Temp." // isitma




label_ACPIC_In_Air   // ic ortam
label_ACPIC_In_Evap // ic evaporator


label_ACPIC_Out_cond  // dis condenser
label_ACPIC_Out_air  // dis ortam
label_ACPIC_Out_Comp  // compressor



compressorToolStripMenuItem
reliabilityToolStripMenuItem

expansionValveToolStripMenuItem
fanToolStripMenuItem

defrostToolStripMenuItem

chartsGraphicsToolStripMenuItem

chartsPlotsToolStripMenuItem  //log menu only

scriptCommunicationToolStripMenuItem




				this->textBox_MotorAnimHz->BackColor= PanelColour_State();

progressBar1
ForeColor



textBox_MotorAnimHz

Compressor 134 Hz




private: System::Void computerToolStripMenuItem1_Click(System::Object^  sender, System::EventArgs^  e) {
			 		CInfo^ F = gcnew CInfo;
					F->BackColor = PanelColour_State();
					F->Show();
		 }


private: System::Void systemToolStripMenuItem1_Click(System::Object^  sender, System::EventArgs^  e) {
			 		Info^ F = gcnew Info;
					F->BackColor = PanelColour_State();
					F->Show();
		 }


		textbox->Text = File_Sources_View;

String^ File_Sources_View(void){
			String^  path = FileName; = "D:\\ACIT_SIM\\Core_Source\\Errors.h";


			if (! (File::Exists( path )) ){
					try {
						//	FileStream^ fs = File::Create( path );
						//	delete fs;
					}
						catch ( IOException^  ) { return;}
				}
				// create a strem reader
			else {return "file not found";}
			StreamReader^ sr  ;
			try {sr = gcnew StreamReader( path );}
			catch ( IOException^  ) {return;}



		//	String^ DataFile;
		//	DataFile = LOG_ReadStream(sr,path); // read data from file
			// read  stremreader

		try{if ( sr != nullptr ) {     // hata dosya aciksa kitleniyor burada
						return sr->ReadToEnd();}
			}
		catch ( IOException^  ) {return "streamread_false";};

		return sr;
		//textbox->Text = sr;

			// delete stremreader

			try{ if(sr != nullptr)	delete sr;}
			catch ( IOException^ ) {return "streamdelete_false";}
		}


/*
public:String^  LOG_ReadStream(StreamReader^ Sr , String ^ path){
		try{
				if ( Sr != nullptr ) {     // hata dosya aciksa kitleniyor burada
						return Sr->ReadToEnd();
				}
			}
		catch ( IOException^  ) {GUI.Log.Error = true;return "false";}
		return "false";
}

*/

// when connects disable all
radio_10Slow_Mode
radio_10xSpeed_Mode
radio_1xSpeed_Mode   // default
radio_100xSpeed_Mode
button_Play          // play mode default

AirCon.SubMode = STANDBYE;
AirCon.MainMode = StopM;

//once connected and once disabled
// play mode default
// inverter stop mode/ / standbye mode default



IndoorCommand.


button_OnOff  // AC Mode button

button_Power_Reset





USB_txtDataReceived
textBox_Temp_Received // burdaki uste sonra iptal


plot_Component_Chart // iptal





computerToolStripMenuItem1_Click_1


private: System::Void computerToolStripMenuItem1_Click(System::Object^  sender, System::EventArgs^  e) {
			 		CInfo^ F = gcnew CInfo;
					F->BackColor = PanelColour_State();
					F->Show();
		 }





private: System::Void reaToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 			  File_View ^F = gcnew File_View;
			 F->BackColor = PanelColour_State();
			 F->Text = "Log File : " + Original_Log_File;
		 F->richTextBox1->Location =System::Drawing::Point(12 , 8);
		 F->richTextBox1->Size = System::Drawing::Size(1184, 684);
		 F->Size = System::Drawing::Size(1216, 732);
		 F->Show();
		 if ( File::Exists(Original_Log_File )) {
					try {
							F->richTextBox1->LoadFile(Original_Log_File, RichTextBoxStreamType::PlainText);
					}
					catch ( IOException^  ) {
							  F->richTextBox1->Text = Original_Log_File +"  open..   Close the file and try again !!";
							return;
				}
		}
		 else {   F->richTextBox1->Text =  Original_Log_File +"  not found !! ";}
	//	 F->richTextBox1->TabIndex
}

|

				 Log_Directory = "D:\\ACIT_SIM\\LOG";
				 Original_Log_File  = "data.csv";




				 checkBox_Rel_Min_01
				 checkBox_Rel_Min_02


				 textBox_Comp_RelibMIn

				 Motor.Reliability.MinStep
				  Motor.Reliability.MaxStep



Connection Speed Type





^String Log_Connection_Type ( void){
	^String str;
	switch(IndoorCommand.Mode){
		default:
		case REMOTE_OFF: 		str = "AC Off" break;  // 18-30
		case REMOTE_COOL: 		str = "Cooling" break;   // 18-30
		case REMOTE_AUTOCHNG:   str = "Autochange" break;
		case REMOTE_DEHUMIDIF:  str = "Dehum.=id" break;
		case REMOTE_HEAT: 		str = "Heating" break;       // 16-30
		case REMOTE_FAN_SPEED:  str = "Fan Speed" break;
	}
	str += ","
	if(USB_Conncetion_OK){	str += "USB Conn.";return str;}
 	if(!GUI.View.Play){
			if(this->radio_1xSpeed_Mode->Checked == true)str += "Play Regular";
			if(this->radio_10Slow_Mode->Checked == true) str +=   "Play Slow";
			if(this->radio_10xSpeed_Mode->Checked == true) str += "Play x10";
			if(this->radio_100xSpeed_Mode->Checked == true)str += "Play x100";
	}
	else  str +="Pause";
	return str;
}


	delegate void USB_SetTextCallback(String^ text);


panel_Compressor_Defrost   // Loc 136, 794
panel_Compressor_Constant // Loc 80, 482

panel_Compressor_THCut // genel panel	// Loc 32, 706

textBox_Comp_SetTemp04   = "< " + COMMON_Show_ShortSigned_Numbers(ThermalCut_Table[0]*-1) + " ?";
textBox_error_ThermalCut = "< " + COMMON_Show_ShortSigned_Numbers(ThermalCut_Table[2]*-1) + " ?";

textBox_CompTHCut1Timeout =  IndoorCommand.ThermalCut.TimerShort.ToString() + " sec";
textBox_CompTHCut2Timeout  = IndoorCommand.ThermalCut.TimerLong.ToString() + " sec";


		if(this->checkBox_ThermalCutEnable->Checked) {IndoorCommand.ThermalCut.EnableLong =ON; IndoorCommand.ThermalCut.EnableShort =ON;}
		else 					     {IndoorCommand.ThermalCut.EnableLong =OFF;IndoorCommand.ThermalCut.EnableShort =OFF;}
		String^ MyString;String^  MyString2;
		if(IndoorCommand.ThermalCut.On){MyString = "ON";MyString2 = "Compressor On" +nl + "AC Operation On"}
		else						  { MyString = "OFF"; MyString2 = "Compressor Off" +nl + "AC Operation Off";}
		this->textBox_ThermalCut_Info->Text =MyString;
		textBox_Compressor_TCCutINfo->Text = MyString2;


//textBox_ThermalCut_Info








//textBox_ThermCutLong  // eskisi
//textBox_ThermCutShort  //

void PANEL_Form_ThermalCut_Update(void){   // IndoorCommand.ThermalCut.TimerShort
		this->textBox_ThermCutLong->Text = 	"Thermal Cut 1"+/* +\r\nMax error" +  Show_ShortSigned_Numbers(High ) +*/
																					"\r\nMin error"  +COMMON_Show_ShortSigned_Numbers(ThermalCut_Table[0]*-1 )   + "\r\n\r\nTimeout:" +
																																		IndoorCommand.ThermalCut.TimerShort.ToString() + "sec";
		this->textBox_ThermCutShort->Text ="Thermal Cut 2"+/*\r\nMax error" + Show_ShortSigned_Numbers(High)  */
																					"\r\nMin error" +COMMON_Show_ShortSigned_Numbers(ThermalCut_Table[2]*-1)   + "\r\n\r\nTimeout:" +
																																		IndoorCommand.ThermalCut.TimerLong.ToString() + "sec";
		if(this->checkBox_ThermalCutEnable->Checked) {IndoorCommand.ThermalCut.EnableLong =ON; IndoorCommand.ThermalCut.EnableShort =ON;}
		else 					     {IndoorCommand.ThermalCut.EnableLong =OFF;IndoorCommand.ThermalCut.EnableShort =OFF;}
		String^ MyString;
		if(IndoorCommand.ThermalCut.On){MyString = "ON";/*this->checkBox_ThermalCutEnable->Checked = false;*/}
					else MyString = "OFF";
		this->textBox_ThermalCut_Info->Text =MyString;
		this->textBox_error_ThermalCut->Text = COMMON_Show_ShortSigned_Numbers(PI.error.CompStep );
}

//		this->textBox_ThermCutLong->Text = 	"Thermal Cut 1"+/* +\r\nMax error" +  Show_ShortSigned_Numbers(High ) +*/
//																					"\r\nMin error"  +COMMON_Show_ShortSigned_Numbers(ThermalCut_Table[0]*-1 )   + "\r\n\r\nTimeout:" +
//																																		IndoorCommand.ThermalCut.TimerShort.ToString() + "sec";
//		this->textBox_ThermCutShort->Text ="Thermal Cut 2"+/*\r\nMax error" + Show_ShortSigned_Numbers(High)  */
/*																					"\r\nMin error" +COMMON_Show_ShortSigned_Numbers(ThermalCut_Table[2]*-1)   + "\r\n\r\nTimeout:" +
																																		IndoorCommand.ThermalCut.TimerLong.ToString() + "sec";
		if(this->checkBox_ThermalCutEnable->Checked) {IndoorCommand.ThermalCut.EnableLong =ON; IndoorCommand.ThermalCut.EnableShort =ON;}
		else 					     {IndoorCommand.ThermalCut.EnableLong =OFF;IndoorCommand.ThermalCut.EnableShort =OFF;}
		String^ MyString;
		if(IndoorCommand.ThermalCut.On){MyString = "ON";/*this->checkBox_ThermalCutEnable->Checked = false;*/}
/*					else MyString = "OFF";
		this->textBox_ThermalCut_Info->Text =MyString;
		this->textBox_error_ThermalCut->Text = COMMON_Show_ShortSigned_Numbers(PI.error.CompStep );
*/



textBox_CompTHCut1
textBox_CompTHCut2


textBox_Comp_SetTemp04 // bunu sildik





checkBox_Chrt_HeatSink  = TEMP_HEATSINK
numericUpDownHeatsinkTemparature TEMP_HEATSINK

if(this->checkBox_Chrt_HeatSink->Checked  )this->plot_Total_Chart->Add(stepBalance11);	//heatsink



// left boxes
this->textBox_Remote_PicTable->BackColor = COL_TEMP_INSET;
this->numericUpDown_InAir1->BackColor = COL_TEMP_INAIR;
this->numericUpDown_InMidPip_01->BackColor = COL_TEMP_INPIPE;

this->numericUpDown_OutAir1->BackColor = COL_TEMP_OUTAIR;
this->numericUpDown_OutMidpipe_01->BackColor = COL_TEMP_OUTPIPE;
this->numericUpDown_Temperature_Discharge->BackColor = COL_TEMP_DISCHARGE;

this->numericUpDownHeatsinkTemparature->BackColor = COL_TEMP_HEATSINK;
this->numericUpDown_Inp_Voltage->BackColor = COL_INP_VOLT;
this->numericUpDown_Current->BackColor = COL_INP_CURRENT;





static GUI.Log.InitTime;




toolStripMenuItem_LogTime // system time i buna ekle




this->startTimeToolStripMenuItem


this->stopTimeToolStripMenuItem




 void SCREEN_Capture_Automatic_Loop(void){


 void SCREEN_Capture_Loop(void){



	 		 static int CaptureCounter;
		 static int CaptureAutomaticCounter;


					unsigned int Base15Minutes;
					bool Flag_Base10mSec;
					bool Flag_Base50mSec;
					bool Flag_Base100mSec;
					bool Flag_Base1Sec;
					bool Flag_Base10Sec;


panel_AC_Pic_vertical
pictureBox23

panel_Charts





void GUI_ANIM_Panel_AC_Picture_Vertical(void){
			if(!Security_Mode){
				this->panel_AC_Pic_vertical->Width = ACPICPANEL_WIDTH;
				this->panel_AC_Pic_vertical->Height = ACPICPANEL_HEIGHT;
					this->panel_AC_Pic_vertical->Location = Point(ACPICPANEL_X_START,ACPICPANEL_Y_START);//Point(0,126);
					this->panel_AC_Pic_vertical->Visible = true;
			}
			else {
			//	this->panel_AC_Pic_vertical->Location = Point(ACPICPANEL_SECURITY_X_START,ACPICPANEL_SECURITY_Y_START);//Point(0,126);
				this->panel_AC_Pic_vertical->Visible = false;
			}
}
void GUI_ANIM_Panel_MotorAnim(void){
			if(!Security_Mode){
								this->panel_EEV_MOTOR_SHOW->Width = ANIMPANEL_WIDTH;
				this->panel_EEV_MOTOR_SHOW->Height = ANIMPANEL_HEIGHT;
					this->panel_EEV_MOTOR_SHOW->Location = Point(ANIMPANEL_X_START,ANIMPANEL_Y_START);  //Point(1296,567);
				this->panel_EEV_MOTOR_SHOW->Visible =true;
			}
			else {
				//	this->panel_EEV_MOTOR_SHOW->Location = Point(ANIMPANEL_X_SECURITY_START,ANIMPANEL_Y_SECURITY_START);  //Point(1296,567);
				this->panel_EEV_MOTOR_SHOW->Visible =false;
			}
}


	  if (GUI.View.Panel_Counter == LOGGING_PANEL){
			this->panel_AC_Pic_vertical->Visible = true;
			this->pictureBox23->Visible = true;

	  }
	  else{
			this->panel_AC_Pic_vertical->Visible = false;
			this->pictureBox23->Visible = false;
	  }

	this->textBox_MotorAnimHz->Visible = true;
	this->textBox_FanAnimHz->Visible = true;
	this->progressBar1->Visible = true;
	this->textBox_EEV_Pulse->Visible = true;


	this->textBox_MotorAnimHz->Visible = false;
	this->textBox_FanAnimHz->Visible = false;
	this->progressBar1->Visible = false;
	this->textBox_EEV_Pulse->Visible = false;


	panel_Charts



panel_EEV_MOTOR_SHOW
charts //
// COL_TEMP_HEATSINK;

this->checkBox_Chrt_Freq->BackColor = COL_MOTOR_FREQ;
this->checkBox_Chrt_Pulse->BackColor = COL_EEV_PULSE;
this->checkBox_Chrt_Fan->BackColor = COL_FAN_RPM;
this->checkBox_Chrt_Current->BackColor = COL_INP_CURRENT;
this->checkBox_Chrt_Voltage->BackColor = COL_INP_VOLT;
this->checkBox_Chrt_COP->BackColor = COL_COP;
this->checkBox_Chrt_error->BackColor = COL_ERROR;
this->checkBox_Chrt_TInAir->BackColor = COL_TEMP_INAIR;
this->checkBox_Chrt_TInSet->BackColor = COL_TEMP_INSET;
this->checkBox_Chrt_TInPipe->BackColor = COL_TEMP_INPIPE;
this->checkBox_Chrt_TDisch->BackColor = COL_TEMP_DISCHARGE;
this->checkBox_Chrt_TOutPipe->BackColor = COL_TEMP_OUTPIPE;
this->checkBox_Chrt_TOutAir->BackColor = COL_TEMP_OUTAIR;
this->checkBox_Chrt_HeatSink->BackColor = COL_TEMP_HEATSINK;



		// Freq
	this->textBox_eevStart_Freq->BackColor = COL_MOTOR_FREQ;
	this->textBox_eevStable_Freq->BackColor = COL_MOTOR_FREQ;
	this->textBox_eevComp_Freq->BackColor = COL_MOTOR_FREQ;
		// Indoor mid Pipe
	this->textBox_eev_InAir01->BackColor = COL_TEMP_INAIR;
	this->textBox_eev_InAir02->BackColor = COL_TEMP_INAIR;
	this->textBox_eev_InAir03->BackColor = COL_TEMP_INAIR;
	this->textBox_eev_StartInAir->BackColor = COL_TEMP_INAIR;
	this->textBox_eev_Stable_InAir->BackColor = COL_TEMP_INAIR;

		// Outdoor Air
	this->textBox_eev_Stable_OutAir->BackColor = COL_TEMP_OUTAIR;
	this->textBox_eev_StartOutAir->BackColor = COL_TEMP_OUTAIR;
	this->textBox_eev_OutAir01->BackColor = COL_TEMP_OUTAIR;
	this->textBox_eev_OutAir02->BackColor = COL_TEMP_OUTAIR;
	this->textBox_eev_OutAir03->BackColor = COL_TEMP_OUTAIR;
	this->textBox_eev_OutAir04->BackColor = COL_TEMP_OUTAIR;
	this->textBox_eev_OutAir05->BackColor = COL_TEMP_OUTAIR;

		// Outdoor mid Pipe
	this->textBox_eev_outMidpipe->BackColor = COL_TEMP_OUTPIPE;

		// Indoor mid Pipe
	this->textBox_eev_HotStartinMidpipe->BackColor = COL_TEMP_INPIPE;
	this->textBox_eev_inMidpipe->BackColor = COL_TEMP_INPIPE;


	// Discharge
	this->textBox_eev_Stable_DiscTemp->BackColor = COL_TEMP_DISCHARGE;






	this->numericUpDownHeatsinkTemparature
	this->numericUpDown_Inp_Voltage
	this->numericUpDown_Current



Hardware.InpCurrent
Hardware.InpVoltage
Hardware.DCVoltage




textBox_Comp_BasicStep

textBox_Comp_RelibMAx // atla

textBox_Comp_RelibMIn  // atla

textBox_Comp_FinalTStep



//silinecekler

textBox_Reliability_Group
textBox_ReliabilityMin_Group

label_compMaxStepArrow  //sil
label_compMaxStepArrow2
label_compMaxStepArrow3

label_compMinStepArrow  // sil
label_compMinStepArrow2
label_compMinStepArrow3

label_MinstepYazi
label_MaxstepYazi



textBox_ReliabilityMin_Group

textBox_MotorOilSupply
textBox_OilSup_Timer

67, 189
textBox_Comp_BasicStep
panel_Compressor_Defrost



textBox_COOL3MINSTART




AirCon.SubModePrevious




pictureBox_ClockAnim
240, 1

textBox_Comp_SampleTimer
203, 10

textBox_Comp_FFDTimer


pictureBox_ClockAnim

pictureBox_FFTClockAnim
294 1

panel_Compressor_Constant
pictureBox14


label_PID_arrow02
label_FFT_arrow01



toolStripMenuItem_Indoor

INDOOR_PANEL

GRAPHICS_PANEL


private: System::Void viewToolStripMenuItem7_Click(System::Object^  sender, System::EventArgs^  e) {
			 GUI.View.SlidePlay = false;
			 GUI.View.Panel_Counter = GRAPHICS_PANEL;
			  PANEL_Panel_Set();
		 }
 private: System::Void  viewtoolStripMenuItem9_Click(System::Object^  sender, System::EventArgs^  e) {
			 GUI.View.SlidePlay = false;
			 GUI.View.Panel_Counter = INDOOR_PANEL;
			  PANEL_Panel_Set();
		 }

PANEL_INDOOR_PANEL

					    this->panel_Indoor->Visible = false;

textBox_IndoorFan   Step1
textBox_4WayValve_Modes

											this->panel_Graphics->BackColor = PANEL_PanelColour_State();

PANEL_Panel_Set();


kumanda

textBox_Remocon_OnOff

button_RemoCon_OnOff


textBox_Remote_Fan
button_Remote_Fan


				switch(Indoor.FanRate){
					case FANRATE_SWING : str = "FSwng" ;break;
					case FANRATE_1 : str = "Step1" ;break;
					case FANRATE_2 : str = "Step2" ;break;
					case FANRATE_3 : str = "Step3" ;break;
					case FANRATE_4 : str = "Step4" ;break;
					case FANRATE_5 : str = "Step5" ;break;
					default: str = "error"; break;
				}



	struct Indoor {
		DefrostStep;
		FinalStep;
		FinalRpm;
	}Indoor;
}Fan;

				ComponentArray3[ARRAYSIZE-1] = Fan.Indoor.FinalRpm  () ;	   // pink

OpModestoolStripMenuItem5

// error case //
GenModeErrtoolStripMenuItem
viewtoolStripMenuItem10
helptoolStripMenuItem10
informationtoolStripMenuItem10
filestoolStripMenuItem10
errortoolStripMenuItem



panel_OpMode
panel_Error



Indoor_toolStripMenuItem // kirmizi back
GenModeErrtoolStripMenuItem // error
OpModestoolStripMenuItem5


GUI_LOCK_Controls_For_USB

			if(GUI.Timer.Flag_Base100mSec){ // 100 msec
					GUI.Timer.Base2Sec++;
					if(GUI.Timer.Base2Sec >= 20){ // 100 msec
							GUI.Timer.Base2Sec = 0;
							GUI.Timer.Flag_Base2Sec = true;
					}
			}



			17036


plot_Defrost

				this->plot_Defrost->BackColor = PANEL_PanelColour_State();
				this->plot_Snap_Chart->BackColor = PANEL_PanelColour_State();
				this->plot_Total_Chart->BackColor = PANEL_PanelColour_State();
				this->plot_Mollier->BackColor = PANEL_PanelColour_State();


textBox_EEV_Pulse
progressBar1


textBox_MotorAnimHz

textBox_FanAnimHz


pictureBox_Compressor


			if((this->progressBar1->Maximum < (signed int)EEV.Final.CycleTargetPulse) == true )	 this->progressBar1->Value = this->progressBar1->Maximum;
			else 		this->progressBar1->Value = EEV.Final.CycleTargetPulse;
			this->progressBar1->ForeColor = PANEL_PanelColour_State();
			this->textBox_EEV_Pulse->Text = " E.Valve " + EEV.Final.CycleTargetPulse.ToString() + " Pulse";  // E.Valve 460 Pulse
			this->textBox_EEV_Pulse->BackColor= PANEL_PanelColour_State();



	for(unsigned int i =0; i< GUI.Chart.ArrayMaxIndex; i++){
				Single::TryParse(DataArray1[i],FloatNum);YData1->Add((FloatNum/10).ToString());
				Single::TryParse(DataArray2[i],FloatNum);YData2->Add(((FloatNum/10)).ToString());
				Single::TryParse(DataArray3[i],FloatNum);YData3->Add(((FloatNum/10)).ToString());
				Single::TryParse(DataArray4[i],FloatNum);YData4->Add(((FloatNum/10)).ToString());
				Single::TryParse(DataArray5[i],FloatNum);YData5->Add(((FloatNum/10)).ToString());
				Single::TryParse(DataArray6[i],FloatNum);YData6->Add(((FloatNum/10)).ToString());
				Single::TryParse(DataArray7[i],FloatNum);YData7->Add(((FloatNum/1)).ToString()); // comp freq
				Single::TryParse(DataArray8[i],FloatNum);YData8->Add(((FloatNum/10)).ToString());
				Single::TryParse(DataArray9[i],FloatNum);YData9->Add(((FloatNum/10)).ToString());   // error
				Single::TryParse(DataArray10[i],FloatNum);YData10->Add(((FloatNum/10)).ToString());
				Single::TryParse(DataArray11[i],FloatNum);YData11->Add(((FloatNum/10)).ToString()); // heatsink
				Single::TryParse(DataArray12[i],FloatNum);YData12->Add(((FloatNum/10)).ToString()); // current
				Single::TryParse(DataArray13[i],FloatNum); YData13->Add(((FloatNum/10)).ToString());// voltage
				Single::TryParse(DataArray14[i],FloatNum); YData14->Add((FloatNum).ToString()); // cop
				YDataAircon->Add("100");
		}
			stepBalance1->AbscissaData = XTime;
			stepBalance1->DataSource = YData1;

CHART_Mollier();


textBox_Rel_Dew_InAirFlow


textBox_Rel_Dew_InitTimer



MIDPANEL_X_START
MIDPANEL_X_START_WIDE

GUI.View.ExpandPanel



panel_AC_Pic_vertical


PANEL_Panel_Remote_And_Mode_Info


 this->textBox_DataLoginfo->Visible = false;
 this->textBox_Remocon_Temperature->
 this->textBox_Remocon_OnOff-
 this->textBox_Remocon_Mode-
 this->textBox_Remote_Fan-


 		 this->textBox_DataLoginfo->Visible = false;
 		 this->textBox_Remocon_Temperature->Visible = false;
 		 this->textBox_Remocon_OnOff->Visible = false;
 		 this->textBox_Remocon_Mode->Visible = false;
		 this->textBox_Remote_Fan->Visible = false;


		 GUI_Write_Model

		 void GUI_Play_Update(void)

		 REMOTE_SleepSetReset
		 GUI_Mode_Info_Update



			ChartPlot1->Pen = gcnew Pen(COL_MOTOR_FREQ);
			ChartPlot2->Pen = gcnew Pen(COL_EEV_PULSE);
			ChartPlot3->Pen = gcnew Pen(COL_ERROR);
			ChartPlot4->Pen = gcnew Pen(COL_INDOORFAN_RPM);


			stepBalance7->Pen =   gcnew Pen(COL_MOTOR_FREQ);
			stepBalance8->Pen =   gcnew Pen(COL_EEV_PULSE);
			stepBalance9->Pen =   gcnew Pen(COL_ERROR);
			stepBalance10->Pen = gcnew Pen(COL_FAN_RPM);


COL_INDOORFAN_RPM


textBox_CompressorModes
textBox_EEV_Modes



checkBox_Rel_09 //default ebable yap

textBox_DefOp_Timer // datalari ekle eev role/ fain ind fan out

comboBox_Model  // model no
text_TotalHeating // ttaol heating time

textBox_Chart_Mollier_TempDisch // Curretn Discharge
textBox_Chart_Mollier_Td // target dizchrage


(AirCon.Timer.TotalHeating/60).ToString() + " min";

Modelname // string model write

		this->textBox_Chart_Mollier_TempDisch->Text =   "Current Disch: "+COMMON_Show_Temperature(Temperature.Discharge);
		this->textBox_Chart_Mollier_Td->Text =  "Target Disch:" + GUI.EEV.TargetTd.ToString()+ "°C";



DefrostReason

checkBox_Defr_8115

textBox_D_FTable_6


checkBox_Defr_8111
if(Defrost8111.FinalMatch)if(Defrost8111.FinalMatch)
Defrost8112.FinalMatch
Defrost8113.FinalMatch
Defrost8114.FinalMatch


textBox_Def_Defrost_Start


GUI_LOCK_Controls_For_USB

GUI_Update_temperatures



textBox_DataLoginfo

textBox_Usb_Connect_Info

USB Emulator-Mode




			if(USB_Conncetion_OK) this->textBox_Usb_Connect_Info->Text = "USB Emulator-Mode";
			else 				  this->textBox_Usb_Connect_Info->Text = "USB Simulator-Mode";

			if(GUI.Log.Status == true){
				//this->textBox_DataLoginfo->BackColor = PANEL_PanelColour_State();
				//this->textBox_DataLoginfo->ForeColor = System::Drawing::Color::Black;
				switch(GUI.View.FlashTimer){
							case 0:case 1:case 3: case 4: case 5:  this->textBox_Usb_Connect_Info->Visible = true; break;
							case 6:case 7:case 8:  case 9:  this->textBox_Usb_Connect_Info->Visible = false;break;
				}
			}



GUI_ANIM_Picture_Show

			if(USB_Conncetion_OK)  this->Text = "ACIT- Emulator    ( Air Conditioner Inverter Thermal Emulation Mode via USB Interface) ";
			else										 this->Text = "ACIT-Simulator     ( Air Conditioner Inverter Thermal Simulator  Mode ) " ;



			PANEL_Panel_Security

						if(Security_Mode){
									PANEL_Panel_Security();
									return;
			}




			PANEL_Form_Main_Update

			panel_Remote
			panel_Communication
			panel_Error
			panel_Indoor
			panel_OpMode

			PANEL_Panel_Set(COMPRESSOR_PANEL);

			void GUI_SlideShow_PanelChange(void){
				switch(



					GUI.View.Panel_Counter = COMPRESSOR_PANEL;
					GUI_SlideShow_PanelChange();


	, Directory::GetCurrentDirectory()+ "\\Helps\\"


	VERSION_Update

	MessageBox::Show("Logging is  Continuing...  Firts Stop Logging !");


	String^ Path = Directory::GetCurrentDirectory() ;//+ "\\Animations\\";


				String^ str =
			// wite 2 stream

			COMPILE_Time_Info()+ ".." + COMPILE_Date_Info()+nl+ nl+ nl +


Priority_High
Security_Mode

		SECURITY_MachineCheck();
	/*
			 if( (Environment::MachineName  ==  "LG_ILKER") ||    (Environment::MachineName  ==  "A00070040")   ||    (Environment::MachineName  ==  "A00069480") ){
							GUI.Access.Priority_High = true;
					}
				 else GUI.Access.Priority_High = false;
	*/

	GUI.Access.Priority_High = false;

	GUI.Access.Priority_Mid= true;


	switch(GUI.Access.Priority){
		case PRIORITY_FIRST: break;
		case PRIORITY_SECOND:
		case PRIORITY_THIRD:
		case PRIORITY_FOURTH:
		default: return; break;
	}


	void GUI_DEMO_ANIMATION(void){

					if(GUI.Access.Demo == false) return;



								static unsigned int StopChartTimer;
								if(GUI.View.Play)return;
								if(AirCon.SubMode == STANDBYE){
									if(GUI.Log.ChartSoftOffTimer == 0){
										GUI.Chart.ArrayMaxIndex =0;
										GUI.Chart.TotalStartIndex=0;
									}
								}
								else{ StopChartTimer  = 0;
										GUI.Log.ChartSoftOffTimer  = 180; // soft off time
								}
								if(GUI.Log.ChartSoftOffTimer != 0){  // if not at the end of soft stop log view go on!!
										GUI.Chart.ArrIndexer ++;
								}
		CHART_BigLog_Plot();

		CHART_DataProcess_Demo

		CHART_Clear_LogChart();

void REMOTE_OnOff(void){

									PANEL_Color_All_Temp_Panels();
									PANEL_Form1_Colour_Update();


Color  PANEL_PanelColour_State(){
				PANEL_Color_NumBoxTemperatures();


Color  PANEL_PanelColour_State(){
				PANEL_Color_NumBoxTemperatures();

			 Color^ ActiveColor	= gcnew Color();

	switch(GUI.Access.Priority){
		case PRIORITY_FIRST: break;
		case PRIORITY_SECOND:
		case PRIORITY_THIRD:  return *COOLING_COLOR;
		case PRIORITY_FOURTH:
		default: return; break;
	}
void PANEL_Form1_Colour_Update(void){

void GUI_DEMO_COLOUR_UPDATE(void){
		this->panel_Compressor->BackColor = PANEL_Demo_PanelColour_State();
		this->textBox_MotorOilSupply->BackColor= PANEL_Demo_PanelColour_State();
		this->textBox_OilSup_Timer->BackColor= PANEL_Demo_PanelColour_State();
		this->textBox_Step2Freq->BackColor= PANEL_Demo_PanelColour_State();
		this->textBox_MaxMinStepFTable->BackColor= PANEL_Demo_PanelColour_State();
		this->textBox_ReliabilityMin_Group->BackColor= PANEL_Demo_PanelColour_State();
		this->textBox_Reliability_Group->BackColor= PANEL_Demo_PanelColour_State();
		this->panel_Reliability->BackColor = PANEL_Demo_PanelColour_State();
		this->panel_SuperHeat->BackColor = PANEL_Demo_PanelColour_State();
		this->textBox_Compen_SHeat_Group->BackColor= PANEL_Demo_PanelColour_State();
		this->textBox_Compen_Start_Group->BackColor= PANEL_Demo_PanelColour_State();
		this->panel_FanMode->BackColor        =   PANEL_Demo_PanelColour_State();
		this->textBox_FanStep2rpm->BackColor= PANEL_Demo_PanelColour_State();
		this->panel_Defrost->BackColor      = PANEL_Demo_PanelColour_State();this->plot_Defrost->BackColor = PANEL_Demo_PanelColour_State();
		this->panel_Indoor->BackColor = PANEL_Demo_PanelColour_State();
		this->trackBar_Chart->BackColor = PANEL_Demo_PanelColour_State(); this->plot_Mollier->BackColor = PANEL_Demo_PanelColour_State();
		this->panel_Graphics->BackColor = PANEL_Demo_PanelColour_State(); this->plot_Total_Chart->BackColor = PANEL_Demo_PanelColour_State();
		this->panel_Error->BackColor = PANEL_Demo_PanelColour_State();
		this->panel_OpMode->BackColor = PANEL_Demo_PanelColour_State();
		this->panel_EEV_MOTOR_SHOW->BackColor= PANEL_Demo_PanelColour_State();
		this->panel_Remote->BackColor= PANEL_Demo_PanelColour_State();
		this->BackColor = PANEL_Demo_PanelColour_State();
		this->menuStrip1->BackColor = PANEL_Demo_PanelColour_State();

}

Color  PANEL_Demo_PanelColour_State(void){
	Color^ ActiveColor	= gcnew Color();
	if(GUI.Access.Demo == false) return *STANDBYE_COLOR;
	else  return *COOLING_COLOR;
}

	 Color^ ActiveColor	= gcnew Color();

				switch(AirCon.MainMode){
								case StopM:		break;
								case CycleM:  	break;
								case SeerM:	   break;
								case CopM: 	   break;
								case PreheatM:
								case LqcM:
								case TestM:	break;
								default:break;
				}
				 switch(AirCon.SubMode){
								case HEAT_DELAY : ActiveColor = HEATDELAY_COLOR; break;
								case COOL_DELAY :	ActiveColor = COOLDELAY_COLOR; break;
								case STANDBYE :		ActiveColor = STANDBYE_COLOR; break;
								case COOL:	  ActiveColor = COOLING_COLOR; break;
								case HEAT:	ActiveColor = HEATING_COLOR; break;
								case DEFROST_0: case DEFROST_1: case DEFROST_2:case DEFROST_3:case DEFROST_4:case DEFROST_5:case DEFROST_6:case DEFROST_7:
																		ActiveColor = DEFROST_COLOR; break;
										default:break;
							}
			return *ActiveColor;


Color  PANEL_PanelColour_State(){
		GUI.View.Demo_Timer

			write syntax

								case  GRAPHICS_PANEL :this->trackBar_Chart->BackColor = PANEL_PanelColour_State();
													   this->plot_Mollier->BackColor = PANEL_PanelColour_State();

									break;
								case    LOGGING_PANEL : this->panel_Graphics->BackColor = PANEL_PanelColour_State();
								t
								his->plot_Total_Chart->BackColor = PANEL_PanelColour_State();

textBox_EEV_Pulse
progressBar1



				System::Drawing::Rectangle workingRectangle = Screen::PrimaryScreen->WorkingArea;
"Screen Resolution Width / Height : " +  workingRectangle.Width    + " / " +  workingRectangle.Height    + nl+ nl;


			System::Drawing::Rectangle Resolution = Screen::PrimaryScreen->WorkingArea;
			unsigned int  RemoteConX_Start = Resolution.Width - REMOCONPANEL_WIDTH ; // 1600 - 195 // 1405
			if (Resolution.Width  > 1600 ) RemoteConX_Start = MIDPANEL_X_START + MIDPANEL_WIDTH +2 ;
			this->Width = 1600;
			this->Height = 900;
			this->panel_RemoteCon->Width = REMOCONPANEL_WIDTH;
			this->panel_RemoteCon->Height = REMOCONPANEL_HEIGHT;

				this->panel_RemoteCon->Location = Point(RemoteConX_Start ,   REMOCONPANEL_Y_START);
				this->panel_RemoteCon->Visible = true;
//			else						 {	this->panel_RemoteCon->Visible = false;}
			unsigned int  LeftInfoX_Start = Resolution.Width - REM_INFOPANEL_WIDTH ;
			if (Resolution.Width  > 1600 ) LeftInfoX_Start = MIDPANEL_X_START + MIDPANEL_WIDTH +2 ;


			void GUI_Screen_Resolution_Warning(void){
F->textBox1->Location = System::Drawing::Point(8,8);


String^  Pic5_path = Subpath +   "compressor5.jpg"	;
 if ( (File::Exists( Pic1_path ))) this->pictureBox_Compressor->Image = System::Drawing::Image::FromFile(Pic1_path);
 					this->panel_AC_Pic_vertical->Location = Point(ACPICPANEL_X_START,ACPICPANEL_Y_START);//Point(0,126);


this->pictureBox_remoconMode

 this->pictureBox_remoconMode->Visible = false;


if(IndoorCommand.FanRate > INDOOR_FANRATE_SWING) IndoorCommand.FanRate = INDOOR_FANRATE_1;


pictureBox_remote_FanRate

REMOTE_IndoorFanUpdate();


pictureBox_Remote_AmbTemp  // ofta iptal et  Normal locatio 70, 71 // ortam secildiginde 70 x sabit y 80 gibi 5 sn
textBox_Remocon_Temperature // PO yazdir

			switch(GUI.View.FlashTimer){
							case 0:case 1:case 3: case 4: case 5:  this->textBox_Usb_Connect_Info->Visible = true; break;
							case 6:case 7:case 8:  case 9:  this->textBox_Usb_Connect_Info->Visible = false;break;
		}

IndoorCommand.Mode.OnOff_Enabled  = OFF;

REMOTE_IndoorPlasmaUpdate


button_RemoCon_Jet
button_RemoCon_Plasma
button_RemoCon_ESaving
button_RemoCon_AClean
button_RemoCon_RoomTemp
button_RemoCon_SwingAlt
button_RemoCon_SwingYan




pictureBox_Remote_Plasma
pictureBox_Remote_Energy
pictureBox_Remote_Clean


pictureBox_Remote_AmbTemp


	//		 if(IndoorCommand.AClean) this->pictureBox_Remote_Clean->Visible = true;
	//		 else  this->pictureBox_Remote_Clean->Visible = false;

			 IndoorCommand.RoomTemp.Timer = ROOM_TEMPERATURE_TIMER;



			 			 IndoorCommand.RoomTemp.Enabled = true;
			 			// IndoorCommand.RoomTemp.Timer = ROOM_TEMPERATURE_TIMER;


pictureBox_remote_ONOFF

			GUI.OnOff.Timer   = 55;
			GUI.OnOff.Flash  =2;



	if(GUI.OnOff.Timer) GUI.OnOff.Timer --;
	else{
		GUI.OnOff.Flash--;
		if(GUI.OnOff.Flash){
			GUI.OnOff.Timer = 55;
			IndoorCommand.Mode.GUI == true;

		}
	}


	REMOTE_OnOff_Show


	pictureBox_Remote_AmbTemp
	pictureBox_Remote_DegreeC


	REMOTE_IndoorAmbientTemperatureUpdate


	REMOTE_IndoorSwingDikeyUpdateGUI
	REMOTE_IndoorSwingYatayUpdateGUI



	IndoorCommand.SwingYatay.GUI = ON;
	IndoorCommand.SwingDikey.GUI = ON;



				this->pictureBox_remote_sleep->Visible = true;
				this->textBox_Remocon_SleepTimer->Visible = true;

				this->textBox_Remocon_RealTime->Visible = true;
				this->pictureBox_remote_TimeOnOff->Visible = true;

String ^ COMMON_GetTime(){ // only for charts
		  String ^AmPm = "";  String ^Saat = ",";
		   DateTime d1 = DateTime::Now;
		   int Hour = d1.Hour;   int Min = d1.Minute;//  int Sec = d1.Second;
		   String^  HourZero="";		  String^   MinZero="";		// String^  SecZero="";
		   if(Hour>12) {
				Hour -=12; AmPm = "PM";
		   }
		   else AmPm = "AM";
		   if(Hour < 10 ) HourZero = "0";else HourZero = "";
		   if(Min < 10 ) MinZero = "0";else MinZero = "";
			Saat =  HourZero +  Hour.ToString()+":"+MinZero+Min.ToString();
}

this->textBox_Remocon_AmPm->Location = Point(RemoteConX_Start ,   REMOCONPANEL_Y_START); //pm 72 140


/*==============================================================================*/
/*		MW_ODU_capa_test_load_set													*/
/*==============================================================================*/
unsigned char MW_ODU_capa_test_load_set(unsigned char mode_syst,unsigned char t_indoor_exist,unsigned char t_indoor_type,unsigned short load_cst)
{
//08.08.07  FU : Add seer Max mode
	unsigned char t_load_seer = 0;

	t_indoor_type = t_indoor_type >> 4;

	if(mode_syst!=0){
//09.04.10	FU : option table upgrade	OP_outdoor_product_type->uc_outdoor_product_type
		if(uc_outdoor_product_type==0||uc_outdoor_product_type==1){
			if(t_indoor_exist==1){
				switch(t_indoor_type){
					case 0:
					case 1:
					case 2:
						t_load_seer = roption[load_cst+3];
						break;
					case 3:
						t_load_seer = roption[load_cst];
						break;
					case 4:
						t_load_seer = roption[load_cst+1];
						break;
					case 5:
						t_load_seer = roption[load_cst+2];
						break;
					case 6:
						t_load_seer = roption[load_cst+4];
						break;
					case 9:
						t_load_seer = roption[load_cst+5];
						break;
					default:
						t_load_seer = roption[load_cst];
						break;
				}
			}
		}
//09.04.10	FU : option table upgrade	OP_outdoor_product_type->uc_outdoor_product_type
		else if(uc_outdoor_product_type==2){
			t_load_seer = roption[load_cst];
		}
	}
	return t_load_seer;
}


checkBox_Rel_09