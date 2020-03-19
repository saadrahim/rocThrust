if("5fa0c79fbb199f83c5202d9e218311a78335a1f4" STREQUAL "")
  message(FATAL_ERROR "Tag for git checkout should not be empty.")
endif()

set(run 0)

if("/workspace/rocThrust/hipclang/build/release/rocPRIM-download/rocPRIM-download-prefix/src/rocPRIM-download-stamp/rocPRIM-download-gitinfo.txt" IS_NEWER_THAN "/workspace/rocThrust/hipclang/build/release/rocPRIM-download/rocPRIM-download-prefix/src/rocPRIM-download-stamp/rocPRIM-download-gitclone-lastrun.txt")
  set(run 1)
endif()

if(NOT run)
  message(STATUS "Avoiding repeated git clone, stamp file is up to date: '/workspace/rocThrust/hipclang/build/release/rocPRIM-download/rocPRIM-download-prefix/src/rocPRIM-download-stamp/rocPRIM-download-gitclone-lastrun.txt'")
  return()
endif()

execute_process(
  COMMAND ${CMAKE_COMMAND} -E remove_directory "/workspace/rocThrust/hipclang/build/release/rocPRIM-src"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to remove directory: '/workspace/rocThrust/hipclang/build/release/rocPRIM-src'")
endif()

# try the clone 3 times incase there is an odd git clone issue
set(error_code 1)
set(number_of_tries 0)
while(error_code AND number_of_tries LESS 3)
  execute_process(
    COMMAND "/usr/bin/git" clone --origin "origin" "https://github.com/ROCmSoftwarePlatform/rocPRIM.git" "rocPRIM-src"
    WORKING_DIRECTORY "/workspace/rocThrust/hipclang/build/release"
    RESULT_VARIABLE error_code
    )
  math(EXPR number_of_tries "${number_of_tries} + 1")
endwhile()
if(number_of_tries GREATER 1)
  message(STATUS "Had to git clone more than once:
          ${number_of_tries} times.")
endif()
if(error_code)
  message(FATAL_ERROR "Failed to clone repository: 'https://github.com/ROCmSoftwarePlatform/rocPRIM.git'")
endif()

execute_process(
  COMMAND "/usr/bin/git" checkout 5fa0c79fbb199f83c5202d9e218311a78335a1f4
  WORKING_DIRECTORY "/workspace/rocThrust/hipclang/build/release/rocPRIM-src"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to checkout tag: '5fa0c79fbb199f83c5202d9e218311a78335a1f4'")
endif()

execute_process(
  COMMAND "/usr/bin/git" submodule init 
  WORKING_DIRECTORY "/workspace/rocThrust/hipclang/build/release/rocPRIM-src"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to init submodules in: '/workspace/rocThrust/hipclang/build/release/rocPRIM-src'")
endif()

execute_process(
  COMMAND "/usr/bin/git" submodule update --recursive 
  WORKING_DIRECTORY "/workspace/rocThrust/hipclang/build/release/rocPRIM-src"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to update submodules in: '/workspace/rocThrust/hipclang/build/release/rocPRIM-src'")
endif()

# Complete success, update the script-last-run stamp file:
#
execute_process(
  COMMAND ${CMAKE_COMMAND} -E copy
    "/workspace/rocThrust/hipclang/build/release/rocPRIM-download/rocPRIM-download-prefix/src/rocPRIM-download-stamp/rocPRIM-download-gitinfo.txt"
    "/workspace/rocThrust/hipclang/build/release/rocPRIM-download/rocPRIM-download-prefix/src/rocPRIM-download-stamp/rocPRIM-download-gitclone-lastrun.txt"
  WORKING_DIRECTORY "/workspace/rocThrust/hipclang/build/release/rocPRIM-src"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to copy script-last-run stamp file: '/workspace/rocThrust/hipclang/build/release/rocPRIM-download/rocPRIM-download-prefix/src/rocPRIM-download-stamp/rocPRIM-download-gitclone-lastrun.txt'")
endif()

