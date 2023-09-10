
# include <stdio.h>
# include <stdlib.h>

# include <stdbool.h>

# define MAX_LN 64

# ifdef _WIN32
	# define WINDOWS true
	# define LINUX false

	# include <windows.h>
	# include <minwindef.h>
	# include <tchar.h>
	# include <conio.h>

	# ifdef _WIN64
		# define OS "Windows (64-bit)"
	# else
		# define OS "Windows (32-bit)"
	# endif
	# define USER getenv("USERNAME")

# endif

# ifdef __linux__
	# define WINDOWS false
	# define LINUX true

	# define OS "Linux"
	# define USER getenv("USER")
	# define SHELL getenv("SHELL")
	# define TERM getenv("TERM")
	# define LANG getenv("LANG")

# endif

int main () {
	printf("%s, %s, %s \n", OS, USER, "a");

	return 0;
}


	
