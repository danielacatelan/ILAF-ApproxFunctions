#include <stdio.h>
#include <math.h>
//*********************************************************
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
//***********************************************************
//TAYLOR_LOG_C42 - 11A, 1S, 20M, 10D
float taylor_log (float x)
{
   float t = 0, aux, xx;

   //xx = (x - 1) / (x + 1);//ORIG
   //xx = (x - 1) / (FADDX(x,1));//C1
   xx = (FSUBX(x, 1)) / (FADDX(x,1));//Taylor
   
   //aux = xx * xx * xx;//aux^3//ORIG
   //aux = xx * FMULX(xx, xx);//C13
   aux = FMULX(xx, FMULX(xx, xx));//C14Taylor
   
   //t = xx + (aux / 3);//ORIG
   //t = FADDX(xx, (aux / 3));//C2
   t = FADDX(xx, (FDIVX(aux , 3)));//C33Taylor
  
  //aux = aux * xx * xx;//aux^5//ORIG
  //aux = aux * FMULX(xx, xx);//C15
  aux = FMULX(aux, FMULX(xx, xx));//C16 Taylor  
  
  //t = t + (aux / 5);//ORIG
  //t = FADDX(t, (aux / 5));//C3
  t = FADDX(t, (FDIVX(aux , 5)));//C34Taylor
  
  //aux = aux * xx * xx;//aux^7//ORIG
  //aux = aux * FMULX(xx, xx);//C17
  aux = FMULX(aux, FMULX(xx, xx));//C18Taylor  
  
  //t = t + (aux / 7);//ORIG
  //t = FADDX(t, (aux / 7));//C4
  t = FADDX(t, (FDIVX(aux , 7)));//C35Taylor
  
  //aux = aux * xx * xx;//aux^9//ORIG
  //aux = aux * FMULX(xx, xx);//C19
  aux = FMULX(aux, FMULX(xx, xx));//C20Taylor  
  
  //t = t + (aux / 9);//ORIG
  //t = FADDX(t, (aux / 9));//C5
  t = FADDX(t, (FDIVX(aux , 9)));//C36Taylor
 
  //aux = aux * xx * xx;//aux^11//ORIG
  //aux = aux * FMULX(xx, xx);//C21
  aux = FMULX(aux, FMULX(xx, xx));//C22Taylor 
  
  //t = t + (aux / 11);//ORIG
  //t = FADDX(t, (aux / 11));//C6
  t = FADDX(t, (FDIVX(aux , 11)));//C37Taylor
  
  //aux = aux * xx * xx;//aux^13//ORIG
  //aux = aux * FMULX(xx, xx);//C23
  aux = FMULX(aux, FMULX(xx, xx));//C24Taylor 
  
  //t = t + (aux / 13);//ORIG
  //t = FADDX(t, (aux / 13));//C7
  t = FADDX(t, (FDIVX(aux , 13)));//C38Taylor
  
  //aux = aux * xx * xx;//aux^15//ORIG
  //aux = aux * FMULX(xx, xx);//C25
  aux = FMULX(aux, FMULX(xx, xx));//C26Taylor  
  
  //t = t + (aux / 15);//ORIG
  //t = FADDX(t, (aux / 15));//C8
  t = FADDX(t, (FDIVX(aux , 15)));//C39Taylor
  
  //aux = aux * xx * xx;//aux^17//ORIG
  //aux = aux * FMULX(xx, xx);//C27
  aux = FMULX(aux, FMULX(xx, xx));//C28 Taylor 
  
  //t = t + (aux / 17);//ORIG
  //t = FADDX(t, (aux / 17));//C9
  t = FADDX(t, (FDIVX(aux , 17)));//C40Taylor
  
  //aux = aux * xx * xx;//aux^19//ORIG
  //aux = aux * FMULX(xx, xx);//C29
  aux = FMULX(aux, FMULX(xx, xx));//C30 Taylor 
  
  //t = t + (aux / 19);//ORIG
  //t = FADDX(t, (aux / 19));//C10
  t = FADDX(t, (FDIVX(aux , 19)));//C41Taylor
  
  //aux = aux * xx * xx;//aux^21//ORIG
  //aux = aux * FMULX(xx, xx);//C31
  aux = FMULX(aux, FMULX(xx, xx));//C32Taylor  
  
  //t = t + (aux / 21);//ORIG
  //t = FADDX(t, (aux / 21));//C11
  t = FADDX(t, (FDIVX(aux , 21)));//C42Taylor

  return 2 * t;//ORIG

}
//**********************************************************

//#define log10(x) log(x)/log(10);//ORIG
//#define log10(x) taylor_log(x)/log(10);//TAYLOR_LOG_T1
#define log10(x) taylor_log(x)/taylor_log(10);//TAYLOR_LOG_T2

float f(float x) {
   return pow(x,2)-4; // Função cuja raiz deve ser determinada
}

// Implementação do Método da Bissecção para zeros de funções
// Autor: Renan Birck
// Disciplina: Métodos Numéricos e Computacionais
// Curso: Eng. Elétrica - Universidade Federal de Santa Maria
// Santa Maria, maio de 2010.

int main() {
   
   // eps: erro -> precisão
   // a0 e b0: pontos iniciais -> entre 0 e 5
   // tam: tamanho do intervalo
   // pm: ponto médio
   // it: número de iterações
   
   //float eps, a0, b0, tam, pm, it;//ORIG 
   float eps=0.01, a0 = 1, b0 = 5, tam=100, pm, it; 
   int bolzano_ok = 0; // flag do teorema de Bolzano
   
  // printf("Digite a precisão requerida: \n");
   //scanf("%f",&eps);

  // printf("Digite o intervalo onde deve se buscar a raiz (ex. [0;5] = digite 0 5): \n");
   //scanf("%f %f",&a0,&b0);

   // O teorema de Bolzano (valor intermediário) foi satisfeito? 
   // f(a0) * f(b0) < 0 -> existe troca de sinal no intervalo dado e, portanto
   // existe raiz nele.
    bolzano_ok = (f(a0)*f(b0) > 0?0:1);
    printf("bolzano_ok %.0d.\n",bolzano_ok);

   // Não, então pedir um novo intervalo inicial.
  /* while(bolzano_ok == 0) {
      printf("\nIntervalo [%f;%f] não satisfaz as condições do teorema de Bolzano. Tente outro.\n Intervalo: ",a0,b0);
      scanf("%f %f", &a0, &b0);
      bolzano_ok = (f(a0)*f(b0) > 0?0:1);
   }//*/

   // Iteraçõs necessárias

   it = log10(b0 - a0);
   it -= log10(eps);
 
   //it /= log(2);//ORIG
   it /= taylor_log(2);//TAYLOR_LOG_T3

   printf("Serão necessárias %.0f iterações.\n",ceil(it));

   // Um dos extremos do intervalo é a raiz
   if(f(a0) == 0 || f(b0) == 0)  {
      printf("O valor %f é zero da expressão. \n", f(a0)==0?a0:b0);
      return 0;
   }

   // Implementação do método da bisecção


   while(tam > eps) {
      tam = b0-a0;
      pm = (a0+b0)/2;
      if(f(pm) == 0) {
         printf("SOLUÇÃO EXATA ENCONTRADA!! x = %f\n",pm);   
         return 0;
      }

      if(f(a0)*f(pm) < 0)  b0 = pm; // a solução está a esquerda
       else a0 = pm;  // a solução está a direita
      
   }
   
   printf("Intervalo final: [%f,%f]\n Solução aproximada: %f",a0,b0,(a0+b0)/2);

   return 0;
}
