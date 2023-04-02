# Project-A
Cache simulation program


Trace files can be uploaded and used, although format must be identical to the gcc.trace file and addresses must be 64 bit.

Test cases can be created/modified in the main.cpp folder. To do so:

1) create an object of your preferred type (DirectMap, FullyAssociative, or SetAssociative).  Follow the parameters as outlined in the .h files.

2) the classes have one or two functions depending on the class.  One will correlate to FIFO and one will correlate to LRU.  Call this function with your address list.

3) compile your program.  In terminal, run the following command

	  g++ o- *name of program* main.cpp
	  ./*name of program*

4) run your program. the function will immediately start printing to terminal and creating a 'data.csv' file in the same directory.
