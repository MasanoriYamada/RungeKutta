#!/bin/sh

echo "# results is -3.905"
for E in `seq -4.5 0.001 -3.5`
do
./RungeKutta.out -E $E -mass 2104.61 -ifname /home/sinyamada/set1/ts32/ave/fitPot/ave_1g1yy3D.000700-000000.RC16x32_B1830Kud013760Ks013710C1761.it09 -solve 10.0 0.1 -Jost 8.0 -Func 1g1yy
done
for E in `seq 0.5 0.1 10`
do
./RungeKutta.out -E $E -mass 2104.61 -ifname /home/sinyamada/set1/ts32/ave/fitPot/ave_1g1yy3D.000700-000000.RC16x32_B1830Kud013760Ks013710C1761.it09 -solve 10.0 0.1 -Jost 8.0 -Func 1g1yy
done


#./RungeKutta.out -E $E -mass 2104.61 -ifname //Users/hoge/lab/src/RungeKutta/dat/sample_param.nobound.dat -solve 10.0 0.1 -Jost 8.0
