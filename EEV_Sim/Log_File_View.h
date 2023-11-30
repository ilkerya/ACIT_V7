#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace EEV_Sim {

	/// <summary>
	/// Summary for Log_File_View
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class Log_File_View : public System::Windows::Forms::Form
	{
	public:
		Log_File_View(void)
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
		~Log_File_View()
		{
			if (components)
			{
				delete components;
			}
		}
	public: System::Windows::Forms::RichTextBox^  richTextBox1;
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
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			this->SuspendLayout();
			// 
			// richTextBox1
			// 
			this->richTextBox1->Location = System::Drawing::Point(48, 48);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->Size = System::Drawing::Size(492, 272);
			this->richTextBox1->TabIndex = 0;
			this->richTextBox1->Text = L"";
			// 
			// Log_File_View
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1302, 592);
			this->Controls->Add(this->richTextBox1);
			this->Name = L"Log_File_View";
			this->Text = L"Log_File_View";
			this->Load += gcnew System::EventHandler(this, &Log_File_View::Log_File_View_Load);
			this->ResumeLayout(false);

		}
#pragma endregion


			  public: void ReplaceCharacters(String^  CharRemove,   String^  CharReplace,   Color^ ActiveColor ){
			  gcnew Color();
			  int maxdatacounter = 0;
				 int len = this->richTextBox1->TextLength;
				int index = 0;
				int lastIndex = this->richTextBox1->Text->LastIndexOf(CharRemove);
				 while ( index < lastIndex ){
							this->richTextBox1->Find(CharRemove,index,len, RichTextBoxFinds::None);
							this->richTextBox1->SelectionColor =*ActiveColor;
/*	    					 switch(maxdatacounter){
									case 0:  this->richTextBox1->SelectionColor =   System::Drawing::Color::MediumPurple;break;
									case 1:this->richTextBox1->SelectionColor = System::Drawing::Color::DarkSeaGreen;break;
									case 2:this->richTextBox1->SelectionColor = System::Drawing::Color::DarkOrange;break;
									case 3:this->richTextBox1->SelectionColor = System::Drawing::Color::DimGray;break;
									default:this->richTextBox1->SelectionColor =*ActiveColor;break;
							 }
	*/						 if( this->richTextBox1->SelectedText == ",") {
									 this->richTextBox1->SelectedText = CharReplace;
		//					maxdatacounter ++;
	// 									if(maxdatacounter > 19)maxdatacounter =0;
							 }

							 index = this->richTextBox1->Text->IndexOf(CharRemove,index);
				 }
			  }
	private: System::Void Log_File_View_Load(System::Object^  sender, System::EventArgs^  e) {
				ReplaceCharacters(",","|",System::Drawing::Color::Red);
		//		 ColorCharacters("}", System::Drawing::Color::Red);
		//		 ColorCharacters("{", System::Drawing::Color::Red);
			 this->richTextBox1->Text->IndexOf(1);
			 this->richTextBox1->AutoSize;
			 this->richTextBox1->Find("\r",    1,    1 , RichTextBoxFinds::None); // just to reach the first line


			 }
	};
}
