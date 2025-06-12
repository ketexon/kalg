#define KALG_MALLOC TestMalloc
#define KALG_FREE TestFree
#define KALG_REALLOC TestRealloc

#include <ktest/KTest.hpp>
#include <kalg/kalg.h>
#include <kalg/vector.h>
#include <iostream>

size_t n_mallocs = 0;
size_t last_malloc = 0;

size_t n_reallocs = 0;
size_t last_realloc_size = 0;

size_t n_frees = 0;
size_t last_realloc = 0;

bool last_free_called = false;

extern "C"
{
	void *TestMalloc(size_t size)
	{
		n_mallocs++;
		last_malloc = size;
		return malloc(size);
	}

	void *TestRealloc(void *ptr, size_t size)
	{
		n_reallocs++;
		last_realloc_size = size;
		return realloc(ptr, size);
	}

	void TestFree(void *ptr)
	{
		n_frees++;
		last_free_called = true;
		free(ptr);
	}
}

TEST_CASE("Vector", vector)
{
	KAlg_LibraryFunctions functions = {
		.malloc = TestMalloc,
		.free = TestFree,
		.realloc = TestRealloc,
		.calloc = calloc,
		.memcpy = memcpy,
	};
	KAlg_SetLibraryFunctions(functions);

	n_mallocs = 0;
	n_reallocs = 0;
	n_frees = 0;

	KAlg_Vector vector;
	KAlg_Vector_Init(&vector, sizeof(int));

	test.AssertEq(vector.length, 0, "Initial length should be 0");
	test.AssertEq(vector.capacity, 0, "Initial capacity should be 0");
	test.AssertEq(vector.element_size, sizeof(int), "Element size should be initialized correctly");

	test.AssertEq(n_mallocs, 0, "No mallocs called for init");

	int element = 42;
	int *pushed_element = static_cast<int *>(KAlg_Vector_PushBack(&vector, &element));

	test.AssertEq(vector.length, 1, "Length should be 1 after pushing an element");
	test.AssertEq(vector.capacity, 4, "Capacity should be 4 after pushing first element");
	test.Assert(pushed_element != nullptr, "Pushed element should not be null");
	test.AssertEq(*pushed_element, 42, "Pushed element should be 42");

	test.AssertEq(n_mallocs, 1, "One malloc should be called for the first push");
	test.AssertEq(last_malloc, 4 * sizeof(int), "Malloc should allocate space for 4 integers");

	KAlg_Vector_PushBack(&vector, &element);
	test.AssertEq(vector.length, 2, "Length should be 2 after pushing another element");
	test.AssertEq(vector.capacity, 4, "Capacity should remain 4 after pushing second element");
	test.AssertEq(n_mallocs, 1, "No additional malloc should be called for the second push");

	KAlg_Vector_PushBack(&vector, &element);
	KAlg_Vector_PushBack(&vector, &element);
	KAlg_Vector_PushBack(&vector, &element);

	test.AssertEq(vector.length, 5, "Length should be 5 after pushing five elements");
	test.AssertEq(vector.capacity, 6, "Capacity should increase to 6 after pushing fifth element");
	test.AssertEq(n_reallocs, 1, "Should realloc once when capacity is exceeded");
	test.AssertEq(last_realloc_size, 6 * sizeof(int), "Realloc should allocate space for 6 integers");

	KAlg_Vector_Free(&vector);

	test.AssertEq(n_frees, 1, "One free should be called after freeing the vector");
}