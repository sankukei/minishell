#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

// def struct
typedef struct s_token
{
	char			*str;
	int				type;
	char			*rules;
	struct s_token	*next;
}   t_token;

typedef struct s_data
{
	char			*input;
	t_token			*token;
}   t_data;



// main
void		minishell_launcher(t_data *data);

// parsing
void		parsing(t_data	*data);
void	init_token_rules(t_data *data);

// struct_utils
t_token		*find_last_token(t_token *token);
t_token		*find_penultimate_token(t_token *token);
int			count_token(t_token *token);
int			add_token(t_token **token, char *str, int type);
#endif
