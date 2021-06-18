#include "Header.h"

int main() {
    setlocale(LC_ALL, "Russian"); // Для поддержки кириллицы

    cout << "Выберите опцию:" << endl
        << "1 - перевод даты в unix time" << endl
        << "2 - перевод unix time в дату" << endl
        << "3 - перевод даты в file time" << endl
        << "4 - перевод file time в дату" << endl
        << "5 - сложение и вычитание времени" << endl
        << "6 - ввод разряженной матрицы(формат ввода -> индекс коэффициент)" << endl
        << "7 - сложение и вычитание двух матриц" << endl
        << "8 - умножение матрицы на число" << endl
        << "9 - ввод и вывод года по солнечному календарю" << endl;

    uint64_t option = 0;
    cin >> option;
    switch (option) {
        case 1:
        {
            Time t;
            cin >> t;
            cout << t << endl
                 << "Unix_time: " << t.GetUnixTime() << endl;
            break;
        }
        case 2:
        {
            Time t;
            uint64_t input_unix_t;
            cin >> input_unix_t;
            t.SetUnixtime(input_unix_t);

            cout << t << endl;
            break;
        }
        case 3:
        {
            Time t;
            cin >> t;
            cout << t << endl
                 << "File_time: " << t.GetFileTime() << endl;

            break;
        }
        case 4:
        {
            Time t;
            uint64_t input_file_t;
            cin >> input_file_t;
            t.SetFiletime(input_file_t);

            cout << t << endl;

            break;
        }
        case 5:
        {
            Time t1,t2;
            cout << "Введите год, месяц, число, час, минуту, секунду: " << endl;
            cin >> t1;
            cout << t1 << endl << "Unix_time: " << t1.GetUnixTime() << endl << endl;

            cout << "Введите год, месяц, число, час, минуту, секунду: " << endl;
            cin >> t2;
            cout << t2 << endl << "Unix_time: " << t2.GetUnixTime() << endl << endl;

            Time t3 = t1 + t2;
            cout << "Сумма введённых дат и времени: " << endl;
            cout << t3 << endl << "Unix_time: " << t3.GetUnixTime() << endl << endl;

            t3.SetUnixtime(t1 - t2);
            cout << "Разность введённых дат и времени: " << endl;
            cout << t3 << endl << "Unix_time: " << t3.GetUnixTime() << endl << endl;

            break;
        }
        case 6:
        {
            cout << "Введите строку, столбец и значение элемента матрицы:" << endl;

            SparseMatrix mat;
            int row, col, answer;
            double val;
            do
            {
                cin >> row >> col >> val;

                if (row < 0 || col < 0)
                    cout << "Индексы строки и столбца должны быть неотрицательны." << endl;
                else {
                    mat.setElement(row, col, val);
                }
                cout << "Продолжить ввод данных (1 - да, 0 - нет): ";
                cin >> answer;
            } while (answer != 0);

            cout << endl << "Введите строку и столбец для вывода значений матрицы:" << endl;
            do
            {
                cin >> row >> col;
                if (row < 0 || col < 0)
                    cout << "Индексы строки и столбца должны быть неотрицательны." << endl;
                else {
                    cout << mat.getElement(row, col) << endl;
                }

                cout << "Продолжить вывод данных (1 - да, 0 - нет): ";
                cin >> answer;
            } while (answer != 0);

            cout << endl << "Поэлементный вывод матрицы:" << endl << mat << endl;

            break;
        }
        case 7:
        {
            cout << "Введите строку, столбец и значение элемента матрицы A:" << endl;

            SparseMatrix matA, matB;
            int row, col, answer;
            double val;
            do
            {
                cin >> row >> col >> val;

                if (row < 0 || col < 0)
                    cout << "Индексы строки и столбца должны быть неотрицательны." << endl;
                else {
                    matA.setElement(row, col, val);
                }
                cout << "Продолжить ввод данных (1 - да, 0 - нет): ";
                cin >> answer;
            } while (answer != 0);

            cout << endl << "Введите строку, столбец и значение элемента матрицы B:" << endl;
            do
            {
                cin >> row >> col >> val;

                if (row < 0 || col < 0)
                    cout << "Индексы строки и столбца должны быть неотрицательны." << endl;
                else {
                    matB.setElement(row, col, val);
                }
                cout << "Продолжить ввод данных (1 - да, 0 - нет): ";
                cin >> answer;
            } while (answer != 0);

            // Сложение и вычитание матриц A и B
            cout    << endl << "Матрица A:" << endl << matA << endl
                    << endl << "Матрица B:" << endl << matB << endl;
            do
            {
                cout << endl << "Выберите опцию:" << endl
                    << "1 - прибавить к A матрицу B" << endl
                    << "2 - вычесть из A матрицу B" << endl;

                cin >> answer;
                if (answer == 1) {
                    matA += matB; // Оператор SparseMatrix +=
                    //matA = matA + matB; Оператор SparseMatrix + SparseMatrix
                    cout << endl << "Результат сложения. Матрица A:" << endl << matA;
                }
                else if (answer == 2) {
                    matA -= matB;
                    //matA = matA - matB; Оператор SparseMatrix - SparseMatrix
                    cout << endl << "Результат вычитания. Матрица A:" << endl << matA;
                }
                
                cout << endl << endl << "Продолжить ввод данных (1 - да, 0 - нет): ";
                cin >> answer;
            } while (answer != 0);

            break;
        }
        case 8: {
            cout << "Введите строку, столбец и значение элемента матрицы A:" << endl;

            SparseMatrix matA;
            int row, col, answer;
            double val;
            do
            {
                cin >> row >> col >> val;

                if (row < 0 || col < 0)
                    cout << "Индексы строки и столбца должны быть неотрицательны." << endl;
                else {
                    matA.setElement(row, col, val);
                }
                cout << "Продолжить ввод данных (1 - да, 0 - нет): ";
                cin >> answer;
            } while (answer != 0);

            cout << endl << "Введите коэффициент для умножения матрицы на него:" << endl;
            cin >> val;
            matA *= val;
            cout << "Результат операции умножения матрицы на число:" << endl << matA;

            break;
        }
        case 9:
        {
            EasterYear year;

            cout << "Введите год в отсчете от Адама:" << endl;
            cin >> year;
            cout << year << endl << endl;


            int christYear;
            cout << "Введите год в отсчете от Рождества Христова:" << endl;
            cin >> christYear;
            year.setYearFromTheBirthOfChrist(christYear);
            cout << year << endl << endl;


            int indict, sunCircle, moonCircle;
            cout << "Введите индикт, круг солнцу, круг луне: " << endl;
            cin >> indict >> sunCircle >> moonCircle;
            cout << EasterYear(indict, sunCircle, moonCircle) << endl << endl;

            break;
        }
}

    return 0;
}
