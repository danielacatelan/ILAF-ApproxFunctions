/*
UNIVERSIDADE FEDERAL DA BAHIA - UFBA
DISCIPLINA: CALCULO NUMERICO - MAT174
PROFESSORA: RAFAELA SOUZA
ALUNOS: CRISTIAN ARAUJO E FABRICIO SIQUEIRA
PROJETO 01 - METODOD DAS CORDAS  
*/ 

#include <stdio.h>  //BIBLIOTECA PARA ENTRADA E SAIDA DE DADOS
#include <math.h>  // BIBLIOTECA PARA FUNCOES MATEMATICAS


double funcao (double x){ 
       //18x
	return (3.14159265358979*pow((300/
	        cos(x)),2)*0.8/(0.5*3.14159265358979*14*14*(1+
	        sin(x)-0.5*
	        cos(x)))-1200);
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
