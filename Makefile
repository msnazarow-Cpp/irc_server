NAME		=	ft_irc
NAME_B		=	ft_irc_bonus

SRC_M		=	main.cpp\
				ServConfig.cpp\
				Server.cpp\
				Parser.cpp\
				Location.cpp\
				utils.cpp\
				Client.cpp\
				response.cpp\
				Channel.cpp\
				Message.cpp\

COMM =		Commands/Command.o\
			Commands/Invite.o\
			Commands/Join.o\
			Commands/Kick.o\
			Commands/Kill.o\
			Commands/Mode.o\
			Commands/Nick.o\
			Commands/Oper.o\
			Commands/Part.o\
			Commands/Pass.o\
			Commands/Privmsg.o\
			Commands/Quit.o\
			Commands/User.o\
			Parse.o

SRC_B		=	main.cpp\
				ServConfig_bonus.cpp \
				Server.cpp\
				Parser.cpp\
				Location.cpp\
				utils.cpp\
				Cgi.cpp\
				Request.cpp\
				Client.cpp\
				MimeTypes.cpp\
				response.cpp\
				GetMethod.cpp\
				PostMethod.cpp\
				PutMethod.cpp\
				response_generator.cpp\
				base64.cpp \
				DeleteMethod.cpp
COMM	:= $(addprefix obj/,$(COMM))
DOBJ = $(OBJ:.o=.d)
NAME = ft_irc
CXX = clang++ -std=c++98
CPPFLAGS = -Wall -Werror -g -MMD -D_GLIBCXX_DEBUG -I$(INCLUDES) #-fsanitize=address 
INCLUDES = Commands
BIN			=	./bin
OBJ_M		=	$(addprefix $(BIN)/, $(SRC_M:cpp=o))
OBJ_B		=	$(addprefix $(BIN)/, $(SRC_B:cpp=o))
DEP			=	$(OBJ_M:%.o=%.d) \
				$(OBJ_B:%.o=%.d) \
				$(COMM:.o=.d)
CC			=	clang++
FLAGS		=	-Wall -Wextra -Werror #-std=c++98

.PHONY: all clean fclean re

all: obj/Commands $(NAME)


obj/Commands:
	mkdir -p obj/Commands

$(BIN)/%.o:./src/%.cpp  | $(BIN)
	$(CC) $(FLAGS) -MMD -I./include -c $< -o $@

obj/%.o : %.cpp
	$(CXX) -c $(CPPFLAGS) $< -o $@ 

$(NAME): $(OBJ_M) $(COMM)
	$(CC) $(FLAGS) $^ -o $@

bonus: $(NAME_B)

$(NAME_B): $(OBJ_B)
	$(CC) $(FLAGS) $^ -o $@

-include $(DEP)

$(BIN):
	@mkdir $(BIN)

clean:
	@rm -rf $(BIN)
	@echo "$(NAME) object files deleted"

fclean: clean
	@rm -f $(NAME)
	@rm -f $(NAME_B)

test: run
	./tester http://localhost:1234

run: all
	./webserv config/mizola.conf &
	./tester http://localhost:1234

re: fclean all