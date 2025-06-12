cmake_minimum_required(VERSION 3.25)

project(KAlg)

add_library(KAlg
	include/kalg/kalg.h src/kalg.c
	include/kalg/vector.h src/vector.c
	include/kalg/btree.h src/btree.c
)

target_include_directories(
	KAlg
	PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_subdirectory(test)