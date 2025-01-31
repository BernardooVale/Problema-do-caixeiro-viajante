#include <iostream>
#include <string>

#include "Aresta.h"
#include "Grafo.h"
#include "Vertice.h"

using namespace std;

int main(){

    Grafo grafo;

    int numVertices, numArestas, dist;

    char estrategia;

    cin >> estrategia;
    cin >> numVertices >> numArestas;

    string nomeOrigem, nomeDestino;

    Vertice* origem = nullptr;
    Vertice* destino = nullptr;

    for (int i = 0; i < numArestas; i++) {

        cin >> nomeOrigem >> nomeDestino >> dist;

        origem = grafo.retVertice(nomeOrigem);
        destino = grafo.retVertice(nomeDestino);

        if (origem == nullptr) {
            Vertice novo(grafo.retTam(), nomeOrigem);
            grafo.adVertice(novo);
        }

        if (destino == nullptr) {
            Vertice novo(grafo.retTam(), nomeDestino);
            grafo.adVertice(novo);
        }

        origem = grafo.retVertice(nomeOrigem);
        destino = grafo.retVertice(nomeDestino);

        Aresta ida(origem->retId(), destino->retId(), dist);
        origem->adAresta(ida);
        Aresta volta(destino->retId(), origem->retId(), dist);
        destino->adAresta(volta);
    }

    switch (estrategia){
        case 'b':

            grafo.partidaTodos(0);

            break;
        case 'g':

            grafo.partidaTodos(1);

            break;
        case 'd':

            grafo.dinamico();

        default:

            cout << "Estrategia incorreta" << endl;

            break;
    }
    return 1;
}
