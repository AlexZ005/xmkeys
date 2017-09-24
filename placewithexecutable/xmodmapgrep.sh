#!/bin/sh
xmodmap -pke | grep $1
exit $?
