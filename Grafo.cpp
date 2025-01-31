#include <vector>
#include <iostream>
#include <string>
#include <queue>
#include <stack>

#include "Grafo.h"
#include "Aresta.h"
#include "Vertice.h"

#define MAX_INT 2147483647

Grafo::Grafo() {}

Vertice* Grafo::retVertice(int id) {	// retorna o vertice cujo id ==id

	for (auto& vertice : this->vertices)
		if (vertice.retId() == id)
			return &vertice;

	return nullptr;
}

Vertice* Grafo::retVertice(string nome) {

	for (auto& vertice : this->vertices)
		if (vertice.retNome() == nome)
			return &vertice;

	return nullptr;
}

void Grafo::adVertice(Vertice novo) {	// adiciona um vertice

	this->vertices.push_back(novo);
}

int Grafo::retTam() { return (int)this->vertices.size(); }	// retorna o tamanho do vertor de vertices

void Grafo::partidaTodos(int estrategia) {

	int distMin = MAX_INT;
	bool* final = new bool(false);
	std::vector<Vertice> menorCaminho;
	std::vector<Vertice> caminhoAtual;
	std::vector<bool> percorridos(this->retTam(), false);

	if (estrategia == 1) this->calcDist();

	estrategia == 0 ? this->forcaBruta(&this->vertices[0], this->vertices[0], &distMin, menorCaminho, caminhoAtual, this->retTam() - 1, percorridos, 0) 
					: this->guloso(&this->vertices[0], this->vertices[0], &distMin, menorCaminho, caminhoAtual, this->retTam() - 1, percorridos, 0, final);

	std::cout << distMin << std::endl;
	for(size_t i = 0; i < menorCaminho.size(); i++)
		std::cout << menorCaminho[i].retNome()  << " ";
	std::cout << std::endl;

	return;
}

void Grafo::forcaBruta(Vertice* inicio, Vertice atual, int* distMin, std::vector<Vertice>& menorCaminho, std::vector<Vertice> caminhoAtual, int numPercorridos, std::vector<bool> percorridos, int distAtual) {

	percorridos[atual.retId()] = true;
	caminhoAtual.push_back(atual);

	for (int i = 0; i < atual.grauVertice(); i++) {

		Aresta* aresta = atual.retAresta_pos(i);
		Vertice* destino = this->retVertice(aresta->retIdDestino());

		if (!(*destino == *inicio) && !percorridos[destino->retId()]) {
			this->forcaBruta(inicio, *destino, distMin, menorCaminho, caminhoAtual, numPercorridos - 1, percorridos, distAtual + aresta->retTam());
		}

		if (*destino == *inicio && numPercorridos == 0) {

			if (distAtual + aresta->retTam() < *distMin) {
				*distMin = distAtual + aresta->retTam();
				menorCaminho = caminhoAtual;
			}
		}
	}

	return;
}

struct Comparador {
	bool operator()(const Proximo& a, const Proximo& b) {
		return a.distLocal > b.distLocal; // Min-heap (idade crescente)
	}
};

void Grafo::calcDist() {

	for (int i = 0; i < this->retTam(); i++) {

		std::priority_queue<Proximo, std::vector<Proximo>, Comparador> minHeap;

		Vertice* atual = this->retVertice(i);

		for (int j = 0; j < atual->grauVertice(); j++) {

			Aresta aresta = *atual->retAresta_pos(j);

			Proximo proximo;
			proximo.distLocal = aresta.retTam();
			proximo.idDestino_local = aresta.retIdDestino();

			minHeap.push(proximo);
		}

		for (size_t k = 0; k < minHeap.size(); k = k) {

			Proximo proximo = minHeap.top();
			minHeap.pop();
			atual->adDist(proximo);
		}
	}
}

void Grafo::guloso(Vertice* inicio, Vertice atual, int* distMin, vector<Vertice>& menorCaminho, vector<Vertice> caminhoAtual, int numPercorridos, vector<bool> percorridos, int distAtual, bool* final) {

	percorridos[atual.retId()] = true;
	caminhoAtual.push_back(atual);
	
	for (int i = 0; i < atual.grauVertice(); i++) {

		Proximo prox = atual.retProx(i);

		if (*final) {
			break;
		}

		if (prox.idDestino_local == inicio->retId() && numPercorridos == 0) {
			*final = true;
			*distMin = distAtual + prox.distLocal;
			menorCaminho = caminhoAtual;

			return;
		}

		if (!(prox.idDestino_local == inicio->retId()) && !percorridos[prox.idDestino_local]) 
			this->guloso(inicio, *this->retVertice(prox.idDestino_local), distMin, menorCaminho, caminhoAtual, numPercorridos - 1, percorridos, distAtual + prox.distLocal, final);
	
	}

	return;
}

void Grafo::dinamico() { 

	int combinacoes = 1 << this->retTam() - 1;

	Vertice inicio = *this->retVertice(0);

	std::vector<std::vector<int>> distRelativas(combinacoes, std::vector<int>(this->retTam() - 1, MAX_INT));

	for(int subConjunto = 1; subConjunto < combinacoes; subConjunto++)  // para todos os possiveis conjuntos
		for (int idVertice = 0; idVertice < this->retTam() - 1; idVertice++) {  // para todos os vertices
			if(subConjunto & (1 << idVertice))  // se o vertice pertence ao conjunto
				for (int idAntigo = 0; idAntigo < this->retTam() - 1; idAntigo++) { // para todos os vertices
					Vertice antigo = *this->retVertice(idAntigo + 1);
					Aresta* aresta = antigo.retAresta(idVertice + 1);

					int subConjunto_Origem = subConjunto ^ (1 << idVertice);    // subconjunto sem o vertice atual

					if (subConjunto_Origem == 0 && idAntigo == idVertice) { // primeira distancia, caso base entre o vertice inicio e esse
						distRelativas[subConjunto][idVertice] = inicio.retAresta(idVertice + 1)->retTam();
					}

					if ((subConjunto & (1 << idAntigo)) &&  // se o subconjunto atual possui o idAntigo, ele nao e o mesmo que o atual e a aresta existe
						idAntigo != idVertice &&
						aresta != nullptr) {

						if (distRelativas[subConjunto_Origem][idAntigo] + aresta->retTam() < distRelativas[subConjunto][idVertice]) // se nova distancia for menor que a atual
							distRelativas[subConjunto][idVertice] = distRelativas[subConjunto_Origem][idAntigo] + aresta->retTam();
					}
				}
		}

	int minDist = MAX_INT;

	for (int i = 0; i < this->retTam() - 1; i++) { // itera sobre todos os caminhos finalizados e ve o qual e menor (soma entre a distancia ate ali, mais a distancia entre o vertice final e o vertice inicio)

		Vertice atual = *this->retVertice(i + 1);
		Aresta* aresta = atual.retAresta(0);

		if (aresta != nullptr) {
			if (distRelativas[combinacoes - 1][i] + aresta->retTam() < minDist)
				minDist = distRelativas[combinacoes - 1][i] + aresta->retTam();
		}
	}

	std::cout << minDist << std::endl;

	std::stack<Vertice> caminho;

	int idPosterior = 0;
	int subConjunto = combinacoes - 1;

	while (subConjunto != 0) {  // enquanto nao passar pelo caminho inteiro

		int menorDist = INT_MAX;
		int idMenor_dist = -1;

		for (int v = 0; v < this->retTam() - 1; v++) {
			Vertice atual = *this->retVertice(v + 1);
			Aresta* aresta = atual.retAresta(idPosterior);

			if (aresta != nullptr && (subConjunto & (1 << v))) {    // ve qual e o menor caminho (ja que ele que foi selecionado)
				if (distRelativas[subConjunto][v] + aresta->retTam() < menorDist) {
					menorDist = distRelativas[subConjunto][v] + aresta->retTam();
					idMenor_dist = v + 1;
				}
			}
		}

		subConjunto = subConjunto ^ (1 << (idMenor_dist - 1));  // vai para o conjunto origem
		idPosterior = idMenor_dist;
		Vertice menor = *this->retVertice(idMenor_dist);
		caminho.push(menor);
	}

	caminho.push(*this->retVertice(0));

	for (size_t i = 0; i < caminho.size(); i = i) {
		std::cout << caminho.top().retNome() << " ";
		caminho.pop();
	}
}