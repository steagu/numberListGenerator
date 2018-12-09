/*
    @author: Samuel Teague
    @date: 05 Dec 2018 (most recent)
    @file: numberListGenerator.cpp
    @description: given a destination file name, amount of numbers, and format
        generates and prints to a file a list of random numbers.
        receives parameters in the form of:
            ./numberListGenerator [datafile] [amt] [format]
            where datafile is the file to write to
            amt is the amount to generate
            and format can take 1 of 4 values:
                identical
                random
                sorted
                rsorted
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include <sstream>
#include <ctime>
#include <random>

enum FormatCode { IDENTICAL, RANDOM, SORTED, RSORTED};
FormatCode translateToFormatCode(std::string formatString)
{
    if (formatString == "identical")
        return IDENTICAL;
    else if (formatString == "random")
        return RANDOM;
    else if (formatString == "sorted")
        return SORTED;
    else if (formatString == "rsorted")
        return RSORTED;
    else throw std::invalid_argument(formatString + " is not a valid format code!");
}

std::vector<unsigned long> generateNumbers(FormatCode format, unsigned long amount, unsigned long range);


int main(int argc, char** argv)
{
    const unsigned long RANGE = 1000000;

    unsigned long numOfNums = 0;

    //parse input
    
    if (argc != 4)    //checks for correct # of args
    {
        std::cerr << "Incorrect input! Correct input is:\n" << std::string(argv[0]) << " [datafile] [amt] [format]\n";
        return 1;
    }

    try
    {
        numOfNums = std::stoul(std::string(argv[2]));
    }
    catch (std::invalid_argument)
    {
        std::cerr << "Second parameter must be a number\n";
        return 1;
    }
    catch (std::out_of_range)
    {
        std::cerr << "Number must be positive and not too large\n";
        return 1;
    }
    catch (std::exception)
    {
        std::cerr << "Something really weird happened when trying to parse 2nd argument.\n";
        return 1;
    }


    std::string fileName(argv[1]);

    //all variables now set with valid values except for potentially fileName

    //opening outfile
    std::ofstream outfile;
    outfile.open(fileName);

    //checking outfile name validity and that open operation was successful
    if (!outfile.is_open())
    {
        std::cerr << "Unable to open file\n";
        return 1;
    }


    std::string format(argv[3]);

    //generate data and write to outfile
    std::vector<unsigned long> numbers;
    try
    {
        numbers = generateNumbers(translateToFormatCode(format), numOfNums, RANGE);
    }
    catch (std::invalid_argument)
    {
        std::cerr << "Invalid fomat code passed to program!\n";
        return 1;
    }
    
    for (unsigned long i = 0; i < numbers.size(); i++)
        outfile << numbers[i] << std::endl;



    // if (format == "identical")
    // {
    //     int num = distribution(generator);
    //     for (unsigned long i = 0; i < numOfNums; ++i)
    //         outfile << num << std::endl;
    // }
    // else if (format == "random")
    // {
    //     for (unsigned long i = 0; i < numOfNums; ++i)
    //         outfile << distribution(generator) << std::endl;
    // }
    // else if (format == "sorted" || format == "rsorted")
    // {
    //     std::vector<int> ary(numOfNums);

    //     for (unsigned long i = 0; i < numOfNums; ++i)
    //         ary[i] = distribution(generator);

    //     std::sort(ary.begin(), ary.end());
    //     if (format == "rsorted")
    //         std::reverse(ary.begin(), ary.end());

    //     for (unsigned long i = 0; i < numOfNums; ++i)
    //         outfile << ary[i] << std::endl;
    // }
    // else
    //     std::cerr << "invalid format type\n";


    outfile.close();


    return 0;
}

std::vector<unsigned long> generateNumbers(FormatCode format, unsigned long amount, unsigned long range)
{
    /*
        @name: generateNumbers()
        @author: Samuel Teague
        @date: 09 Dec 2018
        @description: Generates a vector of unsigned ints meeting the given criteria
        @param: 
            FormatCode format: an enum represented the format the values should be stored in the array
            unsigned long amount: the amount of numbers to be generated
            range: the upper bound of possible values. Lower bound assumed to be 0
        @returns: A std::vector of unsigned longs holding the generated values.
    */
    std::default_random_engine generator(time(NULL));
    std::uniform_int_distribution<unsigned long> distribution(0, range);
    distribution(generator); 

    std::vector<unsigned long> numbers(amount);

    if (format == IDENTICAL)
    {
        unsigned long num = distribution(generator);
        for (unsigned long i = 0; i < amount; i++)
            numbers[i] = num;
    }
    else
    {
        for (unsigned long i = 0; i < amount; i++)
            numbers[i] = distribution(generator);
        if (format != RANDOM)
            std::sort(numbers.begin(), numbers.end());
        if (format == RSORTED)
            std::reverse(numbers.begin(), numbers.end());
    }

    return numbers;
}
