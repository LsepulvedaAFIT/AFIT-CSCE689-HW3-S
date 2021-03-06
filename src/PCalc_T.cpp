#include "PCalc_T.h"

#include <iostream>
#include <thread>
#include <vector>
#include <cmath>
#include <mutex>

PCalc_T::PCalc_T(unsigned int array_size, unsigned int inputNumOfThreads) : PCalc(array_size)
{
    //initializes number of threads to be created
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


//Used pseudocode at https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes
//Sets all nonprimes to 0 in the array memory using multithreading
void PCalc_T::markNonPrimes()
{
    //std::cout << "marking primes" << std::endl;//testing

    this->at(0) = 0;
    this->at(1) = 0;

    //creates the threads
    for (int t = 0; t < this->numOfThreads; t++)
    {
        std::thread createdThread(&PCalc_T::primesThread, this, t);
        this->vectOfThreads.push_back(std::move(createdThread));
    }

    //waits for all the threads to finish
    for (unsigned int j = 0; j < vectOfThreads.size(); j++)
    {
        vectOfThreads.at(j).join();
    }
}

//This function is called when a thread is spawn to 
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
            //updates threadPosition counter to prevent race conditions
            this->mu.lock();
            this->threadPosition = i;
            this->mu.unlock();

            //marks all multiples of it
            for (unsigned int j = i * i; j <= this->array_size(); j = j + i)
            {
                this->at(j) = 0;
            }
        }
    }
}