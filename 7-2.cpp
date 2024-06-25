#include <QCoreApplication>
#include <iostream>
#include <QTextStream>
#include <QString>
#include <QMultiMap>
#include <QVector>
#include <QPair>
#include <algorithm>
#include <locale>
#include <clocale>
#include <Windows.h>

using namespace std;

void printMultiMap(const QMultiMap<QString, QString>& m) {
    QTextStream out(stdout);
    out << "\nMap:" << "\n";
    QString currentKey;
    bool first = true;
    for (auto it = m.constBegin(); it != m.constEnd(); ++it) {
        if (first || it.key() != currentKey) {
            currentKey = it.key();
            first = false;
            out << "\nИмя: " << currentKey << "\n";
        }
        out << "Фамилия: " << it.value() << "\n";
    }
    out << "\n";
}

void add(QMultiMap<QString, QString>& m, const QString& name, const QString& surname) {
    m.insert(name, surname);
}

void sorting(QMultiMap<QString, QString>& m) {
    QVector<QPair<QString, QString>> a1;
    for (auto it = m.begin(); it != m.end(); ++it) {
        a1.push_back(qMakePair(it.key(), it.value()));
    }
    m.clear();
    sort(a1.begin(), a1.end(), [](const QPair<QString, QString>& a, const QPair<QString, QString>& b) {
        return a.second > b.second;
    });
    for (const auto& pair : a1) {
        m.insert(pair.first, pair.second);
    }
}

void remove1(QMultiMap<QString, QString>& m, const QString& name, const QString& surname) {
    auto it = m.find(name);
    while (it != m.end() && it.key() == name) {
        if (it.value() == surname) {
            it = m.erase(it);
        } else {
            ++it;
        }
    }
}

void change1(QMultiMap<QString, QString>& a, const QString& name1, const QString& name2, const QString& surname1, const QString& surname2) {
    auto it = a.find(name1);
    while (it != a.end() && it.key() == name1) {
        if (it.value() == surname1) {
            a.erase(it);
            a.insert(name2, surname1);
            break;
        }
        ++it;
    }
    it = a.find(name2);
    while (it != a.end() && it.key() == name2) {
        if (it.value() == surname2) {
            a.erase(it);
            a.insert(name1, surname2);
            break;
        }
        ++it;
    }
}

void change2(QMultiMap<QString, QString>& a, const QString& name1, const QString& name2, const QString& surname1, const QString& surname2) {
    auto it = a.find(name1);
    while (it != a.end() && it.key() == name1) {
        if (it.value() == surname1) {
            a.erase(it);
            a.insert(name1, surname2);
            break;
        }
        ++it;
    }
    it = a.find(name2);
    while (it != a.end() && it.key() == name2) {
        if (it.value() == surname2) {
            a.erase(it);
            a.insert(name2, surname1);
            break;
        }
        ++it;
    }
}

void copyMap(const QMultiMap<QString, QString>& m, QMultiMap<QString, QString>& m2) {
    for (auto it = m.constBegin(); it != m.constEnd(); ++it) {
        m2.insert(it.key(), it.value());
    }
}

void comp1(const QMultiMap<QString, QString>& a, const QString& name1, const QString& name2, const QString& surname1, const QString& surname2) {
    QTextStream out(stdout);
    int c = 0, d = 0;
    auto it1 = a.find(name1);
    auto it2 = a.find(name2);
    if (it1 != a.end() && it1.value() == surname1) {
        c++;
    }
    if (it2 != a.end() && it2.value() == surname2) {
        d++;
    }
    if (c == 0 || d == 0) {
        out << "Таких людей нет в списке" << "\n";
    } else {
        if (name1 < name2) {
            out << "Имя 1 человека раньше в алфавите" << "\n";
        } else if (name1 > name2) {
            out << "Имя 2 человека раньше в алфавите" << "\n";
        } else {
            out << "Они тёзки" << "\n";
        }
    }
}

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);
    //подключение входного и выходного потоков
    QTextStream in(stdin);
    QTextStream out(stdout);
    //подключение русского языка
    setlocale(LC_ALL, "PL_pl.UTF-8");
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    out << "1. Добавить элемент\n"
        << "2. Удалить элемент\n"
        << "3. Поиск количества элементов, ключи которых равны К\n"
        << "4. Обменивает значения двух объектов (отображений)\n"
        << "5. Скопировать элементы в новый map\n"
        << "6. Сравнение отображений\n"
        << "7. Отсортировать map\n"
        << "8. Выход из программы\n";

    QMultiMap<QString, QString> people;
    QMultiMap<QString, QString> people2;

    while (true) {
        out << "Выберите операцию:" << "\n";
        out.flush();
        QString op;
        in >> op;

        if (op == "1") {
            out << "Введите имя:" << "\n";
            out.flush();
            QString name;
            in >> name;
            out << "Введите фамилию:" <<"\n";
            out.flush();
            QString surname;
            in >> surname;
            add(people, name, surname);
            printMultiMap(people);
        } else if (op == "2") {
            out << "Введите имя:" << "\n";
            out.flush();
            QString name;
            in >> name;
            out << "Введите фамилию:" << "\n";
            out.flush();
            QString surname;
            in >> surname;
            remove1(people, name, surname);
            printMultiMap(people);
        } else if (op == "3") {
            out << "Введите имя:" << "\n";
            out.flush();
            QString name;
            in >> name;
            int count = people.count(name);
            out << "Количество элементов с ключом " << name << " = " << count << "\n";
        } else if (op == "4") {
            out << "Введите имя 1 человека:" << "\n";
            out.flush();
            QString name1;
            in >> name1;
            out << "Введите имя 2 человека:" << "\n";
            out.flush();
            QString name2;
            in >> name2;
            out << "Введите фамилию 1 человека:" << "\n";
            out.flush();
            QString surname1;
            in >> surname1;
            out << "Введите фамилию 2 человека:" << "\n";
            out.flush();
            QString surname2;
            in >> surname2;
            out << "Поменять имена (1) или фамилии (2):" << "\n";
            out.flush();
            int choice;
            in >> choice;
            if (choice == 1) {
                change1(people, name1, name2, surname1, surname2);
                printMultiMap(people);
            } else if (choice == 2) {
                change2(people, name1, name2, surname1, surname2);
                printMultiMap(people);
            } else {
                out << "Некорректный ввод, введите заново:" << "\n";
            }
        } else if (op == "5") {
            printMultiMap(people);
            copyMap(people, people2);
            printMultiMap(people2);
        } else if (op == "6") {
            out << "Введите имя 1 человека:" << "\n";
            out.flush();
            QString name1;
            in >> name1;
            out << "Введите имя 2 человека:" << "\n";
            out.flush();
            QString name2;
            in >> name2;
            out << "Введите фамилию 1 человека:" << "\n";
            out.flush();
            QString surname1;
            in >> surname1;
            out << "Введите фамилию 2 человека:" << "\n";
            out.flush();
            QString surname2;
            in >> surname2;
            comp1(people, name1, name2, surname1, surname2);
        } else if (op == "7"){
            sorting(people);
            printMultiMap(people);
        }
        else if (op == "8") {
            out << "Конец программы!" << "\n";
            out.flush();
            return app.exec();
        } else {
            out << "Ошибка" << "\n";
        }
    }

    return app.exec();
}
