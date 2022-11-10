/*
 * This files includes the declarations of all given functions with its purpose.
 *
 * Author: Harsh Beriwal
 * IDE Used: MCUXpresso IDE v11.6.0 [Build 8187] [2022-07-13]
 *
 * Github Link: https://github.com/harshberiwal/PES_Assignment_6
 *
 * No leveraged code or files
 */

#ifndef COMMAND_PROCESSOR_H_
#define COMMAND_PROCESSOR_H_

#include "string.h"
#include "uart.h"
#include "hexdump.h"


/*
 * Accumulates a line of character from all the commands
 *
 * Parameters:
 *   None
 *
 * Returns:
 *  None
 */
char* accumulate_line();

/*
 * Prints the Name of the Author of the code
 *
 * Parameters:
 *   argc - The numbers of commands
 *   argv - Pointer to each command
 *
 * Returns:
 *  None
 */
void handle_author(int argc, char *argv[]);

/*
 * Tokenizes the input command line. Adds null character after every
 * command and its parameters and dispatches the handler by comparing
 * the command name with the tokenized output.
 *
 * Parameters:
 * Input String Null terminated Command line
 *
 * Returns:
 *  None
 */
void process_command(char *input);

/*
 * Prints the HexDump if the Start address and the legnth is valid
 *
 * Parameters:
 *   argc - The numbers of commands
 *   argv - Pointer to each command
 *
 * Returns:
 *  None
 */
void handle_dump(int argc, char *argv[]);

/*
 * Prints the current info of the computer, with timestamp, date and version
 *
 * Parameters:
 *   argc - The numbers of commands
 *   argv - Pointer to each command
 *
 * Returns:
 *  None
 */
void handle_info(int argc, char *argv[]);

/*
 * Prints the help string for all the command
 *
 * Parameters:
 *   argc - The numbers of commands
 *   argv - Pointer to each command
 *
 * Returns:
 *  None
 */
void handle_help(int argc, char *argv[]);

/*
 * Prints the message if unknown command is pressed by the user.
 *
 * Parameters:
 *  None
 *
 * Returns:
 *  None
 */
void handle_unknown();

#endif
