/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedef.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leothoma <sankukei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:03:53 by leothoma          #+#    #+#             */
/*   Updated: 2025/06/16 15:19:53 by leothoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/types.h>

typedef enum s_type
{
	HEREDOC = 1,
	APPEND,
	INPUT,
	TRUNC,
	PIPE,
	CMD,
	ARG,
}	t_type;

typedef enum s_mode
{
    MODE_MAIN,
    MODE_HEREDOC,
    MODE_CHILD,
    MODE_IGNORE
}	t_mode;

typedef enum s_boolen
{
	false,
	true,
}	t_boolen;

typedef struct s_token
{
	char			*str;
	int				type;
	struct s_token	*next;
}	t_token;

typedef struct s_data
{
	char		*input;
	t_boolen	single_quote;
	t_boolen	double_quote;
	t_token		*token;
	t_token		*front_token;
	char		**env;
	int			test;
	int			last_exit_status;
}	t_data;

typedef struct s_exec
{
	pid_t	pid;
	int		fd;
	int		xd;
	int		old_stdin;
	int		old_stdout;
	int		is_builtin;
	int		is_reddir;
	int		is_heredoc;
	int		n_command;
	int		**pipes;
	int		status;
	int		heredoc_fd;
	char	*cmd;
	char	**args;
}	t_exec;
