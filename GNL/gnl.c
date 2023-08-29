#include "gnl.h"

char    *gnl(int fd)
{
  static char   buffer[B_S];
  static int    buffer_pos = -1;
  static int    max_buffer_pos;
  char          *line = NULL;
  char          *tmp_line;
  int           line_pos = 0;

  if (B_S < 1 || fd < 0 || fd >= 1024)
    return (NULL);
  if (buffer_pos == -1 || buffer_pos == max_buffer_pos)
  {
    max_buffer_pos = read(fd, &buffer, B_S);
    buffer_pos = 0;
  }
  if (max_buffer_pos < 1)
    return (NULL);
  line = malloc(sizeof(char)*(max_buffer_pos + 1));
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
      line[line_pos] = '\0';
      return (line);
    }
  }
  line[line_pos] = '\0';
  return (line);
}
