#include <iostream>
#include <string>
#include "MainForm.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Diagnostics;
[STAThread]
void main(array<String^>^ args)
{
	AllocConsole();
	AttachConsole(ATTACH_PARENT_PROCESS);
	Trace::Listeners->Add( gcnew TextWriterTraceListener( Console::Out ) );
	Trace::AutoFlush = true;
	Trace::Indent();
	Trace::WriteLine( "Entering Main" );
	Console::WriteLine( "Hello World." );
	Trace::WriteLine( "Exiting Main" );
	Trace::Unindent();

	Debug::WriteLine("test");
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Ivanich::MyForm Form;
	Application::Run(%Form);

}