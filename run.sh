#!/usr/bin/env bash

#Setup sockets
gnome-terminal -e "socat -d -d pty,raw,echo=0 pty,raw,echo=0"
gnome-terminal -e "socat -d -d pty,raw,echo=0 pty,raw,echo=0"
read -p "Enter first socat in: " firstin
read -p "Enter first socat out: " firstout
read -p "Enter second socat in: " secondin
read -p "Enter second socat out: " secondout
#
##Start Simulators
gnome-terminal --working-directory "$PWD" -e "bash -c './MsgCreator.py > /dev/pts/$firstin'"
gnome-terminal --working-directory "$PWD" -e "bash -c './RGBMatrix.py < /dev/pts/$secondout'"
gcc src/main.c -lm -lpthread
./a.out /dev/pts/$firstout /dev/pts/$secondin