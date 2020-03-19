# Distributed under the OSI-approved MIT License.  See accompanying
# file LICENSE or https://github.com/Crascit/DownloadProject for details.

cmake_minimum_required(VERSION 2.8.2)

project(rocPRIM-download NONE)

include(ExternalProject)
if(TRUE)
    ExternalProject_Add(rocPRIM-download
                        GIT_REPOSITORY;https://github.com/ROCmSoftwarePlatform/rocPRIM.git;GIT_TAG;5fa0c79fbb199f83c5202d9e218311a78335a1f4;INSTALL_DIR;/workspace/rocThrust/hipclang/build/release/rocPRIM;CMAKE_ARGS;-DBUILD_TEST=OFF;-DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>;-DCMAKE_PREFIX_PATH=/opt/rocm;LOG_DOWNLOAD;TRUE;LOG_CONFIGURE;TRUE;LOG_BUILD;TRUE;LOG_INSTALL;TRUE;UPDATE_DISCONNECTED;TRUE
                        SOURCE_DIR          "/workspace/rocThrust/hipclang/build/release/rocPRIM-src"
                        BUILD_IN_SOURCE     TRUE
                        TEST_COMMAND        ""
    )
else()
    ExternalProject_Add(rocPRIM-download
                        GIT_REPOSITORY;https://github.com/ROCmSoftwarePlatform/rocPRIM.git;GIT_TAG;5fa0c79fbb199f83c5202d9e218311a78335a1f4;INSTALL_DIR;/workspace/rocThrust/hipclang/build/release/rocPRIM;CMAKE_ARGS;-DBUILD_TEST=OFF;-DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>;-DCMAKE_PREFIX_PATH=/opt/rocm;LOG_DOWNLOAD;TRUE;LOG_CONFIGURE;TRUE;LOG_BUILD;TRUE;LOG_INSTALL;TRUE;UPDATE_DISCONNECTED;TRUE
                        SOURCE_DIR          "/workspace/rocThrust/hipclang/build/release/rocPRIM-src"
                        BUILD_IN_SOURCE     TRUE
                        TEST_COMMAND        ""
                        UPDATE_COMMAND      ""
                        CONFIGURE_COMMAND   ""
                        BUILD_COMMAND       ""
                        INSTALL_COMMAND     ""
    )
endif()
