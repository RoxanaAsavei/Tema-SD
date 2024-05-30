#include <bits/stdc++.h>

using namespace std;

ifstream fin("proc2.in");
ofstream fout("proc2.out");

priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > ocupate;
// ordoneaza cresc dupa primul elem perechi de forma (ora pana la care e ocupat, indice procesor)
priority_queue <int, vector<int>, greater<int> > libere;
// ordoneaza crescator indicii procesoarelor disponibile

int n, m;

void rezolvare() {
    fin >> n >> m;
    // initial toate procesoarele sunt libere
    for(int i = 1; i <= n; ++i)
        libere.push(i);
    int start, timp;
    for(int i = 1; i <= m; ++i) {
        fin >> start >> timp;
        while(!ocupate.empty() && ocupate.top().first <= start) {
            libere.push(ocupate.top().second);
            ocupate.pop();
        }
        int ales = libere.top();
        fout << ales << "\n";
        libere.pop();
        ocupate.push({start + timp, ales});
    }


}

int main()
{
    rezolvare();

    return 0;
}
