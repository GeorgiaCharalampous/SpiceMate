#include <../src/DataProcess.h>
#include <iostream>
using namespace std;

int main(int argc, char *argv[]){
    int sequence;
    cout<<"Enter a case number (1-9)\n";
    cin>>sequence;
    DataProcess instance;
    DataProcess* pointer;
    pointer = &instance;

    switch (sequence){
        case 1:
        {
        cout << "Sequence of 30 values under the limit - no print expected" <<endl;
        for(int i = 0; i < 30;i++){
            pointer->value = 0;
            pointer->dataReceived=true;
            pointer->thresholding();
        };
        break;
        }
        case 2:
        {
        cout << "Sequence of 30 values in the range - Start print expected" <<endl;
        for(int i = 0; i < 30;i++){
            pointer->value = 50;
            pointer->dataReceived=true;
            pointer->thresholding();

        };
        break;
        }
        case 3:
        {
        cout << "Sequence of 30 values above the limit - no print expected" <<endl;
        for(int i = 0; i < 30 ;i++){
            pointer->value = 200;
            pointer->dataReceived=true;
            pointer->thresholding();
        };
        break;
        }
        case 4:
        {
        cout << "Sequence of 10 values in the range - no print expected" <<endl;

        for(int i = 0; i < 10;i++){
            pointer->value = 50;
            pointer->dataReceived=true;
            pointer->thresholding();
        };
        break;
        }
        case 5:
        {
        cout << "Sequence of 30 values in and 10 out - expect Start and Stop" <<endl;
        int inputs[40];
        for (int j = 0; j < 30; j++){
            inputs[j] = 50;
        }
        for (int j = 30; j < 40; j++){
            inputs[j] = 0;
        }
        for(int i = 0; i < 40;i++){
            pointer->value = inputs[i];
            pointer->dataReceived=true;
            pointer->thresholding();
        };
        break;
        }
        case 6:
        {
        cout << "Sequence of 10 values out and 30 in - expect Start only" <<endl;
        int inputs[40];
        for (int j = 0; j < 10; j++){
            inputs[j] = 0;
        }
        for (int j = 10; j < 40; j++){
            inputs[j] = 50;
        }
        for(int i = 0; i < 40;i++){
            pointer->value = inputs[i];
            pointer->dataReceived=true;
            pointer->thresholding();
        };
        break;
        }
        case 7:
        {
        cout << "Sequence of 25 values in, 1 out  and 10 in - no print expected" <<endl;
        int inputs[36];
        for (int j =  0; j < 36; j++){
            inputs[j] = 50;
        }
        inputs[25] = 0;

        for(int i = 0; i < 36;i++){
            pointer->value = inputs[i];
            pointer->dataReceived=true;
            pointer->thresholding();
        };
        break;
        }
        case 8:
        {
        cout << "Sequence of 30 values in, 2 out  and 30 in - one Start expected" <<endl;
        int inputs[62]; 
        for (int j = 0; j < 62; j++){
            inputs[j] = 50;
        }
        inputs[30] = 0;
        inputs[31] = 0;

        for(int i = 0; i < 62 ;i++){
            pointer->value = inputs[i];
            pointer->dataReceived=true;
            pointer->thresholding();
        };
        break;
        }
        case 9:
        {
        cout << "Sequence of 30 values in, 5 out and 30 in - Start - Stop - Start expected" <<endl;
        int inputs[65];
        for (int j = 0; j < 65; j++){
            inputs[j] = 50;
        }
        for (int j = 30; j < 35; j++){
            inputs[j] = 0;
        }
        
        for(int i = 0; i < 65;i++){
            pointer->value = inputs[i];
            pointer->dataReceived=true;
            pointer->thresholding();
        };
        break;
        }

    };

    return 0;
}