#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

struct date {
    int dd, mm, yy;
};
struct people {
    string surname;
    string job;
    date birthday;
    int staj;
    int zp;
};

date str_to_date(string str) {
    date x;
    x.dd = atoi(str.substr(0, 2).c_str());
    x.mm = atoi(str.substr(3, 2).c_str());
    x.yy = atoi(str.substr(6, 4).c_str());
    return x;
}

vector<people> inFile(ifstream& in) {
    vector<people> x;
    people temp;
    while (in.peek() != EOF) {
        in >> temp.surname >> temp.job;
        string tmp;
        in >> tmp;
        temp.birthday = str_to_date(tmp);
        in >> temp.staj >> temp.zp;
        x.push_back(temp);
    }
    return x;
}

void print(ofstream& out, const people& x) {
    out << setw(12) << left << x.surname;
    out << setw(12) << left << x.job;
    if (x.birthday.dd < 10) out << '0';
    out << x.birthday.dd << '.';
    if (x.birthday.mm < 10) out << '0';
    out << x.birthday.mm << '.';
    out << setw(6) << left << x.birthday.yy;
    out << setw(6) << left << x.staj;
    out << setw(10) << left << x.zp << endl;
}

bool less_than(const people& a, const people& b) { // 10 задача но еще сравн по стажу так же
    if (a.zp < b.zp) return true;
    if (a.zp == b.zp && a.birthday.yy < b.birthday.yy) return true;
    if (a.zp == b.zp && a.birthday.yy == b.birthday.yy && a.staj < b.staj) return true;
    return false;
}

void vibor(vector<people>& x) {
    for (int i = 0; i < x.size() - 1; i++) { // х сайз -1 т к последний и так там где надо будет
        int min_idx = i;
        for (int j = i + 1; j < x.size(); j++) {
            if (less_than(x[j], x[min_idx])) {
                min_idx = j; // фикс индекс если нашли элемент меньше минимального 
            }
        }
        if (min_idx != i) {
            swap(x[i], x[min_idx]);
        }
    }
}

int main() {
    setlocale(LC_ALL,"RUS")
    ifstream in("input.txt");
    ofstream out("output.txt");
    if (!in.is_open()) {
        cout << "не" << endl;
        return 1;
    }

    vector<people> data = inFile(in);
    in.close();
    vibor(data);
    for (const auto& p : data) {
        print(out, p);
    }
    out.close();
    cout << "ура" << endl;
    return 0;
}