cmake_minimum_required(VERSION 3.21)

project(
  integra_work_queue
  VERSION 0.1.0
  LANGUAGES CXX)

add_library(integra_work_queue INTERFACE)
add_library(Integra::work_queue ALIAS integra_work_queue)

target_include_directories(integra_work_queue
                           INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_features(integra_work_queue INTERFACE cxx_std_20)

# Dependants read the version from this property rather than from a variable: a
# variable set here is invisible in a sibling directory, and a stale one left in
# the parent scope would be read instead — a version check that silently passes.
set_target_properties(integra_work_queue PROPERTIES INTEGRA_VERSION
                                                    ${PROJECT_VERSION})

if(PROJECT_IS_TOP_LEVEL)
  include(FetchContent)
  FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.15.2)
  FetchContent_MakeAvailable(googletest)

  include(GoogleTest)
  enable_testing()

  add_executable(work-queue-test tests/work_queue_test.cpp)
  target_link_libraries(work-queue-test PRIVATE Integra::work_queue
                                                GTest::gtest_main)
  gtest_discover_tests(work-queue-test)
endif()
