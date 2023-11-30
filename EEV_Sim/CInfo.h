#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Net;
using namespace System::Net::Sockets;
using namespace System::Net::NetworkInformation;
using namespace System::Text::RegularExpressions;


//#using <System.dll>

namespace EEV_Sim {

	/// <summary>
	/// Summary for CInfo
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class CInfo : public System::Windows::Forms::Form
	{
	public:
		CInfo(void)
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
		~CInfo()
		{
			if (components)
			{
				delete components;
			}
		}
	public: System::Windows::Forms::TextBox^  textBox1;

	protected: 

	protected: 

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(CInfo::typeid));
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// textBox1
			// 
			this->textBox1->BackColor = System::Drawing::Color::White;
			this->textBox1->Cursor = System::Windows::Forms::Cursors::IBeam;
			this->textBox1->ImeMode = System::Windows::Forms::ImeMode::Off;
			this->textBox1->Location = System::Drawing::Point(25, 31);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(463, 657);
			this->textBox1->TabIndex = 22;
			this->textBox1->TabStop = false;
			this->textBox1->Text = L"1\r\n2\r\n3\r\n4\r\n5\r\n6\r\n7\r\n8\r\n9\r\n10\r\n11\r\n12\r\n13\r\n14\r\n15\r\n16\r\n17\r\n18";
	//		this->textBox1->TextChanged += gcnew System::EventHandler(this, &CInfo::textBox1_TextChanged);
			// 
			// CInfo
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::LimeGreen;
			this->ClientSize = System::Drawing::Size(505, 697);
			this->Controls->Add(this->textBox1);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->Name = L"CInfo";
			this->Text = L"Computer Information";
			this->Load += gcnew System::EventHandler(this, &CInfo::CInfo_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		/*

	private: System::Void listBox1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
      // Return if no list item is selected.

      if ( listBox1->SelectedIndex == -1 )
            return;

			}
 */
	private: System::Void CInfo_Load(System::Object^  sender, System::EventArgs^  e) {
					Computer_Info();

			//	this->textBox1->Text = "ooooooooooooooooooo" ;


	//								array<unsigned char>^ GetAddressBytes();
//										array<Byte>^bytes = System::Net::IPAddress::GetAddressBytes();
					//				String^ str = System::Net::IPAddress;

						//array<Byte>^bytes = GetAddressBytes();
								//	String^ server ;
									//	IPHostEntry^ heserver = Dns::GetHostEntry( server );

									
						//		  System::Collections::IEnumerator^ myEnum = heserver->AddressList->GetEnumerator();
							//	  System::Collections::
							//	IPAddress^ curAdd = safe_cast<IPAddress^>(myEnum->Current);
/*							//		IPAddress^ curAdd = safe_cast<IPAddress^>(IPAddress::GetAddressBytes());
									
									array<String^>^ IPArray  = System::Net::IPAddress::GetAddressBytes().
								String^ Yaz;
								for ( int i = 0; i < bytes->Length; i++ ){
										Yaz +=bytes[ i ].ToString();
								}
								this->textBox1->Text += Yaz;
*/
						//		array<Byte>^bytes = curAdd->GetAddressBytes();
						//	array<Byte>^bytes = curAdd->
					//	array<String^>^ IPArray = gcnew array<String^>(100);
						//array<String^>^ IPArray = curAdd->GetAddressBytes();
/*
						  array<String^>^args = Environment::GetCommandLineArgs();
						String^ IPaddress;
						 if ( args->Length == 1 ){
								Console::WriteLine( "Please enter an IP address." );
								Console::WriteLine( "Usage:   >cs_parse any IPv4 or IPv6 address." );
								Console::WriteLine( "Example: >cs_parse 127.0.0.1" );
								Console::WriteLine( "Example: >cs_parse 0:0:0:0:0:0:0:1" );
						}
						else  IPaddress = args[ 1 ];
	*/					// Get the list of the IPv6 addresses associated with the requested host.
					//	parse( IPaddress );
						//parse(System::Net::
//						String^ IpAddressString ;
			//			   IPAddress^ hostIPAddress = IPAddress::Parse( IpAddressString );
			//			   this->textBox1->Text += IpAddressString;
			//			   this->textBox1->Text += hostIPAddress->Address;
	


			 }
	public: 	void Computer_Info( void){
				String^ nl = Environment::NewLine;
				System::Drawing::Rectangle workingRectangle = Screen::PrimaryScreen->WorkingArea;
						String^ str ;					
	//			String^ ndff =  __TIME__; // deneme
//								this->textBox2->Text = 
	//			"MachineName: "  + Environment::MachineName ;
		//		String^ P2Adr ;
	//			IWebProxy^ PAdr;
//				IWebProxy^ PAdr = gcnew IWebProxy();
//				PAdr =  System::Net::WebRequest::GetSystemWebProxy() ;
	//			P2Adr = Convert::ToString(PAdr);
		//		P2Adr =
		//		InternetConnectionInformation( String^ testUrl, int testTimeout, IWebProxy^ proxy );


		//		this->textBox1->Text = str;
				str = 	"Acit  Compiled  Time & Date : " +   __TIME__ + "..." +  __DATE__ + nl + nl +				
				

	//			"Proxy Server" +     P2Adr   + nl+
			
				"UserName : "  + Environment::UserName + nl+
				"UserDomainName : "  + Environment::UserDomainName + nl+
				"Local IP : " +GetLocalIP()+nl+ nl+
				 "MachineName: "  + Environment::MachineName + nl+
		//		"LINE "  + __LINE__ + nl +
		//		"FILE "  + __FILE__ + nl +
		    //    "ssssss"   +  NumberOfLines.ToString() + nl + 

				"OSVersion : " + Environment::OSVersion + nl+
	//			 "Shutdown ? : " + Environment::HasShutdownStarted+ nl+
				"CLR Version : "  + Environment::Version + nl+ nl +
			//	"WorkingSet  : " + Environment::WorkingSet  + nl+

			//	String^ query = "System drive is %SystemDrive%" + nl + "System root is %SystemRoot%";
			//	String^ str = Environment::ExpandEnvironmentVariables( query );
			Environment::ExpandEnvironmentVariables( "System drive : %SystemDrive%" + nl + "System Root : %SystemRoot%" )  + nl+
				"SystemDirectory : "  + Environment::SystemDirectory + nl+ nl +
				"Screen Resolution Width / Height : " +  workingRectangle.Width    + " / " +  workingRectangle.Height    + nl+ nl;
		//		"Command Line: " + Environment::CommandLine+ nl+
		//		"CurrentDirectory : " + Environment::CurrentDirectory + nl

/*				IDictionary^ environmentVariables = Environment::GetEnvironmentVariables();
				IEnumerator^ myEnum = environmentVariables->GetEnumerator();
				while ( myEnum->MoveNext() ){
						DictionaryEntry^ de = safe_cast<DictionaryEntry^>(myEnum->Current);
						this->textBox1->Text +=  de->Key;//de->Value;
						this->textBox1->Text +=  nl;
						this->textBox1->Text +=  de->Value;
						this->textBox1->Text +=  nl;
				 }
 */		// ( (File::Exists( Pic2_path )
			//	string str ("Test string");
			//	cout << "size: " << str.size() << "\n";



			array<String^>^drives = Environment::GetLogicalDrives();
	//		array String drives 

			str += "Installed LogicalDrives: " ;
			 for(int i = 0;   i < drives->Length  ; i++ ){
						str +=" " + drives[i];
			 }


			//	MessageBox::Show(S"This is the main thread");
			//	System::Windows::Forms::MessageBox::Show("This is the main thread");

//				RECT rc;
// GetWindowRect(GetDesktopWindow(), &rc);
	//	const long nScreenWidth = ::GetSystemMetrics(SM_CXSCREEN);
	//			const long nScreenHeight = ::GetSystemMetrics(SM_CYSCREEN); 
				   Version^ version = Environment::Version;
					if (version) {
						 int build = version->Build;
						 int major = version->Major;
						  int minor = version->Minor;
						  int revision = version->Revision;
						  int MinorRevision = version->MinorRevision;
						   int MajorRevision = version->MajorRevision;

						  //int Pack = version->
						 str += nl + nl + ".NET Framework version:" ;
								// Console::Write(".NET Framework version: ");
								//	Console::WriteLine("{0}.{1}.{2}.{3}", build, major, minor, revision);
						  str +=   major.ToString() + "." +minor.ToString()+ "." + build.ToString() + "." +revision.ToString()  ;
						  str +=  "." + MinorRevision.ToString() + "."  + MajorRevision.ToString();
						 }
					else str +=nl + " .net Framework couldnt find";

			 str += nl + nl ;	

			System::Net::NetworkInformation::IPGlobalProperties  ^ computerProperties =  System::Net::NetworkInformation::IPGlobalProperties::GetIPGlobalProperties();

			str += nl + "Domain name:   " +computerProperties->DomainName;
			str += nl + "Computer name: "+ computerProperties->HostName;
			str += nl + "Host  name:   " +computerProperties->HostName;
		//	str += nl +  "Node type:         "+  computerProperties->NodeType;
			str += nl + "DHCP scope:    "+ computerProperties->DhcpScopeName;
			str += nl +  "WINS proxy exists?   "+ computerProperties->IsWinsProxy ;

			array< System::Net::NetworkInformation::NetworkInterface^>^nics = System::Net::NetworkInformation::NetworkInterface::GetAllNetworkInterfaces();

			if (nics->Length < 1)  {
				str += nl + "  No network interfaces found.";
			 }
			else{

				//foreach (NetworkInterface adapter in nics){
			}
		//	PhysicalAddress address = adapter->GetPhysicalAddress();
		//	System::Net::NetworkInformation::PhysicalAddress();
		
//			System::Net::NetworkInformation::PhysicalAddress ^ strfty = System::Net::NetworkInformation::PhysicalAddress();
			

//array<NetworkInterface^>^nics = NetworkInterface::GetAllNetworkInterfaces();


//   Console::WriteLine( "Interface information for {0}.{1}     ", computerProperties->HostName, computerProperties->DomainName );
   System::Collections::IEnumerator^ myEnum27 = nics->GetEnumerator();
   str += nl + "Network Interfaces : "+ nl;
   while ( myEnum27->MoveNext() )
   {
      NetworkInterface ^ adapter = safe_cast<NetworkInterface ^>(myEnum27->Current);
      IPInterfaceProperties ^ properties = adapter->GetIPProperties();
	  str += nl + "Description : " +  adapter->Description ;
	  str += nl +   "Adress :    " + adapter->GetPhysicalAddress() ;
//			str += nl + adapter->NetworkInterfaceType();

/*  Console::WriteLine( adapter->Description );
    Console::WriteLine( String::Empty->PadLeft( adapter->Description->Length, '=' ) );
    Console::WriteLine( "  Interface type .......................... : {0}",      adapter->NetworkInterfaceType );
      Console::WriteLine( "  Physical Address ........................ : {0}",       adapter->GetPhysicalAddress() );
   Console::WriteLine( "  Is receive only.......................... : {0}",     adapter->IsReceiveOnly );
      Console::WriteLine( "  Multicast................................ : {0}",    adapter->SupportsMulticast );
	  */
   }
 

		this->textBox1->Text = str;



				}
	private:  System::String ^GetLocalIP()  { 
		System::String ^_IP = nullptr; 
		// Resolves a host name or IP address to an IPHostEntry instance. . 
		// IPHostEntry - Provides a container class for Internet host address information.  . 
		System::Net::IPHostEntry ^_IPHostEntry = System::Net::Dns::GetHostEntry(System::Net::Dns::GetHostName()); 
		// IPAddress class contains the address of a computer on an IP network.  . 
				for each (System::Net::IPAddress ^_IPAddress in _IPHostEntry->AddressList)  { 

						 // InterNetwork indicates that an IP version 4 address is expected  . 
						 // when a Socket connects to an endpoint . 
						 if (_IPAddress->AddressFamily.ToString() == "InterNetwork")   { 
								_IP = _IPAddress->ToString(); 
						} 
				} 
		 return _IP; 
 } 
	public: 	void parse( String^ ipAddress ){
						String^ nl = Environment::NewLine;
				try{

						 // Create an instance of IPAddress for the specified address string (in
						// dotted-quad, or colon-hexadecimal notation).
						IPAddress^ address = IPAddress::Parse( ipAddress );

						 // Display the address in standard notation.
						 Console::WriteLine( "Parsing your input string: \"{0}\" produces this address (shown in its standard notation): {1}", ipAddress, address );
						 this->textBox1->Text +="Parsing your input string:" + ipAddress + "produces this address :" + address + nl;
						}
				catch ( ArgumentNullException^ e ) {
						this->textBox1->Text += "ArgumentNullException caught!!!" +nl;
						 this->textBox1->Text += e->Source;
						this->textBox1->Text +=nl;
						 this->textBox1->Text += e->Message;
						 this->textBox1->Text +=nl;

						 Console::WriteLine( "ArgumentNullException caught!!!" );
						Console::WriteLine( "Source : {0}", e->Source );
						Console::WriteLine( "Message : {0}", e->Message );
				 }
				catch ( FormatException^ e ) {
						this->textBox1->Text += "FormatException caught!!!" +nl;
						 this->textBox1->Text += e->Source;
						this->textBox1->Text +=nl;
						 this->textBox1->Text += e->Message;
						 this->textBox1->Text +=nl;

						Console::WriteLine( "FormatException caught!!!" );
						 Console::WriteLine( "Source : {0}", e->Source );
						 Console::WriteLine( "Message : {0}", e->Message );
				}
				catch ( Exception^ e )   {
						this->textBox1->Text += "Exception caught!!!" +nl;
						 this->textBox1->Text += e->Source;
						this->textBox1->Text +=nl;
						 this->textBox1->Text += e->Message;
						 this->textBox1->Text +=nl;

						Console::WriteLine( "Exception caught!!!" );
						 Console::WriteLine( "Source : {0}", e->Source );
						 Console::WriteLine( "Message : {0}", e->Message );
				}
			}

	//private: System::Void textBox1_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	//		 }

};}
