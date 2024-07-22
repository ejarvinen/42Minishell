/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sataskin <sataskin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 13:21:33 by sataskin          #+#    #+#             */
/*   Updated: 2024/07/22 12:16:57 by sataskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"
# include <signal.h>
# include <termios.h>
# include <fcntl.h>

extern int	g_sig;

# define PINK "\001\e[95m\002"
# define PROMPT "MINISHELL💖~$ "
# define HDOC "> "
# define RESET "\001\e[0m\002"

# define READ_END 0
# define WRITE_END 1

typedef struct s_cmds
{
	char			**command;
	char			*path;
	char			*infile_name;
	char			**outfile_name;
	char			*heredoc;
	int				c_pid;
	int				fd_infile;
	int				*fd_outfile;
	int				id;
	int				commands;
	int				builtin;
	int				append;
	int				valid;
	int				exit_status;
	struct s_cmds	*next;
}					t_cmds;

typedef struct s_toks
{
	char			*content;
	int				file;
	int				command;
	int				argument;
	int				pipe;
	int				in_redir;
	int				out_redir;
	int				append;
	int				heredoc;
	int				heredoc_delimiter;
	int				id;
	struct s_toks	*next;
}					t_toks;

typedef struct s_env
{
	char			*key;
	char			*value;
	int				equal;
	int				index;
	struct s_env	*next;
}	t_env;

typedef struct s_mini
{
	t_env	*env;
	t_cmds	*cmds;
	char	**env_p;
	int		shlvl;
	int		saved_stdin;
	int		saved_stdout;
	int		exit_code;
	int		syntax;
	char	*pwd;
	char	*oldpwd;
}	t_mini;

/*				PARSING							*/

char	*ft_strtok(char *str);
void	token_cleanup(t_mini *shell, t_toks **tokens);
void	expand_dollar(t_mini *shell, t_toks **token, int *index,
			int in_doubles);
t_toks	*checker(char *input, t_mini *shell);
void	ft_lstadd_back_toks(t_toks **lst, t_toks *new);
void	ft_lstclear_toks(t_toks **lst);
t_toks	*ft_lstnew_toks(char *content);
int		ft_lstsize_toks(t_toks *lst);
t_toks	*ft_lstlast_toks(t_toks *lst);
void	identify_delims(t_toks **tokens);
void	identify_heredoc(t_toks **tokens);
void	recognize_file(t_toks **tokens);
void	identifier(t_toks **tokens);
void	identify_commands(t_toks **tokens);
void	identify_args(t_toks **tokens);
t_cmds	*ft_lstnew_pars(int index);
int		ft_lstsize_pars(t_cmds *lst);
t_cmds	*ft_lstlast_pars(t_cmds *lst);
void	ft_lstadd_back_pars(t_cmds **lst, t_cmds *new);
void	ft_lstclear_pars(t_cmds **lst);
int		in_quotes(char *token, size_t index);
void	no_blanks_cleanup(t_toks **tokens, t_mini *shell);
void	add_indexes(t_toks **tokens);
int		quote_check(char *token);
void	initialize_token(t_toks *new_node);
int		parser(char *rl, t_mini *shell);
int		struct_sum(t_toks *token);
void	build_command_list(t_toks **tokens, t_mini *shell);
void	add_builtin_info(t_cmds **cmds);
void	add_cmds_info(t_cmds **cmds);
char	**ft_splitstr(char const *s, char *c);
void	validate_commands(t_mini *shell, t_cmds *cmd);
int		validate_command(char *command, char **paths);
char	*full_path(char *path, char *command);
void	fill_cmd_info(t_cmds **cmds, t_toks **tokens);
void	fill_redir_info(t_mini *shell, t_cmds **cmds, t_toks **tokens);
int		syntax_check(t_toks *token, t_cmds **cmds, t_mini *shell);
int		syntax_checker(t_cmds **cmds, t_cmds *cmd,
			t_toks *token, t_mini *shell);
void	sure_pipe(t_toks *token);
void	sure_inredir(t_toks *token);
void	sure_outredir(t_toks *token);
void	sure_append(t_toks *token);
void	sure_hredir(t_toks *token);
int		redir_found(t_toks *token, int type);
int		doubredir_found(t_toks *token, int type);
void	check_append(t_toks *token, t_toks *next);
void	add_pipe_info(t_toks *token);
void	add_inredir_info(t_toks *token);
void	add_outredir_info(t_toks *token);
void	add_append_info(t_toks *token);
void	add_hredir_info(t_toks *token);
int		split_by_delim(t_toks **tokens, t_toks *token, char delim, char *divid);
int		identify_expandable(char *token);
t_env	*key_finder(char *var, t_env **envs);
void	build_list_delimstr(t_toks **addition, char *content,
			char **new_tokens, char *delim);
void	build_list(t_toks **addition, char *content,
			char **new_tokens, char delim);
void	strcpy_without_quotes(char *to, char *from, int fstquote, int sqnquote);
int		end_quote_index(t_mini *shell, t_toks **token, int *index);
int		get_index(char **array);
int		copy_filenames(char **to, char **from, char *new_file, int index);
void	parser_error(char *str);
int		add_heredoc_info(t_mini *shell, t_cmds *cmd, t_toks *token);
int		update_heredoc_info(t_mini *shell, t_cmds *cmd, t_toks *token);
t_toks	*add_infile_info(t_mini *shell, t_cmds *cmd, t_toks *token,
			int heredoc_flag);
t_toks	*add_outfile_info(t_mini *shell, t_cmds *cmd, t_toks *token,
			int append_flag);
void	expand_exit_code(t_toks **tokens, t_mini *shell);
int		identify_exitcode(t_mini *shell, t_toks **token, int *index,
			int in_doubles);
void	trim_token(t_toks **token);

/*				INPUT VALIDATION				*/

void	open_files(t_mini *shell, t_cmds **cmds);
void	close_files(t_cmds **cmds);
int		is_dir(char *command);
void	print_dirmsg(t_cmds *cmd, t_mini *shell);
void	dot_cmd(t_mini *shell, t_cmds *cmd);
void	nonexistent_cmd(t_mini *shell, t_cmds *cmd);
void	heredoc(t_mini *shell, t_cmds *cmd);
void	open_with_correct_flags(t_cmds *cmd, int index);

/*				FOR CREATING ENV				*/

void	ft_lstadd_back_mini(t_env **lst, t_env *new);
char	*get_key(t_mini *shell, char *str);
char	*get_value(t_mini *shell, char *envp);
void	add_input(t_mini *shell, t_env *node, char *envp);
t_env	*add_env(t_mini *shell, char **envp);

/*				FOR PANIC						*/

void	free_env(t_env *env);
void	ft_freearray(char **array);
void	free_data(t_mini *shell, char *message);
void	panic(t_mini *shell, int error_code);

/*				FOR SIGNALs						*/

void	par_sig_handler(int sig);
void	set_signal(int mode);
void	rl_replace_line(const char *text, int clear_undo);
void	rl_redisplay(void);
void	set_term(int num);

/*				FOR EXPORT						*/

void	print_export(t_env *env);
void	export(t_mini *shell, t_cmds *cmd);
int		lstsize(t_env *lst);
t_env	*find_next(t_env *env);
void	change_index(t_env **env);
void	update_index(t_env **env);
void	edit_env(t_mini *shell, t_env *node, char *str);
void	new_env(t_mini *shell, t_env **env, char *str);

/*				FOR UNSET						*/

void	ft_realunset(t_env **env, char *str);
void	ft_unset(t_mini *shell, t_cmds *cmd);

/*				CHECKING FOR VALID KEY			*/

int		validity(char *str, char *function);

/*				FOR PWD							*/

void	pwd(t_mini *shell, t_cmds *cmd);

/*				FOR ENV							*/

void	ft_env(t_mini *shell, t_cmds *cmd);
//char	**ltoa(t_env *env);
char	**ltoa(t_env **env);

/*				FOR CD							*/

void	ft_cd(t_mini *shell, t_cmds *cmd);
void	set_data(t_mini *shell, char **envp);

/*				BUILTIN ERROR					*/

void	cd_error(t_mini *shell, char *test, char *path);
void	cd_more(t_mini *shell, char *message);
void	childish(t_mini *shell);

/*				BUILTIN	UTILS					*/

t_env	*retrieve_key(t_env *env, char *str);

/*				FOR EXIT						*/

void	real_exit(t_mini *shell, char *str, int i);
void	print_toomany(t_mini *shell);
void	print_letter(t_mini *shell, char *str);
int		check_num(char *str);
void	now_exit(t_mini *shell, char **str);

/*				FOR ECHO						*/

void	ft_echo(t_mini *shell, t_cmds *cmds);

/*				FOR TESTING						*/

void	print_cmd_info(t_cmds **cmds);

/*				FOR EXECUTION					*/

void	check_builtin(t_mini *shell, t_cmds *cmd);
void	run_commands(t_mini *shell);
void	run_multiple(t_mini *shell, t_cmds *cmds);
void	execute(t_mini *shell, t_cmds *cmd);
void	first_command(t_mini *shell, t_cmds *cmd);
void	last_command(t_mini *shell, t_cmds *cmd);
void	run_a_single_cmd(t_mini *shell, t_cmds *cmd);
void	minishell(t_mini *shell);
int		safe_to_run(t_cmds *cmds);
void	restore_fds(t_mini *shell);
void	set_pipes(t_mini *shell, t_cmds *cmd);
void	run_builtin(t_mini *shell, t_cmds *cmd);
int		duplicate_fds(t_cmds *cmd);

void	exit_code(t_mini *shell, int code, int sig);
void	update_exitcode(t_mini *shell, t_cmds *cmds);
void	write_exit(t_mini *shell, t_cmds *cmd);
void	free_and_exit(t_mini *shell, char *message);
int		funtastic(t_mini *shell);
void	heredoc_typer(t_env *env, char *str, int fd);
t_env	*hdoc_key(char *str, int index, t_env *env);

#endif
