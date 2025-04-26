#include <omp.h>

extern unsigned int seed;


// Global state variables for the simulation
extern int	NowYear;                              // 2025- 2030
extern int	NowMonth;                             // 0 - 11
extern float	NowPrecip;                          // inches of rain per month
extern float	NowTemp;                            // temperature this month
extern float	NowHeight;                          // grain height in inches
extern int	NowNumDeer;                           // number of deer in the current population

// Global state variables for the barrier
extern omp_lock_t	Lock;
extern volatile int	NumInThreadTeam;
extern volatile int	NumAtBarrier;
extern volatile int	NumGone;


// Constants
extern const float GRAIN_GROWS_PER_MONTH;         // inches of growth
extern const float ONE_DEER_EATS_PER_MONTH;

extern const float AVG_PRECIP_PER_MONTH;	        // average (inches)
extern const float AMP_PRECIP_PER_MONTH;	        // plus or minus
extern const float RANDOM_PRECIP;	                // plus or minus noise
  
extern const float AVG_TEMP;	                    // average (fahrenheit)
extern const float AMP_TEMP;	                    // plus or minus
extern const float RANDOM_TEMP;	                  // plus or minus noise

extern const float MIDTEMP;
extern const float MIDPRECIP;