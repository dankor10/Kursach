//тема 105, система учета проката горнолыжного оборудования
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <io.h>
#include <cstring>
#include <cstdio>

using namespace std;

char name[50]; //тип оборудования 
int number; //инвентарный номер
char Time[20]; //время сдачи в аренду 
int duration; //длительность аренды 
int price; //цена за час

char tempName[50];
int tempNumber;
char tempTime[20];
int tempDuration;
int tempPrice;

int currNumber;
char currName[50];
char currTime[20];
int currDuration;
int currPrice;

void Read(FILE* file, char* name, int& number, char* time, int& durationz, int& price, int index) {

    index = index - 1;

    fseek(file, index * (70 + (3 * sizeof(int))), SEEK_SET);

    fread(name, 50, 1, file);
    fread(&number, sizeof(int), 1, file);
    fread(time, 20, 1, file);
    fread(&durationz, sizeof(int), 1, file);
    fread(&price, sizeof(int), 1, file);

}

void Write(FILE* file, char* name, int& number, char* time, int& durationz, int& price, const char fileName[20] = "Prokat.txt",
    const char fileTape[3] = "ab") {

    fwrite(name, 50, 1, file);
    fwrite(&number, sizeof(int), 1, file);
    fwrite(time, 20, 1, file);
    fwrite(&durationz, sizeof(int), 1, file);
    fwrite(&price, sizeof(int), 1, file);

}

char arrname[12][50] =
{
    {"snowbord"},
    {"ski"},
    {"skates"},
    {"cross-countri skiing"},
    {"tubing"},
    {"set of ski"},
    {"set of snowbord"},
    {"helmet"},
    {"ski boots"},
    {"snowbord boots"},
    {"mask"},
    {"ski poles"},
};


int GetFileSize(FILE* file) {

    fseek(file, 0, SEEK_END);
    int size = ftell(file) / (70 + (3 * sizeof(int)));
    fseek(file, 0, SEEK_SET);

    return size;
}

bool ChekFile(int number) {

    FILE* file;
    errno_t err = fopen_s(&file, "Prokat.txt", "ab");

    for (int i = 1; i - 1 < GetFileSize(file); i++) {

        char name[50];
        int numberChek;
        char time[20];
        int duration;
        int price;


        Read(file, name, numberChek, time, duration, price, i);

        if (numberChek == number) {
            cout << "Оборудование с данными инвентарным номером уже в прокате, введите другой!" << endl;
            return false;
        }
    }

    fclose(file);

    return true;
}

void NewRec(char* name, int& number, char* Time, int& duration, int& price) {
    int hour = -1, minutes = -1, choise2 = 0;

    cout << "Введите тип оборудования: " << endl << endl <<
        "1. Комплект лыж." << endl <<
        "2. Комплект сноуборда." << endl <<
        "3. Сноуборд." << endl <<
        "4. Ботинки сноубордические." << endl <<
        "5. Лыжи." << endl <<
        "6. Ботинки лыжные." << endl <<
        "7. Палки лыжные." << endl <<
        "8. Шлем." << endl <<
        "9. Маска." << endl <<
        "10. Тюбинг." << endl <<
        "11. Коньки." << endl <<
        "12. Беговые лыжи." << endl;

    if (!(cin >> choise2)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Ошибка! Введите число (1-12)" << endl;
        return;
    }

    if (choise2 < 1 || choise2 > 12) {
        cout << "Неверный выбор! Введите число от 1 до 12." << endl;
        return;
    }

    switch (choise2) {
    case 1:
        strcpy_s(name, 50, arrname[5]);
        break;
    case 2:
        strcpy_s(name, 50, arrname[6]);
        break;
    case 3:
        strcpy_s(name, 50, arrname[0]);
        break;
    case 4:
        strcpy_s(name, 50, arrname[9]);
        break;
    case 5:
        strcpy_s(name, 50, arrname[1]);
        break;
    case 6:
        strcpy_s(name, 50, arrname[8]);
        break;
    case 7:
        strcpy_s(name, 50, arrname[11]);
        break;
    case 8:
        strcpy_s(name, 50, arrname[7]);
        break;
    case 9:
        strcpy_s(name, 50, arrname[10]);
        break;
    case 10:
        strcpy_s(name, 50, arrname[4]);
        break;
    case 11:
        strcpy_s(name, 50, arrname[2]);
        break;
    case 12:
        strcpy_s(name, 50, arrname[3]);
        break;
    }

    cout << "Введите инвентарный номер: ";
    while (true) {
        if (!(cin >> number) || number <= 0) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Ошибка! Введите положительное число" << endl;
            continue;
        }

        if (ChekFile(number) == false) {
            continue;
        }
        break;
    }

    while (true) {
        cout << "Введите время сдачи: " << endl;
        while (true) {
            cout << "Введите часы (0-23): ";
            if (!(cin >> hour) || hour < 0 || hour > 23) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Ошибка! Часы должны быть от 0 до 23." << endl;
                continue;
            }
            break;
        }

        while (true) {
            cout << "Введите минуты (0-59): ";
            if (!(cin >> minutes) || minutes < 0 || minutes > 59) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Ошибка! Минуты должны быть от 0 до 59." << endl;
                continue;
            }
            break;
        }

        time_t seconds = time(NULL);
        std::tm* localTime = std::localtime(&seconds);
        int hoursCurr = localTime->tm_hour;
        int minutesCurr = localTime->tm_min;

        if (hour < hoursCurr) {
            break;
        }
        else if (hour == hoursCurr) {
            if (minutes < minutesCurr) {
                break;
            }
            else {
                cout << "Не верное время!" << endl;
                continue;
            }
        }
        else if (hour > hoursCurr) {
            cout << "Не верное время!" << endl;
            continue;
        }
    }

    sprintf_s(Time, 20, "%02d.%02d", hour, minutes);

    cout << "Введите длительность аренды: ";
    while (true) {
        if (!(cin >> duration) || duration < 0) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Ошибка! Введите неотрицательное число" << endl;
            continue;
        }
        break;
    }

    cout << "Введите цену за час: ";
    while (true) {
        if (!(cin >> price) || price <= 0) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Ошибка! Введите положительное число" << endl;
            continue;
        }
        break;
    }
}

int NewRecord() {
    char choise = 'y';

    while (choise == 'y' || choise == 'Y' || choise == 'н' || choise == 'Н') {

        NewRec(name, number, Time, duration, price);

        FILE* file;
        errno_t err = fopen_s(&file, "Prokat.txt", "ab");

        if (err == 0 && file != NULL) {
            Write(file, name, number, Time, duration, price);
            cout << "Запись успешно сохранена в файл" << endl;
            fclose(file);
        }
        else {
            cout << "Ошибка открытия файла!" << endl;
        }

        cout << "Хотите продолжить y/n ";
        cin >> choise;
        cin.ignore(10000, '\n');
    }

    return 0;
}

void Out_Rez() {
    int index = 1;

    FILE* file;
    errno_t err = fopen_s(&file, "Prokat.txt", "rb");

    if (err != 0 || file == NULL) {
        cout << "Ошибка открытия файла или файл не существует!" << endl;
        return;
    }

    cout << left
        << setw(5) << "№"
        << setw(15) << "Название"
        << setw(10) << "Номер"
        << setw(10) << "Время"
        << setw(15) << "Длительность"
        << setw(10) << "Цена" << endl;

    for (int i = 0; i < 65; i++) {
        cout << '-';
    }
    cout << endl;

    int size = GetFileSize(file);

    for (; index <= size; index++) {

        Read(file, name, number, Time, duration, price, index);

        cout << left
            << setw(5) << index
            << setw(15) << name
            << setw(10) << number
            << setw(10) << Time
            << setw(15) << duration
            << setw(10) << price << endl;
    }

    fclose(file);
}

void QuickSort(int size, int order, int Left) {
    if (size <= 1) {
        return;
    }

    int Right = size + Left - 1;
    int Pos = (Left + Right) / 2;
    int Tempi = Left, Tempj = Right;

    FILE* file;
    errno_t err = fopen_s(&file, "Prokat.txt", "rb+");

    if (err != 0 || file == NULL) {
        cout << "Ошибка открытия файла в QuickSort!" << endl;
        return;
    }

    Read(file, name, number, Time, duration, price, Pos + 1);
    int pivotDuration = duration;

    if (order == 2) { // по возрастанию
        while (Tempi <= Tempj) {
            while (Tempi <= Right) {
                Read(file, tempName, tempNumber, tempTime, tempDuration, tempPrice, Tempi + 1);
                if (tempDuration < pivotDuration) {
                    Tempi++;
                }
                else {
                    break;
                }
            }

            while (Tempj >= Left) {
                Read(file, tempName, tempNumber, tempTime, tempDuration, tempPrice, Tempj + 1);
                if (tempDuration > pivotDuration) {
                    Tempj--;
                }
                else {
                    break;
                }
            }

            if (Tempi <= Tempj) {
             
                Read(file, name, number, Time, duration, price, Tempi + 1);
                Read(file, tempName, tempNumber, tempTime, tempDuration, tempPrice, Tempj + 1);

                fseek(file, Tempi * (50 + sizeof(int) + 20 + sizeof(int) + sizeof(int)), SEEK_SET);
                Write(file, tempName, tempNumber, tempTime, tempDuration, tempPrice);

                fseek(file, Tempj * (50 + sizeof(int) + 20 + sizeof(int) + sizeof(int)), SEEK_SET);
                Write(file, name, number, Time, duration, price);

                Tempi++;
                Tempj--;
            }
        }
    }
    else if (order == 1) { // по убыванию
        while (Tempi <= Tempj) {
            
            while (Tempi <= Right) {
                Read(file, tempName, tempNumber, tempTime, tempDuration, tempPrice, Tempi + 1);
                if (tempDuration > pivotDuration) {
                    Tempi++;
                }
                else {
                    break;
                }
            }

            while (Tempj >= Left) {
                Read(file, tempName, tempNumber, tempTime, tempDuration, tempPrice, Tempj + 1);
                if (tempDuration < pivotDuration) {
                    Tempj--;
                }
                else {
                    break;
                }
            }

            if (Tempi <= Tempj) {
               
                Read(file, name, number, Time, duration, price, Tempi + 1);
                Read(file, tempName, tempNumber, tempTime, tempDuration, tempPrice, Tempj + 1);

                fseek(file, Tempi * (50 + sizeof(int) + 20 + sizeof(int) + sizeof(int)), SEEK_SET);
                Write(file, tempName, tempNumber, tempTime, tempDuration, tempPrice);

                fseek(file, Tempj * (50 + sizeof(int) + 20 + sizeof(int) + sizeof(int)), SEEK_SET);
                Write(file, name, number, Time, duration, price);

                Tempi++;
                Tempj--;
            }
        }
    }

    fclose(file);


    QuickSort(Tempj - Left + 1, order, Left);
    QuickSort(Right - Tempi + 1, order, Tempi);
}

void SelectionSort(int size, int order) {
    FILE* file;
    errno_t err = fopen_s(&file, "Prokat.txt", "rb+");

    if (err != 0 || file == NULL) {
        cout << "Ошибка открытия файла!" << endl;
        return;
    }

    for (int i = 0; i < size - 1; i++) {
        int Poisk = i;

        
        Read(file, name, number, Time, duration, price, i + 1);
        int currentNumber = number;

        for (int j = i + 1; j < size; j++) {
            Read(file, currName, currNumber, currTime, currDuration, currPrice, j + 1);

            if (order == 1) { // по убыванию
                if (currNumber > currentNumber) {
                    Poisk = j;
                    currentNumber = currNumber;
                }
            }
            else { // по возрастанию
                if (currNumber < currentNumber) {
                    Poisk = j;
                    currentNumber = currNumber;
                }
            }
        }

        if (Poisk != i) {
            Read(file, name, number, Time, duration, price, i + 1);
            Read(file, tempName, tempNumber, tempTime, tempDuration, tempPrice, Poisk + 1);

            fseek(file, i * (50 + sizeof(int) + 20 + sizeof(int) + sizeof(int)), SEEK_SET);
            Write(file, tempName, tempNumber, tempTime, tempDuration, tempPrice);

            fseek(file, Poisk * (50 + sizeof(int) + 20 + sizeof(int) + sizeof(int)), SEEK_SET);
            Write(file, name, number, Time, duration, price);
        }
    }

    fclose(file);
}

int InsertionSort(int size, int order) {
    FILE* file;
    errno_t err = fopen_s(&file, "Prokat.txt", "rb+");

    if (err != 0 || file == NULL) {
        cout << "Ошибка открытия файла!" << endl;
        return -1;
    }

    for (int i = 1; i < size; i++) {
       
        Read(file, tempName, tempNumber, tempTime, tempDuration, tempPrice, i + 1);
        int currentPrice = tempPrice;

        int j = i - 1;

        if (order == 2) { // По возрастанию
            while (j >= 0) {
                Read(file, name, number, Time, duration, price, j + 1);

                if (price > currentPrice) {
                    
                    fseek(file, (j + 1) * (50 + sizeof(int) + 20 + sizeof(int) + sizeof(int)), SEEK_SET);
                    Write(file, name, number, Time, duration, price);
                    j--;
                }
                else {
                    break;
                }
            }
        }
        else if (order == 1) { // По убыванию
            while (j >= 0) {
                Read(file, name, number, Time, duration, price, j + 1);

                if (price < currentPrice) {
                    
                    fseek(file, (j + 1) * (50 + sizeof(int) + 20 + sizeof(int) + sizeof(int)), SEEK_SET);
                    Write(file, name, number, Time, duration, price);
                    j--;
                }
                else {
                    break;
                }
            }
        }


        fseek(file, (j + 1) * (50 + sizeof(int) + 20 + sizeof(int) + sizeof(int)), SEEK_SET);
        Write(file, tempName, tempNumber, tempTime, tempDuration, tempPrice);
    }

    fclose(file);
    return 0;
}

int Sort() {
    int vibor, vibor2;

    FILE* file;
    errno_t err = fopen_s(&file, "Prokat.txt", "ab+");

    int size = GetFileSize(file);
    if (size == 0) {
        cout << "Файл пуст." << endl;
        fclose(file);
        return 0;
    }

    fclose(file);

    while (true) {
        cout << "Выберите как сортировать:" << endl <<
            "1. Быстрая сортировка по длительности." << endl <<
            "2. Сортировка выбором по инвентарному номеру." << endl <<
            "3. Сортировка вставками по цене за час." << endl <<
            "Введите 0 для выхода." << endl;

        if (!(cin >> vibor) || vibor < 0 || vibor > 3) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Ошибка! Введите число (0 - 3)" << endl;
            continue;
        }

        if (vibor == 0) {
            return 0;
        }

        cout << "Как сортировать" << endl <<
            "1. По убыванию." << endl <<
            "2. По возрастанию. " << endl;

        if (!(cin >> vibor2) || vibor2 < 1 || vibor2 > 2) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Ошибка! Введите число (1 - 2)" << endl;
            continue;
        }

        int Left = 0;

        switch (vibor) {
        case 1:
            QuickSort(size, vibor2, Left);
            cout << "Сортировка выполнена!" << endl;
            Out_Rez();
            break;
        case 2:
            SelectionSort(size, vibor2);
            cout << "Сортировка выполнена!" << endl;
            Out_Rez();
            break;
        case 3:
            InsertionSort(size, vibor2);
            cout << "Сортировка выполнена!" << endl << endl;
            Out_Rez();
            break;
        }

    }

    return 0;
}

int serchBin() {
    int select;
    char choise3 = 'y', choise2;

    FILE* file;
    errno_t err = fopen_s(&file, "Prokat.txt", "rb");

    int size = GetFileSize(file);
    if (size == 0) {
        cout << "Файл пуст." << endl;
        return 0;
    }

    while (choise3 == 'y' || choise3 == 'Y' || choise3 == 'н' || choise3 == 'Н') {

        int jndex = 0;

        for (int i = 0; i < size - 1; i++) {
            Read(file, name, number, Time, duration, price, i + 1);
            Read(file, tempName, tempNumber, tempTime, tempDuration, tempPrice, i + 2);


            if (duration > tempDuration) {
                jndex++;
            }
        }

        fclose(file);

        if (jndex >= 1) {
            while (true) {
                cout << "Данные не отсортированы. Отсортировать?(y/n)";
                cin >> choise2;
                cin.ignore(10000, '\n');

                if (choise2 == 'y' || choise2 == 'Y') {

                    QuickSort(size, 2, 0);

                }
                else {
                    cout << "Данные не отсортированы. Хотите выйти(y/n)";
                    cin >> choise2;
                    cin.ignore(10000, '\n');

                    if (choise2 == 'y' || choise2 == 'Y') {
                        return 0;
                    }
                    else {
                        continue;
                    }
                }
                break;
            }
        }

        err = fopen_s(&file, "Prokat.txt", "rb");

        cout << "Введите значение длительности: ";
        if (!(cin >> select) || select < 0) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Ошибка! Введите неотрицательное число" << endl;
            continue;
        }

        int left = 0, right = size - 1, mid;
        bool found = false;

        while (left <= right) {
            mid = left + (right - left) / 2;

            Read(file, name, number, Time, duration, price, mid + 1);


            if (select == duration) {
                found = true;

                int tempMid = mid;
                while (tempMid <= right) {

                    Read(file, name, number, Time, duration, price, mid + 1);
                    if (duration == select) {
                        cout << name << '\t' <<
                            number << '\t' <<
                            Time << '\t' <<
                            duration << '\t' <<
                            price << '\t' << endl;
                        tempMid++;
                    }
                    else {
                        break;
                    }
                }

                tempMid = mid - 1;
                while (tempMid >= left) {
                    Read(file, name, number, Time, duration, price, mid + 1);
                    if (duration == select) {
                        cout << name << '\t' <<
                            number << '\t' <<
                            Time << '\t' <<
                            duration << '\t' <<
                            price << '\t' << endl;
                        tempMid--;
                    }
                    else {
                        break;
                    }
                }
                break;
            }
            else if (duration > select) {
                right = mid - 1;
            }
            else {
                left = mid + 1;
            }
        }

        if (!found) {
            cout << "Запись не найдена." << endl;
        }

        cout << "Хотите повторить?(y/n)";
        cin >> choise3;
        cin.ignore(10000, '\n');
    }

    fclose(file);

    return 0;
}

int SerchZap() {
    int hour = 0, minutes = 0;
    int currentTimeMinutes = 0;
    int foundCount = 0;

    cout << "Поиск оборудования, находящегося в прокате" << endl;
    cout << "Введите текущее время:" << endl;

    while (true) {
        cout << "Часы (0-23): ";
        if (!(cin >> hour) || hour < 0 || hour > 23) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Ошибка! Введите число от 0 до 23." << endl;
            continue;
        }
        break;
    }

    while (true) {
        cout << "Минуты (0-59): ";
        if (!(cin >> minutes) || minutes < 0 || minutes > 59) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Ошибка! Введите число от 0 до 59." << endl;
            continue;
        }
        break;
    }

    currentTimeMinutes = hour * 60 + minutes;

    FILE* file;
    errno_t err = fopen_s(&file, "Prokat.txt", "rb");

    if (err != 0 || file == NULL) {
        cout << "Ошибка открытия файла или файл не существует!" << endl;
        return 0;
    }

    int size = GetFileSize(file);
    if (size == 0) {
        cout << "Файл пуст." << endl;
        fclose(file);
        return 0;
    }

    cout << "\nОборудование в прокате на момент " << hour << ":" << (minutes < 10 ? "0" : "") << minutes << ":" << endl;
    cout << left
        << setw(5) << "№"
        << setw(15) << "Тип"
        << setw(10) << "Номер"
        << setw(10) << "Время начала"
        << setw(12) << "Длительность"
        << setw(10) << "Цена/час"
        << setw(15) << "Полная стоимость" << endl;

    for (int i = 0; i < 72; i++) cout << '-';
    cout << endl;

    for (int i = 1; i <= size; i++) {
        Read(file, name, number, Time, duration, price, i);

        int startHour = 0, startMin = 0;
        sscanf_s(Time, "%d.%d", &startHour, &startMin);
        int startMinutes = startHour * 60 + startMin;
        int endMinutes = startMinutes + duration * 60;

        if (startMinutes <= currentTimeMinutes && currentTimeMinutes < endMinutes) {
            foundCount++;
            int totalCost = price * duration;
            cout << left
                << setw(5) << foundCount
                << setw(15) << name
                << setw(10) << number
                << setw(10) << Time
                << setw(12) << duration
                << setw(10) << price
                << setw(15) << totalCost << endl;
        }
    }

    if (foundCount == 0) {
        cout << "На заданное время оборудование в прокате отсутствует." << endl;
    }
    else {
        cout << "\nВсего в прокате: " << foundCount << " единиц оборудования." << endl;
    }

    fclose(file);
    return 0;
}

int serchLin() {
    char tipe[100];
    char choise = 'y';

    while (choise == 'y' || choise == 'Y' || choise == 'н' || choise == 'Н') {

        cout << "Введите тип оборудования для поиска: " << endl;
        cout << "Доступные типы:" << endl;
        cout << "snowbord, ski, skates, cross-countri skiing, tubing, set of ski" << endl;
        cout << "set of snowbord, helmet, ski boots, snowbord boots, mask, ski poles" << endl;
        cout << "Введите 0 для выхода: ";

        cin.ignore(10000, '\n');
        cin.getline(tipe, 100);

        if (tipe[0] == '0') {
            break;
        }

        FILE* file;
        errno_t err = fopen_s(&file, "Prokat.txt", "rb");

        if (err != 0 || file == NULL) {
            cout << "Ошибка открытия файла или файл не существует!" << endl;
            return 0;
        }

        int size = GetFileSize(file);
        if (size == 0) {
            cout << "Файл пуст." << endl;
            fclose(file);
            return 0;
        }

        int foundCount = 0;
        cout << "\nРезультаты поиска:" << endl;
        cout << left
            << setw(5) << "№"
            << setw(15) << "Название"
            << setw(10) << "Номер"
            << setw(10) << "Время"
            << setw(15) << "Длительность"
            << setw(10) << "Цена" << endl;

        for (int i = 0; i < 65; i++) {
            cout << '-';
        }
        cout << endl;

        for (int i = 1; i <= size; i++) {

            Read(file, name, number, Time, duration, price, i);

            if (strcmp(name, tipe) == 0) {
                foundCount++;
                cout << left
                    << setw(5) << foundCount
                    << setw(15) << name
                    << setw(10) << number
                    << setw(10) << Time
                    << setw(15) << duration
                    << setw(10) << price << endl;
            }
        }

        if (foundCount == 0) {
            cout << "Записи с типом оборудования \"" << tipe << "\" не найдены" << endl;
        }
        else {
            cout << "\nВсего найдено записей: " << foundCount << endl;
        }

        fclose(file);

        cout << "\nХотите продолжить поиск? (y/n): ";
        cin >> choise;
        cin.ignore(10000, '\n');
    }

    return 0;
}

int Search() {
    int chisl;

    while (true) {
        cout << "Выберите как искать:" << endl <<
            "1. Бинарный поиск по длительности." << endl <<
            "2. Линейный поиск по типу." << endl <<
            "3. Поиск находящегося в прокате оборудоавния." << endl <<
            "Нажмите 0 для выхода.";

        if (!(cin >> chisl) || chisl < 0 || chisl > 3) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Ошибка! Введите число (0 - 3)" << endl;
            continue;
        }

        if (chisl == 0) {
            cout << "Программа завершена." << endl;
            return 0;
        }

        switch (chisl) {
        case 1:
            serchBin();
            break;
        case 2:
            serchLin();
            break;
        case 3:
            SerchZap();
            break;
        }
    }

    return 0;
}

int Stat() {
    cout << "Статистика цен на оборудование..." << endl;

    FILE* file;
    errno_t err = fopen_s(&file, "Prokat.txt", "rb");

    if (err != 0 || file == NULL) {
        cout << "Ошибка открытия файла!" << endl;
        return 0;
    }

    int size = GetFileSize(file);
    if (size == 0) {
        cout << "Файл пуст." << endl;
        fclose(file);
        return 0;
    }

    FILE* file2;
    errno_t err2 = fopen_s(&file2, "Statistika.txt", "w");
    if (err2 != 0 || file2 == NULL) {
        cout << "Ошибка создания файла статистики!" << endl;
        fclose(file);
        return 0;
    }

    fprintf(file2, "%-20s | %-10s | %-10s | %-12s | %-10s\n",
        "Название", "Номер", "Время", "Длительность", "Цена");
    fprintf(file2, "---------------------|------------|------------|--------------|------------\n");

    for (int j = 0; j < 12; j++) {
        for (int i = 1; i <= size; i++) {

            Read(file, name, number, Time, duration, price, i);

            if (strcmp(arrname[j], name) == 0) {
                fprintf(file2, "%-20s | %-10d | %-10s | %-12d | %-10d\n",
                    name, number, Time, duration, price);
            }
        }
    }

    fclose(file2);
    fclose(file);

    cout << "Статистика сохранена в файл Statistika.txt" << endl;

    return 0;
}

int Delete() {
    int choise;
    char choise2 = 'y';

    FILE* file;
    errno_t err = fopen_s(&file, "Prokat.txt", "rb+");

    if (err != 0 || file == NULL) {
        cout << "Ошибка открытия файла!" << endl;
        return 0;
    }

    int size = GetFileSize(file);
    if (size == 0) {
        cout << "Файл пуст." << endl;
        return 0;
    }

    fclose(file);

    cout << "Удаление записи " << endl << endl;

    while (choise2 == 'y' || choise2 == 'Y' || choise2 == 'н' || choise2 == 'Н') {

        Out_Rez();

        cout << endl << "Введите номер записи которую хотите удалить: " << endl
            << "Введите 0 для выхода" << endl;

        if (!(cin >> choise)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Ошибка ввода!" << endl;
            continue;
        }

        if (choise == 0) {
            return 0;
        }

        if (choise < 1 || choise > size) {
            cout << "Неверный номер записи! Введите число от 1 до " << size << endl;
            continue;
        }

        err = fopen_s(&file, "Prokat.txt", "rb+");

        for (int i = choise; i < size; i++) {

            Read(file, tempName, tempNumber, tempTime, tempDuration, tempPrice, i + 1);

            fseek(file, (i - 1) * (70 + (3 * sizeof(int))), SEEK_SET);

            Write(file, tempName, tempNumber, tempTime, tempDuration, tempPrice);
        }

        int newSize = (size - 1) * (70 + (3 * sizeof(int))); //спросить
        _chsize_s(_fileno(file), newSize);

        fclose(file);

        cout << "Запись успешно удалена!" << endl;
        size--;

        cout << "Хотите удалить еще запись?(y/n)";
        cin >> choise2;
        cin.ignore(10000, '\n');
    }

    return 0;
}

int Editing() {

    int Choise, Num, Chet;

    cout << "Выберите запись которую хотите отредактирова: " << endl << endl;

    Out_Rez();

    cout << "Ваш выбор:" << '\t';
    cin >> Num;

    NewRec(name, number, Time, duration, price);

    FILE* file;
    errno_t err = fopen_s(&file, "Prokat.txt", "rb+");

    int pos = (Num - 1) * (70 + (3 * sizeof(int)));
    fseek(file, pos, SEEK_SET);


    Write(file, name, number, Time, duration, price);
    cout << "Запись успешно сохранена в файл" << endl;

    fclose(file);

    return 0;
}

int clearScrean() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
    return 0;
}

int main() {
    setlocale(LC_ALL, "rus");

    int choise = 1;

    cout << "СИСТЕМА УЧЕТА ПРОКАТА ГОРНОЛЫЖНОГО ОБОРУДОВАНИЯ" << endl << endl;
    cout << "Для выбора пункта введите его номер" << endl;

    while (true) {
        cout << "\n1. Добавить запись." << endl <<
            "2. Удалить запись." << endl <<
            "3. Отсортировать." << endl <<
            "4. Найти находящееся в прокате оборудование." << endl <<
            "5. Статистика цен на оборудование." << endl <<
            "6. Отредактировать запись." << endl <<
            "7. Вывести все на экран." << endl <<
            "Для выхода введите 0." << endl <<
            "Введите номер(0 - 7): ";

        int num;

        if (!(cin >> num)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Ошибка! Введите число (0 - 7)" << endl;
            continue;
        }

        if (num < 0 || num > 7) {
            cout << "Введите номер(0 - 7)" << endl;
            continue;
        }

        if (num == 0) {
            cout << "Программа завершена." << endl;
            return 0;
        }

        switch (num) {
        case 1:
            NewRecord();
            clearScrean();
            cout << "СИСТЕМА УЧЕТА ПРОКАТА ГОРНОЛЫЖНОГО ОБОРУДОВАНИЯ" << endl << endl;
            cout << "Для выбора пункта введите его номер" << endl;
            break;
        case 2:
            Delete();
            clearScrean();
            cout << "СИСТЕМА УЧЕТА ПРОКАТА ГОРНОЛЫЖНОГО ОБОРУДОВАНИЯ" << endl << endl;
            cout << "Для выбора пункта введите его номер" << endl;
            break;
        case 3:
            Sort();
            clearScrean();
            cout << "СИСТЕМА УЧЕТА ПРОКАТА ГОРНОЛЫЖНОГО ОБОРУДОВАНИЯ" << endl << endl;
            cout << "Для выбора пункта введите его номер" << endl;
            break;
        case 4:
            Search();
            clearScrean();
            cout << "СИСТЕМА УЧЕТА ПРОКАТА ГОРНОЛЫЖНОГО ОБОРУДОВАНИЯ" << endl << endl;
            cout << "Для выбора пункта введите его номер" << endl;
            break;
        case 5:
            Stat();
            clearScrean();
            cout << "СИСТЕМА УЧЕТА ПРОКАТА ГОРНОЛЫЖНОГО ОБОРУДОВАНИЯ" << endl << endl;
            cout << "Для выбора пункта введите его номер" << endl;
            break;
        case 6:
            Editing();
            cout << "Введите 0 для выхода: ";
            cin >> choise;
            if (choise == 0) {
                clearScrean();
            }
            cout << "СИСТЕМА УЧЕТА ПРОКАТА ГОРНОЛЫЖНОГО ОБОРУДОВАНИЯ" << endl << endl;
            cout << "Для выбора пункта введите его номер" << endl;
            break;
        case 7:
            Out_Rez();
            cout << "Введите 0 для выхода: ";
            cin >> choise;
            if (choise == 0) {
                clearScrean();
            }
            cout << "СИСТЕМА УЧЕТА ПРОКАТА ГОРНОЛЫЖНОГО ОБОРУДОВАНИЯ" << endl << endl;
            cout << "Для выбора пункта введите его номер" << endl;
            break;
        }
    }
    return 0;
}
