#ifndef Grafo_HPP
#define Grafo_HPP

#include <vector>
#include <string>

#include "Aresta.h"
#include "Vertice.h"

using namespace std;

class Grafo {

private:

	vector<Vertice> vertices;

public:

	Grafo();

	void adVertice(Vertice novo);	    // adiciona novo a vertices

	int retTam();	                    // retorna vertice.size()

	Vertice* retVertice(int id);        // retorna vertice cujo id = id
	Vertice* retVertice(string nome);   // retorna vertice cujo nome = nome

	void partidaTodos(int estrategia);  // forca bruta e guloso sao parecidos, entao eles sao chamados pela mesma funcao
	void forcaBruta(Vertice* inicio, Vertice atual, int* distMin, vector<Vertice>& menorCaminho, vector<Vertice> caminhoAtual, int numPercorridos, vector<bool> percorridos, int distAtual);
	void calcDist();                    // ordena as distancias de todas as arestas de todos os vertices
	void guloso(Vertice* inicio, Vertice atual, int* distMin, vector<Vertice>& menorCaminho, vector<Vertice> caminhoAtual, int numPercorridos, vector<bool> percorridos, int distAtual, bool* final);
	void dinamico();
};

#endif