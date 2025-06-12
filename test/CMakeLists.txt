include(FetchContent)

FetchContent_Declare(
	KTest
	GIT_REPOSITORY https://github.com/ketexon/ktest.git
	GIT_TAG main
)
FetchContent_MakeAvailable(KTest)

add_executable(
	KAlgTest
	vector.cpp
)

target_link_libraries(
	KAlgTest
	KAlg
	KTestWithMain
)