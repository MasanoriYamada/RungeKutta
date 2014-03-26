#!/bin/sh
Conf=700
for bin in {1,10,20,50}
do
    MAXconf=`expr "$Conf" / "$bin"`
    for func in {1g1y1D,1g1yy1D,1g1y3D,1g1yy3D}
    do
	echo "bin ="$bin $func "t = 7,8,9"
	
	for it in {7,8,9}
	do
	    for E in `seq -4.0 0.001 1.0`
	    do
	    #echo $(printf %d $bin)
		#in file
	    ifile="spin00.bin$bin/fitPot/jack/$(printf %s $func).$(printf %06d-000000 $MAXconf).RC16x32_B1830Kud013760Ks013710C1761.it$(printf %02d $it)"
	    #out file
	    ofile="spin00.bin$bin/fitPot/jack/$(printf %s $func).$(printf %06d-000000 $MAXconf).RC16x32_B1830Kud013760Ks013710C1761.it$(printf %02d $it)"
	    #.RungeKutta.out -E $E -mass 2104.61 -ifname $ifile -solve 10.0 0.1 -Jost 8.0 |tee $ofile
	    echo "$ifile"
	    done
	done
    done
done
