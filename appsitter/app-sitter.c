#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<time.h>


int task_no = 0;
char *cmd_name;
char *arguments;
char *path = "/bin/";
char *buf;

struct task {
    int task_id;
    struct task *next;
    int exec_val;
    char *name;
    pid_t *pid;
    time_t start_time;
    time_t end_time;
    char *argument;
};

void add_to_list(struct task **head_ptr, char *name, char *argument){
    struct task *node = (struct task *)malloc(sizeof(struct task));
    node->task_id = task_no;
    node->name = name;
    printf("task No:%d  %s\n", node->task_id, node->name);

    node->argument = argument;
    printf("%s\n", node->argument);

    node->next = *head_ptr;
    *head_ptr = node;
    task_no++;
}

void execute(struct task *current_ptr, char *path_name, pid_t pid){
     current_ptr->start_time = time(NULL);
     //printf("pid: %d, time: %ld", *current_ptr->pid, current_ptr->start_time);
    *current_ptr->pid = pid;
    //char * argv_list[] = {current_ptr->argument ,(char*)0};
    //printf("current running: %s, %s", current_ptr->name, current_ptr->argument);
    //execl("/bin/ls", "ls",current_arg, (char *)0);
    execl(path_name, current_ptr->name, current_ptr->argument, (char *)0);
    //printf("current running: %s, %s\n", current_ptr->name, current_ptr->argument);
    //printf("pid: %d, time: %ld\n", *current_ptr->pid, current_ptr->start_time);

}


int main(int argc, char **argv) {

    struct task *head = NULL;



    printf("%d\n", argc);

    //initializer
    for(int i =1; i<argc; i++){
        if(strcmp(argv[i], ".") == 0){  //if its is a delimiter continue
            continue;
        }
        cmd_name = argv[i];

        if((strcmp(argv[i+1], ".") == 0)){  //if the cmd has no arguments
            arguments = NULL;
            add_to_list(&head, cmd_name, arguments);
            continue;
        }

        i++;

        while(i<argc && (strcmp(argv[i], ".") != 0)){
            arguments = argv[i];
            add_to_list(&head, cmd_name, arguments);
            i++;
        }
    }
    //initializer




    //printf("head: %s\n", head->name);
    struct task *current = head;
    buf = malloc(1024*(sizeof(char)));
    strlcat(buf, "/bin/", sizeof(buf));
    char *current_name = current->name;
    char *current_arg = current->argument;

    strlcat(buf, current_name, sizeof(buf));
    printf("buf size%lu", 1024*sizeof(buf));

    pid_t pid = fork();



  if(pid == 0){
      *current->pid = pid;
      printf("pid: %d: %d:, path: %s\n", pid, (int)*current->pid, buf);
      execute(current, buf, pid);
  }


    int c = 0;
    /*
    while(c<=task_no){
        current_name = current->name;
        current_arg = current->argument;
        //printf("execution cmd: %s, argument: %s", current->name, current->argument);
        pid = fork();

        if(pid ==0 ){
            execute(current, buf, pid);
            break;
        }
        current = current->next;
    }
     */

    //wait(&pid);


    wait(NULL);


    while(current!= NULL){
        struct task *next = current->next;
        free(current);
        current = next;

    }

    return 0;
}