// name: Yao Chong Chow
// email: chow.ya@northeastern.edu

// format of document is a bunch of data lines beginning with an integer (rank which we ignore)
// then a ',' followed by a double-quoted string (city name)
// then a ',' followed by a double-quoted string (population) - ignore commas and covert to int; or (X) - convert to 0
// then a lot of entries that are ignored


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define MAXSTRING 200
#define BUCKET_SIZE 400

// finite state machine states
#define STARTSTATE 0
#define S1 1
#define S2 2
#define S3 3
#define S4 4
#define S5 5
#define S6 6
#define ACCEPTSTATE 10
#define ERRORSTATE 11

struct bucket* hashTable1 = NULL;
struct bucket* hashTable2 = NULL;
struct bucket* hashTable3 = NULL;


// node struct
struct node {
    char city[MAXSTRING];
    int population;
    struct node* next;
};

// bucket struct
struct bucket {
    struct node* head;
    int count; // # of nodes in a bucket
};

// create a new node 
struct node* createNode(const char* city, int population) {
    struct node* newNode = (struct node *)malloc(sizeof(struct node));
    strcpy(newNode->city, city);
    newNode->population = population;
    newNode->next = NULL;

    return newNode;
}

// hash function 1 = length of the city/state string (modulo size of table)
int hashFunction1(const char* city) {
    size_t length = strlen(city);
    return length % BUCKET_SIZE;
}

// hash function 2 = sum of the character codes of the city/state string (modulo size of table)
int hashFunction2(const char* city) {
    int sum = 0;
    for (int i = 0; city[i] != '\0'; i++) {
        sum += city[i];
    }
    return sum % BUCKET_SIZE;
}

// product of the first 2 character codes in city/state string (modulo size of table)
int hashFunction3(const char* city) {
    int len = strlen(city);
    if (len < 2) {
        return city[0] % BUCKET_SIZE;
    }
    return (city[0] * city[1]) % BUCKET_SIZE;
}

void add(struct bucket* hashTable, int (*hashFunction)(const char*), const char* city, int population) {
    int hashIndex = hashFunction(city); 

    struct node* newNode = createNode(city, population);
    // when node is empty
    if (hashTable[hashIndex].count == 0) {
        hashTable[hashIndex].count = 1;
        hashTable[hashIndex].head = newNode; 
    }
    // when node has a key
    else {
        newNode->next = hashTable[hashIndex].head;
        hashTable[hashIndex].head = newNode;
        hashTable[hashIndex].count++;
    }
}

void display(struct bucket* hashTable) {
    struct node* iterator;
    for (int i = 0; i < BUCKET_SIZE; i++) {
        iterator = hashTable[i].head;
         
            printf("Table[%d]:\n", i);
            while (iterator != NULL) {
                printf("key/value: [%s] / [%d]\n", iterator->city, iterator->population);
                iterator = iterator->next;
            }
        
    }
}





// check if a character c is a digit
bool isDigit(char c) {
  if ('0' <= c && c <= '9') {
    return true;
  } else {
    return false;
  }
}

// append character c to string s
void appendChar(char* s, char c) {
  char charToStr[2];           // convert char to string
    charToStr[0] = c;
    charToStr[1] = '\0';          // put NUL to terminate string of one character
    strcat(s, charToStr);
}




int main () {

  char inputLine[MAXSTRING];   // temporary string to hold input line
  char cityStr[MAXSTRING];     // city name
  int  lineNum;                // line number (city rank)
  int  popInt;                 // population
  int  state;                  // FSM state
  int  nextChar;               // index of next character in input string
  char temp[MAXSTRING];        // temp string to build up extracted strings from input characters
  
 
  FILE* fp;
  fp = fopen("pop.csv","r");

    hashTable1 = (struct bucket*)malloc(BUCKET_SIZE * sizeof(struct bucket));
    hashTable2 = (struct bucket*)malloc(BUCKET_SIZE * sizeof(struct bucket));
    hashTable3 = (struct bucket*)malloc(BUCKET_SIZE * sizeof(struct bucket));

    for (int i = 0; i < BUCKET_SIZE; i++) {
        hashTable1[i].head = NULL;
        hashTable1[i].count = 0;
        hashTable2[i].head = NULL;
        hashTable2[i].count = 0;
        hashTable3[i].head = NULL;
        hashTable3[i].count = 0;
    }

  if (fp != NULL) {
    fgets(inputLine, MAXSTRING, fp); // prime the pump for the first line

    // ***** BEGIN FINTITE STATE MACHINE *****
    
    // STARTSTATE: digit -> S1
    // S1: digit -> S1; , -> S2
    // S2: " -> S3
    // S3: !" -> S3; " -> S4
    // S4: , -> S5
    // S5: " -> S6; ( -> ACCEPTSTATE
    // S6: digit -> S6; , -> S6; " -> ACCEPTSTATE; 
    // ACCEPTSTATE: done!
    // else go to ERRORSTATE
    //
    while (feof(fp) == 0){

      nextChar = 0;
      state = STARTSTATE; 
      strcpy(temp,"");       // temp = ""

      if (nextChar >= strlen(inputLine)){
	// if no input string then go to ERRORSTATE
	state = ERRORSTATE;
      } 

      while ((state != ERRORSTATE) && (state != ACCEPTSTATE)) {
	  
      switch (state) {
        case STARTSTATE:
          // look a digit to confirm a valid line
          if (isDigit(inputLine[nextChar])) {
            state = S1;
            appendChar(temp, inputLine[nextChar]);
          } else {
            state = ERRORSTATE;
          }  
          break;


	  // ADD YOUR CODE HERE
        case S1:
          if (isDigit(inputLine[nextChar])) {
            appendChar(temp, inputLine[nextChar]);
            } 
            else if (inputLine[nextChar] == ',') {
              state = S2;
              strcpy(temp, "");
            } 
            else {
              state = ERRORSTATE;
            }
        break;

        case S2:
          if (inputLine[nextChar] == '"') {
            state = S3;
          } 
          else {
            state = ERRORSTATE;
          }
        break;

        case S3:
          if (inputLine[nextChar] == '"') {
            strcpy(cityStr, temp);
            state = S4;
            strcpy(temp, "");
          } 
          else {
            appendChar(temp, inputLine[nextChar]);
          }
        break;

        case S4:
          if (inputLine[nextChar] == ',') {
            state = S5;
          } 
          else {
            state = ERRORSTATE;
          }
          break;

        case S5:
          if (inputLine[nextChar] == '"') {
            state = S6;
          } 
          else if (inputLine[nextChar] == '(') {
            popInt=0;
            state = ACCEPTSTATE;
            } 
          else {
            state = ERRORSTATE;
          }
          break;

        case S6:
          if (isDigit(inputLine[nextChar])) {
              appendChar(temp, inputLine[nextChar]);
          } else if (inputLine[nextChar] == ',') {
              state = S6;
          } else if (inputLine[nextChar] == '"') {
              popInt = atoi(temp);//atoi change string to int
              state = ACCEPTSTATE;
          } else {
              state = ERRORSTATE;
          }
          break;
            //
 
	  case ACCEPTSTATE:
	    // nothing to do - we are done!
	    break;
	    
	  default:
	    state = ERRORSTATE;
	    break;
	} // end switch

	// advance input
	nextChar++;
	
      }	// end while state machine loop

      // ***** END FINITE STATE MACHINE *****
	  

      if (state == ACCEPTSTATE) {
                add(hashTable1, hashFunction1, cityStr, popInt);
                add(hashTable2, hashFunction2, cityStr, popInt);
                add(hashTable3, hashFunction3, cityStr, popInt);
            }

            // get next line
            fgets(inputLine, MAXSTRING, fp);
        } // end while file input loop

    

    fclose(fp);
    
    printf("Hash Table 1:\n");
    display(hashTable1);
        
    printf("\nHash Table 2:\n");
    display(hashTable2);
    
    printf("\nHash Table 3:\n");
    display(hashTable3);



    // Free the allocated memory
    for (int i = 0; i < BUCKET_SIZE; i++) {
        struct node* iterator1 = hashTable1[i].head;
        while (iterator1 != NULL) {
            struct node* temp = iterator1;
            iterator1 = iterator1->next;
            free(temp);
            }

        struct node* iterator2 = hashTable2[i].head;
        while (iterator2 != NULL) {
            struct node* temp = iterator2;
            iterator2 = iterator2->next;
            free(temp);
            }

        struct node* iterator3 = hashTable3[i].head;
        while (iterator3 != NULL) {
            struct node* temp = iterator3;
            iterator3 = iterator3->next;
            free(temp);
            }
    }
    
    free(hashTable1);
    free(hashTable2);
    free(hashTable3);

    } else {
        printf("File not found!\n");
    }

  
  return 0;
}
