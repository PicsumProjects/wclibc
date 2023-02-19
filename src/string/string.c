#include <string.h>
#include <malloc.h>
#include <stdint.h>

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

int strinstr(const char *haystack, const char *needle)
{
  size_t haystack_dimensions = strlen(haystack);
  size_t i = haystack_dimensions;
  size_t needlewidth = strlen(needle);
  while(i--) if(!((i + needlewidth) > haystack_dimensions))) if(memcmp(((uintptr_t)haystack) + i, needle, needlewidth) return 1; 
};