#include "stdafx.h"
#include "Menú.h"

using namespace System;
using namespace System::Windows::Forms;  [STAThread]
void main()
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);  Application::Run(gcnew
		TrabajoParcial::Menú()); //Project 1 es el nombre del proyecto
}