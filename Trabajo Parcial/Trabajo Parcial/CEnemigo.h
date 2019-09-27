#pragma once
#include "CNave.h"
#include "CBala.h"
#include <ctime>
#include <iostream>
class CEnemigo : public CNave {

private:
	clock_t temp;
	Lista<CBala*>balas;

public:
	void guardar_enemigos(ofstream & out)
	{
		out.write((char*)&temp, sizeof(clock_t));
		for (int i = 0; i < balas.longitud(); i++)
		{
			balas.obtenerPos(i)->guardar(out);
		}
	}
	void cargar_enemigos(ifstream&in)
	{
		in.read((char*)&temp, sizeof(clock_t));
		for (int i = 0; i < balas.longitud(); i++)
		{
			balas.obtenerPos(i)->cargar(in);
		}
	}
	CEnemigo(int x, int y, int dx, int vidas) :CNave(x, y, dx, vidas)
	{
		Bitmap^bmp2 = gcnew Bitmap("sprites//enemigo.png");
		temp = clock();
		ancho = bmp2->Width;
		alto = bmp2->Height;
		delete bmp2;
	
	}

	void Dibujar(Graphics^ g, Bitmap^ bmp)
	{
	
	/*	bmp->MakeTransparent(bmp->GetPixel(1, 1));*/
		Rectangle porcion = Rectangle(0, 0, bmp->Width, bmp->Height);
		g->DrawImage(bmp, x, y, porcion, GraphicsUnit::Pixel);
		for (int i = 0; i < balas.longitud(); i++)
			balas.obtenerPos(i)->Dibujar(g);
	}

	void Mover(Graphics^ g, Bitmap^ bmp) {
		clock_t start = clock();
		x += dx;
		double duration = (double)(start - temp) / CLOCKS_PER_SEC;
		if (duration >= 3)
		{
			Disparar(g);
			temp = clock();
		}

		dx *= -1;
	}
	void moverBalas(Graphics^g)
	{
		for (int i = balas.longitud() - 1; i >= 0; --i)
		{
			balas.obtenerPos(i)->Mover(g);
			if (balas.obtenerPos(i)->getY() + balas.obtenerPos(i)->getDY() + balas.obtenerPos(i)->getAlto() > g->VisibleClipBounds.Height)
				balas.eliminaPos(i);

		}
	}
	void Disparar(Graphics^g) {
			balas.agregaFinal(new CBala(x + ancho / 2, y + alto / 2, 20));
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