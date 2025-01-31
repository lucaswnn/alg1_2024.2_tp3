#ifndef _ALGORITMOS_
#define _ALGORITMOS_

#include <cstddef>

#include "./../include/grafo.hpp"

namespace alg
{
    // função auxiliar para inverter um vector da posição i até a posição f
    void reverso(std::vector<long> &v, long i, long f);

    // função auxiliar para criar a próxima permutação do vector
    // retorna falso caso não haja mais permutações
    bool perm(std::vector<long> &v);

    // função que verifica se um ciclo é hamiltoniano
    long cert_hamiltoniano(const std::vector<long> &caminho, Grafo &grafo);

    // algoritmo de força bruta
    std::pair<long, std::vector<long>> forca_bruta(Grafo &grafo);

    // função recursiva para memoization no algoritmo de programação dinâmica
    long pd_custo_total(long mascara,
                        long corrente,
                        Grafo &grafo,
                        std::vector<std::vector<long>> &memo,
                        std::vector<std::vector<long>> &memo_rota);

    // recupera a rota do menor caminho do algoritmo de programação dinâmica
    std::vector<long> pd_caminho(Grafo &grafo, std::vector<std::vector<long>> &memo_rota);

    // algoritmo usando programação dinâmica
    std::pair<long, std::vector<long>> programacao_dinamica(Grafo &grafo);

    // algoritmo guloso
    std::pair<long, std::vector<long>> guloso(Grafo &grafo);
}

#endif