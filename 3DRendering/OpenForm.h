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

	public ref class OpenForm : public System::Windows::Forms::Form
	{

	private: String ^curPath, ^openPath;
			 // convert String to unmanaged std::string
			 std::string StringToSTD(String^ value) {
				 msclr::interop::marshal_context context;
				 return context.marshal_as<std::string>(value);
			 }
			 void updateList() {
				 fileList->Items->Clear();

				 this->Text = DirectoryInfo(curPath).Name;
				 array<FileInfo^>^ files = DirectoryInfo(curPath).GetFiles();
				 array<DirectoryInfo^>^ directories = DirectoryInfo(curPath).GetDirectories();

				 fileList->Items->Add("Cancel");
				 fileList->Items->Add("..");

				 for (int i = 0; i < directories->Length; i++) {
					 ListViewItem^ item = gcnew ListViewItem(directories[i]->Name);
					 item->ImageIndex = 0;

					 fileList->Items->Add(item);
				 }

				 for (int i = 0; i < files->Length; i++) {
					 ListViewItem^ item = gcnew ListViewItem(files[i]->Name);
					 item->ImageIndex = 1;

					 fileList->Items->Add(item);
				 }
			 }
	public: System::Windows::Forms::ImageList^  iconList;
	private:

			 System::Windows::Forms::ListView^  fileList;
			 System::ComponentModel::IContainer^  components;
	public:
		OpenForm(void)
		{
			InitializeComponent();
			//
			//TODO: 생성자 코드를 여기에 추가합니다.
			//
			curPath = gcnew String(".\\files");
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
		~OpenForm()
		{
			if (components)
			{
				delete components;
			}
		}


#pragma region Windows Form Designer generated code
		/// <summary>
		/// 디자이너 지원에 필요한 메서드입니다. 
		/// 이 메서드의 내용을 코드 편집기로 수정하지 마세요.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(OpenForm::typeid));
			this->iconList = (gcnew System::Windows::Forms::ImageList(this->components));
			this->fileList = (gcnew System::Windows::Forms::ListView());
			this->SuspendLayout();
			// 
			// iconList
			// 
			this->iconList->ImageStream = (cli::safe_cast<System::Windows::Forms::ImageListStreamer^>(resources->GetObject(L"iconList.ImageStream")));
			this->iconList->TransparentColor = System::Drawing::Color::Transparent;
			this->iconList->Images->SetKeyName(0, L"folderIcon");
			this->iconList->Images->SetKeyName(1, L"txtIcon");
			// 
			// fileList
			// 
			this->fileList->BackColor = System::Drawing::SystemColors::Window;
			this->fileList->Dock = System::Windows::Forms::DockStyle::Fill;
			this->fileList->Font = (gcnew System::Drawing::Font(L"DotumChe", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->fileList->ForeColor = System::Drawing::SystemColors::WindowText;
			this->fileList->HeaderStyle = System::Windows::Forms::ColumnHeaderStyle::None;
			this->fileList->Location = System::Drawing::Point(0, 0);
			this->fileList->MultiSelect = false;
			this->fileList->Name = L"fileList";
			this->fileList->ShowGroups = false;
			this->fileList->Size = System::Drawing::Size(578, 384);
			this->fileList->SmallImageList = this->iconList;
			this->fileList->TabIndex = 1;
			this->fileList->UseCompatibleStateImageBehavior = false;
			this->fileList->View = System::Windows::Forms::View::Details;
			this->fileList->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &OpenForm::fileList_KeyDown);
			// 
			// OpenForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(10, 18);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(578, 384);
			this->Controls->Add(this->fileList);
			this->Margin = System::Windows::Forms::Padding(4);
			this->Name = L"OpenForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = L"Open File";
			this->Load += gcnew System::EventHandler(this, &OpenForm::OpenForm_Load);
			this->ResumeLayout(false);

		}

		#pragma endregion

		private: System::Void fileList_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
			if (e->KeyCode == Keys::Enter) {
				ListViewItem^ selectedItem = fileList->SelectedItems[0];

				// cancel
				if (selectedItem->Text == "Cancel") {
					Response = this->StringToSTD("Cancel");
					this->Close();
				}
				// previous directory
				if (selectedItem->Text == "..") {
					curPath = Directory::GetParent(curPath)->FullName;

					updateList();

					return;
				}
				// select directory
				if (selectedItem->ImageIndex == 0) {
					curPath = curPath + "\\" + selectedItem->Text;

					updateList();

					return;
				}
				// select file
				if (selectedItem->ImageIndex == 1)
					Response = this->StringToSTD(curPath + "\\" + selectedItem->Text);

				this->Close();
			}
		}

		private: System::Void OpenForm_Load(System::Object^  sender, System::EventArgs^  e) {
			// if Directory is not existed, create new one
			if (!Directory::Exists(".\\files"))
				Directory::CreateDirectory(".\\files");

			this->updateList();

			fileList->Columns->Add("파일명", 500, HorizontalAlignment::Left);
			fileList->EndUpdate();
		}
	};
}
