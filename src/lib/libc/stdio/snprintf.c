#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

int snprintf(char *str, size_t n, const char *fmt, ...)
{
	va_list ap;
	int ret;
	char dummy;
	FILE f;
	struct __sfileext fext;
	/* While snprintf(3) specifies size_t stdio uses an int internally */
	if (n > INT_MAX)
		n = INT_MAX;
	/* Stdio internals do not deal correctly with zero length buffer */
	if (n == 0) {
		str = &dummy;
		n = 1;
	}
	_FILEEXT_SETUP(&f, &fext);
	f._file = -1;
	f._flags = __SWR | __SSTR;
	f._bf._base = f._p = (unsigned char *)str;
	f._bf._size = f._w = n - 1;
	va_start(ap, fmt);
	ret = __vfprintf(&f, fmt, ap);
	va_end(ap);
	*f._p = '\0';
	return (ret);
}