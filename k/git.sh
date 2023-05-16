git clone https://github.com/ENCODE-DCC/kentUtils

cp bigWigRegPotential.c makefile kentUtils/src/utils/bigWigAverageOverBed

cd kentUtils/src/jkOwnLib/ && make && cd -
mkdir -p ~/bin/x86_64/

cp userApp.mk kentUtils/src/inc/userApp.mk
cd kentUtils/src/utils/bigWigAverageOverBed/ && make && cd -

