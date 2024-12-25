# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: halnuma <halnuma@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/16 10:13:48 by halnuma           #+#    #+#              #
#    Updated: 2024/12/25 10:26:53 by halnuma          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re libft

# ------ COLORS ------

_END			= \033[0m
_GREY			= \033[0;30m
_RED			= \033[0;31m
_GREEN			= \033[0;32m
_YELLOW			= \033[0;33m
_BLUE			= \033[0;34m
_PURPLE			= \033[0;35m
_CYAN			= \033[0;36m

# ------ VARIABLES ------

NAME			= so_long
CC				= cc
AR				= ar -rcs
CFLAGS			= -Wall -Wextra -Werror
LFLAGS 			= -L$(P_MLX) -L$(P_INC) -lmlx -lXext -lX11 -lm -lbsd

# ------ PATHS ------

P_OBJ 			= obj/
P_SRC 			= src/
P_INC			= includes/
P_LIB			= libft/
P_MLX			= minilibx-linux/

# ------ FILES ------

MAIN			= main						init_game		\
				end_game					map_display		\
				map_error_utils				map_utils		\
				map_solvability_utils		move_player

HDR_SRC			= libft					mlx_int			\
				mlx						so_long

SRC_ALL			= $(addprefix $(P_SRC), $(addsuffix .c, $(MAIN)))

OBJ_ALL 		= $(addprefix $(P_OBJ), $(addsuffix .o, $(MAIN)))

HEADERS			= $(addprefix $(P_INC), $(addsuffix .h, $(HDR_SRC)))
LIBFT			= $(P_LIB)libft.a
MLX				= $(P_MLX)libmlx_Linux.a		$(P_MLX)libmlx.a

# ------ RULES ------

all: 			libft mlx $(NAME)

$(NAME): 		$(SRC_ALL) Makefile $(HEADERS)
				@$(CC) $(CFLAGS) $(LFLAGS) -I $(P_INC) $(SRC_ALL) $(LIBFT) $(MLX) -o $@
				@echo "$(_YELLOW)Compiling $(SRC_ALL)$(_END)"
				@echo "$(_GREEN)$(NAME) compiled!$(_END)"

libft:		
				@$(MAKE) -C $(P_LIB) --no-print-directory

mlx:		
				@$(MAKE) -C $(P_MLX)

# ------ BASIC RULES ------

clean: 
				@rm -rf $(P_OBJ)
				@$(MAKE) -C $(P_LIB) clean --no-print-directory
				@$(MAKE) -C $(P_MLX) clean --no-print-directory
				@echo "$(_CYAN)$(NAME) cleaned!$(_END)"

fclean:
				@$(MAKE) clean --no-print-directory
				@$(MAKE) -C $(P_LIB) fclean --no-print-directory
				@rm -rf $(LIBFT)
				@rm -rf $(NAME)
				@echo "$(_CYAN)$(NAME) full cleaned!$(_END)"

re:
				@$(MAKE) fclean --no-print-directory
				@$(MAKE) all --no-print-directory
				@echo "$(_CYAN)$(NAME) rebuilt!$(_END)"
