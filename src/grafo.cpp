#include <stdexcept>

#include "./../include/grafo.hpp"

Aresta::Aresta(size_t vertice, char categoria) : v(vertice), cat(categoria) {}

// -------

void Vertice::add_aresta(size_t vertice, char categoria)
{
    arestas.push_back(Aresta(vertice, categoria));
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

Fluxo::Fluxo(size_t capacidade,
             size_t fluxo_inicial) : cap(capacidade),
                                     fluxo(fluxo_inicial) {}

void Fluxo::add_fluxo(size_t val)
{
    if (val + fluxo > cap)
    {
        throw std::invalid_argument("Fluxo maior do que a capacidade");
    }

    fluxo += val;
}

void Fluxo::sub_fluxo(size_t val)
{
    if (val > fluxo)
    {
        throw std::invalid_argument("Fluxo maior do que o já existente");
    }

    fluxo -= val;
}

// -------

Grafo::Grafo(size_t n_v) : n_vertices(n_v)
{
    vertices.assign(n_v, Vertice());
    fluxo.assign(n_v, std::vector<Fluxo>(n_v, Fluxo()));
}

void Grafo::add_aresta(size_t v1,
                       size_t v2,
                       size_t capacidade,
                       char categoria)
{
    vertices[v1].add_aresta(v2, categoria);
    vertices[v2].add_aresta(v1, 'r');

    size_t cap_inicial = fluxo[v1][v2].cap;
    if (cap_inicial == 0)
    {
        fluxo[v2][v1] = Fluxo(capacidade, capacidade);
        fluxo[v1][v2] = Fluxo(capacidade);
    }
}

void Grafo::add_capacidade(size_t u, size_t v, size_t val)
{
    fluxo[u][v].cap += val;
    fluxo[v][u].cap += val;
    fluxo[v][u].fluxo += val;
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