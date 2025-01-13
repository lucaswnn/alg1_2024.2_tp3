#ifndef _ALGORITMOS_
#define _ALGORITMOS_

#include <cstddef>

#include "./../include/grafo.hpp"

namespace alg
{
    std::pair<size_t, std::vector<size_t>> forca_bruta(Grafo &grafo);

    std::pair<size_t, std::vector<size_t>> programacao_dinamica(Grafo &grafo);

    std::pair<size_t, std::vector<size_t>> guloso(Grafo &grafo);
}

#endif