// // Bailey Bonaci
// // bonacib@oregonstate.edu
// // project 2
// // Source Cited: Code from Professor Mike Bailey with enchancments by Bailey Bonaci

// #include <stdio.h>
// #define _USE_MATH_DEFINES
// #include <math.h>
// #include <stdlib.h>
// #include <time.h>
// #include <omp.h>

// // The main Program

// #define XMIN     -1.
// #define XMAX      1.
// #define YMIN     -1.
// #define YMAX      1.

// float Height( int, int );	// function prototype

// // print debugging messages?
// #ifndef DEBUG
// #define DEBUG   false
// #endif

// // setting the number of threads:
// #ifndef NUMT
// #define NUMT                4
// #endif

// // setting the number of nodes:
// #ifndef NUMNODES
// #define NUMNODES       10
// #endif

// // how many tries to discover the maximum performance:
// #ifndef NUMTIMES
// #define NUMTIMES        20
// #endif

// // Or, you could also use the <i>collapse</i> OpenMP clause:
// // The (2) means you are collapsing 2 nested for-loops into one

// float allHeights(NUMNODES)
// {
//         // do i need this here? omp_set_num_threads( NUMT );    // set the number of threads to use in parallelizing the for-loop:`
//         omp_set_num_threads( NUMT )
//         #pragma omp parallel for collapse(2) default(none)
//         for( int iv = 0; iv < NUMNODES; iv++ )
//         {
//                 for( int iu = 0; iu < NUMNODES; iu++ )
//                 {
//                         float z1 = Height( iu, iv );
//                         // that z is only half of the superquadratic so double it
//                         float z = z1 * 2;
//                         return z
//                 }
//         }
// }


// // The code to evaluate the height at a given <i>iu</i> and <i>iv</i> is:

// const float N = 2.5f;
// const float R = 1.2f;

// float Height( int iu, int iv)	// iu,iv = 0 .. NUMNODES-1
// {
// 	// this does nto work if NUMNODES is 1 or smaller (divide by 0 or a negative)
//         if (NUMNODES <= 1){
//                 return 0
//         }
//         else {
//                 float x = -1.  +  2.*(float)iu /(float)(NUMNODES-1);	// -1. to +1.
//                 float y = -1.  +  2.*(float)iv /(float)(NUMNODES-1);	// -1. to +1.

//                 float xn = pow( fabs(x), (double)N );
//                 float yn = pow( fabs(y), (double)N );
//                 float rn = pow( fabs(R), (double)N );
//                 float r = rn - xn - yn;
//                 if( r <= 0. )
//                         return 0.;
//                 float height = pow( r, 1./(double)N );
//                 return height;
//         }
// }

// int main( int argc, char *argv[ ] )
// {

// 	// the area of a single full-sized tile:
// 	// (not all tiles are full-sized, though) 

// 	float fullTileArea = (  ( ( XMAX - XMIN )/(float)(NUMNODES-1) )  *
// 				( ( YMAX - YMIN )/(float)(NUMNODES-1) )  );

// 	// sum up the weighted heights into the variable "volume"
// 	// using an OpenMP for-loop and a reduction:

//         omp_set_num_threads( NUMT );    // set the number of threads to use in parallelizing the for-loop:`
//         #pragma opm parallel for default(none) shared(fullTileArea) reduction(+:sum)
//         // beacuse of that for we need a for loop this is not the right for loop 
//         for( int i = 1; i < NUMNODES; i++ )
//         {
//                 height = allHeights(NUMNODES);
//                 fprint("height", height)
                
                
//                 // // generic volumes
//                 // cornerVolume = fullTileArea/4
//                 // edgeVolume = fullTileArea/2
//                 // centerVolume = fullTileArea

//                 // // volumes with numnode
//                 // cornerVolume = cornerVolume * 4
//                 // edgeVolume = edgeVolume * (1 + 4*(NUMNODES - 2)
//                 // centerVolume = centerVolume * (NUMNODES -2 )* (NUMNODES -2)

//                 // //full volume
//                 // volume2d = cornerVolume + edgeVolume + centerVolume
//                 // fprintf(volume)
//         }



//         omp_set_num_threads( NUMT );    // set the number of threads to use in parallelizing the for-loop:`

//         // // get ready to record the maximum performance and the probability:
//         // double  maxPerformance = 0.;    // must be declared outside the NUMTIMES loop
//         // int     numHits;                // must be declared outside the NUMTIMES loop

//         // // looking for the maximum performance:
//         // for( int times = 0; times < NUMTIMES; times++ )
//         // {
//         //         double time0 = omp_get_wtime( );

//         //         numHits = 0;

//         //         #pragma omp parallel for default(none) shared(txs,tys,txvs,svs,sths,stderr) reduction(+:numHits)
//         //         for( int n = 0; n < NUMTRIALS; n++ )
//         //         {
//         //             //do for loop
//         //         }

// //print something!
//     // fprintf(stderr, "%2d threads : %8d trials ; probability = %6.2f%% ; megatrials/sec = %6.2lf\n",
//     //             NUMT, NUMTRIALS, 100.*probability, maxPerformance);

// You could use a single for-loop over all the nodes that looks like this:
#pragma omp parallel for default(none) . . .
for( int i = 0; i < NUMNODES*NUMNODES; i++ )
{
	int iu = i % NUMNODES;
	int iv = i / NUMNODES;
	float z = Height( iu, iv );
	. . .
}

. . .

// Or, you could also use the <i>collapse</i> OpenMP clause:
// The (2) means you are collapsing 2 nested for-loops into one
// The end effect is exactly like what is shown above, but without you needing to do the mod and divide



// The code to evaluate the height at a given <i>iu</i> and <i>iv</i> is:

const float N = 2.5f;
const float R = 1.2f;

 . . .

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
	std::list<int> listofheights ();
        #pragma omp parallel for collapse(2) default(none) shared(listofheights)
        for( int iv = 0; iv < NUMNODES; iv++ )
        {
	        for( int iu = 0; iu < NUMNODES; iu++ )
	        {
		        float z1 = Height( iu, iv );
		        //that z is only half of the superquadratic so double it
                        float z = z1 * 2;
                        listofheights.push_back([z, iu, iv]);
	        }
        }

	// the area of a single full-sized tile:
	// (not all tiles are full-sized, though)
        // this does nto work if NUMNODES is 1 or smaller (divide by 0 or a negative)
        if (NUMNODES <= 1){
                return 0
        }
        else{

                float fullTileArea = (  ( ( XMAX - XMIN )/(float)(NUMNODES-1) )  *
                                        ( ( YMAX - YMIN )/(float)(NUMNODES-1) )  );

                // sum up the weighted heights into the variable "volume"
                // using an OpenMP for-loop and a reduction:
                #pragma omp parallel for default(none) shared(listofheights, fullTileArea) reduction(+:volume)
                for( int i = 0; i < NUMNODES*NUMNODES; i++ )
                {
                        current = listofheights[i]
                        // corner NW
                        if (current[1] == 0){
                                if current[2] = 0{
                                        float partialVolume = current[0] * fullTileArea / 4
                                }
                        }
                        // corner NE
                        if (current[1] == 0){
                                if current[2] = NUMNODES{
                                        float partialVolume = current[0] * fullTileArea / 4
                                }
                        }
                        // corner SW
                        if (current[1] == NUMNODES){
                                if current[2] = 0{
                                        float partialVolume = current[0] * fullTileArea / 4
                                }
                        }
                        // corner SE
                        if (current[1] == NUMNODES){
                                if current[2] = NUMNODES{
                                        float partialVolume = current[0] * fullTileArea / 4
                                }
                        }
                        // E edge
                        if (current[1] == NUMNODES){
                                float partialVolume = current[0] * fullTileArea / 2
                        }
                        // S edge
                        if (current[1] == 0){
                                float partialVolume = current[0] * fullTileArea / 2
                        }
                        // W edge
                        if (current[1] == NUMNODES){
                                float partialVolume = current[0] * fullTileArea / 2
                        }
                        // N edge
                        if (current[1] == 0){
                                float partialVolume = current[0] * fullTileArea / 2
                        }
                        else {
                                float partialVolume = current[0] * fullTileArea
                        }
                        volume = volume + partialVolume
                }
        }
}