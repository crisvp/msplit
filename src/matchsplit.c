#include <string.h>
#include <ctype.h>

size_t matchsplit(char *s, char **argv, size_t max) {
	size_t argc = 0;
	char c, *t;
	static const char *bra = "([{<`'\"";
	static const char *ket = ")]}>''\"";

	if(!s)
		return 0;

	max--;

	for(;;) {
		while(isspace(c = *s))
			s++;
		if(!c)
			break;
		if(argc == max) {
			if(argv)
				argv[argc] = s;
			argc++;
			break;
		}
		t = strchr(bra, c);
		if(t) {
			t = strchr(++s, t[ket-bra]);
		} else {
			t = s;
			for(;;) {
				c = *t;
				if(isspace(c)) {
					break;
				} else if(c) {
					t++;
				} else {
					t = NULL;
					break;
				}
			}
		}
		if(argv)
			argv[argc] = s;
		argc++;
		if(!t)
			break;
		if(argv)
			*t = '\0';
		s = t + 1;
	}

	return argc;
}
