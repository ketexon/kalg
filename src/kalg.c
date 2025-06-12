#include <kalg/kalg.h>

static KAlg_LibraryFunctions kalg_library_functions = {
	.malloc = NULL,
	.free = NULL,
	.realloc = NULL,
	.calloc = NULL,
	.memcpy = NULL};

void KAlg_SetLibraryFunctions(const KAlg_LibraryFunctions functions)
{
	kalg_library_functions = functions;
}

void *KAlg_Malloc(size_t size)
{
	if (kalg_library_functions.malloc)
	{
		return kalg_library_functions.malloc(size);
	}
	return KALG_MALLOC(size);
}

void KAlg_Free(void *ptr)
{
	if (kalg_library_functions.free)
	{
		kalg_library_functions.free(ptr);
	}
	else
	{
		KALG_FREE(ptr);
	}
}

void *KAlg_Realloc(void *ptr, size_t size)
{
	if (kalg_library_functions.realloc)
	{
		return kalg_library_functions.realloc(ptr, size);
	}
	return KALG_REALLOC(ptr, size);
}

void *KAlg_Calloc(size_t count, size_t size)
{
	if (kalg_library_functions.calloc)
	{
		return kalg_library_functions.calloc(count, size);
	}
	return KALG_CALLOC(count, size);
}

void *KAlg_Memcpy(void *dest, const void *src, size_t n)
{
	if (kalg_library_functions.memcpy)
	{
		return kalg_library_functions.memcpy(dest, src, n);
	}
	return KALG_MEMCPY(dest, src, n);
}