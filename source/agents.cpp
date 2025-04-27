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

    nextNumDeer -= (int)round((float)NowNumWolf * ONE_WOLF_EATS_PER_MONTH);
    
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
    cout << "Month Index,Year,Month,Temperature(C),Precipitation,GrainHeight(cm),DeerPopulation,WolfPopulation" << endl;
  #endif
  
  while (NowYear < 2031) {
    // DoneComputing barrier
    WaitBarrier("Watcher");

    // DoneAssigning barrier
    WaitBarrier("Watcher");
    /**/

    #ifdef CSV
      cout << TotalMonthCount << "," << NowYear << "," << NowMonth << "," << (5./9.) * (NowTemp - 32) << "," << NowPrecip << "," << NowHeight * 2.54 << "," << NowNumDeer << "," << NowNumWolf << endl;
    #else
      cout << "Year: " << NowYear << ", Month: " << NowMonth << endl;
      cout << "Temperature: " << NowTemp << ", Precipitation: " << NowPrecip << endl;
      cout << "Grain Height: " << NowHeight << ", Deer Population: " << NowNumDeer << ", Wolf Population: " << NowNumWolf << endl;
      cout << endl;
    #endif
    
    TotalMonthCount++;
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

    // Wolves survive on deer and when the temperature is between -40 and 50 degrees Fahrenheit (-40 and 10 degrees Celsius)
    if (NowNumDeer > nextNumWolf && NowTemp <= 50 && NowTemp >= -40) {
      nextNumWolf++;
    } else {
      // If conditions are not ideal, one wolf may or may not die
      // Randomly decide if a wolf dies (50% chance)
      float theFateOfOneWolf = Ranf((float)0.0, (float)1.0);

      if (theFateOfOneWolf <= 0.50) {
        nextNumWolf--;
      }
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
