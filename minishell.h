/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 13:21:33 by sataskin          #+#    #+#             */
/*   Updated: 2024/07/05 09:38:15 by emansoor         ###   ########.fr       */
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

extern int	g23_sig;

# define READ_END 0
# define WRITE_END 1

typedef struct s_cmds
{
    char            **command;
    char            *path;
    char			*infile_name;
    char			*outfile_name;
    char			*heredoc;
    int                c_pid;
    int                fd_infile;
    int                fd_outfile;
    int                id;
    int                commands;
    int				builtin;
    int				append;
    int                valid;
    int                exit_status;
    struct s_cmds    *next;
}            t_cmds;

typedef struct s_toks
{
	char			*content;
	int			file;
	int			command;
	int			argument;
	int			pipe;
	int			in_redir;
	int			out_redir;
	int			append;
	int			heredoc;
	int			heredoc_delimiter;  // means the '<<'
	int			id;
	struct s_toks	*next;
}					t_toks;

typedef struct s_env
{
	char			*key;
	char			*value;
	int				equal;
	int 			index;
	struct s_env	*next;
	//int				shlvl;
}	t_env;

typedef struct s_mini
{
	t_env	*env;
	t_cmds	*cmds;
	int		shlvl;
	int		EXIT_CODE;
	char	*pwd;
	char	*oldpwd;
}	t_mini;



/*				PARSING							*/

char		*ft_strtok(char *str);
void		token_cleanup(t_toks **tokens, t_env **envs);
void		expand_dollar(t_toks **token, t_env **envs, int *index, int in_doubles);
t_toks	*checker(char *input);
void		ft_lstadd_back_toks(t_toks **lst, t_toks *new);
void		ft_lstclear_toks(t_toks **lst);
t_toks	*ft_lstnew_toks(char *content);
int		ft_lstsize_toks(t_toks *lst);
t_toks	*ft_lstlast_toks(t_toks *lst);
void		identify_delims(t_toks **tokens);
void		identify_heredoc(t_toks **tokens);
void		recognize_file(t_toks **tokens);
void		identifier(t_toks **tokens);
void		identify_commands(t_toks **tokens);
void		identify_args(t_toks **tokens);
t_cmds	*ft_lstnew_pars(int index);
int		ft_lstsize_pars(t_cmds *lst);
t_cmds	*ft_lstlast_pars(t_cmds *lst);
void		ft_lstadd_back_pars(t_cmds **lst, t_cmds *new);
void		ft_lstclear_pars(t_cmds **lst);
void	free_array(char **array);
int	in_quotes(char *token, size_t index);
void	no_blanks_cleanup(t_toks **tokens);
void	add_indexes(t_toks **tokens);
void	add_token_info(t_toks *new_node);
int	parser(char *rl, t_mini *shell);
int	struct_sum(t_toks *token);
t_cmds	*build_command_list(t_toks **tokens);
void	add_builtin_info(t_cmds **cmds);
void	add_cmds_info(t_cmds **cmds);
char	**ft_splitstr(char const *s, char *c);
void	validate_commands(t_cmds **cmds, t_env **envs);
char	*full_path(char *path, char *command);

/*				INPUT VALIDATION				*/

void	prep_for_exec(t_mini *shell);
void	open_files(t_cmds **cmds);
void	close_files(t_cmds **cmds);
int	is_dir(char *command);
void	print_dirmsg(char *command);
void	dot_cmd(t_cmds **cmds);
void	nonexistent_cmd(t_cmds **cmds);

/*				FOR CREATING ENV				*/

void	ft_lstadd_back_mini(t_env **lst, t_env *new);
char	*get_key(char *str);
char	*get_value(char *envp);
void	add_input(t_env *node, char *envp);
t_env	*add_env(char **envp);

/*				FOR PANIC						*/

void	free_env(t_env *env);
void	ft_freearray(char **array);
void	free_data(t_mini *shell, char *message);

/*				FOR SIGNALs						*/

void	par_sig_handler(int sig);
void	set_signal(int mode);
void	rl_replace_line(const char *text, int clear_undo);
void	rl_redisplay(void);

/*				FOR EXPORT						*/

void	print_export(t_env *env);
//void	export(t_env **env, char **str, int fd);
void	export(t_mini *shell, t_cmds *cmd);
int		lstsize(t_env *lst);
t_env	*find_next(t_env *env);
void	change_index(t_env **env);
void	update_index(t_env **env);
void	edit_env(t_env *node, char *str);
void	new_env(t_env **env, char *str);
void 	print_to_file(t_env *env, int fd);

/*				FOR UNSET						*/

void	ft_realunset(t_env **env, char *str);
//void	ft_unset(t_env **env, char **str);
void	ft_unset(t_mini *shell, t_cmds *cmd);

/*				CHECKING FOR VALID KEY			*/

int		validity(char *str, char *function);

/*				FOR PWD							*/

//void	pwd(t_mini *shell);
void	pwd(t_mini *shell, t_cmds *cmd);

/*				FOR ENV							*/

//int		ft_env(t_mini *shell);
int	ft_env(t_mini *shell, t_cmds *cmd);
char	**ltoa(t_env *env);

/*				FOR CD							*/

//void	ft_cd(t_mini *shell, char **path);
void	ft_cd(t_mini *shell, t_cmds *cmd);
void	set_data(t_mini *shell, char **envp);

/*				BUILTIN ERROR					*/

void	cd_error(t_mini *shell, char *test, char *path);

/*				BUILTIN	UTILS					*/

t_env	*retrieve_key(t_env *env, char *str);

/*				FOR EXIT						*/

void	real_exit(t_mini *shell, char *str, int i);
void	print_toomany(t_mini *shell);
void	print_letter(t_mini *shell, char *str);
int		check_num(char *str);
void	now_exit(t_mini *shell, char **str);

/*				FOR ECHO						*/

//void	ft_echo(t_cmds *cmds);
void	ft_echo(t_mini *shell, t_cmds *cmds);

/*				FOR TESTING						*/

void	print_cmd_info(t_cmds **cmds);

/*				FOR EXECUTION					*/

void	check_builtin(t_mini *shell, t_cmds *cmd);
void	run_commands(t_mini *shell);
void	run_multiple(t_mini *shell, char **env, t_cmds *cmds);
void	execute(t_mini *shell, t_cmds *cmd, char **env, int *pipefds);
void	first_command(t_cmds *cmd, int *pipefds);
void	last_command(t_cmds *cmd, int *pipefds);
void	close_pipes(int *pipefds);

#endif
