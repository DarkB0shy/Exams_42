#ifndef GNL_H
# define GNL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>

# ifndef B_S
# define B_S 42
# endif

char    *gnl(int fd);

#endif
