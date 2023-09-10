
# include <stdio.h>
# include <stdlib.h>

# include <stdbool.h>

# include "libs/stringEx.h"

# define MAX_LN 64

# ifdef _WIN32
	# define WINDOWS true
	# define LINUX false

	# include <windows.h>
	# include <winnls.h>
	# include <minwindef.h>
	# include <tchar.h>
	# include <conio.h>

	# ifdef _WIN64
		# define OS "Windows (64-bit)"
	# else
		# define OS "Windows (32-bit)"
	# endif

	# define USER getenv("USERNAME")
	char SHELL[MAX_LN];
	# define TERM "..."
	TCHAR LANG[MAX_LN];


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

	# ifdef _WIN32
	// Get SHELL
	TCHAR name[MAX_LN];
	GetConsoleTitle(name, MAX_LN);
	int end = findChar(name, '-');
	substring(name, SHELL, 0, end > 0 ? end : MAX_LN);

	// Get LANG
	GetLocaleInfo(GetSystemDefaultUILanguage(), LOCALE_SENGLANGUAGE, LANG, MAX_LN);
	# endif

	printf("OS: %s \n", OS);
	printf("USER: %s \n", USER);
	printf("SHELL: %s \n", SHELL);
	printf("TERM: %s \n", TERM);
	printf("LANG: %s \n", LANG);

	return 0;
}


	
