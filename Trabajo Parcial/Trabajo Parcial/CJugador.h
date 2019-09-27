#pragma once
#include "CNave.h"
#include "CBala.h"


 
class CJugador: public CNave {
private:
	short maxHP;
	short dmgBullets;
	bool DobleTiro;
	bool Booster;
	int direccion;
	Lista<CBala*>balas;
public:
	void guardar_jugador(ofstream & out)
	{
		out.write((char*)&maxHP, sizeof(short));
		out.write((char*)&dmgBullets, sizeof(short));
		out.write((char*)&DobleTiro, sizeof(bool));
		out.write((char*)&Booster, sizeof(bool));
		out.write((char*)&direccion, sizeof(int));
		for (int i = 0; i < balas.longitud(); i++)
		{
			balas.obtenerPos(i)->guardar(out);
		}
	}

	void cargar_jugador(ifstream & in) {
		in.read((char*)&maxHP, sizeof(short));
		in.read((char*)&dmgBullets, sizeof(short));
		in.read((char*)&DobleTiro, sizeof(bool));
		in.read((char*)&Booster, sizeof(bool));
		in.read((char*)&direccion, sizeof(int));
		for (int i = 0; i < balas.longitud(); i++)
			balas.obtenerPos(i)->cargar(in);
	}
	CJugador(int x, int y, int vidas):CNave(x,y,vidas)
		
	{
		Bitmap^bmp = gcnew Bitmap("sprites//jugador3.png");
		ancho = bmp->Width;
		alto = bmp->Height;
		this->maxHP = 0;
		this->dmgBullets = 0;
		this->DobleTiro = false;
		this->Booster = false;
		delete bmp;
 
	}
	void Dibujar(Graphics^g, Bitmap^ bmp)
	{
                                                                                       
		/*bmp->MakeTransparent(bmp->GetPixel(1, 1));*/
		Rectangle porcion = Rectangle(0, 0, bmp->Width, bmp->Height);
		g->DrawImage(bmp, x, y, porcion, GraphicsUnit::Pixel);
		Font^ f = gcnew Font("Arial", 10);

		g->DrawString("" + vidas, f, Brushes::Red, Rectangle(x, y, 25, 25));
		for (int i = balas.longitud() - 1; i >= 0; --i)
		{
			balas.obtenerPos(i)->Dibujar(g);

		}
 
	}

	void Mover(Graphics^g, Bitmap^ bmp)
	{
		for (int i = balas.longitud() - 1; i >= 0; --i)
		{
			balas.obtenerPos(i)->Mover(g);
			if (balas.obtenerPos(i)->getY() + balas.obtenerPos(i)->getDY()
				+ balas.obtenerPos(i)->getAlto() < 0)
			{
				balas.eliminaPos(i);
			}
		}
		switch (direccion)
		{
			//NINGUNA
		case 0:
			dx = 0;
			dy = 0;
			break;
			//ARRIBA
		case 1:
			dx = 0;
			dy = -20;
			break;
			//ABAJO
		case 2:
			dx = 0;
			dy = 20;
			break;
			//IZQUIERDA
		case 3:
			dx = -20;
			dy = 0;
			break;
			//DERECHA
		case 4:
			dx = 20;
			dy = 0;
			break;
		}

		if (x + dx + bmp->Width > g->VisibleClipBounds.Width || x + dx < 0)
			dx = 0;
		if (y + dy + bmp->Height > g->VisibleClipBounds.Height || y + dy < g->VisibleClipBounds.Height-bmp->Width-50)
			dy = 0;


		x += dx;
		y += dy;

	}

	void setDireccion(int direccion)
	{
		this->direccion = direccion;
	}

	void Disparar(Graphics^g)
	{
		balas.agregaFinal(new CBala(x+ancho/2-10,y+alto/70,-20));

	}

	bool colision_balas(CNave* nave)
	{
		for (int i = balas.longitud() - 1; i >= 0; i--)
		{
			if (balas.obtenerPos(i)->colision(nave))
			{
				balas.eliminaPos(i);
				return true;
			}
		}
		return false;
	}

};