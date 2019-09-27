#pragma once
#include "CJugador.h"
#include "CLista.h"
#include "CEnemigo.h"
#include <fstream>
#include <ctime>
#include <conio.h>
#include <stdlib.h> 
 
using namespace System;

class CJuego
{
private:
	Lista <CEnemigo*>enemigos;
	CJugador*jugador;
 
	int niveles;
	clock_t temp;
	clock_t temp2;
	clock_t temp3;
	int nro_de_enemigos;
	bool finalizar;
public:
	void guardarPartida() {
		espacio1::_guardarDatos([this](ofstream & out) -> bool
		{
			jugador->guardar_jugador(out);
			out.write((char*)&niveles, sizeof(int));
			out.write((char*)&nro_de_enemigos, sizeof(int));
			out.write((char*)&finalizar, sizeof(bool));
			out.write((char*)&temp, sizeof(clock_t));
			out.write((char*)&temp2, sizeof(clock_t));
			out.write((char*)&temp3, sizeof(clock_t));
			for (int i = 0; i < enemigos.longitud(); i++)
				enemigos.obtenerPos(i)->guardar_enemigos(out);
			return true;
		});
	}

	void cargarPartida() {
		espacio1::_cargarDatos([this](ifstream & in) -> bool
		{

			jugador->cargar_jugador(in);
			in.read((char*)&niveles, sizeof(int));
			in.read((char*)&nro_de_enemigos, sizeof(int));
			in.read((char*)&finalizar, sizeof(bool));
			in.read((char*)&temp, sizeof(clock_t));
			in.read((char*)&temp2, sizeof(clock_t));
			in.read((char*)&temp3, sizeof(clock_t));
			for (int i = 0; i < enemigos.longitud(); i++)
				enemigos.obtenerPos(i)->cargar_enemigos(in);
			return true;
		}
		);
	}

	CJuego(Graphics^g)
	{
		niveles = 1;
		temp = clock();
		temp2 = clock();
		temp3 = clock();
		jugador = new CJugador((g->VisibleClipBounds.Width / 2), (g->VisibleClipBounds.Height) - 80, 100);
		for (int i = 0; i < 6; i++)
			enemigos.agregaInicial(new CEnemigo(45*i*3, 30, 20, 2));
		nro_de_enemigos = enemigos.longitud();
		finalizar = false;
	}
	~CJuego(){}

	CJugador* getJugador()
	{
		return jugador;
	}



	//}
	void DibujaNivel(Graphics^g,Bitmap^nivel1,Bitmap^nivel2, Bitmap^nivel3, Bitmap^nivel4)
	{
		Rectangle pantalla = Rectangle(0, 0, (int)g->VisibleClipBounds.Width, (int)g->VisibleClipBounds.Height);
		agregarEnemigos(g);
			switch (niveles)
			{
			case 1:
				g->DrawImage(nivel1, pantalla);
				break;
			case 2:
				g->DrawImage(nivel2, pantalla);
				break;
			case 3:
				g->DrawImage(nivel3, pantalla);
				break;
			case 4:
				g->DrawImage(nivel4, pantalla);
				break;
			}
			if (cambiar_de_Nivel())
			{
				for (int i = enemigos.longitud() - 1; i >= 0; i--)
					enemigos.eliminaPos(i);

				switch (niveles)
				{
				case 1:
					for (int i = 0; i < 6; i++)
						enemigos.agregaInicial(new CEnemigo(45 * i * 3, 70, 20, 2));
					nro_de_enemigos = enemigos.longitud();
					temp3 = clock();
					break;
				case 2:
					for (int i = 0; i < 6; i++)
						enemigos.agregaInicial(new CEnemigo(45 * i * 3, 70, 20, 2));
					nro_de_enemigos = enemigos.longitud();
					temp3 = clock();
					break;
				case 3:
					for (int i = 0; i < 6; i++)
						enemigos.agregaInicial(new CEnemigo(45 * i * 3, 70, 20, 2));
					nro_de_enemigos = enemigos.longitud();
					temp3 = clock();
					break;
				case 4:
					for (int i = 0; i < 6; i++)
						enemigos.agregaInicial(new CEnemigo(45 * i * 3, 70, 20, 2));
					nro_de_enemigos = enemigos.longitud();
					temp3 = clock();
					break;
				}
			}
		 
	}
	void DibujarTodos(Graphics^g,Bitmap^j,Bitmap^nmy)
	{
		jugador->Dibujar(g, j);
		for (int i = 0; i < enemigos.longitud(); i++)
		{
			enemigos.obtenerPos(i)->Dibujar(g, nmy);
		}
	
	}

	void MoverTodos(Graphics^g, Bitmap^j, Bitmap^nmy)
	{
		clock_t start = clock();
		double duration = (double)(start - temp) / CLOCKS_PER_SEC;
		jugador->Mover(g, j);
		if (duration >= 1)
		{
			for (int i = 0; i < enemigos.longitud(); i++)
			{
				enemigos.obtenerPos(i)->Mover(g, nmy);
			}
			temp = clock();
		}
		for (int i = 0; i < enemigos.longitud(); i++)
			enemigos.obtenerPos(i)->moverBalas(g);
		 
	}
	void agregarEnemigos(Graphics^g)
	{
		Random x;
		clock_t start = clock();
		double duration = (double)(start - temp3) / CLOCKS_PER_SEC;
		if (duration > 3)
		{
			for (int i = 0; i < 3; i++)
			{
				enemigos.agregaFinal(new CEnemigo(rand()%int(g->VisibleClipBounds.Width), rand() % int(g->VisibleClipBounds.Height/3), 20, 2));
			}
			nro_de_enemigos = nro_de_enemigos + 3;
			temp3 = clock();
		}
	}
	bool cambiar_de_Nivel()
	{
		clock_t start = clock();
		double duration = (double)(start - temp2) / CLOCKS_PER_SEC;
		if(jugador->getVidas()==0)
			finalizar = true;
		if (duration > 10 || nro_de_enemigos / 2 > enemigos.longitud())
		{
			niveles++;
			temp2 = clock();
			if (niveles > 4)
				finalizar = true;
			return true;
		}
		else
			return false;

	
	}

	bool getFinalizar()
	{
		return finalizar;
	}
	

	void colisionBalas_Jugador_Enemigos()
	{
		for (int i = enemigos.longitud() - 1; i >= 0; i--)
		{
			if (jugador->colision_balas(enemigos.obtenerPos(i)))
				enemigos.obtenerPos(i)->disminuirVidas();
			 
		}
	}

	void colisionBalas_Enemigos_Jugador()
	{
		for (int i = 0; i < enemigos.longitud(); i++)
		{
			if (enemigos.obtenerPos(i)->colision_balas(jugador))
				jugador->disminuirVidas();
			if (enemigos.obtenerPos(i)->getVidas() == 0)
				enemigos.eliminaPos(i);
		 
		}
	}
};