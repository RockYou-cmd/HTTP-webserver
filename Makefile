CC = c++
INC = inc/

FLAGS= -std=c++98 -Wall -Wextra -Werror
MAIN= main.cpp
B_DIR = build
SERVER=$(addprefix server/, socket.cpp)
HEADER = $(addprefix inc/, server.hpp)
FILES= $(addprefix src/, $(SERVER))
OBJ= $(addprefix build/, $(FILES:.cpp=.o))
NAME= webserv

all:$(NAME)

$(NAME) : $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -I $(INC) -o $(NAME) 

$(B_DIR)/%.o: %.cpp $(HEADER)
	@mkdir -p $(dir $@)
	$(CC) $(FLAGS) -I $(INC) -c $< -o $@
clean:
	rm -rf $(B_DIR)

fclean: clean
	rm  -f $(NAME)

re: fclean all