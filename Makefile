# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nlenoch <nlenoch@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/23 18:12:02 by tlemma            #+#    #+#              #
#    Updated: 2022/02/23 20:22:55 by nlenoch          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc 
CFLAGS = -Wall -Werror -Wextra -Wno-unused-parameter -Wno-missing-braces  -g
READLINE = -L /Users/nlenoch/.brew/opt/readline/lib -lreadline
READLINE_INC = -I /Users/nlenoch/.brew/opt/readline/include

RM = rm -rf
AR = ar rs

SDIR = src
SRCS = main.c lexer.c utils.c lexer_utils.c parser.c xecutor.c xecutor_utils.c init_env.c export.c

ODIR = objs
OBJS = $(patsubst %.c, %.o, $(SRCS))

# LIBFT = $(MAKE) -C ../libft 

$(NAME): $(addprefix $(SDIR)/, $(SRCS))
	@mkdir -p $(ODIR)
	$(CC) $(CFLAGS) $(READLINE_INC) -I ./include/ -c $^
	@mv $(OBJS) $(ODIR)
	$(CC) $(CFLAGS) $(addprefix $(ODIR)/, $(OBJS)) $(READLINE_INC) $(READLINE) -lreadline libft/libft.a -o $(NAME)
	@echo $(NAME) created!\\n

all: $(NAME)

clean:
	$(MAKE) -C ../libft clean
	$(RM) $(ODIR)
	@echo $(ODIR) removed!\\n

fclean: clean
	# $(RM) ../libft/libft.a
	$(RM) $(NAME)
	@echo $(NAME) removed!\\n

re: fclean all
		
.PHONY: all clean fclean re bonus .c .o