NAME = tester

$(NAME):
	clang++ -Wall -Wextra -Werror main.cpp list.cpp -std=c++98 -pedantic -o ./tester

asan:
	clang++ -fsanitize=address -Wall -Wextra -Werror main.cpp list.cpp -std=c++98 -pedantic -o ./tester

lsan:
	clang++ -fsanitize=leak -Wall -Wextra -Werror main.cpp list.cpp -std=c++98 -pedantic -o ./tester

all: $(NAME)

clean:
	echo ":-)"

fclean: clean
	rm tester

re: fclean
	all