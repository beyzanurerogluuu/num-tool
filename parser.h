#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include "records.h"

void read_commands(FILE *input, RecordList *records);
void process_record(CommandRecord *rec);

#endif
