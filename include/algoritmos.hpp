#ifndef _ALGORITMOS_
#define _ALGORITMOS_

#include <cstddef>
#include <tuple>

#include "./../include/grafo.hpp"

// classe que simboliza uma camada de uma BFS
class CamadaBFS
{
public:
    std::vector<std::tuple<size_t, size_t, size_t>> el_ant_pos;

    // construtor padrão
    CamadaBFS() = default;

    // construtor que adiciona uma tupla (v, antecessor, index do antecessor na camada anterior)
    CamadaBFS(size_t el, size_t ant, size_t pos);

    // método que adiciona uma tupla (v, antecessor, index do antecessor na camada anterior)
    void add_elemento(size_t el, size_t ant, size_t pos);

    // override do operador [] para acessar os elementos da camada
    std::tuple<size_t, size_t, size_t> &operator[](size_t i);

    // método para iterar em loop
    std::vector<std::tuple<size_t, size_t, size_t>>::iterator begin();

    // método para iterar em loop
    std::vector<std::tuple<size_t, size_t, size_t>>::iterator end();

    // método que retorna o tamanho da camada
    size_t size() const;
};

class CaminhoBFS
{
private:
    // método auxiliar para processar o caminho entre s e t
    void _montar_caminho();

public:
    std::vector<CamadaBFS> camadas;
    std::vector<std::pair<size_t, size_t>> caminho;

    // posição de t na última camada
    size_t t_pos;

    // método para encontrar o menor caminho entre s e t
    // retorna false se não for possível encontrar o caminho
    bool encontrar_caminho(Grafo &grafo);

    // override do operador [] para acessar uma das camadas
    CamadaBFS &operator[](size_t i);

    // método para iterar em loop
    std::vector<std::pair<size_t, size_t>>::iterator begin();

    // método para iterar em loop
    std::vector<std::pair<size_t, size_t>>::iterator end();
};

namespace alg
{
    // função para adicionar fluxo em um caminho de um grafo
    void aumentar_caminho(Grafo &grafo, CaminhoBFS &caminho);

    // algoritmo de Ford-Fulkerson usando BFS para encontrar o menor caminho entre s e t
    void ford_fulkerson(Grafo &grafo);
}

#endif