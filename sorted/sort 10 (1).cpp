#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
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

bool compare(const people& a, const people& b) { // сравниваем как а раньше б = да/нет (алфавит и зп)
    if (a.job < b.job) return true;
    if (a.job == b.job && a.zp < b.zp) return true;
    return false;
}

void gnome(vector<people>& x) {
    int i = 1; // со второго
    while (i < x.size()) {
        if (i == 0 || compare(x[i - 1], x[i])) { // начало или все норм. ну вообще начало только 1 раз но так как будто бы толерантнее 
            i++;
        }
        else {
            swap(x[i], x[i - 1]);
            i--;
        }
    }
}

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");
    if (!in.is_open()) {
        cout << "не" << endl;
        return 1;
    }

    vector<people> data = inFile(in);
    in.close();
    gnome(data);
    for (const auto& p : data) {
        print(out, p);
    }
    out.close();
    cout << "ура" << endl;
    return 0;
}