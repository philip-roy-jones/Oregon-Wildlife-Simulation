#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>
#include <cmath>
#include <ctime>
#include <iostream>
#include "../header/helper.h"
#include "../header/globals.h"

using namespace std;

float Ranf( float low, float high )
{
  srand(seed); // Use the global seed variable to seed the random number generator
  float r = (float) rand();
  float t = r  /  (float) RAND_MAX;

  return   low  +  t * ( high - low );
}

int Ranf( int ilow, int ihigh )
{
  float low = (float)ilow;
  float high = ceil( (float)ihigh );

  return (int) Ranf(low,high);
}

float SQR( float x )
{
  return x*x;
}


// specify how many threads will be in the barrier:
//	(also init's the Lock)
void InitBarrier( int n )
{
  NumInThreadTeam = n;
  NumAtBarrier = 0;
	omp_init_lock( &Lock );
}

// have the calling thread wait here until all the other threads catch up:
void WaitBarrier(const char* origin)
{
  // cout << "Thread " << omp_get_thread_num() << " from agent " << origin << " has called WaitBarrier()" << endl;
  omp_set_lock( &Lock );
  {
    NumAtBarrier++;
    if( NumAtBarrier == NumInThreadTeam )
    {
      NumGone = 0;
      NumAtBarrier = 0;
      // let all other threads get back to what they were doing
      // before this one unlocks, knowing that they might immediately
      // call WaitBarrier( ) again:
      while( NumGone != NumInThreadTeam-1 );
      omp_unset_lock( &Lock );
      return;
    }
  }
  omp_unset_lock( &Lock );

  while( NumAtBarrier != 0 );	// this waits for the nth thread to arrive

  #pragma omp atomic
  NumGone++;			// this flags how many threads have returned
}


void CalculateWeather()
{
  float ang = (  30.*(float)NowMonth + 15.  ) * ( M_PI / 180. );	// angle of earth around the sun

  float temp = AVG_TEMP - AMP_TEMP * cos( ang );
  NowTemp = temp + Ranf( -RANDOM_TEMP, RANDOM_TEMP );
  
  float precip = AVG_PRECIP_PER_MONTH + AMP_PRECIP_PER_MONTH * sin( ang );
  NowPrecip = precip + Ranf( -RANDOM_PRECIP, RANDOM_PRECIP );
  if( NowPrecip < 0. ) NowPrecip = 0.;
}