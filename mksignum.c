/* Yash: yet another shell */
/* mksignum.c: outputs string for 'signum.h' contents */
/* (C) 2007-2009 magicant */

/* This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.  */


#include "common.h"
#include <locale.h>
#include <signal.h>
#include <stdio.h>
#include <wchar.h>
#include "siglist.h"


int main(void)
{
    setlocale(LC_ALL, "");

    int min = 0;

    wprintf(L"/* signum.h: generated by mksignum */\n\n");
    wprintf(L"#ifndef SIGNUM_H\n#define SIGNUM_H\n\n");
    wprintf(L"#include <stddef.h>\n\n");

    for (const signal_T *s = signals; s->no; s++)
	if (min < s->no)
	    min = s->no;

    if (min < 100) {
	wprintf(L"/* injective function that returns an array index\n");
	wprintf(L" * corresponding to given signal number.\n");
	wprintf(L" * SIGNUM must not be a realtime signal number. */\n");
	wprintf(L"__attribute__((const))\n");
	wprintf(L"static inline size_t sigindex(int signum) {\n");
	wprintf(L"    return (size_t) signum;\n");
	wprintf(L"}\n\n");

	wprintf(L"/* max index returned by sigindex + 1 */\n");
	wprintf(L"#define MAXSIGIDX %d\n\n", min + 1);
    } else {
	sigset_t ss;
	size_t v;

	wprintf(L"/* injective function that returns an array index\n");
	wprintf(L" * corresponding to given signal number.\n");
	wprintf(L" * SIGNUM must not be a realtime signal number. */\n");
	wprintf(L"__attribute__((const))\n");
	wprintf(L"static inline size_t sigindex(int signum) {\n");
	wprintf(L"    switch (signum) {\n");
	wprintf(L"    case 0         : return 0;\n");

	sigemptyset(&ss);
	v = 1;
	for (const signal_T *s = signals; s->no; s++) {
	    if (!sigismember(&ss, s->no)) {
		sigaddset(&ss, s->no);
		wprintf(L"    case SIG%-7s: return %zu;\n", s->name, v++);
	    }
	}

	wprintf(L"    }\n");
	wprintf(L"}\n\n");

	wprintf(L"/* max index returned by sigindex + 1 */\n");
	wprintf(L"#define MAXSIGIDX %zu\n\n", v);
    }

    wprintf(L"/* number of realtime signals that can be handled by yash */\n");
    wprintf(L"#define RTSIZE %d\n\n",
#if defined SIGRTMIN && defined SIGRTMAX
	    SIGRTMAX - SIGRTMIN + 10
#else
	    0
#endif
	   );

    wprintf(L"#endif\n");

    return 0;
}


/* vim: set ts=8 sts=4 sw=4 noet: */
