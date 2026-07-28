#ifndef RECORDS_H
#define RECORDS_H

typedef struct {
    char command[20];
    long long args[4];
    int arg_count;
    char result[100];
    int is_error;
} CommandRecord;

typedef struct {
    CommandRecord *data;
    int size;
    int capacity;
} RecordList;

void init_records(RecordList *list);
void add_record(RecordList *list, CommandRecord rec);
void free_records(RecordList *list);

#endif
