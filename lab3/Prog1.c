#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#define p_n (sizeof(p_sizes)/sizeof(int))

void *mem = 0;
size_t mem_size = 100;
int multiplier = 1024;


//Variable Size Partitioning

struct Partition {
    int size;
    bool occupied;
    struct Partition *next;
};
int allocateated = 0;

void initPartition(struct Partition *part, int size, struct Partition *next) {
    part->size = size;
    part->occupied = false;
    part->next = next;
}

struct Partition *head;

struct Partition *occupyPartial(struct Partition *part, int size) {
    struct Partition *new = (struct Partition *) malloc(sizeof(struct Partition));
    if (new == NULL)
        return NULL;
    initPartition(new, part->size - size, part->next);
    part->size = size;
    part->occupied = true;
    part->next = new;
    return new;
}

void *firstFit(int size) {
    int offset = 0;
    struct Partition *part = head;
    while (part != NULL) {
        if (part->occupied == false) {
            if (part->size > size) {
                occupyPartial(part, size);
                allocateated += size;
                return mem + offset;
            }
            if (part->size == size) {
                part->occupied = true;
                allocateated += size;
                return mem + offset;
            }
        }
        offset += part->size;
        part = part->next;
    }
    return NULL;
}

void *bestFit(int size) {
    int offset = 0;
    struct Partition *part = head, *best_part = NULL;
    int min_diff = INT_MAX, best_offset = 0;
    while (part != NULL) {
        if (part->occupied == false) {
            if (part->size == size) {
                part->occupied = true;
                allocateated += size;
                return mem + offset;
            }
            if (part->size > size && part->size - size < min_diff) {
                best_part = part;
                min_diff = part->size - size;
                best_offset = offset;
            }
        }
        offset += part->size;
        part = part->next;
    }
    if (best_part != NULL) {
        occupyPartial(best_part, size);
        allocateated += size;
        return mem + best_offset;
    }
    return NULL;
}

void *worstFit(int size) {
    int offset = 0;
    struct Partition *part = head, *worst_part = NULL;
    int max_diff = -1, worst_offset = 0;
    while (part != NULL) {
        if (part->occupied == false) {
            if (part->size >= size && part->size - size > max_diff) {
                worst_part = part;
                max_diff = part->size - size;
                worst_offset = offset;
            }
        }
        offset += part->size;
        part = part->next;
    }
    if (worst_part != NULL) {
        if (worst_part->size == size) {
            worst_part->occupied = true;
            allocateated += size;
            return mem + worst_offset;
        } else {
            occupyPartial(worst_part, size);
            allocateated += size;
            return mem + worst_offset;
        }
    }
    return NULL;
}

void *allocate(int size, void *(*fitter)(int)) {
    return fitter(size);
}

bool deallocate(void *ptr) {
    int dest_offset = (int) (ptr - mem), offset = 0;
    struct Partition *part = head, *prevPart = NULL;
    while (part != NULL) {
        if (offset == dest_offset) {
            allocateated -= part->size;
            struct Partition *nextPart = part->next;
            if (prevPart != NULL && prevPart->occupied == false && nextPart != NULL && nextPart->occupied == false) {
                prevPart->size += part->size + nextPart->size;
                prevPart->next = nextPart->next;
                free(part);
                free(nextPart);
                return true;
            }
            if (prevPart != NULL && prevPart->occupied == false) {
                prevPart->size += part->size;
                prevPart->next = nextPart;
                free(part);
                return true;
            }
            if (nextPart != NULL && nextPart->occupied == false) {
                part->size += nextPart->size;
                part->next = nextPart->next;
                part->occupied = false;
                free(nextPart);
                return true;
            }
            part->occupied = false;
            return true;
        }
        offset += part->size;
        prevPart = part;
        part = part->next;
    }
    return false;
}
void deleteNext(struct Partition * prevPart){
  struct Partition* part = prevPart->next;
  if(part==NULL)
    return;
  prevPart->next=part->next;
  free(part);
}
void defragment(){
  if (head == NULL)
    return;
  struct Partition *part = head->next, *prevPart= head;
  struct Partition *freePart = head->occupied ? (struct Partition *) malloc(sizeof(struct Partition)) : head;
  if(head->occupied)
    initPartition(freePart, 0, NULL);
  while (part != NULL) {
      if (!part->occupied){
        freePart->size += part->size;
        deleteNext(prevPart);
        part= prevPart;
      }
      prevPart = part;
      part = part->next;
  }
  if(freePart->size > 0 && head->occupied){
    freePart->next = head;
    head = freePart;
  }
  if(freePart->size ==0 )
    free(freePart);
}

void printPart() {
    struct Partition *part = head;
    while (part != NULL) {
        printf("| %d/%d ", part->occupied ? part->size : 0, part->size);
        part = part->next;
    }
    printf("|\n");
}

int testVariablePart() {
    head = (struct Partition *) malloc(sizeof(struct Partition));
    initPartition(head, (int) mem_size, NULL);
    int option = 0, size;
    void *loc;
    while (option != 7) {
        printf("\n\n1) First Fit Allocate\n2) Best Fit Allocate\n3) Worst Fit Allocate\n4) Deallocate\n5) Show Partitioning\n6) Defragment\n7) Quit");
        printf("\nEnter option: ");
        scanf("%d", &option);
        printf("\n");
        switch (option) {
            case 1:
            case 2:
            case 3:
                printf("Enter size of process: ");
                scanf("%d", &size);
                loc = allocate(size, option == 1 ? firstFit : option == 2 ? bestFit : worstFit);
              if (loc == NULL)
                    printf("Unable to allocate %s", allocateated < size ? "due to external fragmentation" : "");
                else printf("Allocated %d KiB at %p, offset %d", size, loc, (int) (loc - mem));
                break;
            case 4:
                printf("Enter offset of process: ");
                scanf("%d", &size);
                if (deallocate(mem + size))
                    printf("Deallocated!");
                else
                    printf("Failed!");
                break;
            case 5:
                printPart();
                break;
            case 6:
                defragment();
                break;
            default:
                break;
        }
    }
}

int main() {
    mem = malloc(mem_size * multiplier);
    if (mem == NULL)
        return 1;
    testVariablePart();
    free(mem);
    return 0;
}
