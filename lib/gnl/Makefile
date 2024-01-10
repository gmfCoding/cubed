SRCSF = get_next_line.c \
		get_next_line_utils.c

INCSF = get_next_line.h

ifndef $(OS)
OS := $(shell uname)
endif

$(info Compiling for OS:$(OS))
NAME = libgnl.a

DIRSRC = .
DIROBJ = obj
DIRINC = .

# All relative to Makefile's folder
SRCS = $(patsubst %.c,$(DIRSRC)/%.c, $(SRCSF))
OBJS = $(SRCS:$(DIRSRC)/%.c=$(DIROBJ)/%.o)
INCS = $(patsubst %.h,$(DIRINC)/%.h, $(INCSF))
DEPS = $(OBJS:.o=.d)
CC = cc

WFLAGS = -Wall -Werror -Wextra
CPPFLAGS = -I$(DIRINC) -MMD -MP
CFLAGS = $(OPFLAG) $(DFLAGS) $(WFLAGS)
OPFLAG = -O3
#PGFLAGS = -pg

# REMOVE BEFORE EVAL
ifeq ($(DEBUG), )
$(warning USING DEFAULT DEBUG FLAGS (REMOVE BEFORE EVAL))
DEBUG =1
OPFLAG =-O0
endif

# DEBUG LEVEL 1
ifeq ($(shell test $(DEBUG) -ge 1; echo $$?),0)
	DFLAGS += -g3 -fsanitize=address
endif
ifeq ($(shell test $(DEBUG) -ge 2; echo $$?),0)
	PGFLAGS = -pg
endif

# RULES
all: $(NAME)

# OBJ TO PROJECT
$(NAME): $(LIBS) $(OBJS)
	-@printf "${BBLUE}Linking:\n${BLUE}"
	-ar rcs $@ $(OBJS)
	-@printf "${NC}"

# SOURCE TO OBJ
$(OBJS): $(DIROBJ)%.o : $(DIRSRC)%.c $(INCS) | $(DIROBJ)
	-@mkdir -p $(dir $@)
	-@printf "${GREEN}"
	-$(CC) $(PGFLAGS) $(CPPFLAGS) $(CFLAGS) -o $@ -c $<
	-@printf "${NC}"

# CLEANING
fclean: clean
	-@printf "${BRED}Cleaning executable!\n${RED}"
	-rm -f $(NAME)
	-@printf "${NC}"

clean:
	-@printf "${BYELLOW}Cleaning objects!\n${RED}"
	-rm -rf $(DIROBJ)
	-@printf "${NC}"

re: fclean all

# Dependencies
-include $(DEPS)

# Folders
$(DIROBJ):
	-@printf "${CYAN}"
	-mkdir -p $(DIROBJ)
	-@printf "${NC}"

.PHONY: all re fclean clean libclean

# COLORS
export BGREEN = \033[1;32m
export GREEN = \033[0;32m
export BRED = \033[1;31m
export RED = \033[0;31m
export BYELLOW = \033[1;33m
export YELLOW = \033[0;33m
export BBLUE = \033[1;34m
export BLUE = \033[0;34m
export BCYAN = \033[1;36m
export CYAN = \033[0;36m
export NC = \033[0m