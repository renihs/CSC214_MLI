/*
 * Author: Stephen Austin Shiner
 * Account #21
 * File created: 10/17/2014 10:58:32AM
 * File completed: TODO
 * Time spent:10/19/14 - 9hrs, 10/20 - 2hrs
 * Purpose: CSC 214 - Machine Language Interpreter
 *
 *
 * Input File Name: proj1a.dat
 *
 * NOTE: function prototype(s) and #includes are defined in p3.h
 *
 * Sample I/O:
 *
 *
 */

// Preprocessor directives
#include "MLI.h"

// Represents 256-word memory using 16-bit word addressable
//static unsigned short wordMemory[256];
static word wordMemory[MEMORY_SIZE];
// Four 16-bit registers labeled r0-r3
static unsigned short r0, r1, r2, r3;
// 8-bit program counter
static unsigned short programCounter;
// 3-bit Condition Code
static unsigned short conditionCode;
// 16-bit instruction register
static word instructionRegister;

int main(int argc, char * argv[])
{
	// Variable declarations/initializations
	char buffer[17]; // String buffer for reading lines from input file
	int index = 0; // Iterator variable for "memory" storage
	int i; // Used in for loops

	FILE * inputFile = fopen(argv[1], "r"); // Establish input file connection

	if (inputFile == NULL) // Check to make sure file was successfully opened
	{
		printf("Can't open input file!\n");
		exit(1); // If file was not successfully opened, print error message and exit
	}

	// Loop reads in each instruction word from the input file and creates a word
	// struct using it, then stores it in the "memory" array
	// Loop ends at end of input file or if program "memory" is full TODO: IMPLEMENT MEMORY FULL CHECKING
	while (!feof(inputFile))
	{
		fgets(buffer, 17, inputFile); // Get next line from input file, read into char buffer
		fgetc(inputFile); // Get and throw away newline character
		//wordMemory[index] = fromStringToBinary(buffer);
		wordMemory[index] = readInstructionIntoMemory(buffer); // Pass input line to instruction creation function and store result
		index++; // Increment array index variable by one
	}

	/*
	for (i = 0; i < index; i++)
	{
		//printf("%u\n", wordMemory[i]);
		//printf("%u %u %u %u\n", wordMemory[i].opcode, wordMemory[i].addressMode,
		//						wordMemory[i].registerTarget, wordMemory[i].memoryAddress);
		//printBits(wordMemory[i]);
		printBits(wordMemory[i].opcode);
		printBits(wordMemory[i].addressMode);
		printBits(wordMemory[i].registerTarget);
		printBits(wordMemory[i].memoryAddress);
		printf("\n");
	}
	*/

	//printBits(0xF & 0xA);
	//printBits(0xF & HLT);
	if ((0xF & HLT) == 0xF)
		printf("HLT is TRUE\n");
	if ((0x1 & LOD) == LOD)
		printf("LOD is TRUE\n");

	//beginExecution(FIRST_WORD); // Call function to begin executing instructions, starting with argument memory address

	fclose(inputFile); // Terminate program/file connection with input file

	return 0; // Return 0 for successful program run
}

// Accepts 16-bit input string and returns its 16-bit word struct equivalent
word readInstructionIntoMemory(const char * str)
{
	word wrd; // 16-bit word that will be returned
	char * substr; // String to hold each substring from input file instruction word line

	substr = substring(str, 0, 4); // Get substring containing 4 opcode bits
	wrd.opcode = fromStringToBinary(substr); // Convert opcode to binary unsigned short and store

	substr = substring(str, 4, 1); // Get substring containing 1 addressing modebit
	wrd.addressMode = fromStringToBinary(substr); // Convert address mode to binary unsigned short and store

	substr = substring(str, 5, 3); // Get substring containing 3 condition code bits
	wrd.registerTarget = fromStringToBinary(substr); // Convert condition code to binary unsigned short and store

	substr = substring(str, 8, 8); // Get substring containing 8 memory address bits
	wrd.memoryAddress = fromStringToBinary(substr); // Convert memory address to binary short and store

	free(substr); // Free up memory allocated for substr substring variable

	return wrd; // Send constructed 16-bit word back out of the function
}

// Function accepts a string and returns an unsigned short representing it in base 2
unsigned short fromStringToBinary(char * str)
{
	return (unsigned short) strtol(str, NULL, 2);
}

// Returns a substring of argument str from begin position to len number of chars.
// Cannot believe C doesn't have something like this already...
char * substring(const char * str, size_t begin, size_t len)
{	// Check arguments for validity
	if (str == 0 || strlen(str) == 0 || strlen(str) < begin || strlen(str) < (begin+len))
		return 0; // If arguments are invalid, return 0
	// Return argument string + begin size to end argument size value
	return strndup(str + begin, len); // NOTE: strndup both allocates appropriate memory and appends '\0'
}

int beginExecution(unsigned short firstWord)
{
	// TODO: Increment program counter and load firstWord into IR (instruction register)
	//programCounter++; // Increment program counter by one
	programCounter = firstWord; // Initially, the program counter should be the first word argument

	// Machine Instruction Cycle: Fetch, Decode, Execute, (Writeback)
	while (1)
	{
		instructionRegister = wordMemory[programCounter]; // Load instruction into instruction register

		// Determine which operation to perform
		if (instructionRegister.opcode & LOD) // Load operation
			loadOperation(); // Call program load function
		else if ((instructionRegister.opcode & HLT) == HLT) // Halt operation
			haltOperation(); // Call program halt function
		else
			programCounter++;
	}

	return 0; // Successful executions
}

void loadOperation()
{
	programCounter++;
}

// Prints out contents of the registers, the program counter, and the condition code,
// as well as the words executed by the program. Then ends program execution
void haltOperation()
{
	int i; // Increment variable used in for loop

	programCounter++; // Increment program counter by one

	printf("Accumulator: ");
	printBits(r0); // Print out contents of accumulator register
	printf("Register 1: ");
	printBits(r1); // Print out contents of second register
	printf("Register 2: ");
	printBits(r2); // Print out contents of third register
	printf("Register 3: ");
	printBits(r3); // Print out contents of fourth register
	printf("Instruction Register: \n");
	printWord(instructionRegister); // Print out contents of instruction register
	printf("Condition Code: ");
	printBits(conditionCode); // Print out final condition code
	printf("Program Counter: ");
	printBits(programCounter); // Print out final program counter value
	printf("\n");

	// Loop iterates through each 16-bit word in memory and prints its properties
	for (i = 0; i < programCounter; i++)
	{
		printBits(wordMemory[i].opcode);
		printBits(wordMemory[i].addressMode);
		printBits(wordMemory[i].registerTarget);
		printBits(wordMemory[i].memoryAddress);
		printf("\n"); // Print newline for readability
	}

	exit(0); // Terminate program execution
}

// Procedure accepts an unsigned short value and prints out its equivalent binary value
void printBits(unsigned short i)
{
	int bits; // Iterator variable used in the for loop

	// For loop counts DOWN from actual bit length of parameter i down to 0
	// Each iteration, perform a left bitwise shift on the iterator variable's current value
	// This results in each binary value possible for the data type (in our case a long)
	// attempting an AND against the target value. If even a SINGLE 1 matches between the
	// iterator variable and the parameter value, the '&' returns 'true', and a 1 is printed
	for (bits = (sizeof(short) * 8) - 1; bits >= 0; bits--)
	{
		// Perform left-shift on iteration variable, and perform a bitwise AND operation
		if (i & (1<<bits)) // If AND with left-shifted iterator produces a binary 1 (ie TRUE),
			printf("1"); // then we've got a hit, print a 1
		else // Else it must be a zero,
			printf("0"); // so print 0
		if (bits % 4 == 0) // Every 4 bits (nibble),
			printf(" "); // print a space (for readability)
	}
	// Print equivalent values in other numeral systems after binary representation is sent to the console output stream
	printf("\n");
}

void printWord(word wrd)
{
	printBits(wrd.opcode);
	printBits(wrd.addressMode);
	printBits(wrd.registerTarget);
	printBits(wrd.memoryAddress);
}
