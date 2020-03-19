

set(command "/usr/bin/cmake;-DBUILD_TEST=OFF;-DCMAKE_INSTALL_PREFIX=/workspace/rocThrust/hipclang/build/release/rocPRIM;-DCMAKE_PREFIX_PATH=/opt/rocm;-GUnix Makefiles;/workspace/rocThrust/hipclang/build/release/rocPRIM-src")
execute_process(
  COMMAND ${command}
  RESULT_VARIABLE result
  OUTPUT_FILE "/workspace/rocThrust/hipclang/build/release/rocPRIM-download/rocPRIM-download-prefix/src/rocPRIM-download-stamp/rocPRIM-download-configure-out.log"
  ERROR_FILE "/workspace/rocThrust/hipclang/build/release/rocPRIM-download/rocPRIM-download-prefix/src/rocPRIM-download-stamp/rocPRIM-download-configure-err.log"
  )
if(result)
  set(msg "Command failed: ${result}\n")
  foreach(arg IN LISTS command)
    set(msg "${msg} '${arg}'")
  endforeach()
  set(msg "${msg}\nSee also\n  /workspace/rocThrust/hipclang/build/release/rocPRIM-download/rocPRIM-download-prefix/src/rocPRIM-download-stamp/rocPRIM-download-configure-*.log")
  message(FATAL_ERROR "${msg}")
else()
  set(msg "rocPRIM-download configure command succeeded.  See also /workspace/rocThrust/hipclang/build/release/rocPRIM-download/rocPRIM-download-prefix/src/rocPRIM-download-stamp/rocPRIM-download-configure-*.log")
  message(STATUS "${msg}")
endif()
