/* +++Date last modified: 05-Jul-1997 */

/*
**  CUBIC.C - Solve a cubic polynomial
**  public domain by Ross Cottrell
*/
/* o cubic possui 2 soluções, porém apenas 1 solução será avaliada */
//****************************
// TAYLOR
//****************************

#include <math.h>
#include <stdlib.h>
#include <stdio.h>


inline float FADDX(float i, float s) 
{  
    float FADDX;
    printf ("FADDX\n") ;
    asm volatile
    (  
      "faddx.s %[z], %[x], %[y]\n\t"
      : [z] "=f" (FADDX)
      : [x] "f" (i), [y] "f" (s)
    );
    return (FADDX); 
}//end in*/

float taylor_cos (float x) 
{
     float xx, t, aux; 
//****************************************************
    xx = x * x; //x^2 ORIG
//****************************************************
    t = 1.0f - (xx * 0.5f); //1-(x2/!2) ORIG
//****************************************************
    aux = (xx = xx * x * x);//x^4 ORIG
    
    //t = t + aux * 0.04166666666f; //t+(x4/!4) ORIG
    t = FADDX(t, (aux * 0.04166666666f)); //C1
//****************************************************
    aux = (xx = xx *  x * x);//x^6 ORIG
    t = t - aux * 0.00138888888f; //t-(x6/!6)  ORIG
//****************************************************
    aux = (xx = xx *  x * x);//x^8 ORIG
    t = t + aux / 40320.0f; // t+(x8/!8)  ORIG
//****************************************************
    aux = (xx = xx *  x * x);//x^10 ORIG
    t = t - aux / 3628800.0f; // ORIG
//****************************************************
    aux = (xx = xx *  x * x);//x^12 ORIG
    t = t + aux / 479001600.0f; // ORIG 
//****************************************************
    aux = (xx = xx *  x * x);//x^14 ORIG
    t = t - aux / 87178291200.0f; // ORIG
//****************************************************
    aux = (xx = xx *  x * x);//x^16 ORIG
    t = t + aux / 20922789888000.0f; //ORIG
//****************************************************
    aux = (xx = xx *  x * x);//x^18 ORIG
    t = t - aux / 6402373705728000.0f; //  ORIG
//****************************************************
    aux = (xx = xx *  x * x);//x^20 ORIG
    t = t + aux / 243290200817664000.0f; //ORIG 
//****************************************************

  return t;


}

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
     
       
            theta = acos(R/sqrt(Q*Q*Q));
            
            
            //x[0] = -2.0*sqrt(Q)*cos(theta/3.0) - a1/3.0;//ORIG
            //x[0] = -2.0*sqrt(Q)*taylor_cos(theta/3.0) - a1/3.0;//Taylor_EX
           x[0] = -2.0*sqrt(Q)*taylor_cos(theta/3.0) - a1/3.0;//test1
            
            
            //x[1] = -2.0*sqrt(Q)*cos((theta+2.0*PI)/3.0) - a1/3.0;//ORIG
            //x[1] = -2.0*sqrt(Q)*taylor_cos((theta+2.0*PI)/3.0) - a1/3.0;//Taylor_EX
            x[1] = -2.0*sqrt(Q)*taylor_cos((theta+2.0*PI)/3.0) - a1/3.0;//test2
            
            
            //x[2] = -2.0*sqrt(Q)*cos((theta+4.0*PI)/3.0) - a1/3.0;//ORIG
            //x[2] = -2.0*sqrt(Q)*taylor_cos((theta+4.0*PI)/3.0) - a1/3.0;//Taylor_EX
            x[2] = -2.0*sqrt(Q)*taylor_cos((theta+4.0*PI)/3.0) - a1/3.0;//test3
            
            printf("EX = %.2f , %.2f , %.2f \n",result[0],result[1],result[2]);
            printf("Cout = %.2f , %.2f , %.2f \n",x[0],x[1],x[2]);
            //confere resultados

      return *x;
}



int main(void)
{
      double  a1 = 1.0, b1 = -10.5, c1 = 32.0, d1 = -30.0;

      double cubo1;

      cubo1 = Cubic(a1, b1, c1, d1);


      return 0;
}


