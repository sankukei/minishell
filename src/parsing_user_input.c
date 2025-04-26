/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_user_input.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 02:41:26 by amedenec          #+#    #+#             */
/*   Updated: 2025/04/26 20:28:09 by amedenec         ###   ########.fr       */
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
	while (*input != ' ' && *input  != '\0' && (ft_isalnum(*input) == 1 || *input == '_')) // a voir si il faut mettre '\0'
	{
		len++;
		input++;
	}
	return (len);
}
void	replace_var_env(t_data *data, char *var, int i, int len)
{
	//TODO
	int		len_new_input;
	char	*dest;
	char	*ptr;

	len_new_input = ft_strlen(data->input) + ft_strlen(var) - (len + 1);
	dest = malloc(sizeof(char) * len_new_input + 1);
	if (!dest)
	{
		// TODO free all clear exit;
		exit(1);
	}
	ptr = dest;
	memset(dest, '\0', len_new_input);
	dest[len_new_input] = '\0';
	ft_strlcpy(dest, data->input, i + 1);
	ft_strlcpy(dest + i, var, ft_strlen(var) + 1);
	ft_strlcpy(dest + i + ft_strlen(var), data->input + i + len + 1, len_new_input);
	data->input = dest;

}

int	var_is_in_env(t_data *data, char *var)
{
	char	**env;
	int		i;
	
	i = 0;
	env = data->env;
	while (env[i])
	{
		//printf("je check la\n");
		if (ft_strncmp(var, env[i], ft_strlen(var)) == 0)
			return (1);			
		i++;
	}
	return (0);
}

static void	quote_check(t_data *data, int i)
{
	if ((data->input[i] == '\"') && (data->single_quote == false))
			data->double_quote = !(data->double_quote);
	else if ((data->input[i] == '\'') && (data->double_quote == false))
			data->single_quote = !(data->single_quote);
}

char *get_my_env(t_data *data, char *str)
{
	char **env;
	int	i;
	int	j;
	
	i = 0;
	j = 0;
	env = data->env;
	while (env[i])
	{
		//printf("je check la\n");
		if (ft_strncmp(str, env[i], ft_strlen(str)) == 0)
		{
			while (env[i][j] != '=')
				j++;
			j++;
			return (&env[i][j]);
		}			
		i++;
	}
	return (NULL);
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
			if (len && var_is_in_env(data, var))
			{
				var = get_my_env(data, var);
				replace_var_env(data, var, i, len);
				input = data->input;
			}
		}
		i++;
	}
}

void	check_quote_error(t_data *data)
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
		printf("une quote n'est pas ferme\n");
		exit(0);
	}
}

///////////////////////////////////////////////////////

int	is_space(char c)
{
	return (c == ' '); // mettre tout les types d'espaces
}
int	is_operator(char c)
{
	return (c == '<' || c == '>' || c == '|');
}

int	skip_quote(char *str, int i)
{
	char	quote;

	quote = str[i++];
	while (str[i] && str[i] != quote)
		i++;
	i--;
	//if (str[i] == quote) // a pas enlever dans le doute
	//	i++;
	return (i);
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
			token = extract_token(data->input, &i); // a faire
		if (token && *token)
			add_token_refacto(&list, token);
		else
			free(token);
		data->token = list;
	}
}
void	affiche_token_test(t_token *token)
{
	int	i;

	i = 1;
	while (token)
	{
		printf("token numero %d: %s\n", i++, token->str);
		token = token->next;
	}
}


void	parsing(t_data	*data)
{
	check_quote_error(data);
	var_env_handler(data);
	tokenisation(data);
	affiche_token_test(data->token);
	//lexer(data, data->input); // faire
}

/*
objectif pour la tokenisation
parser l input en sautant tout les espaces, puis check si c'est
un token < > << >> ou | sinon c'est un token classque
Pour les tokens classique tu parses jusqu'a croiser un autre espace ou un < > << >> |
le truc check dans les token classique
c'est les quotes, si on tombe dessus on ignore tout jusqu'au prochaine
du meme type
*/
