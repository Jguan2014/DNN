#include <stdio.h>
#include <iostream>
#include <fstream>



using namespace std;

int main(int argc, char *argv[]){
    int input_channel = 64;
    int activation_length = 118;
    int activation_width = 118;

    int weight_length = 3;
    int weight_width = 3;


    int output channel = 128;

    out_t output;

    cout << "Input Reading:" << endl << endl;
    //Read in the two dimension binary input activation and we expand it to a one dimension vector

    ifstream file1("input.dat");
    int num1;
    vector<int> input;
    if (file1.is_open()){
        while (file >> num1)
            input.push_back(num1);
    }

    cout << "count = " << input.size() << endl;
    cout << "first = " <input[0] << endl;
    cout << "last  = " << input[input.size() -1] << endl;
    file1.close();


    cout << "Weight Reading:" << endl << endl;
     ifstream file2("weight.dat");
    int num2;
    vector<int> weight;
    if (file2.is_open()){
        while (file >> num2)
            vec.push_back(num2);
    }

    cout << "count = " << weight.size() << endl;
    cout << "first = " << weight[0] << endl;
    cout << "last  = " << weight[weight.size() -1] << endl;
    file2.close();



	cout << "start DNN " << endl << endl;
    DNN(in, weight_layer1);  //change 
    cout << "DONE DNN " << endl;


	//Print output
	cout << "Output Value:	" << output << endl;

    return 0;
}

