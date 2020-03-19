

set(command "/usr/bin/cmake;-DBUILD_GTEST=ON;-DINSTALL_GTEST=ON;-Dgtest_force_shared_crt=ON;-DBUILD_SHARED_LIBS=ON;-DCMAKE_INSTALL_PREFIX=/workspace/rocThrust/hipclang/build/release/gtest;-GUnix Makefiles;/workspace/rocThrust/hipclang/build/release/googletest-src")
execute_process(
  COMMAND ${command}
  RESULT_VARIABLE result
  OUTPUT_FILE "/workspace/rocThrust/hipclang/build/release/googletest-download/googletest-download-prefix/src/googletest-download-stamp/googletest-download-configure-out.log"
  ERROR_FILE "/workspace/rocThrust/hipclang/build/release/googletest-download/googletest-download-prefix/src/googletest-download-stamp/googletest-download-configure-err.log"
  )
if(result)
  set(msg "Command failed: ${result}\n")
  foreach(arg IN LISTS command)
    set(msg "${msg} '${arg}'")
  endforeach()
  set(msg "${msg}\nSee also\n  /workspace/rocThrust/hipclang/build/release/googletest-download/googletest-download-prefix/src/googletest-download-stamp/googletest-download-configure-*.log")
  message(FATAL_ERROR "${msg}")
else()
  set(msg "googletest-download configure command succeeded.  See also /workspace/rocThrust/hipclang/build/release/googletest-download/googletest-download-prefix/src/googletest-download-stamp/googletest-download-configure-*.log")
  message(STATUS "${msg}")
endif()
