#include <bits/stdc++.h>
#define N 250000
#define logN 18
using namespace std;

ifstream fin("stramosi.in");
ofstream fout("stramosi.out");

int n, m;
int tata[N + 5];
int stramos[N + 5][logN + 5]; // stramos[i][j] = al (1 << j) - lea stramos al nodului j
int logn;

void Citire() {
    int x;
    fin >> n >> m;
    for(int i = 1; i <= n; ++i) {
        fin >> x;
        tata[i] = x;
    }

    logn = int(log2(n));
}

void Precalculare() {
    for(int i = 1; i <= n; ++i) {
        stramos[i][0] = tata[i];
    }

    for(int i = 0; i <= n; ++i) {
        for(int j = 1; j <= logn; ++j) {
            stramos[i][j] = stramos[stramos[i][j - 1]][j - 1];
        }
    }
}

void Rezolvare() {
    int q, p;
    for(int i = 1; i <= m; ++i) {
        fin >> q >> p;
        for(int k = 0; k <= logn; ++k) {
            if (p & (1 << k)) {
                q = stramos[q][k];
            }
        }

        fout << q << "\n";
    }

}

int main()
{
    Citire();
    Precalculare();
    Rezolvare();

    return 0;
}
