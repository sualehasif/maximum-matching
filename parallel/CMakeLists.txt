cmake_minimum_required(VERSION 3.19)
project(maximum_matching)

set(CMAKE_CXX_STANDARD 17)

include_directories(gbbs)
include_directories(external/parlaylib/include)

add_executable(maximum_matching
        benchmarks/parallel-matching/MaximalMatching.h
        benchmarks/parallel-matching/metagraph.cc
        benchmarks/parallel-matching/metagraph.h 
        benchmarks/parallel-matching/CherryTree.h 
        benchmarks/parallel-matching/MVertex.h 
        benchmarks/parallel-matching/utils/Debug.h 
        benchmarks/parallel-matching/utils/HalfEdge.h 
        benchmarks/parallel-matching/MVertex.cpp 
        benchmarks/parallel-matching/utils/Statistics.h 
        benchmarks/parallel-matching/utils/List.h 
        benchmarks/parallel-matching/CherryBlossom.h)
