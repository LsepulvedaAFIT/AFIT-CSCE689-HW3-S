#ifndef PCALC_T_H
#define PCALC_T_H

#include "PCalc.h"
#include <vector>
#include <thread>

// Your implementation of PCalc_T class should go here. 
// Make sure your constructor takes in two parameters:

// PCalc_T::PCalc_T(unsigned int array_size, unsigned int num_threads);

// Call the parent constructor when initializing your constructor and pass in array_size. Then
// use num_threads to cap off how many threads you use to calculate all prime numbers

class PCalc_T : public PCalc
{
public:


    //called virtual in parent class
    virtual ~PCalc_T() override;

    virtual void markNonPrimes() override;

    //called virtual in parent class
    virtual void cleanup() override;

    void primesThread(int startVal);

//protected:
    //should call parent constructor
    PCalc_T(unsigned int array_size, unsigned int inputNumOfThreads);

private:
    unsigned int threadPosition = 0;
    int numOfThreads = 0;

    std::vector<std::thread> vectOfThreads;


};

#endif
