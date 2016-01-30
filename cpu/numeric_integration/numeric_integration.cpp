//
// Pranjal Mittal, Gorantla Sai Krishna
//
// NUMS, NUMT are to be specified, driver program wil specify
// Performance = NUMS*NUMS/time


/*
# Python program that complies and executes this program for multiple values of NUMS, NUMT
# Save in separate file say run_project1.py
# python run_project1.py will generate the table
# NUMT, NUMS, runtime, volume, wtick(precision)

import os
nums_values = range(1000, 15000, 1000);
thread_values = range(1, 12);
for t in thread_values:
    for n in nums_values:
        print os.system('icpc -openmp -DNUMS=%s -DNUMT=%s numeric_integration.cpp  && ./a.out'%(str(n), str(t)))
        # g++ -fopenmp -DNUMS=%s -DNUMT=%s project1.c  && ./a.out
*/

#include <stdio.h>
#include <omp.h>
#include <unistd.h>

float Height( int, int );

#define XMIN     0.
#define XMAX     3.
#define YMIN     0.
#define YMAX     3.

#define Z00 0.
#define Z10 1.
#define Z20 0.
#define Z30 0.

#define Z01 1.
#define Z11 6.
#define Z21 1.
#define Z31 0.

#define Z02 0.
#define Z12 1.
#define Z22 0.
#define Z32 4.

#define Z03 3.
#define Z13 2.
#define Z23 3.
#define Z33 3.

float Height(int iu, int iv)  {
    // iu, iv = 0 .. NUMS-1 

    float u = (float)iu / (float)(NUMS-1);
    float v = (float)iv / (float)(NUMS-1);

    // the basis functions:

    float bu0 = (1.-u) * (1.-u) * (1.-u);
    float bu1 = 3. * u * (1.-u) * (1.-u);
    float bu2 = 3. * u * u * (1.-u);
    float bu3 = u * u * u;

    float bv0 = (1.-v) * (1.-v) * (1.-v);
    float bv1 = 3. * v * (1.-v) * (1.-v);
    float bv2 = 3. * v * v * (1.-v);
    float bv3 = v * v * v;

    // finally, we get to compute something:

    float height =    bu0 * ( bv0*Z00 + bv1*Z01 + bv2*Z02 + bv3*Z03 )
            + bu1 * ( bv0*Z10 + bv1*Z11 + bv2*Z12 + bv3*Z13 )
            + bu2 * ( bv0*Z20 + bv1*Z21 + bv2*Z22 + bv3*Z23 )
            + bu3 * ( bv0*Z30 + bv1*Z31 + bv2*Z32 + bv3*Z33 );

    return height;
}

int main( int argc, char *argv[ ] ) {
    // the area of a single full-sized tile:

    omp_set_num_threads(NUMT);

    float fullTileArea = (  ( (XMAX-XMIN)/(float)(NUMS-1) )  *  ( ( YMAX - YMIN )/(float)(NUMS-1) )  );

    // sum up the weighted heights into the variable "volume"
    // using an OpenMP for loop and an addition reduction:
    double volume = 0.0;
    float height;

    double t = omp_get_wtime();

    #pragma omp parallel for default(none) shared(fullTileArea), private(height), reduction(+:volume)
    for(int i = 0; i < NUMS*NUMS; i++)
    {
        int iu = i % NUMS;
        int iv = i / NUMS;

        height = Height(iu, iv);

        if ((iu == 0 or iu == NUMS-1) and (iv == 0 or iu == NUMS-1)) {
            // Corner tiles
            volume += height * fullTileArea / 4;

        }
        else if ((iu == 0 or iu == NUMS-1) or (iv == 0 or iu == NUMS-1))  
        {
            // Edge tiles (Condition include)s corner tile cases as well
            // but cornder conditions would already be caught in the first if
            volume += height * fullTileArea / 2;
        }
        else {
            volume += height * fullTileArea;
        }

    }

    // t elapsed in for loop in seconds
    t = omp_get_wtime() - t;

    // Printing cleanly formatted metrics
    printf("%d\t", NUMT);
    printf("%d\t", NUMS);
    printf("%f\t", t);
    printf("%f", NUMS*NUMS/t);
    //printf("%f\t", volume);
    //printf("%f", omp_get_wtick());
    return 0;
}

