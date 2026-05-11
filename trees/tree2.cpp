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

bool leaf(tree* nodex) { // у листа нет сиблингов поэтому он и лист
    return (nodex && !nodex->left && !nodex->right); // и он существует
}

void sumnech(tree* tr, int& sum) {
    if (!tr) return; // пустой
    if (leaf(tr) && (tr->inf % 2 != 0)) { // лист нечетный
        sum += tr->inf;
    }
    sumnech(tr->left, sum); // обошли левую часть дерева и правую так же
    sumnech(tr->right, sum);
}

void inorder(tree* tr) {
    if (tr) {
        inorder(tr->left);
        cout << tr->inf << " ";
        inorder(tr->right);
    }
}

int main() {
    setlocale(LC_ALL, "RUS");
    tree* root = NULL;
    int n, x;
    int sum = 0;

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
    sumnech(root, sum);
    if (sum > 0) {
        cout << "cумма всех нечётных листьев: " << sum << endl;
    }
    else {
        cout << "нет нечётных листьев." << endl;
    }
    return 0;
}