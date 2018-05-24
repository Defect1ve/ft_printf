# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ikotvits <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/22 20:37:47 by ikotvits          #+#    #+#              #
#    Updated: 2018/03/28 15:20:49 by ikotvits         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

FLAGS = -Wall -Wextra -Werror

SRC = ./ft_strcmp.c ./ft_alpha.c ./ft_atoi.c ./ft_buf.c ./ft_bzero.c ./ft_manage.c ./ft_numb.c ./ft_printf.c ./ft_strcpy.c ./ft_strlen.c ./ft_strdup.c 

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

$(OBJ): $(SRC)
	 gcc -c $(FLAGS) $(SRC) -I ./

clean:
	 rm -f $(OBJ)

fclean: clean
	 rm -f $(NAME)
	@ rm -f a.out

re: fclean all