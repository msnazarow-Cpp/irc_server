NAME		=	ircserv
NAME_B		=	ft_irc_bonus

SRC_M		=	main.cpp\
				Server.cpp\
				utils.cpp\
				Client.cpp\
				Channel.cpp\
				Message.cpp
BOT_FILES =		bot/main.o
BOT 		= BOT.bot
COMM =		Commands/Command.o\
			Commands/Userhost.o\
			Commands/Names.o\
			Commands/Ison.o\
			Commands/Topic.o\
			Commands/Whois.o\
			Commands/Notice.o\
			Commands/List.o\
			Commands/Who.o\
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
			Commands/RegisteredCommand.o\
			Commands/OperatorsCommand.o\
			Commands/Parse.o
COMM	:= $(addprefix obj/,$(COMM))
DOBJ = $(OBJ:.o=.d)
CXX = clang++ -std=c++98
CPPFLAGS = -Wall -Werror -Wextra -MMD $(INCLUDES)
INCLUDES = -ICommands -Iinclude
BIN			=	./bin
OBJ_M		=	$(addprefix $(BIN)/, $(SRC_M:cpp=o))
OBJ_B		=	$(addprefix $(BIN)/, $(SRC_B:cpp=o))
DEP			=	$(OBJ_M:%.o=%.d) \
				$(OBJ_B:%.o=%.d) \
				$(COMM:.o=.d)
.PHONY: all clean fclean re

all: obj $(NAME) # $(BOT)


obj:
	mkdir -p obj/Commands
	mkdir -p obj/bot
$(BIN)/%.o:./src/%.cpp  | $(BIN)
	$(CXX) -c $(CPPFLAGS) $< -o $@

obj/%.o : %.cpp
	$(CXX) -c $(CPPFLAGS) $< -o $@

$(NAME): $(OBJ_M) $(COMM)
	$(CXX) $(CPPFLAGS) $^ -o $@
$(BOT): $(BOT_FILES) src/utils.o
	$(CXX) $(CPPFLAGS) $^ -o $@
bonus: $(NAME_B)

$(NAME_B): $(OBJ_B)
	$(CC) $(FLAGS) $^ -o $@

-include $(DEP)

$(BIN):
	@mkdir $(BIN)

clean:
	@rm -rf $(BIN)
	rm -rf obj
	@echo "$(NAME) object files deleted"

fclean: clean
	@rm -f $(NAME)
	@rm -f $(NAME_B)

re: fclean all