#! /bin/bash

NAME=$1
IWILL_PREFIX=${PREFIX}/${SUBPREFIX}
mkdir -p ${PREFIX}/bin/
#mkdir -p ${PREFIX}/lib/cmake/${PROJECT}
mkdir -p ${IWILL_PREFIX}/bin 
mkdir -p ${IWILL_PREFIX}/licenses/iwillio
#mkdir -p ${IWILL_PREFIX}/include
#mkdir -p ${IWILL_PREFIX}/lib/cmake/${PROJECT}
#mkdir -p ${IWILL_PREFIX}/cmake
#mkdir -p ${IWILL_PREFIX}/scripts

# install binaries 
cp -R ${BUILD_DIR}/bin/* ${IWILL_PREFIX}/bin 

# install licenses
cp -R ${BUILD_DIR}/licenses/iwillio/* ${IWILL_PREFIX}/licenses

# install libraries
#cp -R ${BUILD_DIR}/lib/* ${IWILL_PREFIX}/lib

# install cmake modules
#sed "s/_PREFIX_/\/${SPREFIX}/g" ${BUILD_DIR}/modules/IwillioTesterPackage.cmake &> ${IWILL_PREFIX}/lib/cmake/${PROJECT}/IwillioTester.cmake
#sed "s/_PREFIX_/\/${SPREFIX}\/${SSUBPREFIX}/g" ${BUILD_DIR}/modules/${PROJECT}-config.cmake.package &> ${IWILL_PREFIX}/lib/cmake/${PROJECT}/${PROJECT}-config.cmake

# install includes
#cp -R ${BUILD_DIR}/include/* ${IWILL_PREFIX}/include

# make symlinks
#pushd ${PREFIX}/lib/cmake/${PROJECT} &> /dev/null
#ln -sf ../../../${SUBPREFIX}/lib/cmake/${PROJECT}/${PROJECT}-config.cmake ${PROJECT}-config.cmake
#ln -sf ../../../${SUBPREFIX}/lib/cmake/${PROJECT}/IwillioTester.cmake IwillioTester.cmake
#popd &> /dev/null

pushd ${PREFIX}/bin &> /dev/null
for f in `ls ${BUILD_DIR}/bin/`; do
   bn=$(basename $f)
   ln -sf ../${SUBPREFIX}/bin/$bn $bn
done
popd &> /dev/null

tar -cvzf $NAME ./${PREFIX}/*
rm -r ${PREFIX}
