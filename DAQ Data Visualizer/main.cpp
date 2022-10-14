#include "dataSend.h"
#include "cstdlib"

int main(){
    std::srand(time(NULL));

    for (int i = 0; i < 10; i++){
        submitToInflux(rand()%100);
    }

    return 0;
}