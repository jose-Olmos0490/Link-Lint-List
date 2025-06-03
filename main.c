#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

typedef struct WordNode_struct { //head
    char* myWord;
    struct WordNode_struct* next; 
} WordNode;

typedef struct LadderNode_struct {
    WordNode* topWord;
    struct LadderNode_struct* next; 
} LadderNode;

int countWordsOfLength(char* filename, int wordSize) { 
    // TODO - write countWordsOfLength()
    // Open a file with name filename and count the number of words
    // in the file that are exactly wordSize letters long, where a 
    // "word" is ANY set of characters that falls between two whitespaces 
    // (or tabs, or newlines, etc.). Return the count if filename is valid.
    // Return -1 if the file cannot be opened

    int numOfWords = 0; //counter
    char name [100]; //stores words from the file
    FILE* file = fopen(filename,"r"); // opening the file to read only

    if (file == NULL) // cheacks if the file is empty
    {
        return -1;
    }
    while (fscanf(file, "%s", name) == 1){ // loop that reads the words untill the next whitespace
        if (strlen(name) == wordSize){ //counts the number of charactors in name
            numOfWords++;//^and if the number is the same as wordSize then increments numOfWords
        }
        
    }
    fclose(file);
    return numOfWords;
}

bool buildWordArray(char* filename, char** words, int numWords, int wordSize) { 
    // TODO - write buildWordArray()    
    // Open a file with name filename and fill the pre-allocated word
    // array words with only words that are exactly wordSize letters long (put in malloc?). 
    // The file should contain exactly numWords words that are the correct
    // number of letters. Thus, words is pre-allocated as numWords char pointers,
    // i.e. char*'s, each pointing to a C-string of length wordSize>+1. 
    // Return true iff the file is opened successfully AND the file contains exactly
    // numWords words of exactly wordSize letters, and those words are stored in the
    // words array; otherwise, return false.
    FILE* file = fopen(filename,"r"); // opens the file
    if (file == NULL){ // if empty then it will return it
        return false;
    }
    int wordCount = 0;
    char name[100];//this is a place for the words in the file

    while (fscanf(file, "%s",name) == 1){ //it will go through the file
        if (strlen(name) == wordSize){ //if the word is the same length as the input
            if (wordCount >= numWords){
                for (int i = 0; i < wordCount; i++) {
                    free(words[i]);
                }
                fclose(file);
                return false;
            }

            words[wordCount] = (char*) malloc((wordSize + 1) * sizeof(char)); 
            if (!words[wordCount]){
                for (int i = 0; i < wordCount; i++){
                    free(words[i]);
                }
                fclose(file);
                return false;
            }
            strcpy(words[wordCount],name);
            wordCount++;
            //fclose(file);
            //return false;
        }
    }
    fclose(file);
    if (wordCount == numWords){
        return true;
    }
    return false;
}

int findWord(char** words, char* aWord, int loInd, int hiInd) { 
    // TODO - write findWord()
    // Binary search for string aWord in an alphabetically sorted
    // array of strings words, only between the indices of loInd
    // and hiInd. Return the index of aWord if found; otherwise
    // return -1 (if not found between loInd and hiInd).

    while (loInd <= hiInd) {
        int midInd = loInd + (hiInd - loInd) / 2;
        int compare = strcmp(words[midInd], aWord);
        if (compare==0){
            return midInd;
        } else if (compare < 0) {
            loInd = midInd + 1; 
        } else {
            hiInd = midInd - 1;
        }
    }
    return -1;
}

void freeWords(char** words, int numWords) {
    // TODO - write freeWords()
    // Free up all heap-allocated space for words,
    // which is an array of numWords C-strings: first,
    // free the space allocated for each C-string; then,
    // free the space allocated for the array of pointers, i.e. words, itself.
    if (words == NULL) {
            return;
        }
    for (int i = 0; i<numWords; i++) {
        if(words[i]!=NULL){
            free(words[i]);
        }
    }
    free(words);
}

void insertWordAtFront(WordNode** ladder, char* newWord) {
    // TODO - write insertWordAtFront()
    // Allocate space for a new WordNode, set its myWord subitem
    // using newWord and insert it to the front of ladder, which
    // is a pointer-passed-by-pointer since the head node of the 
    // ladder changes inside this function;  newWord is a pointer 
    // to a C-string from the full words array, which is already heap-allocated.

WordNode* newNode = (WordNode*) malloc(sizeof(WordNode));
if (newNode==NULL){
    return;
}
    newNode->myWord= newWord;
    newNode->next =*ladder;
    *ladder = newNode;

}

int getLadderHeight(WordNode* ladder) {
    // TODO - write getLadderHeight()
    //Find and return the number of words in the ladder list.
    int counter = 0;
    WordNode* current = ladder;
    while(current != NULL){
        counter++;
        current = current->next;
    }
    return counter; // modify this line
}

WordNode* copyLadder(WordNode* ladder) {
    // TODO - write copyLadder()
    // Make a "complete copy" of ladder and
    // return it. The copied ladder must have
    // new space allocated for each WordNode in
    // ladder, BUT the C-string pointers to elements
    // of the full word array can be reused; i.e. the
    // actual words do NOT need another allocation here.

    if(ladder == NULL){
        return NULL;
    }

    WordNode* newNode = (WordNode*)malloc(sizeof(WordNode));

    if (newNode== NULL){
        return NULL;
    }

    // WordNode* head = ladder;
    // WordNode* current = ladder;
    newNode ->myWord = ladder -> myWord;
    newNode->next = copyLadder(ladder -> next);
    return newNode; //modify this
}

void freeLadder(WordNode* ladder) {
    //---------------------------------------------------------
    // TODO - write freeLadder()
    //---------------------------------------------------------
WordNode* current = ladder;
while (current != NULL) {
    WordNode* next = current -> next;
    free(current);
    current = next;
    }
}

void insertLadderAtBack(LadderNode** list, WordNode* newLadder) {
    //---------------------------------------------------------
    //Allocate space for a new LadderNode and set its topWord subitem using newLadder.
    //Then, find the back of list and append the newly created LadderNode to the back. 
    //Note that list is a pointer-passed-by-pointer, since this function must handle the
    //edge case where list is empty and the new LadderNode becomes the head node.
    //---------------------------------------------------------
    LadderNode* newNode=malloc(sizeof(LadderNode));
    newNode->topWord = newLadder;
    newNode->next = NULL;
    LadderNode* current = *list;

    if(newNode == NULL) return;

    if (*list == NULL){
        *list=newNode;
        return;
    }

    while(current-> next != NULL){
        current = current->next;
    }

    current -> next = newNode; // next node in current is the newNode


}

WordNode* popLadderFromFront(LadderNode** list) {
    //---------------------------------------------------------
    //Pop the first ladder from the front of the list by returning 
    //the pointer to the head node of the ladder that is the subitem 
    //of the head node of list AND updating the head node of list to
    //the next LadderNode. Note that list is a pointer-passed-by-pointer,
    //since this function updates the head node to be one down the list.
    //The LadderNode popped off the front must have its memory freed in
    //this function, since it will go out of scope, but the ladder itself,
    //i.e. the head WordNode, should NOT be freed. 
    //---------------------------------------------------------

    if (*list == NULL) {
        return NULL;
    }

    LadderNode* firstLadder = *list;
    WordNode* ladder = firstLadder -> topWord;
    *list = firstLadder->next;

    free(firstLadder);

    return ladder;
}

void freeLadderList(LadderNode* myList) {
    //---------------------------------------------------------
    //Free up all heap-allocated space for myList. For each ladder
    //in myList, first free the space allocated for each WordNode 
    //in the ladder using freeLadder(), then, free the space allocated
    //for the LadderNode itself.
    //---------------------------------------------------------
    LadderNode* nextLadder = myList;
    while(myList != NULL){
        nextLadder = myList ->next;
        freeLadder(myList->topWord);
        free(myList);
        myList = nextLadder;
    }
}

WordNode* findShortestWordLadder(   char** words, 
                                    bool* usedWord, 
                                    int numWords, 
                                    int wordSize, 
                                    char* startWord, 
                                    char* finalWord ) {
    //---------------------------------------------------------
    //Implement the algorithm to find the shortest word ladder 
    //from startWord to finalWord in the words word array, with 
    //numWords total words where each word is wordSize long. 
    //Also, usedWord has size numWords, such that usedWord[i] 
    //is only true if words[i] has previously be entered into 
    //a ladder, and should therefore not be added to any other 
    //ladders. The algorithm creates partial word ladders, which 
    //are WordNode linked lists, and stores them in a LadderNode 
    //linked list. Return NULL if no ladder is possible; otherwise, 
    //return a pointer to the shortest ladder. Make sure to free all 
    //heap-allocated memory that is created in this function that is 
    //not used for the returned ladder before returning from this function.
    //---------------------------------------------------------
    
    bool *localCopy = (bool*)malloc(numWords * sizeof(bool)); //makes a local copy of the usedWord
    if(localCopy == NULL){
        return NULL;
    }

    for (int i =0; i<numWords; i++) { // copyies usedWord into localcopy
        localCopy[i] = usedWord[i];
    }

    LadderNode* myList = NULL; //makes an emptylist(myList)
    WordNode* startLadder = NULL;
    insertWordAtFront(&startLadder,startWord);

    int startIndex = findWord(words,startWord,0,numWords - 1);
    if (startIndex >= 0) {
        localCopy[startIndex] = true;
    }

    insertLadderAtBack(&myList, startLadder);
    WordNode* shortLadder = NULL;
    while(myList != NULL) {
        WordNode* nowLadder = popLadderFromFront(&myList);
        char* nowWord = nowLadder -> myWord;

        for (int i = 0; i <numWords; i++) { //check each word in dict
            if(localCopy[i]) //skip words that have been used
            continue;
            int diffCount = 0; //checks if its a neighbor
            for (int j = 0; j < wordSize; j++) {
                if (nowWord[j] != words[i][j]){
                    diffCount++;
                    if (diffCount > 1)
                    break; //not a neighbor
                    }
                }
            if (diffCount == 1){//neighbor words
                if (strcmp(words[i], finalWord) == 0){ //if neighbor is final then found ladder
                    insertWordAtFront(&nowLadder,finalWord); //make the final ladder and add last word
                    WordNode* temp = nowLadder;
                    while (temp != NULL){
                        int index = findWord(words, temp->myWord, 0, numWords - 1);
                        if(index >= 0){
                            usedWord[index] = true;
                        }
                        temp = temp ->next;
                    }
                    shortLadder = nowLadder;
                    break;
                }else{
                    WordNode* newLadder = copyLadder(nowLadder);
                    if(newLadder == NULL){
                    freeLadder(nowLadder);
                    freeLadderList(myList);
                    free(localCopy);
                    return NULL;
                    }
                    insertWordAtFront(&newLadder, words[i]);
                    localCopy[i] = true;
                    insertLadderAtBack(&myList, newLadder);
                }
            
            }
        }
        if(shortLadder!=NULL){
            freeLadderList(myList);
            free(localCopy);
            return shortLadder;
        }
        freeLadder(nowLadder);

    }
    free(localCopy);
    return NULL;
}

// interactive user-input to set a word; 
//  ensures the word is in the dictionary word array
void setWord(char** words, int numWords, int wordSize, char* aWord) {
    bool valid = false;
    printf("  Enter a %d-letter word: ", wordSize);
    int count = 0;
    while (!valid) {
        scanf("%s",aWord);
        count++;
        valid = (strlen(aWord) == wordSize);
        if (valid) {
            int wordInd = findWord(words, aWord, 0, numWords-1);
            if (wordInd < 0) {
                valid = false;
                printf("    Entered word %s is not in the dictionary.\n",aWord);
                printf("  Enter a %d-letter word: ", wordSize); 
            }
        } else {
            printf("    Entered word %s is not a valid %d-letter word.\n",aWord,wordSize);
            printf("  Enter a %d-letter word: ", wordSize);
        }
        if (!valid && count >= 5) { //too many tries, picking random word
            printf("\n");
            printf("  Picking a random word for you...\n");
            strcpy(aWord,words[rand()%numWords]);
            printf("  Your word is: %s\n",aWord);
            valid = true;
        }
    }
}

// helpful debugging function to print a single Ladder
void printLadder(WordNode* ladder) {
    WordNode* currNode = ladder;
    while (currNode != NULL) {
        printf("\t\t\t%s\n",currNode->myWord);
        currNode = currNode->next;
    }
}

// helpful debugging function to print the entire list of Ladders
void printList(LadderNode* list) {
    printf("\n");
    printf("Printing the full list of ladders:\n");
    LadderNode* currList = list;
    while (currList != NULL) {
        printf("  Printing a ladder:\n");
        printLadder(currList->topWord);
        currList = currList->next;
    }
    printf("\n");
}


//-----------------------------------------------------
// The primary application is fully provided in main(); 
//  no changes should be made to main(), except for 
//  testing-related purposes (such as command-line 
//  arguments for "TESTING MODE" to call a test case 
//  master function, or something similar)
//-----------------------------------------------------
int main() {
    srand((int)time(0));
    
    printf("\nWelcome to the CS 211 Word Ladder Generator!\n\n");

    // set word length using interactive user-input
    int wordSize;
    printf("Enter the word size for the ladder: ");
    scanf("%d",&wordSize);
    printf("\n");

    printf("This program will make the shortest possible\n"); 
    printf("word ladder between two %d-letter words.\n\n",wordSize);
    
    // interactive user-input sets the dictionary file;
    //  check that file exists; if not, user enters another file
    //  if file exists, count #words of desired length [wordSize]
    char dict[100];
    printf("Enter filename for dictionary: ");
    scanf("%s", dict);
    printf("\n");
    int numWords = countWordsOfLength(dict,wordSize);
    while (numWords < 0) {
        printf("  Dictionary %s not found...\n",dict);
        printf("Enter filename for dictionary: ");
        scanf("%s", dict);
        printf("\n");
        numWords = countWordsOfLength(dict,wordSize);
    }
    
    // allocate heap memory for the word array; only words with desired length
    char** words = (char**)malloc(numWords*sizeof(char*));
    // for (int i = 0; i < numWords; ++i) {
    //     words[i] = (char*)malloc((wordSize+1)*sizeof(char));
    // }

    // end program if file does not have at least two words of desired length
    if (numWords < 2) {
        printf("  Dictionary %s contains insufficient %d-letter words...\n",dict,wordSize);
        printf("Terminating program...\n");
        return -1;
    }
    
    // [usedWord] bool array has same size as word array [words];
    //  all elements initialized to [false];
    //  later, usedWord[i] will be set to [true] whenever 
    //      words[i] is added to ANY partial word ladder;
    //      before adding words[i] to another word ladder,
    //      check for previous usage with usedWord[i] 
    bool* usedWord = (bool*)malloc(numWords*sizeof(bool));
    for (int i = 0; i < numWords; ++i) {
        usedWord[i] = false;
    }
    
    // build word array (only words with desired length) from dictionary file
    printf("Building array of %d-letter words... ", wordSize); 
    bool status = buildWordArray(dict,words,numWords,wordSize);
    if (!status) {
        printf("  ERROR in building word array.\n");
        printf("  File not found or incorrect number of %d-letter words.\n",wordSize);
        printf("Terminating program...\n");
        return -1;
    }
    printf("Done!\n"); 

    // set the two ends of the word ladder using interactive user-input
    //  make sure start and final words are in the word array, 
    //  have the correct length (implicit by checking word array), AND
    //  that the two words are not the same
    char startWord[30];
    char finalWord[30];
    printf("Setting the start %d-letter word... \n", wordSize);
    setWord(words, numWords, wordSize, startWord);
    printf("\n");
    printf("Setting the final %d-letter word... \n", wordSize);
    setWord(words, numWords, wordSize, finalWord);
    while (strcmp(finalWord,startWord) == 0) {
        printf("  The final word cannot be the same as the start word (%s).\n",startWord);
        printf("Setting the final %d-letter word... \n", wordSize);
        setWord(words, numWords, wordSize, finalWord);
    }
    printf("\n");

    // run the algorithm to find the shortest word ladder
    WordNode* myLadder = findShortestWordLadder(words, usedWord, numWords, wordSize, startWord, finalWord);

    // display word ladder and its height if one was found
    if (myLadder == NULL) {
        printf("There is no possible word ladder from %s to %s\n",startWord,finalWord);    
    } else {
        printf("Shortest Word Ladder found!\n");
        printLadder(myLadder);

    }
    printf("Word Ladder height = %d\n",getLadderHeight(myLadder));
    
    // free the heap-allocated memory for the shortest ladder
    freeLadder(myLadder);
    // free the heap-allocated memory for the words array
    freeWords(words,numWords);
    free(usedWord);
    
    return 0;
}
