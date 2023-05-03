#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
extern double func1(double x);
extern double func2(double x);
extern double func3(double x);
double d(double (* f)(double), double (* g)(double), double x){             // функция вычисления производной в точке
    double eps = 0.000001;
    return ((f(x + eps) - g(x + eps)) - (f(x) - g(x)))/eps;
}
double root(double (* f)(double), double (* g)(double), double a, double b, double eps1){  // функция нахождение корня композиции ф-ций
    double c = 0;                                                                          // F := f - g с помощью метода касательных
    double F_a = f(a) - g(a), F_b = f(b) - g(b);            // значения F(a) и F(b) (для знака производной)
    double F_a2b = f((a+b)/2) - g((a+b)/2);                 // значение F((a+b)/2) для н-ва йенсена(т.е для знака 2-ой производной)
    double dF = F_b - F_a, d2F = (F_b + F_a)/2 - F_a2b;     // d(F) и d^2(F)
    if ((dF*d2F) >= 0){
        c = b;
        while ((f(c)-g(c))*(f(c - eps1) - g(c - eps1)) > 0){
            c = c - (f(c)-g(c))/(d(f, g, c));
        }
    }else{
        c = a;
        while ((f(c)-g(c))*(f(c + eps1) - g(c + eps1)) > 0){
            c = c - (f(c)-g(c))/(d(f, g, c));
        }
    }
    return c;
}
double integral(double (* f)(double), double a, double b, double eps2){       // функция вычисления интеграла с помощью метода трапеций
    int n = 20000;                              // n разбиений
    double step = (b - a)/n;                    // шаг разбиения
    double In = 0, I2n = 0;                     // значение определенного интеграла с n и 2n разбиениями соотвественно
    double * arrf = calloc(2*n, sizeof(double));        // массив значений ф-ции в точках разбиений (чтобы дважды не считать их)
    for (int i = 0; i < 2*n; i++){                      // его заполнение
        arrf[i] = f(a + step*i/2);
    }
    for (int i = 0; i < 2*n; i++){                      // суммируем основания трапеций (в In попадет половина из них)
        double value = (arrf[i] + arrf[i + 1]);
        I2n += value;
        if (i % 2 == 0){
            In += value;
        }
    }
    In *= step/2;                                       // умножаем на половину высоты (т.к Sтр = (a+b)*(h/2))
    I2n *= step/4;                                      // шаг для I2n был в 2 раза меньше => и высота делится на 4 (а не половина)
    free(arrf);                                         // очистка массива значений
    if (fabs(In - I2n) >= eps2){
        return 0;
    }
    return I2n;
}
int main(void){
    double x13 = root(func1, func3, -3, -2, 0.00001);
    double x12 = root(func1, func2, 1, 2, 0.00001);
    double x23 = root(func2, func3, 0, 1, 0.00001);
    printf("%.4lf\n", integral(func1, x13, x12, 0.0001) - integral(func2, x23, x12, 0.0001) - integral(func3, x13, x23, 0.0001));
    return 0;
}
