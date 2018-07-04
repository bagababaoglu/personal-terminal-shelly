/*
 * shelly interface program

KUSIS ID:49928  PARTNER NAME:Berke Ağababaoğlu
KUSIS ID:49752  PARTNER NAME:Berkan Hızıroğlu

 */

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <assert.h>
#include <sys/types.h>
#include <signal.h>
#include <errno.h>


#define MAX_LINE 80 /* 80 chars per line, per command, should be enough. */


typedef struct NodeTag {
    char *data;
    struct NodeTag *next;
} Node;

typedef struct ListTag {
    struct NodeTag *first;
} List;



Node *Node_create();
void Node_destroy(Node *node);
List *List_create();
void List_destroy(List *list);
void List_append(List *list, char *str);
void List_insert(List *list, int index, char *str);
char *List_get(List *list, int index);
int List_find(List *list, char *str);
void List_remove(List *list, int index);
char *List_pop(List *list, int index);
int List_length(List *list);
void List_print(List *list);


int parseCommand(char inputBuffer[], char *args[], int *background);
int checkIO(char *args[]);
int findNull(char *args[]);


int saveBookmarks(List *l, FILE *f);
int readBookmarks(List *l, FILE *f);
int checkBookmarks(List l);


int main(void)
{
	FILE *cout;
	FILE *ncout;
	FILE *croncommand;
	FILE *crons;
	FILE *bookmarkf;
	FILE *fptr; //file for script command
	char inputBuffer[MAX_LINE];   /* buffer to hold the command entered */
	int background;				  /* equals 1 if a command is followed by '&' */
	char *args[MAX_LINE / 2 + 1]; /* command line (of 80) has max of 40 arguments */
	pid_t child;				  /* process id of the child process */
	int status;					  /* result from execv system call*/
	int shouldrun = 1;
    int script=0;
	int i, upper;	
	char * filename[80];
	char * pathtohome[50];
	char * command[120];
	List *bookmarks = List_create();

				strcpy(filename,"");
				strcpy(pathtohome,"");
				strcpy(filename, ".mybookmarks");
				//strcpy(pathtohome, "/home/berkan/");
				strcpy(pathtohome, "/home/bagababaoglu/");  //this part will change in another computer
				strcat(pathtohome, filename);
				
			//	fprintf(bookmarkf, "323423423");
			//	fclose(bookmarkf);			
			//	readBookmarks(bookmarks,bookmarkbookmarkff);
		//		List_append(bookmarks, "bergerregre");
		//	   List_print(bookmarks);
			//   Node *node = bookmarks->first;
			//	prinf("%s\n",node->data);

	



   

   
	
	while (shouldrun!=0)

	{ /* Program terminates normally inside setup */


		background = 0;
		shouldrun = parseCommand(inputBuffer, args, &background); /* get next command */
		


				//this part is for checking the script command.
//				printf ("%s\n", inputBuffer);

	


		if (strncmp(inputBuffer, "exit", 4) == 0)
		{


		shouldrun = 0; /* Exiting from myshell*/
		//saveBookmarks(bookmarks,bookmarkf);
		List_destroy(bookmarks);
		if (script ==1)
		{
		fprintf(fptr, "exit");	
		fclose(fptr);
		}

		}

		


		if (shouldrun!=0)
		{




		int number = findNull(args);
			if (strcmp(args[0], "script")==0 && number ==2)
				{
				script=1;
				fptr = fopen(args[1],"w");
//				fputs("This is testing for fputs...\n", fptr);


				}




			pid_t pid;
			pid = fork();

			int fd;
			

			if (pid > 0) //Parent process
			{
				
				if (background == 0) //background=1 if they write & //waits if user doesn't write & because if they write & this means that process should be in background. Parent process keeps going.
				{
					wait(0);
				}
				
				
				
				
			}
			else if (pid == 0) //Child process
			{
				//		printf("blavla");
				//		printf ("\nI am checking what is input buffer: %s\n",inputBuffer);
				//		fflush(stdout);
				//		sleep(10);
				
//				printf("10\n");			

			// Check for redirection
			//	printf ("%s\n", args[number-2]);
		

				if (script ==1)
				
				{

				   if(fptr == NULL)
			  		 {	
			 	     printf("Error!");   
			     	     exit(1);             
			  		 }
				strcpy(command, "");	
				for (int i =0; i<number; i++)
				{
				strcat(command, args[i]);
			    strcat(command, " ");
			//	printf("%s\n", command);
				}
				strcat (command, "\n");
					
			//	fputs(command, fptr);
			//	printf("%s\n", command);
				fprintf(fptr, "%s", command);			
					
 				}	

			
				int sc=-1;
				int sc1=-1;
				if (number >2)
				{

			        sc=strcmp(args[number-2],">");
			        sc1=strcmp(args[number-2],">>");
				}else{
				sc=-1;
				sc1=-1;
				}

			//	printf("%d\n", sc);			
				if(sc==0)
				{
					fd = open(args[number-1], O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
					dup2(fd, 1);
					args[number]=NULL;
					args[number-1]=NULL;
					args[number-2]=NULL;

				}else if (sc1==0)
				{
				
					fd = open(args[number-1], O_CREAT | O_RDWR | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
					dup2(fd, 1);
					args[number]=NULL;
					args[number-1]=NULL;
					args[number-2]=NULL;

				}

				char path[80];
				char program[80];
				strcpy(program, args[0]);
				strcpy(path, "/bin/");
				strcat(path, program);
				
			// this part is for checking new commands if else statements


                if (strcmp(args[0],"whisper")==0)
				{
					
					if (execv("q4", args) < 0) 
						{     
             			printf("There isn't any program file.\n");
                		exit(1);
            			}	
				}else if (strcmp(args[0],"bookmark")==0){
					//bookmark
					//Save key,value to txt
					char key[1024]; //Max size for key is 1024
					//Instead of args[2], there should be a string for all the remaining arg values
					//FILE *bookmarkfile = fopen(dir, "a");
					bookmarkf=fopen (pathtohome , "a+");
				int sterr = errno;
               		 printf("%s\n",strerror(sterr));
					if(bookmarkf!=NULL){
						
						//printf(" PRINTING TO BOOK MARK \n");
						fprintf(bookmarkf," %s %s\n",args[1],args[2]);
						//fprintf(bookmarkf,"dasdasdas\n");
					}
					fclose(bookmarkf);
					exit(0);


				//this part is for my shelly command
				//It will comment out given txt file
				}else if (strcmp(args[0],"commentout")==0){
				if (number==2){
					int line=0;
					cout=fopen (args[1], "r");
					ncout=fopen("tmp","w");
					char str[255]="";
					char temp[3]="";
					int c;
					if(cout == NULL) {
     				 perror("Error in opening file");
      				return(-1);
   					} do {
     				 c = fgetc(cout);
				
      				 if( feof(cout) ) {
            		break ;
   					   }
				
					if(line==0){
					temp[0]='/';
					temp[1]='/';
					temp[2]=c;
					temp[3]='\0';
					fprintf(ncout,"%s",temp);
					line=1;
					}else
					fprintf(ncout,"%c",c);


						if(c=='\n'){
						line=0;
					}
      				
   					} while(1);

					fprintf(ncout,"%c",'\n');

					fclose(cout);
					fclose(ncout);

					cout=fopen (args[1], "w");
					ncout=fopen("tmp","r");
					if(ncout == NULL) {
     				 perror("Error in opening file");
      				return(-1);
   					} do {
     				 c = fgetc(ncout);
				
      				 if( feof(ncout) ) {
            		break ;
   					   }
				
					
					fprintf(cout,"%c",c);
      				
   					} while(1);

					fclose(cout);
					fclose(ncout);
					remove("tmp");

					exit(0);
				
				}else{

					printf("Error CommentOut");
					exit(1);
				}



				}
				else if(strcmp(args[0],"script")==0)
				{

            			exit(0);
					
				}else if (strcmp(args[0],"wforecast")==0){

					crons =fopen("/var/spool/cron/crontabs/bagababaoglu" , "a");
                    croncommand=fopen("/home/bagababaoglu/.croncommand.sh","w");
				    //this part is for editing the executable file
					char str [255]="bash -c 'curl wttr.in/Istanbul.png > /home/bagababaoglu/";
					strcat(str, args[1]);
					strcat(str,"'");
					fprintf(croncommand,"%s\n",str);
					//this part is for editing crons file
					char mycron[255]="0 9 * * * /home/bagababaoglu/.croncommand.sh\n";
					fprintf(crons, "%s" ,mycron);
					

					fclose (crons);
					fclose(croncommand);
					exit(0);
					
					
					
				}else
				{
						
					//Check for bookmark before executing:

					bookmarkf = fopen(pathtohome, "a+");
					char *line = NULL;
					size_t len = 0;
					ssize_t read;
					if (bookmarkf != NULL) {
						while ((read = getline(&line, &len,bookmarkf)) !=-1) {
						// printf("Retrieved line of length
						// %zu :\n", read);
					//	printf("%s XD\n", line);
						char *token = strtok(line, " ");
						while (token) {
							if(strcmp(args[0],token)==0){
								int sterr = errno;
								token = strtok(NULL, " ");
							//	printf("%s",token);
								//char args={};
								char * temp[255];
								int len=strlen (token);
								strncpy(temp, token, len-1);
							//	printf("%s\n",strerror(sterr));
							//	printf("%s\n",temp);
								
								if (execvp(temp, args) < 0) {
									
                					printf("%s\n",strerror(sterr));
									printf("ERROR: exec failed\n");
                					exit(0);
            					}
							}
							token = strtok(NULL, " ");
						}
						}
					}


					//If bookmark not found, execute !!!!!!
					if (execvp(args[0], args) < 0) {     
								printf("ERROR: exec failed\n");
                		exit(0);
            			}	
                		
				}


			
			}

			else
			{
				//you will come here only if fork() fails.
				printf("forkFailed\n");
			}

			/*
	After reading user input, the steps are 
        (1) Fork a child process using fork()
	(2) the child process will invoke execv()
	(3) if command included &, parent will invoke wait()
       */
		}
	}
	return 0;
}

int checkIO(char *args[])

{

	int i;
	for (i = 0; i < findNull(args); i++)
	{

		//	printf("%s\n",args[i]);
		if (strstr(args[i], ">") || strstr(args[i], ">>"))
		{
			return 1;
		}
	}
	return 0;
}
int findNull(char *args[])
{
	int c = 0;
	for (int i = 0; i < 80; i++)
	{
		if (args[i] == NULL)
		{
			return c;
		}
		c++;
	}
	return -1;
}

/** 
 * The parseCommand function below will not return any value, but it will just: read
 * in the next command line; separate it into distinct arguments (using blanks as
 * delimiters), and set the args array entries to point to the beginning of what
 * will become null-terminated, C-style strings. 
 */

int parseCommand(char inputBuffer[], char *args[], int *background)
{
	int length,			/* # of characters in the command line */
		i,				/* loop index for accessing inputBuffer array */
		start,			/* index where beginning of next command parameter is */
		ct,				/* index of where to place the next parameter into args[] */
		command_number; /* index of requested command number */

	ct = 0;

	/* read what the user enters on the command line */
	do
	{
		printf("shelly>");
		fflush(stdout);
		length = read(STDIN_FILENO, inputBuffer, MAX_LINE);
	} while (inputBuffer[0] == '\n'); /* swallow newline characters */

	/**
     *  0 is the system predefined file descriptor for stdin (standard input),
     *  which is the user's screen in this case. inputBuffer by itself is the
     *  same as &inputBuffer[0], i.e. the starting address of where to store
     *  the command that is read, and length holds the number of characters
     *  read in. inputBuffer is not a null terminated C-string. 
     */
	start = -1;
	if (length == 0)
		exit(0); /* ^d was entered, end of user command stream */

	/** 
     * the <control><d> signal interrupted the read system call 
     * if the process is in the read() system call, read returns -1
     * However, if this occurs, errno is set to EINTR. We can check this  value
     * and disregard the -1 value 
     */

	if ((length < 0) && (errno != EINTR))
	{
		perror("error reading the command");
		exit(-1); /* terminate with error code of -1 */
	}

	/**
     * Parse the contents of inputBuffer
     */

	for (i = 0; i < length; i++)
	{
		/* examine every character in the inputBuffer */

		switch (inputBuffer[i])
		{
		case ' ':

			//	if(start != -1){
			//	  args[ct] = &inputBuffer[start];    /* set up pointer */
			//	  ct++;
			//	}
			//	inputBuffer[i] = '\0'; /* add a null char; make a C string */
			//	start = -1;
			//	break;

		case '\t': /* argument separators */
			if (start != -1)
			{
				args[ct] = &inputBuffer[start]; /* set up pointer */
				ct++;
			}
			inputBuffer[i] = '\0'; /* add a null char; make a C string */
			start = -1;
			break;

		case '\n': /* should be the final char examined */
			if (start != -1)
			{
				args[ct] = &inputBuffer[start];
				ct++;
			}
			inputBuffer[i] = '\0';
			args[ct] = NULL; /* no more arguments to this command */
			break;

		default: /* some other character */
			if (start == -1)
				start = i;
			if (inputBuffer[i] == '&')
			{
				*background = 1;
				inputBuffer[i - 1] = '\0';
			}
		} /* end of switch */
	}	 /* end of for */

	/**
     * If we get &, don't enter it in the args array
     */

	if (*background)
		args[--ct] = NULL;

	args[ct] = NULL; /* just in case the input line was > 80 */

	return 1;

} /* end of parseCommand routine */


//these parts are from online sources 
//linked-list implemetation
Node *Node_create() {
    Node *node = malloc(sizeof(Node));
    assert(node != NULL);

    node->data = "";
    node->next = NULL;

    return node;
}


void Node_destroy(Node *node) {
    assert(node != NULL);
    free(node);
}


List *List_create() {
    List *list = malloc(sizeof(List));
    assert(list != NULL);

    Node *node = Node_create();
    list->first = node;

    return list;
}


void List_destroy(List *list) {
    assert(list != NULL);

    Node *node = list->first;
    Node *next;
    while (node != NULL) {
        next = node->next;
        free(node);
        node = next;
    }

    free(list);
}


void List_append(List *list, char *str) {
    assert(list != NULL);
    assert(str != NULL);

    Node *node = list->first;
    while (node->next != NULL) {
        node = node->next;
    }
//	printf("%s\n",str);
//	strcat(str,"\0");
//	strcpy(str,"");	
    node->data = str;
    node->next = Node_create();
}


void List_insert(List *list, int index, char *str) {
    assert(list != NULL);
    assert(str !=NULL);
    assert(0 <= index);
    assert(index <= List_length(list));

    if (index == 0) {
        Node *after = list->first;
        list->first = Node_create();
        list->first->data = str;
        list->first->next = after;
    } else if (index == List_length(list)) {
        List_append(list, str);
    } else {
        Node *before = list->first;
        Node *after = list->first->next;
        while (index > 1) {
            index--;
            before = before->next;
            after = after->next;
        }
        before->next = Node_create();
        before->next->data = str;
        before->next->next = after;
    }
}


char *List_get(List *list, int index) {
    assert(list != NULL);
    assert(0 <= index);
    assert(index < List_length(list));

    Node *node = list->first;
    while (index > 0) {
        node = node->next;
        index--;
    }
    return node->data;
}


int List_find(List *list, char *str) {
    assert(list != NULL);
    assert(str != NULL);

    int index = 0;
    Node *node = list->first;
    while (node->next != NULL) {
        if (strlen(str) == strlen(node->data)) {
            int cmp = strcmp(str, node->data);
            if (cmp == 0) {
                return index;
            }
        }
        node = node->next;
        index++;
    }
    return -1;
}


void List_remove(List *list, int index) {
    assert(list != NULL);
    assert(0 <= index);
    assert(index < List_length(list));

    if (index == 0) {
        Node *node = list->first;
        list->first = list->first->next;
        Node_destroy(node);
    } else {
        Node *before = list->first;
        while (index > 1) {
            before = before->next;
            index--;
        }
        Node *node = before->next;
        before->next = before->next->next;
        Node_destroy(node);
    }
}


char *List_pop(List *list, int index) {
    assert(list != NULL);
    assert(0 <= index);
    assert(index < List_length(list));

    if (index == 0) {
        Node *node = list->first;
        list->first = list->first->next;
        char *data = node->data;
        Node_destroy(node);
        return data;
    } else {
        Node *before = list->first;
        while (index > 1) {
            before = before->next;
            index--;
        }
        Node *node = before->next;
        before->next = before->next->next;
        char *data = node->data;
        Node_destroy(node);
        return data;
    }
}


int List_length(List *list) {
    assert(list != NULL);

    Node *node = list->first;
    int length = 0;
    while (node->next != NULL) {
        length++;
        node = node->next;
    }

    return length;
}


void List_print(List *list) {
    assert(list != NULL);

    
    Node *node = list->first;
    while (node->next != NULL) {
        printf("%s\n", node->data);
        node = node->next;
    }
   
}

int saveBookmarks(List *l, FILE *f){






return 0;
}


int readBookmarks(List *l, FILE *f){
char str[255];
if (f==NULL){
return 1;

}else {
 while (fgets(f, "%s", str)!=EOF)
		{
	//	printf("%s\n",str);
		List_append(l,str);
        
 		}
 		

return 0;

}







}