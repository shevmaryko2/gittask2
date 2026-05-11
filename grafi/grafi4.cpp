#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int>> Gr;
vector<int> used; // посещенные
vector<int> pr; // предки
vector<vector<int>> cycles;
vector<vector<int>> cycles_sort; // отсортированные

void add_cycle(int start, int end) { // пока cur != нач то запис тек верш в век tmp, cur = pr[cur]
    vector<int> tmp;
    int cur = end;
    while (cur != start) {
        tmp.push_back(cur);
        cur = pr[cur]; // и к предку
    }
    tmp.push_back(start); // в тмп есть теперь всеь цикл (наоборот)
    cycles.push_back(tmp); // все в сайклс
    sort(tmp.begin(), tmp.end());
    cycles_sort.push_back(tmp); // без повторов
}

void dfs(int x) { // в глубину
    used[x] = 1; // x = посещ впервые, если встр уже посещ = нашли цикл
    for (int i = 0; i < Gr[x].size(); i++) {
        int to = Gr[x][i];
        if (pr[x] == to) continue; // если предок то пропуск

        if (!used[to]) { // непосещенная = предок это х
            pr[to] = x;
            dfs(to); // обходим
        }
        else {
            add_cycle(to, x); // начало и конец цикла
        }
    }
    used[x] = 0;
}

int main() {
    setlocale(LC_ALL, "RUS");
    int n, m;
    cout << "всего вершин: ";
    cin >> n;
    cout << "всего ребер: ";
    cin >> m;

    Gr.resize(n);
    used.resize(n, 0);
    pr.resize(n, -1);

    cout << "сами ребра:" << endl;
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        Gr[x].push_back(y);
        Gr[y].push_back(x);
    }

    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            dfs(i);
        }
    }

    if (cycles.empty()) {
        cout << "циклов нет" << endl;
    }
    else {
        cout << "циклы:" << endl;
        for (int i = 0; i < cycles.size(); i++) {
            for (int j = 0; j < cycles[i].size(); j++) {
                cout << cycles[i][j] << " ";
            }
            cout << endl;
        }
    }
    return 0;
}