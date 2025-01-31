#ifndef Vertice_HPP
#define Vertice_HPP

#include <vector>
#include <string>

#include "Aresta.h"

using namespace std;

struct Proximo {

	int idDestino_local, distLocal;
};

class Vertice {

private:

	int id;
	string nome;
	vector<Aresta> arestas;
	vector<Proximo> distancias;

public:

	Vertice(int id, string nome);

	void adAresta(Aresta novo);		                // adiciona novo a arestas
	void adDist(Proximo prox);                      // adiciona pro a distancias

	int grauVertice();								// retorna arestas.size()	    
	int retId();						            // retorna id

	string retNome();                               // retorna nome

	Proximo retProx(int i);                         // retorna distancias[i]

	bool operator==(const Vertice& outro) const;

	Aresta* retAresta(int destino);				    // retorna aresta cujo idDestino = destino			
	Aresta* retAresta_pos(int pos);					// retorna aresta arestas[pos]	
};

#endif