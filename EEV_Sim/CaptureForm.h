#pragma once
//    using namespace EEV_Sim;
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Drawing::Imaging;
   using namespace System::Drawing::Printing;
  	using namespace System;
	using namespace System::Windows;
	using namespace System::Windows::Forms;
	using namespace System::IO;

	using namespace System::Collections::Generic;
	using namespace System::Threading;


namespace EEV_Sim {

	/// <summary>
	/// Summary for CaptureForm
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class CaptureForm : public System::Windows::Forms::Form
	{
	public:
		CaptureForm(void)
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
		~CaptureForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^  pictureBox1;

	private: 
	private: System::ComponentModel::IContainer^  components;
	public: 
	protected: 

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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(CaptureForm::typeid));
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureBox1->Location = System::Drawing::Point(0, 0);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(608, 288);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			// 
			// CaptureForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(792, 573);
			this->Controls->Add(this->pictureBox1);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->Name = L"CaptureForm";
			this->Text = L"Screenshot Picture";
			this->MinimumSizeChanged += gcnew System::EventHandler(this, &CaptureForm::ResizeDone_To_form2);
			this->Load += gcnew System::EventHandler(this, &CaptureForm::CaptureForm_Load);
			this->RegionChanged += gcnew System::EventHandler(this, &CaptureForm::ResizeDone_To_form2);
			this->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &CaptureForm::ResizeDone_To_form3);
			this->MaximizedBoundsChanged += gcnew System::EventHandler(this, &CaptureForm::ResizeDone_To_form2);
			this->ContextMenuStripChanged += gcnew System::EventHandler(this, &CaptureForm::ResizeDone_To_form2);
			this->MouseCaptureChanged += gcnew System::EventHandler(this, &CaptureForm::ResizeDone_To_form2);
			this->DoubleClick += gcnew System::EventHandler(this, &CaptureForm::ResizeDone_To_form2);
			this->Click += gcnew System::EventHandler(this, &CaptureForm::ResizeDone_To_form2);
			this->Move += gcnew System::EventHandler(this, &CaptureForm::ResizeDone_To_form2);
			this->ResizeEnd += gcnew System::EventHandler(this, &CaptureForm::ResizeDone_To_form2);
			this->MaximumSizeChanged += gcnew System::EventHandler(this, &CaptureForm::ResizeDone_To_form2);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	//	static	String ^ Log_Directory = Directory::GetCurrentDirectory() + "\\Log\\";
	private: System::Void CaptureForm_Load(System::Object^  sender, System::EventArgs^  e) {

				String ^ Capture_Directory = Directory::GetCurrentDirectory() + "\\Capture\\";
				//		String ^ Capture_Directory = "D:\\ACIT_SIM\\LOG"; 

						CaptureScreen(false,Capture_Directory); // if true hides capture menu
						ResizePicbox();
				//		this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
					//	this->Size = System::Windows::Forms::FormStartPosition::WindowsDefaultLocation;
						this->Width = 800;
						this->Height = 450;
						this->Location = Point(25,25);
			 }

 public: void CaptureScreen(bool ClearCaptureForm,String^ path){

				try{		
					if(ClearCaptureForm == true){
			//			this->WindowState = System::Windows::Forms::FormWindowState::Minimized;
					//	this->TopMost = false;
					}
					Rectangle^ bounds;
	//					if(ClearCaptureForm == true ) System::Threading::Thread::Sleep(250);//  gecerli form gorunmesin istiyorsan bunu koy
						System::Drawing::Bitmap^ screenshot;
						Graphics^ graph;
						
			//			bounds = Screen::PrimaryScreen->WorkingArea; // all screen bounds
						bounds = this->Bounds; // current form bounds
					//	bounds-


				//		bounds= Screen::PrimaryScreen->GetWorkingArea(System::Drawing::Point( 5, 5 ),System::Drawing::Rectangle (0,0,1600,900),System::Windows::Forms::Control ^ctl);
					//	screenshot = gcnew System::Drawing::Bitmap(bounds->Width,bounds->Height,System::Drawing::Imaging::PixelFormat::Format32bppArgb);
						screenshot = gcnew System::Drawing::Bitmap(bounds->Width,bounds->Height,System::Drawing::Imaging::PixelFormat::Format32bppArgb);// all area
						graph = Graphics::FromImage(screenshot);
					graph->CopyFromScreen(bounds->X, bounds->Y, 0, 0, bounds->Size, CopyPixelOperation::SourceCopy); // all screen copy

					//graph->CopyFromScreen(new Point(bounds.Left,bounds.Top), Point.Empty, bounds.Size);

			//		Point^ Pnt =  gcnew Point(bounds->Left,bounds->Top);
				//	Point^ Pnt =  gcnew Point();
					//graph->CopyFromScreen(Pnt(bounds->Left,bounds->Top), Pnt->Empty, bounds->Size);
		//			graph->CopyFromScreen(Pnt::boundsbounds->Left,bounds->Top), Pnt->Empty, bounds->Size);
	
						pictureBox1->Image = screenshot;
					if(ClearCaptureForm == true){
	//						this->WindowState = System::Windows::Forms::FormWindowState::Normal;
						//	this->TopMost = true;
					}
				 }
				 catch(Exception^ ex)
				 {
					 MessageBox::Show(ex->Message);
				 }
				 if(Directory::Exists(path) == false){
					 try{
						 Directory::CreateDirectory(path);
					 }
					 catch(Exception^ ){
							MessageBox::Show("Error No Directory // Can't Create The Directory");
					 }
				 }
				 if(Directory::Exists(path) == true){
						DateTime d1 = DateTime::Now;
						int Hour = d1.Hour;   int Min = d1.Minute;  int Sec = d1.Second; int Day = d1.Day; int Month = d1.Month; int Year = d1.Year;
						 String^  HourZero="";		  String^   MinZero="";		 String^  SecZero=""; 
						  if(Hour < 10 ) HourZero = "0";else HourZero = "";
						  if(Min < 10 ) MinZero = "0";else MinZero = "";
						  if(Sec < 10 ) SecZero = "0";else SecZero = "";
						String ^ Mystring = Day.ToString() + "." +  Month.ToString() + "."+ Year.ToString() + "_";
						Mystring += HourZero +  Hour.ToString()+"."+MinZero+Min.ToString()+"."+SecZero+Sec.ToString() ;

						pictureBox1->Image->Save(path  + "\\" +Mystring + ".jpg");
					 this->Text = "Screenshot Picture saved to : " + path  + "\\" +Mystring + ".jpg";
				 }		
				 else  this->Text = "Screenshot Picture not saved...  File error !.. ";
		 }
		 public:  void ResizePicbox(void){
					  this->pictureBox1->Height = this->Height - 30;
				  this->pictureBox1->Width = this->Width  ;
		 }

private: System::Void ResizeDone_To_form2(System::Object^  sender, System::EventArgs^  e) {
			 ResizePicbox();
		 }

private: System::Void ResizeDone_To_form3(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 ResizePicbox();
		 }
};
}
