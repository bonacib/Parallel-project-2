// Bailey Bonaci
// bonacib@oregonstate.edu
// project 2
// Source Cited: Code from Professor Mike Bailey with small enchancments by Bailey Bonaci


// print debugging messages?
#ifndef DEBUG
#define DEBUG   false
#endif

// setting the number of threads:
#ifndef NUMT
#define NUMT                4
#endif

// setting the number of trials in the monte carlo simulation:
#ifndef NUMNODES
#define NUMNODES       10
#endif

// how many tries to discover the maximum performance:
#ifndef NUMTIMES
#define NUMTIMES        20
#endif

// Or, you could also use the <i>collapse</i> OpenMP clause:
// The (2) means you are collapsing 2 nested for-loops into one
// The end effect is exactly like what is shown above, but without you needing to do the mod and divide
#pragma omp parallel for collapse(2) default(none) . . .
for( int iv = 0; iv < NUMNODES; iv++ )
{
	for( int iu = 0; iu < NUMNODES; iu++ )
	{
		float z = Height( iu, iv );
		// that z is only half of the superquadratic so double it
        float z = z * 2
	}
}


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
	. . .

	// the area of a single full-sized tile:
	// (not all tiles are full-sized, though) 

	float fullTileArea = (  ( ( XMAX - XMIN )/(float)(NUMNODES-1) )  *
				( ( YMAX - YMIN )/(float)(NUMNODES-1) )  );

	// sum up the weighted heights into the variable "volume"
	// using an OpenMP for-loop and a reduction:



omp_set_num_threads( NUMT );    // set the number of threads to use in parallelizing the for-loop:`

        // better to define these here so that the rand() calls don't get into the thread timing:
        float *txs  = new float [NUMTRIALS];
        float *tys  = new float [NUMTRIALS];
        float *txvs = new float [NUMTRIALS];
        float *svs  = new float [NUMTRIALS];
        float *sths = new float [NUMTRIALS];

        // fill the random-value arrays:
        for( int n = 0; n < NUMTRIALS; n++ )
        {
                txs[n]  = Ranf(  TXMIN,  TXMAX );
                tys[n]  = Ranf(  TYMIN,  TYMAX );
                txvs[n] = Ranf(  TXVMIN, TXVMAX );
                svs[n]  = Ranf(  SVMIN,  SVMAX );
                sths[n] = Ranf(  STHMIN, STHMAX );
        }

        // get ready to record the maximum performance and the probability:
        double  maxPerformance = 0.;    // must be declared outside the NUMTIMES loop
        int     numHits;                // must be declared outside the NUMTIMES loop

        // looking for the maximum performance:
        for( int times = 0; times < NUMTIMES; times++ )
        {
                double time0 = omp_get_wtime( );

                numHits = 0;

                #pragma omp parallel for default(none) shared(txs,tys,txvs,svs,sths,stderr) reduction(+:numHits)
                for( int n = 0; n < NUMTRIALS; n++ )
                {
                    //do for loop
                }

//print something!
    // fprintf(stderr, "%2d threads : %8d trials ; probability = %6.2f%% ; megatrials/sec = %6.2lf\n",
    //             NUMT, NUMTRIALS, 100.*probability, maxPerformance);