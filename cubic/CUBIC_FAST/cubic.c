/* +++Date last modified: 05-Jul-1997 */

/*
**  CUBIC.C - Solve a cubic polynomial
**  public domain by Ross Cottrell
*/
/* o cubic possui 2 soluções, porém apenas 1 solução será avaliada */
//****************************
// FAST - MINHA
//****************************

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

inline float FADDX(float i, float s) 
{  
    float FADDX;
    asm volatile
    (  
      "faddx.s %[z], %[x], %[y]\n\t"
      : [z] "=f" (FADDX)
      : [x] "f" (i), [y] "f" (s)
    );
    return (FADDX); 
}//end in*/

float fast_sin(float x)
{ 
  float qpprox, qpproxsq;
  static const float fouroverpi = 1.2732395447351627f;
  static const float fouroverpisq = 0.40528473456935109f;
  static const float q = 0.78444488374548933f;
  union { float f; uint32_t i; } p = { 0.20363937680730309f };
  union { float f; uint32_t i; } r = { 0.015124940802184233f };
  union { float f; uint32_t i; } s = { -0.0032225901625579573f };

  union { float f; uint32_t i; } vx = { x };
  uint32_t sign = vx.i & 0x80000000;
  vx.i = vx.i & 0x7FFFFFFF;
  //******************************
  qpprox = fouroverpi * x - fouroverpisq * x * vx.f;//ORIG 
  //******************************
  qpproxsq = qpprox * qpprox;//ORIG
  
  p.i |= sign; //OR inclusivo
  r.i |= sign;
  s.i ^= sign; // OR exclusivo

  return 
      q * qpprox + qpproxsq * (p.f + qpproxsq * (r.f + qpproxsq * s.f));//ORIG     
} 
  
  
static inline float fast_cos (float x)
{
  static const float halfpi = 1.5707963267948966f;
  static const float halfpiminustwopi = -4.7123889803846899f;
  float offset = (x > halfpi) ? halfpiminustwopi : halfpi;
  
  return 
   //fast_sin (x + offset);//ORIG
    fast_sin (FADDX(x, offset));//C1
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
            //x[0] = -2.0*sqrt(Q)*fast_cos(theta/3.0) - a1/3.0;//FAST_EX
            x[0] = -2.0*sqrt(Q)*fast_cos(theta/3.0) - a1/3.0;//Test1
            
            //x[1] = -2.0*sqrt(Q)*cos((theta+2.0*PI)/3.0) - a1/3.0;//ORIG
            //x[1] = -2.0*sqrt(Q)*fast_cos((theta+2.0*PI)/3.0) - a1/3.0;//FAST_EX
            x[1] = -2.0*sqrt(Q)*fast_cos((theta+2.0*PI)/3.0) - a1/3.0;//Test2
            
            //x[2] = -2.0*sqrt(Q)*cos((theta+4.0*PI)/3.0) - a1/3.0;//ORIG
            //x[2] = -2.0*sqrt(Q)*fast_cos((theta+4.0*PI)/3.0) - a1/3.0;//FAST_EX
            x[2] = -2.0*sqrt(Q)*fast_cos((theta+4.0*PI)/3.0) - a1/3.0;//Test3
            
            printf("EX = %.2f , %.2f , %.2f \n",result[0],result[1],result[2]);
            printf("Cout = %.2f , %.2f , %.2f \n",x[0],x[1],x[2]);

      return *x;
}



int main(void)
{
      double  a1 = 1.0, b1 = -10.5, c1 = 32.0, d1 = -30.0;

      double cubo1;

      cubo1 = Cubic(a1, b1, c1, d1);


      return 0;
}


