#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//typedef struct s_fct t_fct;
//typedef struct s_commut t_commut;

typedef struct s_bloc t_bloc;
typedef struct s_data t_data;
typedef struct s_ref t_ref;

typedef struct s_char t_char;
typedef struct s_int t_int;
typedef int (**t_ptrtab)();

struct s_bloc //'{' '('
{
  t_ref *method;
  int **pc;//M2, M1
  t_data *data;

  //index de pc
  int bl;//M2 ';'
  int bc;//M1
  //index_max de pc
  int bl_max;
  int bc_max;

  t_bloc *next;
  /*	M3
    liste chaine de block
    ou 
    tableau de structure block
  */
};

struct s_ref
{
  t_ptrtab tab_ref;
};

struct s_data
{
  t_char *stack_c;
  t_int *stack_i;
};

struct s_char
{
  char *name;
  char *var;
  char type;

  t_char *next_c;
  t_int *next_i;
};

struct s_int
{
  char *name;
  int *var;
  char type;

  t_char *next_c;
  t_int *next_i;
};

t_data *recup_stack(t_data *stack);
int *recup_pipe_creat(int *pipe);
int *recup_pipe_init(int *pipe);
char whoistype();
char *read_buffer(int *fd);
void init();
void creat_char();
void init_char();
char *ft_fd_in_str(int fd);
