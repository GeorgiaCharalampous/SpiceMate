#include <TestCallback.h>
#include <iostream>
using namespace std;

int main(int argc, char *argv[]){

    TestCallback attempt;
    VL6180xcallbackChild printCallback;

    attempt.registerCallback(&printCallback);
    printf("Callback Registered \n");
    attempt.setActive();
    printf("Status: Active \n");
    while(attempt.getStatus()==1){
        int c = 0;
        attempt.CreateData();
        usleep(400);
        printf("Input a character");
        std::cin>>c;
        if(c != 0) 
        {
            attempt.setInactive();
            printf("Status: Inactive. Process Terminated! \n");
        };
    }

    return 0;
}
