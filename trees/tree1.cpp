#include <iostream>
#include <vector>
using namespace std;

struct tree {
    int inf;
    tree* left;
    tree* right; // потомки
    tree* parent;
};

tree* node(int x) { // узел
    tree* n = new tree;
    n->inf = x;
    n->left = n->right = NULL;
    n->parent = NULL;
    return n;
}

void insert(tree*& tr, int x) {
    tree* n = node(x);
    if (!tr) { // пустое = узел это корень
        tr = n;
    }
    else {
        tree* y = tr; // начало спуска от корня
        while (y) {
            if (n->inf > y->inf) { // новое знач больше тек = иду вправо
                if (y->right) {
                    y = y->right;
                }
                else {
                    n->parent = y; // прав ребёнка нет = встав как прав сына + устан родителя
                    y->right = n;
                    break;
                }
            }
            else if (n->inf < y->inf) { // лево так же
                if (y->left) {
                    y = y->left;
                }
                else {
                    n->parent = y;
                    y->left = n;
                    break;
                }
            }
            else { // знач уже сущ = равно тек = удаляю
                delete n;
                break;
            }
        }
    }
}

tree* find(tree* tr, int x) { // ищу узел
    if (!tr || x == tr->inf) { // узел пустой или нашли = возвращ узел/нул
        return tr;
    }
    if (x < tr->inf) { // иск знач меньше = ищу в левой части дерева
        return find(tr->left, x);
    }
    else { // больше = в правой
        return find(tr->right, x);
    }
}

void printpredki(tree* nodex) { 
    if (!nodex) return;
    tree* p = nodex->parent; // родитель узла
    bool first = true;
    cout << "предки узла " << nodex->inf << ": ";

    while (p) {
        if (!first) cout << ", "; // если не первый то пусть через запятую будет
        cout << p->inf; // родитель
        first = false;
        p = p->parent; // к родителю родителя
    }
    if (first) {
        cout << "узел - это корень";
    }
    cout << endl;
}

void inorder(tree* tr) { // симм обход = всё левое, узел, правое 
    if (tr) {
        inorder(tr->left);
        cout << tr->inf << " ";
        inorder(tr->right);
    }
}

int main() {
    setlocale(LC_ALL, "RUS");
    tree* root = NULL;
    int n, x, X;
    cout << "всего элементов: ";
    cin >> n;

    cout << "элементы: ";
    for (int i = 0; i < n; i++) {
        cin >> x;
        insert(root, x);
    }

    cout << "дерево: ";
    inorder(root);
    cout << endl;
    cout << "узел X: ";
    cin >> X;

    tree* nodex = find(root, X);
    if (nodex) {
        printpredki(nodex);
    }
    else {
        cout << "узла " << X << " не существует" << endl;
    }
    return 0;
}