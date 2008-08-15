#include "nav_iplib.h"

/* Ramp */
void insertRamp( unsigned int num, char *apt, char *gate, char *lat, char *lon, char *hdg, char *elev, pRamp *sPtr )
{
  pRamp newPtr, previousPtr, currentPtr;

  newPtr = ( pRamp )malloc( sizeof( ramp ) );
  if ( newPtr != NULL )
  {
    newPtr->Num = num;

    strncpy( newPtr->Apt, apt, AptSize - 1 );
    newPtr->Apt[AptSize] = 0;

    strncpy( newPtr->Gate, gate, GateSize - 1 );
    newPtr->Gate[GateSize] = 0;

    strncpy( newPtr->Lat, lat, LatSize - 1 );
    newPtr->Lat[LatSize] = 0;

    strncpy( newPtr->Lon, lon, LonSize - 1 );
    newPtr->Lon[LonSize] = 0;

    strncpy( newPtr->Hdg, hdg, HdgSize - 1 );
    newPtr->Hdg[HdgSize] = 0;

    strncpy( newPtr->Elev, elev, ElevSize - 1 );
    newPtr->Elev[ElevSize] = 0;

    newPtr->nextPtr = NULL;

    previousPtr = NULL;
    currentPtr = *sPtr;

    while ( currentPtr != NULL && num > currentPtr->Num )
    {
      previousPtr = currentPtr;
      currentPtr = currentPtr->nextPtr;
    }

    if ( previousPtr == NULL )
    {
      newPtr->nextPtr = *sPtr;
      *sPtr = newPtr;
    }
    else
    {
      previousPtr->nextPtr = newPtr;
      newPtr->nextPtr = currentPtr;
    }
  }
  else
  {
    fprintf( stderr, "%s not inserted.  No memory available.\n", apt );
  }
}

/*---------------------------------------------------------------------------*/
void freeRampList( pRamp *sPtr )
{
  pRamp nextPtr, currentPtr;
  currentPtr = *sPtr;

  while ( currentPtr != NULL )
  {
    nextPtr = currentPtr->nextPtr;
    free( currentPtr );
    currentPtr = nextPtr;
  }
}

/*---------------------------------------------------------------------------*/

unsigned int rampRead( char *szRampFileName, pRamp *sPtr )
{
  FILE *fh;

  static char  szBuffer[256]="";
  unsigned int numRamp = 0, rampNum;
  char apt[AptSize], gate[GateSize], lat[LatSize], lon[LonSize], hdg[HdgSize], elev[ElevSize];
  int i;

  /* Read ramp file */
  if ( ( fh = fopen( szRampFileName, "r" ) ) == NULL ) {
    fprintf( stderr,"Cannot open Ramp IP data file '%s'\n", szRampFileName );
    return;
  }

//
//  Read the file into the local arrays. Limit the amount of data read
//  to the input variable *lpMaxInOut.
  while ( fgets( szBuffer, sizeof( szBuffer ), fh ) ) {
    if ( szBuffer[0] != '#' && strlen( szBuffer ) > 1 ) {   //Comment line?
      i = sscanf( szBuffer, " %d %s %s %s %s %s %s\n",
                  &rampNum, apt, gate, lat, lon, hdg, elev );

      if ( i == 7 ) {                            //Correct number of items?
        insertRamp( rampNum, apt, gate, lat, lon, hdg, elev, sPtr );
        numRamp++;
      }
      else {              //Data Mismatch
        fprintf( stderr,"Ramp Data Mismatch %s/%s.",
                 apt, gate );
      }
    }
    else {
//      fprintf(stderr,"Ramp Data Comment Line %10.10s.", szBuffer );
    }
  }
  fclose( fh );
  return numRamp;
}

/*-------------------------------------Hold----------------------------------*/

void insertHold( unsigned int num, char *apt, char *rwy, char *lat, char *lon, char *hdg, char *elev, pHold *sPtr )
{
  pHold newPtr, previousPtr, currentPtr;

  newPtr = ( pHold )malloc( sizeof( hold ) );
  if ( newPtr != NULL )
  {
    newPtr->Num = num;

    strncpy( newPtr->Apt, apt, AptSize - 1 );
    newPtr->Apt[AptSize] = 0;

    strncpy( newPtr->Rwy, rwy, RwySize - 1 );
    newPtr->Rwy[RwySize] = 0;

    strncpy( newPtr->Lat, lat, LatSize - 1 );
    newPtr->Lat[LatSize] = 0;

    strncpy( newPtr->Lon, lon, LonSize - 1 );
    newPtr->Lon[LonSize] = 0;

    strncpy( newPtr->Hdg, hdg, HdgSize - 1 );
    newPtr->Hdg[HdgSize] = 0;

    strncpy( newPtr->Elev, elev, ElevSize - 1 );
    newPtr->Elev[ElevSize] = 0;

    newPtr->nextPtr = NULL;

    previousPtr = NULL;
    currentPtr = *sPtr;

    while ( currentPtr != NULL && num > currentPtr->Num )
    {
      previousPtr = currentPtr;
      currentPtr = currentPtr->nextPtr;
    }

    if ( previousPtr == NULL )
    {
      newPtr->nextPtr = *sPtr;
      *sPtr = newPtr;
    }
    else
    {
      previousPtr->nextPtr = newPtr;
      newPtr->nextPtr = currentPtr;
    }
  }
  else
  {
    fprintf( stderr, "%s not inserted.  No memory available.\n", apt );
  }
}

void freeHoldList( pHold *sPtr )
{
  pHold nextPtr, currentPtr;
  currentPtr = *sPtr;

  while ( currentPtr != NULL )
  {
    nextPtr = currentPtr->nextPtr;
    free( currentPtr );
    currentPtr = nextPtr;
  }
}

unsigned int holdRead( char *szHoldFileName, pHold *sPtr )
{
  FILE *fh;

  static char  szBuffer[256]="";
  unsigned int numHold = 0, holdNum;
  char apt[AptSize], rwy[RwySize], lat[LatSize], lon[LonSize], hdg[HdgSize], elev[ElevSize];
  int i;

  /* Read hold file */
  if ( ( fh = fopen( szHoldFileName, "r" ) ) == NULL ) {
    fprintf( stderr,"Cannot open Hold IP data file '%s'\n", szHoldFileName );
    return;
  }

//
//  Read the file into the local arrays. Limit the amount of data read
//  to the input variable *lpMaxInOut.
  while ( fgets( szBuffer, sizeof( szBuffer ), fh ) ) {
    if ( szBuffer[0] != '#' && strlen( szBuffer ) > 1 ) {   //Comment line?
      i = sscanf( szBuffer, " %d %s %s %s %s %s %s\n",
                  &holdNum, apt, rwy, lat, lon, hdg, elev );

      if ( i == 7 ) {                            //Correct number of items?
        insertHold( holdNum, apt, rwy, lat, lon, hdg, elev, sPtr );
        numHold++;
      }
      else {              //Data Mismatch
        fprintf( stderr,"Hold Data Mismatch %s/%s.",
                 apt, rwy );
      }
    }
    else {
//      fprintf(stderr,"Hold Data Comment Line %10.10s.", szBuffer );
    }
  }
  fclose( fh );
  return numHold;
}

//---------------------------------------------

unsigned int holRead( char *szHoldFileName, pHold *sPtr )
{
  FILE *fh;

  static char  szBuffer[256]="";
  unsigned int numHold = 0, holdNum;
  char apt[AptSize], rwy[RwySize], lat[LatSize], lon[LonSize], hdg[HdgSize], elev[ElevSize];
  int i;

  /* Read hold file */
  if ( ( fh = fopen( szHoldFileName, "r" ) ) == NULL ) {
    fprintf( stderr,"Cannot open Ramp IP data file '%s'\n", szHoldFileName );
    return;
  }

//
//  Read the file into the local arrays. Limit the amount of data read
//  to the input variable *lpMaxInOut.
  while ( fgets( szBuffer, sizeof( szBuffer ), fh ) ) {
    if ( szBuffer[0] != '#' && strlen( szBuffer ) > 1 ) {   //Comment line?
      i = sscanf( szBuffer, " %d %s %s %s %s %s %s\n",
                  &holdNum, apt, rwy, lat, lon, hdg, elev );

      if ( i == 7 ) {                            //Correct number of items?
        insertHold( holdNum, apt, rwy, lat, lon, hdg, elev, sPtr );
        numHold++;
      }
      else {              //Data Mismatch
        fprintf( stderr,"Ramp Data Mismatch %s/%s.",
                 apt, rwy );
      }
    }
    else {
//      fprintf(stderr,"Ramp Data Comment Line %10.10s.", szBuffer );
    }
  }
  fclose( fh );
  return numHold;
}

/*
void n_ip_hold_read( long *lpMaxInOut,        char    *szHoldFileName,
                     long   **plaAptIdntOut,  long   **plaRwyIdntOut,
                     double **pdaLatOut,      double **pdaLonOut,
                     float  **pfaHdgOut,      float  **pfaElvOut )
{
  FILE *hFp;
  static char  szBuffer[256]="";
  int  i,k,iCnt,iIdx;
  union { char sz[5];
    long l;
  } tAptIdnt;
  union { char sz[5];
    long l;
  } tRwyIdnt;
  double dLat,dLon;
  float fHdg,fElv;

  long   *laAptIdntOut = *plaAptIdntOut;
  long   *laRwyIdntOut = *plaRwyIdntOut;
  double *daLatOut = *pdaLatOut;
  double *daLonOut = *pdaLonOut;
  float  *faHdgOut = *pfaHdgOut;
  float  *faElvOut = *pfaElvOut;

//
// Initialize the arrays to the default data.
//
  for ( i=0; i < *lpMaxInOut; i++ ) {
    laAptIdntOut[i] = BLANK_4;
    laRwyIdntOut[i] = BLANK_4;
    daLatOut[i]     = 0.0;
    daLonOut[i]     = 0.0;
    faHdgOut[i]     = 0.0;
    faElvOut[i]     = 0.0;
  }

//
// Open the IP datafile for read purposes. First check to see if it needs to be checked out of RCS.
//  If the file open fails, post an error to the log file.
//
  if ( ( hFp = fopen( szHoldFileName, "r" ) ) == NULL ) {
    fprintf( stderr,"Cannot open Hold Short IP data file '%s' with read permissions", szHoldFileName );
    *lpMaxInOut = 0;
    return;
  }

//
// Read the file into the local arrays. Limit the amount of data read to the input variable *lpMaxInOut.
//
  iCnt = 0;

  while ( fgets( szBuffer, sizeof( szBuffer ), hFp ) && ( iCnt < *lpMaxInOut ) ) {
    if ( szBuffer[0] != '#' && strlen( szBuffer ) > 1 ) {
      i = sscanf( szBuffer, " %d %s %s %lf %lf %f %f\n",
                  &iIdx,tAptIdnt.sz, tRwyIdnt.sz, &dLat, &dLon, &fHdg, &fElv );

      if ( i == 7 ) {                         //Correct number of items
        for ( k=strlen( tAptIdnt.sz ); k<4; k++ ) {
          tAptIdnt.sz[k] = ' ';
        }
        laAptIdntOut[iCnt] = tAptIdnt.l;

        for ( k=strlen( tRwyIdnt.sz ); k<4; k++ ) {
          tRwyIdnt.sz[k] = ' ';
        }
        laRwyIdntOut[iCnt] = tRwyIdnt.l;

        daLatOut[iCnt] = dLat;
        daLonOut[iCnt] = dLon;
        faHdgOut[iCnt] = fHdg;
        faElvOut[iCnt] = fElv;

        iCnt++;
      }
      else {
        fprintf( stderr,"Hold Data Mismatch %s/%s.",
                 tAptIdnt.sz, tRwyIdnt.sz );
      }
    }
    else {
//      fprintf(stderr,"Hold Data Comment Line %10.10s.", szBuffer );
    }
  }

  fclose( hFp );

  fprintf( stderr,"%d Hold ip's read.  %d ip's requested.", iCnt, *lpMaxInOut );

  *lpMaxInOut = i;

  return;
}

///////////////////////////////////////////////////////////////////////
//  n_ip_ramp_write -
//    Write the ramp information and returns the arrays to the host.
///////////////////////////////////////////////////////////////////////

void n_ip_ramp_write( long *lpMaxIn,          char    *szRampFileName,
                      long   **plaAptIdntIn,  long   **plaGateIdIn,
                      double **pdaLatIn,      double **pdaLonIn,
                      float  **pfaHdgIn,      float  **pfaElvIn )
{
  FILE *hFp;
  static char szString[256]="";
  static char szBuffer[1024];
  int  i, iCnt;
  union { char sz[5];
    long l;
  } tAptIdnt;
  union { char sz[5];
    long l;
  } tGateIdnt;

  long lFileLength,lOffset;

  long   *laAptIdntIn = *plaAptIdntIn;
  long   *laGateIdIn  = *plaGateIdIn;
  double *daLatIn     = *pdaLatIn;
  double *daLonIn     = *pdaLonIn;
  float  *faHdgIn     = *pfaHdgIn;
  float  *faElvIn     = *pfaElvIn;

//  Open the IP datafile for write purposes.
//  Check file access for existence and write priveledges.
//  The file must exist writeable, or be checked out locked in
//  order to update the file.  It will NOT be automatically checked out.
//  If the file open fails, set the number read to zero and return to
//  the calling program.
//

  if ( ( hFp = fopen( szRampFileName, "r+" ) ) == NULL ) {
    fprintf( stderr,"Cannot open Ramp IP data file '%s' with read/write permissions, check file permissions",
             szRampFileName );
    *lpMaxIn = 0;
    return;
  }

// Get the file length, and skip past the comment lines before beginning
// to write out the data.
//
  fseek( hFp, 0L, SEEK_END );
  lFileLength = ftell( hFp );
  fseek( hFp, 0L, SEEK_SET );

  lOffset initialization from incompatible pointer type - C= 0;
  while ( fgets( szBuffer, sizeof( szBuffer )-1, hFp ) ) {
    if ( szBuffer[0] == '#' ) {         //Comment line!
      lOffset = ftell( hFp );           //Start of next line
    }
    else {                              //Non-Comment line
      fseek( hFp, lOffset, SEEK_SET );  //Reset to this line
      break;
    }
  }

//  Write the data arrays out to the data file.
//  Limit the amount of data written to the input variable *lpMaxInOut.
//

  for ( i=0,iCnt=0; i < *lpMaxIn; i++ ) {
    tAptIdnt.l  = laAptIdntIn[i];    //Convert Airport Ident
    tGateIdnt.l = laGateIdIn[i];     //Convert Gate Ident
    if ( tGateIdnt.l == BLANK_4 )  tGateIdnt.l = 0x40404040;

    sprintf( szString, "%4d %4.4s %4.4s %13.8lf %13.8lf %7.3f %7.3f\n",
             i+1, tAptIdnt.sz, tGateIdnt.sz,
             daLatIn[i], daLonIn[i], faHdgIn[i], faElvIn[i] );

    if ( fputs( szString, hFp ) < 0 ) {
      fprintf( stderr,"Error writing to Ramp IP data file '%s' ",
               szRampFileName );
    }
    iCnt++;
  }

// If the new data is shorter than the original data, then there may
// be some left over characters left at the bottom of the file.
// Convert this remaining data to dummy comment lines.
//
  lOffset = ftell( hFp );
  while ( lOffset < lFileLength ) {
    if ( fputs( "###  Dummy Line - Can be removed\n", hFp ) < 0 ) {
      fprintf( stderr,"Error writing to Ramp IP data file '%s' ",
               szRampFileName );
    }
  }

//
// Close the file when completed.
//
  fclose( hFp );

  fprintf( stderr,"%d Ramp ip's written to %s.", i, szRampFileName );

  return;
}

void n_ip_hold_write( long *lpMaxIn,            char    *szHoldFileName,
                      long   **plaAptIdntIn,    long   **plaRwyIdntIn,
                      double **pdaLatIn,        double **pdaLonIn,
                      float  **pfaHdgIn,        float  **pfaElvIn )
{
  FILE *hFp;
  static char szString[256] ="";
  static char szBuffer[1024];
  int  i,iCnt;

  long lFileLength,lOffset;
  union { char sz[5];
    long l;
  } tAptIdnt;
  union { char sz[5];
    long l;
  } tRwyIdnt;

  long   *laAptIdntIn = *plaAptIdntIn;
  long   *laRwyIdntIn = *plaRwyIdntIn;
  double *daLatIn     = *pdaLatIn;
  double *daLonIn     = *pdaLonIn;
  float  *faHdgIn     = *pfaHdgIn;
  float  *faElvIn     = *pfaElvIn;

//  Open the IP datafile for write purposes.
//  Check the file access for existence and write priveledges.
//  The file must have both read/write access, and be checked out.
//  The file will not be automatically checked out.
//  If the file open fails, set the number read to zero and return to
//  the calling program.
//

  if ( ( hFp = fopen( szHoldFileName, "r+" ) ) == NULL ) {
    fprintf( stderr,"Cannot open Hold IP data file '%s' with read/write permissions, check file permissions",
             szHoldFileName );
    *lpMaxIn = 0;
    return;
  }

//  Get the file length, ans skip past the comment lines before
//  beginning to write out the data.
//
  fseek( hFp, 0L, SEEK_END );
  lFileLength = ftell( hFp );
  fseek( hFp, 0L, SEEK_SET );

  lOffset = 0;
  while ( fgets( szBuffer, sizeof( szBuffer )-1, hFp ) ) {
    if ( szBuffer[0] == '#' ) {              //Comment line!
      lOffset = ftell( hFp );                //Start of next line
    }
    else {                                   //Non-Comment line
      fseek( hFp, lOffset, SEEK_SET );       //Start of this line
      break;
    }
  }

//  Write the data arrays out to the data file.
//  Limit the amount of data written to the input variable *lpMaxInOut.
//

  for ( i=0,iCnt=0; i < *lpMaxIn; i++ ) {
    tAptIdnt.l = laAptIdntIn[i];
    tRwyIdnt.l = laRwyIdntIn[i];

    sprintf( szString, " %4d %4.4s %4.4s %13.8lf %13.8lf %7.3f %7.3f\n",
             i+1, tAptIdnt.sz, tRwyIdnt.sz,
             daLatIn[i], daLonIn[i], faHdgIn[i], faElvIn[i] );

    if ( fputs( szString, hFp ) < 0 ) {
      fprintf( stderr,"Error writing to Hold IP data file '%s' ",
               szHoldFileName );
    }
    iCnt++;
  }

// If the new data is shorter than the original data, then there may
// be some left over characters left at the bottom of the file.
// Conver this data to dummy comment lines.
//
  lOffset = ftell( hFp );
  while ( lOffset < lFileLength ) {
    if ( fputs( "###  Dummy Line - Can be removed\n", hFp ) < 0 ) {
      fprintf( stderr,"Error writing to Hold IP data file '%s' ",
               szHoldFileName );
    }
  }

//
// Close the file when completed.
//
  fclose( hFp );
  fprintf( stderr,"%d Hold ip's written to %s.", i, szHoldFileName );
  return;
}
*/

