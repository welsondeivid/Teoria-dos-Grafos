#include <stdio.h>

/*Vvertice	Avertice, vertice-1		Pvertice, vertice-1
1	        2 3 4 6 0	            5 4 2 6 0
2	        1 5 4 0 0	            5 1 7 0 0
3	        1 5 0 0 0	            4 6 0 0 0
4	        1 2 6 0 0	            2 1 1 0 0
5	        2 3 0 0 0	            7 6 0 0 0
6	        1 4 0 0 0	            6 1 0 0 0*/

// a linha 0 contém na matriz de arestas os números ligados ao 1, e na matriz de pesos o peso referente a cada aresta
// aresta[i][j] -> peso[i][j]

void ler_string(int qVertices, int arestas[][qVertices - 1], int pesos[][qVertices - 1], int graus[], int cont_arestas[], int qArestas, int cont)
{
    int vert, ares, peso;
    char c;
    
    if (cont < qArestas)
    {
        scanf ("%d %d", &vert, &ares);  // sempre vai ter os dois primeiros números
        scanf ("%c", &c);
        
        if (c == ' ')  // se o escaneado foi um espaço tem mais 1 número
        {
            scanf("%d", &peso);
        }
        else
        {
            peso = 1;  // peso se não tiver mostrando
        }

        arestas[vert-1][cont_arestas[vert-1]] = ares;
        arestas[ares-1][cont_arestas[ares-1]] = vert;

        pesos[vert-1][cont_arestas[vert-1]] = peso; //linha referente à mesma linha da matriz arestas
        pesos[ares-1][cont_arestas[ares-1]] = peso; //coluna referente à mesma coluna da matriz arestas
        
        graus[vert-1] += 1;
        graus[ares-1] += 1;
        
        cont_arestas[ares-1] += 1;
        cont_arestas[vert-1] += 1;
        
        ler_string (qVertices, arestas, pesos, graus, cont_arestas, qArestas, cont+1);
    }
    return;
}

int total(int percorridos[], int contador, int tamanho)
{
    if (contador == tamanho)
    {
        return 1;
    }
    else
    {
        if (percorridos[contador] == 0)
        {
            return 0;
        }
        return total(percorridos, contador + 1, tamanho);
    }
}

int procurar(int percorridos[], int num, int contador, int tamanho)
{
    if (contador == tamanho)
    {
        return 0;
    }
    else
    {
        if (num == percorridos[contador])
        {
            return 1;
        }
        else
        {
            return procurar(percorridos, num, contador + 1, tamanho);
        }
    }
}

void adicionarVetor(int percorridos[], int num, int contador)
{
    if (percorridos[contador] == 0)
    {
        percorridos[contador] = num;
    }
    else
    {
        adicionarVetor(percorridos, num, contador + 1);
    }
}

void caminho(int qVertices, int arestas[][qVertices-1], int pesos[][qVertices-1], int percorridos[], int mcaminho[], int atual, int pTotal, int final, int cont, int *ccusto)
{
    int cheio, adjVist, atualVist;
    
    cheio = total(percorridos, 0, qVertices);
    
    atualVist = procurar(percorridos, atual, 0, qVertices);
    
    //printf("%d %d\n", atual, atualVist);
    //printf("*%d*\n", cont);
    
    if (cheio == 1 && atual == final)
    {
        
        if (*ccusto == 0 || *ccusto > pTotal)
        {
            *ccusto = pTotal;
            
            for (int i = 0; i < qVertices; i++)
            {
                mcaminho[i] = percorridos[i];
            }
        }
        
        return ;
    }
    
    if (atual == 0 || cheio == 1 || atualVist == 1) // se o vetor estiver cheio, ou este ja foi visitado retorna
    {
        return;
    }
    else
    {
        adicionarVetor(percorridos, atual, 0);
        
        
        for (int i = 0; i < qVertices-1; i++)
        {
            //adjVist = procurar(percorridos, arestas[atual-1][i], 0, qVertices);
            //printf("%i\n", adjVist);
            
            caminho(qVertices, arestas, pesos, percorridos, mcaminho, arestas[atual-1][i], pTotal + pesos[atual-1][i], final, cont+1, ccusto);
            
            /*if (adjVist == 0)
            {
                caminho(qVertices, arestas, pesos, percorridos, arestas[atual-1][i], pTotal + pesos[atual-1][i], final);
            }*/
        }
        //Print lindjo
        /*for (int i = 0; i < qVertices; i++)
        {
            printf ("%d ", percorridos[i]);
        }
        printf ("\n");*/
            
        percorridos[cont] = 0; //Zerando vetor se passou por todas as adjacências
        
        /*for (int i = 0; i < qVertices; i++)
        {
            printf ("%d ", percorridos[i]);
        }            
        printf ("\n");*/
        //printf ("SAIU\n");
    }
}

int Euler (int graus[], int cont, int tam)
{
    if (cont == tam)
    {
        return 1;
    }
    else
    {
        if (graus[cont] % 2 != 0)
        {
            return 0;
        }
        
        return Euler (graus, cont+1, tam);
    }
}

int Dirac (int graus[], int cont, int tam)
{
    if (cont == tam)
    {
        return 1;
    }
    else
    {
        if ((float)graus[cont] < (tam/2.0))
        {
            return 0;
        }
        
        return Dirac (graus, cont+1, tam);
    }
}

int main()
{
    int vert, ares, n = 1, x, y;
    int ccusto = 0;
    
    scanf ("%d %d\n", &vert, &ares);
    int graus[vert], percorridos[vert], cont_arestas[vert], arestas[vert][vert-1], pesos[vert][vert-1], mcaminho[vert];
    
    // preencher todos os vetores com 0's
    for (int i = 0; i < vert; i++)
    {
        graus[i] = 0;
        cont_arestas[i] = 0;
        percorridos[i] = 0;
        mcaminho[i] = 0;
        
        for (int j = 0; j < vert - 1; j++)
        {
            arestas[i][j] = 0;
            pesos[i][j] = 0;
        }
    }
    
    ler_string (vert, arestas, pesos, graus, cont_arestas, ares, 0);
    
    int D = Dirac (graus, 0, vert);
    
    caminho(vert, arestas, pesos, percorridos, mcaminho, 1, 0, 1, 0, &ccusto);
    
    int euleriano = Euler(graus, 0, vert);
    
    if (euleriano == 1) printf ("Grafo Euleriano\n\n");
    
    else    printf ("Grafo nao Euleriano\n\n");
    
    if (D == 1) // Se o teorema funcionar, já sabemos que hamiltoniano
    {
        printf ("Grafo Hamiltoniano (pelo teorema de Dirac)\n");
        return 0;
    }
    
    //Se o teorema falhar, ainda checamos já que o teorema não é sse
    if (ccusto != 0)
    {
        printf ("Grafo Hamiltoniano (achando ciclo hamiltoniano)\n");
        printf ("Exemplo de ciclo: ");
        
        for (int i = 0; i < vert; i++)
        {
            printf ("%d ", mcaminho[i]);
        }
        printf ("1\nCusto: %d\n", ccusto);
    }
    else
    {
        printf ("Grafo nao Hamiltoniano\n");
    }
    
    return 0;
}