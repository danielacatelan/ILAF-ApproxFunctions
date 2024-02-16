#include <math.h>
#include <stdio.h>
//************************************************
float FDIVX(float i, float s) 
{  
    float FDIVX;
    asm volatile
    (  
      "fdivx.s %[z], %[x], %[y]\n\t"
      : [z] "=f" (FDIVX)
      : [x] "f" (i), [y] "f" (s)
    );
    return (FDIVX); 
}//end in*/

// FAST_log2_C1
// 
 static inline float fast_log2 (float x)
{
  union { float f; uint32_t i; } vx = { x };
  union { uint32_t i; float f; } mx = { (vx.i & 0x007FFFFF) | 0x3f000000 };
  float y = vx.i;

  y = y * 1.1920928955078125e-7f;//ORIG

  return 
  //y - 124.22551499f - (1.498030302f * mx.f) - (1.72587999f / (0.3520887068f + mx.f));//ORIG
  
  y - 124.22551499f - (1.498030302f * mx.f) - FDIVX(1.72587999f , (0.3520887068f + mx.f));//C1 ok
  
}//*/
//************************************************

double function_log2 (double x)
{
    //return log2 (x);//ORIG
    return fast_log2 (x);//FAST_LOG2_T1
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
