
#include <stdio.h>

#include <fstream>
#include <vector>
#include <stdlib.h>

#include "DNN.h"
#define __SYNTHESIS__


using namespace std;

#ifndef __SYNTHESIS__ //Enable Printing of intermediate values if not synthesized
	#include <iostream>
#endif

int length = 12544;
void  DNN(float column_vec[576][12544],float W[128][576], float bias[128], float out[128][12544] ){

	  for(int i = 0; i <128; i++){

        for(int j = 0; j < length; j++){
			#pragma HLS PIPELINE II=1
            for(int k = 0; k < 576; ++k){
			#pragma HLS PIPELINE II=1
                out[i][j] += W[i][k] * column_vec[k][j];
            }
           }

      }
	#ifndef __SYNTHESIS__
	  fstream myfile;
	  myfile.open("H:\Fall2020\Rice_Project\output1.dat", ios::out);
	#endif

	 for (int row = 0; row< 128;row++){
		 for (int col=0; col< 12544 ; col++){
			#pragma HLS latency max=5
			#pragma HLS PIPELINE II=1
			 out[row][col] = out[row][col]+bias[row];
			 if  (out[row][col] > 0){
				#ifndef __SYNTHESIS__
				 cout << "row, column " << row<< " ," << col << " =" <<out[row][col] <<endl;
				#endif
			 }
				 else{
					 out[row][col] = 0;
			}

		#ifndef __SYNTHESIS__
			 myfile << out[row][col] <<endl;
		#endif
	 }

}
	#ifndef __SYNTHESIS__
	 myfile.close();
    #endif
}
