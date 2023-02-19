#include <stdio.h>

int get_index(int arr[5], int value){
    for (int i = 0; i < 5; i++){
        if (arr[i] == value){
            return i;
        }
    }
    return -1;
}

int main(){    
    char file_name[50];
    FILE *f;

    printf("Enter input file name: ");
    scanf("%s", file_name);

    f = fopen(file_name, "r");

    char ch;
    int i = 0, j = 0;

    int programmers[5][5];
    int departments[5][5];

    while(ch != EOF){
        ch = fgetc(f);
        if ('0' <= ch && ch <= '9'){
            if (j < 5){
                departments[i++][j] = ch - '0';
            } else {
                programmers[i++][j-5] = ch - '0';
            }
            if (i == 5){
                i = 0;
                j++;
            }
        }
    }

    int scores[5][5]; // scores[i][j] represents the sum of preferences between Department i and Programmer j
    int programmer_score, department_score;

    for(int i = 0; i < 5; i++){
        for (int j = 0; j < 5; j++){
            programmer_score = 5 - get_index(programmers[j], i+1);
            department_score = 5 - get_index(departments[i], j+1);
            scores[i][j] = programmer_score + department_score;
        }
    }

    int matches[5] = {-1,-1,-1,-1,-1}; // ith index represents Department i+1. -1 represents no matches yet
    int max_score = 10, total_matches = 0;

    while(total_matches < 5){
        for(int i = 0; i<5; i++){
            for(int j = 0; j<5; j++){
                if (scores[i][j] == max_score && matches[i] == -1 && get_index(matches, j) == -1){
                    matches[i] = j;
                    total_matches++;
                }
            }
        }
        max_score--;
    }

    for(int i = 0; i<5; i++){
        printf("Department #%d will get Programmer #%d\n", i+1, matches[i]+1);
    }

    return 0;
}