# PES_Assignment_6

 Implementing a SerialBreakfast on the terminal that allows the user to interact with the FRDM board in real-time. 
 Check the hex values at any address, plus info about the build. 
 The code is supposed to be run in DEBUG Mode as it is part of internal use only. 
  
 Author: Harsh Beriwal, harsh.beriwal@colorado.edu
         Howdy Pierce, howdy.pierce@colorado.edu
  		   
 Modified by: Harsh Beriwal
 
 IDE Used: MCUXpresso IDE v11.6.0 [Build 8187] [2022-07-13]
 Github Link: https://github.com/harshberiwal/PES_Assignment_6
 
 Leveraged Code: UART_init and UART_IRQ handler in UART.c and UART.h was taken from Alexander Dean Github Repo the link to which is below.
 https://github.com/alexander-g-dean/ESF/blob/master/NXP/Code/Chapter_8/Serial-Demo/src/UART.c
 
 Few Quotes were taken from - https://blog.hubspot.com/sales/famous-quotes as part of cbfifo.c testing in test_cbfifo.c file. 
 
 The files includes a state machine for tokenizations of the accumulated line in the serial. Following are the important programs given in the files. 
 
 1)char * accumulate_line() - The Accumulated line is seperated by \r\n. The accumulate line function includes a Null chracter after \r is detected. 
  

 2)void Process_command(char * input_str) -  This function takes the accumulated line and adds a null character at the blank space after every command. 
  This helps us differentiate between the command and its paramters (arguments). This Function also makes a pointer points to the first
  character of the command. The function after all lexical analysis calls the dispatch function which is created using a state machine table. 
  
  
 3) void handle_dump(int argc, char * argv[]):   Prints the HexDump if the Start address and the legnth is valid
 Parameters:
  argc - The numbers of commands
  argv - Pointer to each command


 4) void handle_info(int argc, char * argv[]):  Prints the current build info of the code, with timestamp, date and version along with the machine name. 
 Parameters:
  argc - The numbers of commands
  argv - Pointer to each command


 5) void handle_author(int argc, char * argv[]): Prints the Name of the Author of the code
 Parameters:
  argc - The numbers of commands
  argv - Pointer to each command
  
  
 6) void handle_help(int argc, char * argv[]): Prints the help string for all the command
 Parameters:
  argc - The numbers of commands
  argv - Pointer to each command
  
  
 7) void handle_unknown(): Prints a message if unknown command is pressed by the user.
 
 
 8) void hexdump(char * start_add, int length) : Prints the HexDump for a valid start addrress and length
 Parameters:
   start address - The start address to print from
   length - The number of bytes to print in hex
 
 
 9) int sys_write(int handle, char * buf, int size) : This function is called when Printf is called as it overwrites the weak function given for printf in the REDLIB. 
 
 
 10) int __sys_readc(void)__ This function is called when getchar() function is called as it overwrites the weak function given for getchar in the REDLIB. 
 
 
 __EXTRA CREDIT__
 
 1) Backspace was handled by clearing the array element when backspace is entered and moving the array index back. 
 2) Info command was added by adding a makefile.defs which the preprocessor looks for. The info prints the current Github Tag,
    build date, build machine and the commit ID.
    THe Help command was also added to provide help to the user when a particular command is not comphrehensible. 
    
 3) The screenshots required for the submission is included in this Github Repository at https://github.com/harshberiwal/PES_Assignment_6/tree/main/screenshots
 
 
 
