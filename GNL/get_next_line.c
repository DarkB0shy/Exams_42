#include "get_next_line.h"

char    *get_next_line(int fd)
{
  static char   buffer[BUFFER_SIZE];    // Per salvare caratteri da fd
  static int    buffer_pos = -1;        // Per ciclare su buffer[BUFFER_SIZE]
  static int    max_buffer_pos;         // Per salvare il # di caratteri letti con read
  char          *line = NULL;           // Valore di ritorno
  int           line_pos = 0;           // Per riempire line
  char          *tmp_line;              // Per continuare a riempire line se buffer[BUFFER_SIZE] non termina con \n
  int           i;                      // Per ciclare su tmp_line

  if (BUFFER_SIZE < 1 || fd < 0 || fd >= 1024)              // Input check
      return (NULL);
  if (buffer_pos == -1 || buffer_pos == max_buffer_pos)     // Inizializzazione variabili statiche
  {
      max_buffer_pos = read(fd, &buffer, BUFFER_SIZE);
      buffer_pos = 0;
  }
  if (max_buffer_pos < 1)
      return (NULL);                                        // In caso di errore di lettura ritorna NULL
  line = malloc(sizeof(char) * (max_buffer_pos + 1));       // Malloc valore di ritorno
  while (buffer_pos < max_buffer_pos)
  {
      line[line_pos++] = buffer[buffer_pos++];
      if (line[line_pos - 1] == '\n')
          break;
      if (buffer_pos == max_buffer_pos)                     // Aggiorna variabilii statiche se buffer_pos == BUFFER_SIZE
      {
          max_buffer_pos = read(fd, &buffer, BUFFER_SIZE);
          buffer_pos = 0;
          line[line_pos] = '\0';
          return (line);
      }
  }
  line[line_pos] = '\0';
  return (line);
}
