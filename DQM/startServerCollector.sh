#!/bin/bash

DQMV=4.6.0 
ARCH=slc4_ia32_gcc345 
DEV_AREA=${HOME}/DQM/dqmgui 

. $DEV_AREA/rpms/$ARCH/cms/dqmgui/$DQMV/etc/profile.d/env.sh

# start the server
visDQMControl restart all from $DEV_AREA/config/server-conf-devtest.py
echo "GUI server started at http://`hostname -f`:8888/dqm/testbeam"

# start the collector
$DEV_AREA/rpms/$ARCH/cms/dqmgui/$DQMV/etc/restart-collector 9190:$DEV_AREA
