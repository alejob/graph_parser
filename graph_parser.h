// graph_parser.h

#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <vector>
#include <jsoncpp/json/json.h>

#define PI 3.1415926535

using namespace std;

class Graph {

	struct node {
		string id;
		string label;
		float x;
		float y;
		float size; };

	struct edge {
		string id;
		string source;
		string target; };

	private:
		vector< vector<bool> > M; // Matriz de adyacencia.
		unsigned int dim;         // Dimensi'on de M.

		vector<node> nodes; // Nodos para sigmajs.
		vector<edge> edges; // V'ertices para sigmajs.

	public:
		// ---------------------- Constructores et al.
		Graph();               // 
		//Graph(const Graph&); //
		//Graph(Graph&&);      //
		~Graph();              //

		// ----------------------------------------- Métodos para lectura-escritura.
		void read_matrix(string);                 // Lee una matriz desde un string.
		void read_matrix(ifstream&);              // Lee una matriz desde un archivo.
		void read_matrix_file(const char*);       // Lee una matriz desde un archivo.
		void read_sigmajs_json(string);           // Lee formato json para sigmajs desde un string.
		void read_sigmajs_json(ifstream&);        // Lee formato json para sigmajs desde un archivo.
		void read_sigmajs_json_file(const char*); // Lee formato json para sigmajs desde un archivo.

		string matrix();                          // Strings formateadas para output.
		string sigmajs_json();                    //

		// --------------------------- Cambios de visualizaci'on.
		void changeSizesByGrade();  // Cambia el tama~no de los nodos seg'un su grado.

		// ------------------------ Funciones y algoritmos.
		float density();  // Calcula la densidad el grafo,
		int grade(string); // Devuelve el grado de un nodo.
};
