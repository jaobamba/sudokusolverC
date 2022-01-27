all : third

third : third.c
	gcc -Wall -Werror -fsanitize=address third.c -o3 third

clean :
	rm -rf third