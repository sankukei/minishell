#include "../headers/minishell.h"

#define INPUT_RULES 	"FD"
#define HEREDOC_RULES 	"ARGS"
#define TRUNC_RULES 	"FD"
#define APPEND_RULES 	"FD"
#define PIPES_RULES 	"CMD"
#define CMD_RULES 	"ARGS|PIPES|REDIR"
#define ARG_RULES 	"ARGS|PIPES"


int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*dup_str(char *str)
{
	char	*res;
	char	*ptr;

	res = (char *)malloc(ft_strlen(str) + 1);
	if (!res)
		return (NULL);
	ptr = res;
	while (*str)
		*ptr++ = *str++;
	*ptr= '\0';
	return (res);
}

void	init_token_rules(t_data *data)
{
	int	type;
	
	type = data->token->type;
	if (type == 1)
		data->token->rules = dup_str(INPUT_RULES);
	else if (type == 2)
		data->token->rules = dup_str(HEREDOC_RULES);
	else if (type == 3)
		data->token->rules = dup_str(TRUNC_RULES);
	else if (type == 4)
		data->token->rules = dup_str(APPEND_RULES);
	else if (type == 5)
		data->token->rules = dup_str(PIPES_RULES);
	else if (type == 6)
		data->token->rules = dup_str(CMD_RULES);
	else if (type == 7)
		data->token->rules = dup_str(ARG_RULES);
}

/* 
 * echo "hello" >> text.txt
 *  6	   7	4     7
 * types => {
 * 	1 = INPUT (<);
 * 	2 = HEREDOC (<<);
 * 	3 = TRUNC (>);
 * 	4 = APPEND (>>);
 * 	5 = PIPES (|);
 * 	6 = CMD (ex: 'ls');
 * 	7 = ARG (ex: ls '-l');
 * }

	1 = [
		"FD"
	]
	2 = [
		"ARGS"
	]
	3 = [
		"FD"
	]
	4 = [
		"FD"
	]
	5 = [
		"CMD",
	]
	6 = [
		"ARGS",
		"PIPES",
		"REDIR[>, >>]"

	]
	7 = [
		"PIPES",
		"REDIR[>, >>]",
	]

	minishell> : [CMD / REDIRECTION] [ARG] ...

*/
