NAME		= webserv
MODULES		= class main

SDIR		= src/
ODIR		= obj/
INCDIR		= includes
SRCDIR		= $(addprefix $(SDIR), $(MODULES))
OBJDIR		= $(addprefix $(ODIR), $(MODULES))

CXXFLAGS	= -Wall -Wextra -Werror -std=c++98
INCLUDES	= $(addprefix -I $(INCDIR)/, $(MODULES))

SRCS		= $(foreach dir, $(SRCDIR), $(wildcard $(dir)/*.cpp))
OBJS		= $(subst .cpp,.o,$(TEMP_OBJS))
TEMP_OBJS	= $(subst $(SDIR),$(ODIR),$(SRCS))

vpath %.cpp $(SRCDIR)

define compile
$1/%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $$< -o $$@
endef 

all: mkdir $(NAME)

mkdir:
	@mkdir -p $(OBJDIR)

$(NAME): $(OBJS)
	$(CXX) $(OBJS) $(CXXFLAGS) -o $(NAME)

$(foreach dir, $(OBJDIR), $(eval $(call compile, $(dir))))

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re mkdir