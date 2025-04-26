
#include "../headers/minishell.h"

t_token *find_last_token(t_token *token)
{
		if (!token)
				return (NULL);
		while (token && token->next)
				token = token->next;
		return (token);
}

void    print_list(t_data **data, char const *option)
{

		t_token	*current;
		int		i;

	(void)option;
		i = 0;
		current = (*data)->token;
		while (current) 
		{
				printf("index : %d\n", i++);
				printf("string-> %s\n", current->str);
				// printf("TYPE-> %d\n", current->type);
				current = current->next;
		}
}

t_token    *find_penultimate_token(t_token *token)
{
		if (!token)
				return (NULL);
		while (token && token->next && token->next->next)
				token = token->next;
		return (token);
}

int     count_token(t_token *token)
{
		int		i;

		i = 0;
		if (!token)
				return (0);
		while (token && token->next)
		{
				token = token->next;
				i++;
		}
		return (i + 1);
}

int     add_token(t_token **token, char *str, int type)
{
		t_token    *new_token;
		t_token    *last_token;

		if (token == NULL)
				return (1);
		new_token = malloc(sizeof(t_token));
		if (!new_token)
				return (1);
		new_token->next = NULL;
	// new_token->str = malloc(ft_strlen(str) * sizeof(char));
	new_token->str = ft_strdup(str);
		new_token->type = type;
		if (*token == NULL)
			*token = new_token;
		else
		{
				last_token = find_last_token(*token);
				last_token->next = new_token;
		}
		return (0);
}
