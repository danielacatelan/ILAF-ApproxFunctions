/*
UNIVERSIDADE FEDERAL DA BAHIA - UFBA
DISCIPLINA: CALCULO NUMERICO - MAT174
PROFESSORA: RAFAELA SOUZA
ALUNOS: CRISTIAN ARAUJO E FABRICIO SIQUEIRA
PROJETO 01 - METODOD DAS CORDAS  
*/ 

#include <stdio.h>  //BIBLIOTECA PARA ENTRADA E SAIDA DE DADOS
#include <math.h>  // BIBLIOTECA PARA FUNCOES MATEMATICAS
//********************************************************
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

float FMULX(float i, float s) 
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
//*****************************************************
//FAST_COS
float fast_sin_T1(float x)
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

  qpprox = fouroverpi * x - fouroverpisq * x * vx.f;//ORIG
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
    //fast_sin_T1 (x + offset);//ORIG
    //fast_sin_T1 (x + offset);//FAST_EX
     fast_sin_T1 (FADDX(x, offset));//C1
}//*/

//*********************************
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
  
    //qpproxsq = FMULX(qpprox, qpprox);//C6 

  p.i |= sign; //OR inclusivo
  r.i |= sign;
  s.i ^= sign; // OR exclusivo

  return 
      q * qpprox + qpproxsq * (p.f + qpproxsq * (r.f + qpproxsq * s.f));//ORIG 
   
      //FADDX((q * qpprox), (FMULX(qpproxsq, (FADDX(p.f, (qpproxsq * (FADDX(r.f, (FMULX(qpproxsq, s.f))))))))));//C5 
}

//********************************************************

double funcao (double x){ 
       //18x
       
	return 
	
	 /*(3.14159265358979*pow((300/
	        cos(x)),2)*0.8/(0.5*3.14159265358979*14*14*(1+
	        sin(x)-0.5*
	        cos(x)))-1200);//ORIG*/
	  /*(3.14159265358979*pow((300/
	        fast_cos(x)),2)*0.8/(0.5*3.14159265358979*14*14*(1+
	        sin(x)-0.5*
	        cos(x)))-1200);//FAST_COS_T1*/
	   (3.14159265358979*pow((300/
	        fast_cos(x)),2)*0.8/(0.5*3.14159265358979*14*14*(1+
	        sin(x)-0.5*
	        fast_cos(x)))-1200);//FAST_COS_T2*/
	    /*(3.14159265358979*pow((300/
	        fast_cos(x)),2)*0.8/(0.5*3.14159265358979*14*14*(1+
	        fast_sin(x)-0.5*
	        fast_cos(x)))-1200);//FAST_SIN_T3*/       
}

// METODO DAS CORDAS
double cordas(double a, double b, double e1, double e2){
	double erro, fa, fb, c, fc; //VARIAVEIS PARA RAIZ, FUNCAO PARA CADA VALOR E ERRO
	int cont = 0; //VARIAVEL PARA CONTADOR DE INTERAÇÕES
	
	fa=funcao(a); //CALCULANDO O VALOR DA FUNCAO PARA O INICIO DA FAIXA
	fb=funcao(b); //CALCULANDO O VALOR DA FUNCAO PARA O FIM DA FAIXA
	c=(a*fb - b*fa)/(fb-fa); //CALCULANDO VALOR DA RAIZ
	fc=funcao(c); //CALCULANDO O VALOR DA FUNCAO PARA A RAIZ
	erro=fabs(b-a); // CALCULANDO ERRO 
    
	while(erro>e1 || fabs(fc)>e2){ //LOOPING COM VERIFICACAO DAS CONDICOES DE PARADA
		cont++; //INCREMENTANDO CONTADOR
        	a=b; //TROCANDO O INCIO DA FAIXA
        	b=c; //TROCANDO O FIM DA FAIXA
        	fa=funcao(a); //CALCULANDO O VALOR DA FUNCAO PARA O INICIO DA FAIXA
    		fb=funcao(b); //CALCULANDO O VALOR DA FUNCAO PARA O FIM DA FAIXA
        	c=(a*fb - b*fa)/(fb - fa); //CALCULANDO VALOR DA RAIZ
        	fc=funcao(c); //CALCULANDO O VALOR DA FUNCAO PARA A RAIZ
    		erro=fabs(b-a); // CALCULANDO ERRO 
    	}
    
	//printf("\nRaiz: %.3lf",c); //IMPRIME A RAIZ MAIS PROXIMA
	//printf("\nNumero de iteracoes: %d",cont); // IMPRIME O NUMERO DE INTERAÇÕES
	printf("\n%.3lf\n%d\n",c,cont);
	return c;
}

int main(){
	double a=5, b=1, e1=0.5, e2=0.1; //VARIAVEIS INICIAIS
	cordas(a, b, e1, e2); //CHAMA O METODO NUMERICO

}
