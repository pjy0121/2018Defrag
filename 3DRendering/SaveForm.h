#pragma once

#include <string>
#include <msclr\marshal_cppstd.h>

namespace My3DRendering {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;

	/// <summary>
	/// SaveForm에 대한 요약입니다.
	/// </summary>
	public ref class SaveForm : public System::Windows::Forms::Form
	{
	private: String^ curPath;
			 // convert String to unmanaged std::string
			 std::string StringToSTD(String^ value) {
				 msclr::interop::marshal_context context;
				 return context.marshal_as<std::string>(value);
			 }
			 String^ savePath;
			 String^ newFileMenuString;
	public:
		SaveForm(void)
		{
			InitializeComponent();
			//
			//TODO: 생성자 코드를 여기에 추가합니다.
			//
			curPath = ".\\files";
			newFileMenuString = gcnew String("Create New File.");
		}
		property std::string Response {
			std::string get() {
				return StringToSTD(savePath);
			}

			void set(std::string value) {
				savePath = gcnew String(value.c_str());
			}
		}
	protected:
		/// <summary>
		/// 사용 중인 모든 리소스를 정리합니다.
		/// </summary>
		~SaveForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::ListBox^  fileList;
	protected:

	protected:

	protected:

	private:
		/// <summary>
		/// 필수 디자이너 변수입니다.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 디자이너 지원에 필요한 메서드입니다. 
		/// 이 메서드의 내용을 코드 편집기로 수정하지 마세요.
		/// </summary>
		void InitializeComponent(void)
		{
			this->fileList = (gcnew System::Windows::Forms::ListBox());
			this->SuspendLayout();
			// 
			// fileList
			// 
			this->fileList->FormattingEnabled = true;
			this->fileList->ItemHeight = 12;
			this->fileList->Location = System::Drawing::Point(13, 13);
			this->fileList->Name = L"fileList";
			this->fileList->Size = System::Drawing::Size(259, 232);
			this->fileList->TabIndex = 0;
			this->fileList->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &SaveForm::fileList_KeyDown);
			// 
			// SaveForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(7, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 261);
			this->Controls->Add(this->fileList);
			this->Name = L"SaveForm";
			this->Text = L"SaveForm";
			this->Load += gcnew System::EventHandler(this, &SaveForm::SaveForm_Load);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void SaveForm_Load(System::Object^  sender, System::EventArgs^  e) {
		fileList->Items->Clear();

		// if Directory is not existed, create new one
		if (!Directory::Exists(".\\files")) {
			Directory::CreateDirectory(".\\files");
		}

		// retrieve file list from directory
		this->Text = DirectoryInfo(curPath).Name;
		array<String^>^ files = Directory::GetFiles(".\\files");
		array<String^>^ directories = Directory::GetDirectories(curPath);

		fileList->Items->Add("Cancel");
		fileList->Items->Add("..");

		for (int i = 0; i < directories->Length; i++) {
			String^ temp = DirectoryInfo(directories[i]).Name;
			fileList->Items->Add("(dir) " + temp);
		}

		for (int i = 0; i < files->Length; i++) {
			String^ temp = FileInfo(files[i]).Name;
			if (temp->Contains(".txt"))
				fileList->Items->Add("(file) " + temp);
		}
		fileList->Items->Add(newFileMenuString);
	}

	private: System::Void fileList_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
		if (e->KeyCode == Keys::Enter) {
			String^ selectedItem = fileList->SelectedItem->ToString();
			String^ file = curPath + "\\" + fileList->SelectedItem->ToString();

			// cancel
			if (selectedItem->Equals("Cancel")) {
				Response = this->StringToSTD("Cancel");
				this->Close();
			}
			// create new file
			else if (selectedItem->Equals(newFileMenuString)) {
				file = curPath + "\\" + DateTime::Today.ToShortDateString() + "-" + DateTime::Now.Hour + DateTime::Now.Minute + DateTime::Now.Second +".txt";
			}

			// previous directory
			if (selectedItem->Equals("..")) {
				curPath = Directory::GetParent(curPath)->FullName;
				this->Text = DirectoryInfo(curPath).Name;

				array<String^>^ directories = Directory::GetDirectories(curPath);
				array<String^>^ files = Directory::GetFiles(curPath);
				fileList->Items->Clear();

				fileList->Items->Add("Cancel");
				fileList->Items->Add("..");

				for (int i = 0; i < directories->Length; i++) {
					String^ temp = DirectoryInfo(directories[i]).Name;
					fileList->Items->Add("(dir) " + temp);
				}

				for (int i = 0; i < files->Length; i++) {
					String^ temp = FileInfo(files[i]).Name;
					if (temp->Contains(".txt"))
						fileList->Items->Add("(file) " + temp);
				}
				fileList->Items->Add(newFileMenuString);
				return;
			}
			// select directory
			if (selectedItem->Contains("(dir)")) {
				curPath = curPath + "\\" + selectedItem->Replace("(dir) ", "");
				this->Text = DirectoryInfo(curPath).Name;

				array<String^>^ directories = Directory::GetDirectories(curPath);
				array<String^>^ files = Directory::GetFiles(curPath);
				fileList->Items->Clear();

				fileList->Items->Add("Cancel");
				fileList->Items->Add("..");

				for (int i = 0; i < directories->Length; i++) {
					String^ temp = DirectoryInfo(directories[i]).Name;
					fileList->Items->Add("(dir) " + temp);
				}

				for (int i = 0; i < files->Length; i++) {
					String^ temp = FileInfo(files[i]).Name;
					if (temp->Contains(".txt"))
						fileList->Items->Add("(file) " + temp);
				}
				fileList->Items->Add(newFileMenuString);
				return;
			}
			// select file
			if (selectedItem->Contains("(file)"))
				file = file->Replace("(file) ", "");

			Response = this->StringToSTD(file);
			this->Close();
		}
	}
	};
}
