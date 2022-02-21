#first parts 
SRC :=	main.c  gnl/get_next_line.c gnl/get_next_line_utils.c \
		src/*.c

#bonnus 
BSRC :=	$(SRC)

CC = gcc

FLGS = -Wall -Werror -Wextra -Imlx  -g -lm

VALGFLGS = --vgdb=full \
		 --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --verbose \
         --log-file=valgrind-out.txt

FBSIZE =	-D BUFFER_SIZE=42

HEADER = mch.h
LIBFT = libft/libft.a

NAME = minishell


all :$(NAME)
	
$(NAME): $(SRC) $(HEADER) $(LIBFT)
	@echo "compiling ..."
	@$(CC) $(FLGS)  $(FBSIZE) $(SRC) $(LIBFT) -o $(NAME)

bonus: $(BSRC) $(HEADER) $(LIBFT)
	@echo "compiling bonus ..."
	@rm -f $(NAME)
	@$(CC) $(FLGS) $(FBSIZE) $(BSRC) $(LIBFT) -o $(NAME)

$(LIBFT):
	@make -C libft/
	@make bonus -C libft/

so:
	@echo "clreating .so file ..."
	@$(CC) -fPIC $(CFLAGS) -c $(SRC)
	@gcc -shared -o $(NAMESO) $(OBJ)


clean:
	@echo "cleaning all objects"
	@make clean -C libft/

fclean: clean
	@echo "cleaning every thing ..."
	@make fclean -C libft/
	@rm -f $(NAME)

re: fclean all

test:
	@make -C libft/
	@$(CC) $(FRMWK) $(FBSIZE) $(BSRC) $(LIBFT)  -o tst -lm

debug: $(SRC) $(HEADER) $(LIBFT)
	@make debug -C libft/
	@echo "compiling with -g ..."
	@$(CC) -g $(FBSIZE) $(SRC) $(LIBFT) -o $(NAME) -lm

valgrind: $(NAME)
	@valgrind $(VALGFLGS) ./$(NAME) $(TARGS)


.PHONY: all clean fclean bonus so re test

#&.c : &.o libft.a 
