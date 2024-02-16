#include <math.h>
#include <stdio.h>

double function_log2 (double x)
{
    return log2 (x);
}
 int main()
{
    double i, y;
    for (i=0.1; i<5.0; i = i + 0.1)
    {
        y = function_log2 (i);
        //printf("log2(%.2lf) =  %lf\n", i, y);
        printf("%.2lf\n", y);
    }
 
    return 0;
}


//https://www.codesansar.com/numerical-methods/regula-falsi-or-false-position-method-using-c-programming.htm

//https://github.com/destro014/Numerical-Method-In-C/blob/master/trapezoidal%20rule.c
