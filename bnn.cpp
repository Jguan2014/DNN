#include "bnn.h"



void DNN(activation_t input_activation[],weight_t weight_layer1,out_t output){

	//Simple Storage Allocation
	conv_result conv_res[(out1_row*out1_col)]; //Store Intermediate Result
	activation_t IO_buffer[out2_row*out2_col]; //Buffer for input and output


	//First Layer
	conv(out1_row,(weight_row*weight_col),input_activation, weight_layer1, conv_res);

	//Print Output from first layer
#ifndef __SYNTHESIS__
	std::cout << "Convolution Layer 1 Result:" << std::endl;
	for(int i = 0; i < out1_row; i++){
		for(int j = 0; j < out1_col; j++){
			 for(dataSize_t ii = 0; ii < out2_row; ii++){	//ii - Row index of window topleft
				 dataSize_t p = (i-ii); //Row index of element within the window
				 if((p >= 0) && (p < weight_row)){ //Check no out-of-bounds
					 for(dataSize_t jj = 0; jj < out2_col; jj++){ //jj - Column index of window topleft
						dataSize_t q = (j-jj); //Column index of element within the window
						if((q >= 0)  && (q < weight_col)){ //Check no out-of-bounds
							if(j) std::cout << ",";
							//Finds the first occurrence of the element in the packed array
							std::cout << IO_buffer[ii*out2_col+jj][p*weight_col+q];
							break;
						}
					}
					 break;
				 }
			 }
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
#endif
/*
#ifndef __SYNTHESIS__ //Print IO Buffer
	for(int i = 0; i < out2_row*out2_col;i++){
		std::cout <<  "IO Buffer element " << i << ": " << IO_buffer[i].to_string(2) << std::endl;//Binary Output
	}
#endif
*/

}
