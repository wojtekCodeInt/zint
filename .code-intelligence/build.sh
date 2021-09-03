set -e

mkdir -p $WORK_DIR
cd $WORK_DIR

cmake -DCI_FUZZ_INSTALL_ROOT=/opt/ci-fuzz-2.22.0 -DCMAKE_VERBOSE_MAKEFILE:BOOL=ON ..

make -j$(nproc)
