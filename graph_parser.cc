// graph_parser.cc

#include "graph_parser.h"

Graph::Graph() {}
Graph::~Graph() {}

void Graph::read_matrix(string str) {
	M.clear();     // Elimina grafo anterior.
	dim = 0;       //
	nodes.clear(); //
	edges.clear(); //

	for (string::iterator it = str.begin() ; it<str.end() ; it++)
		if (*it == '\n')
			str.erase(it);

	dim = sqrt(str.size()); // Calcula dimensi'on a partir de la cantidad de elementos.

	vector<bool> v_temp;    // Inicializo M.
	for (unsigned int i = 0 ; i<dim ; i++) {
		v_temp.clear();
		for (unsigned int j = 0 ; j<dim ; j++)
			v_temp.push_back((str[i*dim+j]=='0')? false : true);
		M.push_back(v_temp); } 

	// ---------------------------------- Inicializo nodes y edges a valores por defecto.
	node temp_node;
	edge temp_edge;
	for (unsigned int i=0 ; i<dim ; i++) {
		temp_node.id = "n" + to_string(i);
		temp_node.label = to_string(i);
		temp_node.x = cos(2*PI*i/dim);
		temp_node.y = sin(2*PI*i/dim);
		temp_node.size = 1;
		nodes.push_back(temp_node); }

	int counter=0;
	for (unsigned int i=0 ; i+1<dim ; i++) {
		for (unsigned int j=i+1 ; j<dim ; j++)
			if (M[i][j]) {
				temp_edge.id = "e" + to_string(counter);
				counter++;
				temp_edge.source = "n" + to_string(i);
				temp_edge.target = "n" + to_string(j);
				edges.push_back(temp_edge); } } }

void Graph::read_matrix(ifstream& ifile) {
	string text = "";
	string temp;
	while(getline(ifile, temp))
		text+=temp;

	read_matrix(text); }

void Graph::read_matrix_file(const char* str) {
	ifstream file(str);
	read_matrix(file); }

void Graph::read_sigmajs_json(string str) {
	M.clear();     // Elimina grafo anterior.
	dim = 0;       //
	nodes.clear(); //
	edges.clear(); //

	Json::Value root;
	Json::Reader reader;
	reader.parse(str, root);

	// -------------- Inicializo edges y nodes.
	node node_temp;
	for (unsigned int i = 0 ; i<root["nodes"].size() ; i++) {
		node_temp.id    = root["nodes"][i]["id"].asString();
		node_temp.label = root["nodes"][i]["label"].asString();
		node_temp.x     = root["nodes"][i]["x"].asFloat();
		node_temp.y     = root["nodes"][i]["y"].asFloat();
		node_temp.size  = root["nodes"][i]["size"].asFloat();
		nodes.push_back(node_temp); }

	edge edge_temp;
	for (unsigned int i = 0 ; i<root["edges"].size() ; i++) {
		edge_temp.id     = root["edges"][i]["id"].asString();
		edge_temp.source = root["edges"][i]["source"].asString();
		edge_temp.target = root["edges"][i]["target"].asString();
		edges.push_back(edge_temp); }

	// ------------------------------------ Inicializo dim y M.
	dim = root["nodes"].size();
	vector<bool> temp(dim, false);       // Pongo M a cero.
	for (unsigned int i=0 ; i<dim ; i++) //
		M.push_back(temp);               //
	for (unsigned int i=0 ; i<dim ; i++) // Hago la diagonal.
		M[i][i] = true;                  //

	for (vector<edge>::iterator eit=edges.begin() ; eit < edges.end() ; eit++) { // Pongo las aristas.
		unsigned int counter=0;
		unsigned int x,y;
		for (vector<node>::iterator nit=nodes.begin() ; nit < nodes.end() ; nit++) {
			if (eit->source == nit->id)
				x=counter;
			if (eit->target == nit->id)
				y=counter;
			counter++; }
		M[x][y]	= true;
		M[y][x] = true;	} }

void Graph::read_sigmajs_json(ifstream& ifile) {
	string text = "";
	string temp;
	while(getline(ifile, temp))
		text+=temp;

	read_sigmajs_json(text); }

void Graph::read_sigmajs_json_file(const char* str) {
	ifstream file(str);
	read_sigmajs_json(file); }

string Graph::matrix() {
	string temp = "";
	for (unsigned int i=0 ; i<dim ; i++) {
		for (unsigned int j=0 ; j<dim ; j++)
			temp+=M[i][j]? '1' : '0';
		if (i+1!=dim)
			temp+='\n'; }
	return temp; }

string Graph::sigmajs_json() {
	Json::Value root;
	Json::Value jnode;
	Json::Value jedge;
	
	for (unsigned int i=0 ; i<edges.size() ; i++) {
		jedge["id"] = edges[i].id;
		jedge["source"] = edges[i].source;
		jedge["target"] = edges[i].target;
		root["edges"][i] = jedge; }

	for (unsigned int i=0 ; i<nodes.size() ; i++) {
		jnode["id"] = nodes[i].id;
		jnode["label"] = nodes[i].label;
		jnode["x"] = nodes[i].x;
		jnode["y"] = nodes[i].y;
		jnode["size"] = nodes[i].size;
		root["nodes"][i] = jnode; }

	return root.toStyledString(); }

void Graph::changeSizesByGrade() {
	for (vector<node>::iterator it=nodes.begin() ; it<nodes.end() ; it++)
		it->size = grade(it->id); }

float Graph::density() {
	int sum = 0;
	for (unsigned int i=0 ; i<dim ; i++)
		for (unsigned int j=0 ; j<dim ; j++)
			if (M[i][j])
				sum++;
	return (float(sum)-dim)/(dim*dim-dim); }

int Graph::grade(string id) {
	int grade = 0;
	for (vector<edge>::iterator it=edges.begin() ; it<edges.end() ; it++)
		if ((id == it->source) || (id == it->target))
			grade++;
	return grade; }
