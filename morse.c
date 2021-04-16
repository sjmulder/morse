#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#define LEN(a) (sizeof(a)/sizeof(*(a)))

static const char usage[] = "usage: morse [-d]\n";

static const char * const dict_alpha[] = {
	/* A */ ".-",
	/* B */ "-...",
	/* C */ "-.-.",
	/* D */ "-..",
	/* E */ ".",
	/* F */ "..-.",
	/* G */ "--.",
	/* H */ "....",
	/* I */ "..",
	/* J */ ".---",
	/* K */ "-.-",
	/* L */ ".-..",
	/* M */ "--",
	/* N */ "-.",
	/* O */ "---",
	/* P */ ".--.",
	/* Q */ "--.-",
	/* R */ ".-.",
	/* S */ "...",
	/* T */ "-",
	/* U */ "..-",
	/* V */ "...-",
	/* W */ ".--",
	/* X */ "-..-",
	/* Y */ "-.--",
	/* Z */ "--.."
};

static const char * const dict_num[] = {
	/* 0 */ "-----",
	/* 1 */ ".----",
	/* 2 */ "..---",
	/* 3 */ "...--",
	/* 4 */ "....-",
	/* 5 */ ".....",
	/* 6 */ "-....",
	/* 7 */ "--...",
	/* 8 */ "---..",
	/* 9 */ "----."
};

static const char lf[] = "\n";

static const char *
encode(char c)
{
	     if (c >= 'a' && c <= 'z') return dict_alpha[c-'a'];
	else if (c >= 'A' && c <= 'Z') return dict_alpha[c-'A'];
	else if (c >= '0' && c <= '9') return dict_num[c-'A'];
	else if (c == ' ' || c == '.' || c == '\n')
		return lf;
	else
		return NULL;
}

static int
decode(const char *s)
{
	int i;

	for (i=0; i < (int)LEN(dict_alpha); i++)
		if (!strcmp(s, dict_alpha[i]))
			return i+'A';

	for (i=0; i < (int)LEN(dict_num); i++)
		if (!strcmp(s, dict_num[i]))
			return i+'0';

	return -1;
}

int
main(int argc, char **argv)
{
	static char buf[1024];
	int c, opt_decode=0, col0=1, addsp=0;
	char *s, *word;
	const char *code;

	while ((c = getopt(argc, argv, "d")) != -1)
		switch (c) {
			case 'd': opt_decode = 1; break;
			default: fputs(usage, stderr); return 1;
		}

	if (optind > argc)
		{ fputs(usage, stderr); return 1; }

	if (opt_decode) {
		while ((s = fgets(buf, sizeof(buf), stdin))) {
			while ((word = strsep(&s, " \n"))) {
				if ((c = decode(word)) == -1)
					continue;
				if (addsp)
					{ putchar(' '); addsp=0; }
				putchar(c);
				col0=0;
			}
			addsp = !col0;
		}
	} else 
		while ((c = getchar()) != EOF)
			if (!(code = encode(c)))
				;
			else if (code == lf && !col0)
				{ fputs(code, stdout); col0 = 1; }
			else if (code != lf && col0)
				{ fputs(code, stdout); col0 = 0; }
			else if (code != lf && !col0)
				printf(" %s", code);

	if (!col0)
		printf("\n");
	return 0;
}
