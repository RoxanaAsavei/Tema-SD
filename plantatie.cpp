#include <bits/stdc++.h>
#define N 500
#define logN 9
using namespace std;

ifstream fin("plantatie.in");
ofstream fout("plantatie.out");

int n, m, a[N + 3][N + 3];
int maxValue[N + 3][N + 3][logN + 3], p;
// maxValue[i][j][k] = valoarea maxima din patratul cu coltul stanga sus (i, j) si latura 1 << k

void citireTeren() {
    fin >> n >> m;
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= n; ++j) {
            fin >> a[i][j];
        }
    }
}

void prelucrare() {
    p = int(log2(n));
    // calculam maximul pentru patratele de latura 1
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= n; ++j) {
            maxValue[i][j][0] = a[i][j];
        }
    }

    for(int k = 1; k <= p; ++k) {
        for(int i = 1; i + (1 << k) - 1 <= n; ++i) {
            for(int j = 1; j + (1  << k) - 1 <= n; ++j) {
                int max1 = maxValue[i][j][k - 1];
                int max2 = maxValue[i][j + (1 << (k - 1))][k - 1];
                int max3 = maxValue[i + (1 << (k - 1))][j][k - 1];
                int max4 = maxValue[i + (1 << (k - 1))][j + (1 << (k - 1))][k - 1];
                maxValue[i][j][k] = max(max(max1, max2), max(max3, max4));
            }
        }
    }
}

int findMax(int lin1, int col1, int latura) {
    int lin2 = lin1 + latura - 1;
    int col2 = col1 + latura - 1;
    int k = int(log2(latura));
    int max1 = maxValue[lin1][col1][k];
    int max2 = maxValue[lin1][col2 - (1 << k) + 1][k];
    int max3 = maxValue[lin2 - (1 << k) + 1][col1][k];
    int max4 = maxValue[lin2 - (1 << k) + 1][col2 - (1 << k) + 1][k];
    return max(max(max1, max2), max(max3, max4));
}

void rezolvare() {
    int lin, col, latura;
    for(int i = 1; i <= m; ++i) {
        fin >> lin >> col >> latura;
        fout << findMax(lin, col, latura) << "\n";
    }

}

int main()
{
    citireTeren();
    prelucrare();
    rezolvare();
    fin.close();
    fout.close();

    return 0;
}
