#include <bits/stdc++.h>

using namespace std;

ifstream fin("euclid.in");
ofstream fout("euclid.out");

int T;
int m, n, h, w; // m linii, n coloane, h inaltime, w latime
std::vector<std::vector<int> > mat;

/// O submatrice de dimensiune >=h, >=w nu poate avea gcd-ul mai mare decat
/// matricea de dimensiune h și w inclusa in ea

void redimensionare() {
    mat.resize(m);
    for(int i = 0; i < m; ++i) {
        mat[i].resize(n);
    }
}

void citire() {
    for(int i = 0; i < m; ++i) {
        for(int j = 0; j < n; ++j) {
            fin >> mat[i][j];
        }
    }
}

int gcd(int a, int b) {
    if(b == 0) return a;
    return gcd(b, a%b);
}

int rezultat() {

    int gcd_max = 0;
    int gcd_submat;
    for(int l1 = 0; l1 < m - h + 1; ++l1) {
        for(int c1 = 0; c1 < n - w + 1; ++c1) {
            // luam matricea cu coltul stanga sus (l1, c1), dreapta jos (l1 + h - 1, c1 + w - 1)
            gcd_submat = mat[l1][c1];
            for(int i = l1; i < l1 + h - 1 && gcd_submat > gcd_max; ++i) {
                for(int j = c1; j < c1 + w - 1 && gcd_submat > gcd_max; ++j) {
                    gcd_submat = gcd(gcd_submat, mat[i][j]);
                }
            }
            gcd_max = max(gcd_max, gcd_submat);
        }

    }

    return gcd_max;
}

void rezolvare() {
    fin >> T;
    for(int i = 1; i <= T; ++i) {
        fin >> m >> n >> h >> w;
        redimensionare();
        citire();
        fout << "Case #" << i << ": " << rezultat() << "\n";
    }

}

int main()
{
    rezolvare();

    return 0;
}
