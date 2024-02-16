#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define cot(x) (1.0 / tan(x)) //TAN


#define max_surfaces 10

static short current_surfaces;
static short paraxial;

static double clear_aperture;

static double aberr_lspher;
static double aberr_osc;
static double aberr_lchrom;

static double max_lspher;
static double max_osc;
static double max_lchrom;

static double radius_of_curvature;
static double object_distance;
static double ray_height;
static double axis_slope_angle;
static double from_index;
static double to_index;

static double spectral_line[9];
static double s[max_surfaces][5];
static double od_sa[2][2];             

#ifndef ITERATIONS
#define ITERATIONS 10
#endif
int niter = ITERATIONS;            /* Iteration counter */

static double testcase[4][4] = {
        {27.05, 1.5137, 63.6, 0.52},
        {-16.68, 1, 0, 0.138},
        {-16.68, 1.6164, 36.7, 0.38},
        {-78.1, 1, 0, 0}
};


static void transit_surface() {
        double iang,               /* Incidence angle */
               rang,               /* Refraction angle */
               iang_sin,           /* Incidence angle sin */
               rang_sin,           /* Refraction angle sin */
               old_axis_slope_angle, sagitta;

        if (paraxial) {//if1
           if (radius_of_curvature != 0.0) {//if2
              if (object_distance == 0.0) {
                 axis_slope_angle = 0.0;
                 iang_sin = ray_height / radius_of_curvature;//Incidence angle sin 
              } else
                 iang_sin = ((object_distance -
                    radius_of_curvature) / radius_of_curvature) *
                    axis_slope_angle;//Incidence angle sin

              rang_sin = (from_index / to_index) * iang_sin;//Refraction angle sin
              old_axis_slope_angle = axis_slope_angle;
              axis_slope_angle = axis_slope_angle + iang_sin - rang_sin;
              if (object_distance != 0.0)
                 ray_height = object_distance * old_axis_slope_angle;
              object_distance = ray_height / axis_slope_angle;
              return;
           }//if2
           object_distance = object_distance * (to_index / from_index);
           axis_slope_angle = axis_slope_angle * (from_index / to_index);
           return;
        }//fecha if1

        if (radius_of_curvature != 0.0) {//if3
           if (object_distance == 0.0) {
              axis_slope_angle = 0.0;
              iang_sin = ray_height / radius_of_curvature;
           } else {
              iang_sin = ((object_distance -
                 radius_of_curvature) / radius_of_curvature) *
                 sin(axis_slope_angle);//SENO
           }
           iang = asin(iang_sin);
           rang_sin = (from_index / to_index) *
              iang_sin;
           old_axis_slope_angle = axis_slope_angle;
           axis_slope_angle = axis_slope_angle +
              iang - asin(rang_sin);
           sagitta = sin((old_axis_slope_angle + iang) / 2.0);//SENO
           sagitta = 2.0 * radius_of_curvature*sagitta*sagitta;
           object_distance = ((radius_of_curvature * sin(
              old_axis_slope_angle + iang)) *
              cot(axis_slope_angle)) + sagitta;//SENO
           return;
           
        }//if3
        rang = -asin((from_index / to_index) *
           sin(axis_slope_angle));//SENO
           
        object_distance = object_distance * ((to_index *
           cos(-rang)) / (from_index *
           cos(axis_slope_angle)));//COS COS
        axis_slope_angle = -rang;
}

static void trace_line(line, ray_h)
int line;
double ray_h;
{
        int i;

        object_distance = 0.0;
        ray_height = ray_h;
        from_index = 1.0;

        for (i = 1; i <= current_surfaces; i++) {
           radius_of_curvature = s[i][1];
           to_index = s[i][2];
           if (to_index > 1.0)
              to_index = to_index + ((spectral_line[4] -
                 spectral_line[line]) /
                 (spectral_line[3] - spectral_line[6])) * ((s[i][2] - 1.0) /
                 s[i][3]);
           transit_surface();
           from_index = to_index;
           if (i < current_surfaces)
              object_distance = object_distance - s[i][4];
        } 
}


int main (void)
{//main
        int i, j;
        double od_fline, od_cline;

        spectral_line[1] = 7621.0;       /* A */
        spectral_line[2] = 6869.955;     /* B */
        spectral_line[3] = 6562.816;     /* C */
        spectral_line[4] = 5895.944;     /* D */
        spectral_line[5] = 5269.557;     /* E */
        spectral_line[6] = 4861.344;     /* F */
        spectral_line[7] = 4340.477;     /* G'*/
        spectral_line[8] = 3968.494;     /* H */

        clear_aperture = 4.0;
        current_surfaces = 4;
        for (i = 0; i < current_surfaces; i++)
           for (j = 0; j < 4; j++)
              s[i + 1][j + 1] = testcase[i][j];

        //for (itercount = 0; itercount < niter; itercount++) {//for1

           for (paraxial = 0; paraxial <= 1; paraxial++) {
              trace_line(4, clear_aperture / 2.0);
              printf("%.3lf\n",object_distance);//
              od_sa[paraxial][0] = object_distance;
              od_sa[paraxial][1] = axis_slope_angle;
           }//for

           trace_line(3, clear_aperture / 2.0);
           od_cline = object_distance;
           printf("%.3lf\n",object_distance);//40x 

           trace_line(6, clear_aperture / 2.0);
           od_fline = object_distance;
           printf("%.3lf\n",object_distance);//10x 

           aberr_lspher = od_sa[1][0] - od_sa[0][0];
           aberr_osc = 1.0 - (od_sa[1][0] * od_sa[1][1]) /
              (sin(od_sa[0][1]) * od_sa[0][0]);//SENO
           aberr_lchrom = od_fline - od_cline;//SENO
           max_lspher = sin(od_sa[0][1]);//SENO
           printf("%.3lf\n%.3lf\n%.3lf\n",aberr_osc, aberr_lchrom, max_lspher);//

           max_lspher = 0.0000926 / (max_lspher * max_lspher);
           max_osc = 0.0025;
           max_lchrom = max_lspher;

        return 0;
}//main
