# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sataskin <sataskin@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/08 13:19:14 by sataskin          #+#    #+#              #
#    Updated: 2024/06/06 11:08:18 by sataskin         ###   ########.fr        #
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
		builtin/builtin_utils.c

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
