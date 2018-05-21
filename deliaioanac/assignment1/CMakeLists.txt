cmake_minimum_required(VERSION 2.6)
set (CMAKE_CXX_STANDARD 11)
 
# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
  
# Link runTests with what we want to test and the GTest and pthread library
add_executable(runCaseITests CaseIUnitTests.cpp)
target_link_libraries(runCaseITests ${GTEST_LIBRARIES} pthread)

add_executable(runCaseSTests CaseSUnitTests.cpp)
target_link_libraries(runCaseSTests ${GTEST_LIBRARIES} pthread)

add_executable(runSentencesTests SentencesUnitTests.cpp)
target_link_libraries(runSentencesTests ${GTEST_LIBRARIES} pthread)

add_executable(runKthToLastTests KthToLastUnitTests.cpp)
target_link_libraries(runKthToLastTests ${GTEST_LIBRARIES} pthread)
