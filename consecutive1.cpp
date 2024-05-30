#include <bits/stdc++.h>
#define N 100000
#define logN 17
using namespace std;


/**
    O secventa de numere x1, x2 ... xn, cu xm minim si xM maxim este alcatuita din valori consecutive daca:
        1. xM - xm = n - 1
        2. x1 + ... + xn = xM * (xM + 1) / 2 - (xm - 1) * xm / 2
*/

int n, a[N + 3];
int q;
int maxValue[N + 3][logN + 3], minValue[N + 3][logN + 3], m;
long long sumePartiale[N + 3];

void citire() {

    cin >> n;
    for(int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    m = int(log2(n));
}

void prelucrare() {
    // calculam maxValue : maxValue[i][j] = maximul din secventa care incepe la poz i si are lungimea 1 << j
    // initial luam secventele de lungime 1
    for(int i  = 1; i <= n; ++i) {
        maxValue[i][0] = a[i];
    }
    for(int j = 1; j <= m; ++j) {
        for(int i = 1; i + (1 << j) - 1 <= n; ++i)  {
            maxValue[i][j] = max(maxValue[i][j - 1], maxValue[i + (1 << (j - 1))][j - 1]);
        }
    }

    // calculam minValue : minValue[i][j] = minimul din secventa care incepe la poz i si are lungimea 1 << j
    for(int i  = 1; i <= n; ++i) {
        minValue[i][0] = a[i];
    }
    for(int j = 1; j <= m; ++j) {
        for(int i = 1; i + (1 << j) - 1 <= n; ++i)  {
            minValue[i][j] = min(minValue[i][j - 1], minValue[i + (1 << (j - 1))][j - 1]);
        }
    }

    // calculam sumele partiale
    for(int i = 1; i <= n; ++i) {
        sumePartiale[i] = sumePartiale[i - 1] + a[i];
    }

}

int determinaMinim(int st, int dr) {
    // determina minimul din intervalul de indici [st, dr]
    int lg = dr - st + 1;
    int k = int(log2(lg));
    return min(minValue[st][k], minValue[dr - (1 << k) + 1][k]);
}

int determinaMaxim(int st, int dr) {
    int lg = dr - st + 1;
    int k = int(log2(lg));
    return max(maxValue[st][k], maxValue[dr - (1 << k) + 1][k]);

}

long long sumaGauss(int n) {
    return 1LL * n * (n + 1) / 2;
}

void rezolvare() {
    int st, dr;
    cin >> q;
    for(int i = 1; i <= q; ++i) {
        cin >> st >> dr;
        int lg = dr - st + 1;
        int m = determinaMinim(st, dr);
        int M = determinaMaxim(st, dr);
        if(M - m == lg - 1 && sumePartiale[dr] - sumePartiale[st - 1] == sumaGauss(M) - sumaGauss(m - 1)) {
            cout << 1;
        }
        else {
            cout << 0;
        }
    }

}

int main()
{
   citire();
   prelucrare();
   rezolvare();

    return 0;
}
