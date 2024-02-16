#include <math.h>
#include <stdio.h>
//************************************************
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
}//end in

inline float FSUBX(float i, float s) 
{  
    float FSUBX;
    asm volatile
    (  
      "fsubx.s %[z], %[x], %[y]\n\t"
      : [z] "=f" (FSUBX)
      : [x] "f" (i), [y] "f" (s)
    );
    return (FSUBX); 
}//end in*/

inline float FMULX(float i, float s) 
{  
    float FMULX;
    asm volatile
    (  
      "fmulx.s %[z], %[x], %[y]\n\t"
      : [z] "=f" (FMULX)
      : [x] "f" (i), [y] "f" (s)
    );
    return (FMULX); 
}//end in*/

inline float FDIVX(float i, float s) 
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

//TAYLOR_LOG2_C42
float taylor_log2 (float x)
{
  float D = 2.88539083340;//2/ln(2)
  float t = 0, aux, xx;

   //xx = (x - 1) / (x + 1);//ORIG
   //xx = (x - 1) / (FADDX(x,1));//C1
   xx = (FSUBX(x, 1)) / (FADDX(x,1));//C12taylor*
   
   
   //aux = xx * xx * xx;//aux^3//ORIG
   //aux = xx * FMULX(xx, xx);//C13
   aux = FMULX(xx, FMULX(xx, xx));//C14taylor*


   //t = xx + (aux / 3);//ORIG
   //t = FADDX(xx, (aux / 3));//C2
   t = FADDX(xx, (FDIVX(aux , 3)));//C33taylor*

  //aux = aux * xx * xx;//aux^5//ORIG
  //aux = aux * FMULX(xx, xx);//C15
  aux = FMULX(aux, FMULX(xx, xx));//C16taylor*
   
  //t = t + (aux / 5);//ORIG
  //t = FADDX(t, (aux / 5));//C3
  t = FADDX(t, (FDIVX(aux , 5)));//C34taylor*

  //aux = aux * xx * xx;//aux^7//ORIG
  //aux = aux * FMULX(xx, xx);//C17
  aux = FMULX(aux, FMULX(xx, xx));//C18taylor*
  
  //t = t + (aux / 7);//ORIG
  //t = FADDX(t, (aux / 7));//C4
  t = FADDX(t, (FDIVX(aux , 7)));//C35taylor*

  //aux = aux * xx * xx;//aux^9//ORIG
  //aux = aux * FMULX(xx, xx);//C19
  aux = FMULX(aux, FMULX(xx, xx));//C20taylor*
  
  //t = t + (aux / 9);//ORIG
  //t = FADDX(t, (aux / 9));//C5
  t = FADDX(t, (FDIVX(aux , 9)));//C36taylor*

  //aux = aux * xx * xx;//aux^11//ORIG
  //aux = aux * FMULX(xx, xx);//C21
  aux = FMULX(aux, FMULX(xx, xx));//C22taylor*
  
  //t = t + (aux / 11);//ORIG
  //t = FADDX(t, (aux / 11));//C6
  t = FADDX(t, (FDIVX(aux , 11)));//C37taylor*

  //aux = aux * xx * xx;//aux^13//ORIG
  //aux = aux * FMULX(xx, xx);//C23
  aux = FMULX(aux, FMULX(xx, xx));//C24taylor*
  
  //t = t + (aux / 13);//ORIG
  //t = FADDX(t, (aux / 13));//C7
  t = FADDX(t, (FDIVX(aux , 13)));//C38taylor*

  //aux = aux * xx * xx;//aux^15//ORIG
  //aux = aux * FMULX(xx, xx);//C25
  aux = FMULX(aux, FMULX(xx, xx));//C26taylor*
  
  //t = t + (aux / 15);//ORIG
  //t = FADDX(t, (aux / 15));//C8
  t = FADDX(t, (FDIVX(aux , 15)));//C39taylor*

  //aux = aux * xx * xx;//aux^17//ORIG
  //aux = aux * FMULX(xx, xx);//C27
  aux = FMULX(aux, FMULX(xx, xx));//C28taylor*
  
  //t = t + (aux / 17);//ORIG
  //t = FADDX(t, (aux / 17));//C9
  t = FADDX(t, (FDIVX(aux , 17)));//C40taylor*

  //aux = aux * xx * xx;//aux^19//ORIG
  //aux = aux * FMULX(xx, xx);//C29
  aux = FMULX(aux, FMULX(xx, xx));//C30taylor*
  
  //t = t + (aux / 19);//ORIG
  //t = FADDX(t, (aux / 19));//C10
  t = FADDX(t, (FDIVX(aux , 19)));//C41taylor*

  //aux = aux * xx * xx;//aux^21//ORIG
  //aux = aux * FMULX(xx, xx);//C31
  aux = FMULX(aux, FMULX(xx, xx));//C32taylor*
  
  //t = t + (aux / 21);//ORIG
  //t = FADDX(t, (aux / 21));//C11
  t = FADDX(t, (FDIVX(aux , 21)));//C42taylor*

    return D * t;

}
//************************************************
double function_log2 (double a, double b)
{
    double c = 1 + b/a, x1, x2;
    //x1 = log2(a);//ORIG
    x1 = taylor_log2(a);//t1
    //x2 = log2(c);//ORIG
    x2 = taylor_log2(c);//t2
    
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



