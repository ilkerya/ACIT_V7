#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Threading;

namespace EEV_Sim {

	/// <summary>
	/// Summary for USB
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class USB : public System::Windows::Forms::Form
	{
				static int numPorts = 0;
        //Create a delegate function for this thread that will take
        //  in a string and will write it to the txtDataReceived textbox

	delegate void SetTextCallback(String^ text);
	public:
		USB(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~USB()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  btnClose;
	protected: 
	private: System::Windows::Forms::ComboBox^  lstCOMPorts;
	private: System::Windows::Forms::TextBox^  txtSendData;
	private: System::Windows::Forms::Button^  btnSendData;
	private: System::Windows::Forms::Button^  btnConnect;
	private: System::Windows::Forms::TextBox^  txtDataReceived;
	private: System::IO::Ports::SerialPort^  serialPort1;
	public: System::Windows::Forms::Timer^  timer1;
	private: 
	private: System::ComponentModel::IContainer^  components;
	public: 

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
				this->components = (gcnew System::ComponentModel::Container());
				System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(USB::typeid));
				this->btnClose = (gcnew System::Windows::Forms::Button());
				this->lstCOMPorts = (gcnew System::Windows::Forms::ComboBox());
				this->txtSendData = (gcnew System::Windows::Forms::TextBox());
				this->btnSendData = (gcnew System::Windows::Forms::Button());
				this->btnConnect = (gcnew System::Windows::Forms::Button());
				this->txtDataReceived = (gcnew System::Windows::Forms::TextBox());
				this->serialPort1 = (gcnew System::IO::Ports::SerialPort(this->components));
				this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
				this->SuspendLayout();
				// 
				// btnClose
				// 
				this->btnClose->Enabled = false;
				this->btnClose->Location = System::Drawing::Point(199, 14);
				this->btnClose->Name = L"btnClose";
				this->btnClose->Size = System::Drawing::Size(78, 22);
				this->btnClose->TabIndex = 11;
				this->btnClose->Text = L"Close";
				this->btnClose->UseVisualStyleBackColor = true;
				this->btnClose->Click += gcnew System::EventHandler(this, &USB::btnClose_Click);
				// 
				// lstCOMPorts
				// 
				this->lstCOMPorts->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
				this->lstCOMPorts->FormattingEnabled = true;
				this->lstCOMPorts->Location = System::Drawing::Point(94, 14);
				this->lstCOMPorts->Name = L"lstCOMPorts";
				this->lstCOMPorts->Size = System::Drawing::Size(99, 21);
				this->lstCOMPorts->TabIndex = 10;
				this->lstCOMPorts->SelectedIndexChanged += gcnew System::EventHandler(this, &USB::lstCOMPorts_SelectedIndexChanged);
				// 
				// txtSendData
				// 
				this->txtSendData->Location = System::Drawing::Point(94, 42);
				this->txtSendData->Name = L"txtSendData";
				this->txtSendData->Size = System::Drawing::Size(440, 20);
				this->txtSendData->TabIndex = 9;
				// 
				// btnSendData
				// 
				this->btnSendData->Location = System::Drawing::Point(12, 41);
				this->btnSendData->Name = L"btnSendData";
				this->btnSendData->Size = System::Drawing::Size(76, 21);
				this->btnSendData->TabIndex = 8;
				this->btnSendData->Text = L"Send Data";
				this->btnSendData->UseVisualStyleBackColor = true;
				// 
				// btnConnect
				// 
				this->btnConnect->Location = System::Drawing::Point(12, 14);
				this->btnConnect->Name = L"btnConnect";
				this->btnConnect->Size = System::Drawing::Size(76, 21);
				this->btnConnect->TabIndex = 7;
				this->btnConnect->Text = L"Connect";
				this->btnConnect->UseVisualStyleBackColor = true;
				this->btnConnect->Click += gcnew System::EventHandler(this, &USB::btnConnect_Click);
				// 
				// txtDataReceived
				// 
				this->txtDataReceived->Location = System::Drawing::Point(12, 68);
				this->txtDataReceived->Multiline = true;
				this->txtDataReceived->Name = L"txtDataReceived";
				this->txtDataReceived->Size = System::Drawing::Size(522, 155);
				this->txtDataReceived->TabIndex = 6;
				// 
				// timer1
				// 
				this->timer1->Enabled = true;
				this->timer1->Interval = 1;
				this->timer1->Tick += gcnew System::EventHandler(this, &USB::timer1_Tick);
				// 
				// USB
				// 
				this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
				this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				this->ClientSize = System::Drawing::Size(546, 236);
				this->Controls->Add(this->btnClose);
				this->Controls->Add(this->lstCOMPorts);
				this->Controls->Add(this->txtSendData);
				this->Controls->Add(this->btnSendData);
				this->Controls->Add(this->btnConnect);
				this->Controls->Add(this->txtDataReceived);
				this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
				this->Name = L"USB";
				this->Text = L"USB";
				this->ResumeLayout(false);
				this->PerformLayout();

		}
#pragma endregion
		/***************************************************************************/
		private: void UpdateCOMPortList(void){
			int i;
			bool foundDifference;
			cli::array<System::String^,1>^ portNames; 

			i = 0;
			foundDifference = false;

			//If the number of COM ports is different than the last time we
			//  checked, then we know that the COM ports have changed and we
			//  don't need to verify each entry.
			portNames = serialPort1->GetPortNames();
			if(lstCOMPorts->Items->Count == portNames->Length){
				//Search the entire SerialPort object.  Look at COM port name
				//  returned and see if it already exists in the list.
				for(i=0;i<portNames->Length;i++)	{
					if(lstCOMPorts->Items[i]->Equals(portNames[i]) ==  false){
						foundDifference = true;
					}
				}
			}
			else{
				foundDifference = true;
			}

			//If nothing has changed, exit the function.
			if (foundDifference == false)
			{
				return;
			}

			//If something has changed, then clear the list
			lstCOMPorts->Items->Clear();

			//Add all of the current COM ports to the list
			for(i=0;i<portNames->Length;i++){
				lstCOMPorts->Items->Add(portNames[i]);
			}
			//Set the listbox to point to the first entry in the list
			lstCOMPorts->SelectedIndex = 0;
		}
	private: System::Void btnConnect_Click(System::Object^  sender, System::EventArgs^  e) {
			//This section of code will try to open the COM port.
			//  Please note that it is important to use a try/catch
			//  statement when opening the COM port.  If a USB virtual
			//  COM port is removed and the PC software tries to open
			//  the COM port before it detects its removal then
			//  an exeception is thrown.  If the execption is not in a
			//  try/catch statement this could result in the application
			//  crashing.
			try{
				//Get the port name from the application list box.
				//  the PortName attribute is a string name of the COM
				//  port (e.g. - "COM1").
				serialPort1->PortName = lstCOMPorts->Items[lstCOMPorts->SelectedIndex]->ToString();

				//Open the COM port.
				serialPort1->Open();

				//Change the state of the application objects
				btnConnect->Enabled = false;
				lstCOMPorts->Enabled = false;
				btnClose->Enabled = true;

				//Clear the textbox and print that we are connected.
				txtDataReceived->Clear();
				txtDataReceived->AppendText("Connected.\r\n");
			}
			catch(...){
				//If there was an exception, then close the handle to 
				//  the device and assume that the device was removed
				btnClose_Click(this, gcnew EventArgs());
			}


			 }
private: System::Void btnClose_Click(System::Object^  sender, System::EventArgs^  e) {
			//Reset the state of the application objects
			btnClose->Enabled = false;
			btnConnect->Enabled = true;
			lstCOMPorts->Enabled = true;

			//This section of code will try to close the COM port.
			//  Please note that it is important to use a try/catch
			//  statement when closing the COM port.  If a USB virtual
			//  COM port is removed and the PC software tries to close
			//  the COM port before it detects its removal then
			//  an exeception is thrown.  If the execption is not in a
			//  try/catch statement this could result in the application
			//  crashing.
			try{
				//Dispose the In and Out buffers;
				serialPort1->DiscardInBuffer();
				serialPort1->DiscardOutBuffer();

				//Close the COM port
				serialPort1->Close();
			}
			//If there was an exeception then there isn't much we can
			//  do.  The port is no longer available.
			catch(...){}

		 }
	/****************************************************************************
			Function:
				private void serialPort1_DataReceived(  object sender, 
														SerialDataReceivedEventArgs e)

			Summary:
				This function prints any data received on the COM port.

			Description:
				This function is called when the data is received on the COM port.  This
				function attempts to write that data to the txtDataReceived textbox.  If
				an exception occurs the btnClose_Click() function is called in order to
				close the COM port that caused the exception.

			Precondition:
				None

			Parameters:
				object sender     - Sender of the event (this form)
				SerialDataReceivedEventArgs e       - The event arguments

			Return Values:
				None

			Remarks:
				None
		***************************************************************************/
		private: System::Void serialPort1_DataReceived(System::Object^  sender, System::IO::Ports::SerialDataReceivedEventArgs^  e) {
			try{
				SetText(serialPort1->ReadExisting());
			}
			catch(...){
				btnClose_Click(this, gcnew EventArgs());
			}
		}

		/****************************************************************************
			Function:
				private void SetText(string text)

			Summary:
				This function prints the input text to the txtDataReceived textbox.

			Description:
				This function prints the input text to the txtDataReceived textbox.  If
				the calling thread is the same as the thread that owns the textbox, then
				the AppendText() method is called directly.  If a thread other than the
				main thread calls this function, then an instance of the delegate function
				is created so that the function runs again in the main thread.

			Precondition:
				None

			Parameters:
				string text     - Text that needs to be printed to the textbox

			Return Values:
				None

			Remarks:
				None
		***************************************************************************/
		private: void SetText(String^ text){
			//InvokeRequired required compares the thread ID of the
			//  calling thread to the thread ID of the creating thread.
			//  If these threads are different, it returns true.  We can
			//  use this attribute to determine if we can append text
			//  directly to the textbox or if we must launch an a delegate
			//  function instance to write to the textbox.
			if (this->txtDataReceived->InvokeRequired){
				//InvokeRequired returned TRUE meaning that this function
				//  was called from a thread different than the current
				//  thread.  We must launch a deleage function.

				//Create an instance of the SetTextCallback delegate and
				//  assign the delegate function to be this function.  This
				//  effectively causes this same SetText() function to be
				//  called within the main thread instead of the second
				//  thread.
				SetTextCallback^ d = gcnew SetTextCallback(this,&EEV_Sim::USB::SetText); // NamespaceName::FormName

				//Invoke the new delegate sending the same text to the
				//  delegate that was passed into this function from the
				//  other thread.
				this->Invoke(d,gcnew String(text));
			}
			else{
				//If this function was called from the same thread that 
				//  holds the required objects then just add the text.
				txtDataReceived->AppendText(text);
			}
		}
private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
			//Update the COM ports list so that we can detect
			//  new COM ports that have been added.
			UpdateCOMPortList();

		 }
private: System::Void lstCOMPorts_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
		 }
};
}
