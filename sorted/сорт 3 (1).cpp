#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <cmath>
using namespace std;

struct date {
    int dd, mm, yy;
};
struct people { // всё и сразу про каждого, вообще почаще б пользоваться
    string surname;
    string job;
    date birthday;
    int staj;
    int zp;
};

date str_to_date(string str) { // если 02.02.08
    date x;
    string temp = str.substr(0, 2); // то сюда день и в число
    x.dd = atoi(temp.c_str()); // атой только с ц строками \0 работает поэтому с_стр
    temp = str.substr(3, 2); // месяц
    x.mm = atoi(temp.c_str());
    temp = str.substr(6, 4); // год
    x.yy = atoi(temp.c_str());
    return x;
}

vector<people> inFile(ifstream& in) { // сбор из файла (ссылку берем чтоб ошибки не было &)
    vector<people> x; 
    people temp; // временно чтоб прочитать
    while (in.peek() != EOF) { // по идее еоф это чисто конец (аналог чтнения в питоне но как бы вайл как мне кажется)
        in >> temp.surname;
        in >> temp.job;
        string tmp;
        in >> tmp;
        temp.birthday = str_to_date(tmp);
        in >> temp.staj;
        in >> temp.zp;
        x.push_back(temp);
    }
    return x;
}

void print(ofstream& out, const people& x) { 
    out << setw(12) << left << x.surname; // красиво
    out << setw(12) << left << x.job;

    if (x.birthday.dd < 10) out << '0'; // это тоже для норм вывода, если 2 февраля то 02 
    out << x.birthday.dd << '.';
    if (x.birthday.mm < 10) out << '0';
    out << x.birthday.mm << '.';
    out << setw(6) << left << x.birthday.yy;
    out << setw(6) << left << x.staj;
    out << setw(10) << left << x.zp << endl;
}

void radix_sort_lsd(vector<people>& x) { // поразрядная сортировка lsd по зп
    int maxzp = 0;
    for (const auto& p : x) { // проходимся по людам за зп
        if (p.zp > maxzp) maxzp = p.zp;
    }
    int exp = 1; // чтоб разряды чекнуть
    vector<people> output(x.size()); // резы сюда
    while (maxzp / exp > 0) {
        vector<int> count(10, 0);

        for (const auto& p : x) {
            int digit = (p.zp / exp) % 10;
            count[digit]++;
        }
        for (int i = 1; i < 10; i++) {
            count[i] += count[i - 1]; // сколько чисел имеют цифру меньше или равную i
        }
        for (int i = x.size() - 1; i >= 0; i--) { // осортированный и с конца
            int digit = (x[i].zp / exp) % 10;
            output[count[digit] - 1] = x[i]; // -1 т к индексация с 0
            count[digit]--;
        }
        x = output;
        exp *= 10;
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
    radix_sort_lsd(data);
    for (const auto& p : data) { // для каждого в отсортированных записываем
        print(out, p);
    }
    out.close();
    cout << "ура" << endl;

    return 0;
}