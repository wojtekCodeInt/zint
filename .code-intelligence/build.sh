set -e

mkdir -p $WORK_DIR
cd $WORK_DIR

cmake -DCIFUZZ_INSTALL_ROOT=/opt/ci-fuzz-2.29.1 -DCMAKE_VERBOSE_MAKEFILE:BOOL=ON ..

make -j$(nproc)
