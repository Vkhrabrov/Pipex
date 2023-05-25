# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vkhrabro <vkhrabro@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/04 21:21:32 by vkhrabro          #+#    #+#              #
#    Updated: 2023/05/25 00:04:24 by vkhrabro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
HEADER = pipex.h
HEADER_B = pipex_bonus.h
LIBS = libft/

SRC_F:= pipex pipex_utils pipex_utils_2 pipex_utils_3 get_next_line/get_next_line  get_next_line/get_next_line_utils

SRC_BNS_F:= pipex_bonus pipex_utils_bonus pipex_utils_2_bonus pipex_utils_3_bonus get_next_line/get_next_line get_next_line/get_next_line_utils

FLAGS = -Wall -Wextra -Werror
RM = rm -f
SRC = $(addsuffix .c, $(SRC_F))
OBJS = $(SRC:.c=.o)
SRC_BNS = $(addsuffix .c, $(SRC_BNS_F))
OBJS_BNS = $(SRC_BNS:.c=.o)

CC = gcc

%.o: %.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

all: 	make_libs $(NAME)

make_libs:
	$(MAKE) -C $(LIBS)

$(NAME): $(OBJS) $(HEADER)
	$(CC) $(FLAGS) -L$(LIBS) -lft -o $@ $(OBJS)

bonus: make_libs $(OBJS_BNS) $(HEADER_B)
	$(CC) $(FLAGS) -L$(LIBS) -lft -o $(NAME) $(OBJS_BNS)

clean:
	$(RM) $(OBJS) $(OBJS_BNS) 
	$(MAKE) -C $(LIBS) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBS) fclean

re: fclean all

.PHONY: re clean fclean all bonus




