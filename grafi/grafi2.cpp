#include <iostream>
#include <vector>
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
    cout << "a и b для добавки ребра: ";
    cin >> a >> b;
    Gr[a].push_back(b); // б в список ашных вершин и а в список бэшных просто
    Gr[b].push_back(a);

    cout << "теперь есть ребро " << a << "-" << b << endl;
    return 0;
}