/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedef.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:03:53 by leothoma          #+#    #+#             */
/*   Updated: 2025/07/18 05:49:40 by amedenec         ###   ########.fr       */
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
	FD,
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

typedef struct s_values
{
	int	n_cmds;
	int	n_infiles;
	int	n_outfiles;
	int	n_heredocs;
}	t_values;

typedef struct s_redir
{
	int				type;
	char			*target;
	int				fd;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			**cmd;
	char			**path;
	t_redir			*redirs;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_token
{
	char			*str;
	int				type;
	struct s_token	*next;
}	t_token;

typedef struct s_exec
{
	pid_t	pid;
	int		fd;
	int		xd;
	int		old_stdin;
	int		old_stdout;
	int		is_builtin;
	int		is_reddir;
	int		heredoc;
	int		n_command;
	int		**pipes;
	int		status;
	int		heredoc_fd;
	int		heredoc_index;
	int		current_pipe_index;
	int		reddir_fd_type;
	char	*cmd;
	char	*reddir_fd_name;
	char	**args;
}	t_exec;

typedef struct s_data
{
	char		*input;
	t_boolen	single_quote;
	t_boolen	double_quote;
	t_token		*token;
	t_token		*front_token;
	t_cmd		*cmd;
	t_exec		*vars;
	char		**env;
	int			test;
	int			n_commands;
	int			last_exit_status;
}	t_data;



typedef struct s_dup
{
	int	heredoc;
	int	infile_redir;
	int	infile_fd;
	int	outfile_redir;
	int	outfile_fd;
}	t_dup;
