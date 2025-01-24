# CMake generated Testfile for 
# Source directory: O:/Training Assignments/GTEST
# Build directory: O:/Training Assignments/GTEST/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if(CTEST_CONFIGURATION_TYPE MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test(GTestExample "O:/Training Assignments/GTEST/build/Debug/GTestExample.exe")
  set_tests_properties(GTestExample PROPERTIES  _BACKTRACE_TRIPLES "O:/Training Assignments/GTEST/CMakeLists.txt;47;add_test;O:/Training Assignments/GTEST/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test(GTestExample "O:/Training Assignments/GTEST/build/Release/GTestExample.exe")
  set_tests_properties(GTestExample PROPERTIES  _BACKTRACE_TRIPLES "O:/Training Assignments/GTEST/CMakeLists.txt;47;add_test;O:/Training Assignments/GTEST/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test(GTestExample "O:/Training Assignments/GTEST/build/MinSizeRel/GTestExample.exe")
  set_tests_properties(GTestExample PROPERTIES  _BACKTRACE_TRIPLES "O:/Training Assignments/GTEST/CMakeLists.txt;47;add_test;O:/Training Assignments/GTEST/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test(GTestExample "O:/Training Assignments/GTEST/build/RelWithDebInfo/GTestExample.exe")
  set_tests_properties(GTestExample PROPERTIES  _BACKTRACE_TRIPLES "O:/Training Assignments/GTEST/CMakeLists.txt;47;add_test;O:/Training Assignments/GTEST/CMakeLists.txt;0;")
else()
  add_test(GTestExample NOT_AVAILABLE)
endif()
subdirs("_deps/googletest-build")
