#include "Header.h"

bool Time::IsLeapYear(uint64_t year) {
    return (year % 4 == 0) && (year % 100 != 0 || year % 400 == 0);
}
Time::Time() :year(0), month(0), day(0), hour(0), minute(0), second(0), isLeap(IsLeapYear(year)) {};
Time::Time(uint64_t year, uint64_t month, uint64_t day, uint64_t hour, uint64_t minute, uint64_t second) :
    year(year), month(month), day(day), hour(hour), minute(minute), second(second), isLeap(IsLeapYear(year)) {};

Time::Time(const Time& t) :
    year(t.year), month(t.month), day(t.day), hour(t.hour), minute(t.minute), second(t.second), isLeap(t.isLeap) {}

uint64_t Time::GetYear() const {
    return year;
}
uint64_t Time::GetMonth() const {
    return month;
}
uint64_t Time::GetDay() const {
    return day;
}
uint64_t Time::GetHour() const {
    return hour;
}
uint64_t Time::GetMinute() const {
    return minute;
}
uint64_t Time::GetSecond() const {
    return second;
}

void Time::SetUnixtime(uint64_t unixtime) {
    second = unixtime % seconds_in_minute;
    unixtime /= seconds_in_minute; // количество минут с 1970 года

    minute = unixtime % minutes_in_hour;
    unixtime /= minutes_in_hour; // количество часов с 1970 года

    hour = unixtime % hours_in_day;
    unixtime /= hours_in_day; // количество суток с 1970 года

    // Определяем год, месяц, число по пройденным суткам

    year = 1970;
    isLeap = IsLeapYear(year);
    while (true) {
        const uint64_t days_in_current_year = isLeap ? 366 : 365;

        if (unixtime >= days_in_current_year) {
            year++;
            isLeap = IsLeapYear(year);
            unixtime -= days_in_current_year;
        }
        else {
            break;
        }
    }
    // Заданный год хранится в year

    // Узнаем месяц
    month = 1;
    while (true) {
        const uint64_t days_in_current_month = DaysInCurrentMonth();

        if (unixtime >= days_in_current_month) {
            month++;
            unixtime -= days_in_current_month;
        }
        else {
            break;
        }
    }
    day = unixtime + 1;

}

uint64_t Time::GetUnixTime() const {
    if (year < 1970) {
        return 0;
    }

    uint64_t daysCounter = 0;

    for (int j = 1970; j < year; ++j) {
        if (IsLeapYear(j)) {
            daysCounter += 366;
        }
        else {
            daysCounter += 365;
        }
    }
    for (int j = 1; j < month; ++j) {
        // Считаем количество суток в текущем календарном году
        daysCounter += GetDaysInMonth(j, isLeap);
    }
    daysCounter += day - 1;

    return ((daysCounter * hours_in_day + hour) * minutes_in_hour + minute) * seconds_in_minute + second;
}

void Time::SetFiletime(uint64_t filetime) {

    filetime /= 10000000; // Отбрасываем часть с сотнями наносекунд до секунд

    second = filetime % seconds_in_minute;
    filetime /= seconds_in_minute; // количество минут с 1601 года

    minute = filetime % minutes_in_hour;
    filetime /= minutes_in_hour; // количество часов с 1601 года

    hour = filetime % hours_in_day;
    filetime /= hours_in_day; // количество суток с 1601 года

    // Определяем год, месяц, число по пройденным суткам

    year = 1601;
    isLeap = IsLeapYear(year);
    while (true) {
        const uint64_t days_in_current_year = isLeap ? 366 : 365;

        if (filetime >= days_in_current_year) {
            year++;
            isLeap = IsLeapYear(year);
            filetime -= days_in_current_year;
        }
        else {
            break;
        }
    }
    // Заданный год хранится в year

    // Узнаем месяц
    month = 1;
    while (true) {
        const uint64_t days_in_current_month = DaysInCurrentMonth();

        if (filetime >= days_in_current_month) {
            month++;
            filetime -= days_in_current_month;
        }
        else {
            break;
        }
    }
    day = filetime + 1;
}

uint64_t Time::GetFileTime() {
    if (year < 1601) {
        return 0;
    }

    uint64_t daysCounter = 0;

    for (int j = 1601; j < year; ++j) {
        if (IsLeapYear(j)) {
            daysCounter += 366;
        }
        else {
            daysCounter += 365;
        }
    }
    for (int j = 1; j < month; ++j) {
        // Считаем количество суток в текущем календарном году
        daysCounter += GetDaysInMonth(j, isLeap);
    }
    daysCounter += day - 1;

    return (((daysCounter * hours_in_day + hour) * minutes_in_hour + minute) * seconds_in_minute + second) * 10000000;
}

uint64_t Time::GetDaysInMonth(uint64_t month, bool isLeapYear) {
    if (month == 2) {
        if (isLeapYear)
            return 29;
        else {
            return 28;
        }
    }

    // Если не февраль
    if (month < 8) {
        if (month % 2 == 0)
            return 30;
        else
            return 31;
    }
    else {
        if (month % 2 == 0)
            return 31;
        else
            return 30;
    }
}

uint64_t Time::DaysInCurrentMonth() const {
    if (month == 2) {
        if (isLeap)
            return 29;
        else {
            return 28;
        }
    }

    // Если не февраль
    if (month < 8) {
        if (month % 2 == 0)
            return 30;
        else
            return 31;
    }
    else {
        if (month % 2 == 0)
            return 31;
        else
            return 30;
    }
}

Time& Time::operator=(const Time& t) {
    year = t.year;
    month = t.month;
    day = t.day;
    hour = t.hour;
    minute = t.minute;
    second = t.second;
    isLeap = t.isLeap;
    return *this;
}

int64_t Time::operator-(const Time& t) {
    return GetUnixTime() - t.GetUnixTime();
}

Time Time::operator+(const Time& t) {
    Time newTime;
    newTime.SetUnixtime(GetUnixTime() + t.GetUnixTime());
    return newTime;
}

Time::~Time() {

}

istream& operator>>(istream& in, Time& t) {
    in >> t.year >> t.month >> t.day >> t.hour >> t.minute >> t.second;
    t.isLeap = t.IsLeapYear(t.year);
    return in;
}

ostream& operator<<(ostream& out, const Time& t) {
    return out << "Date: " << t.GetDay() << "." << t.GetMonth() << "." << t.GetYear() << endl
        << "Time: " << t.GetHour() << ":" << t.GetMinute() << ":" << t.GetSecond();
}

// Статические константы класса Time
const uint64_t Time::seconds_in_minute = 60;
const uint64_t Time::minutes_in_hour = 60;
const uint64_t Time::hours_in_day = 24;



// Task 4
Element::Element(int row, int col, double value) :row(row), col(col), value(value) {}
Element::Element() : row(0), col(0), value(0) {}

bool Element::operator<(const Element& b) const {
    return row < b.row || row == b.row && col < b.col;
}

// Перегрузка оператора ввода Element
istream& operator>>(istream& in, Element& el) {
    return in >> el.row >> el.col >> el.value;
}
ostream& operator<<(ostream& out, const Element& el) {
    return out << '(' << el.row << ',' << el.col << ',' << el.value << ')';
}

SparseMatrix::SparseMatrix():sorted(false) {}

SparseMatrix::SparseMatrix(const SparseMatrix& mat) {
    data=mat.data;
    sorted = mat.sorted;
}

// Метод для сортировки и удаления дублирующих элементов (с одинаковыми индексами)
void SparseMatrix::sortAndRemoveDuplicates() {
    if (sorted) return;
    sorted = true;

    if (data.size() <= 1) return;

    // Отсортировали массив по возрастанию строк.
    // При совпадающих строках сортировка по возрастанию столбцов
    sort(data.begin(), data.end());

    // Удаляем дубликаты

    size_t indexForWrite = 0;  // Индекс для записи
    size_t indexStart = 0;  // Индекс первого элемента с расматриваемой строкой и столбцом
    size_t currentIndex = 1; // Текущий правый индекс

    for (; currentIndex < data.size(); currentIndex++) {
        if (data[indexStart].row == data[currentIndex].row &&
            data[indexStart].col == data[currentIndex].col) {
            // Индексы соседних элементов равны. Идём дальше
            continue;
        }

        // Если значение записываемого элемента равно нулю, то он игнорируется
        if (data[currentIndex - 1].value != 0) {
            data[indexForWrite++] = data[currentIndex - 1];
        }

        indexStart = currentIndex;
    }
    data[indexForWrite++] = data[currentIndex - 1];

    // Изменяем размер динамического массива
    data.resize(indexForWrite);

}

// Устанавливаем значение в ячейке
void SparseMatrix::setElement(Element& el) {
    data.push_back(el);
    sorted = false;
}

void SparseMatrix::setElement(int row, int col, double value) {
    Element el(row, col, value);
    setElement(el);
}

// Получаем значение в ячейке
double SparseMatrix::getElement(int row, int col) {
    sortAndRemoveDuplicates();

    for (long long i = data.size() - 1; i >= 0; i--) {
        if (data[i].row == row && data[i].col == col)
            return data[i].value;
    }
    return 0;
}

// Оператор умножения матрицы на вещественное число
SparseMatrix& SparseMatrix::operator*=(double multiplier) {
    for (size_t i = 0; i < data.size(); i++) {
        data[i].value *= multiplier;
    }
    return *this;
}

SparseMatrix& SparseMatrix::operator+=(SparseMatrix& mat) {
    // Подготавливаем обе матрицы
    sortAndRemoveDuplicates();
    mat.sortAndRemoveDuplicates();

    const size_t mat1size = data.size();
    size_t j = 0;
    for (size_t i = 0; i < mat1size && j < mat.data.size();) {
        // Если позиция элемента в матрице одна и та же, то складываем
        if (data[i].row == mat.data[j].row && data[i].col == mat.data[j].col) {
            data[i].value += mat.data[j].value;
            i++;
            j++;
            continue;
        }

        // Индекс в первом массиве меньше текущего индекса во втором
        if (data[i] < mat.data[j]) {
            i++;
            continue;
        }
        // Индекс в первом массиве больше текущего индекса во втором
        // У нас точно в первой матрицы нет элемента с индексом (mat.data[j].row, mat.data[j].col)
        setElement(mat.data[j]);
        j++;
    }

    // Если в первом массиве закончились элементы, но во втором ещё присутствуют,
    // то мы добавляем в первую матрицу соответствующие элементы из второй
    for (; j < mat.data.size(); j++) {
        setElement(mat.data[j]);
    }

    // Отмечаем, что матрица должна быть отсортирована снова
    sorted = false;

    return *this;
}

SparseMatrix& SparseMatrix::operator-=(SparseMatrix& mat) {
    // Подготавливаем обе матрицы
    sortAndRemoveDuplicates();
    mat.sortAndRemoveDuplicates();

    const size_t mat1size = data.size();
    size_t j = 0;
    for (size_t i = 0; i < mat1size && j < mat.data.size();) {
        // Если позиция элемента в матрице одна и та же, то складываем
        if (data[i].row == mat.data[j].row && data[i].col == mat.data[j].col) {
            data[i].value -= mat.data[j].value;
            i++;
            j++;
            continue;
        }

        // Индекс в первом массиве меньше текущего индекса во втором
        if (data[i] < mat.data[j]) {
            i++;
            continue;
        }
        // Индекс в первом массиве больше текущего индекса во втором
        // У нас точно в первой матрицы нет элемента с индексом (mat.data[j].row, mat.data[j].col)
        Element el = mat.data[j];
        el.value = -el.value;
        setElement(el);
        j++;
    }

    // Если в первом массиве закончились элементы, но во втором ещё присутствуют,
    // то мы добавляем в первую матрицу соответствующие элементы из второй со знаком минус
    for (; j < mat.data.size(); j++) {
        Element el = mat.data[j];
        el.value = -el.value;
        setElement(el);
    }

    // Отмечаем, что матрица должна быть отсортирована снова
    sorted = false;

    return *this;
}

SparseMatrix SparseMatrix::operator+(SparseMatrix& mat) {
    // Подготавливаем обе матрицы
    sortAndRemoveDuplicates();
    mat.sortAndRemoveDuplicates();

    SparseMatrix matResult;

    size_t j = 0;
    for (size_t i = 0; i < data.size() && j < mat.data.size();) {
        // Если позиция элемента в матрице одна и та же, то складываем
        if (data[i].row == mat.data[j].row && data[i].col == mat.data[j].col) {
            matResult.setElement(data[i].row, data[i].col, data[i].value + mat.data[j].value);
            i++;
            j++;
            continue;
        }

        // Индекс в первом массиве меньше текущего индекса во втором
        if (data[i] < mat.data[j]) {
            i++;
            continue;
        }

        matResult.setElement(mat.data[j]);
        j++;
    }

    // Если в первом массиве закончились элементы, но во втором ещё присутствуют,
    // то мы добавляем в первую матрицу соответствующие элементы из второй
    for (; j < mat.data.size(); j++) {
        matResult.setElement(mat.data[j]);
    }

    return matResult;
}

SparseMatrix SparseMatrix::operator-(SparseMatrix& mat) {
    // Подготавливаем обе матрицы
    sortAndRemoveDuplicates();
    mat.sortAndRemoveDuplicates();

    SparseMatrix matResult;

    size_t j = 0;
    for (size_t i = 0; i < data.size() && j < mat.data.size();) {
        // Если позиция элемента в матрице одна и та же, то складываем
        if (data[i].row == mat.data[j].row && data[i].col == mat.data[j].col) {
            matResult.setElement(data[i].row, data[i].col, data[i].value - mat.data[j].value);
            i++;
            j++;
            continue;
        }

        // Индекс в первом массиве меньше текущего индекса во втором
        if (data[i] < mat.data[j]) {
            i++;
            continue;
        }

        Element el = mat.data[j];
        el.value = -el.value;
        matResult.setElement(el);
        j++;
    }

    // Если в первом массиве закончились элементы, но во втором ещё присутствуют,
    // то мы добавляем в первую матрицу соответствующие элементы из второй
    for (; j < mat.data.size(); j++) {
        Element el = mat.data[j];
        el.value = -el.value;
        matResult.setElement(el);
    }

    return matResult;
}

SparseMatrix& SparseMatrix::operator=(const SparseMatrix& mat) {
    sorted = mat.sorted;
    std::copy(mat.data.begin(), mat.data.end(), data.begin());
    return *this;
}

// Перегрузка оператора вывода матрицы
ostream& operator<<(ostream& out, SparseMatrix& mat) {
    mat.sortAndRemoveDuplicates();
    if (mat.data.size() == 0)
        return out;

    for (int i = 0; i < mat.data.size() - 1; i++)
        out << mat.data[i] << endl;

    return out << mat.data[mat.data.size() - 1];
}



// Task 3
EasterYear::EasterYear(int indict, int sunCircle,int moonCircle):indict(indict),sunCircle(sunCircle),moonCircle(moonCircle) {
    if (indict <= 0 || indict > 15) 
        throw "Ошибка! Индикт должен принимать значения в диапазоне 1-15.";
    if (sunCircle <= 0 || sunCircle > 28)
        throw "Ошибка! Круг солнцу должен принимать значения в диапазоне 1-28.";
    if (moonCircle <= 0 || moonCircle > 19)
        throw "Ошибка! Круг луне должен принимать значения в диапазоне 1-19.";

    year = 1; // Год в отсчёте от Сотворения мира (5508 до н.э.)

    while (indict != 1 || sunCircle != 1 || moonCircle != 1) {
        if (--indict == 0) indict = 15;
        if (--sunCircle == 0) sunCircle = 28;
        if (--moonCircle == 0) moonCircle = 19;
        year++;
    }
}

EasterYear::EasterYear(int year):year(year) {
    indict = year % 15;
    sunCircle = year % 28;
    moonCircle = year % 19;
}
EasterYear::EasterYear():year(1),indict(1),sunCircle(1),moonCircle(1){}

// Преобразование от года сотворения мира к Григорианскому календарю
int EasterYear::getYearFromTheBirthOfChrist() const {
    int christYear = year - 5508;
    if (christYear <= 0)
        christYear--;

    return christYear;
}

// Преобразование от Григрианского календаря к солнечному календарю
void EasterYear::setYearFromTheBirthOfChrist(int christYear) {
    if (christYear <= 0)
        throw "Ошибка! Укажите положительный год от Рождества Христова.";

    year = christYear + 5508;
    indict = year % 15;
    sunCircle = year % 28;
    moonCircle = year % 19;
}

EasterYear::EasterYear(const EasterYear& el) {
    year = el.year;
    indict = el.indict;
    sunCircle = el.sunCircle;
    moonCircle = el.moonCircle;
}

EasterYear& EasterYear::operator=(const EasterYear& el) {
    year = el.year;
    indict = el.indict;
    sunCircle = el.sunCircle;
    moonCircle = el.moonCircle;

    return *this;
}

ostream& operator<<(ostream& out, const EasterYear& easterYear) {
    int christYear = easterYear.getYearFromTheBirthOfChrist();
    if (christYear < 0)
        out << -christYear << " до н.э. (";
    else
        out << christYear << " н.э. (";

    return out << easterYear.indict << '-' << easterYear.sunCircle << '-' << easterYear.moonCircle << ") год от Адама: " << easterYear.year;
}

istream& operator>>(istream& in, EasterYear& easterYear) {
    int year;
    in >> year;
    easterYear=EasterYear(year);
    return in;
}
