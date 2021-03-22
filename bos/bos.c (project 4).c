#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <memory.h>

const int INIT_SIZE = 64 * 1024;

#pragma pack(1)
struct bos_hdr {
    int magic; // must be set to 0xb055;
    union {
        char padding[16];
    } u;
};

struct bos_entry {
    int allocated:1; // will be non-zero if allocated
    int size; // includes the size of bos_entry
    union {
        char padding[8];
    } u;
};

//struct bos_entry *free = NULL;
//struct bos_entry free_first = NULL;

#pragma pack()

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("USAGE: %s bos_filename\n", argv[0]);
        exit(2);
    }
    int fd = open(argv[1], O_CREAT | O_RDWR, 0777);
    if (fd == -1) {
        perror(argv[1]);
        exit(3);
    }

    void *base = mmap(NULL, 1024*1024, PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0);
    void *end;
    struct bos_hdr *hdr = base;
    struct bos_entry *first_entry = (struct bos_entry *)(hdr+1);

    struct stat stat;
    if (fstat(fd, &stat) == -1) {
        perror("fstat");
        exit(4);
    }
    if (stat.st_size == 0) {
        ftruncate(fd, INIT_SIZE);
        memset(hdr, 0, sizeof *hdr);
        hdr->magic = 0xb055;
        memset(first_entry, 0, sizeof *first_entry);
        first_entry->size = INIT_SIZE - sizeof *hdr;
        end = (char*)base + INIT_SIZE;
    } else {
        end = (char*)base + stat.st_size;
    }

    size_t n;
    char *line = NULL;
    while (getline(&line, &n, stdin) > 0) {
        // remove the newline
        size_t endi = strlen(line) - 1;
        if (line[endi] == '\n') {
            line[endi] = '\0';
        }
        switch(line[0]) {
            // need to add 'd'
            case 'l': {
                struct bos_entry *entry = first_entry;
                while ((void*)entry < end) {
                    if (entry->allocated) {
                        printf("%s\n", (char*)&entry[1]);
                    }
                    entry = (struct bos_entry *) ((char *) entry + entry->size);
                }
            }
                break; // break from the switch statement
            case 'a': {
                // we should check for duplicates first!
                int isAllocated =0;       // 1->duplicate and 0->Not duplicate
                char *str = &line[2];
                struct bos_entry *entry = first_entry;
                //check for duplicates
                while ((void*)entry < end) {
                    if (strcmp((char*)&entry[1], str)==0) {             // only allocated entries
                        printf("duplicate string could not be added");
                        isAllocated = 1;
                        break;
                    }
                    entry = (struct bos_entry *) ((char *) entry + entry->size);
                }
                entry = first_entry;

                if (isAllocated == 0){
                    while ((void*)entry < end) {
                        if (!entry->allocated) {
                            // split it (note this should be fixed so that it can grow if needed
                            int needed_size = sizeof(*entry) + strlen(str) + 1;
                            int left_over = entry->size - needed_size;
                            if (left_over < sizeof(*entry)) {
                                // if we don't have enough left over for an entry struct, we just
                                // use it here and it will be internal fragmentation
                                needed_size = entry->size;
                                left_over = 0;
                            }
                            if (entry->size < needed_size) {
                                printf("hmmm, you need to grow!!!\n");
                                exit(6);
                            }
                            entry->size = needed_size;
                            entry->allocated = 1;
                            strcpy((char *)&entry[1], str);
                            if (left_over > 0) {
                                entry = (struct bos_entry *) ((char *) entry + entry->size);
                                memset(entry, 0, sizeof *entry);
                                entry->size = left_over;
                            }
                            break;
                        }
                        entry = (struct bos_entry *) ((char *) entry + entry->size);
                    }

                }

            }
                break; // break from the switch statement

                //delete
            case 'd':{
                int isDeleted =0;       // 1->deleted and 0->Not deleted
                char *str = &line[2];
                struct bos_entry *entry = first_entry;

                //check for duplicates
                while ((void*)entry < end) {
                    if (strcmp((char*)&entry[1], str)==0) { // only allocated entries
                        printf("value found");
                        entry->allocated = 0;
                        struct bos_entry *next = (entry +1);
                        struct bos_entry *prev = (entry -1);

                        if(next->allocated == 0 && next!=NULL){
                            entry->size = entry->size + next->size;
                        }

                        if(prev->allocated == 0 && prev!=NULL){
                            prev->size = prev->size+entry->size;
                        }
                        printf("prev: %d", prev->size);
                        printf("entry: %d", entry->size);
                        printf("next: %d", next->size);

                        isDeleted = 1;
                        break;
                    }

                    entry = (struct bos_entry *) ((char *) entry + entry->size);
                }
                entry = first_entry;
            }
                break;  // break from switch
        }


        free(line);
        n = 0;
        line = 0;
    }
    return 0;
}
