#ifndef KALG_H
#define KALG_H

#ifndef KALG_MALLOC
#include <stdlib.h>
#define KALG_MALLOC malloc
#endif

#ifndef KALG_FREE
#include <stdlib.h>
#define KALG_FREE free
#endif

#ifndef KALG_REALLOC
#include <stdlib.h>
#define KALG_REALLOC realloc
#endif

#ifndef KALG_CALLOC
#include <stdlib.h>
#define KALG_CALLOC calloc
#endif

#ifndef KALG_MEMCPY
#include <string.h>
#define KALG_MEMCPY memcpy
#endif

typedef struct KAlg_LibraryFunctions
{
	void *(*malloc)(size_t size);
	void (*free)(void *ptr);
	void *(*realloc)(void *ptr, size_t size);
	void *(*calloc)(size_t count, size_t size);
	void *(*memcpy)(void *dest, const void *src, size_t n);
} KAlg_LibraryFunctions;

#ifdef __cplusplus
extern "C"
{
#endif

	void KAlg_SetLibraryFunctions(const KAlg_LibraryFunctions functions);

	void *KAlg_Malloc(size_t size);
	void KAlg_Free(void *ptr);
	void *KAlg_Realloc(void *ptr, size_t size);
	void *KAlg_Calloc(size_t count, size_t size);
	void *KAlg_Memcpy(void *dest, const void *src, size_t n);

#ifdef __cplusplus
}
#endif

#endif