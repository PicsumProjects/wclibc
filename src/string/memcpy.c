#include <string.h>
#include <stdint.h>
#include <endian.h>

void *memcpy(void *restrict dest, const void *restrict src, size_t n)
{
	
	if((n & (~3)) == n)
	{
		unsigned long *d = (unsigned long *)dest;
		const unsigned long *s = (const unsigned long *)src;
		size_t i = (n & (~3))-1;
		while(i--)
			d[i] = s[i];
	} else if (n > 3) {
		memcpy(dest, src, (n & (~3)));
		memcpy(dest, src, (((n & (~3)) - n)));
	} else {
		unsigned char *d = (unsigned char *)dest;
		const unsigned char *s = (const unsigned char *)src;
		size_t i = n;
		while(i--) d[i] = s[i];
	};

	return dest;
}
