
/***

To Do: Fix Words Distribution
 ---> Use a Layered Distribution Model
 ----> ...

***/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int mightofthelord = 133997; //the length of the wordlist in total lines - 1 (zero inclusive)
fpos_t inthebeginning; //when initialized (see main) the beginning of the wordlist filestream

int zipfish (void){
    int ret = 1; //initialize ret to 1
    int num = rand (); //initialize num to an arbitrary positive integer
    for (int mod = 1; mod < mightofthelord; mod++) //iterator is 1, while iterator is less than the length of the filestream
        if ((num % mod) == 0) //check if the random integer is divisible by the iterator
		      ret = mightofthelord/mod; //if so, set ret equal to the floor of the length of the filestream divided by the iterator
    ret = rand () % (ret+1); //done iterating: set ret equal to the modulo of an arbitrary positive integer
                //and the previous value of ret + 1
    return ret; //return the integer ret
}

int print_word (int given_id, FILE * wordslist) {
    fsetpos(wordslist, &inthebeginning); //return to the beginning of the filestream
    char ret_char = ' '; //initialize the return character to a horizontal space
    for (int i = given_id; ; i--){ //iterate for the parameter given, fetch from that line of the filestream
        if (i == 0){ //if parameter is 0, or iterations have made iterator 0
            while (ret_char != '\n'){ //until newline is reached
                ret_char = getc(wordslist); //set ret_char equal to the next character in the wordlist
                if (ret_char != '\n') //unless newline is reached
                    printf("%c", ret_char); //print ret_char
            }
            return 0; //terminate
        }
        else { //otherwise, read characters until a newline is reached (and decrement the iterator, repeating)
            while (getc(wordslist) != '\n');
        }
    }
}

void punctuate (void){ //ten different punctuation marks to use enumerated 0 to 9
    int whichpunk = rand() % 10; //randomly, 0 to 9
    switch (whichpunk) { //print the puntuation mark determined by whichpunk
        case 0:
            printf(".");
            break;
        case 1:
            printf(",");
            break;
        case 2:
            printf(";");
            break;
        case 3:
            printf(":");
            break;
        case 4:
            printf("?");
            break;
        case 5:
            printf("!");
            break;
        case 6:
            printf("(");
            break;
        case 7:
            printf(")");
            break;
        case 8:
            printf("'");
            break;
        case 9:
            printf("\"");
            break;
    }
}

int main (void) {
    unsigned int seedsoflife = time(NULL); //initial random seed uses current time
    srand(seedsoflife); //seed with current time
    FILE * wl = fopen ("angel_metatron.txt","r"); //open wordlist for reading
    fgetpos (wl, &inthebeginning); //set beginning of stream to position inthebeginning
    int previousword = zipfish(); //initialize previousword with arbitrary int
    int currentword = previousword; //initialize currentword with previousword
    int num_words;
    scanf("%d", &num_words); //number of iterations to the following for loop
    for (int i = 0; i < num_words; i++){ //iterate for a number of words (783137 words in the bible)
        if( i % ( 500 + ((rand() % 55) - (rand()%24) )) == 0 ) { //if iteration is divisible by any 446 to 554
    //or this is the first iteration, then print a newline and a tab
            printf("\n\t");
        }
        while(previousword == currentword) //while the previousword and the currentword are equal
            currentword = zipfish(); //reset currentword
        print_word(currentword,wl); //print currentword
        previousword = currentword; //set previousword to currentword
        if( i % ((rand() % 8) + 7) == 0 ) //if the iteration is divisible by any 7 to 15, then punctuate
            punctuate();
        printf(" "); //print a horizontal space
        seedsoflife++; //increment seeds of life
        srand(seedsoflife); //reseed random engine
    }
    fclose(wl);//iterations over, close wordlist
    return 0; //terminate
}
