#ifndef _GRAFO_
#define _GRAFO_

#include <vector>

// classe que simboliza um grafo por meio de matriz de adjacências
class Grafo
{
public:
    long n_vertices;
    std::vector<std::vector<long>> dists;

    // construtor que reserva um número inicial de vértices
    Grafo(long n_vertices);

    // método que adiciona uma nova aresta com sua distância
    void add_aresta(long v1,
                    long v2,
                    long distancia);

    // override do operador [] para acessar os vértices
    std::vector<long> &operator[](long i);
};

#endif