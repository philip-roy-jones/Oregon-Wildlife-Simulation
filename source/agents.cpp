#include <iostream>
#include <cmath>
#include "../header/globals.h"
#include "../header/helper.h"
#include "../header/agents.h"

using namespace std;

void Deer()
{
  while (NowYear < 2031) {
    int nextNumDeer = NowNumDeer;
    int carryingCapacity = (int)( NowHeight );
    if ( nextNumDeer < carryingCapacity ) nextNumDeer++;
    else if ( nextNumDeer > carryingCapacity ) nextNumDeer--;
    
    if( nextNumDeer < 0 ) nextNumDeer = 0;

    // DoneComputing barrier
    WaitBarrier("Deer");

    NowNumDeer = nextNumDeer;

    // DoneAssigning barrier
    WaitBarrier("Deer");

    // DonePrinting barrier
    WaitBarrier("Deer");
  }
}

void Grain()
{
  while (NowYear < 2031) {
    float tempFactor = exp(   -SQR(  ( NowTemp - MIDTEMP ) / 10.  )   );
    float precipFactor = exp(   -SQR(  ( NowPrecip - MIDPRECIP ) / 10.  )   );
  
    float nextHeight = NowHeight;
    nextHeight += tempFactor * precipFactor * GRAIN_GROWS_PER_MONTH;
    nextHeight -= (float)NowNumDeer * ONE_DEER_EATS_PER_MONTH;
  
    if( nextHeight < 0. ) nextHeight = 0.;

    // DoneComputing barrier
    WaitBarrier("Grain");

    NowHeight = nextHeight;

    // DoneAssigning barrier
    WaitBarrier("Grain");

    // DonePrinting barrier
    WaitBarrier("Grain");
  }
  
}

void Watcher() 
{
  while (NowYear < 2031) {
    // DoneComputing barrier
    WaitBarrier("Watcher");

    // DoneAssigning barrier
    WaitBarrier("Watcher");
    /**/
    cout << "Month: " << NowMonth << ", Year: " << NowYear << endl;
    cout << "Temperature: " << NowTemp << ", Precipitation: " << NowPrecip << endl;
    cout << "Grain Height: " << NowHeight << ", Deer Population: " << NowNumDeer << endl;
    cout << endl;
    
    NowMonth++;
    if (NowMonth == 12) {
        NowMonth = 0;
        NowYear++;
    }

    CalculateWeather();

    // DonePrinting barrier
    WaitBarrier("Watcher");
  }
}
