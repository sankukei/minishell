#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

// def struct
typedef enum s_boolen
{
	false,
	true,
}	t_boolen;

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
	t_boolen		single_quote;
	t_boolen		double_quote;
	t_token			*token;
}   t_data;



// main
void		minishell_launcher(t_data *data);

// start parsing
void		parsing(t_data	*data);

// parsing input
void		check_quote_error(t_data *data);
void		var_env_handler(t_data *data);
char		*detect_var_env(char *input);

// parsing tokinsation
void		init_token_rules(t_data *data);

// struct_utils
t_token		*find_last_token(t_token *token);
t_token		*find_penultimate_token(t_token *token);
int			count_token(t_token *token);
int			add_token(t_token **token, char *str, int type);

// string_utils
int     ft_iscapitalise(char c);

#endif
