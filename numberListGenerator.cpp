//IMPORTANT: Must be compiled in C++ 11 or higher

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


/*
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
int main(int argc, char** argv)
{
    const int RANGE = 1000000;

    unsigned long numOfNums = 0;

        //parse input
        
        if (argc != 4)    //checks for correct # of args
        {
            std::cerr << "input should be:\ninputFileGenerator [datafile] [amt] [format]\n";
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
        catch (std::exception)
        {
            std::cerr << "Something really weird happened when trying to parse 2nd argument.\n";
            return 1;
        }

        //verify that number is possitive

        if (numOfNums < 0)
        {
            std::cerr << "# of items must be positive\n";
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

        std::default_random_engine generator;
        generator.seed(time(NULL));
        std::uniform_int_distribution<int> distribution(0, RANGE);
        distribution(generator); //flushing out the initial value, which may be extremely similar to the last run of the program.

        if (format == "identical")
        {
            int num = distribution(generator);
            for (unsigned long i = 0; i < numOfNums; ++i)
                outfile << num << std::endl;
        }
        else if (format == "random")
        {
            for (unsigned long i = 0; i < numOfNums; ++i)
                outfile << distribution(generator) << std::endl;
        }
        else if (format == "sorted" || format == "rsorted")
        {
            std::vector<int> ary(numOfNums);

            for (unsigned long i = 0; i < numOfNums; ++i)
                ary[i] = distribution(generator);

            std::sort(ary.begin(), ary.end());
            if (format == "rsorted")
                std::reverse(ary.begin(), ary.end());

            for (unsigned long i = 0; i < numOfNums; ++i)
                outfile << ary[i] << std::endl;
        }
        else
            std::cerr << "invalid format type\n";


        outfile.close();


    return 0;
}