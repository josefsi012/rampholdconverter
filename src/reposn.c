#include "reposn.h"

void readReposn( char *reposnIncludeFile )
{
  wxRegEx reHoldPosition( wxT( "'([A-Z]{4,})','([\\w]{2,3})',([-+]?[0-9]*\\.?[0-9]+),([-+]?[0-9]*\\.?[0-9]+)," ), wxRE_ADVANCED );
  wxRegEx reRampPosition( wxT( "'([A-Z]{4,})',([-+]?[0-9]*\\.?[0-9]+),([-+]?[0-9]*\\.?[0-9]+)," ), wxRE_ADVANCED );
  wxRegEx reCommon( wxT( ">([-+]?[0-9]*\\.?[0-9]+),([-+]?[0-9]*\\.?[0-9]+)" ), wxRE_ADVANCED );

  regex_t reHoldPosition, reRampPosition, reCommon;
  regmatch_t matched;
  FILE *fh;

  static char  szBuffer[256]="";
  unsigned int numHold = 0, holdNum;
  //char apt[AptSize], rwy[RwySize], lat[LatSize], lon[LonSize], hdg[HdgSize], elev[ElevSize];
  int i;

  /* Read hold file */
  if ( ( fh = fopen( reposnIncludeFile, "r" ) ) == NULL )
    {
      fprintf( stderr,"Cannot open reposn data file '%s'\n", reposnIncludeFile );
      return;
    }

//
//  Read the file into the local arrays. Limit the amount of data read
//  to the input variable *lpMaxInOut.
  while ( fgets( szBuffer, sizeof( szBuffer ), fh ) )
    {
      if ( szBuffer[0] != '*' || szBuffer[0] != 'c' )     //Comment line?
        {






        }
      else
        {
//      fprintf(stderr,"Ramp Data Comment Line %10.10s.", szBuffer );
        }
    }
  regfree(&reHoldPosition);
  regfree(&reRampPosition);
  regfree(&reCommon);
  fclose( fh );
  //return numHold;
}

