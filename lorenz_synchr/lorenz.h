#pragma once
#include <iostream>
#include <math.h>
#include <vector>
#include <random>
#include <functional>
#include<fstream>

using namespace std;


template<typename T>
int sign(T var)
{
    if (var < 0)
    {
        return -1;
    }
    else { return 1; }
}

std::vector<double> lorenzModel_PWS(vector<double> point, vector<double> parameters) {
    //�����������:
    //point={x,y,z}
    //dPoint={dx/dt, dy/dt, dz/dt}
    //parameters={ N(0), b(1), alpha(2), delta(3), lambda(4), nu(5), omega(6), K(7)}

    //������ ����������� {dx/dt, dy/dt, dz/dt}
    vector<double> dPoint(9);
    double sum = 0;
    for (int i = 0; i < 3; i++) {
        sum += point[3 * i];
    }
    sum = parameters[7] * sum;
    for (int i = 0; i < 3; i++) {
        if ((abs(point[3 * i]) < 1) && (point[3 * i + 2] < parameters[1]))
        {
            //������� �s
            dPoint[3 * i] = point[3 * i] + sum - parameters[7] * parameters[0] * point[3 * i];
            dPoint[3 * i + 1] = -parameters[2] * point[3 * i + 1];
            dPoint[3 * i + 2] = -parameters[5] * point[3 * i + 2];
        }
        else
        {
            if (((point[3 * i] < -1) && (point[3 * i + 2] <= parameters[1]))
                || ((point[3 * i] < -sign(point[3 * i + 1])) && (point[3 * i + 2] > parameters[1])))
            {
                //������� Al
                dPoint[3 * i] = -parameters[4] * (point[3 * i] + 1) + parameters[6] * (point[3 * i + 2] - parameters[1]) + sum - parameters[7] * parameters[0] * point[3 * i];
                dPoint[3 * i + 1] = -parameters[3] * (point[3 * i + 1] + 1);
                dPoint[3 * i + 2] = -parameters[6] * (point[3 * i] + 1) - parameters[4] * (point[3 * i + 2] - parameters[1]);
            }
            else
            {
                //������� Ar
                dPoint[3 * i] = -parameters[4] * (point[3 * i] - 1) - parameters[6] * (point[3 * i + 2] - parameters[1]) + sum - parameters[7] * parameters[0] * point[3 * i];
                dPoint[3 * i + 1] = -parameters[3] * (point[3 * i + 1] - 1);
                dPoint[3 * i + 2] = parameters[6] * (point[3 * i] - 1) - parameters[4] * (point[3 * i + 2] - parameters[1]);
            }
        }
    }

    return dPoint;
}

void pwl_system_3D(double* point, double* dPoint, double* parameters)
{
    //�����������:
    //point={x,y,z}
    //dPoint={dx/dt, dy/dt, dz/dt}
    //parameters={Omega(0),h(1),alpha(2),beta(3),r(4),nu(5),omega(6)}

    //������ ����������� {dx/dt, dy/dt, dz/dt}

    double sum = 0;
    for (int i = 0; i < 3; i++) {
        sum += point[3 * i];
    }
    sum = parameters[7] * sum;
    for (int i = 0; i < 3; i++) {
        if ((abs(point[3 * i]) < 1) && (point[3 * i + 2] < parameters[1]))
        {
            //������� �s
            dPoint[3 * i] = point[3 * i] + sum - parameters[7] * parameters[0] * point[3 * i];
            dPoint[3 * i + 1] = -parameters[2] * point[3 * i + 1];
            dPoint[3 * i + 2] = -parameters[5] * point[3 * i + 2];
        }
        else
        {
            if (((point[3 * i] < -1) && (point[3 * i + 2] <= parameters[1]))
                || ((point[3 * i] < -sign(point[3 * i + 1])) && (point[3 * i + 2] > parameters[1])))
            {
                //������� Al
                dPoint[3 * i] = -parameters[4] * (point[3 * i] + 1) + parameters[6] * (point[3 * i + 2] - parameters[1]) + sum - parameters[7] * parameters[0] * point[3 * i];
                dPoint[3 * i + 1] = -parameters[3] * (point[3 * i + 1] + 1);
                dPoint[3 * i + 2] = -parameters[6] * (point[3 * i] + 1) - parameters[4] * (point[3 * i + 2] - parameters[1]);
            }
            else
            {
                //������� Ar
                dPoint[3 * i] = -parameters[4] * (point[3 * i] - 1) - parameters[6] * (point[3 * i + 2] - parameters[1]) + sum - parameters[7] * parameters[0] * point[3 * i];
                dPoint[3 * i + 1] = -parameters[3] * (point[3 * i + 1] - 1);
                dPoint[3 * i + 2] = parameters[6] * (point[3 * i] - 1) - parameters[4] * (point[3 * i + 2] - parameters[1]);
            }
        }
    }
}


void lorenz_orig(double* point, double* dPoint, double* parameters)
{
    //�����������:
    //point={x,y,z}
    //dPoint={dx/dt, dy/dt, dz/dt}
    //parameters={N(0),sigma(1), r(2), beta(3), K(4)}

    //������ ����������� {dx/dt, dy/dt, dz/dt}

    double sum = 0;
    for (int i = 0; i < 3; i++) {
        sum += point[3 * i];
    }
    sum = parameters[4] * sum;

    for (int i = 0; i < 3; i++) {
        dPoint[3 * i] = parameters[1] * (point[3 * i + 1] - point[3 * i]) + sum - parameters[4] * parameters[0] * point[3 * i]; 
        dPoint[3 * i + 1] = point[3 * i] * (parameters[2] - point[3 * i + 2]) - point[3 * i + 1]; 
        dPoint[3 * i + 2] = point[3 * i] * point[3 * i + 1] - parameters[3] * point[3 * i + 2];
    }
}
std::vector<double> lorenzModel(vector<double> point, vector<double> parameters) {
    //�����������:
    //point={x,y,z}
    //dPoint={dx/dt, dy/dt, dz/dt}
    //parameters={N(0),sigma(1), r(2), beta(3), K(4)}

    //������ ����������� {dx/dt, dy/dt, dz/dt}
    vector<double> dPoint(9);
    double sum = 0;
    for (int i = 0; i < 3; i++) {
        sum += point[3 * i];
    }
    sum = parameters[4] * sum;
    for (int i = 0; i < 3; i++) {
        dPoint[3 * i] = parameters[1] * (point[3 * i + 1] - point[3 * i]) + sum - parameters[4] * parameters[0] * point[3 * i]; //parameters[1] * (point[3 * i + 1] - point[3 * i])
        dPoint[3 * i + 1] = point[3 * i] * (parameters[2] - point[3 * i + 2]) - point[3 * i + 1]; //point[3 * i] * (parameters[2] - perem[3 * i + 2]) - perem[3 * i + 1]
        dPoint[3 * i + 2] = point[3 * i] * point[3 * i + 1] - parameters[3] * point[3 * i + 2]; // point[3 * i] * point[3 * i + 1] - parameters[3] * point[3 * i + 2]
    }

    return dPoint;
}

//���������� �����-����� 4-�� ������� � ������������� �����
std::vector<double> odeRK4(vector<double>(*fun)(vector<double>, vector<double>),
    vector<double> initCon, vector<double> parameters, double t_step)
{
    //������� "�����" ������� � ������ ��������� �������
    vector<double> point(initCon.size());
    vector<double> buf_point(initCon.size());

    point = initCon;

    //������ �����������
    vector<double> dpoint(initCon.size());

    //��������� ������ ������������� ��������������
    double** K = new double* [initCon.size()];
    for (int i = 0; i < point.size(); i++)
    {
        K[i] = new double[4];
    }

    /////////////////////////////////////////
    //K1
    for (int i = 0; i < point.size(); i++)
    {
        K[i][0] = t_step * fun(point, parameters)[i];
    }

    //���������� buf_point ��� K2
    for (int i = 0; i < point.size(); i++)
    {
        buf_point[i] = point[i] + 0.5 * K[i][0];
    }

    //K2
    for (int i = 0; i < point.size(); i++)
    {
        K[i][1] = t_step * fun(buf_point, parameters)[i];
    }

    //���������� buf_point ��� K3
    for (int i = 0; i < point.size(); i++)
    {
        buf_point[i] = point[i] + 0.5 * K[i][1];
    }

    //K3
    for (int i = 0; i < point.size(); i++)
    {
        K[i][2] = t_step * fun(buf_point, parameters)[i];
    }

    //���������� buf_point ��� K4
    for (int i = 0; i < point.size(); i++)
    {
        buf_point[i] = point[i] + K[i][2];
    }

    //K4
    for (int i = 0; i < point.size(); i++)
    {
        K[i][3] = t_step * fun(buf_point, parameters)[i];
    }

    //��������������
    for (int i = 0; i < point.size(); i++)
    {
        point[i] += (K[i][0] + 2 * K[i][1] + 2 * K[i][2] + K[i][3]) / 6;
    }
    /////////////////////////////////////////

    //������� ������
    for (int i = 0; i < point.size(); i++)
    {
        delete[] K[i];
    }
    delete[] K;

    return point;
}

void RK(void(*fun)(double* point, double* dPoint, double* parameters),
    double* point, double* dPoint, double* parameters, int* dim, double* t_step)
{
    //������� "�����" ������� � ������ ��������� �������
    //vector<double> point(initCon.size());
    //vector<double> buf_point(initCon.size());

    double* buf_point = new double[*dim];

    //��������� ������ ������������� ��������������
    double** K = new double* [*dim];
    for (int i = 0; i < *dim; i++)
    {
        K[i] = new double[4];
    }

    /////////////////////////////////////////
    //K1
    fun(point, dPoint, parameters);
    for (int i = 0; i < *dim; i++)
    {
        K[i][0] = *t_step * dPoint[i];
        buf_point[i] = point[i] + 0.5 * K[i][0];
    }

    //K2
    fun(buf_point, dPoint, parameters);
    for (int i = 0; i < *dim; i++)
    {
        K[i][1] = *t_step * dPoint[i];
        buf_point[i] = point[i] + 0.5 * K[i][1];
    }

    //K3
    fun(buf_point, dPoint, parameters);
    for (int i = 0; i < *dim; i++)
    {
        K[i][2] = *t_step * dPoint[i];
        buf_point[i] = point[i] + K[i][2];
    }

    //K4
    fun(buf_point, dPoint, parameters);
    for (int i = 0; i < *dim; i++)
    {
        K[i][3] = *t_step * dPoint[i];
    }

    //��������������
    for (int i = 0; i < *dim; i++)
    {
        point[i] += (K[i][0] + 2 * K[i][1] + 2 * K[i][2] + K[i][3]) / 6;
    }
    /////////////////////////////////////////

    //������� ������
    for (int i = 0; i < *dim; i++)
    {
        delete[] K[i];
    }
    delete[] K;
    delete[] buf_point;

}
