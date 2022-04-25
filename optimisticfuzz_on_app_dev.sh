#!/bin/sh
alias adctl="cictl -s grpc.dev.code-intelligence.com:443"
rm -f fuzzing-artifacts.tar.gz
rm -rf fuzzing-artifact
docker run -id --name zintbuild -v /opt/ci-fuzz-2.30.4/:/cifuzz -v $PWD:/zint cifuzz/builder-zint:ubuntu_latest || docker start zintbuild
docker exec zintbuild /cifuzz/bin/ci-build fuzzers --directory=/zint
mkdir -p fuzzing-artifact
cd fuzzing-artifact
docker exec zintbuild chmod a+r /zint/fuzzing-artifacts.tar.gz
tar -xf ../fuzzing-artifacts.tar.gz
docker exec zintbuild rm /zint/fuzzing-artifacts.tar.gz
docker exec zintbuild cp /lib/x86_64-linux-gnu/libpng16.so.16 /zint/fuzzing-artifact/cifuzz-libs/
tar -czf ../fuzzing-artifacts.tar.gz *
cd ..
ARTIFACT_NAME=$(adctl import artifact fuzzing-artifacts.tar.gz -p projects/zint-2dd7cf83)
adctl start $ARTIFACT_NAME
