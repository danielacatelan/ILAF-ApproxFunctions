#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "cast.h"
//***********************************
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
//FAST_EXP_C1
static inline float fast_pow2 (float p)
{
  float offset = (p < 0) ? 1.0f : 0.0f;
  float clipp = (p < -126) ? -126.0f : p;
  int w = clipp;
  float z = clipp - w + offset;
  union { uint32_t i; float f; } 
        //v = { cast_uint32_t ( (1 << 23) * ((clipp + 121.2740575f) + (27.7280233f / (4.84252568f - z)) - (1.49012907f * z)) ) };//ORIG
        
        v = { cast_uint32_t ( (1 << 23) * ((clipp + 121.2740575f) + (27.7280233f / FSUBX(4.84252568f, z)) - (1.49012907f * z)) ) };//C1
      
  return v.f;
}

static inline float fast_exp (float p)
{
  return fast_pow2 (1.442695040f * p);//ORIG     
}
//***********************************
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
    double ff = fast_exp(-pow(z, 2) / 2) * f;//FAST_EXP_1
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
     double ls = fast_log(s);//FAST_LOG_1
     //***********************************
     //double lx = log(strike);//ORIG
     double lx = fast_log(strike);//FAST_LOG_2
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
         s * nd1 - strike * fast_exp(-r * t) * nd2;//FAST_EXP_2
     //***********************************
}
    
double putValue(double strike, double s, double sd, double r, double days)
{
     //***********************************
     //double ls = log(s);//ORIG
     double ls = fast_log(s);//FAST_LOG_3
     //***********************************
     //double lx = log(strike);//ORIG
     double lx = fast_log(strike);//FAST_LOG_4
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
         strike * fast_exp(-r * t) * (1 - nd2) - s * (1 - nd1);//FAST_EXP_3
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
