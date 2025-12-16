//АиСД лаба 2

#include <iostream>
#include <string>
#include <limits>
#include <locale>
#include <stdlib.h>
#include <iomanip>
#include <sstream>

using namespace std;

// Хранение данных о времени
struct Time {
    int hours;
    int minutes;
    int seconds;
};

// Сравнение времени
bool isTimeGreater(const Time& time1, const Time& time2) {
    if (time1.hours != time2.hours)
        return time1.hours > time2.hours;
    if (time1.minutes != time2.minutes)
        return time1.minutes > time2.minutes;
    return time1.seconds > time2.seconds;
}

// Ввод времени
bool inputTime(Time& time) {
    string timeStr;
    char colon1, colon2;

    cout << "Введите время в формате ЧЧ:ММ:СС: ";
    getline(cin, timeStr);

    // Символ для завершения цикла
    if (timeStr == "=") {
        return false;
    }

    istringstream timeStream(timeStr);
    if (timeStream >> time.hours >> colon1 >> time.minutes >> colon2 >> time.seconds) {
        if (colon1 == ':' && colon2 == ':' &&
            time.hours >= 0 && time.hours < 24 &&
            time.minutes >= 0 && time.minutes < 60 &&
            time.seconds >= 0 && time.seconds < 60) {
            return true;
        }
    }

    cout << "Неверный формат времени, корректный формат: 11:11:11)" << endl;
    return true;
}

// Вывод времени
void printTime(const Time& time) {
    cout << setw(2) << setfill('0') << time.hours << ":"
        << setw(2) << setfill('0') << time.minutes << ":"
        << setw(2) << setfill('0') << time.seconds;
}

// Вывод массива времён
void printTimes(const Time times[], int size) {
    if (size == 0) {
        cout << "Массив пустой" << endl;
        return;
    }

    cout << "Список времён:" << endl;
    for (int i = 0; i < size; i++) {
        cout << i + 1 << ". ";
        printTime(times[i]);
        cout << endl;
    }
}

// Сортировка выбором
void selectionSort(Time times[], int size, int& comparisons, int& swaps) {
    comparisons = 0;
    swaps = 0;

    for (int i = 0; i < size - 1; i++) {
        int maxIndex = i;
        for (int j = i + 1; j < size; j++) {
            comparisons++;
            if (isTimeGreater(times[j], times[maxIndex])) {
                maxIndex = j;
            }
        }

        if (maxIndex != i) {
            swap(times[i], times[maxIndex]);
            swaps++;
        }
    }
}

// Сортировка вставками
void insertionSort(Time times[], int size, int& comparisons, int& swaps) {
    comparisons = 0;
    swaps = 0;

    for (int i = 1; i < size; i++) {
        Time key = times[i];
        int j = i - 1;

        comparisons++;
        while (j >= 0 && isTimeGreater(key, times[j])) {
            times[j + 1] = times[j];
            j--;
            swaps++;
            if (j >= 0) comparisons++;
        }

        times[j + 1] = key;
        if (j + 1 != i) swaps++;
    }
}

// Сортировка методом Шелла
void shellSort(Time times[], int size, int& comparisons, int& swaps) {
    comparisons = 0;
    swaps = 0;

    for (int gap = size / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < size; i++) {
            Time temp = times[i];
            int j;

            comparisons++;
            for (j = i; j >= gap && isTimeGreater(temp, times[j - gap]); j -= gap) {
                times[j] = times[j - gap];
                swaps++;
                if (j >= gap) comparisons++;
            }
            times[j] = temp;
            if (j != i) swaps++;
        }
    }
}

// Функция для быстрой сортировки
int partition(Time times[], int low, int high, int& comparisons, int& swaps) {
    Time pivot = times[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        comparisons++;
        if (isTimeGreater(times[j], pivot)) {
            i++;
            swap(times[i], times[j]);
            swaps++;
        }
    }
    swap(times[i + 1], times[high]);
    swaps++;
    return (i + 1);
}

// Вспомогательная функция для быстрой сортировки
void quickSortHelper(Time times[], int low, int high, int& comparisons, int& swaps) {
    if (low < high) {
        int pi = partition(times, low, high, comparisons, swaps);

        quickSortHelper(times, low, pi - 1, comparisons, swaps);
        quickSortHelper(times, pi + 1, high, comparisons, swaps);
    }
}

// Быстрая сортировка
void quickSort(Time times[], int size, int& comparisons, int& swaps) {
    comparisons = 0;
    swaps = 0;
    quickSortHelper(times, 0, size - 1, comparisons, swaps);
}

void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Main menu
int getMenuChoice() {
    int choice;
    while (true) {
        cout << "Выберите пункт меню: ";
        cin >> choice;

        if (cin.fail()) {
            cout << "Введите число от 1 до 7." << endl;
            clearInputBuffer();
        }
        else if (choice < 1 || choice > 7) {
            cout << "Неверный выбор, введите число от 1 до 7." << endl;
        }
        else {
            clearInputBuffer();
            return choice;
        }
    }
}

int main() {
    const int MAX_SIZE = 100;
    Time times[MAX_SIZE];
    int currentSize = 0;
    int choice;

    system("chcp 1251");
    setlocale(LC_ALL, "Russian");

    do {
        cout << "\n МЕНЮ ПРОГРАММЫ " << endl;
        cout << "1. Ввод данных" << endl;
        cout << "2. Вывод исходных данных" << endl;
        cout << "3. Сортировка массива выбором" << endl;
        cout << "4. Сортировка массива вставками" << endl;
        cout << "5. Сортировка методом Шелла" << endl;
        cout << "6. Быстрая сортировка" << endl;
        cout << "7. Выйти" << endl;

        choice = getMenuChoice();

        switch (choice) {
        case 1: {
            if (currentSize >= MAX_SIZE) {
                cout << "Массив заполнен. Максимальный размер: " << MAX_SIZE << endl;
                break;
            }

            cout << "\nВвод времен. Для завершения ввода введите =" << endl;

            while (currentSize < MAX_SIZE) {
                Time newTime;
                if (!inputTime(newTime)) {
                    break;
                }

                times[currentSize] = newTime;
                currentSize++;
            }

            cout << "Ввод данных завершен. Добавлено " << currentSize << " времен." << endl;
            break;
        }

        case 2: {
            cout << "\n";
            printTimes(times, currentSize);
            break;
        }

        case 3: {
            if (currentSize == 0) {
                cout << "Массив пуст, заполните" << endl;
                break;
            }

            int comparisons, swaps;
            selectionSort(times, currentSize, comparisons, swaps);

            cout << "\nСортировка методом выбора окончена." << endl;
            cout << "Количество сравнений: " << comparisons << endl;
            cout << "Количество обменов: " << swaps << endl;
            cout << "\nОтсортированный массив (по убыванию времени):" << endl;
            printTimes(times, currentSize);
            break;
        }

        case 4: {
            if (currentSize == 0) {
                cout << "Массив пуст, заполните." << endl;
                break;
            }

            int comparisons, swaps;
            insertionSort(times, currentSize, comparisons, swaps);

            cout << "\nСортировка вставками окончена." << endl;
            cout << "Количество сравнений: " << comparisons << endl;
            cout << "Количество обменов: " << swaps << endl;
            cout << "\nОтсортированный массив (по убыванию времени):" << endl;
            printTimes(times, currentSize);
            break;
        }

        case 5: {
            if (currentSize == 0) {
                cout << "Массив пуст, заполните." << endl;
                break;
            }

            int comparisons, swaps;
            shellSort(times, currentSize, comparisons, swaps);

            cout << "\nСортировка методом Шелла окончена." << endl;
            cout << "Количество сравнений: " << comparisons << endl;
            cout << "Количество обменов: " << swaps << endl;
            cout << "\nОтсортированный массив (по убыванию времени):" << endl;
            printTimes(times, currentSize);
            break;
        }

        case 6: {
            if (currentSize == 0) {
                cout << "Массив пуст, заполните." << endl;
                break;
            }

            int comparisons, swaps;
            quickSort(times, currentSize, comparisons, swaps);

            cout << "\nБыстрая сортировка окончена." << endl;
            cout << "Количество сравнений: " << comparisons << endl;
            cout << "Количество обменов: " << swaps << endl;
            cout << "\nОтсортированный массив (по убыванию времени):" << endl;
            printTimes(times, currentSize);
            break;
        }

        case 7: {
            cout << "Конец программы." << endl;
            break;
        }
        }

    } while (choice != 7);

    return 0;
}