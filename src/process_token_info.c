#include "../headers/minishell.h"

#define INPUT_RULES 	"FD"
#define HEREDOC_RULES 	"ARGS"
#define TRUNC_RULES 	"FD"
#define APPEND_RULES 	"FD"
#define PIPES_RULES 	"CMD"
#define CMD_RULES 	"ARGS|PIPES|REDIR"
#define ARG_RULES 	"ARGS|PIPES"

int	check_rules(int	type, int next)
{
	if (type == 1 && next != FD)
		return (1);
	else if (type == 2 && next != ARGS)
		return (1);
	else if (type == 3 && next != FD)
		return (1);
	else if (type == 4 && next != FD)
		return (1);
	else if (type == 5 && next != CMD)
		return (1);
	else if (type == 6 && (next != ARGS || next != PIPES || next != REDIR))
		return (1);
	else if (type == 7 && (next != ARGS || next != PIPES))
		return (1);
	return (0);
}

int	process(t_token *token)
{
	while (token && token->next)
	{
		if (!(check_rules(token->next)))
			return (FALSE);
		token = token->next;
	}
	return (TRUE);
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
