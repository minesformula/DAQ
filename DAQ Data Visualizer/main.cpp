#include "include/dataSend.h"
#include <cstdlib>
#include <random>


int main(){
    std::srand(time(NULL));
    double array[9]; 
    
    for (int i = 0; i != -1; i++){
        for (int j = 0; j < 9; j++)
        {
            array[j] = (double)rand()/((double)RAND_MAX/100);
        }
        submitToInflux(array);
    }

    return 0;
}