#include <bits/stdc++.h>
#define N 10000
using namespace std;

ifstream fin("timbre.in");
ofstream fout("timbre.out");

struct interval {
    int dr;
    int cost;
};

int n, m, k;
interval a[N + 5];
priority_queue <int, vector<int>, greater<int> > Q;

void citire() {
    fin >> n >> m >> k;
    for(int i = 1; i <= m; ++i) {
        fin >> a[i].dr >> a[i].cost;
    }
}

inline bool comp(interval A, interval B) {
    return A.dr > B.dr;
}

void rezolvare() {
    // sortam intervalele descrescator dupa r
    sort(a + 1, a + m + 1, comp);
    int cost = 0, cautat = n;
    int idx = 1;
    while(cautat >= 1) {
        // luam intervalele care il acopera pe cautat
        // si le bagam in Q
        while(idx <= m && a[idx].dr >= cautat) {
            Q.push(a[idx].cost);
            idx++;
        }
        // il luam pe cel mai convenabil
        cost += Q.top();
        Q.pop();
        cautat -= k;
    }
    fout << cost;
}

int main()
{
    citire();
    rezolvare();

    return 0;
}
