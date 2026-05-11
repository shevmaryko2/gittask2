#include <iostream>
#include <vector>
using namespace std;

int main() {
    setlocale(LC_ALL, "RUS");

    int n, m;
    cout << "всего вершин: ";
    cin >> n;
    cout << "всего ребер: ";
    cin >> m;

    vector<vector<int>> Gr(n); // список смежных вершин для н вершин 

    cout << "сами ребра:" << endl;
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        Gr[x].push_back(y); // к одной вершине другую и к другой первую
        Gr[y].push_back(x);
    }

    int v;
    cout << "вершина: ";
    cin >> v;
    cout << "всего смежных вершин: " << Gr[v].size() << endl;

    return 0;
}