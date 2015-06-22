// ejemplo.cc

// Compilo usando:
//
//  g++ -std=c++11 -o ejemplo ejemplo.cc graph_parser.cc -ljsoncpp 
//


#include <iostream>
#include "graph_parser.h"

int main() {

	// --------------------------------- Ejemplo sencillo
	Graph G;                          // Crea un grafo G.
	G.read_matrix_file("matriz.dat"); // Lee el grafo del archivo "matriz.dat".
	G.changeSizesByGrade();           // Cambia el tama~no de los nodos seg'un su grado,
	cout << G.sigmajs_json() << endl; // Salida por pantalla en formato json para sigmajs.

	return 0; }
