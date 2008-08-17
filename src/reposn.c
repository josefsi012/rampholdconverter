#include "reposn.h"

#define RAMP_REG_COUNT 4
#define HOLD_REG_COUNT 5
#define COMMON_REG_COUNT 3

void readReposn( char *reposnIncludeFile )
{
  int err;
  char buf[ BUFSIZ ], copybuf[ BUFSIZ ];
  char *szHoldPosition =  "'([A-Z]{4,})','([\\w]{2,3})',([-+]?[0-9]*\\.?[0-9]+),([-+]?[0-9]*\\.?[0-9]+),";
  char *szRampPosition = "'([A-Z]{4,})',([-+]?[0-9]*\\.?[0-9]+),([-+]?[0-9]*\\.?[0-9]+),";
  char *szCommon = ">([-+]?[0-9]*\\.?[0-9]+),([-+]?[0-9]*\\.?[0-9]+)";

  regex_t reHoldPosition, reRampPosition, reCommon;
  regmatch_t rampMatches[RAMP_REG_COUNT], holdMatches[HOLD_REG_COUNT], commonMatches[COMMON_REG_COUNT];
  FILE *fh;

  static char  szBuffer[256]="";
  unsigned int numHold = 0, holdNum;
  //char apt[AptSize], rwy[RwySize], lat[LatSize], lon[LonSize], hdg[HdgSize], elev[ElevSize];
  int i;

  if ( ( err = regcomp( &reHoldPosition, rightWay, REG_EXTENDED ) ) ) {
    regerror( err, &reg, buf, BUFSIZ );
    fprintf( stderr, "%s\n", buf );
    exit( EXIT_FAILURE );
  }

  if ( ( err = regcomp( &reRampPosition, rightWay, REG_EXTENDED ) ) ) {
    regerror( err, &reg, buf, BUFSIZ );
    fprintf( stderr, "%s\n", buf );
    exit( EXIT_FAILURE );
  }

  if ( ( err = regcomp( &reCommon, rightWay, REG_EXTENDED ) ) ) {
    regerror( err, &reg, buf, BUFSIZ );
    fprintf( stderr, "%s\n", buf );
    exit( EXIT_FAILURE );
  }

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

      if ( ( regexec( &reHoldPosition, reHoldPosition, HOLD_REG_COUNT, holdMatches, 0 ) ) == 0 )
      {
        int i, n, charCount;
        for ( i = 1; i < HOLD_REG_COUNT; i++ ) {
          if ( -1 != ( n = matches[i].rm_so ) ) {
            charCount = matches[i].rm_eo - matches[i].rm_so; /* Grab the char count for last match */
            printf( "\tThe position numbers are: %d %d\n\tCharacter Count: %d\n",matches[i].rm_so,matches[i].rm_eo, charCount );
            strncpy( copybuf, str+n, charCount );
            copybuf[charCount] = 0;
            printf( "Match number %d: %s\n\n", i, copybuf );
          }
        }
      }
    }
    else
    {
//      fprintf(stderr,"Ramp Data Comment Line %10.10s.", szBuffer );
    }
  }
  regfree( &reHoldPosition );
  regfree( &reRampPosition );
  regfree( &reCommon );
  fclose( fh );
  //return numHold;
}

