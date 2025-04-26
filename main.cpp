#include <omp.h>
#include <stdlib.h>
#include <iostream>
#include "./header/helper.h"
#include "./header/agents.h"
#include "./header/globals.h"

using namespace std;

int main() {
  CalculateWeather( );

  omp_set_num_threads( 3 );	// same as # of sections
  InitBarrier( 3 );
  #pragma omp parallel sections
  {
    #pragma omp section
    {
      Deer( );
      cout << "Deer thread finished." << endl;
    }
  
    #pragma omp section
    {
      Grain( );
      cout << "Grain thread finished." << endl;
    }
  
    #pragma omp section
    {
      Watcher( );
      cout << "Watcher thread finished." << endl;
    }
  
    /*
    #pragma omp section
    {
      MyAgent( );	// your own
    }
    */
  }       // implied barrier -- all functions must return in order
          // to allow any of them to get past here

  return 0;
}