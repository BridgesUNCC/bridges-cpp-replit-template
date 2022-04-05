#!/bin/sh

#
# the command line argument should reflect the path to repl folder root
#
REPL_PATH=$1
#
# install Curl - can only use the install-pkg script which is buggy
#
install-pkg libcurl4
install-pkg libcurl4-openssl-dev


#
# create directory for curl includes and libraries
#
mkdir ${REPL_PATH}/curl

mv ~/.apt/usr/*  ${REPL_PATH}/curl

#
# download the BRIDGES C++ client
#
wget http://bridgesuncc.github.io/sw/bridges-cxx-3.3.0-x86_64-linux-gnu.tgz  -O ~/bridges-cxx.tgz

# get an example makefile for repl
wget http://bridgesuncc.github.io/sw/replit-example-Makefile -O ${HOME}/Makefile

#
# explode it in the REPL directory
#
cd ${REPL_PATH}
tar xvfz ~/bridges-cxx.tgz

#
# mv the Makefile to the REPL folder
#
mv ${HOME}/Makefile ${REPL_PATH}

#
#
#
rm -f ${REPL_PATH}/.replit
cat >> ${REPL_PATH}/.replit << EOF

run = "make run"

EOF
#
# need to set up environment variables that need to be appended to the .bashrc
# done in the Makefile now
#cat >> ~/.bashrc <<EOF

#export BRIDGES_CXXFLAGS="-I${REPL_PATH}/bridges-cxx-3.1.1-x86_64-linux-gnu/include -I${REPL_PATH}/curl/include/x86_64-linux-gnu"
#export BRIDGES_LDFLAGS="-L${REPL_PATH}/bridges-cxx-3.1.1-x86_64-linux-gnu/lib -L{HOME}/${REPL_PATH}/curl/lib/x86_64-linux-gnu"
#
#export BRIDGES_CXX=clang++
#export BRIDGES_CC=clang++
#export BRIDGES_LD=clang++

#EOF
