#include <string.h>
#include <malloc.h>
#include <stdint.h>
#include <errno.h>
#if __wasm64__
#define ULONG_MAX 18446744073709551615
#else
#define ULONG_MAX 4294967295
#endif

void *memset(void *p1, int val, size_t size)
{
  char val_char = (char)val;
  size_t i = size;
  char *ptr = (char *)p1;
  while(i--)
    ptr[i] = val_char;
  return ptr;
};
  

void *memcpy(void *p1 __restrict, const void *p2 __restrict, size_t size)
{
  if((p1 == NULL) || (p2 == NULL)) return NULL;
  if(size < 4)
  {
    size_t i = size;
    char *ptr1 = (char *)p1;
    char *ptr2 = (char *)p2;
    while(i--) ptr1[i] = ptr2[i];
  } else {
    long *ptr1 = (long *)p1;
    long *ptr2 = (long *)p2;
    size_t newsize = (size - (size % sizeof(long))) / 4;
    size_t i = newsize;
    while(i--) ptr1[i] = ptr2[i];
    if(!(size - newsize)) return p1;
    memcpy((void *)(((uintptr_t)ptr1) + newsize), (void *)(((uintptr_t)ptr2) + newsize), size - newsize);
  };
  
  return p1;
};

void *memmove(void *dest, const void *src, size_t n) 
{
  if(
    ((((uintptr_t)dest) + n)
    > ((uintptr_t)src)) ||
    ((((uintptr_t)src) + n)
    > ((uintptr_t)dest))
  ) {
    void *temp = malloc(n);
    memcpy(temp, src, n);
    memcpy(dest, temp, n);
    free(temp);
    return dest;
  } else return memcpy(dest, src, n);
};

int memcmp(const void *p1, const void *p2, size_t size)
{
  if((p1 == NULL) || (p2 == NULL)) return NULL;
  if(size < 4)
  {
    size_t i = size;
    char *ptr1 = (char *)p1;
    char *ptr2 = (char *)p2;
    while(i--) if(ptr1[i] != ptr2[i]) return 0;
  } else {
    long *ptr1 = (long *)p1;
    long *ptr2 = (long *)p2;
    size_t newsize = (size - (size % sizeof(long))) / 4;
    size_t i = newsize;
    while(i--) if(ptr1[i] != ptr2[i]) return 0;
    return memcmp((void *)(((uintptr_t)ptr1) + newsize), (void *)(((uintptr_t)ptr2) + newsize), size - newsize);
  };
};

size_t strlen(const char *buf)
{
  size_t i = 0;
  while(i++) if(!(buf[i]) || i == 16384) return i;
};

int strcmp(const char *str1, const char *str2)
{
  return memcmp(str1, str2, strlen(str1));
};

char *strcpy(char *dest __restrict, const char *src __restrict)
{
  return (char *)memcpy(dest, src, strlen(src));
};

int strncmp(const char *p1, const char *p2, size_t size)
{ return memcmp(p1, p2, size); };

size_t strnlen(const char *buf, size_t maxsize)
{
  size_t i = 0;
  while(i++) if(!(buf[i]) || i == maxsize) return i;
};

#define ISSPACE(x) x == 0x20
#define ISUPPER(x) ((x >= 0x41) && (x < 0x60))
#define ISLOWER(x) ((x >= 0x61) && (x < 0x7B))
#define ISDIGIT(x) ((x >= 0x30) && (x < 0x3A))
#define ISALPHA(x) (ISUPPER(x) || ISLOWER(x))
// from gcc
unsigned long
strtoul(const char *nptr, char **endptr, register int base)
{
	register const char *s = nptr;
	register unsigned long acc;
	register int c;
	register unsigned long cutoff;
	register int neg = 0, any, cutlim;

	/*
	 * See strtol for comments as to the logic used.
	 */
	do {
		c = *s++;
	} while (ISSPACE(c));
	if (c == '-') {
		neg = 1;
		c = *s++;
	} else if (c == '+')
		c = *s++;
	if ((base == 0 || base == 16) &&
	    c == '0' && (*s == 'x' || *s == 'X')) {
		c = s[1];
		s += 2;
		base = 16;
	}
	if (base == 0)
		base = c == '0' ? 8 : 10;
	cutoff = (unsigned long)ULONG_MAX / (unsigned long)base;
	cutlim = (unsigned long)ULONG_MAX % (unsigned long)base;
	for (acc = 0, any = 0;; c = *s++) {
		if (ISDIGIT(c))
			c -= '0';
		else if (ISALPHA(c))
			c -= ISUPPER(c) ? 'A' - 10 : 'a' - 10;
		else
			break;
		if (c >= base)
			break;
		if (any < 0 || acc > cutoff || (acc == cutoff && c > cutlim))
			any = -1;
		else {
			any = 1;
			acc *= base;
			acc += c;
		}
	}
	if (any < 0) {
		acc = ULONG_MAX;
		errno = ERANGE;
	} else if (neg)
		acc = -acc;
	if (endptr != 0)
		*endptr = (char *) (any ? s - 1 : nptr);
	return (acc);
}
