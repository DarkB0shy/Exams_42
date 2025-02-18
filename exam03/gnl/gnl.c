#include "gnl.h"

char    *gnl(int fd)
{
  static char   buffer[B_S];
  static int    max_buffer_pos = 0;
  static int    buffer_pos = -1;
  char          *line;
  int           line_pos = 0;

  if (B_S < 1 || fd == -1)
    return (NULL);
  if (buffer_pos == max_buffer_pos || buffer_pos == -1)
  {
    max_buffer_pos = read(fd, &buffer, B_S);
    buffer_pos = 0;
  }
  if (max_buffer_pos < 1)
    return (NULL);
  line = malloc(sizeof(char) * (1 + max_buffer_pos));
  line[line_pos] = '\0';
  while (buffer_pos < max_buffer_pos)
  {
    line[line_pos++] = buffer[buffer_pos++];
    if (line[line_pos - 1] == '\n')
      break;
  }
  line[line_pos] = '\0';
  return (line);
}

int main (int argc, char **argv)
{
  if (argc != 2)
    printf("No Johnny");
  else
  {
    int fd = open(argv[1], O_RDONLY);
    char    *str = gnl(fd);
    while (str)
    {
      printf("%s", str);
      free(str);
      str = gnl(fd);
    }
    free(str);
    close(fd);
  }
  printf("\n");
  return (0);
}
