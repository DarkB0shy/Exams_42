#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
static int ft_strlen(char *str) {
  int   i = 0;
  while (str[i])
    i++;
  return (i);
}
static void    std_errore(char *str, char *err) {
  write(2, "error: ", 7);
  write(2, str, ft_strlen(str));
  if (err)
    write(2, err, ft_strlen(err));
  exit(write(2, "\n", 1));
}
static void    ft_execve(int argc, char **argv, char **env, int tmp) {
  argv[argc] = NULL;
  dup2(tmp, 0);
  close(tmp);
  execve(argv[0], argv, env);
  std_errore("cannot execute: ", argv[0]);
}
int main(int argc, char **argv, char **env) {
  argc = 0;
  int   pid = 0;
  int   fd[2];
  int   tmp = dup(0);

  while (argv[argc] && argv[argc + 1]) {
    argv = &argv[argc + 1];
    argc = 0;
    while (argv[argc] && strcmp(argv[argc], ";") && strcmp(argv[argc], "|"))
      argc++;
    if (argc != 0 && !strcmp(argv[0], "cd")) {
      if (!argv[1])
        std_errore("cd: bad arguments", NULL);
      if (chdir(argv[1]))
        std_errore("cd: cannot change directory to ", argv[1]);
    }
    else if (argc != 0 && (argv[argc] == NULL || !strcmp(argv[argc], ";"))) {
      pid = fork();
      if (!pid)
        ft_execve(argc, argv, env, tmp);
      else {
        close (tmp);
        while (waitpid(-1, NULL, WUNTRACED) != -1)
          ;
        tmp = dup(0);
      }
    }
    else if (argc != 0 && !strcmp(argv[argc], "|")) {
      pipe(fd);
      pid = fork();
      if (!pid) {
        dup2(fd[1], 1);
        close(fd[0]);
        close(fd[1]);
        ft_execve(argc, argv, env, tmp);
      }
      else {
        close(tmp);
        close(fd[1]);
        tmp = fd[0];
      }
    }
  }
  close(tmp);
  return (0);
}