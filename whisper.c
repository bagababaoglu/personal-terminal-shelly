#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <mqueue.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <time.h>




int main(int argc, char *argv[]){

    //For random number
    srand(time(NULL));


    //Set queue
    struct mq_attr attr, old_attr;
    struct sigevent sigevent;

    mqd_t mqdes, mqdes2;
    
    char buf[100];
    unsigned int prio;

    attr.mq_maxmsg = 1024;
    attr.mq_msgsize = 4096;
    attr.mq_flags = 0;


    //TAKE A WORD AS INPUT
    //printf("Enter a word: ");
    char strInput[100];
    //scanf("%s",strInput);
    //printf("%s",strInput);
    strcpy(strInput,argv[1]);

   

    //Fork N processes where N is the number of characters in the input
    size_t NFork = strlen(strInput);
    int nFork = (int) NFork;



    //mqdes2= mq_open("/test-queue",O_RDWR | O_CREAT, 0664, 0);
    //mq_unlink("/test-queue");

    //mq_getattr(mqdes,&attr);



    //if(mqdes==-1){
    //    printf("[ERROR]: Queue not created!\n");
    //    perror("QUEUE NOT CREATED!\n");
    //}


    //mq_send(mqdes,strInput,4096,0);
    //fflush(stdout);

    //For random number
    int r;

    //printf("ARE THERE MESSAGES ON THE QUEUE?  %d",attr.mq_curmsgs);
    int pid;
    for(int i=0;i<nFork;i++){
        pid = fork();
        if(pid<0){
            printf("FORK ERROR!\n");
            exit(1);
        }else if(pid==0){ //Child
            //printf("Child: %d\n",getpid());

            //Open the queue
            mqdes = mq_open("/bbqueue9", O_CREAT | O_WRONLY, 0666, NULL);
            //strncpy (buf, strInput, sizeof(buf));

            if(mqdes==-1){
                printf("[ERROR]: Child %d could not create queue.\n",getpid());
                int sterr = errno;
                printf("%s\n",strerror(sterr));
            }
            //printf("NUMBER OF BYTES IN THE QUEUE %d\n",attr.mq_msgsize);



            //If first child, just send. If not, then first get the message and then send.
            if(i==0){
                //int data_read = mq_receive(mqdes,nFork,) 

                //Generate a random number
                r = rand()%10;
                //printf("%d\n",r);
                if(r>5){
                    strInput[i]++;// = strInput[i] + '1'; 
                }

                if(mq_send(mqdes,strInput,sizeof(strInput)+1,0)==-1){
                    int sterr = errno;
                    printf("%s\n",strerror(sterr));    
                }
            }else{ //The nth child will receive the message from n-1th child and then send it to n+1th chield
                //printf("XDXDXDXD\n");
                //Generate a random number
                //printf("XDXDXDXDXDXDXD\n");

                if (mq_receive(mqdes, buf,sizeof(buf)+1, 0) == -1)
                    {
                        int sterr = errno;
                        //printf("XD\n");
                        //printf("%s\n",strerror(sterr));
                        //printf("XD\n");
                        //exit(1);

                    }
                    int b= rand()%10;
                    if(b>5){
                        buf[i]++;// = strInput[i] + '1'; 
                    }
                    strcpy(buf,strInput);
                //printf("Received %s and will send it again.\n",buf);
                if(mq_send(mqdes,strInput,sizeof(strInput)+1,0)==-1){
                    int sterr = errno;
                    //printf("XD\n");
                    printf("%s\n",strerror(sterr));    
                    //printf("XD\n");
                }
            }
            

            //printf("XDXDXDXDXD\n");
            mq_close(mqdes);

            exit(0);
        }else{ //Parent
            wait(NULL); //Wait for child
        }
        
    }

    //Remaining is only PARENT
    mqdes = mq_open("/bbqueue9",O_CREAT | O_RDONLY, 0666, &attr);
    if(mqdes==-1){
        printf("[ERROR]: Parent could not create queue.\n");
        int sterr = errno;
        printf("%s",strerror(sterr));
    }
    char buffer[10000];
    for(int j=0;j<nFork;j++){

        mq_getattr(mqdes,&attr);
        //printf("NUMBER OF BYTES IN THE QUEUE %d\n",attr.mq_msgsize);
        if (mq_receive(mqdes, buffer, sizeof(buffer)+1, 0) == -1)
        {
            int sterr = errno;
            //printf("XD\n");
            printf("%s\n",strerror(sterr));
            //printf("XD\n");
            //exit(1);
        }
        if(j==0){ //Receive the message from the biggest (oldest) child.
            printf("%s\n",buffer);
        }

    }

    //mq_receive(mqdes,&buf[0],4096,&prio);
    mq_unlink("/bbqueue9");
    mq_close(mqdes);
    //printf("FINAL CHECK ON PARENT BEFORE EXITING: %s!\n",buf);
    
    return 0;
}
