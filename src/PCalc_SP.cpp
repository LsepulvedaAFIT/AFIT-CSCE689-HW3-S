#include "PCalc_SP.h"

#include <iostream>
#include <cmath>

PCalc_SP::PCalc_SP(unsigned int array_size) : PCalc(array_size)
{
    
}

PCalc_SP::~PCalc_SP()
{
    cleanup();
}

void PCalc_SP::cleanup()
{
    PCalc::cleanup();
}


void PCalc_SP::markNonPrimes(){
    std::cout << "marking primes" << std::endl;
    
    //marks of initial values 
    this->at(0) = 0;
    this->at(1) = 0;

    //runs through entire 
    for (unsigned int i = 2; i <= sqrt(this->array_size()); i++ ){
        //checks if number has been marked
        if (this->at(i) == 1)
        {
            //marks all multiples of it
            for (unsigned int j = i * i; j < this->array_size(); j = j + i)
            {
                this->at(j) = 0;
            }
        }
        //std::cout << "prime[" << i << "] = " << this->at(i) << std::endl;
    }
}

