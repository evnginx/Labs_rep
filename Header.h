#pragma once
#include <iostream>
#include <clocale>
#include <vector>
#include <algorithm>

using namespace std;

class Time {
    const static uint64_t seconds_in_minute;
    const static uint64_t minutes_in_hour;
    const static uint64_t hours_in_day;

    uint64_t year;
    uint64_t month;
    uint64_t day;
    uint64_t hour;
    uint64_t minute;
    uint64_t second;

    bool isLeap;
public:
    bool static IsLeapYear(uint64_t);

    Time();

    Time(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

    Time(const Time&);

    uint64_t GetYear() const;
    uint64_t GetMonth() const;
    uint64_t GetDay() const;
    uint64_t GetHour() const;
    uint64_t GetMinute() const;
    uint64_t GetSecond() const;
    void SetUnixtime(uint64_t);
    uint64_t GetUnixTime() const;

    void SetFiletime(uint64_t);
    uint64_t GetFileTime();
    uint64_t static GetDaysInMonth(uint64_t, bool);
    uint64_t DaysInCurrentMonth() const;
    Time& operator=(const Time&);

    int64_t operator-(const Time&);
    Time operator+(const Time&);

    ~Time();

    friend istream& operator>>(istream&, Time&);
};

istream& operator>>(istream&, Time&);
ostream& operator<<(ostream&, const Time&);

struct Element {
    int row, col;
    double value;
    Element(int, int, double);

    Element();

    bool operator<(const Element&) const;
};

istream& operator>>(istream&, Element&);
ostream& operator<<(ostream&, const Element&);

class SparseMatrix {
    vector<Element> data;
    bool sorted;
    void sortAndRemoveDuplicates();
public:
    SparseMatrix();
    SparseMatrix(const SparseMatrix&);

    void setElement(Element&);
    void setElement(int, int, double);

    double getElement(int, int);

    SparseMatrix& operator*=(double);
    SparseMatrix& operator+=(SparseMatrix&);
    SparseMatrix& operator-=(SparseMatrix&);
    SparseMatrix operator+(SparseMatrix&);
    SparseMatrix operator-(SparseMatrix&);
    SparseMatrix& operator=(const SparseMatrix&);

    friend ostream& operator<<(ostream&, SparseMatrix&);
};

ostream& operator<<(ostream&, SparseMatrix&);

class EasterYear {
    int indict;    
    int sunCircle;  
    int moonCircle; 

    int year;

public:
    EasterYear(int, int, int);
    EasterYear(int);
    EasterYear();
    EasterYear(const EasterYear&);

    int getYearFromTheBirthOfChrist() const;
    void setYearFromTheBirthOfChrist(int);

    EasterYear& operator=(const EasterYear&);

    friend ostream& operator<<(ostream&, const EasterYear&);
};

ostream& operator<<(ostream&, const EasterYear&);
istream& operator>>(istream&, EasterYear&);
