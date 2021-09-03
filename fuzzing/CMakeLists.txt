set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "/opt/ci-fuzz-2.22.0/lib/cmake")


find_package(CIFuzz)

add_cifuzz_test(ean_fuzzer
        SOURCES     fuzz_targets/ean_fuzzer.cpp
        MAX_RUNTIME "30m"
        PARALLEL_EXECUTIONS "2"
        SEED_CORPUS "a/b/c"
        TARGET_ARGS -foo --target=1
	ENGINE_ARGS -detect_leaks=0 -use_value_profile=1
)

cifuzz_test_link_libraries(ean_fuzzer zint)

target_include_directories(ean_fuzzer PRIVATE ../backend)
