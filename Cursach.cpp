#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <cctype>
#include <regex>
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <locale>


const int MAX_STUDENTS = 20;
const int MAX_CREDITS = 10;
const int MAX_EXAMS = 5;

struct Date {
    int day;
    int month;
    int year;
};

struct Student {
    std::string lastName;
    std::string firstName;
    std::string middleName;
    Date birthDate;
    int creditCount;
    Date credits[MAX_CREDITS];
    int examCount;
    struct Exam {
        Date date;
        int score;
    } exams[MAX_EXAMS];
};

bool isValidName(const std::string& name) {
    std::regex regex("[A-Z][a-z]+");
    return std::regex_match(name, regex);
}

bool isValidDate(const Date& date) {
    if (date.day < 1 || date.day > 31 || date.month < 1 || date.month > 12 || date.year < 1900 || date.year > 2023) {
        return false;
    }
    return true;
}

bool isValidScore(int score) {
    return score >= 2 && score <= 5;
}

void addStudent(Student* students[], int& count) {
    if (count >= MAX_STUDENTS) {
        std::cout << "Ошибка: достигнуто максимальное количество студентов в группе." << std::endl;
        return;
    }

    Student* student = new Student;

    std::cout << "Введите фамилию студента: ";
    std::cin >> student->lastName;

    if (!isValidName(student->lastName)) {
        std::cout << "Ошибка: недопустимое значение фамилии." << std::endl;
        delete student;
        return;
    }

    std::cout << "Введите имя студента: ";
    std::cin >> student->firstName;

    if (!isValidName(student->firstName)) {
        std::cout << "Ошибка: недопустимое значение имени." << std::endl;
        delete student;
        return;
    }

    std::cout << "Введите отчество студента (если отчества нет, введите '-'): ";
    std::cin >> student->middleName;

    if (student->middleName != "-" && !isValidName(student->middleName)) {
        std::cout << "Ошибка: недопустимое значение отчества." << std::endl;
        delete student;
        return;
    }

    std::cout << "Введите дату рождения студента (день месяц год): ";

    if (!(std::cin >> student->birthDate.day >> student->birthDate.month >> student->birthDate.year)) {
        // Очистить состояние потока ввода и проигнорировать некорректный ввод
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Ошибка: недопустимая дата рождения." << std::endl;
        return;
    }

    if (!isValidDate(student->birthDate)) {
        std::cout << "Ошибка: недопустимая дата рождения." << std::endl;
        delete student;
        return;
    }

    std::cout << "Введите количество сданных зачетов (максимум " << MAX_CREDITS << "): ";
    if (!(std::cin >> student->creditCount)) {
        // Очистить состояние потока ввода и проигнорировать некорректный ввод
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Ошибка: недопустимое количество сданных зачетов." << std::endl;
        return;
    }

    if (student->creditCount < 0 || student->creditCount > MAX_CREDITS) {
        std::cout << "Ошибка: недопустимое количество сданных зачетов." << std::endl;
        delete student;
        return;
    }

    for (int i = 0; i < student->creditCount; i++) {
        std::cout << "Введите дату сдачи зачета " << i + 1 << " (день месяц год): ";
        if (!(std::cin >> student->credits[i].day >> student->credits[i].month >> student->credits[i].year)) {
            // Очистить состояние потока ввода и проигнорировать некорректный ввод
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка: недопустимая дата сдачи зачета." << std::endl;
            return;
        }

        if (!isValidDate(student->credits[i])) {
            std::cout << "Ошибка: недопустимая дата сдачи зачета." << std::endl;
            delete student;
            return;
        }
    }

    std::cout << "Введите количество экзаменационных оценок (максимум " << MAX_EXAMS << "): ";
    if (!(std::cin >> student->examCount)) {
        // Очистить состояние потока ввода и проигнорировать некорректный ввод
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Ошибка: недопустимое количество экзаменационных оценок." << std::endl;
        return;
    }

    if (student->examCount < 0 || student->examCount > MAX_EXAMS) {
        std::cout << "Ошибка: недопустимое количество экзаменационных оценок." << std::endl;
        delete student;
        return;
    }

    for (int i = 0; i < student->examCount; i++) {
        std::cout << "Введите дату сдачи экзамена " << i + 1 << " (день месяц год): ";
        if (!(std::cin >> student->exams[i].date.day >> student->exams[i].date.month >> student->exams[i].date.year)) {
            // Очистить состояние потока ввода и проигнорировать некорректный ввод
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка: недопустимая дата сдачи экзамена." << std::endl;
            return;
        }

        if (!isValidDate(student->exams[i].date)) {
            std::cout << "Ошибка: недопустимая дата сдачи экзамена." << std::endl;
            delete student;
            return;
        }

        std::cout << "Введите оценку за экзамен " << i + 1 << ": ";
        if (!(std::cin >> student->exams[i].score)) {
            // Очистить состояние потока ввода и проигнорировать некорректный ввод
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка: недопустимая оценка за экзамен." << std::endl;
            return;
        }

        if (!isValidScore(student->exams[i].score)) {
            std::cout << "Ошибка: недопустимая оценка за экзамен." << std::endl;
            delete student;
            return;
        }
    }

    students[count] = student;
    count++;

    std::cout << "Студент успешно добавлен." << std::endl;
}

void printStudents(Student* students[], int count) {

    if (count == 0) {
        std::cout << "В базе данных нет студентов." << std::endl;
        return;
    }

    std::cout << std::endl;

    for (int i = 0; i < count; i++) {
        const Student* student = students[i];

        std::cout << "Студент " << i + 1 << ":" << std::endl;
        std::cout << "Фамилия: " << student->lastName << std::endl;
        std::cout << "Имя: " << student->firstName << std::endl;
        std::cout << "Отчество: " << student->middleName << std::endl;
        std::cout << "Дата рождения: " << student->birthDate.day << "." << student->birthDate.month << "." << student->birthDate.year << std::endl;
        std::cout << "Сданные зачеты: " << std::endl;
        for (int j = 0; j < student->creditCount; j++) {
            std::cout << "Зачет " << j + 1 << ": " << student->credits[j].day << "." << student->credits[j].month << "." << student->credits[j].year << std::endl;
        }
        std::cout << "Экзамены: " << std::endl;
        for (int j = 0; j < student->examCount; j++) {
            std::cout << "Экзамен " << j + 1 << ": " << student->exams[j].date.day << "." << student->exams[j].date.month << "." << student->exams[j].date.year << ", Оценка: " << student->exams[j].score << std::endl;
        }
        std::cout << std::endl;
    }
}

void saveDatabaseToFile(Student* students[], int count, const std::string& filename) {

    std::ofstream file(filename);

    if (!file) {
        std::cout << "Ошибка: Не удалось открыть файл для записи. Был создан новый файл." << std::endl;
        return;
    }

    file << count << std::endl;

    for (int i = 0; i < count; i++) {
        const Student* student = students[i];

        file << student->lastName << std::endl;
        file << student->firstName << std::endl;
        file << student->middleName << std::endl;
        file << student->birthDate.day << " " << student->birthDate.month << " " << student->birthDate.year << std::endl;
        file << student->creditCount << std::endl;

        for (int j = 0; j < student->creditCount; j++) {
            file << student->credits[j].day << " " << student->credits[j].month << " " << student->credits[j].year << std::endl;
        }

        file << student->examCount << std::endl;

        for (int j = 0; j < student->examCount; j++) {
            file << student->exams[j].date.day << " " << student->exams[j].date.month << " " << student->exams[j].date.year << " " << student->exams[j].score << std::endl;
        }
    }

    file.close();
    if (!file) {
        std::cout << "Ошибка: не удалось закрыть файл после записи." << std::endl;
        return;
    }

    std::cout << "База данных успешно сохранена в файле." << std::endl;
}

void loadStudents(Student* students[], int& count, const std::string& filename) {

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Ошибка: не удалось открыть файл для чтения." << std::endl;
        return;
    }

    int loadedCount;
    file >> loadedCount;
    file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (loadedCount > MAX_STUDENTS) {
        std::cout << "Ошибка: количество студентов в файле превышает максимально допустимое значение." << std::endl;
        file.close();
        return;
    }

    for (int i = 0; i < loadedCount; i++) {
        if (count >= MAX_STUDENTS) {
            std::cout << "Предупреждение: количество студентов в файле превышает максимально допустимое значение. Загружены первые " << MAX_STUDENTS << " студентов." << std::endl;
            break;
        }

        Student* student = new Student;

        std::getline(file, student->lastName);
        std::getline(file, student->firstName);
        std::getline(file, student->middleName);
        file >> student->birthDate.day >> student->birthDate.month >> student->birthDate.year;
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        file >> student->creditCount;
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        for (int j = 0; j < student->creditCount; j++) {
            file >> student->credits[j].day >> student->credits[j].month >> student->credits[j].year;
            file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        file >> student->examCount;
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        for (int j = 0; j < student->examCount; j++) {
            file >> student->exams[j].date.day >> student->exams[j].date.month >> student->exams[j].date.year >> student->exams[j].score;
            file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        students[count] = student;
        count++;
    }

    file.close();

    std::cout << "Данные успешно загружены из файла." << std::endl;
}


void deleteStudent(Student* students[], int& count) {
    if (count == 0) {
        std::cout << "В базе данных нет студентов." << std::endl;
        return;
    }

    std::cout << "Введите номер студента для удаления: ";
    int index;
    if (!(std::cin >> index)) {
        // Очистить состояние потока ввода и проигнорировать некорректный ввод
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Ошибка: неверный номер студента." << std::endl;
        return;
    }

    if (index < 1 || index > count) {
        std::cout << "Ошибка: неверный номер студента." << std::endl;
        return;
    }

    index--;

    delete students[index];

    for (int i = index; i < count - 1; i++) {
        students[i] = students[i + 1];
    }

    count--;

    std::cout << "Студент успешно удален." << std::endl;
}

void modifyStudent(Student* students[], int count) {
    if (count == 0) {
        std::cout << "В базе данных нет студентов." << std::endl;
        return;
    }

    std::cout << "Введите номер студента для изменения: ";
    int index;
    if (!(std::cin >> index)) {
        // Очистить состояние потока ввода и проигнорировать некорректный ввод
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Ошибка: неверный номер студента." << std::endl;
        return;
    }

    if (index < 1 || index > count) {
        std::cout << "Ошибка: неверный номер студента." << std::endl;
        return;
    }

    index--;

    Student* student = students[index];

    Student tempStudent = *student;

    std::cout << "Введите фамилию студента: ";
    std::cin >> tempStudent.lastName;

    if (!isValidName(tempStudent.lastName)) {
        std::cout << "Ошибка: недопустимое значение фамилии. Изменения не приняты." << std::endl;
        return;
    }

    std::cout << "Введите имя студента: ";
    std::cin >> tempStudent.firstName;

    if (!isValidName(tempStudent.firstName)) {
        std::cout << "Ошибка: недопустимое значение имени. Изменения не приняты." << std::endl;
        return;
    }

    std::cout << "Введите отчество студента (если отчества нет, введите '-'): ";
    std::cin >> tempStudent.middleName;

    if (tempStudent.middleName != "-" && !isValidName(tempStudent.middleName)) {
        std::cout << "Ошибка: недопустимое значение отчества. Изменения не приняты." << std::endl;
        return;
    }

    std::cout << "Введите дату рождения студента (день месяц год): ";
    if (!(std::cin >> tempStudent.birthDate.day >> tempStudent.birthDate.month >> tempStudent.birthDate.year)) {
        // Очистить состояние потока ввода и проигнорировать некорректный ввод
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Ошибка: недопустимая дата рождения. Изменения не приняты." << std::endl;
        return;
    }

    if (!isValidDate(tempStudent.birthDate)) {
        std::cout << "Ошибка: недопустимая дата рождения. Изменения не приняты." << std::endl;
        return;
    }

    bool isValid = true;

    std::cout << "Введите количество сданных зачетов (максимум " << MAX_CREDITS << "): ";
    if (!(std::cin >> tempStudent.creditCount)) {
        // Очистить состояние потока ввода и проигнорировать некорректный ввод
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Ошибка: недопустимое количество сданных зачетов. Изменения не приняты." << std::endl;
        return;
    }

    if (tempStudent.creditCount < 0 || tempStudent.creditCount > MAX_CREDITS) {
        std::cout << "Ошибка: недопустимое количество сданных зачетов. Изменения не приняты." << std::endl;
        return;
    }

    for (int i = 0; i < tempStudent.creditCount; i++) {
        std::cout << "Введите дату сдачи зачета " << i + 1 << " (день месяц год): ";
        if (!(std::cin >> tempStudent.credits[i].day >> tempStudent.credits[i].month >> tempStudent.credits[i].year)) {
            // Очистить состояние потока ввода и проигнорировать некорректный ввод
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка: недопустимая дата сдачи зачета. Изменения не приняты." << std::endl;
            return;
        }

        if (!isValidDate(tempStudent.credits[i])) {
            isValid = false;
            std::cout << "Ошибка: недопустимая дата сдачи зачета. Изменения не приняты." << std::endl;
            break;
        }
    }

    if (!isValid) {
        return;
    }

    isValid = true;

    std::cout << "Введите количество экзаменационных оценок (максимум " << MAX_EXAMS << "): ";
    if (!(std::cin >> tempStudent.examCount)) {
        // Очистить состояние потока ввода и проигнорировать некорректный ввод
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Ошибка: недопустимое количество экзаменационных оценок. Изменения не приняты." << std::endl;
        return;
    }

    if (tempStudent.examCount < 0 || tempStudent.examCount > MAX_EXAMS) {
        std::cout << "Ошибка: недопустимое количество экзаменационных оценок. Изменения не приняты." << std::endl;
        return;
    }

    for (int i = 0; i < tempStudent.examCount; i++) {
        std::cout << "Введите дату сдачи экзамена " << i + 1 << " (день месяц год): ";
        if (!(std::cin >> tempStudent.exams[i].date.day >> tempStudent.exams[i].date.month >> tempStudent.exams[i].date.year)) {
            // Очистить состояние потока ввода и проигнорировать некорректный ввод
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка: недопустимая дата сдачи экзамена. Изменения не приняты." << std::endl;
            return;
        }

        if (!isValidDate(tempStudent.exams[i].date)) {
            isValid = false;
            std::cout << "Ошибка: недопустимая дата сдачи экзамена. Изменения не приняты." << std::endl;
            break;
        }

        std::cout << "Введите оценку за экзамен " << i + 1 << ": ";
        if (!(std::cin >> tempStudent.exams[i].score)) {
            // Очистить состояние потока ввода и проигнорировать некорректный ввод
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка: недопустимая оценка за экзамен. Изменения не приняты." << std::endl;
            return;
        }

        if (!isValidScore(tempStudent.exams[i].score)) {
            isValid = false;
            std::cout << "Ошибка: недопустимая оценка за экзамен. Изменения не приняты." << std::endl;
            break;
        }
    }

    if (!isValid) {
        return;
    }

    // Создание динамической копии объекта tempStudent
    Student* modifiedStudent = new Student(tempStudent);

    // Освобождение ресурсов, занятых предыдущим объектом Student в массиве students[]
    delete students[index];

    // Присвоение новой копии объекта tempStudent в массив students[]
    students[index] = modifiedStudent;

    std::cout << "Информация о студенте успешно изменена." << std::endl;
}

void searchStudent(Student* students[], int count) {
    if (count == 0) {
        std::cout << "В базе данных нет студентов." << std::endl;
        return;
    }

    std::string searchLastName;
    std::string searchFirstName;
    std::string searchMiddleName;

    std::cout << "Введите фамилию студента для поиска: ";
    std::cin >> searchLastName;

    if (!isValidName(searchLastName)) {
        std::cout << "Ошибка: недопустимое значение фамилии." << std::endl;
        return;
    }

    std::cout << "Введите имя студента для поиска: ";
    std::cin >> searchFirstName;

    if (!isValidName(searchFirstName)) {
        std::cout << "Ошибка: недопустимое значение имени." << std::endl;
        return;
    }

    std::cout << "Введите отчество студента для поиска (если отчества нет, введите '-'): ";
    std::cin >> searchMiddleName;

    if (searchMiddleName != "-" && !isValidName(searchMiddleName)) {
        std::cout << "Ошибка: недопустимое значение отчества." << std::endl;
        return;
    }

    bool found = false;

    for (int i = 0; i < count; i++) {
        const Student* student = students[i];

        if (student->lastName == searchLastName && student->firstName == searchFirstName &&
            (student->middleName == searchMiddleName || (student->middleName == "-" && searchMiddleName.empty()))) {
            std::cout << std::endl;
            std::cout << "Студент найден:" << std::endl;
            std::cout << std::endl;
            std::cout << "Фамилия: " << student->lastName << std::endl;
            std::cout << "Имя: " << student->firstName << std::endl;
            std::cout << "Отчество: " << student->middleName << std::endl;
            std::cout << "Дата рождения: " << student->birthDate.day << "." << student->birthDate.month << "." << student->birthDate.year << std::endl;
            std::cout << "Сданные зачеты: " << std::endl;
            for (int j = 0; j < student->creditCount; j++) {
                std::cout << "Зачет " << j + 1 << ": " << student->credits[j].day << "." << student->credits[j].month << "." << student->credits[j].year << std::endl;
            }
            std::cout << "Экзамены: " << std::endl;
            for (int j = 0; j < student->examCount; j++) {
                std::cout << "Экзамен " << j + 1 << ": " << student->exams[j].date.day << "." << student->exams[j].date.month << "." << student->exams[j].date.year << ", Оценка: " << student->exams[j].score << std::endl;
            }
            std::cout << std::endl;

            found = true;
        }
    }

    if (!found) {
        std::cout << "Студент не найден." << std::endl;
    }
}

void searchStudentsByAge(Student* students[], int count) {

    std::cout << "Введите возраст: ";
    int age;
    if (!(std::cin >> age)) {
        // Очистить состояние потока ввода и проигнорировать некорректный ввод
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Ошибка: недопустимое значение возраста." << std::endl;
        return;
    }

    if (age < 12) {
        std::cout << "Ошибка: недопустимое значение возраста." << std::endl;
        return;
    }

    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    std::tm now_tm;
    localtime_s(&now_tm, &now_c);
    int currentYear = now_tm.tm_year + 1900;

    std::cout << std::endl;
    std::cout << "Результаты поиска:" << std::endl;
    std::cout << std::endl;

    bool found = false;

    for (int i = 0; i < count; i++) {
        const Student* student = students[i];

        int studentAge = currentYear - student->birthDate.year;

        if (student->birthDate.month > now_tm.tm_mon + 1 || (student->birthDate.month == now_tm.tm_mon + 1 && student->birthDate.day > now_tm.tm_mday)) {
            studentAge--;
        }

        if (studentAge == age) {
            std::cout << "Студент найден:" << std::endl;
            std::cout << "Фамилия: " << student->lastName << std::endl;
            std::cout << "Имя: " << student->firstName << std::endl;
            std::cout << "Отчество: " << student->middleName << std::endl;
            std::cout << "Дата рождения: " << student->birthDate.day << "." << student->birthDate.month << "." << student->birthDate.year << std::endl;
            std::cout << "Сданные зачеты: " << std::endl;
            for (int j = 0; j < student->creditCount; j++) {
                std::cout << "Зачет " << j + 1 << ": " << student->credits[j].day << "." << student->credits[j].month << "." << student->credits[j].year << std::endl;
            }
            std::cout << "Экзамены: " << std::endl;
            for (int j = 0; j < student->examCount; j++) {
                std::cout << "Экзамен " << j + 1 << ": " << student->exams[j].date.day << "." << student->exams[j].date.month << "." << student->exams[j].date.year << ", Оценка: " << student->exams[j].score << std::endl;
            }
            std::cout << std::endl;

            found = true;
        }
    }

    if (!found) {
        std::cout << "Студент(ы) не найден(ы)." << std::endl;
    }
}

void saveDatabaseToFileForPrint(Student* students[], int count) {

    std::ofstream file("print.txt");

    if (!file) {
        return;
    }

    for (int i = 0; i < count; i++) {
        const Student* student = students[i];

        file << "Номер студента: " << i + 1 << std::endl;
        file << "Фамилия: " << student->lastName << std::endl;
        file << "Имя: " << student->firstName << std::endl;
        file << "Отчество: " << student->middleName << std::endl;
        file << "Дата рождения: " << student->birthDate.day << "." << student->birthDate.month << "." << student->birthDate.year << std::endl;
        file << "Сданные зачеты: " << std::endl;
        for (int j = 0; j < student->creditCount; j++) {
            file << "Зачет " << j + 1 << ": " << student->credits[j].day << "." << student->credits[j].month << "." << student->credits[j].year << std::endl;
        }
        file << "Экзамены: " << std::endl;
        for (int j = 0; j < student->examCount; j++) {
            file << "Экзамен " << j + 1 << ": " << student->exams[j].date.day << "." << student->exams[j].date.month << "." << student->exams[j].date.year << ", Оценка: " << student->exams[j].score << std::endl;
        }
        file << std::endl;
    }

    file.close();
}

void printFile(const std::string& filename) {
    std::string command = "print /D:\\\"Printer Name\\\" \"" + filename + "\"";
    system(command.c_str());
}

void PrintDatabase(Student* students[], int count, const std::string& filename) {

    saveDatabaseToFileForPrint(students, count);

    std::ifstream file("print.txt");
    if (!file.is_open()) {
        std::cout << "Ошибка: не удалось открыть файл для чтения." << std::endl;
        return;
    }

    std::string line;
    std::cout << std::endl;
    std::cout << "Содержимое БД:" << std::endl;
    std::cout << std::endl;
    while (std::getline(file, line)) {
        std::cout << line << std::endl;
    }

    file.close();

    std::cout << "Вы хотите распечатать файл на принтере? (y/n): ";
    std::string answer;
    std::cin >> answer;
    if (answer == "y" || answer == "Y") {
        printFile(filename);
    }
}

int main() {
    std::setlocale(LC_ALL, "en_US.UTF-8");
    Student* students[MAX_STUDENTS];
    int studentCount = 0;
    bool xxx = true;

    std::string filename;
    std::cout << "Введите название файла с БД: ";
    std::cin >> filename;
    filename.append(".txt");

    loadStudents(students, studentCount, filename);

    int choice;
    do {
        std::cout << "---------------------------" << std::endl;
        std::cout << "1. Добавить студента" << std::endl;
        std::cout << "2. Вывести список студентов" << std::endl;
        std::cout << "3. Сохранить базу данных в файл" << std::endl;
        std::cout << "4. Удалить студента" << std::endl;
        std::cout << "5. Изменить информацию о студенте" << std::endl;
        std::cout << "6. Поиск студента по ФИО" << std::endl;
        std::cout << "7. Поиск студентов, которым исполнилось N лет" << std::endl;
        std::cout << "8. Распечатать БД" << std::endl;
        std::cout << "9. Выход" << std::endl;
        std::cout << "---------------------------" << std::endl;
        std::cout << "Выберите действие: ";

        if (!(std::cin >> choice)) {
            // Очистить состояние потока ввода и проигнорировать некорректный ввод
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка ввода. Пожалуйста, введите число." << std::endl;
            continue;
        }

        switch (choice) {
        case 1:
            addStudent(students, studentCount);
            break;
        case 2:
            printStudents(students, studentCount);
            break;
        case 3:
            saveDatabaseToFile(students, studentCount, filename);
            break;
        case 4:
            deleteStudent(students, studentCount);
            break;
        case 5:
            modifyStudent(students, studentCount);
            break;
        case 6:
            searchStudent(students, studentCount);
            break;
        case 7:
            searchStudentsByAge(students, studentCount);
            break;
        case 8:
            PrintDatabase(students, studentCount, filename);
            break;
        case 9:
            std::cout << "До свидания!" << std::endl;
            xxx = false;
            break;
        default:
            std::cout << "Неверный выбор. Пожалуйста, выберите действие из списка." << std::endl;
            break;
        }
    } while (xxx == true);
}
