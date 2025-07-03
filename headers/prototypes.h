/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:02:56 by leothoma          #+#    #+#             */
/*   Updated: 2025/07/02 04:55:24 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// main
void		minishell_launcher(t_data *data);

// init
void		init(t_data *data, char **envp);

// start parsing
int			parsing(t_data	*data);
// parsing input
int			check_quote_error(t_data *data);
void		var_env_handler(t_data *data);
char		*detect_var_env(char *input);
char		*get_my_env(t_data *data, char *str);
void		tokenisation(t_data *data);
void		type_tokens(t_data *data);
int			check_token_syntax(t_token *head);
void		extern_quote_handler(t_data *data);
void		affiche_token_test(t_token *token);
void		quote_check(t_data *data, int i);
int			count_var_len(char *input);
int			var_is_in_env(t_data *data, char *var, int len);
void		replace_var_env(t_data *data, char *var, int i, int len);
int			is_operator(char c);
int			is_space(char c);
char		*ft_itoa_stack(int n);
void		classify_cmd_and_args(t_token *token);
void	copy_var_name(char *dest, char *src);

// parsing tokinsation
void		init_token_rules(t_data *data);
void		init_token_types(t_data *data, char **tokens);
void		check_token_types(t_data *data, char *str);
void		split_tokens(t_data *data);
void		add_token_refacto(t_token **list, char *str);

// struct_utils
t_token		*find_last_token(t_token *token);
t_token		*find_penultimate_token(t_token *token);
int			count_token(t_token *token);
int			add_token(t_token **token, char *str, int type);
void		add_token_refacto(t_token **list, char *str);
void		print_list(t_data **data, char const *option);

// setup_signals
void		handle_sigint(int signum);
void		setup_signals(void);
t_mode		*get_shell_mode(void);
void		init_terminal(void);

// string_utils
int			ft_iscapitalise(char c);
char		*ft_join(int size, char **strs, char *sep);

// lexer
void		lexer(t_data *data, char *str);

// clear_utils
void		prepare_next_input(t_data *data, t_cmd **cmd);
void		clear_struct(t_token **tokens);
void		exit_program(t_data *data, char **args);
void		clear_double_array(char **str);
void		clear_cmds(t_cmd **cmds);

// EXEC
void		cd(t_data *data, char **args);
void		pwd(t_data *data, int fd);
void		ft_exit(t_data *data, char **args);
void		echo(t_data *data, char **args, int fd);
void		export(t_data *data, char **args);
void		unset(t_data *data, char **args);
void		env(t_data *data);
void		children_exec(t_exec *vars, t_data *data, int i);
void		init_exec_variables(t_exec *vars);
int			init_pipes(t_exec *vars);
void		start_children(t_exec *vars, t_data *data);
void		close_pipes(t_exec *vars);
void		wait_all_childrens(t_data *data, t_exec *vars);
void		restore_fds(t_exec *vars);
void		exec_builtin(int selector, char **args, t_data *data, t_dup dups);
void		free_arr(char **arr);
void		free_exec(t_exec *vars);
int			__exec_startup__(t_data *data, t_cmd *cmds);
int			exec_single(t_data *data, char *cmd, char **args);
int			setup_output_pipes(t_exec *vars, int i);
int			setup_input_pipes(t_exec *vars, int i);
int			fill_args(char **res, t_token **token, int *is_reddir, t_exec *vars);
int			handle_export_error(t_data *data, char **args);
int			count_env_size(char **env);
int			is_same_var(char *env_entry, char *arg);
int			var_name_len(char *arg);
int			check_if_builtin(char *str);
int			check_if_redir(t_token *token);
int			get_fd_from_reddir(char *fd_name, int type, t_exec *vars);
int			get_number_of_commands(t_token *token);
int			handle_single_builtin(t_exec *vars, t_data *data);
int			skip_first_tokens(t_token **token);
int			check_flag(char *arg);
char		*get_my_env2(t_data *data, char *str);
char		*join_args(char **args);
char		**alloc_args_array(int count);
char		**chang_args_ls(t_data *data, char **args);
void		parser(t_data *data, t_cmd **cmd_list);
void	close_unused_pipes(t_data *data, t_exec *vars, int i);
void	check_for_heredoc(t_exec *vars, t_cmd *cmds);
t_dup	handle_redir(t_redir *redir);
void	handle_dups(t_dup dups);
int	handle_single_builtin_new(t_exec *vars, t_cmd *commands, t_data *data);
void	get_reddirs(t_token *token, t_redir **redir_list);
int	check_for_redirs(t_token *token);
int	check_for_cmds(int type);
int	get_malloc_size_for_cmds(t_token *token);
void	add_redir_list(t_token *token, t_redir **redir_list);
char	**save_cmds_info(t_token *token, t_cmd *cmd_list);
int	add_cmd_list(t_data *data, t_token *token, t_cmd **cmd_list);
int	get_n_command(t_token *token);
void	advance_pointer(t_token **token);
void	clear_cmd_node(t_cmd *cmds);
int	open_fds(char *fd_name, int type);
void	fill_t_dups(t_dup *dups, int type, int fd);
