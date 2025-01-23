#ifndef _ALGORITMOS_
#define _ALGORITMOS_

#include <cstddef>

#include "./../include/grafo.hpp"

namespace alg
{
    // função auxiliar para inverter um vector da posição i até a posição f
    void reverso(std::vector<size_t> &v, size_t i, size_t f);

    // função auxiliar para criar a próxima permutação do vector
    // retorna falso caso não haja mais permutações
    bool perm(std::vector<size_t> &v);

    // função que verifica se um ciclo é hamiltoniano
    size_t cert_hamiltoniano(const std::vector<size_t> &caminho, Grafo &grafo);

    // algoritmo de força bruta
    std::pair<size_t, std::vector<size_t>> forca_bruta(Grafo &grafo);

    // algoritmo usando programação dinâmica
    //std::pair<size_t, std::vector<size_t>> programacao_dinamica(Grafo &grafo);

    // algoritmo guloso
    //std::pair<size_t, std::vector<size_t>> guloso(Grafo &grafo);
}

#endif