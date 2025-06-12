#include <kalg/kalg.h>
#include <kalg/vector.h>

void KAlg_Vector_Init(KAlg_Vector *vector, size_t element_size)
{
	vector->data = NULL;
	vector->length = 0;
	vector->capacity = 0;
	vector->element_size = element_size;
}

void KAlg_Vector_Resize(KAlg_Vector *vector, size_t new_length)
{
	if (new_length > vector->capacity)
	{
		size_t new_capacity = vector->capacity > 0 ? vector->capacity * 1.6f : new_length;
		// if the new length is still larger than the new capacity,
		// just set the new capacity to the new length
		if (new_length > new_capacity)
		{
			new_capacity = new_length;
		}
		KAlg_Vector_Reserve(vector, new_capacity);
	}
	vector->length = new_length;
}

void KAlg_Vector_Reserve(KAlg_Vector *vector, size_t new_capacity)
{
	if (new_capacity > vector->capacity)
	{
		if (vector->data)
		{
			vector->data = KAlg_Realloc(vector->data, new_capacity * vector->element_size);
		}
		else
		{
			vector->data = KAlg_Malloc(new_capacity * vector->element_size);
		}
		vector->capacity = new_capacity;
	}
}

void *KAlg_Vector_PushBack(KAlg_Vector *vector, const void *element)
{
	if (vector->length >= vector->capacity)
	{
		size_t new_capacity = vector->capacity > 0 ? vector->capacity * 1.5 : 4;
		KAlg_Vector_Reserve(vector, new_capacity);
	}

	void *new_element_ptr = (char *)vector->data + vector->length * vector->element_size;
	KAlg_Memcpy(
		(char *)new_element_ptr,
		element,
		vector->element_size);
	vector->length++;
	return new_element_ptr;
}

void *KAlg_Vector_Get(const KAlg_Vector *vector, size_t index)
{
	return vector->data
			   ? ((char *)vector->data + index * vector->element_size)
			   : NULL;
}

void KAlg_Vector_Free(KAlg_Vector *vector)
{
	if (vector->data)
	{
		KAlg_Free(vector->data);
		vector->data = NULL;
	}
	vector->length = 0;
	vector->capacity = 0;
	vector->element_size = 0;
}
