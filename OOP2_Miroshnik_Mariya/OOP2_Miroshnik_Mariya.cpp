#include <iostream>
#include <fstream>

using namespace std;

const size_t MAX_LINE_LENGTH = 256;



class TextFile {
private:
    char* filename; //файл - указатель на первый символ строки
public:
    //Создание файла — конструктор с параметром
    TextFile(const char* fname) {
        filename = _strdup(fname);
    }

    //Аннулирование файла — деструктор
    ~TextFile() {
        if (filename != nullptr) {
            free(filename);
        }
    }

    // Конструктор копирования (глубокое копирование)
    TextFile(const TextFile& other) {
        if (other.filename != nullptr) {
            filename = _strdup(other.filename);
        }
        else {
            filename = nullptr;
        }
    }

    // Оператор присваивания (глубокое копирование)
    TextFile& operator=(const TextFile& other) {
        if (this != &other) { // Защита от самоприсваивания
            // Освобождаем старые ресурсы
            if (filename != nullptr) {
                free(filename);
            }

            // Копируем новые ресурсы
            if (other.filename != nullptr) {
                filename = _strdup(other.filename);
            }
            else {
                filename = nullptr;
            }
        }
        return *this;
    }

    //Отбор строк заданной длины — метод с параметром длина строки
    void printLinesOfLength(size_t targetLength) {
        FILE* file = nullptr;
        errno_t err = fopen_s(&file, filename, "r");
        if (err != 0 || file == nullptr) {
            fprintf(stderr, "Не удалось открыть файл: %s\n", filename);
            return;
        }

        char buffer[MAX_LINE_LENGTH];
        bool found = false; 

        printf("\nОтвет: \n");

        while (fgets(buffer, MAX_LINE_LENGTH, file) != NULL) {
            // Удаляем символ новой строки, если он присутствует
            size_t len = strlen(buffer);
            if (len > 0 && buffer[len - 1] == '\n') {
                buffer[len - 1] = '\0'; 
                len--; 
            }
            if (len > 0 && buffer[len - 1] == '\r') {
                buffer[len - 1] = '\0'; // Удаляем символ возврата каретки
                len--; 
            }

            // Проверяем условие соответствия длины
            if (len == targetLength) {
                printf("'%s'\n", buffer);
                found = true;
            }
        }

        if (!found) {
            printf("Строки длиной %zu не найдены.\n", targetLength);
        }
        fclose(file); // Закрываем файл
    }
};

class Line {
public:
    char* text; //Символьная строка 
    size_t length; //Длина строки

    // Конструктор по умолчанию (ОБЯЗАТЕЛЬНО!)
    Line() : text(nullptr), length(0) {} 

    //Инициализация строки — метод с параметром массивом символов
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
    // Конструктор копирования (глубокое копирование)
    Line(const Line& other) : text(nullptr), length(0) {
        if (other.text != nullptr) {
            length = other.length;
            text = (char*)malloc(length + 1);
            if (text != nullptr) {
                strcpy_s(text, length + 1, other.text);
            }
        }
    }

    // Оператор присваивания (глубокое копирование)
    Line& operator=(const Line& other) {
        if (this != &other) { // Защита от самоприсваивания
            // Освобождаем старые ресурсы
            if (text != nullptr) {
                free(text);
                text = nullptr;
            }

            // Копируем новые ресурсы
            if (other.text != nullptr) {
                length = other.length;
                text = (char*)malloc(length + 1);
                if (text != nullptr) {
                    strcpy_s(text, length + 1, other.text);
                }
            }
            else {
                length = 0;
                text = nullptr;
            }
        }
        return *this;
    }


    //Аннулирование строки — деструктор
    ~Line() {
        if (text != nullptr) {
            free(text);
        }
    }
};
int main() {
    setlocale(LC_ALL, "");
    setlocale(LC_ALL, ".1251");
    cout << "Лабораторная работа №2\nВыполнила студентка группы 6301-020302D\nМирошник Мария Леонидовна\n" << endl;

    cout << "Вариант 10\nЗадание:\n\n" << endl;
    cout << "Написать программу, которая открывает в текстовом режиме произвольный текстовый файл в указанном каталоге, в соответствии с его полным именем, вводимым с клавиатуры.\nДалее программа должна распечатать все строки файла, имеющие длину, которая задается с клавиатуры. Строки выводятся в порядке их следования в файле." << endl;

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