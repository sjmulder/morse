DESTDIR?=
PREFIX?=	/usr/local
MANPREFIX?=	${PREFIX}/man

CFLAGS+=	-Wall -Wextra

all: morse morse-pwmplay

clean:
	rm -f morse morse-pwmplay

install:
	install -d ${DESTDIR}${PREFIX}/bin
	install -d ${DESTDIR}${MANPREFIX}/man1
	install -m755 morse   morse-pwmplay   ${DESTDIR}${PREFIX}/bin/
	install -m644 morse.1 morse-pwmplay.1 \
	  ${DESTDIR}${MANPREFIX}/man1/

uninstall:
	rm -f \
	  ${DESTDIR}${PREFIX}/bin/morse \
	  ${DESTDIR}${PREFIX}/bin/morse-pwmplay \
	  ${DESTDIR}${MANPREFIX}/man1/morse.1 \
	  ${DESTDIR}${MANPREFIX}/man1/morse-pwmplay.1

.PHONY: all clean install uninstall
