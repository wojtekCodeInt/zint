set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CIFUZZ_INSTALL_ROOT}/share/cmake")

find_package(CIFuzz)

file(GLOB targets "fuzz_targets/*.cpp")
foreach(fuzzer_source ${targets})

  get_filename_component(fuzzer ${fuzzer_source} NAME_WE)

  add_cifuzz_test(${fuzzer}
    SOURCES     ${fuzzer_source}
    MAX_RUNTIME "30m"
    PARALLEL_EXECUTIONS "2"
    SEED_CORPUS "${CMAKE_CURRENT_SOURCE_DIR}/seeds/${fuzzer}"
  )
  
  cifuzz_test_link_libraries(${fuzzer} zint)
  
  target_include_directories(${fuzzer} PRIVATE ../backend)

endforeach()
