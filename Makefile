# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vkhrabro <vkhrabro@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/04 21:21:32 by vkhrabro          #+#    #+#              #
#    Updated: 2023/05/17 21:10:52 by vkhrabro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
HEADER = pipex.h
LIBS:= libft/

SRC_F:= pipex pipex_utils pipex_utils_2 pipex_utils_3 get_next_line/get_next_line 

#SRC_BNS_F:= ft_lstnew ft_lstadd_front ft_lstsize ft_lstlast ft_lstadd_back ft_lstdelone ft_lstclear ft_lstiter ft_lstmap

FLAGS = -Wall -Wextra -Werror
RM = rm -f
SRC = $(addsuffix .c, $(SRC_F))
OBJS = $(SRC:.c=.o)
#SRC_BNS = $(addsuffix .c, $(SRC_BNS_F))
#OBJS_BNS = $(SRC_BNS:.c=.o)

CC = gcc

%.o: %.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

all: 	make_libs $(NAME)

make_libs:
		$(MAKE) -C $(LIBS)

$(NAME): $(OBJS) $(HEADER) $(LIBS)
	cp libft/libft.a $(NAME)
	$(CC) $(FLAGS) -L$(LIBS) -lft -o $@ $(OBJS)

#bonus: $(OBJS) $(OBJS_BNS) $(HEADER)
#		 ar -rcs $(NAME) $(OBJS) $(OBJS_BNS) $(NAME)
#		@touch $@

clean:
	$(RM) $(OBJS)
	$(RM) libft/libft.a
	$(MAKE) -C libft/ clean  

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: re clean fclean all