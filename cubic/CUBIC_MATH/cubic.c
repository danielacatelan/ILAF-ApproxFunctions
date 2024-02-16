/* +++Date last modified: 05-Jul-1997 */

/*
**  CUBIC.C - Solve a cubic polynomial
**  public domain by Ross Cottrell
*/
/* o cubic possui 2 soluções, porém apenas 1 solução será avaliada */

#include <math.h>
#include <stdlib.h>
#include <stdio.h>


static double Cubic(double  a,
                double  b,
                double  c,
                double  d)
               
{
       double    a1 = b/a, a2 = c/a, a3 = d/a;
       double    Q = (a1*a1 - 3.0*a2)/9.0;
       double    R = (2.0*a1*a1*a1 - 9.0*a1*a2 + 27.0*a3)/54.0;
       double    R2_Q3 = R*R - Q*Q*Q;

      double    theta;
      double    x[3];
      double    PI = 3.14159265;
      
      double result[3] = {2.00, 6.00, 2.50};//eu
      int count = 0;
 
            theta = acos(R/sqrt(Q*Q*Q));
            x[0] = -2.0*sqrt(Q)*cos(theta/3.0) - a1/3.0;
            x[1] = -2.0*sqrt(Q)*cos((theta+2.0*PI)/3.0) - a1/3.0;
            x[2] = -2.0*sqrt(Q)*cos((theta+4.0*PI)/3.0) - a1/3.0;
            printf("C1 = %.2f , %.2f , %.2f \n",x[0],x[1],x[2]);
            if (x[0] = result[0])
                count++;
            if (x[1] = result[1])
                count++;
            if (x[2] = result[2])
                count++;        
            printf("ACC = %d\n",count);

      return *x;
}



int main(void)
{
      double  a1 = 1.0, b1 = -10.5, c1 = 32.0, d1 = -30.0;

      double cubo1;

      cubo1 = Cubic(a1, b1, c1, d1);


      return 0;
}


