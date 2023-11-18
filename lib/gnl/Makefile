# SOURCE FILES
SRCS = 	get_next_line.c \
		get_next_line_utils.c

# TARGET NAME AND VARIBLES
NAME = libgnl.a

OBJDIR = obj/
CC = cc
WFLAGS = -Wall -Wextra -Werror
CFLAGS = $(WFLAGS) $(DFLAGS)

$(info $(CFLAGS))


# OBJECT FILES
OBJ = $(patsubst %.c,$(OBJDIR)%.o, $(SRCS))

all: $(NAME)

# BUILD LIBRARY
$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ)
	@echo "ar rcs $(NAME) ...\nget_next_line libary generated!"

# COMPILE SOURCES
$(OBJDIR)%.o: %.c get_next_line.h 
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled: $<"

# CLEANING
re: fclean all

fclean: clean
	@echo "Full clean!"
	@-rm -f $(NAME)

clean:
	@-rm -rf $(OBJDIR)

.PHONY: clean fclean $(NAME) all re

