# Number List Generator

This program generates large lists of numbers which can be identical, sorted, reverse-sorted, or random. 
The numbers are saved to a designated text file. It is useful for generating large lists of numbers for use 
in testing algorithms. It can be used for small lists as well. It does have a max size for the list; 
however, that max size is sufficiently large so as to not be a major concern.

Example usage:
	./numberListGenerator [datafile] [amt] [format]
        where datafile is the file to write to
        amt is the amount to generate
        and format can take 1 of 4 values:
            identical
            random
            sorted
            rsorted

