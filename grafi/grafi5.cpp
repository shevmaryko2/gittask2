#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int main() {
    setlocale(LC_ALL, "RUS");

    int n, m;
    cout << "всего вершин: ";
    cin >> n;
    cout << "всего ребер: ";
    cin >> m;

    vector<vector<int>> Gr(n);

    cout << "сами ребра:" << endl;
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        Gr[x].push_back(y);
        Gr[y].push_back(x);
    }

    int a, b;
    cout << "a и b: "; // нач и кон для пути 
    cin >> a >> b;

    vector<int> dist(n, -1); // расст от a до каждой верш
    vector<int> parent(n, -1); // пред верш 
    queue<int> q; // для bsf
    dist[a] = 0; // беру нач верш, помеч ее как посещ и в очередь
    q.push(a);

    while (!q.empty()) {
        int v = q.front(); // из начала и убрали 
        q.pop();
        for (int i = 0; i < Gr[v].size(); i++) { // ищу смеж не посещ верш и обход относ ее
            int to = Gr[v][i];
            if (dist[to] == -1) { // если не посещена
                dist[to] = dist[v] + 1; 
                parent[to] = v; // в to из v 
                q.push(to);
            }
        }
    }

    if (dist[b] == -1) {
        cout << "пути нет" << endl;
    }
    else {
        cout << "длина пути: " << dist[b] << endl;

        vector<int> path;
        int cur = b;
        while (cur != -1) {
            path.push_back(cur);
            cur = parent[cur];
        }
        reverse(path.begin(), path.end());
        cout << "путь: ";
        for (int i = 0; i < path.size(); i++) {
            cout << path[i] << " ";
        }
        cout << endl;
    }
    return 0;
}