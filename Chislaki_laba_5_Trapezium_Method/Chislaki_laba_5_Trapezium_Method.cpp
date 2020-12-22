#include <iostream>
#include <math.h>
using namespace std;

double Function_1(double x)
{
    double function;
    function = ((1 + x + x * x) / sqrt(pow(x, 3) - 1));
    return function;
}
double Integral(double x, double n, const double left_board = 1.000, const double right_board = 2.631)
{
    double Integral = 0;
    double step;
    
    step = (right_board - left_board) / n;

    x = left_board + step / 1000;
    for (int i = 1; i < n - 1; i++)
    {
        Integral += Function_1(x);
        x += step;
    }
    Integral *= 2;

    Integral += Function_1(left_board + step);
    Integral += Function_1(right_board);
    Integral *= step;
    Integral /= 2;

    return Integral;
}
double Trapezion_Method(double x, const double left_board = 1.000, const double right_board = 2.631)
{
    const double eps = 1e-4;
    double n = 100;     
   
    double Integral_h = 0;
    double Integral_rh = 0;    
    do
    {
        Integral_h = 0;
        Integral_rh = 0;
        Integral_h = Integral(x,n, 1.000, 2.631);        
        n *= 2;
        Integral_rh = Integral(x,n, 1.000, 2.631);
      
        cout << Integral_h << "        " << Integral_rh << endl;
    } while (abs(Integral_h - Integral_rh) >= 3 * eps);
    cout << "Интегрирование функции одной переменной методом трапеций:" << endl;
    return Integral_rh;
}
double Simphsone_Method(double x, const double left_board = 1.000, const double right_board = 2.631)
{
    const double eps = 1e-5;

    double n = 100;
    double step;

    double Integral_h = 0;
    double Integral_rh = 0;
    double Memory_Integral = 0;

    do
    {
        Integral_h = 0;
        Integral_rh = 0;
        Memory_Integral = 0;
        step = (right_board - left_board) / n;

        x = left_board + step;
        for (int i = 2; i < n / 2 - 1; i++)
        {
            Integral_h += Function_1(x);
            x += 2 * step;
        }
        Integral_h *= 2;

        
        x = left_board + step;
        for (int i = 1; i < n / 2; i++)
        {
            Memory_Integral += Function_1(x);
            x += 2 * step;
        }
        Memory_Integral *= 4;
        Integral_h += Memory_Integral;
        Integral_h += Function_1(left_board + step);
        Integral_h += Function_1(right_board);
        Integral_h *= step;
        Integral_h /= 3;

        n *= 2;
        Memory_Integral = 0;
        step = (right_board - left_board) / n;
        x = left_board + step;
        for (int i = 2; i < n / 2 - 1; i++)
        {
            Integral_rh += Function_1(x);
            x += 2 * step;
        }
        Integral_rh *= 2;

        
        x = left_board + step;
        for (int i = 1; i < n / 2; i++)
        {
            Memory_Integral += Function_1(x);
            x += 2 * step;
        }
        Memory_Integral *= 4;
        Integral_rh += Memory_Integral;
        Integral_rh += Function_1(left_board + step);
        Integral_rh += Function_1(right_board);
        Integral_rh *= step;
        Integral_rh /= 3;
        cout << Integral_h << "        " << Integral_rh << endl;
    } while (abs(Integral_h - Integral_rh) >= 3 * eps);

    cout << "Интегрирование функции одной переменной методом Симпсона:" << endl;
    return Integral_rh;

}
double Function_2(double x, double y)
{
    double function;
    function = 4 - x * x - y * y;
    return function;
}
double Variable(double first_x, double first_y, int first_i, int first_j, int n, int m, double step_x, double step_y)
{
    double x;
    double y;
    double Memory_Integral = 0;

    x = first_x;
    for (int i = first_i; i < n - 1; i++)
    {
        y = first_y;
        for (int j = 0; j < m - 1; j++)
        {
            Memory_Integral += Function_2(x, y);
            y += 2 * step_y;
        }
        x += 2 * step_x;
    }
    return Memory_Integral;
}
double Simphsone_for_double_integral(double x, double y, const double left_x = -1.00, const double right_x = 1, const double left_y = -1, const double right_y = 1)
{
    double n = 1e4;
    double m = 1e4;
    double step_x = (right_x - left_x) / (2*n);
    double step_y = (right_y - left_y) / (2*m);

    double Memory_Integral = 0;
    double Real_Integral = 0;

    Memory_Integral = Variable(left_x, left_y, 0, 0, n, m, step_x, step_y);       
    Real_Integral += Memory_Integral;
    Memory_Integral = 0;

    Memory_Integral = Variable(left_x + step_x, left_y, 1, 0, n, m, step_x, step_y);
    Real_Integral += 4* Memory_Integral;
    Memory_Integral = 0;

    Memory_Integral = Variable(left_x + 2*step_x, left_y, 2, 0, n, m, step_x, step_y);
    Real_Integral += Memory_Integral;
    Memory_Integral = 0;

    Memory_Integral = Variable(left_x, left_y + step_y, 0, 1, n, m, step_x, step_y);
    Real_Integral += 4 * Memory_Integral;
    Memory_Integral = 0;

    Memory_Integral = Variable(left_x, left_y + 2 * step_y, 0, 2, n, m, step_x, step_y);
    Real_Integral += Memory_Integral;
    Memory_Integral = 0;

    Memory_Integral = Variable(left_x + step_x, left_y + 2 * step_y, 1, 2, n, m, step_x, step_y);
    Real_Integral += 4*Memory_Integral;
    Memory_Integral = 0;

    Memory_Integral = Variable(left_x + 2*step_x, left_y + step_y, 2, 1, n, m, step_x, step_y);
    Real_Integral += 4 * Memory_Integral;
    Memory_Integral = 0;

    Memory_Integral = Variable(left_x + step_x, left_y + step_y, 1, 1, n, m, step_x, step_y);
    Real_Integral += 16 * Memory_Integral;
    Memory_Integral = 0;

    Memory_Integral = Variable(left_x + 2* step_x, left_y + 2* step_y, 2, 2, n, m, step_x, step_y);
    Real_Integral += Memory_Integral;
    Memory_Integral = 0;

    Real_Integral *= (step_x * step_y)/9;

    cout << "Интегрирование функции двух переменных методом Симпсона:" << endl;
    return Real_Integral;
}
int main()
{
    setlocale(LC_ALL, "rus");
    double x = 0;
    const double left_board = 1.000;
    const double right_board = 2.631;
    double integral_1 = Trapezion_Method(x, left_board, right_board);
    cout << integral_1 << endl;
    
    /*double integral_2 = Simphsone_Method(x, left_board, right_board);
    cout << integral_2 << endl;

    double y = 0;
    const double left_x = -1.00;
    const double right_x = 1;
    const double left_y = -1;
    const double right_y = 1;
    double integral_3 = Simphsone_for_double_integral(x, y, left_x, right_x, left_y, right_y);
    cout << integral_3 << endl;*/
}