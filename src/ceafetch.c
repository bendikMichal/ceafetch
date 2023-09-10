
# include <stdio.h>
# include <stdlib.h>

# include <stdbool.h>

# include "libs/stringEx.h"

# define MAX_LN 64

#define CNORM "\x1B[00m"

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

	printf("\t\x1B[32m OS:%s \t%s \n", CNORM, OS);
	printf("\t\x1B[33m USER:%s \t%s \n", CNORM, USER);
	printf("\t\x1B[34m SHELL:%s\t%s \n", CNORM, SHELL);
	printf("\t\x1B[35m TERM:%s \t%s \n", CNORM, TERM);
	printf("\t\x1B[36m LANG:%s \t%s \n", CNORM, LANG);
	printf("\t\t\t%s\x1B[40m \x1B[41m \x1B[42m \x1B[43m \x1B[44m \x1B[45m \x1B[46m \x1B[47m %s\n", CNORM, CNORM);

	return 0;
}


	
