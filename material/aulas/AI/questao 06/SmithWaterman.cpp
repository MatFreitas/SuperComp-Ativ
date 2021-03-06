#include<iostream>
#include<algorithm>
#include <bits/stdc++.h>
#include <bits/stdc++.h>
#include<fstream>
#include<random>
#include <string.h>
using namespace std;

int algorithmLocalAlignment(int n, int m, string a, string b, uint seed) {
    int max_k;

    if(n > m) {
        max_k = m;
    } else {
        max_k = n;
    }

    // Gerar uma subsequencia sb=b[j,j+1,...,j+k] 
    // de b, de tamanho aleatório k, 1<=k<=m, e 0<=j<=m 
    default_random_engine generator{seed};
    int k, max_j, j, i, max_i, teste;
    string sa, sb;

    // TODO: Essa parte não faz nada, mas é necessária,
    // pois a seed não está sendo gerada corretamente
    uniform_int_distribution<int> distribution_teste(1, 50);
    teste = distribution_teste(generator);
    // Evitar warning de unused variable, variável será
    // sobrescrita depois
    max_j = teste;

    // Gerando k
    uniform_int_distribution<int> distribution_k(1, max_k);
    k = distribution_k(generator);
    max_j = m - k;

    // Gerando j
    uniform_int_distribution<int> distribution_j(0, max_j);  
    j = distribution_j(generator); 
    sb = b.substr(j, k);
    

    // Gerar um número aleatório inteiro positivo p
    uniform_int_distribution<int> distribution_p(1, 50);
    int p = distribution_p(generator);
     
    // Gerar i 
    max_i = n - k;
    uniform_int_distribution<int> distribution_i(0, max_i);


    // cout << "sb: " << sb << endl;
    // cout << "k: " << k << endl;
    // cout << "j: " << j << endl;
    // cout << "max_j: " << max_j << endl;
    // cout << "max_i: " << max_i << endl;
    
    // Adicionando gap no sb
    sb = "-" + sb;
    m = sb.size();
    	
    // Guardar o melhor score dentre as p 
    // comparações entre pares (sa, sb)
    int maxValor_Global = 0;
    string sa_Global;

    // Gerar p subsequencias sa=a[i,i+1,...,i+k] de 
    // a, com tamanho k calculado no passo (1), 0<=i<=n
    for(int iter = 0; iter < p; iter++) {
        i = distribution_i(generator);

        // cout << endl << "i: " << i << endl;
        sa = a.substr(i, k);
        // cout << "sa: " << sa << endl;

        // Calcular os scores de cada par (sa,sb) com os 
        // pesos wmat, wmis e wgap

        // Adicionando o gap _
        sa = "-" + sa;
        n = sa.size();
        
        // Matriz H a ser preenchida
        int H[n][m];

        // Inicializar matriz com 0s.
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                H[i][j] = 0;
            }
        }

        int maxValor = 0;

        
        // Para cada 1≤i≤n e 1≤j≤m:
        for(int i = 1; i < n; i++) {
            for(int j = 1; j < m; j++) {
                // Calculando score w
                int w;

                if(sa[i] == sb[j]) {
                    // match
                    w = 2;
                } else {
                    // mismatch ou gap
                    w = -1;
                }

                int diagonal, delecao, insercao;

                // Calcular diagonal
                diagonal = H[i-1][j-1] + w;

                // Calcular deleção
                delecao = H[i-1][j] - 1;

                // Calcular inserção
                insercao = H[i][j-1] - 1;

                // Calcular H[i,j]=máximo (0, diagonal, deleção, inserção)
                H[i][j] = max({0, diagonal, delecao, insercao});

                // Retornar o máximo de H[_,_]
                if(H[i][j] > maxValor) {
                    maxValor = H[i][j];
                }
            }
        }

        // cout << "Valor máximo: " << maxValor << endl;
        
        if(maxValor > maxValor_Global) {
            maxValor_Global = maxValor;
            sa_Global = sa;
        }

        // for(int i = 0; i < n; i++) {
        //     for(int j = 0; j < m; j++) {
        //         cout << H[i][j] << " ";
        //     }
        //     cout<< endl;
        // }
    }

    cout << endl << "k: " << k << endl;
    cout << "Maior valor global: " << maxValor_Global << endl;
    cout << "Subsequências com alinhamento de score máximo: " << endl;
    cout << "sa: " << sa_Global.substr(1, sa_Global.size() + 1) << endl;
    cout << "sb: " << sb.substr(1, sb.size() + 1) << endl;

    // ofstream output;
    // output.open("output");

    // output << alignmentSeqA << "\n";
    // output << match << "\n";
    // output << alignmentSeqB << "\n";

    // output.close();

    // // cout << alignmentSeqA << endl;
    // // cout << match << endl;
    // // cout << alignmentSeqB;

    return 0;
}

int main() {
    // Inicializando as seq. A e B e 
    // seus respectivos tamanhos
    int n, m;
    string a, b;

    cin >> n >> m;
    cin >> a >> b;

    // cout << "a: " << a << endl;
    // cout << "b: " << b << endl;

    int seed = 13607;
    for(int i = 0; i < 10; i++) {
        algorithmLocalAlignment(n, m, a, b, seed);
        seed++;
    }
    return 0;
}