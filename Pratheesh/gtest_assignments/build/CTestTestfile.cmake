# CMake generated Testfile for 
# Source directory: F:/MCW/Submissions/FTTU-interns/Pratheesh/gtest_assignments
# Build directory: F:/MCW/Submissions/FTTU-interns/Pratheesh/gtest_assignments/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(math_lib_test "F:/MCW/Submissions/FTTU-interns/Pratheesh/gtest_assignments/build/math_lib_test.exe")
set_tests_properties(math_lib_test PROPERTIES  _BACKTRACE_TRIPLES "F:/MCW/Submissions/FTTU-interns/Pratheesh/gtest_assignments/CMakeLists.txt;33;add_test;F:/MCW/Submissions/FTTU-interns/Pratheesh/gtest_assignments/CMakeLists.txt;0;")
add_test(edge_case_tests "F:/MCW/Submissions/FTTU-interns/Pratheesh/gtest_assignments/build/edge_case_tests.exe")
set_tests_properties(edge_case_tests PROPERTIES  _BACKTRACE_TRIPLES "F:/MCW/Submissions/FTTU-interns/Pratheesh/gtest_assignments/CMakeLists.txt;34;add_test;F:/MCW/Submissions/FTTU-interns/Pratheesh/gtest_assignments/CMakeLists.txt;0;")
subdirs("googletest")
