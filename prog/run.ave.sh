#!/bin/sh
Conf=700
#for bin in {1,10,20,50}
for bin in 1
do
    MAXconf=`expr "$Conf" / "$bin"`
#    for func in {1g1y1D,1g1yy1D,1g1y3D,1g1yy3D}
    for func in 1g1yy
    do
#	for dim in {1D,3D} 
	for dim in 1D 
	do
	    echo "bin ="$bin $func $dim "t = 7,8,9"
	    
#	    for it in {7,8,9}
	    for it in 7
	    do
		echo "=========== t = $it ================="
		for E in `seq -4.0 0.01 1.0`

		do
	   		#in file
		    ifile="/Users/hoge/data/omgomg/RC16x32_B1830Kud013760Ks013710C1761/results/ts32/ave/fitPot/$(printf %s%s $func $dim).$(printf %06d-000000 $MAXconf).RC16x32_B1830Kud013760Ks013710C1761.it$(printf %02d $it)"
	    #out file
		    ofile="/Users/hoge/data/omgomg/RC16x32_B1830Kud013760Ks013710C1761/results/ts32/ave/Smatrix/$(printf %s $func).$(printf %06d-000000 $MAXconf).RC16x32_B1830Kud013760Ks013710C1761.it$(printf %02d $it)"
		    ./RungeKutta.out -E $E -mass 2104.61 -ifname $ifile -solve 10.0 0.1 -Jost 8.0 -Func $func 
	    #echo "$ifile"
		done
	    done
	done
    done
done
