#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Reflection;
namespace EEV_Sim{

	/// <summary>
	/// Summary for Info
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class Info : public System::Windows::Forms::Form
	{
	public:
		Info(void)
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
		~Info()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^  textBox1;
	protected: 
	private: System::Windows::Forms::ListBox^  listBox1;
	private:
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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Info::typeid));
			this->SuspendLayout();
			// 
			// Info
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(416, 288);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->Name = L"Info";
			this->Text = L"Info";
			this->Load += gcnew System::EventHandler(this, &Info::Info_Load);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void listBox1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
      // Return if no list item is selected.

      if ( listBox1->SelectedIndex == -1 )
            return;


      // Get the property name from the list item.
      String^ propname = listBox1->Text;
      if ( propname->Equals( "PowerStatus" ) )
      {

         // Cycle and display the values of each property of the PowerStatus property.
         textBox1->Text = String::Concat( textBox1->Text, "\r\nThe value of the PowerStatus property is:" );
         Type^ t = System::Windows::Forms::PowerStatus::typeid;
         array<PropertyInfo^>^pi = t->GetProperties();
         for ( int i = 0; i < pi->Length; i++ )
         {
            Object^ propval = pi[ i ]->GetValue( SystemInformation::PowerStatus, nullptr );
            textBox1->Text = String::Format( "{0}\r\n    PowerStatus.{1} is: {2}", textBox1->Text, pi[ i ]->Name, propval );

         }
      }
      else
      {

         // Display the value of the selected property of the SystemInformation type.
         Type^ t = System::Windows::Forms::SystemInformation::typeid;
         array<PropertyInfo^>^pi = t->GetProperties();
         PropertyInfo^ prop = nullptr;
         for ( int i = 0; i < pi->Length; i++ )
            if ( pi[ i ]->Name == propname )
            {
               prop = pi[ i ];
               break;
            }
         Object^ propval = prop->GetValue( nullptr, nullptr );
         textBox1->Text = String::Format( "{0}\r\nThe value of the {1} property is: {2}", textBox1->Text, propname, propval );
      }

   }

   void InitForm()
   {

      // Initialize the form settings
      this->listBox1 = gcnew System::Windows::Forms::ListBox;
      this->textBox1 = gcnew System::Windows::Forms::TextBox;
      this->listBox1->Anchor = (System::Windows::Forms::AnchorStyles)(System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right);
      this->listBox1->Location = System::Drawing::Point( 8, 16 );
      this->listBox1->Size = System::Drawing::Size( 172, 496 );
      this->listBox1->TabIndex = 0;
      this->textBox1->Anchor = (System::Windows::Forms::AnchorStyles)(System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right);
      this->textBox1->Location = System::Drawing::Point( 188, 16 );
      this->textBox1->Multiline = true;
      this->textBox1->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
      this->textBox1->Size = System::Drawing::Size( 420, 496 );
      this->textBox1->TabIndex = 1;
      this->ClientSize = System::Drawing::Size( 616, 525 );
      this->Controls->Add( this->textBox1 );
      this->Controls->Add( this->listBox1 );
      this->Text = "Select a SystemInformation property to get the value of";
   }



			
	private: System::Void Info_Load(System::Object^  sender, System::EventArgs^  e) {
		this->SuspendLayout();
      InitForm();

      // Add each property of the SystemInformation class to the list box.
      Type^ t = System::Windows::Forms::SystemInformation::typeid;
      array<PropertyInfo^>^pi = t->GetProperties();
      for ( int i = 0; i < pi->Length; i++ )
         listBox1->Items->Add( pi[ i ]->Name );
      textBox1->Text = String::Format( "The SystemInformation class has {0} properties.\r\n", pi->Length );

      // Configure the list item selected handler for the list box to invoke a 
      // method that displays the value of each property.
      listBox1->SelectedIndexChanged += gcnew EventHandler( this, &Info::listBox1_SelectedIndexChanged );
      this->ResumeLayout( false );

			 }
			 
};}
