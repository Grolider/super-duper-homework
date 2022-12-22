#pragma once
#include "msclr\marshal_cppstd.h"
#pragma comment(lib,"ws2_32.lib")
#include <WinSock2.h>
#include <string>
#include <time.h>

SOCKET Connection;
char id[10];
char key;
int count;//переменна€  дл€ счЄта строк в сообщении об игроках
std::string _key;
std::string text;
char* list[100];
int rounds=1;

#pragma warning(disable: 4996)
namespace Reform {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading;

	/// <summary>
	/// —водка дл€ MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
			ClientHandlerThread = gcnew Thread(gcnew ThreadStart(this, &MyForm::ClientHandler));
			ClientHandlerThread->IsBackground = true;
			ClientHandlerThread->Start();
		}


		void Update() {

			button1->Visible = false;
			button2->Visible = false;
			button3->Visible = false;
			pictureBox1->Visible = false;
			pictureBox2->Visible = false;
			BackButton->Visible = false;
			label1->Visible = false;
			label2->Visible = false;

			NameLabel->Visible = false;
			IPLabel->Visible = false;
			NameTextBox->Visible = false;
			IPTextBox->Visible = false;
			RegistrationButton->Visible = false;
			NoButton->Visible = false;
			YesButton->Visible = false;
			label3->Visible = false;

			listBox1->Visible = true;
			InviteButton->Visible = true;

			listBox1->Items->Clear();
			for (int i = 0; i < count; i++) {

				text = list[i];
				listBox1->Items->Add(gcnew System::String(text.c_str()));

			}
			rounds = 1;
			//toolStripStatusLabel1->Text = "";
		}

		void PlayerDisconnected() {
			Update();
			text = "Connection with player ";
			text += id;
			text += " failed";
			toolStripStatusLabel1->Text = msclr::interop::marshal_as<String^>(text);
		}

		void Invitation() {
			listBox1->Visible = false;
			label3->Visible = false;
			InviteButton->Visible = false;

			NoButton->Visible = true;
			YesButton->Visible = true;

			text = "Player ";
			text += id;
			text += " invited you to game";
			label3->Text= msclr::interop::marshal_as<String^>(text);
			label3->Visible = true;
			toolStripStatusLabel1->Text = "New invitation";
		}

		void RefusedInvitation() {
			Update();
			text = "Player ";
			text += id;
			text += " refused your invitation";
			toolStripStatusLabel1->Text = msclr::interop::marshal_as<String^>(text);
		}

		void GameStart() {
			NameLabel->Visible = false;
			IPLabel->Visible = false;
			NameTextBox->Visible = false;
			IPTextBox->Visible = false;
			RegistrationButton->Visible = false;
			NoButton->Visible = false;
			YesButton->Visible = false;
			label3->Visible = false;
			listBox1->Visible = false;
			InviteButton->Visible = false;
			BackButton->Visible = false;

			label1->Visible = true;
			label2->Visible = true;
			pictureBox1->Visible = true;
			pictureBox2->Visible = true;
			if (rounds==1)
			{
				pictureBox1->ImageLocation = "whut.png";
				pictureBox2->ImageLocation = "whut.png";
				pictureBox1->Load();
				pictureBox2->Load();
			}

			button1->Visible = true;
			button2->Visible = true;
			button3->Visible = true;

			YourMoveMSG();
		}

		void YourMoveMSG() {
			toolStripStatusLabel1->Text = "Round " + rounds.ToString();
		}

		void OpponentMoveMSG() {
			toolStripStatusLabel1->Text = "Opponent move...";
		}

		void OpponentMoveView() {
			//images
			switch (key)
			{
			case 'r':
				pictureBox2->ImageLocation = "Rock.jpg"; 
					//"E:/Codes(2021)/Reform2/Release/Pictures/Rock.jpg";
				break;
			case 'p':
				pictureBox2->ImageLocation = "Paper.jpg";
					//"E:/Codes(2021)/Reform2/Release/Pictures/Paper.jpg";
				break;
			case 's':
				pictureBox2->ImageLocation = "scissors.png";
					// "E:/Codes(2021)/Reform2/Release/Pictures/scissors.png";
				break;
			default:
				break;
			}
			pictureBox2->Load();
			pictureBox2->Visible = true;
			rounds++;

			time_t Start = time(NULL);
			if (rounds!=4)
			{

				if (this->InvokeRequired) {
					this->Invoke(gcnew Action(this, &MyForm::GameStart));
				}
				else {
					GameStart();
				}
			}
		}

		void VictoryMSG() {
			BackButton->Visible = true;
			toolStripStatusLabel1->Text = "VICTORY!";
		}

		void DefeatMSG() {
			BackButton->Visible = true;
			toolStripStatusLabel1->Text = "DEFEAT";
		}

		void DrawMSG() {
			BackButton->Visible = true;
			toolStripStatusLabel1->Text = "DRAW";
		}

		void Disconnect() {
			NameLabel->Visible = true;
			IPLabel->Visible = true;
			NameTextBox->Visible = true;
			IPTextBox->Visible = true;
			RegistrationButton->Visible = true;

			listBox1->Visible = false;
			label3->Visible = false;
			InviteButton->Visible = false;
			NoButton->Visible = false;
			YesButton->Visible = false;

			button1->Visible = false;
			button2->Visible = false;
			button3->Visible = false;
			pictureBox1->Visible = false;
			pictureBox2->Visible = false;
			label1->Visible = false;
			label2->Visible = false;

			toolStripStatusLabel1->Text = "Connection failed";
		}
private: System::Windows::Forms::Button^ button1;
public:
private: System::Windows::Forms::Button^ button2;
private: System::Windows::Forms::Button^ button3;
private: System::Windows::Forms::PictureBox^ pictureBox1;
private: System::Windows::Forms::PictureBox^ pictureBox2;
private: System::Windows::Forms::Label^ label1;
private: System::Windows::Forms::Label^ label2;

		int iResult = 0;
		//функци€ дл€ обработки сообщений с сервера
		void ClientHandler() {

			char msg[2500];
			char code[2] = "";

			int n;//переменна€ дл€ исправного считывани€ сообщени€ по символам
			int size;//переменна€ размера отправл€емого сообщени€
			char msg_c[10];
			while (true) {
				if (iResult > 0) {
					while (iResult > 0) {
						iResult = recv(Connection, msg, 2500, NULL);
						strncpy(code, msg, 2);
						switch (atoi(code))
						{
						case 2://код списка игроков
							n = 1;
							for (int i = 0; i < 100; i++) {
								count = i;
								if (msg[n + 1] == '\n') break;
								if (n == sizeof(msg)) break;
								list[i] = new char[25];
								strcpy(list[i], "");
								for (int j = n + 1; j < sizeof(msg); j++) {
									if (msg[j] == '\n') {
										n = j;
										break;
									}
									strncat(list[i], msg + j, 1);
									if (msg[j] == '\0') {
										j = sizeof(msg);
										n = j;
									}
								}
							}
							if (iResult > 0) {
								if (this->InvokeRequired) {
									this->Invoke(gcnew Action(this, &MyForm::Update));
								}
								else {
									Update();
								}
							}
							break;

						case 3://код ошибки соединени€ с игроком
							strcpy(id, msg + 2);

							memset(msg_c, '\0', 10);
							strncpy(msg_c, "84", 2);
							size = strlen(msg_c) + 1;
							send(Connection, msg_c, size, NULL);

							memset(msg_c, '\0', 10);
							strncpy(msg_c, "02", 2);
							size = strlen(msg_c) + 1;
							send(Connection, msg_c, size, NULL);

							if (this->InvokeRequired) {
								this->Invoke(gcnew Action(this, &MyForm::PlayerDisconnected));
							}
							else {
								PlayerDisconnected();
							}

							break;

						case 13://код приглашени€ игрока
							strcpy(id, msg + 2);
							if (this->InvokeRequired) {
								this->Invoke(gcnew Action(this, &MyForm::Invitation));
							}
							else {
								Invitation();
							}
							break;

						case 23://код ответа на приглашение
							strcpy(id, msg + 2);
							break;

						case 33://код отказа на приглашение
							strcpy(id, msg + 2);
							if (this->InvokeRequired) {
								this->Invoke(gcnew Action(this, &MyForm::RefusedInvitation));
							}
							else {
								RefusedInvitation();
							}
							break;

						case 4://код подключени€ к игре
							iResult = send(Connection, msg, sizeof(msg), NULL);

							if (this->InvokeRequired) {
								this->Invoke(gcnew Action(this, &MyForm::GameStart));
							}
							else {
								GameStart();
							}
							break;

						case 14://код хода игрока none
							if (this->InvokeRequired) {
								this->Invoke(gcnew Action(this, &MyForm::YourMoveMSG));
							}
							else {
								YourMoveMSG();
							}
							break;

						case 24://код хода оппонента
							if (this->InvokeRequired) {
								this->Invoke(gcnew Action(this, &MyForm::OpponentMoveMSG));
							}
							else {
								OpponentMoveMSG();
							}
							break;


						case 44://код отображени€ хода оппонента
							key = msg[2];

							memset(msg_c, '\0', 10);
							strncpy(msg_c, "74", 2);
							_key = key;
							strcat(msg_c, _key.c_str());
							size = strlen(msg_c) + 1;
							send(Connection, msg_c, size, NULL);

							if (this->InvokeRequired) {
								this->Invoke(gcnew Action(this, &MyForm::OpponentMoveView));
							}
							else {
								OpponentMoveView();
							}

							break;

						case 54://код победы
							if (this->InvokeRequired) {
								this->Invoke(gcnew Action(this, &MyForm::VictoryMSG));
							}
							else {
								VictoryMSG();
							}
							break;

						case 64://код поражени€
							if (this->InvokeRequired) {
								this->Invoke(gcnew Action(this, &MyForm::DefeatMSG));
							}
							else {
								DefeatMSG();
							}

							break;

						case 94://код ничьей
							if (this->InvokeRequired) {
								this->Invoke(gcnew Action(this, &MyForm::DrawMSG));
							}
							else {
								DrawMSG();
							}

							break;



						case 6://противник уже сходил
							key = msg[2];

							memset(msg_c, '\0', 10);
							strncpy(msg_c, "74", 2);
							_key = key;
							strcat(msg_c, _key.c_str());
							size = strlen(msg_c) + 1;
							send(Connection, msg_c, size, NULL);

							break;


						case 7://отобразить ход противника
							key = msg[2];

							if (this->InvokeRequired) {
								this->Invoke(gcnew Action(this, &MyForm::OpponentMoveView));
							}
							else {
								OpponentMoveView();
							}
							break;

						default:
							break;
						}
					}
					if (this->InvokeRequired) {
						this->Invoke(gcnew Action(this, &MyForm::Disconnect));
					}
					else {
						Disconnect();
					}
				}
			}
			
		}
	protected:
		/// <summary>
		/// ќсвободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			delete ClientHandlerThread;
			if (components)
			{
				delete components;
			}
		}
private: System::Windows::Forms::Button^ RegistrationButton;
private: System::Windows::Forms::TextBox^ IPTextBox;

private: System::Windows::Forms::TextBox^ NameTextBox;

private: System::Windows::Forms::Label^ IPLabel;

private: System::Windows::Forms::Label^ NameLabel;

private: System::Windows::Forms::Button^ InviteButton;


	private: System::Windows::Forms::Label^ label3;
	public: System::Windows::Forms::ListBox^ listBox1;
private: System::Windows::Forms::Button^ NoButton;

private: System::Windows::Forms::Button^ YesButton;

	private: System::Windows::Forms::StatusStrip^ statusStrip1;
	private: System::Windows::Forms::ToolStripStatusLabel^ toolStripStatusLabel1;

private: System::Windows::Forms::Button^ BackButton;


	private:
		/// <summary>
		/// ќб€зательна€ переменна€ конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// “ребуемый метод дл€ поддержки конструктора Ч не измен€йте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->RegistrationButton = (gcnew System::Windows::Forms::Button());
			this->IPTextBox = (gcnew System::Windows::Forms::TextBox());
			this->NameTextBox = (gcnew System::Windows::Forms::TextBox());
			this->IPLabel = (gcnew System::Windows::Forms::Label());
			this->NameLabel = (gcnew System::Windows::Forms::Label());
			this->InviteButton = (gcnew System::Windows::Forms::Button());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->listBox1 = (gcnew System::Windows::Forms::ListBox());
			this->NoButton = (gcnew System::Windows::Forms::Button());
			this->YesButton = (gcnew System::Windows::Forms::Button());
			this->statusStrip1 = (gcnew System::Windows::Forms::StatusStrip());
			this->toolStripStatusLabel1 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->BackButton = (gcnew System::Windows::Forms::Button());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->statusStrip1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			this->SuspendLayout();
			// 
			// RegistrationButton
			// 
			this->RegistrationButton->BackColor = System::Drawing::Color::Transparent;
			this->RegistrationButton->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->RegistrationButton->FlatAppearance->MouseDownBackColor = System::Drawing::Color::LightSlateGray;
			this->RegistrationButton->FlatAppearance->MouseOverBackColor = System::Drawing::Color::LightSteelBlue;
			this->RegistrationButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->RegistrationButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 21.75F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->RegistrationButton->ForeColor = System::Drawing::Color::GhostWhite;
			this->RegistrationButton->Location = System::Drawing::Point(127, 305);
			this->RegistrationButton->Name = L"RegistrationButton";
			this->RegistrationButton->Size = System::Drawing::Size(203, 49);
			this->RegistrationButton->TabIndex = 9;
			this->RegistrationButton->Text = L"Registration";
			this->RegistrationButton->UseVisualStyleBackColor = false;
			this->RegistrationButton->Click += gcnew System::EventHandler(this, &MyForm::RegistrationButton_Click);
			// 
			// IPTextBox
			// 
			this->IPTextBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->IPTextBox->Location = System::Drawing::Point(104, 219);
			this->IPTextBox->Name = L"IPTextBox";
			this->IPTextBox->Size = System::Drawing::Size(262, 31);
			this->IPTextBox->TabIndex = 8;
			// 
			// NameTextBox
			// 
			this->NameTextBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->NameTextBox->Location = System::Drawing::Point(104, 123);
			this->NameTextBox->Name = L"NameTextBox";
			this->NameTextBox->Size = System::Drawing::Size(262, 31);
			this->NameTextBox->TabIndex = 7;
			this->NameTextBox->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MyForm::NameTextBox_KeyPress_1);
			// 
			// IPLabel
			// 
			this->IPLabel->AutoSize = true;
			this->IPLabel->BackColor = System::Drawing::Color::Transparent;
			this->IPLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->IPLabel->ForeColor = System::Drawing::SystemColors::ControlLightLight;
			this->IPLabel->Location = System::Drawing::Point(210, 178);
			this->IPLabel->Name = L"IPLabel";
			this->IPLabel->Size = System::Drawing::Size(40, 31);
			this->IPLabel->TabIndex = 6;
			this->IPLabel->Text = L"IP";
			// 
			// NameLabel
			// 
			this->NameLabel->AutoSize = true;
			this->NameLabel->BackColor = System::Drawing::Color::Transparent;
			this->NameLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->NameLabel->ForeColor = System::Drawing::SystemColors::ControlLightLight;
			this->NameLabel->Location = System::Drawing::Point(188, 74);
			this->NameLabel->Name = L"NameLabel";
			this->NameLabel->Size = System::Drawing::Size(86, 31);
			this->NameLabel->TabIndex = 5;
			this->NameLabel->Text = L"Name";
			// 
			// InviteButton
			// 
			this->InviteButton->BackColor = System::Drawing::Color::Transparent;
			this->InviteButton->FlatAppearance->MouseDownBackColor = System::Drawing::Color::LightSlateGray;
			this->InviteButton->FlatAppearance->MouseOverBackColor = System::Drawing::Color::LightSteelBlue;
			this->InviteButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->InviteButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->InviteButton->ForeColor = System::Drawing::Color::GhostWhite;
			this->InviteButton->Location = System::Drawing::Point(194, 382);
			this->InviteButton->Name = L"InviteButton";
			this->InviteButton->Size = System::Drawing::Size(92, 36);
			this->InviteButton->TabIndex = 13;
			this->InviteButton->Text = L"Invite";
			this->InviteButton->UseVisualStyleBackColor = false;
			this->InviteButton->Visible = false;
			this->InviteButton->Click += gcnew System::EventHandler(this, &MyForm::InviteButton_Click);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->BackColor = System::Drawing::Color::Transparent;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label3->ForeColor = System::Drawing::SystemColors::ControlLightLight;
			this->label3->Location = System::Drawing::Point(50, 232);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(86, 25);
			this->label3->TabIndex = 11;
			this->label3->Text = L"*empty*";
			this->label3->Visible = false;
			// 
			// listBox1
			// 
			this->listBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->listBox1->FormattingEnabled = true;
			this->listBox1->ItemHeight = 20;
			this->listBox1->Location = System::Drawing::Point(88, 12);
			this->listBox1->Name = L"listBox1";
			this->listBox1->Size = System::Drawing::Size(306, 364);
			this->listBox1->TabIndex = 10;
			this->listBox1->Visible = false;
			// 
			// NoButton
			// 
			this->NoButton->BackColor = System::Drawing::Color::Transparent;
			this->NoButton->FlatAppearance->MouseDownBackColor = System::Drawing::Color::LightSlateGray;
			this->NoButton->FlatAppearance->MouseOverBackColor = System::Drawing::Color::LightSteelBlue;
			this->NoButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->NoButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->NoButton->ForeColor = System::Drawing::Color::GhostWhite;
			this->NoButton->Location = System::Drawing::Point(338, 360);
			this->NoButton->Name = L"NoButton";
			this->NoButton->Size = System::Drawing::Size(100, 54);
			this->NoButton->TabIndex = 15;
			this->NoButton->Text = L"No";
			this->NoButton->UseVisualStyleBackColor = false;
			this->NoButton->Visible = false;
			this->NoButton->Click += gcnew System::EventHandler(this, &MyForm::NoButton_Click);
			// 
			// YesButton
			// 
			this->YesButton->BackColor = System::Drawing::Color::Transparent;
			this->YesButton->FlatAppearance->MouseDownBackColor = System::Drawing::Color::LightSlateGray;
			this->YesButton->FlatAppearance->MouseOverBackColor = System::Drawing::Color::LightSteelBlue;
			this->YesButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->YesButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->YesButton->ForeColor = System::Drawing::Color::GhostWhite;
			this->YesButton->Location = System::Drawing::Point(36, 360);
			this->YesButton->Name = L"YesButton";
			this->YesButton->Size = System::Drawing::Size(100, 54);
			this->YesButton->TabIndex = 14;
			this->YesButton->Text = L"Yes";
			this->YesButton->UseVisualStyleBackColor = false;
			this->YesButton->Visible = false;
			this->YesButton->Click += gcnew System::EventHandler(this, &MyForm::YesButton_Click);
			// 
			// statusStrip1
			// 
			this->statusStrip1->BackColor = System::Drawing::Color::Transparent;
			this->statusStrip1->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->statusStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->toolStripStatusLabel1 });
			this->statusStrip1->Location = System::Drawing::Point(0, 503);
			this->statusStrip1->Name = L"statusStrip1";
			this->statusStrip1->Size = System::Drawing::Size(484, 22);
			this->statusStrip1->SizingGrip = false;
			this->statusStrip1->TabIndex = 31;
			this->statusStrip1->Text = L"statusStrip1";
			// 
			// toolStripStatusLabel1
			// 
			this->toolStripStatusLabel1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 20.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->toolStripStatusLabel1->ForeColor = System::Drawing::SystemColors::ControlLightLight;
			this->toolStripStatusLabel1->Name = L"toolStripStatusLabel1";
			this->toolStripStatusLabel1->Size = System::Drawing::Size(0, 17);
			// 
			// BackButton
			// 
			this->BackButton->BackColor = System::Drawing::Color::Transparent;
			this->BackButton->FlatAppearance->MouseDownBackColor = System::Drawing::Color::LightSlateGray;
			this->BackButton->FlatAppearance->MouseOverBackColor = System::Drawing::Color::LightSteelBlue;
			this->BackButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->BackButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->BackButton->ForeColor = System::Drawing::Color::GhostWhite;
			this->BackButton->Location = System::Drawing::Point(172, 424);
			this->BackButton->Name = L"BackButton";
			this->BackButton->Size = System::Drawing::Size(130, 53);
			this->BackButton->TabIndex = 32;
			this->BackButton->Text = L"Back";
			this->BackButton->UseVisualStyleBackColor = false;
			this->BackButton->Visible = false;
			this->BackButton->Click += gcnew System::EventHandler(this, &MyForm::BackButton_Click);
			// 
			// button1
			// 
			this->button1->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button1.BackgroundImage")));
			this->button1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->button1->Location = System::Drawing::Point(36, 38);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(100, 100);
			this->button1->TabIndex = 33;
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Visible = false;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::cell1_Click);
			// 
			// button2
			// 
			this->button2->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button2.BackgroundImage")));
			this->button2->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->button2->Location = System::Drawing::Point(338, 38);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(100, 100);
			this->button2->TabIndex = 34;
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Visible = false;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::cell2_Click);
			// 
			// button3
			// 
			this->button3->BackColor = System::Drawing::SystemColors::ButtonHighlight;
			this->button3->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button3.BackgroundImage")));
			this->button3->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->button3->Location = System::Drawing::Point(186, 39);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(100, 100);
			this->button3->TabIndex = 35;
			this->button3->UseVisualStyleBackColor = false;
			this->button3->Visible = false;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::cell3_Click);
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(34, 203);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(160, 160);
			this->pictureBox1->TabIndex = 36;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->Visible = false;
			// 
			// pictureBox2
			// 
			this->pictureBox2->Location = System::Drawing::Point(265, 203);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(160, 160);
			this->pictureBox2->TabIndex = 37;
			this->pictureBox2->TabStop = false;
			this->pictureBox2->Visible = false;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::Color::Transparent;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->ForeColor = System::Drawing::SystemColors::ControlLightLight;
			this->label1->Location = System::Drawing::Point(85, 178);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(51, 25);
			this->label1->TabIndex = 38;
			this->label1->Text = L"You";
			this->label1->Visible = false;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->BackColor = System::Drawing::Color::Transparent;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label2->ForeColor = System::Drawing::SystemColors::ControlLightLight;
			this->label2->Location = System::Drawing::Point(331, 178);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(63, 25);
			this->label2->TabIndex = 39;
			this->label2->Text = L"Not u";
			this->label2->Visible = false;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(484, 525);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->pictureBox2);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->BackButton);
			this->Controls->Add(this->NoButton);
			this->Controls->Add(this->YesButton);
			this->Controls->Add(this->InviteButton);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->RegistrationButton);
			this->Controls->Add(this->IPTextBox);
			this->Controls->Add(this->NameTextBox);
			this->Controls->Add(this->IPLabel);
			this->Controls->Add(this->NameLabel);
			this->Controls->Add(this->statusStrip1);
			this->Controls->Add(this->listBox1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;
			this->Name = L"MyForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Rock-Paper-Scissors";
			this->statusStrip1->ResumeLayout(false);
			this->statusStrip1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		bool nick_ip(String^ nick, String^ ipS);
		Boolean b = true;

	private: System::Void YesButton_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void RegistrationButton_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void BackButton_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void cell1_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void cell2_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void cell3_Click(System::Object^ sender, System::EventArgs^ e);
	   public:System::Threading::Thread^ ClientHandlerThread;
private: System::Void InviteButton_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void NoButton_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void NameTextBox_KeyPress_1(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e);
};
}
