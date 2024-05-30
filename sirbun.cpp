#include <bits/stdc++.h>
#define N 262144
using namespace std;

ifstream fin("sirbun.in");
ofstream fout("sirbun.out");

int n;
struct {
    int val;
    int lazy;
} arb[N + 5];

vector<int> v;

void Build(int node = 1, int left = 1, int right = n) {
    if (left == right) {
        arb[node].val = left;
        return;
    }
    int m = (left + right) / 2;
    Build(2 * node, left, m);
    Build(2 * node + 1, m + 1, right);
    arb[node].val = min(arb[2 * node].val, arb[2 * node + 1].val);
}

void Propagate(int node, int left, int right) {
    if (!arb[node].lazy) // nu are ce propaga
        return;
    arb[node].val += arb[node].lazy; // actualizam valoarea
    if (left != right) { // daca nu e frunza, propaga mai departe la copii
        arb[2 * node].lazy += arb[node].lazy;
        arb[2 * node + 1].lazy += arb[node].lazy;
    }
    arb[node].lazy = 0; // s-a actualizat, deci nu mai are nicio restanta
}

void UpdateIncrement(int posleft, int posright, int node = 1, int left = 1, int right = n) {
    if (posleft <= left && right <= posright) {
        ++arb[node].lazy;
        Propagate(node, left, right);
        return;
    }
    Propagate(node, left, right);
    int m = (left + right) / 2;
    if (posleft <= m)
        UpdateIncrement(posleft, posright, 2 * node, left, m), Propagate(2 * node + 1, m + 1, right);
    if (posright > m)
        UpdateIncrement(posleft, posright, 2 * node + 1, m + 1, right), Propagate(2 * node, left, m);
    arb[node].val = min(arb[2 * node].val, arb[2 * node + 1].val);
}

void UpdateDecrement(int posleft, int posright, int node = 1, int left = 1, int right = n) {
    if (posleft <= left && right <= posright) {
        --arb[node].lazy;
        Propagate(node, left, right);
        return;
    }
    Propagate(node, left, right);
    int m = (left + right) / 2;
    if (posleft <= m)
        UpdateDecrement(posleft, posright, 2 * node, left, m), Propagate(2 * node + 1, m + 1, right);
    if (posright > m)
        UpdateDecrement(posleft, posright, 2 * node + 1, m + 1, right), Propagate(2 * node, left, m);
    arb[node].val = min(arb[2 * node].val, arb[2 * node + 1].val);
}




int main() {
    long long ans = 0;

    // citire
    fin >> n;
    v.resize(n);
    for (int i = 0; i < n; ++i) {
        fin >> v[i];
    }

    // construirea arborelui : momentan nimeni nu are nimic de propagat
    Build();

    // prelucrare secvente
    for (int left = 0, right = 0; right < n; ++right) {
        UpdateDecrement(v[right], n);
        while (arb[1].val < 0)
            UpdateIncrement(v[left++], n);

        ans += right - left + 1;
    }

    fout << ans;
}