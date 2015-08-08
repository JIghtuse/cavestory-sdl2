#!/bin/bash

STEAM_PATH=$HOME/.steam/steam/steamapps/common/
GAME_PATH="$STEAM_PATH/Cave Story+/data/base/"
PROJECT_PATH=$PWD

cp "$GAME_PATH"/{Arms,Bullet,bkBlue,Caret,MyChar,TextBox,Npc/NpcCemet,Stage/PrtCave}.bmp "$PROJECT_PATH/content/" && \
    sed -i 's/ORIGINAL/HIGH/' src/config.cpp
