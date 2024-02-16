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
//****************************************************
//TAYLOR_COS_C1
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
//****************************************************
//TAYLOR_SIN_C1
float taylor_sin(float x)
{

 float aux, t, xx; 
 //***************************
  xx = x * x * x; //x^3 - ORIG
  t = x - (xx * 0.16666666666f); // x3/!3  - ORIG
 //***************************
 aux = (xx = xx * x * x); //x^5 - ORIG
 
 //t = t + (aux) * 0.00833333333f; // x5/!5  - ORIG
 t = FADDX(t, (aux * 0.00833333333f)); //C1
//***************************
 aux = (xx = xx * x * x);//x^7 - ORIG
 t = t - (aux) * 0.00019841269f; // x7/!7  - ORIG

 aux = (xx = xx * x * x); //x^9 - ORIG
 t =  t + (aux) / 362880.0f; // - ORIG

 aux = (xx = xx * x * x); //x^11 - ORIG
 t =  t - (aux) / 39916800.0f; // - ORIG

 aux = (xx = xx * x * x); //x^13 - ORIG
 t =  t + (aux) / 6227020800.0f; // - ORIG

 aux = (xx = xx * x * x); //x^15 - ORIG
 t =  t - (aux) / 1307674368000.0f; // - ORIG

 aux = (xx = xx * x * x); //x^17 - ORIG
 t =  t + (aux) / 355687428096000.0f; // - ORIG

 aux = (xx = xx * x * x); //x^19 - ORIG
 t =  t - (aux) / 121645100408832000.0f; // - ORIG

 aux = (xx = xx * x * x); //x^21 - ORIG
 t =  t + (aux) / 51090942171709440000.0f; // - ORIG

 return t;
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
	        taylor_cos(x)),2)*0.8/(0.5*3.14159265358979*14*14*(1+
	        sin(x)-0.5*
	        cos(x)))-1200);//FAST_COS_T1*/
	   /*(3.14159265358979*pow((300/
	        taylor_cos(x)),2)*0.8/(0.5*3.14159265358979*14*14*(1+
	        sin(x)-0.5*
	        taylor_cos(x)))-1200);//FAST_COS_T2*/
	    (3.14159265358979*pow((300/
	        taylor_cos(x)),2)*0.8/(0.5*3.14159265358979*14*14*(1+
	        taylor_sin(x)-0.5*
	        taylor_cos(x)))-1200);//FAST_SIN_T3*/       
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
