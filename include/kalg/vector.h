#ifndef KALG_VECTOR_H
#define KALG_VECTOR_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stddef.h>

	typedef struct KAlg_Vector
	{
		void *data;
		size_t length;
		size_t capacity;
		size_t element_size;
	} KAlg_Vector;

	void KAlg_Vector_Init(KAlg_Vector *vector, size_t element_size);

	void KAlg_Vector_Resize(KAlg_Vector *vector, size_t new_length);
	void KAlg_Vector_Reserve(KAlg_Vector *vector, size_t new_capacity);

	void *KAlg_Vector_PushBack(KAlg_Vector *vector, const void *element);

	void *KAlg_Vector_Get(const KAlg_Vector *vector, size_t index);

	void KAlg_Vector_Free(KAlg_Vector *vector);

#ifdef __cplusplus
}
#endif

#endif