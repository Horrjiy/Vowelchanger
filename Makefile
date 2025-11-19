CXX			:=	c++
CXXFLAGS	:=	-Wall -Wextra -Werror -std=c++17
NAME		:=	Vowelchanger.exe

SRCS		=	src\main.cpp \
				src\file_handling.cpp src\window_process.cpp src\window_start.cpp
OBJS		= $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(OBJS) $(CXXFLAGS) -o $(NAME)

clean:
	@del /Q $(OBJS) 2>nul

fclean: clean
	@del /Q $(NAME) 2>nul

re: fclean all

.SILENT: $(OBJS) $(NAME) 
.PHONY: all clean fclean re