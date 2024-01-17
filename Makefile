CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf


CLIENT = client
SERVER = server

CLIENT_BONUS = client_bonus
SERVER_BONUS = server_bonus

CLIENT_SRC = client.c
SERVER_SRC = server.c

CLIENT_BONUS_SRC = client_bonus.c
SERVER_BONUS_SRC = server_bonus.c

HEADER = minitalk.h
LIBFT_SRC = ft_atoi.c ft_putstr_fd.c ft_isdigit.c ft_putnbr_fd.c ft_putchar_fd.c
LIBFT_OBJ = $(LIBFT_SRC:.c=.o)

CLIENT_OBJ = $(CLIENT_SRC:.c=.o)
SERVER_OBJ = $(SERVER_SRC:.c=.o)

CLIENT_BONUS_OBJ = $(CLIENT_BONUS_SRC:.c=.o)
SERVER_BONUS_OBJ = $(SERVER_BONUS_SRC:.c=.o)


all: $(CLIENT) $(SERVER) 

$(CLIENT): $(LIBFT_OBJ) $(CLIENT_OBJ) 
	@$(CC) $(CFLAGS) $(CLIENT_OBJ) $(LIBFT_OBJ) -o $(CLIENT)
	@echo "Client compiled successfully"

$(SERVER): $(LIBFT_OBJ) $(SERVER_OBJ)
	@$(CC) $(CFLAGS) $(SERVER_OBJ) $(LIBFT_OBJ) -o $(SERVER)
	@echo "Server compiled successfully"

#PART BONUS
bonus: $(CLIENT_BONUS) $(SERVER_BONUS)

$(CLIENT_BONUS): $(LIBFT_OBJ) $(CLIENT_BONUS_OBJ)
	@$(CC) $(CFLAGS) $(CLIENT_BONUS_OBJ) $(LIBFT_OBJ) -o $(CLIENT_BONUS)
	@echo "Client compiled successfully - bonus"


$(SERVER_BONUS): $(LIBFT_OBJ) $(SERVER_BONUS_OBJ)
	@$(CC) $(CFLAGS) $(SERVER_BONUS_OBJ) $(LIBFT_OBJ) -o $(SERVER_BONUS)
	@echo "Server compiled successfully - bonus"

$(LIBFT_OBJ): $(HEADER)
clean:
	@$(RM) $(CLIENT_OBJ) $(SERVER_OBJ)
	@$(RM) $(LIBFT_OBJ)
	@$(RM) $(CLIENT_BONUS_OBJ) $(SERVER_BONUS_OBJ)
	@echo "Object files cleaned"
fclean: clean
	@$(RM) $(CLIENT) $(SERVER)
	@$(RM) $(CLIENT_BONUS) $(SERVER_BONUS)
	@echo "Executable files cleaned"

re: fclean all
