#!/bin/sh
## 出力が追記なので注意!

Conf=700
Mass=2104.61
under_lmit=-0.0000001
#for bin in {1,10,20,50}
for bin in 20
do
    idir="../dir/spin00.bin$bin/fitPot/bin"
    odir="../dir/spin00.bin$bin/Smatrix/bin"
    mkdir -p $odir
    MAXconf=`expr "$Conf" / "$bin"`
#    for func in {1g1y,1g1yy}
    for func in 1g1yy
    do
#	for dim in {1D,3D} 
	for dim in 3D 
	do
	    for it in {7,8,9}
#	    for it in 7
	    do
		echo "=========== bin =$bin  func = $dim$func  t = $it ================="
		for iconf in `seq 0 1 34`
#		for iconf in 10
		do
		    echo "=========== iconf = $iconf ================="
		    #in file
		    ifile="$idir/$(printf %s%s $func $dim).Smat.$(printf %06d-%06d $MAXconf $iconf).RC16x32_B1830Kud013760Ks013710C1761.it$(printf %02d $it)"
		    #out file
		    ofile="$odir/$(printf %s%s $func $dim).Smat.$(printf %06d-%06d $MAXconf $iconf).RC16x32_B1830Kud013760Ks013710C1761.it$(printf %02d $it)"
		    
		    ######################### for bound ###########################
		    for E in `seq -5.0 0.001 -0.001`
#		    for E in -0.00001
		    do
			./RungeKutta.out -E $E -mass $Mass -ifname $ifile -solve 10.0 0.01 -Jost 8.0 -Func $func  >> $ofile
			#echo "$ifile"
		    done
		    E=$under_lmit
			./RungeKutta.out -E $E -mass $Mass -ifname $ifile -solve 10.0 0.01 -Jost 8.0 -Func $func  >> $ofile
		    ######################### for scatter ###########################
		    #		    for E in `seq 0.000001 0.00001 1.0`
		    #		    do
		    #in file
		    #					ifile="../dir/spin00.bin$bin/fitPot/bin/$(printf %s%s $func $dim).$(printf %06d-%06d $MAXconf $iconf).RC16x32_B1830Kud013760Ks013710C1761.it$(printf %02d $it)"
		    #out file
		    #			ofile="$odir/$(printf %s%s $func $dim).$(printf %06d-%06d $MAXconf $iconf).RC16x32_B1830Kud013760Ks013710C1761.it$(printf %02d $it)"
		    #			./RungeKutta.out -E $E -mass $Mass -ifname $ifile -solve 10.0 0.1 -Jost 8.0 -Func $func #>> $ofile
		    #echo "$ifile"
		    #		    done
		done
	    done
	done
    done
done    
