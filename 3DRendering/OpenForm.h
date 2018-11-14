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
	/// OpenForm�� ���� ����Դϴ�.
	/// </summary>
	public ref class OpenForm : public System::Windows::Forms::Form
	{
	private: String^ curPath;
			 // convert String to unmanaged std::string
			 std::string StringToSTD(String^ value) {
				 msclr::interop::marshal_context context;
				 return context.marshal_as<std::string>(value);
			 }
			 String^ openPath;
	public:
		OpenForm(void)
		{
			InitializeComponent();
			//
			//TODO: ������ �ڵ带 ���⿡ �߰��մϴ�.
			//
			curPath = gcnew String(".\\files");
			openPath = gcnew String(".\\files\\output.txt");
		}
		property std::string Response {
			std::string get() {
				return StringToSTD(openPath);
			}

			void set(std::string value) {
				openPath = gcnew String(value.c_str());
			}
		}
	protected:
		/// <summary>
		/// ��� ���� ��� ���ҽ��� �����մϴ�.
		/// </summary>
		~OpenForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::ListBox^  fileList;
	protected:

	private:
		/// <summary>
		/// �ʼ� �����̳� �����Դϴ�.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// �����̳� ������ �ʿ��� �޼����Դϴ�. 
		/// �� �޼����� ������ �ڵ� ������� �������� ������.
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
			this->fileList->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &OpenForm::fileList_KeyDown);
			// 
			// OpenForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(7, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 261);
			this->Controls->Add(this->fileList);
			this->Name = L"OpenForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Open File";
			this->Load += gcnew System::EventHandler(this, &OpenForm::OpenForm_Load);
			this->ResumeLayout(false);
		}

		#pragma endregion
		private: System::Void fileList_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
			if (e->KeyCode == Keys::Enter) {
				String^ file = fileList->SelectedItem->ToString();

				if (file->Equals("Cancel")) {
					Response = this->StringToSTD("Cancel");
					this->Close();
				}

				Response = this->StringToSTD(file);
				this->Close();
			}
		}

		private: System::Void OpenForm_Load(System::Object^  sender, System::EventArgs^  e) {
			fileList->Items->Clear();

			// if Directory is not existed, create new one
			if (!Directory::Exists(".\\files")) {
				Directory::CreateDirectory(".\\files");
			}

			// retrieve file list from directory
			array<String^>^ files = Directory::GetFiles(".\\files");

			fileList->Items->Add("Cancel");

			for (int i = 0; i < files->Length; i++) {
				fileList->Items->Add(files[i]);
			}
		}
	};
}
