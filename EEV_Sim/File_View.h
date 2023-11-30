#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace EEV_Sim {

	/// <summary>
	/// Summary for File_View
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class File_View : public System::Windows::Forms::Form
	{
	public:
		File_View(void)
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
		~File_View()
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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(File_View::typeid));
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			this->SuspendLayout();
			// 
			// richTextBox1
			// 
			this->richTextBox1->BackColor = System::Drawing::SystemColors::Info;
			this->richTextBox1->Location = System::Drawing::Point(12, 8);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->ReadOnly = true;
			this->richTextBox1->ShowSelectionMargin = true;
			this->richTextBox1->Size = System::Drawing::Size(1184, 684);
			this->richTextBox1->TabIndex = 4;
			this->richTextBox1->Text = L"fdfdfd\ndfd\ndfd\ndfd\ndf";
			// 
			// File_View
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1208, 705);
			this->Controls->Add(this->richTextBox1);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->Name = L"File_View";
			this->Text = L"Source File Name";
			this->Load += gcnew System::EventHandler(this, &File_View::File_View_Load);
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &File_View::Closed);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void File_View_Load(System::Object^  sender, System::EventArgs^  e) {
			
			C_KeyWords();
		//		 this->richTextBox1->TabStop = true;
		//		 this->richTextBox1->TabIndex = 48;
			//	 this->richTextBox1->Text == " ";

		//		 ReplaceCharacters(",","|",System::Drawing::Color::Red);
		//		 ColorCharacters("}", System::Drawing::Color::Red);
		//		 ColorCharacters("{", System::Drawing::Color::Red);

			 this->richTextBox1->Text->IndexOf(1);
			 this->richTextBox1->AutoSize;
			 this->richTextBox1->Find("\r",    1,    1 , RichTextBoxFinds::None); // just to reach the first line
			 }
	public: void C_KeyWords(void){
				 ColorCharacters("}", System::Drawing::Color::Red);
				 ColorCharacters("{", System::Drawing::Color::Red);
				 ColorCharacters("(", System::Drawing::Color::Red);
				 ColorCharacters(")", System::Drawing::Color::Red);
				 ColorCharacters("[", System::Drawing::Color::Red);
				 ColorCharacters("]", System::Drawing::Color::Red);

				 ColorCharacters("default", System::Drawing::Color::Blue);
				 ColorCharacters("switch", System::Drawing::Color::Blue);
				 ColorCharacters("case", System::Drawing::Color::Blue);
				 ColorCharacters("break", System::Drawing::Color::Blue);
			 ColorCharacters("if", System::Drawing::Color::Blue);
			 ColorCharacters("else", System::Drawing::Color::Blue);
			 ColorCharacters("while", System::Drawing::Color::Blue);
			ColorCharacters("for", System::Drawing::Color::Blue);

			 ColorCharacters("include", System::Drawing::Color::Blue);
			ColorCharacters("#", System::Drawing::Color::Blue);
			 ColorCharacters("define", System::Drawing::Color::Blue);
			 ColorCharacters("ifdef", System::Drawing::Color::Blue);
			 ColorCharacters("endif", System::Drawing::Color::Blue);
			 ColorCharacters("defined", System::Drawing::Color::Blue);

			ColorCharacters("namespace", System::Drawing::Color::AliceBlue);
			 ColorCharacters("void", System::Drawing::Color::Blue);
			 ColorCharacters("return", System::Drawing::Color::Blue);
			 ColorCharacters("const", System::Drawing::Color::Blue);
			 ColorCharacters("pragma", System::Drawing::Color::Blue);
			 ColorCharacters("volatile", System::Drawing::Color::Blue);

			 ColorCharacters("unsigned", System::Drawing::Color::Blue);
			 ColorCharacters("signed", System::Drawing::Color::Blue);
 			 ColorCharacters("bool", System::Drawing::Color::Blue);
		    ColorCharacters("BOOL", System::Drawing::Color::Blue);
			 ColorCharacters("char", System::Drawing::Color::Blue);
			 ColorCharacters("int", System::Drawing::Color::Blue);
 			 ColorCharacters("short", System::Drawing::Color::Blue);
			 ColorCharacters("float", System::Drawing::Color::Blue);
			 ColorCharacters("struct", System::Drawing::Color::Blue);
			 ColorCharacters("union", System::Drawing::Color::Blue);

			 ColorCharacters(">", System::Drawing::Color::Chocolate);
			 ColorCharacters("<", System::Drawing::Color::Chocolate);
			 ColorCharacters("+", System::Drawing::Color::Chocolate);
			 ColorCharacters("-", System::Drawing::Color::Chocolate);
			 ColorCharacters("*", System::Drawing::Color::Chocolate);
			 ColorCharacters("/ ", System::Drawing::Color::Chocolate);

			 ColorCharacters("!", System::Drawing::Color::Purple);
			 ColorCharacters("=", System::Drawing::Color::Purple);
			 ColorCharacters("&", System::Drawing::Color::Purple);

  			 ColorCharacters("--", System::Drawing::Color::Chocolate);
   			 ColorCharacters("++", System::Drawing::Color::Chocolate);
 			 ColorCharacters("==", System::Drawing::Color::Chocolate);
  			 ColorCharacters("!=", System::Drawing::Color::Chocolate);
			 ColorCharacters(">=", System::Drawing::Color::Chocolate);
			 ColorCharacters("<=", System::Drawing::Color::Chocolate);

   			 ColorCharacters("+=", System::Drawing::Color::Yellow);
 			 ColorCharacters("-=", System::Drawing::Color::Yellow);
			 ColorCharacters("/=", System::Drawing::Color::Yellow);
			 ColorCharacters("*=", System::Drawing::Color::Yellow);
			 
			 ColorCharacters("->", System::Drawing::Color::Purple);
	//		 ColorCharacters("//", System::Drawing::Color::DarkSeaGreen);
 		//	 ColorCharacters("/*", System::Drawing::Color::DarkSeaGreen);
 		//	 ColorCharacters("*/", System::Drawing::Color::DarkSeaGreen);
		//	 ColorCharacters("", System::Drawing::Color::Blue);
			 ColorFill("/*", "*/", 2,System::Drawing::Color::Green);
	//		 ColorFill("//", "\r\n", System::Drawing::Color::Green);
			 ColorFill("//", "\r", 1, System::Drawing::Color::Green);
//			 ColorFill("//", System::Environment::NewLine, System::Drawing::Color::Green);

		
			}

  	  public:
		  void ColorFill2(String^ start_text, String^ end_text    , Color^ ActiveColor ){
			  gcnew Color();
				 int Tot_length = this->richTextBox1->TextLength;
				int index = 0;
				int lastIndex = this->richTextBox1->Text->LastIndexOf(start_text);

				 while ( index < lastIndex ){
							this->richTextBox1->Find(start_text,    index,    Tot_length , RichTextBoxFinds::None);
							 this->richTextBox1->SelectionColor =   *ActiveColor;
							index = this->richTextBox1->Text->IndexOf(start_text,  index)+1;

							int secindex = this->richTextBox1->Find(end_text,   index, RichTextBoxFinds::None);
							while (   index < secindex){
									index++;
									this->richTextBox1->Select(index,1);		
									 this->richTextBox1->SelectionColor =   *ActiveColor;					
							}
				 }
		  }
	  public:
		  void ColorFill(String^ start_text, String^ end_text    ,  int CharacterCount , Color^ ActiveColor ){
			  gcnew Color();
				 int Tot_length = this->richTextBox1->TextLength;
				int index = 0;
				int lastIndex = this->richTextBox1->Text->LastIndexOf(start_text);

				 while ( index < lastIndex ){
							this->richTextBox1->Find(start_text,    index,    Tot_length , RichTextBoxFinds::None);
							 this->richTextBox1->SelectionColor =   *ActiveColor;
							index = this->richTextBox1->Text->IndexOf(start_text,  index)+1;

							int secindex = this->richTextBox1->Find(end_text,   index, RichTextBoxFinds::None);
							if( CharacterCount == 2){
								while (   index <= secindex){
									index++;
									this->richTextBox1->Select(index,1);		
									 this->richTextBox1->SelectionColor =   *ActiveColor;					
								}
							}
							if( CharacterCount == 1){
								while (   index < secindex){
									index++;
									this->richTextBox1->Select(index,1);		
									 this->richTextBox1->SelectionColor =   *ActiveColor;					
								}
							}
							//		index = this->richTextBox1->Text->IndexOf(text,index)+1;
										//	this->richTextBox1->Select(index,secindex - index )
									//	index = this->richTextBox1->Text->IndexOf(text,index)+1;	
				//			index = this->richTextBox1->Text->IndexOf(text,index)+1;
			//				index = this->richTextBox1->Text->IndexOf(text,index)+1;
//
			//				this->richTextBox1->Select(index,secindex - index );
			//				this->richTextBox1->Select(index,5 );
					//		  this->richTextBox1->SelectionColor =   *ActiveColor;
					//			index = this->richTextBox1->Text->IndexOf(text,secindex)+1;
					//       this->richTextBox1->Find("*/",RichTextBoxFinds::None);	
			//				for (;    endtext   != "*/"  ; index++  ){
												//index++;
											//endtext = 
										//		this->richTextBox1->Text[5];
					//							this->richTextBox1->Select(index,3);
											//	this->richTextBox1-
						//				   this->richTextBox1->SelectionColor =   *ActiveColor;
				//			}
						//	this->richTextBox1->Find("*/",RichTextBoxFinds::None);
					//		 this->richTextBox1->SelectionColor =   *ActiveColor;
							// this->richTextBox1->SelectionCharOffset
				//			index = this->richTextBox1->Text->IndexOf(text,index)+1;			
				 }
		  }
	  public:
		  void ColorCharacters(String^ text, Color^ ActiveColor ){
			  gcnew Color();
				 int len = this->richTextBox1->TextLength;
				int index = 0;
				int lastIndex = this->richTextBox1->Text->LastIndexOf(text);
				 while ( index < lastIndex ){
							this->richTextBox1->Find(text,index,len, RichTextBoxFinds::None);
							 this->richTextBox1->SelectionColor =   *ActiveColor;
							 index = this->richTextBox1->Text->IndexOf(text,index)+1;
				 }
		  }



	private: System::Void Closed(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
				//NumberOfLines = 3;

			 }
	};
}
