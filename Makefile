# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/21 11:50:38 by jkauppi           #+#    #+#              #
#    Updated: 2021/03/11 13:24:40 by jkauppi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Input parameters
# P --> Projection which define a picture projection
ifdef P
	PROJECTION	=	$(P)
else
	PROJECTION	=	0
endif
ifdef L
	LOGING_LEVEL	=	$(L)
else
	LOGING_LEVEL	=	4
endif
ifdef C
	LOG_USE_COLOR	=	1
endif

# Application specific parameters
NAME			=	fdf
NAMES			=	$(NAME)

# Folders
LIB				=	lib
BIN				=	.
DATA			=	data
OBJ				=	obj
SRC				=	src
INCLUDE			=	include
FOLDERS			=	$(LIB) $(BIN) $(DATA) $(OBJ) $(SRC) $(INCLUDE)
INCLUDES		=	-I $(INCLUDE) -I $(LIB)

# Compiler and linking parameters
CC				=	clang
C_FLAGS			=	-g -Wall -Wextra -Werror $(INCLUDES) \
											-D LOGING_LEVEL=$(LOGING_LEVEL) \
											-D LOG_USE_COLOR=$(LOG_USE_COLOR)
LD_FLAGS		=	-std=gnu17 \
					-Llib \
					-lft_addons -lftprintf -lft -lmlx_Linux -lGLEW -lGL -lm -lXext -lX11

# C (Source code) and H (Header) files
SRC_C_FILES		=	read_cmd_arguments.c ft_login_event.c initialize_window.c \
					set_elem_positions.c create_element.c draw_element_lines.c \
					render_frame.c release_mlx_win.c hook_functions1.c \
					hook_functions2.c close_win.c elemental_rotation.c \
					bresenham_line.c argp_parse.c
SRC_H_FILES		=	fdf.h

# Path folders for H, C, O and APP files
H_FILES			=	$(addprefix $(INCLUDE)/, $(SRC_H_FILES))
C_FILES			=	$(addprefix $(SRC)/, $(SRC_C_FILES))
C_FILES			+=	$(addprefix $(SRC)/, $(patsubst %, %.c, $(NAMES)))
O_FILES			=	$(addprefix $(OBJ)/, $(patsubst %.c, %.o, $(SRC_C_FILES)))
MAIN_FILES		=	$(addprefix $(SRC)/, $(patsubst %, %.c, $(NAMES)))
APP_FILES		=	$(addprefix $(BIN)/, $(NAMES))

# Colours for printouts
RED				=	\033[0;31m
GREEN			=	\033[0;32m
YELLOW			=	\033[0;33m
END				=	\033[0m

.PHONY: all
all: $(FOLDERS) $(C_FILES) libraries $(APP_FILES)
	@echo "$(GREEN)Done!$(END)"

$(APP_FILES): $(BIN)/%: $(SRC)/%.c $(H_FILES) $(O_FILES) Makefile
	$(CC) -o $@ $< $(O_FILES) $(LD_FLAGS) $(C_FLAGS)

$(O_FILES): $(OBJ)/%.o: $(SRC)/%.c $(H_FILES) Makefile
	$(CC) -c -o $@ $< $(C_FLAGS)

$(FOLDERS):
	mkdir $@

$(C_FILES):
	touch $@

$(H_FILES):
	touch $@

.PHONY: libraries
libraries:
	@make -C ${LIB}

.PHONY: libraries_re
libraries_re:
	@make -C ${LIB} re

.PHONY: libraries_norm
libraries_norm:
	@make -C ${LIB} norm

.PHONY: run
run: all
	valgrind -s --tool=memcheck --leak-check=full --show-leak-kinds=all ./$(NAME) -f $(DATA)/maps/42.fdf -P $(PROJECTION)

.PHONY: clean
clean:
	@make -C ${LIB} clean
	rm -f $(O_FILES)

.PHONY: fclean
fclean: clean
	@make -C ${LIB} fclean
	rm -f $(NAME_1)

.PHONY: re
re: fclean all

.PHONY: norm
norm:
	@make -C ${LIB} norm
	norminette $(SRC)/* $(INCLUDE)/*
