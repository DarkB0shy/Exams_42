#include "get_next_line.h"

int main (int argc, char **argv)
{
  if (argc != 2)
    return (1 * printf("Utilizzo: ./a.out <FILE_DA_LEGGERE>\n"));
  int fd = open(argv[1], O_RDONLY);
  char  *line = get_next_line(fd);
  while (line)
  {
    printf("%s", line);
    free(line);
    line = get_next_line(fd);
  }
  close (fd);
  return (0);
}
