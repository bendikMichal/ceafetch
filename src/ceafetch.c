
# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <stdbool.h>
# include <math.h>
# include <string.h>

# include "libs/stringEx.h"

# define MAX_LN 64

# define CNORM "\x1B[00m"

# ifdef _WIN32
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
	# include <sys/sysinfo.h>
	# include <unistd.h>
	
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

	sRAM RAM = {};
	# ifdef _WIN32

	char logo[6][66] = {
	" ______     ______     ______    ",
	"/\\  ___\\   /\\  ___\\   /\\  __ \\   ",
	"\\ \\ \\____  \\ \\  __\\   \\ \\  __ \\  ",
	" \\ \\_____\\  \\ \\_____\\  \\ \\_\\ \\_\\ ",
	"  \\/_____/   \\/_____/   \\/_/\\/_/ ",
	"                                 "
	};

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
	RAM.all = (uint64_t) stx.ullTotalPhys;
	RAM.available = (uint64_t) stx.ullAvailPhys;
	RAM.used = (uint64_t) (stx.ullTotalPhys - stx.ullAvailPhys);
	# endif

	# ifdef __linux__

	char logo[6][66] = {
	" ██████╗███████╗ █████╗",
	"██ ════ ██ ════╝██ ══██╗",
	"██║     █████╗  ███████║",
	"██║     ██ ══╝  ██ ══██║",
	"╚██████ ███████ ██║  ██║",
	"                        "
	};

	// Get Available RAM
	FILE* memf = fopen("/proc/meminfo", "r");
	if (memf == NULL) {
		printf("Failed to load /proc/meminfo \n");
	}
	char lnbuf[256];
	unsigned long av;
	while (fgets(lnbuf, sizeof(lnbuf), memf)) {
		if (sscanf(lnbuf, "MemAvailable: %lu kB", &av)) break;
	}
	fclose(memf);
	RAM.available = (uint64_t) av * 1024;
	// works too but does not count cached RAM
	/* RAM.available = get_avphys_pages() * sysconf(_SC_PAGESIZE); */
	/* RAM.available = sysconf(_SC_AVPHYS_PAGES) * sysconf(_SC_PAGESIZE); */

	RAM.all = get_phys_pages() * sysconf(_SC_PAGESIZE);

	RAM.used = RAM.all - RAM.available;
	# endif

	// fetch out
	printf("\n");
	char o[MAX_LN];
	printf("\t%s \t\x1B[32m USER:%s \t%s \n", logo[0], CNORM, USER);
	printf("\t%s\t\x1B[33m SHELL:%s\t%s \n", logo[1], CNORM, SHELL);
	printf("\t%s\t\x1B[34m TERM:%s \t%s \n", logo[2], CNORM, TERM);
	printf("\t%s\t\x1B[35m LANG:%s \t%s \n", logo[3], CNORM, LANG);
	printf("\t%s\t\x1B[36m OS:%s \t%s \n", logo[4], CNORM, OS);
	char u[256];
	char a[256];
	printf("\t%s\t\x1B[37m RAM:%s \t%s / %s \n", logo[5], CNORM, normalize(u, RAM.used), normalize(a, RAM.all));

	printf("\t\t\t%s\x1B[40m  \x1B[41m  \x1B[42m  \x1B[43m  \x1B[44m  \x1B[45m  \x1B[46m  \x1B[47m  %s\n", CNORM, CNORM);
	printf("\t\t\t%s\x1B[100m  \x1B[101m  \x1B[102m  \x1B[103m  \x1B[104m  \x1B[105m  \x1B[106m  \x1B[107m  %s\n", CNORM, CNORM);
	printf("\n");

	return 0;
}


	
