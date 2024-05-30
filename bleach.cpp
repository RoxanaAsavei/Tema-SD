#include <bits/stdc++.h>

using namespace std;

ifstream fin("bleach.in");
ofstream fout("bleach.out");

priority_queue <int, vector<int>, greater<int> > q;
long long putereInit, putereActuala;
int N, K;

void rezolvare() {
    int x;
    for(int i = 1; i <= K + 1; ++i) {
        fin >> x;
        q.push(x);
    }

    int minValue = q.top();
    q.pop();
    putereInit = minValue;
    putereActuala = 2 * minValue;
    for(int i = K + 2; i <= N; ++i) {
        fin >> x;
        q.push(x);
        minValue = q.top();
        q.pop();
        if(minValue <= putereActuala) {
            putereActuala += minValue;
        }

        else {
            putereInit += (minValue - putereActuala);
            putereActuala = minValue * 2;
        }
    }

    while(!q.empty()) {
        minValue = q.top();
        q.pop();
        if(minValue <= putereActuala) {
            putereActuala += minValue;
        }

        else {
            putereInit += (minValue - putereActuala);
            putereActuala = minValue * 2;
        }
    }

    fout << putereInit;

}

int main()
{
    fin >> N >> K;
    rezolvare();
    return 0;
}
