// Bailey Bonaci
// bonacib@oregonstate.edu
// project 2
// Source Cited: Code from Professor Mike Bailey with enchancments by Bailey Bonaci

#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

// print debugging messages?
#ifndef DEBUG
#define DEBUG   false
#endif

// setting the number of threads:
#ifndef NUMT
#define NUMT                4
#endif

// setting the number of nodes:
#ifndef NUMNODES
#define NUMNODES       10
#endif

// how many tries to discover the maximum performance:
#ifndef NUMTIMES
#define NUMTIMES        20
#endif


const float N = 2.5f;
const float R = 1.2f;
float maxPerformance = 0;

float
Height( int iu, int iv )	// iu,iv = 0 .. NUMNODES-1
{
	float x = -1.  +  2.*(float)iu /(float)(NUMNODES-1);	// -1. to +1.
	float y = -1.  +  2.*(float)iv /(float)(NUMNODES-1);	// -1. to +1.

	float xn = pow( fabs(x), (double)N );
	float yn = pow( fabs(y), (double)N );
	float rn = pow( fabs(R), (double)N );
	float r = rn - xn - yn;
	if( r <= 0. )
	        return 0.;
	float height = pow( r, 1./(double)N );
	return height;
}

// The main Program

#define XMIN     -1.
#define XMAX      1.
#define YMIN     -1.
#define YMAX      1.

float Height( int, int );	// function prototype

int main( int argc, char *argv[ ] )
{
        // this does nto work if NUMNODES is 1 or smaller (divide by 0 or a negative)
        if (NUMNODES <= 1){
                return 0;
        }
        // area of a single full-sized tile:
        float fullTileArea = (  ( ( XMAX - XMIN )/(float)(NUMNODES-1) )  *
                                ( ( YMAX - YMIN )/(float)(NUMNODES-1) )  );

        int volume = 0;
        int time0;

        // looking for the maximum performance:
        for( int times = 0; times < NUMTIMES; times++ )
        {
                double time0 = omp_get_wtime( );

                omp_set_num_threads( NUMT );    // set the number of threads to use in parallelizing the for-loop
                #pragma omp parallel for default(none) shared(fullTileArea) reduction(+:volume)
                for( int i = 0; i < NUMNODES*NUMNODES; i++ )
                {
                        // this finds all the iu and iv the individual pins code from TA Hongyu Nie
                        int iu = i % NUMNODES;
                        int iv = i / NUMNODES;
                        
                        //find height 
                        float z1 = Height( iu, iv );
                        //that z is only half of the superquadratic so double it
                        float z = z1 * 2;

                        //find location of pin
                        //edges - a corner will hit 2 edges
                        if (iu == 0){
                                z = z/2;
                        }
                        if (iv == 0){
                                z = z/2;
                        }
                        if (iu == NUMNODES-1){
                                z = z/2;
                        }
                        if (iv == NUMNODES-1){
                                z = z/2;
                        }

                        volume = volume + (fullTileArea * z);
                }
                // Modified from Project 1
                double time1 = omp_get_wtime( );
                        double megaHeightsPerSecond = (NUMNODES*NUMNODES) / ( time1 - time0 ) / 1000000.;
                        if( megaHeightsPerSecond > maxPerformance )
                                maxPerformance = megaHeightsPerSecond;
        }
        fprintf(stderr, "%2d threads : %8d NUMNODES ; %8d NUMTIMES ;  megaHeights/sec = %6.2lf\n", NUMT, NUMNODES, NUMTIMES, maxPerformance, volume/NUMTIMES);
}