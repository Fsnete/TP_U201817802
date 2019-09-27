#pragma once
#include "MyForm.h"
namespace TrabajoParcial {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Resumen de Menú
	/// </summary>
	public ref class Menú : public System::Windows::Forms::Form
	{
	public:
		Bitmap^bmp;
		Menú(void)
		{
			InitializeComponent();
		/*	bmp = gcnew Bitmap("fondo//space.png");

			Graphics^g = this->CreateGraphics();
			Rectangle pantalla = Rectangle(0, 0, g->VisibleClipBounds.Width, g->VisibleClipBounds.Height);
			g->DrawImage(bmp, pantalla);*/

			//
			//TODO: agregar código de constructor aquí
			//
		}

	protected:
		/// <summary>
		/// Limpiar los recursos que se estén usando.
		/// </summary>
		~Menú()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	protected:
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  button2;

	protected:

	protected:

	protected:

	private:
		/// <summary>
		/// Variable del diseñador necesaria.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Método necesario para admitir el Diseñador. No se puede modificar
		/// el contenido de este método con el editor de código.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Menú::typeid));
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(0, 1);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(538, 321);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(216, 259);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(117, 23);
			this->button1->TabIndex = 1;
			this->button1->Text = L"Jugar";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Menú::button1_Click_1);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(216, 288);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(117, 23);
			this->button2->TabIndex = 2;
			this->button2->Text = L"Cargar partida";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Menú::button2_Click);
			// 
			// Menú
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(539, 322);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->pictureBox1);
			this->Name = L"Menú";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Menú";
			this->Load += gcnew System::EventHandler(this, &Menú::Menú_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void label1_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void pictureBox1_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void Menú_Load(System::Object^  sender, System::EventArgs^  e) {
		
	}
	private: System::Void button1_Click_1(System::Object^  sender, System::EventArgs^  e) {
		MyForm^juego=gcnew MyForm(false);
		juego->Show();

	}
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {

	MyForm^juego = gcnew MyForm(true);
	juego->Show();
}
};
}
