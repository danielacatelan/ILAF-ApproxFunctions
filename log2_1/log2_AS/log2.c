#include <math.h>
#include <stdio.h>

double function_log2 (double a, double b)
{
    double c = 1+ b/a, x1, x2;
    x1 = log2(a);
    x2 = log2(c);
    
    return (x1 + x2);
}
 int main()
{
    double a, b, j, i, resp;
    for (i=0.1; i<5.0; i = i + 0.1)
    {
      for (j=5.0; j>0.1; j = j - 0.1)
    {
        a = i;
        b = j;
        resp = function_log2 (a, b);
        //printf("a=%.2lf b=%.2lf resp=%.2lf\n",a,b,resp);
        printf("%.2lf\n",resp);
    }
    //printf("\n");
    }
 
    return 0;
}



