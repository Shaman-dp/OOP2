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
	struct CANDY *next;
} candy;

char** split(char* str, char separator) {
	int i, is_separator, word_index, word_number, words_count;
	char** words;

	words_count = 0;
	for (i = 0; i < strlen(str); ++i) {
		if (str[i] == separator) {
			++words_count;
		}
	}
	++words_count;

	words = (char**)malloc((words_count + 2) * sizeof(char*));
	if (words != NULL) {
		for (i = 0; i < words_count + 2; ++i) {
			words[i] = (char*)malloc(strlen(str) * sizeof(char));
		}
	}
	else {
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

void view_struct(candy* p, candy* head) {
	p = head;


	printf("| %16s | %16s | %16s | %16s | %16s | %16s | %s\n", "name", "producer", "production", "year", "price", "weight", "parameters");
	printf("| %16s | %16s | %16s | %16s | %16s | %16s | %s\n", "________________", "________________", "________________",
		"________________", "________________", "________________", "________________");


	while (p != NULL) {
		printf("| %16s | %16s | %16d | %16d | %16.3f | %16.3f | %4d %4d %4d %4d \n",
						p->name, p->producer, p->production, p->year,
						p->price, p->weight, p->parameters[0],
						p->parameters[1], p->parameters[2], p->parameters[3]);
		p = p->next;
	}
}

candy *delete_(candy *p, candy *head){
	candy *h;
	char str[MAX_LEN];

    p = head;

    /*printf("What names of candys you want to delete: ");*/
    fgets(str, MAX_LEN, stdin);
    str[strlen(str) - 1] = '\0';

    if (p == head) {
        if (strcmp(p->name, str) == 0) {
            h = p;
            p = p->next;
            head = p;
            free(h);
            return head;
        }
    }

    while (p->next != NULL) {

        if (strcmp(p->next->name, str) == 0) {
            h = p->next;
            p->next = p->next->next;
            free(h);
            return head;
        }
        p = p->next;
    }

    puts("Element not found");
	return head;
}

int main()
{
    int i, j;
	FILE* file;
	char str[MAX_LEN];

	char** text;

	candy *head = NULL, *p = NULL;

	file = fopen("dataa.csv", "r");


	if (file != NULL)
	{
		while (fgets(str, MAX_LEN, file) != NULL)
		{
			str[strlen(str) - 1] = '\0';
			text = split(str, ';');

			p = (candy*)malloc(MAX_LEN * sizeof(candy));
			p->name = (char*)malloc(strlen(text[1]) * sizeof(char));
			p->producer = (char*)malloc(strlen(text[2]) * sizeof(char));
			p->parameters = (int*)malloc(4 * sizeof(int));

			strcpy(p->name, text[1]);
			strcpy(p->producer, text[2]);
			p->production = atoi(text[3]);
			p->year = atoi(text[4]);
			p->price = atof(text[5]);
			p->weight = atof(text[6]);
			for (i = 7; i < 11; ++i) {
				p->parameters[i - 7] = atoi(text[i]);
			}
			p->next = head;
			head = p;
		}

	}
	else
	{
		puts("File no open");
	}

	view_struct(p, head);

	puts("How many records do you want to add?");
    fgets(str, MAX_LEN, stdin);
    str[strlen(str) - 1] = '\0';
    for (j = 0; j < atoi(str); j++){
        printf("What names of %d candys you want to delete: ", j + 1);
        head = delete_(p, head);
    }

    /*system("cls");*/

    view_struct(p, head);

	getchar();
	return 0;
}
