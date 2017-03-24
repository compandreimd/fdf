# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amalcoci <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/10/07 13:33:51 by amalcoci          #+#    #+#              #
#    Updated: 2016/10/31 16:59:10 by amalcoci         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
SRC = src/main.c src/fdf_map.c src/fdf_orto.c src/fdf_tools.c src/fdf_pers.c
OBJ = $(SRC:.c=.o)
LIB = -Llibft -lft -lmlx -framework OpenGL -framework AppKit
FLAGS = -Wall -Wextra -Werror -Ilibft/includes
all: $(NAME)

$(NAME): $(OBJ)
	@gcc $(FLAGS) $(INCLUDE) -o $(NAME) $(OBJ) $(LIB)

$(OBJ): lib
	@gcc $(FLAGS) $*.c -o $@ -c $(INCLUDE)

lib:
	@make -C ./libft

clean:
	@rm -rf $(OBJ)
	@make clean -C libft

fclean: clean
	@rm -rf $(NAME)
	@make fclean -C libft
re: fclean all