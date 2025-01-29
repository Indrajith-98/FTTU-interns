# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "F:/MULTICOREWARE_FTU_INTERN/GTEST/build/_deps/gtest-src")
  file(MAKE_DIRECTORY "F:/MULTICOREWARE_FTU_INTERN/GTEST/build/_deps/gtest-src")
endif()
file(MAKE_DIRECTORY
  "F:/MULTICOREWARE_FTU_INTERN/GTEST/build/_deps/gtest-build"
  "F:/MULTICOREWARE_FTU_INTERN/GTEST/build/_deps/gtest-subbuild/gtest-populate-prefix"
  "F:/MULTICOREWARE_FTU_INTERN/GTEST/build/_deps/gtest-subbuild/gtest-populate-prefix/tmp"
  "F:/MULTICOREWARE_FTU_INTERN/GTEST/build/_deps/gtest-subbuild/gtest-populate-prefix/src/gtest-populate-stamp"
  "F:/MULTICOREWARE_FTU_INTERN/GTEST/build/_deps/gtest-subbuild/gtest-populate-prefix/src"
  "F:/MULTICOREWARE_FTU_INTERN/GTEST/build/_deps/gtest-subbuild/gtest-populate-prefix/src/gtest-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "F:/MULTICOREWARE_FTU_INTERN/GTEST/build/_deps/gtest-subbuild/gtest-populate-prefix/src/gtest-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "F:/MULTICOREWARE_FTU_INTERN/GTEST/build/_deps/gtest-subbuild/gtest-populate-prefix/src/gtest-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
