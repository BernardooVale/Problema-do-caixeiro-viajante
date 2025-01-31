#include "Vertice.h"
#include "Aresta.h"

#include <iostream>
#include <string>

Vertice::Vertice(int id, std::string nome) {

	this->id = id;
	this->nome = nome;
}

Aresta* Vertice::retAresta(int destino) {	

	for (auto& aresta : this->arestas)
		if (aresta.retIdDestino() == destino)
			return &aresta;

	return nullptr;
}

Aresta* Vertice::retAresta_pos(int pos) { return &this->arestas[pos]; } 

void Vertice::adAresta(Aresta novo) {	

	this->arestas.push_back(novo);
}

void Vertice::adDist(Proximo prox) {

	this->distancias.push_back(prox);
}

Proximo Vertice::retProx(int i) {

	return this->distancias[i];
}

int Vertice::grauVertice() { return (int)this->arestas.size(); }	
int Vertice::retId() { return this->id; }	// retorna id
std::string Vertice::retNome() { return this->nome; }

bool Vertice::operator==(const Vertice& other) const { return (this->id == other.id); }