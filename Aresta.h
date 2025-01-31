#ifndef Aresta_HPP
#define Aresta_HPP
class Aresta {

private:

	int idOrigem, idDestino, tam;

public:

	Aresta(int idOrigem, int idDestino, int tam);

	int retIdDestino();			// retorna id destino
	int retIdOrigem();			// retorna id origem
	int retTam();               // retorna tamanho
};

#endif

