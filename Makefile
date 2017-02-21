# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sduprey <sduprey@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/12/17 05:35:05 by sduprey           #+#    #+#              #
#    Updated: 2017/02/21 18:37:02 by tlepeche         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = avm

SRC = Factory.cpp \
	  main.cpp \
	  Instruction.cpp \
	  Exception.cpp \

SRCDIR = src/

OBJDIR = obj/

OBJ = $(SRC:%.cpp=$(OBJDIR)%.o)

CC = clang++

RM = rm -rf

INC = -I includes

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) -o $(NAME) $(OBJ)
	@echo ""
	@echo $(PX_STR) : $(EX_COLOR)$(NAME)$(NO_COLOR)
	@echo ""

$(OBJDIR)%.o: $(SRCDIR)%.cpp
	@mkdir -p $(OBJDIR)
	@$(CC) -c $(INC) $< -o $@ 
	@echo $(CC_STR) $*

clean:
	@$(RM) $(OBJDIR)
	@echo $(RM_STR) objects

fclean: clean
	@$(RM) $(NAME)
	@echo $(RM_STR) $(NAME)

re: fclean all

NO_COLOR = "\033[0;0m"
CC_COLOR = "\033[0;33m"
EX_COLOR = "\033[0;32m"
PX_COLOR = "\033[4;37m"
RM_COLOR = "\033[0;31m"

CC_STR = $(CC_COLOR)[CC]$(NO_COLOR)
PX_STR = $(PX_COLOR)Binary compiled successfully$(NO_COLOR)
RM_STR = $(RM_COLOR)Remove$(NO_COLOR)
