#include <stdio.h>
#include "parser.h"
#include "records.h"

static void write_output(FILE *output, RecordList *records) {
    int i;
    int j;
    CommandRecord rec;

    for (i = 0; i < records->size; i++) {
        rec = records->data[i];

        fprintf(output, "%s", rec.command);

        for (j = 0; j < rec.arg_count; j++) {
            fprintf(output, " %lld", rec.args[j]);
        }

        fprintf(output, " -> %s\n", rec.result);
        printf("%s", rec.command);

        for (j = 0; j < rec.arg_count; j++) {
            printf(" %lld", rec.args[j]);
        }

        printf(" -> %s\n", rec.result);
    }
}

int main(int argc, char *argv[]) {
    FILE *input;
    FILE *output;
    RecordList records;

    if (argc != 3) {
        printf("Kullanim: ./numtool <giris_dosyasi> <cikis_dosyasi>\n");
        return 1;
    }

    input = fopen(argv[1], "r");
    if (input == NULL) {
        printf("Giris dosyasi acilamadi.\n");
        return 1;
    }

    output = fopen(argv[2], "w");
    if (output == NULL) {
        printf("Cikis dosyasi olusturulamadi.\n");
        fclose(input);
        return 1;
    }

    init_records(&records);

    read_commands(input, &records);
    write_output(output, &records);

    free_records(&records);

    fclose(input);
    fclose(output);

    return 0;
}
