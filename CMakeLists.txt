cmake_minimum_required(VERSION 3.25)

project(KAlg LANGUAGE C)

add_library(KAlg
	include/kalg/btree.h src/btree.c
)

target_include_directories(
	KAlg
	PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/include
)