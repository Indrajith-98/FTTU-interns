#include <gtest/gtest.h>

int main(int argc, char **argv)
{
    :: testing :: InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

/*
CMDS : gcov CMakeFiles/MathLib.dir/src/my_math.cpp.gcno

LCOV CMDS :

cd CMakeFiles/MathLib.dir/src

lcov --capture --directory . --output-file coverage.info

genhtml coverage.info --output-directory out

cd out

explorer index.html

*/ 