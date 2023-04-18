NAME = webserv

CXXFLAGS = -Wall -Wextra -Werror -std=c++98

SRCDIR = srcs
OBJDIR = objs

SRCS = $(wildcard $(SRCDIR)/*.cpp)

OBJS = $(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

all: mkdir $(NAME)

mkdir:
	mkdir -p objs

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CXX) $(OBJS) $(CXXFLAGS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re mkdir