#include<bits/stdc++.h>
#define N 100000
using namespace std;

int n;
vector<std::pair<int, int> > perechi; // (valoare, idx_pereche)
deque<std::pair<int, int> > prelucrare;
int nrAparitii[N + 5]; // nrAparitii[i] = cate elemente din perechea i apar in prelucrare

void citire() {
    int A, B;
    cin >> n;
    for(int i = 1; i <= n; ++i) {
        cin >> A >> B;
        perechi.push_back({A, i});
        perechi.push_back({B, i});
    }
}

void rezolvare() {
    int ans = 1e9;
    int ct_perechi = 0; // nr de perechi distincte din prelucrare
    sort(perechi.begin(), perechi.end());
    for(int i = 0; i < 2 * n; ++i) {
        prelucrare.push_back(perechi[i]);
        int idxPereche = perechi[i].second;
        nrAparitii[idxPereche]++;
        if(nrAparitii[idxPereche] == 1) {// e prima data cand apare
                ct_perechi++;
        }

        while(!prelucrare.empty() && ct_perechi == n) { // am o solutie posibila
            int dif = prelucrare.back().first - prelucrare.front().first;
            ans = min(ans, dif);
            int idx = prelucrare.front().second;
            nrAparitii[idx]--;
            if(nrAparitii[idx] == 0) ct_perechi--;
            prelucrare.pop_front();
        }
    }

    cout << ans;

}

int main() {

    citire();
    rezolvare();

    return 0;
}