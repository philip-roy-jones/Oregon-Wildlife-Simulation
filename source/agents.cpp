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
  #define CSV

  #ifdef CSV
    cout << "Year,Month,Temperature(C),Precipitation,GrainHeight(cm),DeerPopulation,WolfPopulation" << endl;
  #endif
  
  while (NowYear < 2031) {
    // DoneComputing barrier
    WaitBarrier("Watcher");

    // DoneAssigning barrier
    WaitBarrier("Watcher");
    /**/

    #ifdef CSV
      cout << NowYear << "," << NowMonth << "," << (5./9.) * (NowTemp - 32) << "," << NowPrecip << "," << NowHeight * 2.54 << "," << NowNumDeer << "," << NowNumWolf << endl;
    #else
      cout << "Year: " << NowYear << ", Month: " << NowMonth << endl;
      cout << "Temperature: " << NowTemp << ", Precipitation: " << NowPrecip << endl;
      cout << "Grain Height: " << NowHeight << ", Deer Population: " << NowNumDeer << ", Wolf Population: " << NowNumWolf << endl;
      cout << endl;
    #endif
    
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

void Wolf()
{
  while (NowYear < 2031) {
    int nextNumWolf = NowNumWolf;
    
    // Wolves survive on deer and when the temperature is between -40 and 50 degrees Fahrenheit
    if (NowNumDeer > nextNumWolf && NowTemp <= 50 && NowTemp >= -40) {
      nextNumWolf++;
    } else {
      nextNumWolf--;
    }

    if (nextNumWolf < 0) nextNumWolf = 0;

    // DoneComputing barrier
    WaitBarrier("Wolf");

    NowNumWolf = nextNumWolf;

    // DoneAssigning barrier
    WaitBarrier("Wolf");

    // DonePrinting barrier
    WaitBarrier("Wolf");
  }
}
