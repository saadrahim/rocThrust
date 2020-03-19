

set(command "${make};install")
execute_process(
  COMMAND ${command}
  RESULT_VARIABLE result
  OUTPUT_FILE "/workspace/rocThrust/hipclang/build/release/googletest-download/googletest-download-prefix/src/googletest-download-stamp/googletest-download-install-out.log"
  ERROR_FILE "/workspace/rocThrust/hipclang/build/release/googletest-download/googletest-download-prefix/src/googletest-download-stamp/googletest-download-install-err.log"
  )
if(result)
  set(msg "Command failed: ${result}\n")
  foreach(arg IN LISTS command)
    set(msg "${msg} '${arg}'")
  endforeach()
  set(msg "${msg}\nSee also\n  /workspace/rocThrust/hipclang/build/release/googletest-download/googletest-download-prefix/src/googletest-download-stamp/googletest-download-install-*.log")
  message(FATAL_ERROR "${msg}")
else()
  set(msg "googletest-download install command succeeded.  See also /workspace/rocThrust/hipclang/build/release/googletest-download/googletest-download-prefix/src/googletest-download-stamp/googletest-download-install-*.log")
  message(STATUS "${msg}")
endif()
