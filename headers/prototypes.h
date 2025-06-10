/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sankukei <sankukei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:02:56 by leothoma          #+#    #+#             */
/*   Updated: 2025/06/11 00:13:50 by sankukei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// main
void		minishell_launcher(t_data *data);

// init
void		init(t_data *data, char **envp);

// start parsing
int		parsing(t_data	*data);

// parsing input
int	        check_quote_error(t_data *data);
void		var_env_handler(t_data *data);
char		*detect_var_env(char *input);
char        *get_my_env(t_data *data, char *str);


// parsing tokinsation
void		init_token_rules(t_data *data);
void		init_token_types(t_data *data, char **tokens);
void		check_token_types(t_data *data, char *str);
void		split_tokens(t_data *data);

// struct_utils
t_token		*find_last_token(t_token *token);
t_token		*find_penultimate_token(t_token *token);
int			count_token(t_token *token);
int			add_token(t_token **token, char *str, int type);
void		add_token_refacto(t_token **list, char *str);
void		print_list(t_data **data, char const *option);

// setup_signals
void	handle_sigint(int signum);
void	setup_signals(void);


// string_utils
int     ft_iscapitalise(char c);
char	*ft_join(int size, char **strs, char *sep);


// lexer
void	lexer(t_data *data, char *str);

// clear_utils
void	prepare_next_input(t_data *data);
void	clear_struct(t_token **tokens);
void	exit_program(t_data *data);
void	clear_double_array(char **str);

// EXEC
int	__exec_startup__(t_data *data);
void    cd(char **args);
void    pwd(char **args, int fd);
char    *get_my_env2(t_data *data, char *str);
void	ft_exit(t_data *data, char **args);
void	echo(char **args, int fd);
int     handle_export_error(t_data *data, char **args);
void    export(t_data *data, char **args);
int     count_env_size(char **env);
int     is_same_var(char *env_entry, char *arg);
int     var_name_len(char *arg);
void	unset(t_data *data, char **args);
void	env(t_data *data);
char	**chang_args_ls(t_data *data, char **args);

