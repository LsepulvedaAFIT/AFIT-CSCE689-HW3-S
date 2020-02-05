#include "PCalc_T.h"

#include <iostream>
#include <thread>
#include <vector>
#include <cmath>

PCalc_T::PCalc_T(unsigned int array_size, unsigned int inputNumOfThreads) : PCalc(array_size)
{
    this->numOfThreads = inputNumOfThreads;

}

PCalc_T::~PCalc_T()
{
    cleanup();
}

void PCalc_T::cleanup()
{
    PCalc::cleanup();
}



void PCalc_T::markNonPrimes()
{
    this->at(0) = 0;
    this->at(1) = 0;

    for (int t = 0; t < this->numOfThreads; t++)
    {
        std::thread createdThread(&PCalc_T::primesThread, this, t);
        this->vectOfThreads.push_back(std::move(createdThread));
    }

    for (unsigned int j = 0; j < vectOfThreads.size(); j++)
    {
        vectOfThreads.at(j).join();
    }
}

void PCalc_T::primesThread(int startVal){

    int startNum = startVal + 2;
    for (unsigned int i = startNum; i <=  sqrt(this->array_size()); i++ ){

        //checks if number has been marked, Protects aganist race conditions
        if (i <= this->threadPosition)
        {
            continue;
        }
        else if (this->at(i) == 1)
        {
            this->threadPosition = i;

            //marks all multiples of it
            for (unsigned int j = i * i; j < this->array_size(); j = j + i)
            {
                this->at(j) = 0;
            }
        }
    }
}