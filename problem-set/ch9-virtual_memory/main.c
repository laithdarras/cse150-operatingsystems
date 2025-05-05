/*
Write a program that implements the FIFO and LRU page-replacement algorithms presented in this chapter. First, generate a random page-reference string where page numbers
range from 0 to 9. Apply the page-reference string to each algorithm, and record the number of page faults incurred by each algorithm. Implement the replacement algorithms so that
the number of page frames can vary from 1 to 7. Assume that demand paging is used.
*/

/*
Plan
1. Generate a random page reference string
2. Create FIFO and LRU functions that take the reference string and number of frames
3. Run both algos for each frame size 1-7
4. Print total page faults for both algos
*/

#include <stdio.h>
#include <stdbool.h>
#include <time.h>


void generateRefString(int refStr[], int len) {
    for (int i = 0; i < len; i++) {
        refStr[i] = rand() % 10; // pages range from 0-9
    }
}

// helper function to check if a page is already in one of the frames
bool helper(int frames[], int page, int size) {
    for (int i = 0; i < size; i++) {
        if (frames[i] == page) {
            return true;    // hit
        }
    }

    return false;   // fault
}

int fifo(int refStr[], int refLen, int count) {
    int frames[count];
    int next = 0;
    int total = 0;

    for (int i = 0; i < count; i++) {
        frames[i] = -1;     // base case: initialize all frames as empty
    }

    for (int i = 0; i < refLen; i++) {
        int page = refStr[i];   // current page request

        // if page is not in main memory (page fault)
        if (!helper(frames, page, count)) {
            frames[next] = page;
            next = (next + 1) % count;
            total++;
        }
    }

    return total;
}


int lru(int refStr[], int refLen, int count) {
    int frames[count];
    int lastUsed[count];
    int total = 0;
    int time;

    for (int i = 0; i < count; i++) {
        frames[i] = -1;
        lastUsed[i] = -1;
    }

    for (int i = 0; i < refLen; i++) {
        int page = refStr[i];
        bool pageHit = false;

        // check if page is already in frame
        for (int j = 0; j < count; j++) {
            if (frames[j] == page) {
                lastUsed[j] = time++;
                pageHit = true;
            }
        }
        // page fault -> find lru
        if (!pageHit) {
            int index = 0;
            for (int j = 1; j < count; j++) {
                if (lastUsed[j] < lastUsed[index]) {
                    index = j;
                }
            }
            frames[index] = page;
            lastUsed[index] = time++;
            total++;
        }
    }

    return total;
}


int optimal(int refStr[], int refLen, int count) {
    int frames[count];
    int total = 0;

    for (int i = 0; i < count; i++) {
        frames[i] = -1;
    }

    for (int i = 0; i < refLen; i++) {
        int page = refStr[i];
        bool hit = false;

        // check if page already exists
        for (int j = 0; j < count; j++) {
            if (frames[j] == page) {
                hit = true;
            }
        }

        // no fault if page already in memory
        if (hit) {
            continue;
        }

        total++;    // page fault

        // use free frame if available
        bool placed = false;
        for (int j = 0; j < count; j++) {
            if (frames[j] == -1) {
                frames[j] = page;
                placed = true;
            }
        }

        if (placed) {
            continue;
        }

        // evict page using optimal strategy
        int farthest = -1, indexToReplace = -1;
        
        for (int j = 0; j < count; j++) {
            int next = -1;

            // find next use of frames[j]
            for (int k = i + 1; k < refLen; k++) {
                if (refStr[k] == frames[j]) {
                    next = k;
                }
            }

            // if not used again, EVICT IT!
            if (next == -1) {
                indexToReplace = j;
                break;
            }

            // track farthest future use
            if (next > farthest) {
                farthest = next;
                indexToReplace = j;
            }
        }

        frames[indexToReplace] = page;      // replace page
    }

    return total;
}



int main() {
    srand(time(NULL));
    int refStr[15];     // reference string length (15 page requests)
    generateRefString(refStr, 15);

    printf("Page Reference String: ");
    for (int i = 0; i < 15; i++) {
        printf("%d ", refStr[i]);
    }

    printf("\n");
    printf("--------------FIFO--------------\n");

    // run fifo with 1-7 frames and print total page faults for each
    printf("Total Page Faults: ");
    printf("\n");
    for (int frames = 1; frames <= 7; frames++) {
        int fifoFaults = fifo(refStr, 15, frames);
        printf("Frames %d -> Total Page Faults: %d\n", frames, fifoFaults);
    }
    printf("----------------LRU------------------\n");

    // run lru with 1-7 frames and print total page faults for each
    printf("Total Page Faults: ");
    printf("\n");
    for (int frames = 1; frames <= 7; frames++) {
        int lruFaults = lru(refStr, 15, frames);
        printf("Frames %d -> Total Page Faults: %d\n", frames, lruFaults);
    }
    printf("----------------OPTIMAL (MIN)------------------\n");

    // run optimal with 1-7 frames and print total page faults for each
    printf("Total Page Faults: ");
    printf("\n");
    for (int frames = 1; frames <= 7; frames++) {
        int optimalFaults = optimal(refStr, 15, frames);
        printf("Frames %d -> Total Page Faults: %d\n", frames, optimalFaults);
    }

    return 0;
}