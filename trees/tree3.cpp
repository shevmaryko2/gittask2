#include <iostream>
#include <vector>
using namespace std;

struct tree {
    int inf;
    tree* left;
    tree* right;
    tree* parent;
};

tree* node(int x) {
    tree* n = new tree;
    n->inf = x;
    n->left = n->right = NULL;
    n->parent = NULL;
    return n;
}

void insert(tree*& tr, int x) {
    tree* n = node(x);
    if (!tr) {
        tr = n;
    }
    else {
        tree* y = tr;
        while (y) {
            if (n->inf > y->inf) {
                if (y->right) {
                    y = y->right;
                }
                else {
                    n->parent = y;
                    y->right = n;
                    break;
                }
            }
            else if (n->inf < y->inf) {
                if (y->left) {
                    y = y->left;
                }
                else {
                    n->parent = y;
                    y->left = n;
                    break;
                }
            }
            else {
                delete n;
                break;
            }
        }
    }
}

tree* find(tree* tr, int x) {
    if (!tr || x == tr->inf) {
        return tr;
    }
    if (x < tr->inf) {
        return find(tr->left, x);
    }
    else {
        return find(tr->right, x);
    }
}

tree* Min(tree* tr) { // самый мал узел в левой части = минимальный
    if (!tr->left) return tr;
    else return Min(tr->left);
}

tree* Next(tree* tr, int x) {
    tree* n = find(tr, x); // нашли узел со знач х
    if (n->right) return Min(n->right); // есть правый ребенок значит след = мин в правой части
    tree* y = n->parent; // нет - вверх иду и возвр родителя
    while (y && n == y->right) {
        n = y;
        y = y->parent;
    }
    return y;
}

void Delete(tree*& tr, tree* v) {
    if (!v) return;

    tree* p = v->parent; // запомнили родителя
    if (!v->left && !v->right) { // удаление листа
        if (!p) {
            tr = NULL; // дерево из одного узла было
        }
        else {
            if (p->left == v) p->left = NULL;
            else p->right = NULL; // не из одного = уберу и предка
        }
        delete v;
    }
    else if (!v->left || !v->right) { // удаление узла с одним ребенком
        tree* child = (v->left) ? v->left : v->right;

        if (!p) { // убрали корень с 1 ребенком
            tr = child;
            child->parent = NULL;
        }
        else {
            if (p->left == v) p->left = child; // убрали узел с одним ребенком
            else p->right = child; // ребенок занял место узла
            child->parent = p; // новый родитель
        }
        delete v;
    }
    else { // удаление узла с двумя детьми
        tree* succ = Next(tr, v->inf); // у след узла точно нет левого ребенка
        v->inf = succ->inf;
        Delete(tr, succ);
    }
}

tree* grandfather(tree* nodex) { // найду деда
    if (!nodex || !nodex->parent) return NULL;
    return nodex->parent->parent; // дед это папа папы
}

void inorder(tree* tr) {
    if (tr) {
        inorder(tr->left);
        cout << tr->inf << " ";
        inorder(tr->right);
    }
}

int main() {
    tree* root = NULL;
    int n, x, X;

    cout << "всего элементов: ";
    cin >> n;
    cout << "элементы: ";
    for (int i = 0; i < n; i++) {
        cin >> x;
        insert(root, x);
    }

    cout << "дерево до удаления: ";
    inorder(root);
    cout << endl;
    cout << "узел X: ";
    cin >> X;

    tree* nodex = find(root, X);
    if (!nodex) {
        cout << "узла " << X << " не существует" << endl;
        return 0;
    }

    tree* ded = grandfather(nodex);
    if (!ded) {
        cout << "деда у " << X << " не существует " << endl;
    }
    else {
        int dedValue = ded->inf;
        cout << "дед " << X << " = " << dedValue << endl;
        Delete(root, ded);
        cout << "удалили: ";
        inorder(root);
        cout << endl;
    }
    return 0;
}