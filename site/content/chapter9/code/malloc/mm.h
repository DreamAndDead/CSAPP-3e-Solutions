/* $begin mmheader */
/* $begin mallocinterface */
extern int mm_init(void);
extern void *mm_malloc (size_t size);
extern void mm_free (void *ptr);
/* $end mallocinterface */

#define malloc(size) mm_malloc(size)
#define free(ptr) mm_free(ptr)

extern void *mm_realloc(void *ptr, size_t size);
extern void *mm_calloc (size_t nmemb, size_t size);
extern void mm_checkheap(int verbose);
/* $end mmheader */
