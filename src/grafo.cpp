#include <stdexcept>

#include "./../include/grafo.hpp"

Grafo::Grafo(long n_v) : n_vertices(n_v)
{
    dists.assign(n_v, std::vector<long>(n_v));
}

void Grafo::add_aresta(long v1,
                       long v2,
                       long distancia)
{
    dists[v1][v2] = distancia;
}