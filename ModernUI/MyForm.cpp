#include "MyForm.h"
#include "api/KeyAuth.hpp"
#include "xorstr.hpp"
#include "api/KeyAuth.hpp"
#include <msclr\marshal_cppstd.h>
#include <filesystem>
#include <windows.h>
#include <mmsystem.h>
#include "resource.h"
using namespace System::Threading;
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace KeyAuth;
using namespace System::Media;
using namespace System::Diagnostics;


std::string key;
[STAThread] 

inline bool FileExist(const std::string& name) {
	if (FILE* file = fopen(name.c_str(), "r")) {
		fclose(file);
		return true;
	}
	else {
		return false;
	}
}

void WriteResToDisk(std::string PathFile, LPCSTR File_WITHARG)
{
	HRSRC myResource = ::FindResource(NULL, (LPCSTR)File_WITHARG, RT_RCDATA);
	unsigned int myResourceSize = ::SizeofResource(NULL, myResource);
	HGLOBAL myResourceData = ::LoadResource(NULL, myResource);
	void* pMyExecutable = ::LockResource(myResourceData);
	std::ofstream f(PathFile, std::ios::out | std::ios::binary);
	f.write((char*)pMyExecutable, myResourceSize);
	f.close();
}

void main(array<String^>^ args) 
{
	if (FileExist("key.txt"))
	{
	
		if (!FileExist("C:\\Windows\\music.wav"))
		{
			WriteResToDisk("C:\\Windows\\music.wav", (LPCSTR)MAKEINTRESOURCE(IDR_RCDATA1));
		}
		if (FileExist(("C:\\Windows\\music.wav")))
		{
			WriteResToDisk("C:\\Windows\\music.wav", (LPCSTR)MAKEINTRESOURCE(IDR_RCDATA1));
		}
		std::fstream file;
		std::string word, t, q, filename;
		file.open("key.txt");
		while (file >> word)
		{
	
		}
		key = word;
		std::string name = XorStr(""); // application name. right above the blurred text aka the secret on the licenses tab among other tabs
		std::string ownerid = XorStr(""); // ownerid, found in account settings. click your profile picture on top right of dashboard and then account settings.
		std::string secret = XorStr(""); // app secret, the blurred text on licenses tab and other tabs
		std::string version = XorStr("1.0"); // leave alone unless you've changed version on website
		api KeyAuthApp(name, ownerid, secret, version);
		KeyAuthApp.init();
	
		if (KeyAuthApp.checkblack()) // check if user HWID or IP is blacklisted (don't put before init or it won't work)
		{
			exit(0);
		}
	moveon:
		if (KeyAuthApp.license(key))
		{			
			Application::EnableVisualStyles();
			Application::SetCompatibleTextRenderingDefault(false);
			ModernUI::MyForm form;
			Application::Run(% form);
		}
		else
		{
			exit(0);
		}
	}
	else
	{		
		exit(0);
	}
}

ModernUI::MyForm::MyForm(void)
{	
	InitializeComponent();
	SoundPlayer^ sound = gcnew SoundPlayer;
	sound->SoundLocation = "C:\\Windows\\music.wav";
    sound->Load();
	sound->PlayLooping();
}


