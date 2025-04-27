float Ranf( float low, float high );
int Ranf( int ilow, int ihigh );
float SQR( float x );

// Barrier
void InitBarrier(int n);
void WaitBarrier(const char* origin);

void InitializeRandomSeed();
void CalculateWeather();