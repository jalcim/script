#include "context.h"

t_data *recup_stack(t_data *stack)
{
  static t_data *save_stack = NULL;

  if (stack)
    save_stack = stack;
  return (save_stack);
}

int *recup_pipe_creat(int *pipe)
{
  static int *save_pipe = NULL;

  if (pipe)
    save_pipe = pipe;
  else if (pipe == (int *)-1)
    {
      close(save_pipe[0]);
      close(save_pipe[1]);
    }
  return (save_pipe);
}

int *recup_pipe_init(int *pipe)
{
  static int *save_pipe = NULL;

  if (pipe)
    save_pipe = pipe;
  else if (pipe == (int *)-1)
    {
      close(save_pipe[0]);
      close(save_pipe[1]);
    }
  return (save_pipe);
}

char whoistype()
{
  int *fd;
  char type;

  fd = recup_pipe_creat(NULL);
  read(fd[0], &type, 1);
  if (type != 'c' && type != 'i')
    printf("error type\n");//error
  return (type);
  //lire 1 octer sur la pipe_creat et le renvoyer;
}

char *read_buffer(int *fd)
{
  char *buffer;

  buffer = ft_fd_in_str(fd[0]);
  if (!buffer)
    ;//error
  return (buffer);
  //lire sur la pipe et renvoyer jusqu'au \0
}

static void ft_fusion(char **buffer, char *tmp);
char *ft_fd_in_str(int fd)
{
  char *tmp;
  char *buffer;
  int compt;

  compt = -1;
  tmp = malloc(1024);
  buffer = malloc(1);
  buffer[0] = '\0';
  while (read(fd, &tmp[++compt], 1) > 0 && tmp[compt] != '\0')
    {
      if (compt == 1022)
        {
	  tmp[compt + 1] = '\0';
	  ft_fusion(&buffer, tmp);
	  bzero(tmp, 1024);
	  compt = -1;
        }
    }
  tmp[compt] = '\0';
  ft_fusion(&buffer, tmp);
  free(tmp);
  return (buffer);
}

static void ft_fusion(char **buffer, char *tmp)
{
  if (!((*buffer) = (char *)realloc((*buffer), (strlen((*buffer)) + strlen(tmp)) + 1)))
    printf("error realloc \n");
  strcat((*buffer), tmp);
}
