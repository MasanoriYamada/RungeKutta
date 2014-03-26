#!/bin/sh

for E in `seq 0.9 0.01 0.99`
do
./RungeKutta.out -E $E -mass 2104.61 -ifname /Users/hoge/lab/src/RungeKutta/dat/sample_param.bound.dat -solve 10.0 0.1 -Jost 8.0
done
#./RungeKutta.out -E $E -mass 2104.61 -ifname //Users/hoge/lab/src/RungeKutta/dat/sample_param.nobound.dat -solve 10.0 0.1 -Jost 8.0
