/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_user_input.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 02:41:26 by amedenec          #+#    #+#             */
/*   Updated: 2025/06/04 02:36:12 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	*detect_var_env(char *input)
{
	int		len;
	char	*dest;
	char	*ptr;
	
	input++; // pour passer le $
	ptr = input;
	len = 0;
	if (*input == '?')
	{
		dest = malloc(sizeof(char) * 2);
		dest[0] = '?';
		dest[1] = '\0';
		return (dest);						// ca a l air de marcher
	}
	while (*input != ' ' && *input  != '\0' && (ft_isalnum(*input) == 1 || *input == '_')) // a voir si il faut mettre '\0'
	{
		len++;
		input++;
	}
	dest = malloc(sizeof(char) * len + 1);
	while (*ptr != ' ' && *ptr != '\0' && (ft_isalnum(*ptr) == 1 || *ptr == '_'))
		*dest++ = *ptr++;
	*dest = '\0';
	return (dest - len);
}
int	count_var_len(char *input)
{
	int		len;
	
	input++; // pour passer le $
	len = 0;
	if (*input == '?')
		return (1);
	while (*input != ' ' && *input  != '\0' && (ft_isalnum(*input) == 1 || *input == '_')) // a voir si il faut mettre '\0'
	{
		len++;
		input++;
	}
	return (len);
}
void	replace_var_env(t_data *data, char *var, int i, int len)
{
	int		len_new_input;
	char	*dest;

	len_new_input = ft_strlen(data->input) + ft_strlen(var) - (len + 1);
	dest = malloc(sizeof(char) * len_new_input + 1);
	if (!dest)
	{
		// TODO free all clear exit;
		exit(1);
	}
	memset(dest, '\0', len_new_input);
	dest[len_new_input] = '\0';
	ft_strlcpy(dest, data->input, i + 1);
	ft_strlcpy(dest + i, var, ft_strlen(var) + 1);
	ft_strlcpy(dest + i + ft_strlen(var), data->input + i + len + 1, len_new_input);
	data->input = dest;

}

int	var_is_in_env(t_data *data, char *var, int len)
{
	char	**env;
	int		i;
	
	i = 0;
	env = data->env;
	if (ft_strncmp(var, "?", 2) == 0)
		return (1);
	while (env[i])
	{
		if (ft_strncmp(var, env[i], len) == 0)
			return (1);			
		i++;
	}
	free(var);
	return (0);
}

static void	quote_check(t_data *data, int i)
{
	if ((data->input[i] == '\"') && (data->single_quote == false))
			data->double_quote = !(data->double_quote);
	else if ((data->input[i] == '\'') && (data->double_quote == false))
			data->single_quote = !(data->single_quote);
}
//######################
#include <limits.h>
static int	ft_nblen(long n)
{
	int	len;

	len = 0;
	if (n <= 0)
	{
		len++;
		n = -n;
	}
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static void	ft_fillnum(char *buf, long n, int len)
{
	buf[len] = '\0';
	if (n == 0)
		buf[0] = '0';
	if (n < 0)
	{
		buf[0] = '-';
		n = -n;
	}
	while (n > 0)
	{
		buf[--len] = (n % 10) + '0';
		n /= 10;
	}
}

char	*ft_itoa_stack(int n)
{
	static char	buf[12];
	long		nb;
	int			len;

	nb = (long)n;
	len = ft_nblen(nb);
	ft_fillnum(buf, nb, len);
	return (buf);
}


//#####################
char *get_my_env(t_data *data, char *str)
{
	char **env;
	int	i;
	int	j;
	
	i = 0;
	j = 0;
	env = data->env;
	if (ft_strncmp(str, "?", 2) == 0)
		return (free(str), ft_itoa_stack(data->last_exit_status));
	while (env[i])
	{
		//printf("je check la\n");
		if (ft_strncmp(str, env[i], ft_strlen(str)) == 0)
		{
			while (env[i][j] != '=')
				j++;
			j++;
			return (free(str), &env[i][j]);
		}			
		i++;
	}
	return (free(str), NULL);
}

void	var_env_handler(t_data *data)
{
	char	*input;
	char	*var;
	int		i;
	int		len;

	input = data->input;
	i = 0;
	while (input[i])
	{
		quote_check(data, i);
		if (input[i] == '$' && data->single_quote != true)
		{
			var = detect_var_env(&input[i]);
			len = count_var_len(&input[i]);
			if (len == 0)
				free(var);
			if (len && var_is_in_env(data, var, len))
			{
				var = get_my_env(data, var);
				replace_var_env(data, var, i, len);
				free(input);
				input = data->input;
			}
		}
		i++;
	}
}

int	check_quote_error(t_data *data)
{
	char		*input;

	input = data->input;
	while (*input)
	{
		if ((*input == '\"') && (data->single_quote == false))
			data->double_quote = !(data->double_quote);
		else if ((*input == '\'') && (data->double_quote == false))
			data->single_quote = !(data->single_quote);
		input++;
	}
	if (data->single_quote || data->double_quote)
	{
		data->single_quote = false;
		data->double_quote = false;
		printf("une quote n'est pas ferme\n");
		return (1);
	}
	return (0);
}

///////////////////////////////////////////////////////

int	is_space(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}
int	is_operator(char c)
{
	return (c == '<' || c == '>' || c == '|');
}

int	skip_quote(char *str, int i)
{
	char	quote;
	quote = str[i++];
	int	len;

	len = 0;
	//if (str[i] == quote) // le if est pour gerer le cas "" (extremement degeu mais ca passe)
	//{
	//	while (str[i] && str[i] != quote)
	//		i++;
	//	return (i);
	//}	
	while (str[i] && str[i] != quote)
	{
		i++;
		len++;
		//printf("jeskip\n");		
	}
	//i++;
	return (len + 2);
}

char	*extract_token(char *str, int *i)
{
	int		start;

	start = *i;
	while (str[*i] && !is_operator(str[*i]) && !is_space(str[*i]))
	{
		if (str[*i] == '\"' || str[*i] == '\'')
			*i += skip_quote(str, *i);
		else
			(*i)++;
	}
	//printf("start :%d\ni:%d\n", start, *i);
	return (ft_substr(str, start, *i - start));
}

void	tokenisation(t_data *data)
{
	int	i;
	char *token;
	t_token *list;
	
	list = NULL;
	i = 0;
	while (data->input[i])
	{
		while (is_space(data->input[i]))
			i++;
		if (is_operator(data->input[i]))
		{
			if ((data->input[i] == '<' || data->input[i] == '>') && data->input[i] == data->input[i + 1])
				token = ft_substr(data->input, i, 2), i += 2; // i ain't fixing that
			else
				token = ft_substr(data->input, i++, 1);
		}
		else
			token = extract_token(data->input, &i);
		if (token && *token)
			add_token_refacto(&list, token);
		else
			free(token);
	}
	data->token = list;
}

char	*remove_quote(char *str)
{
	int				i;
	int				l;
	unsigned char	c;
	char	*dest;

	dest = malloc(sizeof(char) * (ft_strlen(str) + 1));
	i = 0;
	l = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			c = str[i++];
			while (str[i] && str[i] != c)
				dest[l++] = str[i++];
			i++; // passer le deuxieme "
		}
		else
			dest[l++] = str[i++];
		dest[l] = 0;
	}
	free(str);
	return (dest);
}

void	extern_quote_handler(t_data *data)
{
	t_token	*token;
	char	*str;
	
	token = data->token;
	while (token)
	{
		str = token->str;
		token->str = remove_quote(str);
		token = token->next;
	}
}

void	affiche_token_test(t_token *token)
{
	int	i;

	i = 1;
	while (token)
	{
		printf("token numero %d: %s\ntype : %d\n", i++, token->str, token->type);
		token = token->next;
	}
}

void	put_hard_coded_type(t_data *data)
{
	t_token	*token;
	
	token = data->token;
	while (token)
	{
		if (token->str[0] == '|' && token->str[1] == '\0')
			token->type = PIPE;
		if (token->str[0] == '<' && token->str[1] == '\0')
			token->type = INPUT;
		if (token->str[0] == '>' && token->str[1] == '\0')
			token->type = TRUNC;
		if (token->str[0] == '<' && token->str[1] == '<' && token->str[2] == '\0')
			token->type = HEREDOC;
		if (token->str[0] == '>' && token->str[1] == '>' && token->str[2] == '\0')
			token->type = APPEND;
		token = token->next;
	}
}

void	classify_cmd_and_args(t_token *token)
{
	t_boolen	expect_cmd;
	t_type		prev_type;

	expect_cmd = true;
	prev_type = -1;
	while (token)
	{
		if (token->type == -1)
		{
			if (expect_cmd)
			{
				token->type = CMD;
				expect_cmd = false;
			}
			else if (prev_type >= HEREDOC && prev_type <= TRUNC)
				token->type = ARG; // redirection
			else
				token->type = ARG; // simple argument
		}
		if (token->type == PIPE)
			expect_cmd = true;
		prev_type = token->type;
		token = token->next;
	}
}


void	type_tokens(t_data *data)
{
	put_hard_coded_type(data);
	classify_cmd_and_args(data);
}
// check les tokens de gauche a droit
// mettre les hardcoded, | < > << >>
// si ce n'est pas un hardcoded, on regarde si on attend une commande
// si oui CMD
// sinon regarder si le token precedent est une redirection si oui, le token est un FD
// sinon c'est un ARG

int	parsing(t_data	*data)
{
	if (check_quote_error(data))
		return (1);
	var_env_handler(data);
	tokenisation(data);
	type_tokens(data);
	extern_quote_handler(data);
	affiche_token_test(data->token);
	return (0);
}
