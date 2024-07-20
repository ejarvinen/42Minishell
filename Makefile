# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/08 13:19:14 by sataskin          #+#    #+#              #
#    Updated: 2024/07/20 13:01:36 by emansoor         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = main.c \
		control/add_env.c \
		control/panic.c \
		control/signal.c \
		control/more_signal.c\
		control/ltoa.c \
		control/set_data.c \
		control/exit_code.c \
		builtin/export_index.c \
		builtin/export.c \
		builtin/update_env.c \
		builtin/unset.c \
		builtin/validity.c \
		builtin/pwd.c \
		builtin/env.c \
		builtin/cd.c \
		builtin/builtin_error.c \
		builtin/builtin_utils.c \
		builtin/exit.c \
		builtin/echo.c \
		parser/tokenizer.c \
		parser/build_token_list.c \
		parser/build_command_list.c \
		parser/open_dollars.c \
		parser/token_cleanup.c \
		parser/token_cleanup_utils.c \
		parser/t_toks_utils.c \
		parser/match_delim.c \
		parser/match_delim_args_and_cmds.c \
		parser/match_delim_double_check_tools.c \
		parser/identify_delims.c \
		parser/identify_delims_redirs.c \
		parser/identify_delims_set_token_specs.c \
		parser/identify_file.c \
		parser/identify_file_append.c \
		parser/parser_struct_utils.c \
		parser/no_blanks_cleanup.c \
		parser/no_blanks_cleanup_list_tools.c \
		parser/no_blanks_cleanup_splitting.c \
		parser/add_cmd_info.c \
		parser/add_heredoc_info.c \
		parser/add_infile_info.c \
		parser/add_outfile_info.c \
		parser/parser.c \
		parser/parser_utils.c \
		parser/ft_splitstr.c \
		parser/command_validation.c \
		parser/command_validation_tools.c \
		parser/fill_cmd_info.c \
		parser/fill_redir_info.c \
		parser/syntax_check.c \
		parser/token_list_tools.c \
		parser/expand_exit_code.c \
		execute/open_files.c \
		execute/close_files.c \
		execute/error_messages.c \
		execute/error_msg_utils.c \
		execute/run_commands.c \
		execute/heredoc.c \
		execute/run_builtins.c \
		execute/minishell.c \
		execute/hdc_to_file.c \
		execute/run_multiple_cmds.c \
		execute/execute.c \
		execute/pipe_utils.c \

OBJECTS = $(SRCS:.c=.o)

LIBFT = libft/libft.a

RL_PATH := ~/.brew/opt/readline/lib

all: $(NAME)

%.o:%.c
	@cc -Wall -Wextra -Werror -c $< -o $(<:.c=.o)

$(NAME): $(OBJECTS)
	@make -C ./libft
	@cc -Wall -Wextra -Werror $(OBJECTS) $(LIBFT) -o $(NAME) -lreadline -L $(RL_PATH)
	@echo shell sisters MINISHELL done

clean:
	@make clean -C ./libft
	@rm -f $(OBJECTS)

fclean: clean
	@make fclean -C ./libft
	@rm -f $(NAME)

re: fclean all

valgrind:
	valgrind ./minishell

fvalgrind:
	valgrind --leak-check=full --track-fds=all --trace-children=yes ./minishell

.PHONY: clean fclean all re run fvalgrind
