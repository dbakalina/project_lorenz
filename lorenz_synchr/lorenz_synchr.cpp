#include <iostream>
#include <math.h>
#include <vector>
#include <random>
#include <functional>
#include<fstream>
#include "lorenz.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");
    int dim = 9;

    //point={x(0),y(1),z(2)}
    double* point_orig = (double*)malloc(sizeof(double) * dim);
    double* point_pws = (double*)malloc(sizeof(double) * dim);
    //dPoint={dx/dt, dy/dt, dz/dt}
    double* dPoint_orig = (double*)malloc(sizeof(double) * dim);
    double* dPoint_pws = (double*)malloc(sizeof(double) * dim);
    double* parameters = (double*)malloc(sizeof(double) * 8);
    double* param = (double*)malloc(sizeof(double) * 5);

    ofstream f, f1, f2, f3, f4, f5, f6;
    //f.open("res_orig.txt", ios::out);
    f1.open("res_diff_orig.txt", ios::out);
    f2.open("res_diff_pws.txt", ios::out);
    //
    f3.open("res_grad_orig4.txt", ios_base::out);
    f4.open("res_grad_pws7.txt", ios_base::out);
    //
    f5.open("res_orig_point.txt", ios_base::out);
    f6.open("res_pws_point.txt", ios_base::out);
    //f.open("point.txt", ios::out);

    //parameters={ N(0), b(1), alpha(2), delta(3), lambda(4), nu(5), omega(6), K(7)}
    parameters[0] = 3;  // размер сети N
    parameters[1] = 21; //b
    parameters[2] = 2.0; //alpha
    parameters[3] = 0.588; //delta
    parameters[4] = 0.294; //lambda
    parameters[5] = 0.65; // nu
    parameters[6] = 2.0; //w
    parameters[7] = 0.4; //Сила связи K


    //parameters={ N(0), sigma(1), r(2), beta(3), K(4)}
    param[0] = 3;  //N
    param[1] = 10.0; //sigma
    param[2] = 28.0; //r
    param[3] = 8.0 / 3.0;  //beta
    param[4] = 8; //Сила связи K

    double dt = 0.001;  //Шаг для метода
    int time = 20000;  //Время работы метода

    double eps = 0.1; //Полоса для синхронизации
    double n = 0.0; // Есть синхронизация
    double N = 10.0; // Число экспериментов
    double p = 0.0; //Вероятность синхронизации

    int choice = 0;

    do {
        cout << "Меню:\n\n";
        cout << "\t\t 1. Задать начальные значения для классического Лоренца." << endl;
        cout << "\t\t 2. Задать начальные значения для кусочно-гладкого Лоренца." << endl;
        //
        cout << endl;
        cout << "\t\t 3. Осцилограмма для классического Лоренца." << endl;
        cout << "\t\t 4. Осцилограмма для кусочно-гладкого Лоренца." << endl;
        //cout << endl;
        //
        cout << endl;
        cout << "\t\t 5. График P(r, k) для классического Лоренца." << endl;
        cout << "\t\t 6. График P(b, k) для кусочно-гладкого Лоренца." << endl;
        //
        cout << endl;
        cout << "\t\t 7. Запись точек для классического Лоренца." << endl;
        cout << "\t\t 8. Запись точек для кусочно-гладкого Лоренца." << endl;
        //
        cout << endl;
        cout << "\t\t Для выхода нажмите 0." << endl;
        cout << "\n Введенный вариант: ";
        cin >> choice;
        switch (choice) {
        case 1:
        {
            //начальные значения
            point_orig[0] = ((double)(rand() - 0.5 * RAND_MAX) / RAND_MAX) * 2 * (sqrt(param[3] * (param[2] - 1)));
            point_orig[1] = ((double)(rand() - 0.5 * RAND_MAX) / RAND_MAX) * 2 * (sqrt(param[3] * (param[2] - 1)));
            point_orig[2] = (double)(rand()) / RAND_MAX * (param[2] - 1);
            //
            point_orig[6] = ((double)(rand() - 0.5 * RAND_MAX) / RAND_MAX) * 2 * (sqrt(param[3] * (param[2] - 1)));
            point_orig[7] = ((double)(rand() - 0.5 * RAND_MAX) / RAND_MAX) * 2 * (sqrt(param[3] * (param[2] - 1)));
            point_orig[8] = (double)(rand()) / RAND_MAX * (param[2] - 1);
            //
            point_orig[3] = ((double)(rand() - 0.5 * RAND_MAX) / RAND_MAX) * 2 * (sqrt(param[3] * (param[2] - 1)));
            point_orig[4] = ((double)(rand() - 0.5 * RAND_MAX) / RAND_MAX) * 2 * (sqrt(param[3] * (param[2] - 1)));
            point_orig[5] = (double)(rand()) / RAND_MAX * (param[2] - 1);

            cout << "НУ заданы." << endl;
        }break;
        case 2:
        {
            //начальные значения
            point_pws[0] = ((double)(rand() - 0.5 * RAND_MAX) / RAND_MAX) * 2;
            point_pws[1] = ((double)(rand() - 0.5 * RAND_MAX) / RAND_MAX) * 2;
            point_pws[2] = (double)(rand()) / RAND_MAX * parameters[1];
            //
            point_pws[6] = ((double)(rand() - 0.5 * RAND_MAX) / RAND_MAX) * 2;
            point_pws[7] = ((double)(rand() - 0.5 * RAND_MAX) / RAND_MAX) * 2;
            point_pws[8] = (double)(rand()) / RAND_MAX * parameters[1];
            //
            point_pws[3] = ((double)(rand() - 0.5 * RAND_MAX) / RAND_MAX) * 2;
            point_pws[4] = ((double)(rand() - 0.5 * RAND_MAX) / RAND_MAX) * 2;
            point_pws[5] = (double)(rand()) / RAND_MAX * parameters[1];

            cout << "НУ заданы." << endl;
        }break;
        case 3:
        {
            cout << "Введите время и шаг для метода:" << endl;
            cout << "time: ";
            cin >> time;
            cout << "dt: ";
            cin >> dt;

            for (int i = 0; i < time; i++) {
                RK(lorenz_orig, point_orig, dPoint_orig, parameters, &dim, &dt);
                f1 << i << " " << point_orig[0] - point_orig[6] << " " << point_orig[3] - point_orig[6] <<
                    " " << point_orig[1] - point_orig[7] << " " << point_orig[4] - point_orig[7] <<
                    " " << point_orig[2] - point_orig[8] << " " << point_orig[5] - point_orig[8] << endl;
            }
        }break;
        case 4:
        {
            cout << "Введите время и шаг для метода:" << endl;
            cout << "time: ";
            cin >> time;
            cout << "dt: ";
            cin >> dt;

            for (int i = 0; i < time; i++) {
                //point = odeRK4(lorenzModel_PWS, point, parameters, dt);
                RK(pwl_system_3D, point_pws, dPoint_pws, parameters, &dim, &dt);

                f2 << i << " " << abs(point_pws[0] - point_pws[6]) << " " << abs(point_pws[3] - point_pws[6]) <<
                    " " << abs(point_pws[1] - point_pws[7]) << " " << abs(point_pws[4] - point_pws[7]) <<
                    " " << abs(point_pws[2] - point_pws[8]) << " " << abs(point_pws[5] - point_pws[8]) << endl;
            }
        }break;
        //
        case 5:  //График P(r, k)
        {
            double start_orig = 28.0;
            double end_orig = 120;
            int porog = 8500;
            cout << "Введите необходимые параметры:" << endl;
            cout << "Число экспериментов N: ";
            cin >> N;
            //cout << endl;
            cout << "eps: ";
            cin >> eps;
            //cout << endl;
            cout << "Начальное значение r: ";
            cin >> start_orig;
           //cout << endl;
            cout << "Конечное значение r: ";
            cin >> end_orig;
            //cout << endl;
            cout << "Введите время и шаг для метода:" << endl;
            cout << "time: ";
            cin >> time;
            cout << "dt: ";
            cin >> dt;
            cout << "С какого значения i следует рассматривать синхронизацию: ";
            cin >> porog;
            cout << endl;

            for (param[2] = start_orig; param[2] < end_orig; param[2]++) {
                cout << "r = " << param[2] << endl;
                for (param[4] = 0; param[4] < 10.0; param[4] += 0.1) {
                    cout << "k = " << param[4] << endl;
                    for (int j = 0; j < N; j++) {
                        // начальные значения
                        point_orig[0] = ((double)(rand() - 0.5 * RAND_MAX) / RAND_MAX) * 2;//* (sqrt(param[3] * (param[2] - 1)));
                        point_orig[1] = ((double)(rand() - 0.5 * RAND_MAX) / RAND_MAX) * 2; // *(sqrt(param[3] * (param[2] - 1)));
                        point_orig[2] = (double)(rand()) / RAND_MAX;// *(param[2] - 1);
                        //
                        point_orig[6] = ((double)(rand() - 0.5 * RAND_MAX) / RAND_MAX) * 2;// *(sqrt(param[3] * (param[2] - 1)));
                        point_orig[7] = ((double)(rand() - 0.5 * RAND_MAX) / RAND_MAX) * 2; // *(sqrt(param[3] * (param[2] - 1)));
                        point_orig[8] = (double)(rand()) / RAND_MAX; // *(param[2] - 1);
                        //
                        point_orig[3] = ((double)(rand() - 0.5 * RAND_MAX) / RAND_MAX) * 2;// *(sqrt(param[3] * (param[2] - 1)));
                        point_orig[4] = ((double)(rand() - 0.5 * RAND_MAX) / RAND_MAX) * 2; // *(sqrt(param[3] * (param[2] - 1)));
                        point_orig[5] = (double)(rand()) / RAND_MAX;// *(param[2] - 1);
                        for (int i = 0; i < time; i++) {
                            RK(lorenz_orig, point_orig, dPoint_orig, param, &dim, &dt);
                            if (i > porog) {
                                if ((abs(point_orig[0] - point_orig[6]) > eps) || (abs(point_orig[3] - point_orig[6]) > eps) ||
                                    (abs(point_orig[1] - point_orig[7]) > eps) || (abs(point_orig[4] - point_orig[7]) > eps) ||
                                    (abs(point_orig[2] - point_orig[8]) > eps) || (abs(point_orig[5] - point_orig[8]) > eps)) {
                                    n++;
                                    break;
                                }
                            }
                        }
                    }
                    p = (N - n) / N;
                    cout << "p = " << p << endl;
                    f3 << param[2] << " " << param[4] << " " << p << endl;
                    n = 0;
                }
            }
        }break;
        //
        case 6:  //График P(b, k)
        {
            double start_pws = 3.8;
            double end_pws = 21;
            int porog = 8500;
            cout << "Введите необходимые параметры:" << endl;
            cout << "Число экспериментов N: ";
            cin >> N;
            cout << "eps: ";
            cin >> eps;
            //cout << endl;
            cout << "Начальное значение b: ";
            cin >> start_pws;
            //cout << endl;
            cout << "Конечное значение b: ";
            cin >> end_pws;
            //cout << endl;
            cout << "Введите время и шаг для метода:" << endl;
            cout << "time: ";
            cin >> time;
            cout << "dt: ";
            cin >> dt;
            cout << "С какого значения i следует рассматривать синхронизацию: ";
            cin >> porog;
            cout << endl;

            for (parameters[1] = start_pws; parameters[1] < end_pws; parameters[1] += 0.5) {
                cout << "b = " << parameters[1] << endl;
                for (parameters[7] = 0; parameters[7] < 1.0; parameters[7] += 0.01) {
                    std::cout << "k = " << parameters[7] << endl;
                    for (int j = 0; j < N; j++) {
                        //начальные значения
                        point_pws[6] = ((double)(rand() - 0.5 * RAND_MAX) / RAND_MAX) * 2;
                        point_pws[7] = ((double)(rand() - 0.5 * RAND_MAX) / RAND_MAX) * 2;
                        point_pws[8] = (double)(rand()) / RAND_MAX * parameters[1];
                        //
                        point_pws[0] = ((double)(rand() - 0.5 * RAND_MAX) / RAND_MAX) * 2;
                        point_pws[1] = ((double)(rand() - 0.5 * RAND_MAX) / RAND_MAX) * 2;
                        point_pws[2] = (double)(rand()) / RAND_MAX * parameters[1];
                        //
                        point_pws[3] = ((double)(rand() - 0.5 * RAND_MAX) / RAND_MAX) * 2;
                        point_pws[4] = ((double)(rand() - 0.5 * RAND_MAX) / RAND_MAX) * 2;
                        point_pws[5] = (double)(rand()) / RAND_MAX * parameters[1];

                        for (int i = 0; i < time; i++) {
                            RK(pwl_system_3D, point_pws, dPoint_pws, parameters, &dim, &dt);
                            if (i > 8500) {
                                if ((abs(point_pws[0] - point_pws[6]) > eps) || (abs(point_pws[3] - point_pws[6]) > eps) ||
                                    (abs(point_pws[1] - point_pws[7]) > eps) || (abs(point_pws[4] - point_pws[7]) > eps) ||
                                    (abs(point_pws[2] - point_pws[8]) > eps) || (abs(point_pws[5] - point_pws[8]) > eps)) {
                                    n++;
                                    break;
                                }
                            }
                        }
                    }
                    p = (N - n) / N;
                    cout << "p = " << p << endl;
                    f4 << parameters[1] << " " << parameters[7] << " " << p << endl;
                    n = 0;
                }
            }
        }break;
        case 7:
        {
            int num_orig = 1;
            cout << "Введите время и шаг для метода:" << endl;
            cout << "time: ";
            cin >> time;
            cout << "dt: ";
            cin >> dt;
            cout << "Введите номер системы (1, 2, 3): ";
            cin >> num_orig;
            if (num_orig == 1) {
                for (int i = 0; i < time; i++) {
                    RK(lorenz_orig, point_orig, dPoint_orig, parameters, &dim, &dt);
                    f5 << i << " " << point_orig[0] << " " << point_orig[1] << " " << point_orig[2] << endl;
                }
            }
            if (num_orig == 2) {
                for (int i = 0; i < time; i++) {
                    RK(lorenz_orig, point_orig, dPoint_orig, parameters, &dim, &dt);
                    f5 << i << " " << point_orig[3] << " " << point_orig[4] << " " << point_orig[5] << endl;
                }
            }
            if (num_orig == 3) {
                for (int i = 0; i < time; i++) {
                    RK(lorenz_orig, point_orig, dPoint_orig, parameters, &dim, &dt);
                    f5 << i << " " << point_orig[6] << " " << point_orig[7] << " " << point_orig[8] << endl;
                }
            }
        }break;
        case 8:
        {
            int num_pws = 1;
            cout << "Введите время и шаг для метода:" << endl;
            cout << "time: ";
            cin >> time;
            cout << "dt: ";
            cin >> dt;
            cout << "Введите номер системы (1, 2, 3): ";
            cin >> num_pws;
            if (num_pws == 1) {
                for (int i = 0; i < time; i++) {
                    RK(pwl_system_3D, point_pws, dPoint_pws, parameters, &dim, &dt);
                    f6 << i << " " << point_pws[0] << " " << point_pws[1] << " " << point_pws[2] << endl;
                }
            }
            if (num_pws == 2) {
                for (int i = 0; i < time; i++) {
                    RK(pwl_system_3D, point_pws, dPoint_pws, parameters, &dim, &dt);
                    f6 << i << " " << point_pws[3] << " " << point_pws[4] << " " << point_pws[5] << endl;
                }
            }
            if (num_pws == 3) {
                for (int i = 0; i < time; i++) {
                    RK(pwl_system_3D, point_pws, dPoint_pws, parameters, &dim, &dt);
                    f6 << i << " " << point_pws[6] << " " << point_pws[7] << " " << point_pws[8] << endl;
                }
            }

        }break;
    }
    } while (choice != 0);
}

