#include <stdio.h>
#include <limits.h>

#include "usage.h"
#include "nav_iplib.h"

int main( int argc, char **argv )
{
  char *szBaseName = 0;
  char *szSupportedOpts = 0;
  char szRampFileName[PATH_MAX] = "";
  char szHoldFileName[PATH_MAX] = "";

  int rc = 0;
  int optch;
  unsigned int numOfRamps, numOfHolds;
  ramp *Ramps = NULL, *currentRampPtr;
  hold *Holds = NULL, *currentHoldPtr;

  numOfRamps = rampRead("navIpRamp.ndat", &Ramps);
  currentRampPtr = Ramps;

  numOfHolds = holdRead("navIpHold.ndat", &Holds);
  currentHoldPtr = Holds;

/*
  while( currentRampPtr != NULL)
  {
    printf("Apt: %s\tGate: %s\tLat: %s\tLon: %s\n", currentRampPtr->Apt, currentRampPtr->Gate, currentRampPtr->Lat, currentRampPtr->Lon );
    currentRampPtr = currentRampPtr->nextPtr;
  }
  printf("Read in %d ramp positions\n", numOfRamps);
*/

/*
  while( currentHoldPtr != NULL)
  {
    printf("Apt: %s\tRwy: %s\tLat: %s\tLon: %s\n", currentHoldPtr->Apt, currentHoldPtr->Rwy, currentHoldPtr->Lat, currentHoldPtr->Lon );
    currentHoldPtr = currentHoldPtr->nextPtr;
  }
  printf("Read in %d hold positions\n", numOfHolds);
*/

  /* Clean up */
  freeRampList( &Ramps );

  free( szBaseName );
  szBaseName = 0;

  free( szSupportedOpts );
  szSupportedOpts = 0;
  return 0;
}
