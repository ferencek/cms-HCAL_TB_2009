#!/bin/bash

DQMV=4.6.0 
ARCH=slc4_ia32_gcc345 
DEV_AREA=${HOME}/DQM/dqmgui 
DATA_AREA=${HOME}/DQM/dqmdata

. $DEV_AREA/rpms/$ARCH/cms/dqmgui/$DQMV/etc/profile.d/env.sh
[ -f $DEV_AREA/dqm.db ] || visDQMRegisterFile $DEV_AREA/dqm.db /Global/Online/ALL "Global run"
mv $DEV_AREA/dqm.db{,.new}
visDQMUnregisterFile $DEV_AREA/dqm.db.new $DATA_AREA/DQM_[^V]*.root
visDQMRegisterFile $DEV_AREA/dqm.db.new /Global/Online/ALL "Global run" $DATA_AREA/DQM_V*.root
mv $DEV_AREA/dqm.db{.new,}
