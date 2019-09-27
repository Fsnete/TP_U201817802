#pragma once
#include "CLista.h"
using namespace System::Drawing;
using namespace std;


class CNave
{
protected:
	int x, y, dx, dy, vidas;
	int ancho, alto;
 
public:
	//PARA EL JUGADOR
	CNave(int x, int y,int vidas)
	{
		this->x = x;
		this->y = y;
		dx = 0;
		dy = 0;
		this->vidas = vidas;
		ancho = 0;
		alto = 0;
 
	}
	//PARA EL ENEMIGO
	CNave(int x, int y, int dx, int vidas)
	{
		Bitmap^bmp2 = gcnew Bitmap("sprites//enemigo.png");
		this->x = x;
		this->y = y;
		this->dx = dx;
		this->vidas = vidas;
		ancho = bmp2->Width;
		alto = bmp2->Height;
		delete bmp2;
 
	}

	virtual void Dibujar(Graphics^g, Bitmap^bmp) = 0;
	virtual void Mover(Graphics^g, Bitmap^ bmp) = 0;
	virtual void Disparar(Graphics^g) = 0;
	Rectangle getRectangle()
	{
		return Rectangle(x, y, ancho, alto);
	}
	bool estaMuerto()
	{
		if (vidas == 0)
			return true;
		else
			return false;
	}

	int getX()
	{
		return this->x;
	}

	int getY()
	{
		return this->y;
	}
	int getAncho()
	{
		return this->ancho;
	}
	int getAlto()
	{
		return this->alto;
	}


	int disminuirVidas()
	{
		return vidas--;
	}

	 
	
	int getVidas()
	{
		return this->vidas=vidas;
	}
};