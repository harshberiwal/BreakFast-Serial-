/*
 * This files implements a State Machine for Handling various commands given
 * by the user in the serial terminal for the breakfastserial.
 *
 * The details of each function is given in the respective .h file.
 *
 * Author: Harsh Beriwal
 * IDE Used: MCUXpresso IDE v11.6.0 [Build 8187] [2022-07-13]
 *
 * Github Link: https://github.com/harshberiwal/PES_Assignment_6
 *
 * Part of Process Command function was taken from the Dean's book and lecture slides.
 */

#include "command_processor.h"

#define BACKSPACE   	8
#define NULL_CHARACTER	255
#define MAX_INDEX		255
#define WHITESPACE		32
#define COMMAND_INDEX	10
#define MAX_DUMP_LENGTH	640
#define HEX_BASE		16

//*************************CREATING ENUM FOR AGRV*******************************
enum{
	command,
	address,
	length,
};

typedef void (*command_handler_t)(int, char *argv[]);

//*********************CREATING A STATE MACHINE TABLE*****************************
typedef struct {
 const char *name;
 command_handler_t handler;
 const char *help_string;
}command_table_t;


//******************CREATING TABLE CONTENTS FOR EACH COMMANDS*********************
static const command_table_t commands[] = {
	 {"Author", handle_author, "Prints the Author of this code\n\r"},
	 {"Dump", handle_dump, "Output a Hexdump starting at location loc.\n\r\t"
			 "Always specify loc in hex, specify len in hex(0xNN) or dec(NN)\n\r"},
	 {"Info", handle_info, "Print various build info\n\r"},
	 {"help", handle_help, "Print this help message\n\r"},
};

static const int num_commands = sizeof(commands)/sizeof(command_table_t);

//*********************CONTAINS THE CHARACTERS ENTERED****************************
char cmd[256];

char* accumulate_line()
{
	//***********************CLEARS THE LAST COMMAND CONTENTS*********************
	memset(cmd,0,256);
	char *str;
	int c=0;
	int count =0;
	str = cmd;
	c = getchar();                   			     //Takes value from the User
	//*******************LOOPS UNTIL THE USER PRESSED ENTER***********************
	while(c!='\r'){
	if((c == BACKSPACE) && (count !=0))				//HANDLING BACKSPACE
		cmd[--count] = 255;
	else if((c!=NULL_CHARACTER) && (c!=BACKSPACE))	//Inserts the character
		cmd[count++] = c;
	if(count ==MAX_INDEX)
		count =0;
	c = getchar();
	}
	cmd[count] ='\0';						//Inserts Null character after the line
	return str;
}

void process_command(char *input)
{
	char *p = input;
	char *end;
	//*************FINDING THE END OF THE STRING AND POINTING TO IT****************
	for(end = input; *end!= '\0';end++);
	char *argv[COMMAND_INDEX];
	int argc =0;
	int first_command =0, command_taken =0;
	memset(argv, 0, sizeof(argv));				//Clearing previous command address
	for(p = input; p<end; p++){
		//***************POINTING TO THE FIRST COMMAND CHARACTER*******************
		if((*p!=WHITESPACE) & (!command_taken)){
			argv[argc] = p;
			argc++;
			command_taken =1;
			first_command =1;
		}
		//*****************INSERTING NULL CHRACTER AFTER THE COMMAND***************
		else if((*p==WHITESPACE) && first_command){
			*p = '\0';
			first_command =0;
			command_taken =0;
		}
	}
	//******************IF DIRECTLY ENTER IS PRESSED, DO NOTHING*******************
	if(argc ==0)
		return;
	//*********************DISPATCH HANDLER AFTER TOKENIZING***********************
	for(int i =0; i<num_commands; i++){
		if(strcasecmp(argv[command], commands[i].name) == 0){
			commands[i].handler(argc, argv);
			return;
		}
	}
	handle_unknown(argc, argv);						//handles unknown command
}

void handle_author(int argc, char *argv[])
{
	printf("\n\rHarsh Beriwal\n\r");
}

void handle_dump(int argc, char *argv[])
{
	char *start_address = 0;
	int len =0;
	//********************CONVERTS HEXSTRING TO DECIMAL***********************
	start_address = (char *)strtol(argv[address], 0, HEX_BASE);
	//********************IF LENGTH IS ENTERED IN HEX*************************
	if((*(argv[length]+1) == 'x')|| (*(argv[length]+1) == 'X'))
		len = strtol(argv[length],0, HEX_BASE);
	//************************LENGTH IS ENTERED IN DEC************************
	else
		len = atoi(argv[length]);
	//*******************CHECKS IF LENGTH IS WITHIN LIMITS********************
	if(len<0 || len>MAX_DUMP_LENGTH)
		printf("\n\rInvalid Length\n\r");
	//******************DISPLAYS HEXSTRING OF GIVEN ADDRESS*******************
	else
		hexdump(start_address, len);
}

void handle_help(int argc, char *argv[])
{
	printf("\n\r");
	for(int i=0; i<(num_commands); i++)
	{
		printf("%s ", commands[i].name);			//Prints the command name
		if(i==1)
			printf("<loc> <len>");
		printf("\n\r\t");
		printf("%s", commands[i].help_string);		//Prints the help string
	}
}

void handle_info(int argc, char *argv[])
{
	printf("\n\r%s built on %s at %s\n\rCommit %s\n\r", VERSION_TAG, VERSION_BUILD_MACHINE, VERSION_BUILD_DATE, VERSION_BUILD_INFO);
}

void handle_unknown(int argc, char *argv[])
{
	printf("\n\rUnknown Command: ");
	while(*argv[command] != '\0')
		 printf("%c", *argv[command]++);
	printf("\n\r");
}

