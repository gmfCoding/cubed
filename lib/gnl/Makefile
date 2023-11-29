# SOURCE FILES
SRCS = get_next_line.c \
		get_next_line_utils.c

# TARGET NAME AND VARIBLES
NAME = libgnl.a
OBJDIR = obj/
CC = cc
FLAGS = $(DFLAGS) -Wall -Wextra -Werror

# OBJECT FILES
OBJ := $(patsubst %.c, $(OBJDIR)%.o, $(SRCS))
BONUS_OBJ := $(patsubst %.c, $(OBJDIR)%.o, $(SRCSB))

# ANY
all: $(NAME)

# CLEAN
re: fclean all

fclean: clean
	rm -f $(NAME)

clean:
	rm -rf $(OBJDIR)

# BUILD LIBRARY
$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ)
	@echo "ar rcs $(NAME) ..."
	@echo "Libft libary generated!"

# COMPILE
$(OBJDIR)%.o : %.c libft.h
	@mkdir -p $(OBJDIR)
	$(CC) $(FLAGS) -c $< -o $@

bonus: $(BONUS_OBJ)
	@ar r $(NAME) $(BONUS_OBJ)
	@echo "Libft bonus content generated!"
