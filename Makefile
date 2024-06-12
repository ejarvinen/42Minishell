# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sataskin <sataskin@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/08 13:19:14 by sataskin          #+#    #+#              #
#    Updated: 2024/06/11 12:55:46 by sataskin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = main.c \
		builtin/pwd.c \
		add_env.c \
		builtin/export_index.c \
		builtin/export.c \
		builtin/update_env.c \
		builtin/unset.c \
		builtin/validity.c \
		panic_pt1.c \
		signal.c \
		builtin/env.c \
		ltoa.c \
		builtin/cd.c \
		set_data.c \
		builtin/builtin_error.c \
		builtin/builtin_utils.c \
		parser/tokenizer.c \
		parser/build_token_list.c \
		parser/build_command_list.c \
		parser/open_dollars.c \
		parser/token_cleanup.c \
		parser/t_toks_utils.c \
		parser/match_delim.c \
		parser/identify_delims.c \
		parser/identify_file.c \
		parser/parser_struct_utils.c \
		parser/no_blanks_cleanup.c \
		parser/add_cmd_info.c \
		parser/parser.c \
		parser/ft_splitstr.c \
		builtin/exit.c

OBJECTS = $(SRCS:.c=.o)

LIBFT = libft/libft.a

RL_PATH := ~/.brew/opt/readline/lib

all: $(NAME)

%.o:%.c
#	@cc -Wall -Wextra -Werror -g -fsanitize=address -c $< -o $(<:.c=.o)
	@cc -Wall -Wextra -Werror -c $< -o $(<:.c=.o)

$(NAME): $(OBJECTS)
	@make -C ./libft
#	@cc -Wall -Wextra -Werror -g3 -fsanitize=address $(OBJECTS) $(LIBFT) -o $(NAME) -lreadline -L $(RL_PATH)
	@cc -Wall -Wextra -Werror $(OBJECTS) $(LIBFT) -o $(NAME) -lreadline -L $(RL_PATH)
	@echo shell sisters MINISHELL done

clean:
	@make clean -C ./libft
	@rm -f $(OBJECTS)

fclean: clean
	@make fclean -C ./libft
	@rm -f $(NAME)

re: fclean all

debug:
	@cc -Wall -Wextra -Werror -g3 -fsanitize=address $(OBJECT) $(LIBFT) -o $(NAME) -lreadline

.PHONY: clean fclean all re
