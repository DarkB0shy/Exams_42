#include "gnl.h"

char    *gnl(int fd)
{
  static char   buffer[B_S];
  static int    buffer_pos = -1;
  static int    max_buffer_pos = 0;
  char  *line = NULL;
  int   line_pos = 0;

  if (B_S < 1 || fd < 0 || fd >= 1024)
    return (NULL);
  if (buffer_pos == -1 || buffer_pos == max_buffer_pos)
  {
    max_buffer_pos = read(fd, &buffer, B_S);
    buffer_pos = 0;
  }
  if (max_buffer_pos < 1)
    return (NULL);
  line = malloc (sizeof(char) * (max_buffer_pos + 1));
  line[line_pos] = '\0';
  while (buffer_pos < max_buffer_pos)
  {
    line[line_pos++] = buffer[buffer_pos++];
    if (line[line_pos - 1] == '\n')
      break;
    if (buffer_pos == max_buffer_pos)
    {
      max_buffer_pos = read(fd, &buffer, B_S);
      buffer_pos = 0;
      break;
    }
  }
  line[line_pos] = '\0';
  return (line);
}

int main (int argc, char **argv)
{
  if (argc != 2)
    printf("Insert the file to read line per line\n");
  else
  { 
    int fd = open(argv[1], O_RDONLY);
    char *line = gnl(fd);
    while (line)
    {
      printf("%s", line);
      free(line);
      line = gnl(fd);
    }
    free(line);
    close(fd);

  }
  printf("\n");
  return (0);
}
