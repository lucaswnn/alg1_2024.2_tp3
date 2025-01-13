#ifndef _GRAFO_
#define _GRAFO_

#include <cstddef>
#include <vector>

// classe que simboliza aresta
class Aresta
{
public:
    size_t v;
    char cat;

    // construtor padrão
    Aresta() = default;

    // construtor com o ID do vértice e a categoria
    Aresta(size_t vertice, char categoria);
};

// classe que simboliza um vértice de um grafo
class Vertice
{
public:
    std::vector<Aresta> arestas;

    // método para adicionar arestas
    void add_aresta(size_t vertice, char categoria);

    // override do operador [] para acessar as arestas
    Aresta &operator[](size_t i);

    // método para iterar em loop
    std::vector<Aresta>::iterator begin();

    // método para iterar em loop
    std::vector<Aresta>::iterator end();
};

// classe que simboliza o fluxo de uma aresta
class Fluxo
{
public:
    size_t cap;
    size_t fluxo;

    // construtor padrão
    Fluxo() = default;

    // construtor com a capacidade e fluxo inicial
    // fluxo inicial usado para produzir arestas reversas
    Fluxo(size_t capacidade, size_t fluxo_inicial = 0);

    // método para adicionar fluxo
    void add_fluxo(size_t val);

    // método para reduzir fluxo de arestas reversas
    void sub_fluxo(size_t val);
};

// classe que simboliza um grafo por meio de lista de adjacências
class Grafo
{
public:
    size_t n_vertices;
    std::vector<Vertice> vertices;
    std::vector<std::vector<Fluxo>> fluxo;

    // construtor que reserva um número inicial de vértices
    Grafo(size_t n_vertices);

    // método que adiciona uma nova aresta de acordo com a categoria
    // 'o': original
    // 's': de origem
    // 't': de destino
    // 'r': reverso
    void add_aresta(size_t v1,
                    size_t v2,
                    size_t capacidade,
                    char categoria);
    
    // método para incrementar a capacidade de uma aresta
    void add_capacidade(size_t u, size_t v, size_t val);

    // override do operador [] para acessar os vértices
    Vertice &operator[](size_t i);

    // método para iterar em loop
    std::vector<Vertice>::iterator begin();

    // método para iterar em loop
    std::vector<Vertice>::iterator end();
};

#endif