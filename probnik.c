#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN 200


typedef struct CANDY
{
    char* name;
    char* producer;
    int production;
    int year;
    float price;
    float weight;
    int* parameters;
} candy;



char** split(char* str, char separator) {
    int i, is_separator, word_index, word_number, words_count;
    char** words;

    words_count = 0;
    for(i = 0; i < strlen(str); ++i) {
        if(str[i] == separator) {
            ++words_count;
        }
    }
    ++words_count;

    words = (char**)malloc((words_count + 2) * sizeof(char*));
    if (words != NULL) {
        for (i = 0; i < words_count + 2; ++i) {
            words[i] = (char*) malloc(strlen(str) * sizeof(char));
        }
    } else {
        puts("Memory allocation error");
    }

    sprintf(words[0], "%d", words_count);

    i = 0;
    word_index = 0;
    word_number = 1;

    while (str[i] != '\0') {
        is_separator = 0;
        if (str[i] == separator) {
            if (word_index != 0) {
                words[word_number][word_index++] = '\0';
                word_index = 0;
                word_number++;
            }
            is_separator = 1;
        }

        if (!is_separator) {
            if (words[word_number] != NULL) {
                words[word_number][word_index++] = str[i];
            }
        }

        ++i;
    }

    return words;
}


candy* line_to_struct(char** line) {
    int i;
    candy* one_note = (candy*)malloc(sizeof(candy));
    if (one_note) {
        one_note->name = (char*)malloc(strlen(line[1]) * sizeof(char));
        one_note->producer = (char*)malloc(strlen(line[2]) * sizeof(char));
        one_note->parameters = (int*)malloc(4 * sizeof(int));

        if (one_note->name && one_note->producer && one_note->parameters) {

            strcpy(one_note->name, line[1]);
            strcpy(one_note->producer, line[2]);

            one_note->production = atoi(line[3]);
            one_note->year = atoi(line[4]);
            one_note->price = atof(line[5]);
            one_note->weight = atof(line[6]);

            for (i = 7; i < 11; ++i) {
                one_note->parameters[i - 7] = atoi(line[i]);
            }
        } else {
            puts("Memory allocation error");
        }
    }
    else {
        puts("Memory allocation error");
    }

    return one_note;
}

void view_struct(candy** array, int rows) {
    int i;

    printf("| %16s | %16s | %16s | %16s | %16s | %16s | %s\n", "name", "producer", "production", "year", "price", "weight", "parameters");
    printf("| %16s | %16s | %16s | %16s | %16s | %16s | %s\n", "________________", "________________", "________________",
                                                               "________________", "________________", "________________", "________________");

    for (i = 0; i < rows; ++i)
    {
        printf("| %16s | %16s | %16d | %16d | %16.3f | %16.3f | %4d %4d %4d %4d \n",
               array[i]->name, array[i]->producer, array[i]->production, array[i]->year,
               array[i]->price, array[i]->weight, array[i]->parameters[0],
               array[i]->parameters[1], array[i]->parameters[2], array[i]->parameters[3]);
    }
}

void sort(candy** array, int rows) {
	int i, k, old;
    float sort_param1, sort_param2;
	candy* old_sport;
    char str[MAX_LEN];

    printf("Enter the field name for sorting: production, year, price or weight: ");
    fgets(str, MAX_LEN, stdin);
    str[strlen(str) - 1] = '\0';

	for(i = 1; i < rows; ++i) {
		for(k = i; k > 0; --k) {
            sort_param1 = 0.0;
            sort_param2 = 0.0;
            if (strcmp(str, "production") == 0){
                sort_param1 = array[k-1]->production;
                sort_param2 = array[k]->production;
            }
            else if (strcmp(str, "year") == 0){
                sort_param1 = array[k-1]->year;
                sort_param2 = array[k]->year;
            }
            else if (strcmp(str, "price") == 0){
                sort_param1 = array[k-1]->price;
                sort_param2 = array[k]->price;
            }
            else if (strcmp(str, "weight") == 0){
                sort_param1 = array[k-1]->weight;
                sort_param2 = array[k]->weight;
            }

            if (sort_param1 > sort_param2){
                old_sport = array[k-1];
                array[k-1] = array[k];
                array[k] = old_sport;
            }
		}
	}
	old_sport = NULL;
}

int main()
{
    FILE* file;
    candy** array;
    candy** array2;
    char str[MAX_LEN];
    int i, j, cnt;
    char** text;


    file = fopen("dataa.csv", "r");
    array = (candy**) malloc(MAX_LEN * sizeof(candy*));
    array2 = (candy**) malloc(MAX_LEN * sizeof(candy*));
    if (file != NULL)
    {
        if((array != NULL) && (array2 != NULL))
        {
            i = 0;
            while (fgets(str, MAX_LEN, file) != NULL)
            {
                str[strlen(str) - 1] = '\0';
                text = split(str, ';');

                array[i] = line_to_struct(text);
                i++;
            }
        }
        else
        {
            puts("Memory allocation error");
        }
    }
    else
    {
        puts("File no open");
    }

    puts("Write 'yes' if you want to add an entry or 'no' if you don't want to: ");
    fgets(str, MAX_LEN, stdin);
    str[strlen(str) - 1] = '\0';
    if (strcmp(str, "yes") == 0)
    {
        puts("How many records do you want to add?");
        fgets(str, MAX_LEN, stdin);
        str[strlen(str) - 1] = '\0';
        for (j = 0; j < atoi(str); j++)
        {
            printf("Enter %d line", j + 1);
            fgets(str, MAX_LEN, stdin);
            str[strlen(str) - 1] = '\0';
            text = split(str, ';');
            array[i] = line_to_struct(text);
            i++;

        }
    }

    puts("Enter a search term: ");
    fgets(str, MAX_LEN, stdin);
    str[strlen(str) - 1] = '\0';
    cnt = 0;
    for (j = 0; j < i; j++)
    {
        text = split(array[j]->name, ' ');
        if (strcmp(text[1], str) == 0)
        {
            array2[cnt] = array[j];
            cnt++;
        }
    }

    sort(array2, cnt);
    view_struct(array2, cnt);

    return 0;
}
