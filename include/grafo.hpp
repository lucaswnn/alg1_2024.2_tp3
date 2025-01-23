#ifndef _GRAFO_
#define _GRAFO_

#include <cstddef>
#include <vector>

// classe que simboliza aresta
class Aresta
{
public:
    size_t v;
    size_t d;

    // construtor padrão
    Aresta() = default;

    // construtor com o ID do vértice e a categoria
    Aresta(size_t destino, size_t distancia);
};

// classe que simboliza um vértice de um grafo
class Vertice
{
public:
    std::vector<Aresta> arestas;

    // método para adicionar arestas
    void add_aresta(size_t destino, size_t distancia);

    // método que busca uma aresta e retorna um iterador
    // caso não encontre, retorna o iterador end de arestas
    std::vector<Aresta>::const_iterator possui_aresta(size_t v) const;

    // override do operador [] para acessar as arestas
    Aresta &operator[](size_t i);

    // método para iterar em loop
    std::vector<Aresta>::iterator begin();

    // método para iterar em loop
    std::vector<Aresta>::iterator end();
};

// classe que simboliza um grafo por meio de lista de adjacências
class Grafo
{
public:
    size_t n_vertices;
    std::vector<Vertice> vertices;

    // construtor que reserva um número inicial de vértices
    Grafo(size_t n_vertices);

    // método que adiciona uma nova aresta com sua distância
    void add_aresta(size_t v1,
                    size_t v2,
                    size_t distancia);

    // override do operador [] para acessar os vértices
    Vertice &operator[](size_t i);

    // método para iterar em loop
    std::vector<Vertice>::iterator begin();

    // método para iterar em loop
    std::vector<Vertice>::iterator end();
};

#endif