#include "context.h"
int main()
{
  int *fd;
  t_data *stack;

  init();

  if (!(fd = recup_pipe_creat(NULL)))
    printf("error recup pipe creat\n");
  write(fd[1], "c", 1);
  write(fd[1], "variable1\0", 10);
  if ('c' == whoistype())
    creat_char();

  if (!(fd = recup_pipe_init(NULL)))
    printf("error recup pipe init\n");
  write(fd[1], "variable1\0", 10);
  write(fd[1], "yoooo man\0", 10);
  init_char();

  if (!(stack = recup_stack(NULL)))
    printf("error recup stack\n");
  if (stack && stack->stack_c && stack->stack_c->name)
    printf("name = :%s:\n", stack->stack_c->name);
  if (stack && stack->stack_c && stack->stack_c->var)
    printf("value = :%s:\n", stack->stack_c->var);
  //  recup_pipe_creat((int *)-1);
  //recup_pipe_init((int *)-1);

  if (!(fd = recup_pipe_creat(NULL)))
    printf("error recup pipe creat\n");
  write(fd[1], "c", 1);
  write(fd[1], "variable2\0", 10);
  if ('c' == whoistype())
    creat_char();

  if (!(fd = recup_pipe_init(NULL)))
    printf("error recup pipe init\n");
  write(fd[1], "variable2\0", 10);
  write(fd[1], "yessai\0", 7);
  init_char();

  write(fd[1], "variable2\0", 10);
  write(fd[1], "yep\0", 4);
  concat_char();

  if (!(stack = recup_stack(NULL)))
    printf("error recup stack\n");
  if (stack && stack->stack_c && stack->stack_c->name)
    printf("name = :%s:\n", stack->stack_c->name);
  if (stack && stack->stack_c && stack->stack_c->var)
    printf("value = :%s:\n", stack->stack_c->var);

  recup_pipe_creat((int *)-1);
  recup_pipe_init((int *)-1);
}

void init()
{
  int *pipe_creat;
  int *pipe_init;
  t_data *stack;

  pipe_creat = malloc(sizeof(int) * 2);
  pipe_init = malloc(sizeof(int) * 2);
  printf("init\n");
  pipe(pipe_creat);
  pipe(pipe_init);
  recup_pipe_creat(pipe_creat);
  recup_pipe_init(pipe_init);
  //initialisation et sauvegarde des pipes
  stack = (t_data *)malloc(sizeof(t_data));
  stack->stack_i = NULL;
  stack->stack_c = NULL;
  recup_stack(stack);
  //initialisation et sauvegarde de la liste
}

void creat_char()
{
  t_data *stack;
  t_char *car;
  int *fd;

  printf("creation de la variable\n");
  car = (t_char *)malloc(sizeof(t_char));
  if (!(fd = recup_pipe_creat(NULL)))
    printf("error recup pipe creat\n");
  car->name = read_buffer(fd);
  car->type = 'c';

  car->next_c = NULL;
  car->next_i = NULL;
  stack = recup_stack(NULL);
  if (stack->stack_c)
      car->next_c = stack->stack_c;
  else if (stack->stack_i)
    car->next_i = stack->stack_i;
  stack->stack_c = car;
  stack->stack_i = NULL;
}

void init_char()
{
  t_data *data;
  int *fd;

  printf("initialisation de la variable\n");
  if (!(fd = recup_pipe_init(NULL)))
    printf("error recup pipe init\n");
  data = data_select(fd);
  data->stack_c->var = read_buffer(fd);
}

void concat_char()
{
  t_data *data;
  int *fd;
  char *cat;

  printf("concatenation de la variable\n");
  if (!(fd = recup_pipe_init(NULL)))
    printf("error recup pipe concat\n");
  data = data_select(fd);
  cat = read_buffer(fd);
  ft_fusion(&data->stack_c->var, cat);
}

t_data *data_select(int *fd)
{
  t_data *stack;//stack alternative

  t_char *car;//alternateur
  t_int *tmp;

  char *name;

  name = read_buffer(fd);
  stack = recup_stack(NULL);

  car = NULL;
  tmp = NULL;
  if (stack->stack_c)
    car = stack->stack_c;
  else if (stack->stack_i)
    tmp = stack->stack_i;
  else
    printf("error no stack\n");
  while (((car && (car->next_c || car->next_i))
	  || (tmp && (tmp->next_c || tmp->next_i)))
	 && (car && strcmp(name, car->name)))
    {
      if (car->next_c)
	{
	  car = car->next_c;
	  tmp = NULL;
	}
      else if (tmp->next_c)
	{
	  car = tmp->next_c;
	  tmp = NULL;
	}
      else if (tmp->next_i)
	{
	  tmp = tmp->next_i;
	  car = NULL;
	}
      else if (car->next_i)
	{
	  tmp = car->next_i;
	  car = NULL;
	}
      else
	printf("error while\n");
    }
  if (car)
    {
      if (strcmp(name, car->name))
	printf("error variable no exist\n");
      stack = (t_data *)malloc(sizeof(t_data));
      stack->stack_c = car;
      return (stack);
    }
  if (tmp)
    {
      if (strcmp(name, tmp->name))
	printf("error variable no exist\n");
      stack = (t_data *)malloc(sizeof(t_data));
      stack->stack_i = tmp;
      return (stack);
    }
  return (NULL);
}
