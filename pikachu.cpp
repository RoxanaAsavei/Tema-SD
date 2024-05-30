#include <fstream>
#include <algorithm>
#include <climits>
#define N 100000
#define DMAX 262144
#define MAXLL LLONG_MAX
using namespace std;

ifstream fin("pikachu.in");
ofstream fout("pikachu.out");

int n, k;
int a[N + 5];
int dimST;
int idx[N + 5], pozSortat[N + 5];

    int poz, ct, valoare;

// pozSortat[i] = poz pe care se va afla in vectorul sortat elementul a[i]

// segment trees
int nrValori[DMAX];
long long suma[DMAX];
int idx1, idx2;

void citire() {
    fin >> n >> k;
    for(int i = 1; i <= n; ++i) {
        fin >> a[i];
    }
}

inline bool comp(int idx1, int idx2) {
    return a[idx1] < a[idx2];
}

void prelucrare() {
    for(int i = 1; i <= n; ++i) {
        idx[i] = i;
    }

    // sortam indecsii dupa valorile din vecotrul a
    sort(idx + 1, idx + n + 1, comp);
    for(int i = 1; i <= n; ++i) {
        pozSortat[idx[i]] = i;
    }
}

void update(int left, int right, int nod) { // se adauga un numar = valoare si cu frecventa ct
    if(left == right) {// avem un singur nr in interval
        nrValori[nod] = ct;
        suma[nod] = valoare;
    }

    else {
        int m = (left + right) / 2;
        if(poz <= left) update(left, m, 2 * nod);
        else update(m + 1, right, 2 * nod + 1);

        suma[nod] = suma[2 * nod] + suma[2 * nod + 1];
        nrValori[nod] = nrValori[2 * nod] + nrValori[2 * nod + 1];

    }
}

int find(int left, int right, int nod) {
    if(left == right) return left;
    int m = (left + right) / 2;
    if (poz <= nrValori[2 * nod]) return find(left, m, 2 * nod);

    poz -= nrValori[2 * nod];
    return find(m + 1, right, 2 * nod + 1);
}

long long calcSuma(int left, int right, int nod) { // nodul nod tine suma pt [left, right]
    if(idx1 <= left && right <= idx2) { // intervalul [left, right] este complet inclus in intervalul [idx1, idx2]
        return suma[nod];
    }
    else {
        int m = (left + right) / 2;
        long long ans = 0;
        if(idx1 <= m) ans += calcSuma(left, m, 2 * nod);
        if(m + 1 <= idx2) ans += calcSuma(m + 1, right, 2 * nod + 1);
        return ans;
    }

}

int main() {

    citire();
    prelucrare;
    dimST = 1;
    while(dimST < n) {
        dimST *= 2;
    }

    long long sol = MAXLL;

    	for (int i = 1; i <= N; i++) {
		poz = pozSortat[i]; // pozitia la care se afla in vectorul sortat elementul A[i]
		ct = 1;
        valoare = a[i];
		update(1, dimST, 1);

		if (i - k > 0) { // din momentul in care i > k, la fiecare pas renunt la cel mai din stanga
			poz = pozSortat[i-k]; // sterg elementul de la poz X
			ct = 0, valoare = 0;
			update(1, dimST, 1);
		}

		if (i - k >= 0) { // abia cand i >= k are sens sa ma apuc sa calculez
			poz = k/2 + 1;
			int mediana = find(1, dimST, 1);

			idx1 = 1, idx2 = mediana - 1;
			long long S = (1LL * a[idx[mediana]] * (k/2)) - calcSuma(1, dimST, 1);
			
			idx1 = mediana + 1, idx2 = n;
			S += calcSuma(1, dimST, 1) - (1LL * a[idx[mediana]]*(k-(k/2+1)));

			sol = min(sol, S);
		}
	}

	fout << sol << "\n";

    return 0;
}