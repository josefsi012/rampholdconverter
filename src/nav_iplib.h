#ifndef NAV_IPLIB_H_INCLUDED
#define NAV_IPLIB_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef NULL
#define NULL 0
#endif

#define AptSize 5
#define GateSize 5
#define RwySize 5
#define LatSize 20
#define LonSize 20
#define HdgSize 20
#define ElevSize 20

/*----- Link Structure -----*/
struct rampstruct
{
  unsigned int Num;
  char Apt[AptSize];
  char Gate[GateSize];
  char Lat[LatSize];
  char Lon[LonSize];
  char Hdg[HdgSize];
  char Elev[ElevSize];
  struct rampstruct *nextPtr;
};
typedef struct rampstruct ramp;
typedef ramp *pRamp;

struct holdstruct
{
  unsigned int Num;
  char Apt[AptSize];
  char Rwy[RwySize];
  char Lat[LatSize];
  char Lon[LonSize];
  char Hdg[HdgSize];
  char Elev[ElevSize];
  struct holdstruct *nextPtr;
};
typedef struct holdstruct hold;
typedef hold *pHold;

void insertRamp( unsigned int num, char *apt, char *gate, char *lat, char *lon, char *hdg, char *elev, pRamp *sPtr);
void freeRampList( pRamp *sPtr);
unsigned int rampRead(char *szRampFileName, pRamp *sPtr );

void insertHold( unsigned int num, char *apt, char *rwy, char *lat, char *lon, char *hdg, char *elev, pHold *sPtr);
void freeHoldList( pHold *sPtr);
unsigned int holdRead(char *szHoldFileName, pHold *sPtr );


#endif // NAV_IPLIB_H_INCLUDED
