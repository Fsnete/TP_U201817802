#pragma once
#include <fstream>
#include <functional>
using namespace std;

namespace espacio1
{
	inline bool _guardarDatos(std::function<bool(std::ofstream &)>funcion)
	{
		ofstream guardar("partida1.txt");
		funcion(guardar);
		guardar.close();
		return true;
	}

	static bool _cargarDatos(std::function<bool(std::ifstream &)>funcion)
	{
		ifstream cargar("partida1.txt");
		funcion(cargar);
		cargar.close();
		return true;
	}
}