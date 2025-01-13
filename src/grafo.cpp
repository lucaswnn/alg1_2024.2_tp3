#include <stdexcept>

#include "./../include/grafo.hpp"

Aresta::Aresta(size_t destino, size_t distancia) : v(destino), d(distancia) {}

// -------

void Vertice::add_aresta(size_t destino, size_t distancia)
{
    arestas.push_back(Aresta(destino, distancia));
}

Aresta &Vertice::operator[](size_t i)
{
    return arestas[i];
}

std::vector<Aresta>::iterator Vertice::begin()
{
    return arestas.begin();
}

std::vector<Aresta>::iterator Vertice::end()
{
    return arestas.end();
}

// -------

Grafo::Grafo(size_t n_v) : n_vertices(n_v)
{
    vertices.assign(n_v, Vertice());
}

void Grafo::add_aresta(size_t v1,
                       size_t v2,
                       size_t distancia)
{
    vertices[v1].add_aresta(v2, distancia);
}

Vertice &Grafo::operator[](size_t i)
{
    return vertices[i];
}

std::vector<Vertice>::iterator Grafo::begin()
{
    return vertices.begin();
}

std::vector<Vertice>::iterator Grafo::end()
{
    return vertices.end();
}