

set(command "/usr/bin/cmake;-P;/workspace/rocThrust/hipclang/build/release/rocPRIM-download/rocPRIM-download-prefix/tmp/rocPRIM-download-gitclone.cmake")
execute_process(
  COMMAND ${command}
  RESULT_VARIABLE result
  OUTPUT_FILE "/workspace/rocThrust/hipclang/build/release/rocPRIM-download/rocPRIM-download-prefix/src/rocPRIM-download-stamp/rocPRIM-download-download-out.log"
  ERROR_FILE "/workspace/rocThrust/hipclang/build/release/rocPRIM-download/rocPRIM-download-prefix/src/rocPRIM-download-stamp/rocPRIM-download-download-err.log"
  )
if(result)
  set(msg "Command failed: ${result}\n")
  foreach(arg IN LISTS command)
    set(msg "${msg} '${arg}'")
  endforeach()
  set(msg "${msg}\nSee also\n  /workspace/rocThrust/hipclang/build/release/rocPRIM-download/rocPRIM-download-prefix/src/rocPRIM-download-stamp/rocPRIM-download-download-*.log")
  message(FATAL_ERROR "${msg}")
else()
  set(msg "rocPRIM-download download command succeeded.  See also /workspace/rocThrust/hipclang/build/release/rocPRIM-download/rocPRIM-download-prefix/src/rocPRIM-download-stamp/rocPRIM-download-download-*.log")
  message(STATUS "${msg}")
endif()
