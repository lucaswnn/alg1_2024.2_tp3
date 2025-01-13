#include <iostream>
#include <limits>
#include <set>

#include "./../include/grafo.hpp"
#include "./../include/algoritmos.hpp"

Grafo carregar_entrada()
{
    size_t n_vertices, n_arestas;
    std::cin >> n_vertices >> n_arestas;

    Grafo grafo = Grafo(n_vertices + 2);
    auto geradores = std::vector<bool>(n_vertices, false);

    for (size_t i = 0; i != n_vertices; i++)
    {
        size_t v, demanda;
        std::cin >> v >> demanda;

        if (demanda == 0)
        {
            geradores[v] = true;
            grafo.add_aresta(0, v, 0, 's');
        }
        else
        {
            grafo.add_aresta(v, n_vertices + 1, demanda, 't');
        }
    }

    for (size_t i = 0; i != n_arestas; i++)
    {
        size_t v1, v2, cap;
        std::cin >> v1 >> v2 >> cap;
        if (geradores[v1])
        {
            grafo.add_capacidade(0, v1, cap);
        }
        grafo.add_aresta(v1, v2, cap, 'o');
    }

    return grafo;
}

// comparador para ordenar o set de conexões críticas
struct cmp
{
    typedef std::tuple<size_t, size_t, size_t> tupla;
    bool operator()(const tupla &e1, const tupla &e2) const
    {
        size_t u1 = std::get<0>(e1), u2 = std::get<0>(e2);
        size_t cap1 = std::get<2>(e1), cap2 = std::get<2>(e2);
        if (cap1 == cap2)
        {
            return u1 < u2;
        }
        return cap1 > cap2;
    }
};

void processar_saida(Grafo &grafo)
{
    size_t e_total = 0, e_nao_atendida = 0;
    size_t cap_total = 0;

    // conexões críticas (u, v, capacidade)
    std::set<std::tuple<size_t, size_t, size_t>, cmp>
        c_crit;

    for (size_t u = 0; u != grafo.n_vertices; u++)
    {
        for (auto &aresta : grafo[u])
        {
            size_t v = aresta.v;
            auto &fluxo = grafo.fluxo[u][v];
            switch (aresta.cat)
            {
            case 'o':
                if (fluxo.cap == fluxo.fluxo)
                {
                    c_crit.insert({u, v, fluxo.fluxo});
                }
                break;
            case 'r':
                break;
            case 's':
                cap_total += fluxo.cap;
                e_total += fluxo.fluxo;
                break;
            case 't':
                e_nao_atendida += (fluxo.cap - fluxo.fluxo);
                break;
            default:
                throw "Algo deu errado";
            }
        }
    }

    size_t e_perdida = cap_total - e_total;

    std::cout << e_total << "\n"
              << e_nao_atendida << "\n"
              << e_perdida << std::endl;

    std::cout << c_crit.size() << std::endl;
    if (c_crit.size() != 0)
    {
        for (auto &c : c_crit)
        {
            std::cout << std::get<0>(c) << " "
                      << std::get<1>(c) << " "
                      << std::get<2>(c) << "\n";
        }
    }
}

int main()
{
    // carrega a entrada do problema
    auto grafo = carregar_entrada();

    // atualiza o grafo com o fluxo a partir do algoritmo de Ford-Fulkerson
    alg::ford_fulkerson(grafo);

    // processa e imprime a saída
    processar_saida(grafo);

    return 0;
}