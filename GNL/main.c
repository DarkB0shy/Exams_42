#include "gnl.h"

int main(int argc, char **argv)
{
  if (argc != 2)
    printf("Usage: ./a.out <file_to_read>\n");
  int fd = open(argv[1], O_RDONLY);
  char  *line = gnl(fd);
  while (line)
  {
    printf("%s", line);
    free(line);
    line = gnl(fd);
  }
  free(line);
  close(fd);
  return(0);
}
