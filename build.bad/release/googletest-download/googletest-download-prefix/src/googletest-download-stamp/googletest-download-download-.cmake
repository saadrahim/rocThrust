

set(command "/usr/bin/cmake;-P;/workspace/rocThrust/hipclang/build/release/googletest-download/googletest-download-prefix/tmp/googletest-download-gitclone.cmake")
execute_process(
  COMMAND ${command}
  RESULT_VARIABLE result
  OUTPUT_FILE "/workspace/rocThrust/hipclang/build/release/googletest-download/googletest-download-prefix/src/googletest-download-stamp/googletest-download-download-out.log"
  ERROR_FILE "/workspace/rocThrust/hipclang/build/release/googletest-download/googletest-download-prefix/src/googletest-download-stamp/googletest-download-download-err.log"
  )
if(result)
  set(msg "Command failed: ${result}\n")
  foreach(arg IN LISTS command)
    set(msg "${msg} '${arg}'")
  endforeach()
  set(msg "${msg}\nSee also\n  /workspace/rocThrust/hipclang/build/release/googletest-download/googletest-download-prefix/src/googletest-download-stamp/googletest-download-download-*.log")
  message(FATAL_ERROR "${msg}")
else()
  set(msg "googletest-download download command succeeded.  See also /workspace/rocThrust/hipclang/build/release/googletest-download/googletest-download-prefix/src/googletest-download-stamp/googletest-download-download-*.log")
  message(STATUS "${msg}")
endif()
