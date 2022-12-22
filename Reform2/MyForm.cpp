#define _WINSOCKAPI_
#include <windows.h>
#include "MyForm.h"
#pragma warning(disable: 4996)
using namespace System;
using namespace System::Windows::Forms;

    bool Connect(std::string ip) {
        WSADATA wsaData;
        WORD DLLVersion = MAKEWORD(2, 1);
        if (WSAStartup(DLLVersion, &wsaData) != 0)
        {
			return false;
        }

        SOCKADDR_IN addr;
        int sizeofaddr = sizeof(addr);
        addr.sin_addr.s_addr = inet_addr(ip.c_str());
        addr.sin_port = htons(1111);
        addr.sin_family = AF_INET;


        Connection = socket(AF_INET, SOCK_STREAM, 0);
        if (connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0) {
            return false;
        }
        else {
            return true;
        }
    }
    
    char msg_c[13] = { 0 };
    int size;

[STAThreadAttribute]
void main(array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	Reform::MyForm form;
	Application::Run(% form);
}

inline bool Reform::MyForm::nick_ip(String^ nick, String^ ipS) {
	if (nick->Length < 2 || nick->Length > 10) {
		MessageBox::Show(this, "Your nick should consist of 2 to 10 characters!", "Warning", MessageBoxButtons::OK, MessageBoxIcon::Warning);
		return false;
	}

	if (ipS->Length < 9) {
		MessageBox::Show(this, "IP  should consist of 10 or more characters!", "Warning", MessageBoxButtons::OK, MessageBoxIcon::Warning);
		return false;
	}
	return true;
}

inline System::Void Reform::MyForm::YesButton_Click(System::Object^ sender, System::EventArgs^ e) {
	// переход со второй на третью

	memset(msg_c, '\0', 10);
	strncpy(msg_c, "23", 2);
	strcat(msg_c, id);
	size = strlen(msg_c) + 1;
	send(Connection, msg_c, size, NULL);

	NoButton->Visible = false;
	YesButton->Visible = false;
	label3->Visible = false;
}

inline System::Void Reform::MyForm::NoButton_Click(System::Object^ sender, System::EventArgs^ e) {
	memset(msg_c, '\0', 10);
	strncpy(msg_c, "33", 2);
	strcat(msg_c, id);
	size = strlen(msg_c) + 1;
	send(Connection, msg_c, size, NULL);

	NoButton->Visible = false;
	YesButton->Visible = false;
	label3->Visible = false;
	button1->Visible = false;
	button2->Visible = false;
	button3->Visible = false;
	pictureBox1->Visible = false;
	pictureBox2->Visible = false;

	listBox1->Visible = true;
	InviteButton->Visible = true;
}

inline System::Void Reform::MyForm::RegistrationButton_Click(System::Object^ sender, System::EventArgs^ e) {
	String^ nick = NameTextBox->Text;
	String^ ip = IPTextBox->Text;
    
	if (nick_ip(nick, ip)) {
		std::string name = msclr::interop::marshal_as<std::string>(nick);
		std::string ipS = msclr::interop::marshal_as<std::string>(ip);
			
		if (Connect(ipS)) {
            strncpy(msg_c, "01", 2);
            strncat(msg_c, name.c_str(), 10);
            size = strlen(msg_c) + 1;
            send(Connection, msg_c, size, NULL);
			iResult = 1;  
        }
		else {
			toolStripStatusLabel1->Text = "NO CONNECTION";
        }
	}
}

inline System::Void Reform::MyForm::InviteButton_Click(System::Object^ sender, System::EventArgs^ e) {
	if (listBox1->SelectedIndex>=0) {
		InviteButton->Visible = false;
		memset(msg_c, '\0', sizeof(msg_c));
		strcpy(msg_c, "03");
		std::string Selected_string = msclr::interop::marshal_as<std::string>(listBox1->SelectedItem->ToString());
		for (int i = 0; i < 5; i++) {
			if (Selected_string[i] == ' ') {
				break;
			}
			strncat(msg_c, (Selected_string.c_str()) + i, 1);
		}
		size = strlen(msg_c) + 1;
		send(Connection, msg_c, size, NULL);
		Selected_string = "Waiting for answer player ";
		Selected_string += (msg_c + 2);
		toolStripStatusLabel1->Text = msclr::interop::marshal_as<String^>(Selected_string);
	}
	else {
		toolStripStatusLabel1->Text = "Choose player";
	}
}

inline System::Void Reform::MyForm::BackButton_Click(System::Object^ sender, System::EventArgs^ e){

	// переход с третьей на вторую

	memset(msg_c, '\0', 10);
	strncpy(msg_c, "84", 2);
	size = strlen(msg_c) + 1;
	send(Connection, msg_c, size, NULL);

}

inline System::Void Reform::MyForm::cell1_Click(System::Object^ sender, System::EventArgs^ e) {
	memset(msg_c, '\0', 10);
	strncpy(msg_c, "44r", 3);
	size = strlen(msg_c) + 1;
	send(Connection, msg_c, size, NULL);
	button1->Visible = false;
	button2->Visible = false;
	button3->Visible = false;
	pictureBox1->ImageLocation = "Rock.jpg";
		//"E:/Codes(2021)/Reform2/Release/Pictures/Rock.jpg";
	pictureBox1->Load();


	pictureBox2->ImageLocation = "Paper.jpg";
		//"E:/Codes(2021)/Reform2/Release/Pictures/whut.png";
	pictureBox2->Load();
}

inline System::Void Reform::MyForm::cell2_Click(System::Object^ sender, System::EventArgs^ e) {
	memset(msg_c, '\0', 10);
	strncpy(msg_c, "44p", 3);
	size = strlen(msg_c) + 1;
	send(Connection, msg_c, size, NULL);
	button1->Visible = false;
	button2->Visible = false;
	button3->Visible = false;
	pictureBox1->ImageLocation = "Paper.jpg";
		//"E:/Codes(2021)/Reform2/Release/Pictures/Paper.jpg";
	pictureBox1->Load();


	pictureBox2->ImageLocation = "whut.png";
		//"E:/Codes(2021)/Reform2/Release/Pictures/whut.png";
	pictureBox2->Load();
}

inline System::Void Reform::MyForm::cell3_Click(System::Object^ sender, System::EventArgs^ e) {
	memset(msg_c, '\0', 10);
	strncpy(msg_c, "44s", 3);
	size = strlen(msg_c) + 1;
	send(Connection, msg_c, size, NULL);
	button1->Visible = false;
	button2->Visible = false;
	button3->Visible = false;
	pictureBox1->ImageLocation = "scissors.png"; //"E:/Codes(2021)/Reform2/Release/Pictures/scissors.png";
	pictureBox1->Load();


	pictureBox2->ImageLocation = "whut.png"; //"E:/Codes(2021)/Reform2/Release/Pictures/whut.png";
	pictureBox2->Load();
}


inline System::Void Reform::MyForm::NameTextBox_KeyPress_1(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {

		if ((!Char::IsLetter(e->KeyChar) || e->KeyChar < 0 || e->KeyChar > 127) && (e->KeyChar != (char)Keys::Back))
		{
			e->Handled = true;
			toolStripStatusLabel1->Text = "USE ENGLISH LETTERS";
		}
}
