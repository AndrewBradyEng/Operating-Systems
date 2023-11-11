/*
COMP3602 - ASSIGNMENT 2
BOB CODE
Andrew Brady
C2O769825
16/10/2023
*/
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <unistd.h>

struct msg_buf {
 long mtype;
 char mtext[128];
} msg;

int main(){
 int running = 1;
// connecting to a message queue.
 int q_id = msgget(3333, 0777|IPC_CREAT);
 printf("Message queue %d is connected\n", q_id);

while(running){
 printf("Bob: Enter your message (or 'Bye' to exit): ");
 fgets(msg.mtext, sizeof(msg.mtext), stdin);
 msg.mtype = 1;

 msgsnd(q_id, &msg, sizeof(msg.mtext), 0);

 if(strncmp(msg.mtext, "Bye", 3) == 0){
  running= 0;
  continue;
 }
 msgrcv(q_id, &msg, sizeof(msg.mtext), 2, 0);
 printf("Alice: %s\n", msg.mtext);

 if(strncmp(msg.mtext, "Bye", 3) == 0){
  running = 0;
 }
}

return 0;
}
