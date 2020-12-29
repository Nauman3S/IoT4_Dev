#include <HCSR04.h>

HCSR04 hc(3,new int[6]{4,5},2);//initialisation class HCSR04 (trig pin , echo pin, number of sensor)

void setupSonar()
{  }

float loopSonar1()
{ 
    return ( hc.dist(0) );
  
    }

float loopSonar2()
{ 
    return ( hc.dist(1) );
  
    }
