#pragma once
#include "CJuego.h"


namespace TrabajoParcial {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Resumen de MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		CJuego*juego;
		Bitmap^bmp;		
		Bitmap^bmp2;
		Bitmap^nivel1;
		Bitmap^nivel2;
		Bitmap^nivel3;
	public:
		Bitmap^nivel4;

	public:
 
		MyForm(bool cargado)
		{
			InitializeComponent();
			Graphics^g = this->CreateGraphics();
			bmp = gcnew Bitmap("sprites//jugador3.png");
			bmp2 = gcnew Bitmap("sprites//enemigo.png");
			nivel1 = gcnew Bitmap("fondo//nivel1.jpg");
			nivel2 = gcnew Bitmap("fondo//nivel2.jpg");
			nivel3 = gcnew Bitmap("fondo//nivel3.png");
			nivel4 = gcnew Bitmap("fondo//nivel4.jpg");
			juego = new CJuego(g);
			if (cargado)
				juego->cargarPartida();
			//V
			//TODO: agregar código de constructor aquí
			//
		}

	protected:
		/// <summary>
		/// Limpiar los recursos que se estén usando.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Timer^  timer1;
	protected:
	private: System::ComponentModel::IContainer^  components;

	private:
		/// <summary>
		/// Variable del diseñador necesaria.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Método necesario para admitir el Diseñador. No se puede modificar
		/// el contenido de este método con el editor de código.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Tick += gcnew System::EventHandler(this, &MyForm::timer1_Tick);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(752, 590);
			this->Name = L"MyForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"MyForm";
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::MyForm_KeyDown);
			this->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::MyForm_KeyUp);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
		Graphics^g = this->CreateGraphics();
		BufferedGraphicsContext^espacio = BufferedGraphicsManager::Current;
		BufferedGraphics^buffer = espacio->Allocate(g, this->ClientRectangle);
		juego->DibujaNivel(buffer->Graphics,nivel1,nivel2,nivel3,nivel4);
		juego->DibujarTodos(buffer->Graphics, bmp, bmp2);
		juego->MoverTodos(g,bmp, bmp2);
		juego->colisionBalas_Enemigos_Jugador();
		juego->colisionBalas_Jugador_Enemigos();

		buffer->Render(g);
		if (juego->getFinalizar() == true)
		{
			this->Close();
		}

		delete buffer;
		delete espacio;
		delete g;
	}
	private: System::Void MyForm_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
		Graphics^g = this->CreateGraphics();
		if (e->KeyCode == Keys::Up)
			juego->getJugador()->setDireccion(1);
		if (e->KeyCode == Keys::Down)
			juego->getJugador()->setDireccion(2);
		if (e->KeyCode == Keys::Left)
			juego->getJugador()->setDireccion(3);
		if (e->KeyCode == Keys::Right)
			juego->getJugador()->setDireccion(4);
		if (e->KeyCode == Keys::Space)
			juego->getJugador()->Disparar(g);
		if (e->KeyCode == Keys::G)
			juego->guardarPartida();
	
		if (e->KeyCode == Keys::P)
		{
			if (timer1->Enabled == false)
				timer1->Enabled = true;
			else
			timer1->Enabled = false;
			 
		}
	}
	private: System::Void MyForm_KeyUp(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
		juego->getJugador()->setDireccion(0);
	}

private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
	//juego->guardarPartida();
}
};
}
