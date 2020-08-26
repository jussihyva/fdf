# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/21 11:50:38 by jkauppi           #+#    #+#              #
#    Updated: 2020/08/26 10:05:28 by jkauppi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME					=	fdf
CC						=	gcc
FLAGS					=	-g -Wall -Wextra -Werror
FRAMEWORKS				=	-framework OpenGL -framework AppKit
LIBS					=	-lmlx -lft -lftprintf
LIB_FOLDER				=	lib
SRC_FOLDER				=	src
OBJ_FOLDER				=	obj
INCLUDES				=	-I $(SRC_FOLDER) -I $(LIB_FOLDER)
SRCS					=	bresenham_line.c event_handler.c image_line.c \
							read_opt.c input.c input_map.c
HEADERS					=	$(SRC_FOLDER)/fdf.h
OBJS					=	$(addprefix $(OBJ_FOLDER)/, \
											$(patsubst %.c, %.o, $(SRCS)))

all: $(NAME)

$(NAME): $(SRC_FOLDER)/$(NAME).c $(HEADERS) $(OBJS) | library $(OBJ_FOLDER)
	$(CC) $(FLAGS) $(INCLUDES) -o $(NAME) $(SRC_FOLDER)/$(NAME).c $(OBJS) -L $(LIB_FOLDER) $(LIBS) $(FRAMEWORKS)

$(OBJS): $(OBJ_FOLDER)/%.o: $(SRC_FOLDER)/%.c $(HEADERS)
	$(CC) $(FLAGS) $(INCLUDES) -c -o $@ $<

$(OBJ_FOLDER):
	mkdir $(OBJ_FOLDER)

library:
	@make -C ${LIB_FOLDER}

clean:
	rm -f $(OBJS)

fclean: clean
	rm $(NAME)

re: fclean all

norm:
	norminette *[ch]

.PHONY: all clean fclean re norm library
