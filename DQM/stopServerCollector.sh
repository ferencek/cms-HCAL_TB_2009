#!/bin/bash

DQMV=4.6.0 
ARCH=slc4_ia32_gcc345 
DEV_AREA=${HOME}/DQM/dqmgui

. $DEV_AREA/rpms/$ARCH/cms/dqmgui/$DQMV/etc/profile.d/env.sh
visDQMControl stop all from $DEV_AREA/config/server-conf-devtest.py
ps x | perl -ne '/[ ]DQMCollector.*9190/ && kill 2, (split)[0]'
