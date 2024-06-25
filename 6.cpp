#include <QCoreApplication>
#include <iostream>
#include <QList>
#include <list>
#include <algorithm>
#include <iterator>
#include <cmath>
#include <QtGlobal>
#include <numeric>
#include <clocale>
#include <Windows.h>
using namespace std;
using namespace Qt;

QList<int> createLeadingZeroBitsList(const QList<int>& or1){ //возвращает новый list где каждый эл-т представляет количество ведущих нулевых битов
    QList<int> res;
    for (int value : or1) {
        quint8 quintV = static_cast<quint8>(value);
        res.push_back(qCountLeadingZeroBits(quintV));
    }
    return res;
}
void copBackQList(QList<int>& lst, QList<int>& lsta2) {
    copy_backward(lst.begin(), lst.end(), lsta2.end());
}
void printList(const QList<int>& lst, QTextStream& out) {
    for (int n : lst) {
        out << n << ' ';
    }
    out << '\n';
}

void addElement(QList<int>& lst, QTextStream& in, QTextStream& out) {
    int element;
    out << "Введите целое число для добавления в список: ";
    out.flush();
    in >> element;
    lst.push_back(element);
}

void removeElements(QList<int>& lst, QTextStream& in, QTextStream& out) {
    int count;
    out << "Введите количество удаляемых элементов: ";
    out.flush();
    in >> count;
    while (count-- > 0 && !lst.empty()) {
        int element;
        out << "Введите удаляемый элемент (" << count + 1 << " осталось): ";
        out.flush();
        in >> element;
        lst.remove(element); // Удаляет все вхождения элемента
    }
}

void removeDuplicates(QList<int>& lst) {
    sort(lst.begin(), lst.end()); // Сортировка списка
    lst.erase(unique(lst.begin(), lst.end()), lst.end()); // Удаление последовательных дубликатов
}

void addMultipleElements(QList<int>& lst, QTextStream& in, QTextStream& out) {
    int count, element;
    out << "Сколько элементов вы хотите добавить? ";
    out.flush();
    in >> count;
    out << "Введите элементы: ";
    out.flush();
    for (int i = 0; i < count; ++i) {
        in >> element;
        lst.push_back(element);
    }
}

void partitionList(const QList<int>& lst, QTextStream& in, QTextStream& out) {
    int pivot;
    QList<int> less, equal_or_greater;
    out << "Введите опорное значение: ";
    out.flush();
    in >> pivot;

    partition_copy(
        lst.begin(),
        lst.end(),
        back_inserter(less),
        back_inserter(equal_or_greater),
        [&pivot](int value) { return value < pivot; });

    out << "Элементы < " << pivot << ": ";
    printList(less, out);
    out << "Элементы >= " << pivot << ": ";
    printList(equal_or_greater, out);
}

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    QTextStream in(stdin);
    QTextStream out(stdout);
    setlocale(LC_ALL, "PL_pl.UTF-8");
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    QList<int> lst;

    lst.push_back(10);
    lst.push_back(10);
    lst.push_back(20);
    lst.push_front(5);
    lst.push_front(15);
    lst.push_front(25);

    int kol=lst.size();
    QList<int>lsta2(kol+2);
    int choice;
    do {
        out << "\nМеню:\n"
               "1. Просмотреть состояние списка\n"
               "2. Добавить элемент\n"
               "3. Удалить несколько элементов\n"
               "4. Удалить парные элементы (unique)\n"
               "5. Добавить несколько элементов из массива\n"
               "6. Разделить элементы на две группы (partition)\n"
               "7. Создать новый список с количеством нулевых битов в начале\n"
               "8. Скопировать с конца\n"
               "9. Выход из программы\n"
               "Введите номер действия: ";
        out.flush();
        in >> choice;

        switch (choice) {
        case 1:
            printList(lst, out);
            break;
        case 2:
            addElement(lst, in, out);
            break;
        case 3:
            removeElements(lst, in, out);
            break;
        case 4:
            removeDuplicates(lst);
            break;
        case 5:
            addMultipleElements(lst, in, out);
            break;
        case 6:
            partitionList(lst, in, out);
            break;
        case 7:
            out << "Новый список:\n";
            out.flush();
            printList(createLeadingZeroBitsList(lst),out);
            break;
        case 8:
            copBackQList(lst,lsta2);
            printList(lsta2,out);
            break;
        case 9:
            out << "Выход из программы.\n";
            out.flush();
            break;
        default:
            out << "Неверный выбор, попробуйте снова.\n";
            out.flush();
            break;
        }
    } while (choice != 9);

    return a.exec();
}

