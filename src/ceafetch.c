
# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <stdbool.h>
# include <math.h>

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
	/* # include <sysinfoapi.h> */

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

char* normalize(char *out, uint64_t bytes) {
	if (bytes >= (uint64_t) pow(10, 12)) {
		sprintf(out, "%.2f tb", (float)(bytes / pow(2, 40)));
		return out;
	} else if (bytes >= (uint64_t) pow(10, 9)) {
		sprintf(out, "%.2f gb", (float)(bytes / pow(2, 30)));
		return out;
	} else if (bytes >= (uint64_t) pow(10, 6)) {
		sprintf(out, "%.2f mb", (float)(bytes / pow(2, 20)));
		return out;
	} else if (bytes >= (uint64_t) pow(10, 3)) {
		sprintf(out, "%.2f kb", (float)(bytes / pow(2, 10)));
		return out;
	} else if (bytes < (uint64_t) pow(10, 3)) {
		sprintf(out, "%llu b", bytes);
		return out;
	} 
}

typedef struct sRAM {
	uint64_t used;
	uint64_t available;
	uint64_t all;
} sRAM;

int main () {

	# ifdef _WIN32
	// Get SHELL
	TCHAR name[MAX_LN];
	GetConsoleTitle(name, MAX_LN);
	int end = findChar(name, '-');
	substring(name, SHELL, 0, end > 0 ? end : MAX_LN);

	// Get LANG
	GetLocaleInfo(GetSystemDefaultUILanguage(), LOCALE_SENGLANGUAGE, LANG, MAX_LN);

	// Get RAM
	MEMORYSTATUSEX stx;
	stx.dwLength = sizeof(stx);
	GlobalMemoryStatusEx(&stx);
	sRAM RAM = {
		.all = (uint64_t) stx.ullTotalPhys,
		.available = (uint64_t) stx.ullAvailPhys,
		.used = (uint64_t) (stx.ullTotalPhys - stx.ullAvailPhys)
	};
	# endif

	// fetch out
	printf("\t\x1B[33m USER:%s \t%s \n", CNORM, USER);
	printf("\t\x1B[34m SHELL:%s\t%s \n", CNORM, SHELL);
	printf("\t\x1B[35m TERM:%s \t%s \n", CNORM, TERM);
	printf("\t\x1B[36m LANG:%s \t%s \n", CNORM, LANG);
	printf("\t\x1B[37m OS:%s \t%s \n", CNORM, OS);
	char u[256];
	char a[256];
	printf("\t\x1B[38m RAM:%s \t%s / %s \n", CNORM, normalize(u, RAM.used), normalize(a, RAM.all));
	printf("\t\t\t%s\x1B[40m  \x1B[41m  \x1B[42m  \x1B[43m  \x1B[44m  \x1B[45m  \x1B[46m  \x1B[47m  %s\n", CNORM, CNORM);
	printf("\t\t\t%s\x1B[100m  \x1B[101m  \x1B[102m  \x1B[103m  \x1B[104m  \x1B[105m  \x1B[106m  \x1B[107m  %s\n", CNORM, CNORM);

	return 0;
}


	
