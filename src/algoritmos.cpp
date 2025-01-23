#include <iostream>
#include <limits>

#include "./../include/algoritmos.hpp"

void alg::reverso(std::vector<size_t> &v, size_t i, size_t f)
{
    while (i < f)
    {
        std::swap(v[i], v[f]);
        i++;
        f--;
    }
}

bool alg::perm(std::vector<size_t> &v)
{
    size_t n = v.size();
    size_t i = n - 2;

    while (i + 1 >= 1 && v[i] >= v[i + 1])
    {
        i--;
    }

    if (i + 1 < 1)
    {
        return false; // Última permutação alcançada previamente
    }

    size_t j = n - 1;
    while (v[j] <= v[i])
    {
        j--;
    }

    std::swap(v[i], v[j]);

    reverso(v, i + 1, n - 1);

    return true;
}

size_t alg::cert_hamiltoniano(const std::vector<size_t> &caminho, Grafo &grafo)
{
    size_t dist_total = 0;
    size_t n = caminho.size() - 1;
    for (size_t i = 0; i != n; i++)
    {
        size_t u = caminho[i];
        size_t v = caminho[i + 1];
        auto aresta_it = grafo[u].possui_aresta(v);
        if (aresta_it == grafo[u].arestas.end())
        {
            return 0;
        }
        dist_total += aresta_it->d;
    }
    return dist_total;
}

std::pair<size_t, std::vector<size_t>> alg::forca_bruta(Grafo &grafo)
{
    size_t n = grafo.n_vertices;
    std::vector<size_t> perm_i(n);
    for (size_t i = 0; i < n; i++)
    {
        perm_i[i] = i;
    }

    size_t menor_dist = std::numeric_limits<size_t>::max();
    std::vector<size_t> menor_caminho(n);
    size_t dist;
    do
    {
        perm_i.push_back(perm_i.front());
        dist = cert_hamiltoniano(perm_i, grafo);
        perm_i.pop_back();

        if (dist != 0)
        {
            if (dist < menor_dist)
            {
                menor_dist = dist;
                menor_caminho = perm_i;
            }
        }

    } while (perm(perm_i));

    menor_caminho.push_back(menor_caminho.front());

    return std::make_pair(menor_dist, menor_caminho);
}