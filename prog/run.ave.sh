#!/bin/sh
Conf=399
under_lmit=-0.0000001

Mass=1963
#for bin in {1,10,20,50}
for bin in {21,3,1}
do
    MAXconf=`expr "$Conf" / "$bin"`
    mkdir -p /home/sinyamada/results/kappa_013700.013640/ts32/spin00.bin$(printf %d $bin)/ave/Smatrix
#    for func in {1g1y1D,1g1yy1D,1g1y3D,1g1yy3D}
#    for func in {1g1y,1g1yy}
    for func in 2g1yy
    do
#	for dim in {1D,3D} 
	for dim in 1D 
	do
	    echo "bin ="$bin $func $dim 
	    for it in {11,12,13}
#	    for it in 14
	    do
		echo "=========== t = $it ================="
		for E in `seq -15.0 0.01 -0.001`
		do
	        #for binding energy part!
	       	#in file
		    ifile="/home/sinyamada/results/kappa_013700.013640/ts32/spin00.bin$(printf %d $bin)/ave/fitPot/$(printf %s%s $func $dim).$(printf %06d-%06d $MAXconf $Conf).RC32x64_B1900Kud01370000Ks01364000C1715.it$(printf %02d $it)"
	    #out file
		    ofile_energy="/home/sinyamada/results/kappa_013700.013640/ts32/spin00.bin$(printf %d $bin)/ave/Smatrix/energy.$(printf %s%s $func $dim).$(printf %06d-%06d $MAXconf $Conf).RC16x32_B1830Kud013760Ks013710C1761.it$(printf %02d $it)"
		    ./RungeKutta.out -E $E -mass $Mass -ifname $ifile -solve 10.0 0.1 -Jost 8.0 -Func $func  >> $ofile_energy
	    #echo "$ifile"
		done
		E=$under_lmit
                ./RungeKutta.out -E $E -mass $Mass -ifname $ifile -solve 10.0 0.01 -Jost 8.0 -Func $func >> $ofile_energy
		for E in `seq 0.0001 0.01 30.0`
		do
		    ofile_phase="/home/sinyamada/results/kappa_013700.013640/ts32/spin00.bin$(printf %d $bin)/ave/Smatrix/phase.$(printf %s%s $func $dim).$(printf %06d-%06d $MAXcon\
f $Conf).RC16x32_B1830Kud013760Ks013710C1761.it$(printf %02d $it)"

		    ./RungeKutta.out -E $E -mass $Mass -ifname $ifile -solve 10.0 0.01 -Jost 8.0 -Func $func >> $ofile_phase
		done
	    done
	done
    done
done
