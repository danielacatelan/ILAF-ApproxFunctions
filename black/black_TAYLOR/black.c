#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

//***********************************
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
//***********************************
//TAYLOR_EXP_C1 - 1A
 float taylor_exp(float x) 
    { 
        float aux, xx, t=0;       
        xx = x * x; //x^2-ORIG
 //***************************************       
        //t = 1 + (x / 1.0f); //x/1!-ORIG
        t = FADDX(1 , (x / 1.0f));//C1	
//****************************************       
        t = t + (xx / 2.0f); //x^2/2!-ORIG
        aux = (xx = xx * x); //x^3-ORIG        
        t = t + (aux / 6.0f);//-ORIG        
        aux = (xx = xx * x); //x^4//-ORIG        
        t = t + (aux / 24.0f);//-ORIG        
        aux = (xx = xx * x); //x^5//-ORIG        
        t = t + (aux / 120.0f);//-ORIG        
        aux = (xx = xx * x); //x^6//-ORIG                
        t = t + (aux / 720.0f);//-ORIG        
        aux = (xx = xx * x); //x^7//-ORIG        
        t = t + (aux / 5040.0f);//-ORIG        
        aux = (xx = xx * x); //x^8//-ORIG       
        t = t + (aux / 40320.0f);//-ORIG      
        aux = (xx = xx * x); //x^9//-ORIG       
        t = t + (aux / 362880.0f);//-ORIG        
        aux = (xx = xx * x); //x^10//-ORIG       
        t = t + (aux / 3628800.0f);//-ORIG       
        aux = (xx = xx * x); //x^11//-ORIG        
        t = t + (aux / 39916800.0f);//-ORIG        
        aux = (xx = xx * x); //x^12//-ORIG        
        t = t + (aux / 479001600.0f);//-ORIG       
        aux = (xx = xx * x); //x^13//-ORIG        
        t = t + (aux / 6227020800.0f);//-ORIG        
        aux = (xx = xx * x); //x^14//-ORIG       
        t = t + (aux / 87178291200.0f);//-ORIG       
        aux = (xx = xx * x); //x^15//-ORIG        
        t = t + (aux / 1307674368000.0f);//-ORIG        
        aux = (xx = xx * x); //x^16//-ORIG        
        t = t + (aux / 20922789888000.0f);//-ORIG       
        aux = (xx = xx * x); //x^17//-ORIG        
        t = t + (aux / 355687428096000.0f);//-ORIG        
        aux = (xx = xx * x); //x^18//-ORIG        
        t = t + (aux / 6402373705728000.0f);//-ORIG        
        aux = (xx = xx * x); //x^19//-ORIG        
        t = t + (aux / 121645100408832000.0f);//-ORIG       
        aux = (xx = xx * x); //x^20//-ORIG  
        t = t + (aux / 2432902008176640000.0f);//*///-ORIG      
        return t; 
    } 

//***********************************
//FAST_LOG_C42 - 11A, 1S, 20M, 10D
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

//***********************************


double Normal(double zz)
{ 
    //cdf of 0 is 0.5
    if (zz == 0)   
    { 
        return 0.5;
    }
    
    double z = zz;  //zz is input variable,  use z for calculations
    
    if (zz < 0)
        z = -zz;  //change negative values to positive
    
    //set constants
    double p = 0.2316419;  
    double b1 = 0.31938153;
    double b2 = -0.356563782;
    double b3 = 1.781477937;
    double b4 = -1.821255978;
    double b5 = 1.330274428;
    
    //CALCULATIONS
    double f = 1 / sqrt(2 * M_PI);
    //***********************************
    //double ff = exp(-pow(z, 2) / 2) * f;//ORIG
    double ff = taylor_exp(-pow(z, 2) / 2) * f;//TAYLOR_EXP_1
    //***********************************
    double s1 = b1 / (1 + p * z);
    double s2 = b2 / pow((1 + p * z), 2);
    double s3 = b3 / pow((1 + p * z), 3);
    double s4 = b4 / pow((1 + p * z), 4);
    double s5 = b5 / pow((1 + p * z), 5);
    
    //sz is the right-tail approximation
    double  sz = ff * (s1 + s2 + s3 + s4 + s5); 

    double rz; 
    //cdf of negative input is right-tail of input's absolute value 
    if (zz < 0)
        rz = sz;
    
    //cdf of positive input is one minus right-tail 
    if (zz > 0)
        rz = (1 - sz);
    
    
    return rz;
}

double callValue(double strike, double s, double sd, double r, double days)
{ 
     //***********************************
     //double ls = log(s);//ORIG
     double ls = taylor_log(s);//TAYLOR_LOG_1
     //***********************************
     //double lx = log(strike);//ORIG
     double lx = taylor_log(strike);//TAYLOR_LOG_2
     //***********************************
     double t = days / 365;
     double sd2 = pow(sd, 2);
     double n = (ls - lx + r * t + sd2 * t / 2);
     double sqrtT = sqrt(days / 365);
     double d = sd * sqrtT;
     double d1 = n / d;
     double d2 = d1 - sd * sqrtT;
     double nd1 = Normal(d1);
     double nd2 = Normal(d2);
     //***********************************
    
     return 
         //s * nd1 - strike * exp(-r * t) * nd2;//ORIG
         s * nd1 - strike * taylor_exp(-r * t) * nd2;//TAYLOR_EXP_2
     //***********************************
}
    
double putValue(double strike, double s, double sd, double r, double days)
{
     //***********************************
     //double ls = log(s);//ORIG
     double ls = taylor_log(s);//TAYLOR_LOG_3
     //***********************************
     //double lx = log(strike);//ORIG
     double lx = taylor_log(strike);//TAYLOR_LOG_4
     //***********************************
     double t = days / 365;
     double sd2 = pow(sd, 2);
     double n = (ls - lx + r * t + sd2 * t / 2);
     double sqrtT = sqrt(days / 365);
     double d = sd * sqrtT;
     double d1 = n / d;
     double d2 = d1 - sd * sqrtT;
     double nd1 = Normal(d1);
     double nd2 = Normal(d2);
     //***********************************
    
     return 
         //strike * exp(-r * t) * (1 - nd2) - s * (1 - nd1);//ORIG
         strike * taylor_exp(-r * t) * (1 - nd2) - s * (1 - nd1);//TAYLOR_EXP_3
     //***********************************
}

int main(int argc, char *argv[])
{
     /*double strike_price = atof(argv[1]);
     double asset_price = atof(argv[2]);
     double standard_deviation = atof(argv[3]);
     double risk_free_rate = atof(argv[4]);
     double days_to_exp = atof(argv[5]);*/
     double strike_price = 10.00;//42
     double asset_price = 5.00;//40
     double standard_deviation = 1.0;//0.1000
     double risk_free_rate = 0.1;//1.00
     double days_to_exp = 100;//4
     /*printf("Strike Price: %f \n", strike_price);
     printf("Asset Price:  %f \n", asset_price);
     printf("Std Dev:      %f \n", standard_deviation);
     printf("Risk Free:    %f \n", risk_free_rate);
     printf("Days to Exp:  %f \n", days_to_exp);
     printf("Put Value:    %f \n", putValue(strike_price, asset_price, standard_deviation, risk_free_rate, days_to_exp));
     printf("Call Value:   %f \n", callValue(strike_price, asset_price, standard_deviation, risk_free_rate, days_to_exp));*/
     
     printf("%.2f\n%.2f\n", putValue(strike_price, asset_price, standard_deviation, risk_free_rate, days_to_exp), callValue(strike_price, asset_price, standard_deviation, risk_free_rate, days_to_exp));  
     return 0;
}
