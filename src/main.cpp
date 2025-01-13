#include <iostream>
#include <unordered_map>

#include "./../include/grafo.hpp"
#include "./../include/algoritmos.hpp"

typedef std::unordered_map<size_t, std::string> mapa_ull_str_t;
typedef std::unordered_map<std::string, size_t> mapa_str_ull_t;

std::tuple<mapa_ull_str_t, Grafo, char> carregar_entrada()
{
    // captura tipo do algoritmo
    char metodo;
    std::cin >> metodo;

    int n_vertices, n_arestas;
    std::cin >> n_vertices >> n_arestas;

    // associa cada cidade com um índice e vice-versa
    mapa_ull_str_t mapa_ull_str;
    mapa_str_ull_t mapa_str_ull;
    Grafo grafo = Grafo(n_vertices);

    // contador para diferenciar vértices e criar grafo ordenado pelos ids
    int contador = 0;

    for (int i = 0; i != n_arestas; i++)
    {
        std::string v1, v2;
        size_t dist;
        std::cin >> v1 >> v2 >> dist;

        auto [v1_it, inseriu_v1] = mapa_str_ull.insert(std::make_pair(v1, contador));
        // se v1 ainda não existe no mapa
        if (inseriu_v1)
        {
            mapa_ull_str.insert(std::make_pair(contador, v1));
            contador++;
        }

        auto [v2_it, inseriu_v2] = mapa_str_ull.insert(std::make_pair(v2, contador));
        // se v2 ainda não existe no mapa
        if (inseriu_v2)
        {
            mapa_ull_str.insert(std::make_pair(contador, v2));
            contador++;
        }

        // pega os iteradores do mapa e insere o conteúdo no grafo
        grafo.add_aresta(v1_it->second, v2_it->second, dist);
        grafo.add_aresta(v2_it->second, v1_it->second, dist);
    }

    return std::make_tuple(mapa_ull_str, grafo, metodo);
}

std::pair<size_t, std::vector<size_t>> algoritmo(Grafo &grafo, char metodo)
{
    switch (metodo)
    {
    case 'b':
        return alg::forca_bruta(grafo);
        break;
    case 'd':
        return alg::programacao_dinamica(grafo);
        break;
    case 'g':
        return alg::guloso(grafo);
        break;
    default:
        throw "Algo deu errado";
    }
}

void processar_saida(mapa_ull_str_t &mapa, Grafo &grafo, char metodo)
{
    auto [dist, caminho] = algoritmo(grafo, metodo);
    std::cout << dist << "\n";

    size_t n_c = caminho.size();
    size_t i;
    for(i = 0; i <= n_c; i++)
    {
        size_t u = caminho[i];
        auto c = mapa[u];
        std::cout << c << " ";
    }
    std::cout << mapa[caminho[i]] << std::endl;
}

int main()
{
    // carrega a entrada do problema
    auto [mapa, grafo, metodo] = carregar_entrada();

    // processa e imprime a saída
    processar_saida(mapa, grafo, metodo);

    return 0;
}