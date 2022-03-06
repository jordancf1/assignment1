#include "fulawkaJordanA1.h"

FILE *openFileForReading(char *fileName){
    FILE* file = NULL;
    file = fopen(fileName, "r");
    return file;
}

int readMovies(FILE *file, char movieNames[NUMBER_MOVIES][MAX_STR]){
    int count;
    int i;
    int j;
    if(file == NULL){
        return 0;
    }
    count = 0;
    while(!feof(file)){
        fgets(movieNames[count], MAX_STR, file);
        count++;
    }
    for(i = 0; i < NUMBER_MOVIES; i++){
        for(j = 0; j < MAX_STR; j++){
            if(movieNames[i][j] == '\n'){
                movieNames[i][j] = '\0';
            }
        }
    }
    if(count > NUMBER_MOVIES){
        return 0;
    }
    else if(count < NUMBER_MOVIES){
        return 0;
    }
    else{
        return 1;
    }
}

int readReviews(FILE *file, struct reviewStruct reviews[NUMBER_REVIEWERS]){
    char temp0, temp1, temp2;
    int count;
    if(file == NULL){
        return 0;
    }
    count = 0;
    while(!feof(file)){
        fscanf(file, "%s %c %c %c", reviews[count].reviewer, &temp0, &temp1, &temp2);
        if(temp0 == 89 || temp0 == 121){
            reviews[count].feedback[0] = 1;
        }
        else{
            reviews[count].feedback[0] = 0;
        }
        if(temp1 == 89 || temp1 == 121){
            reviews[count].feedback[1] = 1;
        }
        else{
            reviews[count].feedback[1] = 0;
        }
        if(temp2 == 89 || temp2 == 121){
            reviews[count].feedback[2] = 1;
        }
        else{
            reviews[count].feedback[2] = 0;
        }
        count++;
    }
    if(count > NUMBER_REVIEWERS+1){
        return 0;
    }
    else if(count < NUMBER_REVIEWERS+1){
        return 0;
    }
    else{
        return 1;
    }
}

int getMostCriticalReviewers(struct reviewStruct reviews[NUMBER_REVIEWERS], char mostCriticalReviewers[NUMBER_REVIEWERS][MAX_STR]){
    int max;
    max = 0;
    int index;
    index = 0;
    int i;
    int j;
    int current;
    for(i = 0; i < NUMBER_REVIEWERS; i++){
        current = 0;
        for(j = 0; j < NUMBER_MOVIES; j++){
            if(reviews[i].feedback[j] == 0){
                current++;
            }
        }
        if(current > max){
            max = current;
        }
    }
    for(i = 0; i < NUMBER_REVIEWERS; i++){
        current = 0;
        for(j = 0; j < NUMBER_MOVIES; j++){
            if(reviews[i].feedback[j] == 0){
                current++;
            }
        }
        if(current == max){
            strcpy(mostCriticalReviewers[index], reviews[i].reviewer);
            index++;
        }
    }
    return index;
}

int getMostRecommendedMovies(const char movieNames[NUMBER_MOVIES][MAX_STR], const struct reviewStruct reviews[NUMBER_REVIEWERS], char mostRecommendedMovies[NUMBER_MOVIES][MAX_STR]){
    int max;
    max = 0;
    int index;
    index = 0;
    int current;
    int i;
    int j;
    for(i = 0; i < NUMBER_MOVIES; i++){
        current = 0;
        for(j = 0; j < NUMBER_REVIEWERS; j++){
            if(reviews[j].feedback[i] == 1){
                current++;
            }
        }
        if(current > max){
            max = current;
        }
    }
    for(i = 0; i < NUMBER_MOVIES; i++){
        current = 0;
        for(j = 0; j < NUMBER_REVIEWERS; j++){
            if(reviews[j].feedback[i] == 1){
                current++;
            }
        }
        if(current == max){
            strcpy(mostRecommendedMovies[index], movieNames[i]);
            index++;
        }
    }
    return index;
}

int predictMovie(const char movie[MAX_STR]){
    int numOfWords = 1;
    int sales = 0;
    bool allEqual;
    int numEven = 0;
    int i;
    for(i = 0; i < strlen(movie); i++){
        if(movie[i] == ' '){
            numOfWords++;
        }
    }

    switch(numOfWords){
        case 0:
            return 0;
            break;
        case 1:
            sales = 0;
            break;
        case 2:
            enumerateMovie(movie, charCounts);
            for(i = 0; i < numOfWords-1; i++){
                if(charCounts[i] == charCounts[i+1]){
                    allEqual = true;
                }
                else{
                    allEqual = false;
                    break;
                }
            }
            if(allEqual == true){
                sales = sales + 2;
            }
            for(int i = 0; i < numOfWords; i++){
                if(charCounts[i] % 2 == 0){
                    numEven++;
                }
            }
            if(numEven > 1){
                sales = sales + 1;
            }
            break;
        default:
            sales = sales - 1;
            enumerateMovie(movie, charCounts);
            for(i = 0; i < numOfWords-1; i++){
                if(charCounts[i] == charCounts[i+1]){
                    allEqual = true;
                }
                else{
                    allEqual = false;
                    break;
                }
            }
            if(allEqual == true){
                sales = sales + 2;
            }
            for(i = 0; i < numOfWords; i++){
                if(charCounts[i] % 2 == 0){
                    numEven++;
                }
            }
            if(numEven > 1){
                sales = sales + 1;
            }
            break;
    }
    printf("%d %d %d", numEven, numOfWords, allEqual);
    if(sales > 2){
        return 2;
    }
    else if(sales < -2){
        return -2;
    }
    else{
        return sales;
    }
}



int enumerateMovie(const char movie[MAX_STR], int charCounts[MAX_WORDS]){
    char tempmovie[MAX_STR];
    int count;
    count = 0;
    strcpy(tempmovie, movie);
    char * token;
    token = strtok(tempmovie, " ");
    while( token != NULL ) {
      charCounts[count] = strlen(token);
      token = strtok(NULL, " ");
      count++;
   }
   return count;
}