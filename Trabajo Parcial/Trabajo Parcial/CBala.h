#pragma once
#include "CNave.h"
#include "Archivos.h"
using namespace System::Drawing;
using namespace std;

class CBala {

private:

	int x, y, dy;
	int ancho, alto;
 
public:

	CBala(int x, int y,int dy)
	{
		this->x = x;
		this->y = y;
		this->dy = dy;
		ancho = 20;
		alto = 20;
		
	}
	void guardar(ofstream& out)
	{
		out.write((char*)&x, sizeof(int));
		out.write((char*)&y, sizeof(int));
		out.write((char*)&dy, sizeof(int));
		out.write((char*)&ancho,sizeof(int));
		out.write((char*)&alto, sizeof(int));
	}

	void cargar(ifstream& in)
	{
		in.read((char*)&x,sizeof(int));
		in.read((char*)&y,sizeof(int));
		in.read((char*)&dy,sizeof(int));
		in.read((char*)&ancho,sizeof(int));
		in.read((char*)&alto, sizeof(int));
	}

	void Dibujar(Graphics^g)
	{
		Rectangle visible = Rectangle(x,y,ancho, alto);
		g->FillEllipse(Brushes::Aqua, visible);
	}

	void Mover(Graphics^g)
	{
		y += dy;
	}


	int getY()
	{
		return y;
	}

	int getAlto()
	{
		return alto;
	}
	int getDY()
	{
		return dy;
	}

	Rectangle getRectangle()
	{
		return Rectangle(x, y, ancho, alto);
	}
	bool colision(CNave* nave)
	{
		if (this->getRectangle().IntersectsWith(nave->getRectangle()))
		{
			return true;
		}
		return false;
	}
};