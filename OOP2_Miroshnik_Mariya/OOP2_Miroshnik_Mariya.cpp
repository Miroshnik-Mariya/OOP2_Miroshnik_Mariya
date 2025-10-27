#include <iostream>
#include <fstream>

using namespace std;

const size_t MAX_LINE_LENGTH = 1024;

class Line {
public:
    char* text;
    size_t length;

    // Конструктор
    Line() : text(nullptr), length(0) {}

    // Инициализация строки
    void setLine(const char* str) {
        // Освобождение памяти, если ранее была выделена
        if (text != nullptr) {
            free(text);
        }
        // Выделение памяти под новую строку
        size_t len = strlen(str);
        text = (char*)malloc(len + 1);
        strcpy_s(text, len + 1, str);
        length = len;
    }

    // Деструктор
    ~Line() {
        if (text != nullptr) {
            free(text);
        }
    }
};

class TextFile {
private:
    char* filename;
public:
    // Конструктор
    TextFile(const char* fname) {
        filename = _strdup(fname);
    }

    // Деструктор
    ~TextFile() {
        if (filename != nullptr) {
            free(filename);
        }
    }

   
    void printLinesOfLength(size_t targetLength) {
        ifstream fin(filename);
        if (!fin.is_open()) {
            cerr << "Не удалось открыть файл: " << filename << endl;
            return;
        }

        char buffer[MAX_LINE_LENGTH];

        bool found = false; // Флаг, показывающий, были ли найдены строки нужной длины
        cout << "\nОтвет: \n";
        while (fin.getline(buffer, MAX_LINE_LENGTH)) {
            // Полностью очищаем строку от ненужных символов (например, перенос строки)
            size_t len = strlen(buffer);
            if (len > 0 && buffer[len - 1] == '\n') { // Проверяем наличие символа '\n'
                buffer[len - 1] = '\0';               // Обрезаем строку
                len--;                                // Длина уменьшается на единицу
            }

            
            // Проверяем условие соответствия длины
            if (len == targetLength) {
                cout << "'" << buffer << "'" << endl;
                found = true;
            }
        }

        if (!found) {
            cout << "Строки длиной " << targetLength << " не найдены." << endl;
        }
        fin.close(); // Закрываем поток файла
    }
    /*
    void printLinesOfLength(size_t targetLength) {
        ifstream fin(filename);
        if (!fin.is_open()) {
            cerr << "Не удалось открыть файл: " << filename << endl;
            return;
        }

        char buffer[MAX_LINE_LENGTH];

        bool found = false;

        while (fin.getline(buffer, MAX_LINE_LENGTH)) {
            size_t len = strlen(buffer);
            if (len > 0 && buffer[len - 1] == '\n') {
                buffer[len - 1] = '\0';
                len--;
            }

            cout << "Прочитано: '" << buffer << "', длина строки: " << len << endl;

            if (len == targetLength) {
                cout << "Подходит: '" << buffer << "'" << endl;
                found = true;
            }
        }

        if (!found) {
            cout << "Строки длиной " << targetLength << " не найдены." << endl;
        }

        fin.close();
    }*/
};

int main() {
    //setlocale(LC_ALL, "Russian");
    setlocale(LC_ALL, "");
    setlocale(LC_ALL, ".1251");
    printf("Лабораторная работа №2\nВыполнила студентка группы 6301-020302D\nМирошник Мария Леонидовна\n");

    printf("\nВариант 10\nЗадание:\n\n");
    printf("Написать программу, которая открывает в текстовом режиме произвольный текстовый файл в указанном каталоге, в соответствии с его полным именем, вводимым с клавиатуры.\nДалее программа должна распечатать все строки файла, имеющие длину, которая задается с клавиатуры. Строки выводятся в порядке их следования в файле.\n");

    char filename[256];
    size_t lineLength;

    cout << "Введите полное имя файла: ";
    cin.getline(filename, sizeof(filename));

    cout << "Введите длину строк для вывода: ";
    cin >> lineLength;

    // Очищаем буфер после ввода числа
    cin.ignore();

    // Создаем объект класса TextFile и открываем указанный файл
    TextFile tf(filename);
    tf.printLinesOfLength(lineLength);
    return 0;
}