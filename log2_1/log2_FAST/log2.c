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

double function_log2 (double a, double b)
{
    double c = 1+ b/a, x1, x2;
    x1 = fast_log2(a);
    x2 = fast_log2(c);
    //x2 = log2(c);
    
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



