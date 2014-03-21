#!/bin/sh

case $# in
2) E_in=$1;;
*) echo 'usage: run.sh (E[MeV])' 1>&2; exit 1;;
esac

./RungeKutta.out -E $E -mass 2000 -ifname $(in_FILE) -solve 10.0 0.1 -Jost 8.0
