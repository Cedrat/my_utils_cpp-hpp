NAME = a.out
SRCS = main.cpp errors.cpp utils.cpp

OBJS = ${SRCS:.cpp=.o}

CFLAGS = -Wall -Wextra -Werror

RM = rm -f

all : 		${NAME}

${NAME}:	${OBJS}
			clang++ -std=c++98 ${CFLAGS} ${SRCS}

clean :		
			${RM} ${OBJS} ${BONUS}

fclean :	clean
			${RM} a.out

re :		fclean all