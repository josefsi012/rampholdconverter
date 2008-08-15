#include "reposn.h"
#include <stdio.h>

int main( int argc, char **argv){
  char buff1[255] = "Hello world from New Jersey!! !!! !!!!!";
  char buff2[255];
  
  removeSpaces( buff1, buff2 );
  printf("String 1 %s\nString 2 %s\n", buff1, buff2);
  return 0;
}  

