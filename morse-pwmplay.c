#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <getopt.h>
#include <err.h>

#define TONE_HZ 440
#define DOT_MS 50

static const char usage[] =
"usage: morse-pwmplay [chip [channel]]\n";

static FILE *
xfopen(const char *fmt, ...)
{
	char buf[512];
	va_list ap;
	int n;
	FILE *f;

	va_start(ap, fmt);	
	n = vsnprintf(buf, sizeof(buf), fmt, ap);
	va_end(ap);

	if (n == -1) err(1, "snprintf");
	if (n >= (int)sizeof(buf)) errx(1, "buffer too small");
	if (!(f = fopen(buf, "w"))) err(1, "%s", buf);

	setbuf(f, NULL);
	return f;
}

int
main(int argc, char **argv)
{
	int chip=0, chan=0, c;
	FILE *export, *period, *duty, *enable;

	if (getopt(argc, argv, "") != -1)
		{ fputs(usage, stderr); return 1; }

	argc -= optind;
	argv += optind;
	if (argc > 2) { fputs(usage, stderr); return 1; }
	if (argc > 0) chip = (int)strtol(argv[0], NULL, 10);
	if (argc > 1) chan = (int)strtol(argv[1], NULL, 10);

	export = xfopen("/sys/class/pwm/pwmchip%d/export", chip);
	fputs("0", export);
	fclose(export);
	usleep(100000); /* wait for the export to happen */

	period = xfopen("/sys/class/pwm/pwmchip%d/pwm%d/period", chip,
	    chan);
	duty = xfopen("/sys/class/pwm/pwmchip%d/pwm%d/duty_cycle", chip,
	    chan);
	enable = xfopen("/sys/class/pwm/pwmchip%d/pwm%d/enable", chip,
	    chan);

	fprintf(period, "%ld", 1000000000L/TONE_HZ);
	fprintf(duty, "%ld", 1000000000L/TONE_HZ/2);

	while ((c = getchar()) != EOF)
		switch (c) {
		case '.':
			fputs("1", enable); usleep(1000L*DOT_MS);
			fputs("0", enable); usleep(1000L*DOT_MS);
			break;
		case '-':
			fputs("1", enable); usleep(1000L*DOT_MS*3);
			fputs("0", enable); usleep(1000L*DOT_MS);
			break;
		case ' ':
			usleep(1000L*DOT_MS*2);
			break;
		case '\n':
			usleep(1000L*DOT_MS*6);
			break;
		}

	fputs("0", enable);
	fclose(enable);
	fclose(period);
	fclose(duty);

	return 0;
}
