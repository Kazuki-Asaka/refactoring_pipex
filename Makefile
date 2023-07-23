# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akazuki <akazuki@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/24 16:44:17 by akazuki           #+#    #+#              #
#    Updated: 2023/05/01 15:56:21 by akazuki          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	add_token_type.c	\
		change_str_to_words.c	\
		create_tree.c		\
		ft_strncmp.c		\
		lexical_analysis.c	\
		main.c			\
		utils_check.c		\
		utils_count.c		\
		utils_del.c		\
		utils_error_check.c	\
		utils_is.c		\
		utils_is_2.c	\
		utils_strdup.c	\
		pipex.c			\
		ft_strjoin.c		\
		ft_strlen.c	\
		ft_putendl_fd.c\
		ft_putstr_fd.c\
		ft_split.c\
		ft_strchr.c\
		ft_strlcpy.c\
		access.c\
		do_cmd.c		\
		path_check.c	\
		redirect.c

# check_not_close_quotation.c
OBJS	=	$(SRCS:.c=.o)

CC	=	cc

CFLAGS	=	-Wall -Wextra -Werror

NAME	=	new_pipex

all:	$(NAME)

$(NAME):	$(OBJS)
		$(CC) $(OBJS) -o $(NAME)

clean:	
		rm -f $(OBJS)

fclean:	clean
		rm -f $(NAME) 

bonus:	$(NAME)

re:		fclean all

.PHONY:	all clean fclean re
