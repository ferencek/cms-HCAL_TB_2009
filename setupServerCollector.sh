#!/bin/bash

DQMV=4.6.0 
ARCH=slc4_ia32_gcc345 
DEV_AREA=${HOME}/DQM/dqmgui 
DATA_AREA=${HOME}/DQM/dqmdata

mkdir -p $DEV_AREA
mkdir -p $DATA_AREA
cd $DEV_AREA
mkdir -p rpms

cd rpms
export VO_CMS_SW_DIR=$PWD SCRAM_ARCH=$ARCH
wget -O bootstrap.sh http://cmsrep.cern.ch/cmssw/cms/bootstrap.sh
sh -x ./bootstrap.sh setup -path $PWD -arch $ARCH >& $PWD/bootstrap-$ARCH.log </dev/null
. ./$ARCH/external/apt/*/etc/profile.d/init.sh
apt-get update
apt-get install -y cms+dqmgui+$DQMV

cd $DEV_AREA
export CVSROOT=:pserver:anonymous@cmscvs.cern.ch:/cvs/CMSSW
cvs -Q co -r ONLINE_CONFIG_INTEGRATION -d config CMSSW/DQM/Integration/config
cvs -Q co -r ONLINE_CONFIG_INTEGRATION -d style CMSSW/DQM/RenderPlugins/src

