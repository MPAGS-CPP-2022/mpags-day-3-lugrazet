# - Build sub-script for the MPAGSCipher library unit tests

# - Create interface library for Catch
add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE ${CMAKE_CURRENT_LIST_DIR})
target_compile_features(Catch INTERFACE cxx_noexcept)

# - Catch-test
add_executable(testCatch testCatch.cpp)
target_link_libraries(testCatch Catch)
add_test(NAME test-Catch COMMAND testCatch)

# - TransformChar test.
add_executable(testTransformChar testTransformChar.cpp)
target_link_libraries(testTransformChar MPAGSCipher Catch)
add_test(NAME test-TransformChar COMMAND testTransformChar)

# - CaesarCipher test.
add_executable(testCaesarCipher testCaesarCipher.cpp)
target_link_libraries(testCaesarCipher MPAGSCipher Catch)
add_test(NAME test-CaesarCipher COMMAND testCaesarCipher)

# - ProcessCommandLine test.
add_executable(testProcessCommandLine testProcessCommandLine.cpp)
target_link_libraries(testProcessCommandLine MPAGSCipher Catch)
add_test(NAME test-ProcessCommandLine COMMAND testProcessCommandLine)


