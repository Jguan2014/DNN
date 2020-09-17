#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>

#include "DNN.h"
    int input_channel = 64;

    int output_channel = 128;
    int input_height = 112;
    int input_width = 112;
    int weight_height = 3;
    int weight_width = 3;
	using namespace std;
	float input[64][114][114];
	float weight [128][64][3][3];
	float bias[128];
	float weight_m[73728];
	float out[128][12544];
	float column_vec[576][12544];
	int input_ch = 9;
	float W[128][576];

int main(int argc, char *argv[]){
	cout <<"starting testbench" << endl;




    cout << "Input Reading:" << endl << endl;
    ifstream file1("input.dat");
    float num1;
    int count = 0;
    cout << "while:" << endl << endl;
    	 for(int i = 0; i < input_channel; i++){
    		 input[i][113][0] = 0; //pad 0 at 4 corners
    		 input[i][0][113] = 0;
    		 input[i][0][0] = 0;
    		 input[i][113][113] = 0;
    	 		for (int j = 0; j < input_height; j++){
    	 			for (int k = 0; k < input_width; k++){
    	 					file1 >> num1;
    	 					input[i][0][k] = 0;
    	 					input[i][j][0] = 0;
    	 					input[i][113][k] = 0;
    	 					input[i][j][113] = 0;
    	 					input[i][j+1][k+1] = num1;
    	 					count ++;
    	 			}
    	 		}
    	 }
    cout << "count = " << count << endl;
    cout << "first = " << input[0][0][0] <<endl;
    file1.close();

	count =0;

	// construct column matrix, stack 9 elements and 64 channels vertically
	 for (int row = 0; row<112; row++){
	      for (int col = 0; col<112; col++){
	         for(int ic = 0; ic<64; ic++){

	        	 column_vec[ic*input_ch][count] = input[ic][row][col];
	        	 column_vec[ic*input_ch+1][count] = input[ic][row][col+1];
	        	 column_vec[ic*input_ch+2][count] = input[ic][row][col+2];
	        	 column_vec[ic*input_ch+3][count] = input[ic][row+1][col];
	        	 column_vec[ic*input_ch+4][count] = input[ic][row+1][col+1];
	        	 column_vec[ic*input_ch+5][count] = input[ic][row+1][col+2];
	        	 column_vec[ic*input_ch+6][count] = input[ic][row+2][col];
	        	 column_vec[ic*input_ch+7][count] = input[ic][row+2][col+1];
				 column_vec[ic*input_ch+8][count] = input[ic][row+2][col+2];

	         }
	         count ++;
	      }
	 }

    cout << "Weight Reading:" << endl << endl;
     ifstream file2("weight.dat");
    float num2;
    int count2 =0;

    //read in weights
   	 for(int i = 0; i < output_channel; i++){
   	 		for (int j = 0; j < input_channel; j++){
   	 			for (int k = 0; k < weight_height; k++){
   	 				for (int l = 0; l < weight_width; l++){
   	 					file2 >> num2;
   	 					weight[i][j][k][l] = num2;
   	 					weight_m[count2]= num2;
   	 					count2 ++;
   	 			  }
   	 		   }
   	      }
        }

   	 //flatten weight into 64 by 576
    cout << "count = " << count2 << endl;
    cout << "first = " << weight[0][0][0][0] <<endl;
	 for (int oc = 0; oc < 128; oc++){
		 for (int q=0; q<576; q++){
		     W[oc][q]= weight_m[oc*576+q];
		 }
	 }

	 //read in bias
  	 for(int i = 0; i < output_channel; i++){
  		 	 file2 >> num2;
  		 	bias[i] = num2;
       }
    file2.close();

	cout << "start DNN " << endl << endl;
    DNN(column_vec, W, bias, out);

    cout << "DONE DNN " << endl;
    return 0;
}

