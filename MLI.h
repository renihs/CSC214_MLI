/*
 * Author: Stephen Austin Shiner
 * Account #21
 * File created: 10/17/2014 10:17:08AM
 * File completed: TODO
 *
 * Purpose: CSC 214 - Machine Language Interpreter
 * This is the Machine Language Interpreter (MLI) header file, containing all function prototypes,
 * define directives, and library #include directives
 *
 *
 */

// Preprocessor directives
#include <stdio.h> // For access to C's I/O functionality
#include <stdlib.h> // For C standard library functionality
#include <string.h> // For splitting input file lines up
#include <ctype.h> // For isprint and isspace functions
#define MEMORY_SIZE 256 // Number of 16-bit words possible
#define FIRST_WORD 0 // Memory address of first 16-bit instruction word

// Check for namespace collisions
#ifndef MLI_H_
#define MLI_H_

// Structs and enums
typedef struct
{
	unsigned short opcode;
	unsigned short addressMode;
	unsigned short registerTarget;
	unsigned short memoryAddress;
} word;

// Define the 16 4-bit opcodes
static unsigned short LOD = 0x0; // load *				-> Load register -- LOD rN or LOD
static unsigned short STO = 0x1; // store *    			-> Store register -- STO rN or STO
static unsigned short ADD = 0x2; // add *   	  		-> Add r0/A and memory
static unsigned short SUB = 0x3; // subtract * 			-> Subtract r0/A and memory
static unsigned short ADR = 0x4; // add indirect * 		-> Add rN and memory
static unsigned short SUR = 0x5; // subtract indirect * -> Subtract rN and memory
static unsigned short AND = 0x6; // logical AND *		-> Logical AND rN and memory
static unsigned short IOR = 0x7; // logical OR *		-> Logical OR rN and memory
static unsigned short NOT = 0x8; // logical NOT *		-> Logical Negate rN
static unsigned short JMP = 0x9; // jump				-> Unconditionally jumps to rN
static unsigned short JEQ = 0xA; // jump EQUAL **		-> Jumps to rN if and only if
static unsigned short JGT = 0xB;
static unsigned short JLT = 0xC;
static unsigned short CMP = 0xD;
static unsigned short CLR = 0xE;
static unsigned short HLT = 0xF;
// *  indicates that the operation affects condition codes
// ** indicates that the operation is AFFECTED BY condition codes

// Function prototypes
word readInstructionIntoMemory(const char * str); // Accepts a string, then creates and returns its 16-bit word equiv
unsigned short fromStringToBinary(char * str); // Returns binary short version of argument string
char * substring(const char * str, size_t begin, size_t end); // Returns substring from begin to end of argument string
int beginExecution(unsigned short firstWord); // Begins executing instructions, starting with the word at the argument's memory address
void loadOperation();
void haltOperation();
void printBits(unsigned short i);


#endif /* MLI_H_ */
