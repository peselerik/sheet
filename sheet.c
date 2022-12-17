#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

#define MAX_ROWS 50
#define MAX_COLUMNS 50
#define MAX_CHARS_IN_COLUMN 100

/// @brief Pokud je command neplatny, vyhodi chybovou hlasku
void invalid () {
    fprintf(stderr, "%s", "Invalid command\n");
}

/// @brief Pokud je parametr 1 vetsi nez parametr 2, prohodi je
void my_swap(int *operationParameter1, int *operationParameter2) {
    int temp;

    temp = *operationParameter2;
    *operationParameter2 = *operationParameter1;
    *operationParameter1 = temp;
}

int main(int argc, char* argv[]) {
    char table[MAX_ROWS][MAX_COLUMNS][MAX_CHARS_IN_COLUMN];
    char delimiter, character, *operation;
    int row = argc, column = 0, charInColumn = 0, numberOfColumns = 0, numberOfRows = 0, operationParameter1, operationParameter2;
    row = 0;

    //program se spusti pokud je delimiter indentifikovan symbolem -d
    if((strcmp(argv[1], "-d") == 0)) {

        delimiter = *argv[2];
        operation = argv[3];

        if(((strcmp(operation, "acol")) == 0) || ((strcmp(operation, "arow")) == 0)){

        }else if((strcmp(operation, "drows") == 0) || (strcmp(operation, "move") == 0) || (strcmp(operation, "dcols") == 0) || (strcmp(operation, "swap") == 0) || (strcmp(operation, "copy") == 0)){
            operationParameter1 = atoi(argv[4]);
            operationParameter2 = atoi(argv[5]);
        }else{
            operationParameter1 = atoi(argv[4]);
        }
        
        while (character != EOF) {
            character = getchar();
            
            //pokud je znak delimiter, do pole se zapise \0
            if (character == delimiter) {
                table[row][column][charInColumn] = '\0';
                charInColumn = 0;
                column++;

            }
            else if (character == '\n') {
                if (numberOfColumns == 0) {
                    numberOfColumns = column; 
                }
                
                charInColumn = 0;

                //pokud je znak newline, nastavi se column na 0, aby se mohlo na novem radku zacit nultym sloupcem
                column = 0;
                row++;
                numberOfRows++;
            }
            else {
                /*kdyz zadna z ifovych podminek neni splnena, vypisuje se do pole znak po znaku,
                coz znamena, ze pole je automaticky naformatovano jako pole charu, neni tedy nutno pouzit cset*/
                table[row][column][charInColumn] = character;
                charInColumn++;
            }
        }

        if (strcmp(operation, "arow") == 0) {
            row +=1;

            for (int j = 0; j < numberOfColumns +1; j++) {  //kdyz pouziju v poli numberOfColumns a v kteremkoli prikazu zadam posledni sloupec, nevezme ho to, proto +1
                *table[(row-1)][j] = '\0';
            }
        }

        else if (strcmp(operation, "irow") == 0) {

            if(!((operationParameter1 <= 0) || (operationParameter1 > numberOfRows))) {
                
                //pridame radek, abychom vsechny radky pod zvolenym posunout o jednu pozici niz
                row +=1;
                numberOfRows +=1;

                //program musi jet odspodu; kdyby jel zvrchu, kopiroval by se jeden radek na vsechny nizsi pozice
                for (int i = numberOfRows; i > 0; i--) {
                    for (int j = 0 ; j <= numberOfColumns; j++){
                        if(i >= (operationParameter1 - 1)){
                            strcpy(table[i][j], table[i-1][j]);
                        }
                    }
                }

                //nastavuje hodnotu radku, ktery jsme chteli vlozit, na "\0"
                for (int i = 0; i <= (operationParameter1 - 1); i++) {
                    for (int j = 0 ; j <= numberOfColumns; j++) {
                        if(i == operationParameter1 - 1) {
                            *table[operationParameter1 - 1][j] = '\0';
                        }
                    }
                }
            } else {
                invalid();
            }
        }

        //radek v poli se smaze tak, ze vsechny radky pod nim se posunou o jednu pozici vys
        else if (strcmp(operation, "drow") == 0) {

            if (!((operationParameter1 > numberOfRows) || (operationParameter1 <= 0))){
                for (int i = 0; i < numberOfRows; i++) {
                    for (int j = 0; j <= numberOfColumns; j++) {
                        if(i >= (operationParameter1 - 1)){
                            strcpy(table[i][j], table[i+1][j]);
                        }
                    }
                }

                //radek se smaze, aby na vystupu nebyl posledni radek 2x
                row -=1;
            }else{
                invalid();
            }
        }

        else if (strcmp(operation, "drows") == 0) {

            if (!(((operationParameter1 <= 0) || (operationParameter2 <= 0)) || ((operationParameter1 > numberOfRows) || (operationParameter2 > numberOfRows)))) {
                
                //pokud je op1 > op2, prohodime jejich hodnoty, abychom nemuseli psat celou fuknci 2x
                if (operationParameter1 > operationParameter2) {
                    my_swap(&operationParameter1, &operationParameter2);
                }

                //urcime, kolikrat cely program projede radky a sloupce a pak pouzijeme stejny postup jako u drow
                int repetitions = (operationParameter2 - operationParameter1+1);

                for(int x = 0; x < repetitions; x++){
                    for (int i = 0; i < numberOfRows; i++) {
                        for (int j = 0; j <= numberOfColumns; j++) {
                            if(i >= (operationParameter1 - 1)){
                                strcpy(table[i][j], table[i+1][j]);
                            }
                        }
                    }
                }

                //musime odecist pocet radku rovny rozdilu dvou zadanych parametru
                row = row - repetitions;
            } else {
                invalid();
            }
        }

        else if (strcmp(operation, "acol") == 0) {
            column +=1;
            numberOfColumns +=1;
        }

        else if (strcmp(operation, "icol") == 0) {
            if(!((operationParameter1 <= 0) || (operationParameter1 > numberOfColumns +1))) {
                column +=1;
                numberOfColumns +=1;
                    for (int i = 0; i <= numberOfRows; i++) {

                        //for musi bezet odzadu, jinak se jeden sloupec kopiruje do vsech za nim
                        for (int j = numberOfColumns; j > 0 ; j--) {

                            //stejne jako u irow, sloupce za sloupcem zvolenym musime zkopirovat o jednu pozici doprava
                            if(j > (operationParameter1 - 1)) {
                                strcpy(table[i][j], table[i][j-1]);
                            }
                        }
                    }

                    //prebyvajici sloupec "vynulujeme"
                    for (int i = 0; i < (row); i++) {
                        for (int j = 0 ; j <= (operationParameter1 - 1); j++) {
                            if(j == operationParameter1 - 1) {
                            *table[i][operationParameter1 - 1] = '\0';
                            }
                        }
                    }

            } else {
                invalid();
            }
        }

        //stejny princip jako u drow - sloupce za zvolenym sloupcem zkopirovat o jednu pozici doleva a na konci odecteme jeden sloupec
        else if (strcmp(operation, "dcol") == 0) {
            if (!((operationParameter1 > numberOfColumns +1) || (operationParameter1 <= 0))){
                for (int i = 0; i < row; i++) {
                    for (int j = 0 ; j <= numberOfColumns; j++) {
                        if(j >= (operationParameter1 - 1)) {
                            strcpy(table[i][j], table[i][j+1]);
                        }
                    }
                }
                numberOfColumns -=1;
            }else{
                invalid();
            }
        }

        //opet stejny princip jako u drow
        else if (strcmp(operation, "dcols") == 0) {
            if (!(((operationParameter1 <= 0) || (operationParameter2 <= 0)) || ((operationParameter1 > numberOfColumns +1) || (operationParameter2 > numberOfColumns +1)))) {
                
                if (operationParameter1 > operationParameter2) {
                    my_swap(&operationParameter1, &operationParameter2);
                }

                int repetitions = (operationParameter2 - operationParameter1 + 1);

                for(int x = 0; x < repetitions; x++){
                    for (int i = 0; i < numberOfRows; i++) {
                        for (int j = 0; j < numberOfColumns; j++) {
                            if (j >= operationParameter1 - 1) {
                                strcpy(table[i][j], table[i][j+1]);
                            }
                            
                        }
                    }
                }
                numberOfColumns = numberOfColumns - repetitions;
            } else {
                invalid();
            }
        }

        //neni treba nic delat, jelikoz soubor ukladame jako array of chars
        else if (strcmp(operation, "cset") == 0) {
            fprintf(stderr, "%s", "This column is already in string format\n");
        }

        else if (strcmp(operation, "tolower") == 0) {
            if (!((operationParameter1 > numberOfColumns +1) || (operationParameter1 <= 0))){
                for (int i = 0; i <= (row); i++) {
                    for (int j = 0 ; j <= (operationParameter1 - 1); j++) {
                        for(int k = 0; k <= MAX_CHARS_IN_COLUMN; k++) {
                            if(j == operationParameter1 - 1) {
                                //char po charu ve zvolenem sloupci vse zmenime na lowercase
                                table[i][operationParameter1 - 1][k] = tolower(table[i][operationParameter1 - 1][k]);
                            }
                        }
                    }
                }
            } else {
                invalid();
            }
        }

        else if (strcmp(operation, "toupper") == 0) {
            if (!((operationParameter1 > numberOfColumns +1) || (operationParameter1 <= 0))){
                for (int i = 0; i <= (row); i++) {
                    for (int j = 0 ; j <= (operationParameter1 - 1); j++) {
                        for(int k = 0; k <= MAX_CHARS_IN_COLUMN; k++) {
                            //char po charu ve zvolenem sloupci vse zmenime na uppercase
                            table[i][operationParameter1 - 1][k] = toupper(table[i][operationParameter1 - 1][k]);
                        }
                    }
                }
            } else {
                invalid();
            }
        }

        //neprisel jsem na to, stale to hazi segfault
        else if (strcmp(operation, "round") == 0) {
            fprintf(stderr, "%s", "Unable to execute command\nCommand not defined\n");

            /*for (int i = 0; i <= (row); i++) {
                for (int j = 0 ; j <= (numberOfColumns); j++) {
                    for(int k = 0; k < charInColumn; k++) {
                        if(j == operationParameter1 - 1) {
                            table[i][operationParameter1 - 1][k] = atoi(table[i][operationParameter1 - 1][k]);
                            table[i][operationParameter1 - 1][k] = round(table[i][operationParameter1 - 1][k]);
                        }
                    }
                }
            }*/
        }

        //stejne jako u round
        else if (strcmp(operation, "int") == 0) {
            fprintf(stderr, "%s", "Unable to execute command\nCommand not defined\n");\

            /*for (int i = 0; i <= (row); i++) {
                for (int j = 0 ; j <= (numberOfColumns); j++) {
                    for(int k = 0; k < charInColumn; k++) {
                        if(j == operationParameter1 - 1) {
                            table[i][operationParameter1 - 1][k] = atoi(table[i][operationParameter1 - 1][k]);
                        }
                    }
                }
            }*/
        }

        else if (strcmp(operation, "copy") == 0) {
            if (!(((operationParameter1 <= 0) || (operationParameter2 <= 0)) || ((operationParameter1 > numberOfColumns +1) || (operationParameter2 > numberOfColumns +1)))) {
                for (int i = 0; i <= row; i++) {
                    for (int k = 0; k < MAX_CHARS_IN_COLUMN; k++) {
                        table[i][operationParameter2 - 1][k] = table[i][operationParameter1 - 1][k];
                    }
                }
            } else {
                invalid();
            }
        }

        //vyuzivame principu prehazovani hodnot z funkci drows a dcols
        else if (strcmp(operation, "swap") == 0) {
            if (!(((operationParameter1 <= 0) || (operationParameter2 <= 0)) || ((operationParameter1 > numberOfColumns +1) || (operationParameter2 > numberOfColumns +1)))) {
                for (int i = 0; i <= row; i++) {
                    for (int k = 0; k < MAX_CHARS_IN_COLUMN; k++) {
                        char temp;
                        temp = table[i][operationParameter1 - 1][k];
                        table[i][operationParameter1 - 1][k] = table[i][operationParameter2 - 1][k];
                        table[i][operationParameter2 - 1][k] = temp;
                    }
                }
            } else {
                invalid();
            }
        }

        /*Tato funkce vyuziva funkce swap, aby v pripade 'op1 < op2' postupne prehodila sloupecek op1+x za op1+x+1, pricemz plati ze x++, takze se sloupce postupne zamenuji,
        nez se dosahne pozadovaneho vysledku. V pripade 'op1 > op2' se prohazuje sloupecek op1-x za op1-x-1, abychom dosahli prehazovani zprava doleva.*/
        else if (strcmp(operation, "move") == 0) {
            if (!(((operationParameter1 <= 0) || (operationParameter2 <= 0)) || ((operationParameter1 > numberOfColumns +1) || (operationParameter2 > numberOfColumns +1)))) {

                if(operationParameter1 < operationParameter2){
                    int repetitions = operationParameter2 - operationParameter1;
                    char temp;
                
                    for (int x = 0; x < repetitions; x++) {
                        for (int i = 0; i <= row; i++) {
                            for (int k = 0; k < MAX_CHARS_IN_COLUMN; k++) {
                                temp = table[i][operationParameter1 - 1+x][k];
                                table[i][operationParameter1 - 1+x][k] = table[i][operationParameter1 - 1+x+1][k];
                                table[i][operationParameter1 - 1+x+1][k] = temp;
                            }
                        }
                    }
                } else if (operationParameter1 > operationParameter2) {
                    int repetitions = operationParameter1 - operationParameter2;
                
                    for (int x = 0; x < repetitions; x++) {
                        for (int i = 0; i <= row; i++) {
                            for (int k = 0; k < MAX_CHARS_IN_COLUMN; k++) {
                                char temp;
                                temp = table[i][operationParameter1 - 1-x][k];
                                table[i][operationParameter1 - 1-x][k] = table[i][operationParameter1 - 1-x-1][k];
                                table[i][operationParameter1 - 1-x-1][k] = temp;
                            }
                        }
                    }
                }else{
                    fprintf(stderr, "%s", "The numbers are the same\n");
                }
            }else {
                invalid();
            }
        } else {
            invalid();
        }
    }
    
    else {
        fprintf(stderr, "%s", "Invalid command\nCouldn't figure out how to set a space as a delimiter value\n");
    }

    for (int i = 0; i < row; i++) { //vypise cele pole po uprave prikazem
        for (int j = 0; j <= numberOfColumns; j++) {
            if (j == numberOfColumns) {
                fprintf(stdout, "%s",table[i][j]);
            } else {
                fprintf(stdout, "%s%c",table[i][j], delimiter);
            }
        }
        fprintf(stdout, "%s", "\n");
    }

    return 0;
}