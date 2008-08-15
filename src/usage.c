#include "usage.h"
#include "config.h"
#include "string.h"

void usage(const char *cmd)
{
  fprintf(stderr, "Usage: %s [-h] [-v] -r <ramp_file> -h <hold_file> -f <fortran_include_file>\n", cmd);
  fputs("\t-h\t\t\tGives this help display.\n",stderr);
  fputs("\t-v\t\t\tDisplays current version.\n",stderr);
  fputs("\t-r <ramp_file>\t\tRamp file (SimNT machine *.ndat file)\n", stderr);
  fputs("\t-h <hold_file>\t\tRamp file (SimNT machine *.ndat file)\n", stderr);
  fputs("\t-f <fortran_include>\tFortran include file (*.inc file)\n", stderr);
  fprintf(stderr, "\nCommand %s converts between SimNT based type ramp/hold\ndata to a NightHawk based Fortran inlclude file and vice-versa.\n", cmd);
  fprintf(stderr, "\nSend all bug reports to: %s\n", PACKAGE_BUGREPORT );
}

void getSupportedOptions(char *opts)
{
  char supportedOpts[] = "hvr:h:f:";
  free (opts);
  opts = strdup( supportedOpts );
}
