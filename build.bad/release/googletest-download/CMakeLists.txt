# Distributed under the OSI-approved MIT License.  See accompanying
# file LICENSE or https://github.com/Crascit/DownloadProject for details.

cmake_minimum_required(VERSION 2.8.2)

project(googletest-download NONE)

include(ExternalProject)
if(TRUE)
    ExternalProject_Add(googletest-download
                        GIT_REPOSITORY;https://github.com/google/googletest.git;GIT_TAG;release-1.8.1;INSTALL_DIR;/workspace/rocThrust/hipclang/build/release/gtest;CMAKE_ARGS;-DBUILD_GTEST=ON;-DINSTALL_GTEST=ON;-Dgtest_force_shared_crt=ON;-DBUILD_SHARED_LIBS=ON;-DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>;LOG_DOWNLOAD;TRUE;LOG_CONFIGURE;TRUE;LOG_BUILD;TRUE;LOG_INSTALL;TRUE;UPDATE_DISCONNECTED;TRUE
                        SOURCE_DIR          "/workspace/rocThrust/hipclang/build/release/googletest-src"
                        BUILD_IN_SOURCE     TRUE
                        TEST_COMMAND        ""
    )
else()
    ExternalProject_Add(googletest-download
                        GIT_REPOSITORY;https://github.com/google/googletest.git;GIT_TAG;release-1.8.1;INSTALL_DIR;/workspace/rocThrust/hipclang/build/release/gtest;CMAKE_ARGS;-DBUILD_GTEST=ON;-DINSTALL_GTEST=ON;-Dgtest_force_shared_crt=ON;-DBUILD_SHARED_LIBS=ON;-DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>;LOG_DOWNLOAD;TRUE;LOG_CONFIGURE;TRUE;LOG_BUILD;TRUE;LOG_INSTALL;TRUE;UPDATE_DISCONNECTED;TRUE
                        SOURCE_DIR          "/workspace/rocThrust/hipclang/build/release/googletest-src"
                        BUILD_IN_SOURCE     TRUE
                        TEST_COMMAND        ""
                        UPDATE_COMMAND      ""
                        CONFIGURE_COMMAND   ""
                        BUILD_COMMAND       ""
                        INSTALL_COMMAND     ""
    )
endif()
