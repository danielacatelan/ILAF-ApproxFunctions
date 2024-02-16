#include <stdio.h>
#include <math.h>
//*********************************************************
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

//FAST_LOG_C1
static inline float fast_log2 (float x)
{
  union { float f; uint32_t i; } vx = { x };
  union { uint32_t i; float f; } mx = { (vx.i & 0x007FFFFF) | 0x3f000000 };
  float y = vx.i;

  y = y * 1.1920928955078125e-7f;//ORIG

  return 
    //y - 124.22551499f - 1.498030302f * mx.f - 1.72587999f / (0.3520887068f + mx.f);//ORIG
  
     y - 124.22551499f - 1.498030302f * mx.f - FDIVX(1.72587999f , (0.3520887068f + mx.f));//FAST_C1

}

static inline float fast_log (float x)
{
  return 0.69314718f * fast_log2(x);//ORIG
}
//**********************************************************

//#define log10(x) log(x)/log(10);//ORIG
//#define log10(x) fast_log(x)/log(10);//FAST_LOG_T1
#define log10(x) fast_log(x)/fast_log(10);//FAST_LOG_T2

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
   it /= fast_log(2);//FAST_LOG_T3

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
