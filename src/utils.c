void removeSpaces(const char *source, char *dest)
{
  unsigned int sourceLen = strlen(source);
  unsigned int i,j = 0;

  for( i = 0; i < sourceLen; i++)
  {
    if(source[i] != ' ') {
      dest[j] = source[i];
      j++;
    }
  }
  dest[j] = 0;
}
