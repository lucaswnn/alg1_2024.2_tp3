#include <iostream>
#include <limits>

#include "./../include/algoritmos.hpp"

void alg::reverso(std::vector<long> &v, long i, long f)
{
    while (i < f)
    {
        std::swap(v[i], v[f]);
        i++;
        f--;
    }
}

bool alg::perm(std::vector<long> &v)
{
    long n = v.size();
    long i = n - 2;

    while (i + 1 >= 1 && v[i] >= v[i + 1])
    {
        i--;
    }

    if (i + 1 < 1)
    {
        return false; // Última permutação alcançada previamente
    }

    long j = n - 1;
    while (v[j] <= v[i])
    {
        j--;
    }

    std::swap(v[i], v[j]);

    reverso(v, i + 1, n - 1);

    return true;
}

long alg::cert_hamiltoniano(const std::vector<long> &caminho, Grafo &grafo)
{
    long dist_total = 0;
    long n = caminho.size() - 1;
    for (long i = 0; i != n; i++)
    {
        long u = caminho[i];
        long v = caminho[i + 1];
        dist_total += grafo[u][v];
    }
    return dist_total;
}

std::pair<long, std::vector<long>> alg::forca_bruta(Grafo &grafo)
{
    long n = grafo.n_vertices;
    std::vector<long> perm_i(n);
    for (long i = 0; i < n; i++)
    {
        perm_i[i] = i;
    }

    long menor_dist = std::numeric_limits<long>::max();
    std::vector<long> menor_caminho(n);
    long dist;
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

long alg::pd_custo_total(long mascara,
                         long corrente,
                         Grafo &grafo,
                         std::vector<std::vector<long>> &memo,
                         std::vector<std::vector<long>> &memo_rota)
{
    long n = grafo.n_vertices;

    // todas cidades foram visitadas, retornando para a origem
    if (mascara == (1 << n) - 1)
    {
        return grafo[corrente][0];
    }

    // se já foi computado
    if (memo[corrente][mascara] != -1)
        return memo[corrente][mascara];

    long ans = std::numeric_limits<long>::max(), melhor_cidade;

    // visita as cidades ainda não visitadas
    for (long cidade = 0; cidade < n; cidade++)
    {
        if ((mascara & (1 << cidade)) == 0)
        {

            // se a cidade iterada não foi visitada, visita e atualiza a mascara
            long ans_cidade = grafo[corrente][cidade] +
                              pd_custo_total(
                                  (mascara | (1 << cidade)),
                                  cidade,
                                  grafo,
                                  memo,
                                  memo_rota);

            if (ans_cidade < ans)
            {
                melhor_cidade = cidade;
                ans = ans_cidade;
            }
        }
    }

    memo_rota[corrente][mascara] = melhor_cidade;
    return memo[corrente][mascara] = ans;
}

std::vector<long> alg::pd_caminho(Grafo &grafo, std::vector<std::vector<long>> &memo_rota)
{
    std::vector<long> caminho;
    long mascara = 1, pos = 0;
    long n = grafo.n_vertices;
    for (long cidade = 0; cidade < n; cidade++)
    {
        caminho.push_back(pos);
        pos = memo_rota[pos][mascara]; // Próximo nó a ser visitado
        mascara |= (1 << pos);         // Marca a cidade como visitada
    }

    caminho.push_back(0); // Retorna ao início
    return caminho;
}

std::pair<long, std::vector<long>> alg::programacao_dinamica(Grafo &grafo)
{
    long n = grafo.n_vertices;
    std::vector<std::vector<long>> memo(n, std::vector<long>(1 << n, -1));
    std::vector<std::vector<long>> memo_rota(n, std::vector<long>(1 << n, -1));

    // começa pela cidade zero
    long menor_caminho = pd_custo_total(1, 0, grafo, memo, memo_rota);
    auto caminho = pd_caminho(grafo, memo_rota);

    return std::make_pair(menor_caminho, caminho);
}

std::pair<long, std::vector<long>> alg::guloso(Grafo &grafo)
{
    long n = grafo.n_vertices;
    std::vector<bool> visitado(n, false);
    std::vector<long> caminho(n);
    long custo_total = 0;
    long atual = 0;
    visitado[atual] = true;
    caminho.push_back(0);
    for (long u = 1; u < n; u++)
    {
        long prox;
        long menor_dist = std::numeric_limits<long>::max();
        for (long v = 0; v < n; v++)
        {
            if (!visitado[v] && grafo[u][v] < menor_dist)
            {
                menor_dist = grafo[u][v];
                prox = v;
            }
        }

        visitado[prox] = true;
        caminho.push_back(prox);
        custo_total += menor_dist;
        atual = prox;
    }

    return std::make_pair(custo_total, caminho);
}