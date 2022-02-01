# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/23 18:12:02 by tlemma            #+#    #+#              #
#    Updated: 2022/02/01 15:15:41 by tlemma           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc 
CFLAGS = -Wall -Werror -Wextra 
READLINE = -L /Users/$(USER)/.brew/opt/readline/lib
READLINE_INC = -I /Users/$(USER)/.brew/opt/readline/include

RM = rm -rf

AR = ar rs

SDIR = src
SRCS = main.c

ODIR = objs
OBJS = $(patsubst %.c, %.o, $(SRCS))

# LIBFT = $(MAKE) -C ../libft 

$(NAME): $(addprefix $(SDIR)/, $(SRCS))
	$(CC) $(CFLAGS) -c $^
	@mkdir -p $(ODIR)
	@mv $(OBJS) $(ODIR)
	$(CC) $(CFLAGS) $(addprefix $(ODIR)/, $(OBJS)) $(READLINE_INC) -lreadline libft/libft.a -o $(NAME)
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