#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace EEV_Sim {

	/// <summary>
	/// Summary for Password
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class Password : public System::Windows::Forms::Form
	{
	public:
		Password(void)
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
		~Password()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::Button^  Password_Button;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TextBox^  textBox2;

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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Password::typeid));
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->Password_Button = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// textBox1
			// 
			this->textBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->textBox1->Location = System::Drawing::Point(64, 56);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(160, 22);
			this->textBox1->TabIndex = 0;
			this->textBox1->UseSystemPasswordChar = true;
			// 
			// Password_Button
			// 
			this->Password_Button->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Password_Button->Location = System::Drawing::Point(64, 80);
			this->Password_Button->Name = L"Password_Button";
			this->Password_Button->Size = System::Drawing::Size(160, 64);
			this->Password_Button->TabIndex = 1;
			this->Password_Button->Text = L"     Press  To \r\nVerify The Code";
			this->Password_Button->UseVisualStyleBackColor = true;
			this->Password_Button->Click += gcnew System::EventHandler(this, &Password::Password_Button_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(72, 24);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(156, 32);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Please Enter Access \r\n      Code Below";
			this->label1->Click += gcnew System::EventHandler(this, &Password::label1_Click);
			// 
			// textBox2
			// 
			this->textBox2->Font = (gcnew System::Drawing::Font(L"Miriam", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(177)));
			this->textBox2->ForeColor = System::Drawing::Color::Red;
			this->textBox2->Location = System::Drawing::Point(64, 168);
			this->textBox2->Multiline = true;
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(152, 24);
			this->textBox2->TabIndex = 3;
			// 
			// Password
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(292, 209);
			this->ControlBox = false;
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->Password_Button);
			this->Controls->Add(this->textBox1);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->Name = L"Password";
			this->Text = L"Access Code Verification";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: System::Void Password_Button_Click(System::Object^  sender, System::EventArgs^  e) {
				 Close();	
				 if(this->textBox1->Text == "Acit") {
					 this->textBox2->Text  = " Dogru  !! ";
					 Close();		
				 }
				 else  {
					 	this->textBox2->Text  = " yanlis tekrar dene  !! ";
						// Close();
					//	Application::Exit();
						//MessageBox-Show("Dot Net Perls is awesome.");
						  
			//			unsigned int f = 0;
		//			for(unsigned int i = 0; i<55555;i++){
							
			//				f++;
								//	this->textBox1->Text  = " olmadi simdi bak!! ";
						//}
						//Application::Exit();
					//	 Close();
			//	 }
			 }
 }
	
private: System::Void label1_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
};
}
