#include <iostream>

#include "Aresta.h"

Aresta::Aresta(int idOrigem, int idDestino, int tam) {

	this->idDestino = idDestino;
	this->idOrigem = idOrigem;
	this->tam = tam;
}
							
int Aresta::retIdDestino() { return this->idDestino; }		
int Aresta::retIdOrigem() { return this->idOrigem; }
int Aresta::retTam() { return this->tam; }