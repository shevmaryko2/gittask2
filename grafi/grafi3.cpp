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

    vector<vector<int>> Gr(n);

    cout << "сами ребра:" << endl;
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        Gr[x].push_back(y);
        Gr[y].push_back(x);
    }

    cout << "степени вершин:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "вершина " << i << ": " << Gr[i].size() << endl; // это ж просто длина списка смеж т к все ребра из вершины
    }

    return 0;
}