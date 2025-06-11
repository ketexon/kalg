include(FetchContent)

FetchContent_Declare(
	KTest
	GIT_REPOSITORY https://github.com/ketexon/ktest.git
)
FetchContent_MakeAvailable(KTest)

add_executable(
	KAlgTest
	btree.cpp
)