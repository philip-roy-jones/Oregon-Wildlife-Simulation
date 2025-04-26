#include <omp.h>
#include <ctime>
#include "../header/globals.h"

unsigned int seed = time(NULL);

// Global state variables
int	NowYear = 2025;   // 2025- 2030
int	NowMonth = 0;     // 0 - 11
  
float	NowPrecip;      // inches of rain per month
float	NowTemp;        // temperature this month
float	NowHeight = 5;  // grain height in inches
int	NowNumDeer = 2;   // number of deer in the current population
int NowNumWolf = 2;   // number of wolves in the current population

// Global state variables for the barrier
omp_lock_t	Lock;
volatile int	NumInThreadTeam;
volatile int	NumAtBarrier;
volatile int	NumGone;

// Constants
const float GRAIN_GROWS_PER_MONTH =	        12.0; // inches of growth
const float ONE_DEER_EATS_PER_MONTH =		    1.0;
  
const float AVG_PRECIP_PER_MONTH =		      7.0;	// average (inches)
const float AMP_PRECIP_PER_MONTH =		      6.0;	// plus or minus
const float RANDOM_PRECIP =			            2.0;	// plus or minus noise
  
const float AVG_TEMP =				              60.0;	// average (fahrenheit)
const float AMP_TEMP =				              20.0;	// plus or minus
const float RANDOM_TEMP =			              10.0;	// plus or minus noise
  
const float MIDTEMP =				                40.0;
const float MIDPRECIP =				              10.0;