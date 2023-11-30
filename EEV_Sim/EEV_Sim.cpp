// EEV_Sim.cpp : main project file.

#include "stdafx.h"
#include "math.h"
//#include "marshal_windows.h"
//#include "marshal_cppstd.h"

#define MANAGED_DOTNET_COMPILER   // default 1. priority  SELECT ONLY ONE
#define ACIT_INCLUDED  // TO ADD  INITIAL MEMORY USAGE WITHOUT ANY ACIT LIBRARY
#define ACIT_MEMORY     // TO ADD  ONLY ACIT  MEMORY USAGE
#define ACIT_FUNCTIONS  // TO ADD  TOTAL  ACIT  MEMORY USAGE

#include "ACIT.h"
#include "FileErr.h"
#include "EndApp.h"
#include "Abt.h"
//#include "Password.h"
#include "Strt.h"
#include "Info.h"
#include "CInfo.h"
#include "Form1.h"
#include "Information_Menu.h"
#include "File_View.h"
#include "CaptureForm.h"
#using <System.dll>
using namespace ACIT_Stack;
using namespace EEV_Sim;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// Enabling Windows XP visual effects before any controls are created
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 
	String^  Pic1_path = Environment::SystemDirectory ;
	String^  Pic2_path =   "NPlot.dll";  // Resources
				if ( File::Exists( Pic1_path )  ||    File::Exists( Pic2_path )    ) {
					//	Application::Run(gcnew Strt()); // staring logo
					//	Application::Run(gcnew Password());
						Application::Run(gcnew Form1());
				}
				else{
			//			System::Windows::Forms::MessageBox::Show("!! NPlot.dll missing  at Windows System\r\nClick  obtain from\r\n");
						Application::Run(gcnew FileErr());
						//	Application::Exit();
				}
		return 0;
}