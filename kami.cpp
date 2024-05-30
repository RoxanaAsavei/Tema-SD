#include <bits/stdc++.h>
#define VALMAX 1e9
using namespace std;

ifstream fin("kami.in");
ofstream fout("kami.out");

int n;
std::vector<int> munte;
int nrOp;

void citire() {
    fin >> n;
    munte.resize(n + 1);
    for(int i = 1; i <= n; ++i)
        fin >> munte[i];
}

void rezolvare() {
    int op, idx, h;
    int nivelStart;
    bool flag = 0;
    fin >> nrOp;
    for(int i = 0; i < nrOp; ++i) {
        fin >> op;
        if(op == 0) {
            fin >> idx >> h;
            munte[idx] = h;
        }

        else {
            fin >> nivelStart;
            int cantitate = munte[nivelStart];
            flag = 0;
            while(nivelStart > 0) {
                nivelStart--;
                if(cantitate <= munte[nivelStart]) break;
                else {
                    cantitate += munte[nivelStart];
                    if(cantitate > VALMAX) { // din punctul asta nu-l mai opreste nimeni
                        fout << 0 << "\n";
                        flag = 1;
                        break;
                    }
                }
            }

            if(!flag) fout << nivelStart << "\n";
        }
    }

}


int main()
{
    citire();
    rezolvare();

    return 0;
}
