#include"headers.h"

char **in()
{
	int in_size=1024,x=0;
  char *buffer=(char*)malloc(1024);
  int c;

  if (!buffer) {
    perror("buffer");
    environ = 1;
    return 0;
  }

  while (1) {
    c = getchar();
    
    if(c==EOF && x==0)
      {
        printf("\n");
        exit(EXIT_SUCCESS);
      }

    if (c == EOF || c == '\n') {
      buffer[x] = '\0';
      return parse_semi(buffer);
    } else buffer[x] = c;
    x++;

    if (x>=in_size) {
      in_size+=1024;
      buffer = realloc(buffer,in_size);
      if (!buffer) {
        environ = 1;
        perror("buffer");
        return 0;
      }
    }
  }
}

