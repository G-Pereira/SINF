#!/usr/bin/env bash

#Setup sockets
gnome-terminal -e "socat -d -d pty,raw,echo=0 pty,raw,echo=0"
read -p "Enter first socat in: " firstin
read -p "Enter first socat out: " firstout

#Start Simulators
echo $PWD
gnome-terminal --working-directory "$PWD/simulators" -e "bash -c './MsgCreator.py > /dev/pts/$firstin'"
cmake .
make SINF
gnome-terminal --working-directory "$PWD" -e "bash -c './SINF /dev/pts/$firstout'"