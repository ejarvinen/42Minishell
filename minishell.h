/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sataskin <sataskin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 13:21:33 by sataskin          #+#    #+#             */
/*   Updated: 2024/06/06 11:43:21 by sataskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"
# include <signal.h>
# include <termios.h>
# include <fcntl.h>

static int	g23_sig = 0;

typedef struct s_cmds
{
    char            **command;
    char            *path;
    int                c_pid;
    int                fd_infile;
    int                fd_outfile;
    int                id;
    int                commands;
    int                valid;
    int                exit_status;
    struct s_cmds    *next;
}            t_cmds;

typedef struct s_pars
{
	char			**ptr;
	int				quote_type;
    int             delimiter;
	int				quotecount;
    int             delimcount;
	int				wordcount;
	size_t			str_len;
}			t_pars;

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
	int		shlvl;
	int		EXIT_CODE;
	char	*pwd;
	char	*oldpwd;
}	t_mini;



/*				PARSING							*/

char	**parser(char const *str);
char	**null(void);
void	initialize_parsing_specs(t_pars *specs, char const *str);
int		find_delimiter(char const *str);

/*				FOR CREATING ENV				*/

void	ft_lstadd_back_mini(t_env **lst, t_env *new);
char	*get_key(char *str);
char	*get_value(char *envp);
void	add_input(t_env *node, char *envp);
t_env	*add_env(char **envp);

/*				FOR PANIC						*/

void	free_env(t_env *env);
void	*ft_freearray(char **array);
void	free_data(t_mini *shell);

/*				FOR SIGNALs						*/

void	par_sig_handler(int sig);
void	set_signal(int mode);
void	rl_replace_line(const char *text, int clear_undo);
void	rl_redisplay(void);

/*				FOR EXPORT						*/

void	print_export(t_env *env);
void	export(t_env **env, char **str);
int		lstsize(t_env *lst);
t_env	*find_next(t_env *env);
void	change_index(t_env **env);
void	update_index(t_env **env);
void	edit_env(t_env *node, char *str);
void	new_env(t_env **env, char *str);

/*				FOR UNSET						*/

void	ft_realunset(t_env **env, char *str);
void	ft_unset(t_env **env, char **str);

/*				CHECKING FOR VALID KEY			*/

int		validity(char *str, char *function);

/*				FOR PWD							*/

void	pwd(t_mini *shell);

/*				FOR ENV							*/

int		ft_env(t_env *env);
char	**ltoa(t_env *env);

/*				FOR CD							*/

void	ft_cd(t_mini *shell, char *path);
void	set_data(t_mini *shell, char **envp);

/*				BUILTIN ERROR					*/

void	cd_error(t_mini *shell, char *test, char *path);

/*				BUILTIN	UTILS					*/

t_env	*retrieve_key(t_env *env, char *str);

#endif