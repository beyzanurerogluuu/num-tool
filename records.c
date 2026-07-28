#include <stdio.h>
#include <stdlib.h>
#include "records.h"

void init_records(RecordList *list) {
    list->size = 0;
    list->capacity = 8;
    list->data = (CommandRecord *)malloc(list->capacity * sizeof(CommandRecord));

    if (list->data == NULL) {
        printf("Bellek ayrilamadi.\n");
        exit(1);
    }
}

void add_record(RecordList *list, CommandRecord rec) {
    CommandRecord *temp;

    if (list->size >= list->capacity) {
        list->capacity *= 2;
        temp = (CommandRecord *)realloc(list->data,
                                        list->capacity * sizeof(CommandRecord));

        if (temp == NULL) {
            printf("Bellek genisletilemedi.\n");
            free(list->data);
            exit(1);
        }

        list->data = temp;
    }

    list->data[list->size] = rec;
    list->size++;
}

void free_records(RecordList *list) {
    free(list->data);
    list->data = NULL;
    list->size = 0;
    list->capacity = 0;
}
