SRCSF = $(TEST) \
		texture/texture.c \
		texture/pixel.c \
		texture/texture_util.c \
		vector/vector2_math_extra.c \
		vector/vector2_math.c \
		vector/vector2.c \
		vector/vector2i_math_extra.c \
		vector/vector2i_math.c \
		vector/vector2i.c \
		render/render_util.c \
		render/loop.c \
		render/line.c \
		util/time.c \
		cerror.c \
		dda_simple.c \
		input.c \

INCSF = cubed.h

ifndef $(TEST)
TEST=main.c
endif

ifndef $(OS)
OS := $(shell uname)
endif

$(info Compiling for OS:$(OS))

NAME = cubed

DIRSRC = src
DIROBJ = obj
DIRINC = inc
DIRLIB = lib

LIBFT = libft/libft.a
LIBGNL = gnl/libgnl.a

ifeq ($(OS),Linux)
LIBMLX = mlx-linux/libmlx.a
else
LIBMLX = mlx/libmlx.a
endif

LIBSF = $(LIBFT) $(LIBGNL) $(LIBMLX)

# All relative to Makefile's folder
SRCS = $(patsubst %.c,$(DIRSRC)/%.c, $(SRCSF))
OBJS = $(SRCS:$(DIRSRC)/%.c=$(DIROBJ)/%.o)
LIBS = $(patsubst %.a,$(DIRLIB)/%.a, $(LIBSF)) 
INCS = $(patsubst %.h,$(DIRINC)/%.h, $(INCSF))
DEPS = $(OBJS:.o=.d)

LIB-I = $(patsubst %,-I%,$(dir $(LIBS))) -I$(DIRLIB)
LIB-l = $(subst lib,-l,$(basename $(notdir $(LIBSF))))
LIB-L = $(patsubst %,-L$(DIRLIB)/%, $(dir $(LIBSF)))

CC = cc

WFLAGS =#-Wall -Werror -Wextra
CPPFLAGS =-I$(DIRINC) $(LIB-I)  -MMD -MP
CFLAGS = $(OPFLAG) $(DFLAGS) $(XCFLAGS) $(WFLAGS)
LDFLAGS = $(OPFLAG) $(DFLAGS) $(XLDFLAGS) $(LIB-L) $(LIB-l) -lz -lm 
PGFLAGS = #-pg
OPFLAG = -O4

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

ifeq ($(EXTRA),1)
CPPFLAGS += -D EXTRA
endif

ifneq ($(OS),Linux) 
LDFLAGS += -framework OpenGL -framework AppKit 
else 
LDFLAGS += -lX11 -lXext
CPPFLAGS += -DKEYMAP_LINUX
endif

# RULES
all: $(NAME)

# OBJ TO PROJECT
$(NAME): $(LIBS) $(OBJS)
	-@printf "${BLUE}"
	$(CC) $(PGFLAGS) $(OBJS) $(LDFLAGS) -o $@
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

$(DIRLIB)/$(LIBFT):
	make -s -C $(dir $@) all bonus

$(DIRLIB)/$(LIBGNL):
	make -s -C $(dir $@) all

$(DIRLIB)/$(LIBMLX):
	make -s -C $(dir $@)

$(DIRLIB)/$(LIBMLX_SO): $(LIBMLX)
	cp $(DIRMLX)/libmlx.so ./libmlx.so

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