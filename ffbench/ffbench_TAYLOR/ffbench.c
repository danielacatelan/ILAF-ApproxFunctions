
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define Float    double            /* Floating point type used in FFT */

#define Asize    256               /* Array edge size */// ORIGINAL


#ifndef ITERATIONS                 /* Allow iterations to be supplied by -D */
//#define ITERATIONS 100000
#define ITERATIONS 1
#endif
int niter = ITERATIONS;            /* Iteration counter */

#define Passes   1 
//#define Passes   50               /* Number of FFT/Inverse passes */
#define Ntimes   (ITERATIONS / Passes) /* Number of outer loop passes */

#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<=(b)?(a):(b))

#define SWAP(a,b) tempr=(a); (a)=(b); (b)=tempr

//#################################
// TAYLOR - SENO C1
//#################################
//**********************************************
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


float taylor_sin(float x)
{

 float aux, t, xx; 
 //***************************
  xx = x * x * x; //x^3 - ORIG
  t = x - (xx * 0.16666666666f); // x3/!3  - ORIG
 //***************************
 aux = (xx = xx * x * x); //x^5 - ORIG
 
 t = t + (aux) * 0.00833333333f; // x5/!5  - ORIG
 //t = FADDX(t, (aux * 0.00833333333f)); //C1
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
//**********************************************

static void fourn(data, nn, ndim, isign)
  Float data[];
  int nn[], ndim, isign;
{
        register int i1, i2, i3;
        int i2rev, i3rev, ip1, ip2, ip3, ifp1, ifp2;
        int ibit, idim, k1, k2, n, nprev, nrem, ntot;
        Float tempi, tempr;
        double theta, wi, wpi, wpr, wr, wtemp;

        ntot = 1;
        for (idim = 1; idim <= ndim; idim++)
           ntot *= nn[idim];
        nprev = 1;
        for (idim = ndim; idim >= 1; idim--) {
           n = nn[idim];
           nrem = ntot / (n * nprev);
           ip1 = nprev << 1;
           ip2 = ip1 * n;
           ip3 = ip2 * nrem;
           i2rev = 1;
           for (i2 = 1; i2 <= ip2; i2 += ip1) {
              if (i2 < i2rev) {
                 for (i1 = i2; i1 <= i2 + ip1 - 2; i1 += 2) {
                    for (i3 = i1; i3 <= ip3; i3 += ip2) {
                       i3rev = i2rev + i3 - i2;
                       SWAP(data[i3], data[i3rev]);
                       SWAP(data[i3 + 1], data[i3rev + 1]);
                    }
                 }
              }
              ibit = ip2 >> 1;
              while (ibit >= ip1 && i2rev > ibit) {
                 i2rev -= ibit;
                 ibit >>= 1;
              }
              i2rev += ibit;
           }
           ifp1 = ip1;
           while (ifp1 < ip2) {
              ifp2 = ifp1 << 1;
              theta = isign * 6.28318530717959 / (ifp2 / ip1);
              //***********************************
              //wtemp = sin(0.5 * theta);//ORIG
              wtemp = taylor_sin(0.5 * theta);//Taylor_EX
              //wtemp = taylor_sin(0.5 * theta);//test1
              //***********************************
              wpr = -2.0 * wtemp * wtemp;
              //***********************************
              //wpi = sin(theta);//ORIG
              wpi = taylor_sin(theta);//Taylor_EX
              //wpi = taylor_sin(theta);//test2
              //***********************************
              wr = 1.0;
              wi = 0.0;
              for (i3 = 1; i3 <= ifp1; i3 += ip1) {
                 for (i1 = i3; i1 <= i3 + ip1 - 2; i1 += 2) {
                    for (i2 = i1; i2 <= ip3; i2 += ifp2) {
                       k1 = i2;
                       k2 = k1 + ifp1;
                       tempr = wr * data[k2] - wi * data[k2 + 1];
                       tempi = wr * data[k2 + 1] + wi * data[k2];
                       data[k2] = data[k1] - tempr;
                       data[k2 + 1] = data[k1 + 1] - tempi;
                       data[k1] += tempr;
                       data[k1 + 1] += tempi;
                    }
                 }
                 wr = (wtemp = wr) * wpr - wi * wpi + wr;
                 wi = wi * wpr + wtemp * wpi + wi;
              }
              ifp1 = ifp2;
           }
           nprev *= n;
        }
}
#undef SWAP

int main(int argc, char *argv[])
{
        int i, j, k, l, m, times,
            npasses = Passes, iters = 0, faedge;
        Float *fdata;
        static int nsize[] = {0, 0, 0};
        long fanum, fasize;
        double mapbase, mapscale, rmin, rmax, imin, imax;

        faedge = Asize;            /* FFT array edge size */
        fanum = faedge * faedge;   /* Elements in FFT array */
        fasize = ((fanum + 1) * 2 * sizeof(Float)); /* FFT array size */
        nsize[1] = nsize[2] = faedge;

        fdata = (Float *) malloc(fasize);
        if (fdata == NULL) {
           //fprintf(stderr, "Can't allocate data array.\n");
             printf("Can't allocate data array.");
           exit(1);
        }

        if (argc > 1) {
           niter = atoi(argv[1]);
           if (*argv[1] == '-' || niter < Passes ||
              ((niter % Passes) != 0)) {
              printf("Invalid iteration count %d.  Must be a multiple of %d.\n",
                niter, Passes);
              return 1;
           }
        }

/*printf("Iterations: %d\n", niter);*/
        times = niter / Passes;
        for (k = 0; k < times; k++) {
/*printf("Time %d of %d\n", k, times);*/

            /*  Generate data array to process.  */

#define Re(x,y) fdata[1 + (faedge * (x) + (y)) * 2]
#define Im(x,y) fdata[2 + (faedge * (x) + (y)) * 2]

            memset(fdata, 0, fasize);
            for (i = 0; i < faedge; i++) {
               for (j = 0; j < faedge; j++) {
                  if (((i & 15) == 8) || ((j & 15) == 8))
                     Re(i, j) = 128.0;
               }
            }

            for (i = 0; i < npasses; i++) {
/*printf("Pass %d\n", i);*/
               /* Transform image to frequency domain. */
               fourn(fdata, nsize, 2, 1);

               /* Back-transform to image. */
               fourn(fdata, nsize, 2, -1);

               iters++;
            }
        }

        {
           double r, ij, ar, ai;
           rmin = 1e10; rmax = -1e10;
           imin = 1e10; imax = -1e10;
           ar = 0;
           ai = 0;

           for (i = 1; i <= fanum; i += 2) {
              r = fdata[i];
              ij = fdata[i + 1];
              ar += r;
              ai += ij;
              rmin = min(r, rmin);
              rmax = max(r, rmax);
              imin = min(ij, imin);
              imax = max(ij, imax);
           }
#ifdef DEBUG
           printf("Real min %.4g, max %.4g.  Imaginary min %.4g, max %.4g.\n",
              rmin, rmax, imin, imax);
           printf("Average real %.4g, imaginary %.4g.\n",
              ar / fanum, ai / fanum);
#endif
           mapbase = rmin;
           mapscale = 255 / (rmax - rmin);
        }

        /* See if we got the right answers. */

        m = 0;
        for (i = 0; i < faedge; i++) {
           for (j = 0; j < faedge; j++) {
              k = (Re(i, j) - mapbase) * mapscale;
              l = (((i & 15) == 8) || ((j & 15) == 8)) ? 255 : 0;
              if (k != l) {
                 m++;
                 printf("Wrong answer at (%d,%d)!  Expected %d, got %d.\n",
                    i, j, l, k);
                    //fprintf(stderr,"Wrong answer at (%d,%d)!  Expected %d, got %d.\n", i, j, l, k);
              }
           }
        }
        if (m == 0) {
           //fprintf(stderr, "%d passes.  No errors in results.\n", iters);
           printf("%d passes.  No errors in results.\n", iters);
        } else {
           //fprintf(stderr, "%d passes.  %d errors in results.\n", iters, m);
           printf("%d passes.  %d errors in results.\n", iters, m);
        }

#ifndef CAPOUT

        {
#define SCRX  322
#define SCRY  200
#define SCRN  (SCRX * SCRY)
           unsigned char patarr[SCRY][SCRX];
           
           char texto1[2] = ":";
           int texto2 = 1;
           int texto3 = 6;
           
           FILE *fp;

#define UtoI(x) (((((x) >> 1) & 0x7F) | ((x) << 7)) & 0xFF)

           /* Copy data from FFT buffer to map. */

           memset(patarr, 0, sizeof patarr);
           l = (SCRX - faedge) / 2;
           m = (faedge > SCRY) ? 0 : ((SCRY - faedge) / 2);
           for (i = 1; i < faedge; i++) {
              for (j = 0; j < min(SCRY, faedge); j++) {
                 k = (Re(i, j) - mapbase) * mapscale;
                 patarr[j + m][i + l] = UtoI(k);
              }
           }
           
           for(int i = 0; i < SCRY; i++)
           {
             for(int j = 0; j < SCRX; j++)
             {
                printf("%hhu \n", patarr[i][j]);
             }
             //printf("\n\n ");
           }//*/
        }
#endif

        return 0;
}
