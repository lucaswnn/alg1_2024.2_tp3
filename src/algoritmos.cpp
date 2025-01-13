#include <limits>

#include "./../include/algoritmos.hpp"

CamadaBFS::CamadaBFS(size_t el, size_t ant, size_t pos)
{
    el_ant_pos.push_back({el, ant, pos});
}

void CamadaBFS::add_elemento(size_t el, size_t ant, size_t pos)
{
    el_ant_pos.push_back({el, ant, pos});
}

std::tuple<size_t, size_t, size_t> &CamadaBFS::operator[](size_t i)
{
    return el_ant_pos[i];
}

std::vector<std::tuple<size_t, size_t, size_t>>::iterator CamadaBFS::begin()
{
    return el_ant_pos.begin();
}

std::vector<std::tuple<size_t, size_t, size_t>>::iterator CamadaBFS::end()
{
    return el_ant_pos.end();
}

size_t CamadaBFS::size() const
{
    return el_ant_pos.size();
}

// -------

CamadaBFS &CaminhoBFS::operator[](size_t i)
{
    return camadas[i];
}

std::vector<std::pair<size_t, size_t>>::iterator CaminhoBFS::begin()
{
    return caminho.begin();
}

std::vector<std::pair<size_t, size_t>>::iterator CaminhoBFS::end()
{
    return caminho.end();
}

bool CaminhoBFS::encontrar_caminho(Grafo &grafo)
{
    size_t s = 0, t = grafo.n_vertices - 1;
    std::vector<char> descoberto(grafo.n_vertices, 0);
    descoberto[s] = 1;
    camadas.push_back(CamadaBFS({s, s, s}));
    size_t camada = 0;

    // interrompe o algoritmo quando o vértice t é encontrado
    while (!descoberto[t])
    {
        // se na próxima iteração a camada corrente estiver vazia
        // significa que a BFS não encontrou o vértice t
        if (camadas[camada].size() == 0)
        {
            return false;
        }

        camadas.push_back(CamadaBFS());

        // buffer para posição do antecessor de v na camada anterior
        size_t pos = 0;

        t_pos = 0;
        for (auto &u_tupla : camadas[camada])
        {
            size_t u = std::get<0>(u_tupla);
            for (auto u_v : grafo[u])
            {
                size_t v = u_v.v;
                auto &fluxo_u_v = grafo.fluxo[u][v];

                // aresta com fluxo cheio
                if (fluxo_u_v.cap == fluxo_u_v.fluxo)
                {
                    continue;
                }

                if (!descoberto[v])
                {
                    descoberto[v] = 1;
                    camadas[camada + 1].add_elemento(v, u, pos);

                    // interrompe o algoritmo ao descobrir o vértice t
                    if (v == t)
                    {
                        break;
                    }
                    t_pos++;
                }
            }

            // interrompe o algoritmo ao descobrir o vértice t
            if (descoberto[t])
            {
                break;
            }
            pos++;
        }

        camada++;
    }

    _montar_caminho();
    return true;
}

void CaminhoBFS::_montar_caminho()
{
    std::vector<std::pair<size_t, size_t>> caminho_rev;
    // inicializa iterador com a última camada da BFS
    auto camada_it = camadas.rbegin();

    // pega o item da camada (v, u, posição do antecessor na camada anterior)
    auto camada_el = (*camada_it)[t_pos];

    size_t u = std::get<1>(camada_el), v = std::get<0>(camada_el);
    caminho_rev.push_back({u, v});

    size_t ant_pos = std::get<2>(camada_el);
    camada_it++;

    // itera nas camadas de trás para frente
    while (camada_it != (camadas.rend() - 1))
    {
        camada_el = (*camada_it)[ant_pos];

        u = std::get<1>(camada_el), v = std::get<0>(camada_el);
        caminho_rev.push_back({u, v});

        ant_pos = std::get<2>(camada_el);
        camada_it++;
    }

    // inverte o vetor de caminho processado
    caminho = std::vector<std::pair<size_t, size_t>>(caminho_rev.rbegin(), caminho_rev.rend());
}

// -------

void alg::aumentar_caminho(Grafo &grafo, CaminhoBFS &caminho)
{
    // encontra o gargalo do caminho
    size_t gargalo = std::numeric_limits<size_t>::max();
    for (const auto &aresta : caminho)
    {
        size_t u = aresta.first, v = aresta.second;
        auto &fluxo = grafo.fluxo[u][v];
        size_t balanco = fluxo.cap - fluxo.fluxo;
        if (balanco < gargalo)
        {
            gargalo = balanco;
        }
    }

    // altera o fluxo do caminho
    for (const auto &aresta : caminho)
    {
        size_t u = aresta.first, v = aresta.second;
        auto &fluxo = grafo.fluxo[u][v];
        auto &fluxo_rev = grafo.fluxo[v][u];
        fluxo.add_fluxo(gargalo);
        fluxo_rev.sub_fluxo(gargalo);
    }
}

void alg::ford_fulkerson(Grafo &grafo)
{
    while (true)
    {
        CaminhoBFS caminho;
        bool tem_caminho = caminho.encontrar_caminho(grafo);
        if (!tem_caminho)
        {
            break;
        }
        aumentar_caminho(grafo, caminho);
    }
}