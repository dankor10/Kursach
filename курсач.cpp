#include <iostream>
//#include <ctime>
#include <stdio.h>
#include <cstring> 

using namespace std;

struct Arenda {

    //Сноуборд, горные лыжи, беговые лыжи, палки для лыж, ботинки для сноуборда , 
    //ботинки для лыж, маска, шлем, коньки, тюбинг, комплект лыж и комплект сноуборда
    char name[25]; //тип оборудования 
    int number; //инвентарный номер
    char time[10]; //время сдачи в аренду 
    int duration; //длительность аренды 
    int price; // цена за час 

};



int NewRecord() { // новая запись

    const int NAME_SIZE = 25;
    const int TIME_SIZE = 20;

    char name[NAME_SIZE];
    int number;
    char time[TIME_SIZE];
    int duration;
    int price;

    char snowbord[] = "snowbord";
    char ski[] = "ski";
    char skates[] = "skates";
    char cross_countriSkiing[] = "cross-countri skiing";
    char tubing[] = "tubing";
    char setSki[] = "set of Ski";
    char setsnowbord[] = "set of snowbord";
    char helmet[] = "helmet";
    char skiBoots[] = "ski boots";
    char snowbordBoots[] = "snowbord boots";
    char mask[] = "mask";
    char skiPoles[] = "ski poles";

    int choise2 = 0;

    cout << "Добавление записи..." << endl;

    char choise = 'y';

    FILE* file;
    errno_t err = fopen_s(&file, "Prokat.txt", "a");

    if (err != 0) {

        cout << "Ошибка, файл не найден";
        return 1;
    }

    while (choise == 'y' || choise == 'Y') {

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

        switch (choise2) {
        case 1:
            strcpy_s(name, setSki);
            break;
        case 2:
            strcpy_s(name, setsnowbord);
            break;
        case 3:
            strcpy_s(name, snowbord);
            break;
        case 4:
            strcpy_s(name, skiBoots);
            break;
        case 5:
            strcpy_s(name, ski);
            break;
        case 6:
            strcpy_s(name, skiBoots);
            break;
        case 7:
            strcpy_s(name, skiPoles);
            break;
        case 8:
            strcpy_s(name, helmet);
            break;
        case 9:
            strcpy_s(name, setSki);
            break;
        case 10:
            strcpy_s(name, tubing);
            break;
        case 11:
            strcpy_s(name, skates);
            break;
        case 12:
            strcpy_s(name, cross_countriSkiing);
            break;
        }

        cout << "Введите инвентарный номер: ";
        while (!(cin >> number)) {
            cin.ignore();
            cin.clear(1000,'\n');
            cout << "Введите число: ";
        }

        cout << "Введите время сдачи: ";
        cin.getline(time, TIME_SIZE);


        cout << "Введите длительность аренды: ";
        while (!(cin >> duration)) {
            cin.ignore();
            cin.clear(1000, '\n');
            cout << "Введите число: ";
        }

        cout << "Введите цену за час: ";
        while (!(cin >> price)) {
            cin.ignore();
            cin.clear(1000, '\n');
            cout << "Введите число: ";
        }

        fprintf(file, "%s|%d|%s|%d|%d\n", name, number, time, duration, price);

        cout << "Запись успешно сохранена в файл" << endl;

        cout << "Хотите продолжить y/n ";
        cin >> choise;
        cin.ignore();
    }

    fclose(file);

    return 0;
}

int Delete() {// для удаления
    cout << "Удаление записи..." << endl;
    return 0;
}

void Out_Rez(Arenda* note, int size) {// для вывода 

    for (int i = 0; i < size; i++) {

        cout << note[i].name << '\t' <<
            note[i].number << '\t' <<
            (note[i].time) << '\t' <<
            note[i].duration << '\t' <<
            note[i].price << '\t' << endl;
    }
}

int QuickSort(Arenda* note, int size, int vibor2) { //Быстрая сортировка, не работает
    // чтобы справа были эл больше опорногго, слева меньше

    if (size <= 1) {
        return 1;
    }

    Arenda point = note[(size - 1) / 2]; // Опорный элемент
    int i = 0, j = size - 1;

    while (i <= j) {
        if (vibor2 == 1) { // По убыванию

            while (i <= j && note[i].duration >= point.duration) {
                i++;
            }

            while (i <= j && note[j].duration <= point.duration) {
                j--;
            }
        }
        else { // По возрастанию

            while (i <= j && note[i].duration <= point.duration) {
                i++;
            }

            while (i <= j && note[j].duration >= point.duration) {
                j--;
            }
        }

        // Если нашли пару для обмена
        if (i <= j) {
            Arenda temp = note[i];
            note[i] = note[j];
            note[j] = temp;
            i++;
            j--;
        }
    }

    if (j > 0) {
        QuickSort(note, j + 1, vibor2);      // Левая часть
    }
    if (i < size) {
        QuickSort(&note[i], size - i, vibor2); // Правая часть
    }

    return 0;
}

int SelectionSort(Arenda* note, int size, int vibor2) { //Сортировка выбором
    //находим максимум или минимум и ставим в конец

    if (size <= 1) {
        return 1;
    }

    for (int i = 0; i < size - 1; i++) {
        int extremumIndex = i;

        for (int j = i + 1; j < size; j++) {
            if (vibor2 == 1) { // По убыванию 
                if (note[j].number > note[extremumIndex].number) {
                    extremumIndex = j;
                }
            }
            else { // По возрастанию 
                if (note[j].number < note[extremumIndex].number) {
                    extremumIndex = j;
                }
            }
        }

        // Если нашли элемент, который должен быть на позиции i
        if (extremumIndex != i) {
            Arenda temp = note[i];
            note[i] = note[extremumIndex];
            note[extremumIndex] = temp;
        }
    }

    return 0;
}

int InsertionSort(Arenda* note, int size, int vibor2) { //Сортировка вставками
    // проверям чтобы каждый эл был меньше левого и больше правого и наоборот

    if (size <= 1) {
        return 1;
    }

    for (int i = 1; i < size; i++) {
        Arenda key = note[i];
        int j = i - 1;

        if (vibor2 == 1) { // По убыванию

            while (j >= 0 && note[j].number < key.number) {
                note[j + 1] = note[j];
                j--;
            }
        }
        else { // По возрастанию

            while (j >= 0 && note[j].number > key.number) {
                note[j + 1] = note[j];
                j--;
            }
        }

        note[j + 1] = key;
    }

    return 0;
}

int Sort(Arenda* note, int size) { // для сортировки 

    int vibor, vibor2;

    cout << "Сортировка..." << endl;

    while (true) {

        cout << "Выберите как сортирвоать:" << endl <<
            "1. Быстрая сортировка по длительности." << endl <<
            "2. Сортировка выбором по инвентарному номеру." << endl <<
            "3. Сортировка вставками по цене за час." << endl <<
            "Введите 0 для выхода." << endl;

        while (!(cin >> vibor)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Ошибка! Введите число (0 - 3): ";
        }

        cout << "Как сортировать" << endl <<
            "1. По возрастсанию." << endl <<
            "2. По убыванию. " << endl <<
            "Введите 0 для выхода" << endl;

        while (!(cin >> vibor2)) {
            cin.clear();
            cin.ignore(1000, '\n'); //нормально понять че это - очищает неверный ввод
            cout << "Ошибка! Введите число (1 - 2): ";
        }

        if (vibor == 0) {
            cout << "Программа завершена." << endl;
            return 0;
        }

        if (vibor < 0 || vibor > 3) {
            cout << "Введите номер(0 - 3): ";
            continue;
        }

        switch (vibor) {
        case 1:
            QuickSort(note, size, vibor2);
            Out_Rez(note, size);
            break;
        case 2:
            SelectionSort(note, size, vibor2);
            Out_Rez(note, size);
            break;
        case 3:
            InsertionSort(note, size, vibor2);
            Out_Rez(note, size);
            break;
        }
    }


    return 0;
}

int serchBin(Arenda* note, int size) {// Бинарный поиск по длительности
    //бинанрный поиск когда ищем по половинам

    const int SIZE = 1000;
    int indices[SIZE];
    int index = 0, zndex = 0, cndex = 0;
    char choise, choise2, choise3 = 'y';
    int select;
    int left, right, mid;


    while (choise3 == 'y' || choise3 == 'Y') {
        while (note[index].duration > note[index + 1].duration) {
            cout << "Данные не отсортированы. Отсортировать?(y/n)";
            cin >> choise;

            if (choise == 'y' || choise == 'Y') {

                QuickSort(note, size, choise);

            }
            else {
                cout << "Данные не отсортированы. Хотите выйти(y/n)";
                cin >> choise2;

                if (choise2 == 'y' || choise2 == 'Y') {
                    return 0;
                }
                else {
                    continue;
                }
            }
        }

        cout << "Введите значение длительности: ";
        cin >> select;

        left = 0;
        right = size - 1;
        cndex = 0;
        bool found = false;

        while (left <= right) {

            mid = left + (right - left) / 2;

            if (select == note[mid].duration) {
                found = true;

                int tempMid = mid;
                while (tempMid <= right && note[tempMid].duration == select) {
                    if (cndex < SIZE) {
                        indices[cndex] = tempMid;
                        cndex++;
                    }
                    tempMid++;
                }

                tempMid = mid - 1;
                while (tempMid >= left && note[tempMid].duration == select) {
                    if (cndex < SIZE) {
                        indices[cndex] = tempMid;
                        cndex++;
                    }
                    tempMid--;
                }

                for (int i = 0; i < cndex - 1; i++) {
                    for (int j = 0; j < cndex - i - 1; j++) {
                        if (indices[j] > indices[j + 1]) {
                            int temp = indices[j];
                            indices[j] = indices[j + 1];
                            indices[j + 1] = temp;
                        }
                    }
                }

                for (int i = 0; i < cndex; i++) {

                    int v = indices[i];

                    cout << note[v].name << '\t';
                    cout << note[v].number << '\t';
                    cout << note[v].time << '\t';
                    cout << note[v].duration << '\t';
                    cout << note[v].price << endl;
                }

                break;
            }
            else if (note[mid].duration > select) {
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
    }

    return 0;
}

int serchLin(Arenda* note, int size) { //линейный поиск
    //обычный поик когда проходим просто по всем элементам

    const int MAX_SIZE = 100;
    const int SIZE = 1000;
    char tipe[MAX_SIZE];
    char str[MAX_SIZE];
    int chisl[SIZE];
    char choise = 'y';

    int index = 0, jndex = 0, cndex = 0;

    while (choise == 'y' || choise == 'Y') {

        cout << "Введите тип оборудования: " << endl <<
            "Введите 0 для выхода";
        cin.ignore();
        cin.getline(tipe, MAX_SIZE);

        if (tipe[cndex] == '0') {

            return 0;

        }

        for (int j = 0; j < size; j++) {

            for (int i = 0; i < strlen(note[j].name); i++) {
                str[i] = note[j].name[i];
            }

            str[strlen(note[j].name)] = '\0';


            if (strcmp(str, tipe) == 0) {
                chisl[index] = j;
                index++;
            }
        }

        if (index == 0) {
            cout << "Записи не найдены" << endl;
            return -1;
        }

        cout << "Найдено записей: " << index << endl;

        for (int i = 0; i < index; i++) {

            int v = chisl[i];

            cout << note[v].name << '\t';
            cout << note[v].number << '\t';
            cout << note[v].time << '\t';
            cout << note[v].duration << '\t';
            cout << note[v].price << endl;

        }

        cout << "Хотите продолжить?(y/n)";
        cin >> choise;
    }

    return index;
}

int Search(Arenda* note, int size) {// для поиска

    int chisl;

    while (true) {

        cout << "Выберите как искать:" << endl <<
            "1. Бинарный поиск по длительности." << endl <<
            "2. Линейный поиск по типу." << endl <<
            "Нажмите 0 для выхода.";

        while (!(cin >> chisl)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Ошибка! Введите число (0 - 2): ";
        }

        if (chisl == 0) {
            cout << "Программа завершена." << endl;
            return 0;
        }

        if (chisl < 0 || chisl > 2) {
            cout << "Введите номер(0 - 2): ";
            continue;
        }

        switch (chisl) {
        case 1:
            serchBin(note, size);
            break;
        case 2:

            if (serchLin(note, size) == 0);
            break;
        }
    }

    return 0;
}

int Stat(Arenda* note, int size) {// для статистики
    cout << "Статистика цен на оборудование..." << endl;

    int choise = 2;

    const int SIZE = 100;
    char snowbord[] = "snowbord";
    Arenda arrSnowbord[SIZE];
    int indexSnowbord = 0, jndexSnowbord = 0;
    char ski[] = "ski";
    Arenda arrSki[SIZE];
    int indexSki = 0, jndexSki = 0;
    char skates[] = "skates";
    Arenda arrSkates[SIZE];
    int indexSkates = 0, jndexSkates = 0;
    char cross_countriSkiing[] = "cross-countri skiing";
    Arenda arrCross_countriSkiing[SIZE];
    int indexCross_countriSkiing = 0, jndexCross_countriSkiing = 0;
    char tubing[] = "tubing";
    Arenda arrTubing[SIZE];
    int indexTubing = 0, jndexTubing = 0;
    char setSki[] = "Set of ski";
    Arenda arrSetSki[SIZE];
    int indexSetSki = 0, jndexSetSki = 0;
    char setSnowbord[] = "Set of snowbord";
    Arenda arrSetSnowbord[SIZE];
    int indexSetSnowbord = 0, jndexSetSnowbord = 0;
    char helmet[] = "helmet";
    Arenda arrHelmet[SIZE];
    int indexHelmet = 0, jndexHelmet = 0;
    char skiBoots[] = "ski boots";
    Arenda arrSkiBoots[SIZE];
    int indexSkiBoots = 0, jndexSkiBoots = 0;
    char snowbordBoots[] = "snowbord boots";
    Arenda arrSnowbordBoots[SIZE];
    int indexSnowbordBoots = 0, jndexSnowbordBoots = 0;
    char mask[] = "mask";
    Arenda arrMask[SIZE];
    int indexMask = 0, jndexMask = 0;
    char skiPoles[] = "ski poles";
    Arenda arrSkiPoles[SIZE];
    int indexSkiPoles = 0, jndexSkiPoles = 0;


    for (int i = 0; i < size; i++) {

        if (strcmp(note[i].name, snowbord) == 0) {

            arrSnowbord[indexSnowbord] = note[i];
            indexSnowbord++;

        }
        else {
            if (strcmp(note[i].name, ski) == 0) {
                arrSki[indexSki] = note[i];
                indexSki++;
            }
            if (strcmp(note[i].name, skates) == 0) {
                arrSkates[indexSkates] = note[i];
                indexSkates++;
            }
            if (strcmp(note[i].name, cross_countriSkiing) == 0) {
                arrCross_countriSkiing[indexCross_countriSkiing] = note[i];
                indexCross_countriSkiing++;
            }
            if (strcmp(note[i].name, tubing) == 0) {
                arrTubing[indexTubing] = note[i];
                indexTubing++;
            }
            if (strcmp(note[i].name, setSki) == 0) {
                arrSetSki[indexSetSki] = note[i];
                indexSetSki++;
            }
            if (strcmp(note[i].name, setSnowbord) == 0) {
                arrSetSnowbord[indexSetSnowbord] = note[i];
                indexSetSnowbord++;
            }
            if (strcmp(note[i].name, helmet) == 0) {
                arrHelmet[indexHelmet] = note[i];
                indexHelmet++;
            }
            if (strcmp(note[i].name, skiBoots) == 0) {
                arrSkiBoots[indexSkiBoots] = note[i];
                indexSkiBoots++;
            }
            if (strcmp(note[i].name, snowbordBoots) == 0) {
                arrSnowbordBoots[indexSnowbordBoots] = note[i];
                indexSnowbordBoots++;
            }
            if (strcmp(note[i].name, mask) == 0) {
                arrMask[indexMask] = note[i];
                indexMask++;
            }
            if (strcmp(note[i].name, skiPoles) == 0) {
                arrSkiPoles[indexSkiPoles] = note[i];
                indexSkiPoles++;
            }
        }
    }

    QuickSort(arrSnowbord, indexSnowbord, choise);
    QuickSort(arrSki, indexSki, choise);
    QuickSort(arrSkates, indexSkates, choise);
    QuickSort(arrCross_countriSkiing, indexCross_countriSkiing, choise);
    QuickSort(arrTubing, indexTubing, choise);
    QuickSort(arrSetSki, indexSetSki, choise);
    QuickSort(arrSetSnowbord, indexSetSnowbord, choise);
    QuickSort(arrHelmet, indexHelmet, choise);
    QuickSort(arrSkiBoots, indexSkiBoots, choise);
    QuickSort(arrSnowbordBoots, indexSnowbordBoots, choise);
    QuickSort(arrMask, indexMask, choise);
    QuickSort(arrSkiPoles, indexSkiPoles, choise);

    cout << "Статистика проката сноуборда" << endl << endl;
    Out_Rez(arrSnowbord, indexSnowbord);
    cout << "Статистика проката сноубордических ботинок" << endl << endl;
    Out_Rez(arrSkiBoots, indexSkiBoots);
    cout << "Статистика проката горных лыж" << endl << endl;
    Out_Rez(arrSki, indexSki);
    cout << "Статистика проката лыжных ботинок" << endl << endl;
    Out_Rez(arrSkiBoots, indexSkiBoots);
    cout << "Статистика проката лыжных палок" << endl << endl;
    Out_Rez(arrSkiPoles, indexSkiPoles);
    cout << "Статистика проката коньков" << endl << endl;
    Out_Rez(arrSkates, indexSkates);
    cout << "Статистика проката беговых лыж" << endl << endl;
    Out_Rez(arrCross_countriSkiing, indexCross_countriSkiing);
    cout << "Статистика проката тюбинга" << endl << endl;
    Out_Rez(arrTubing, indexTubing);
    cout << "Статистика проката комплекта горных лыж" << endl << endl;
    Out_Rez(arrSetSki, indexSetSki);
    cout << "Статистика проката комплекта сноуборда" << endl << endl;
    Out_Rez(arrSetSnowbord, indexSetSnowbord);
    cout << "Статистика проката шлемов" << endl << endl;
    Out_Rez(arrHelmet, indexHelmet);
    cout << "Статистика проката горнолыжных масок" << endl << endl;
    Out_Rez(arrMask, indexMask);

    return 0;
}

int main() {
    setlocale(LC_ALL, "rus");

    const int MAX_LINE = 1000;
    const int MAX_FIELDS = 5;
    const int FIELD_SIZE = 100;

    int index = 0;

    char buffer[MAX_LINE];
    Arenda note[1000];

    FILE* file;
    errno_t err = fopen_s(&file, "Prokat.txt", "r");

    if (err == 0 && file != NULL) {
        // чтение первой строки из файла

        while (true) {
            if (fgets(buffer, MAX_LINE, file) != NULL) {
                int len = strlen(buffer);
                if (len > 0 && buffer[len - 1] == '\n') {
                    buffer[len - 1] = '\0';
                }

                // разбитие строки по словам
                char* context = NULL;
                char* token = strtok_s(buffer, "|", &context);

                if (token != NULL) {
                    strcpy_s(note[index].name, sizeof(note[index].name), token);

                    token = strtok_s(context, "|", &context);
                    if (token != NULL) note[index].number = atoi(token);

                    token = strtok_s(context, "|", &context);
                    if (token != NULL) {

                        strcpy_s(note[index].time, sizeof(note[index].time), token);
                    }

                    token = strtok_s(context, "|", &context);
                    if (token != NULL) note[index].duration = atoi(token);

                    token = strtok_s(context, "|", &context);
                    if (token != NULL) note[index].price = atoi(token);
                }

                index++;

            }
            else {
                break;
            }
        }
        fclose(file);
    }

    cout << "СИСТЕМА УЧЕТА ПРОКАТА ГОРНОЛЫЖНОГО ОБОРУДОВАНИЯ" << endl << endl;
    cout << "Для выбора пункта введите его номер" << endl;

    while (true) {
        cout << "\n1. Добавить запись." << endl <<
            "2. Удалить запись." << endl <<
            "3. Отсортировать." << endl <<
            "4. Найти находящееся в прокате оборудование." << endl <<
            "5. Статистика цен на оборудование." << endl <<
            "6. Вывести все на экран." << endl <<
            "Для выхода введите 0." << endl <<
            "Введите номер(0 - 6): ";

        int num;

        while (!(cin >> num)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Ошибка! Введите число (0 - 6): ";
        }

        if (num == 0) {
            cout << "Программа завершена." << endl;
            return 0;
        }

        if (num < 0 || num > 6) {
            cout << "Введите номер(0 - 6): ";
            continue;
        }


        switch (num) {
        case 1:
            NewRecord();
            break;
        case 2:
            Delete();
            break;
        case 3:
            if (Sort(note, index) == 0) {
            }
            break;
        case 4:
            Search(note, index);
            break;
        case 5:
            Stat(note, index);
            break;
        case 6:
            Out_Rez(note, index);
            break;
        }
    }

    return 0;
}