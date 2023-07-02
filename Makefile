# CC specifies the compiler to be used
CC = gcc

# SRC specifies the .c files
SRC = driver_boilerplate.c #add file containing solver function here

# NAME specifies the name of our exectuable
NAME = 'driver'

# RM specifies the program to delete files
RM = rm -f

# CFLAGS specifies your favorite compiler flags
CFLAGS = -Wall -Werror -Wextra -pedantic

# IFLAGS specifies the include flags
# IFLAGS = -I include\sdl\include

# LFLAGS specifies the linker flags
# LFLAGS = -L include\sdl\lib

# Makefile should work even if there is a file in the folder
# that has the same name as rule
.PHONY: all clean eclean fclean re

# This rule builds our executable
# Makefile should not compile if the header file main.h is missing
all: $(SRC)
	$(CC) $(SRC) -o $(NAME)

# This rule deletes all Emacs and Vim temporary files along with the executable
clean:
	$(RM) *~ $(NAME)

eclean:
	$(RM) $(NAME)

# This rule deletes all Emacs and Vim temporary files, the executable, and the object files
fclean: eclean clean

# This rule forces recompilation of all source files
re: fclean all