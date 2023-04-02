# Cache-Project
This C++ project simulates a cache system using different replacement policies and reports the hit ratio of each test.  The data is output into a "data.csv" file that can be used for further analysis. The **main.cpp** file uses **gcc.trace** to implement **DirectMap.H, FullyAssociative.H,** and **SetAssociative.h**.  

If you have a trace file you'd like to test, be sure to name it "gcc.trace", or edit line 36 in main.cpp accordingly. Addresses must be 64 bit, but the l and s characters at the beginning of each line, along with the single-digit at the end of each line, are ignored by the program.  So, in theory, any character could replace these and the file will still be read the same.  See the **LoadTraceFile** function in **main.cpp** to better understand how the trace file lines are interpreted.

Test cases can be created/modified in the main.cpp folder. To do so:

1) create an object of your preferred type (DirectMap, FullyAssociative, or SetAssociative).  The first parameter should be the cache size (in bytes), the second paramter should be the number of bytes per line, the third parameter should be the integer 64.

2) the classes have one or two functions depending on the class.  **FullyAssociative.h** and **SetAssociative.h** each have the FIFORatio and LRURatio functions, while **DirectMap.h** only has a HitRatio function.

3) To compile your program with g++, run the following command in terminal:

	  g++ o- \*name of program\* main.cpp

4) To run your program, simply use the following command. Note that the function will immediately start printing to terminal and creating a 'data.csv' file in the same directory. This process can take a while.
		
	  ./\*name of program\*

