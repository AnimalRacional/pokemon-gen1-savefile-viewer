#include "MainForm.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
void Main(array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	bool debug = false;
	for (int i = 0; i < sizeof(args) / sizeof(args[0]); i++) {
		if (args->Equals("-d")) {
			debug = true;
			break;
		}
	}
	Gen1savefileediting::MainForm form(debug);
	Application::Run(% form);
}