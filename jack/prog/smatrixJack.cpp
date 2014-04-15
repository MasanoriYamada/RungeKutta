//--------------------------------------------------------------------------
/**
 * @file smatrixJack.cpp
 * @brief JK err for smatrix
 * @ingroup YAMADA
 * @author  M.YAMADA 
 * @date    Tue April 15 2014
 */
//--------------------------------------------------------------------------

#include <boost/lexical_cast.hpp>
#include <boost/foreach.hpp>
#include "../include/io.h"
#include "../include/jack.h"
#include "../include/analys.h"

using namespace std;
using boost::lexical_cast;

int main(){
  string inPath = "/Users/hoge/data/omgomg/set1/ts" + lexical_cast<string>(Tshiftsize) +
    ".tmp/spin00.bin" + lexical_cast<string>( binsize ) + "/Smatrix/bin";
  string outPath = "/Users/hoge/data/omgomg/set1/ts" + lexical_cast<string>(Tshiftsize) +
    "/spin00.bin" + lexical_cast<string>( binsize ) + "/Smatrix/jack";
  string physInfo = "RC16x32_B1830Kud013760Ks013710C1761";
//  string func_array[] = {"1g1y1D.Smat", 
// 			 "1g1y3D.Smat", 
// 			 "1g1yy1D.Smat", 
// 			 "1g1yy3D.Smat" };  

  string func_array[] = {"1g1yy3D" };  
  
  
  IODATA iod;
  iod.setReadBinaryMode(false);
  iod.setWriteBinaryMode(false);
  iod.setConfSize(binnumber);
  iod.setD("1D");
  int datasize = 5000;

  static bool flg_boune_is = "false";
  
  root_mkdir("outPath");
  
 BOOST_FOREACH( string funcType, func_array ){
   string staticsInfoIn = funcType;
   string staticsInfoOut = funcType + "_jack";
   
   
   for (int it =T_in; it<T_fi+1; it++) {
     JACK jackPot(Confsize,binsize,1);
     double *xData = new double[datasize]();
     double *binE = new double[1]();
     iod.callData(xData,1,inPath,staticsInfoIn,physInfo,0,it);
     for (int j= 0; j <binnumber; j++) {
       double* yData = new double[datasize]();
       iod.callData(yData,4,inPath,staticsInfoIn,physInfo,j,it);
       for (int id =0; id <datasize; id++) {
	 //	        cout << id<<" "<<xData[id]<<"   "<<yData[id] <<endl;
	 if(yData[id-1] < 0)
	   {
	     binE[0] = xData[id];
	     flg_boune_is = true;
	   }
       }
       if(! flg_boune_is ) 
	 {
	   cout << "un bound!"<<endl;
	 }
       cout << binE[0] <<endl;

       jackPot.setBinData(binE,j);
       //jackPot.setData(yData,j);
       //iod.outData(data ,outPath ,staticsInfo,physInfo, j,it,300);                                                                                                                                    
       delete[] yData; 
     }
     double* err= new double[1];
     double* ave= new double[1];
     err= jackPot.calcErr();
     ave= jackPot.calcAve();
     for(int id = 0;id<datasize;id++){cout<<xData[id]<<" "<<ave[id]<<" "<<err[id]<<endl;}
     
     iod.outErr(xData,ave,err,outPath,staticsInfoOut,physInfo,700,it,1);  
     delete []xData;
   }
 }  
 cout<<"@End of all"<<endl;
 return 0;
}
