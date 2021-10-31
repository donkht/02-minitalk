NAME		=	minitalk

all:	${NAME}

${NAME}: server client

server: server.c utils.c minitalk.h
	gcc -Wall -Wextra -Werror server.c utils.c  -o server

client: client.c utils.c minitalk.h
	gcc -Wall -Wextra -Werror client.c utils.c  -o client


bonus:  server_bonus client_bonus

server_bonus: server_bonus.c utils_bonus.c minitalk_bonus.h
	gcc -Wall -Wextra -Werror server_bonus.c utils_bonus.c -o server

client_bonus: client_bonus.c utils_bonus.c minitalk_bonus.h
	gcc -Wall -Wextra -Werror client_bonus.c utils_bonus.c -o client
	
clean:

fclean: clean
		rm -f server client

re:		fclean all

.PHONY: all clean fclean re bonus server_bonus client_bonus
	







