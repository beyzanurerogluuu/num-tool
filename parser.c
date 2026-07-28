#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "parser.h"
#include "math_utils.h"

static char *trim_spaces(char *str) {
    char *end;

    while (isspace((unsigned char)*str)) {
        str++;
    }

    if (*str == '\0') {
        return str;
    }

    end = str + strlen(str) - 1;

    while (end > str && isspace((unsigned char)*end)) {
        *end = '\0';
        end--;
    }

    return str;
}

static int parse_one_command(char *text, CommandRecord *rec) {
    char cmd[20];
    long long a, b, c;
    int count;

    rec->arg_count = 0;
    rec->is_error = 0;
    rec->result[0] = '\0';

    count = sscanf(text, "%19s %lld %lld %lld", cmd, &a, &b, &c);

    if (count < 1) {
        return 0;
    }

    strcpy(rec->command, cmd);

    if (strcmp(cmd, "GCD") == 0) {
        if (count == 3) {
            rec->args[0] = a;
            rec->args[1] = b;
            rec->arg_count = 2;
        } else {
            rec->is_error = 1;
            strcpy(rec->result, "ERROR_INVALID_INPUT");
        }
    } else if (strcmp(cmd, "POW") == 0) {
        if (count == 4) {
            rec->args[0] = a;
            rec->args[1] = b;
            rec->args[2] = c;
            rec->arg_count = 3;
        } else {
            rec->is_error = 1;
            strcpy(rec->result, "ERROR_INVALID_INPUT");
        }
    } else if (strcmp(cmd, "PRIME") == 0 || strcmp(cmd, "PHI") == 0) {
        if (count == 2) {
            rec->args[0] = a;
            rec->arg_count = 1;
        } else {
            rec->is_error = 1;
            strcpy(rec->result, "ERROR_INVALID_INPUT");
        }
    } else if (strcmp(cmd, "INV") == 0 || strcmp(cmd, "CHECK") == 0) {
        if (count == 3) {
            rec->args[0] = a;
            rec->args[1] = b;
            rec->arg_count = 2;
        } else {
            rec->is_error = 1;
            strcpy(rec->result, "ERROR_INVALID_INPUT");
        }
    } else {
        rec->is_error = 1;
        strcpy(rec->result, "ERROR_INVALID_COMMAND");
    }

    return 1;
}

void process_record(CommandRecord *rec) {
    long long a, b, m;
    long long inv;
    int has_inverse;

    if (rec->is_error) {
        return;
    }

    if (strcmp(rec->command, "GCD") == 0) {
        a = rec->args[0];
        b = rec->args[1];

        if (a <= 0 || b <= 0) {
            rec->is_error = 1;
            strcpy(rec->result, "ERROR_INVALID_INPUT");
        } else {
            sprintf(rec->result, "%lld", gcd_ll(a, b));
        }

    } else if (strcmp(rec->command, "POW") == 0) {
        a = rec->args[0];
        b = rec->args[1];
        m = rec->args[2];

        if (b < 0 || m <= 0) {
            rec->is_error = 1;
            strcpy(rec->result, "ERROR_INVALID_INPUT");
        } else {
            sprintf(rec->result, "%lld", mod_pow(a, b, m));
        }

    } else if (strcmp(rec->command, "PRIME") == 0) {
        a = rec->args[0];

        if (a < 2) {
            rec->is_error = 1;
            strcpy(rec->result, "ERROR_INVALID_INPUT");
        } else {
            if (is_prime(a)) {
                strcpy(rec->result, "YES");
            } else {
                strcpy(rec->result, "NO");
            }
        }

    } else if (strcmp(rec->command, "INV") == 0) {
        a = rec->args[0];
        m = rec->args[1];

        if (m <= 1) {
            rec->is_error = 1;
            strcpy(rec->result, "ERROR_INVALID_INPUT");
        } else {
            inv = mod_inverse(a, m, &has_inverse);

            if (has_inverse) {
                sprintf(rec->result, "%lld", inv);
            } else {
                rec->is_error = 1;
                strcpy(rec->result, "ERROR_NO_INVERSE");
            }
        }

    } else if (strcmp(rec->command, "PHI") == 0) {
        a = rec->args[0];

        if (a < 1) {
            rec->is_error = 1;
            strcpy(rec->result, "ERROR_INVALID_INPUT");
        } else {
            sprintf(rec->result, "%lld", phi_value(a));
        }

    } else if (strcmp(rec->command, "CHECK") == 0) {
        a = rec->args[0];
        m = rec->args[1];

        if (m <= 1) {
            rec->is_error = 1;
            strcpy(rec->result, "ERROR_INVALID_INPUT");
        } else {
            inv = mod_inverse(a, m, &has_inverse);

            if (!has_inverse) {
                rec->is_error = 1;
                strcpy(rec->result, "ERROR_NO_INVERSE");
            } else if ((a * inv) % m == 1) {
                strcpy(rec->result, "CORRECT");
            } else {
                rec->is_error = 1;
                strcpy(rec->result, "FAILED");
            }
        }
    }
}

void read_commands(FILE *input, RecordList *records) {
    char line[512];
    char *part;
    char *clean;
    CommandRecord rec;

    while (fgets(line, sizeof(line), input) != NULL) {
        clean = trim_spaces(line);

        if (clean[0] == '\0' || clean[0] == '#') {
            continue;
        }

        part = strtok(clean, ";");

        while (part != NULL) {
            clean = trim_spaces(part);

            if (clean[0] != '\0' && clean[0] != '#') {
                if (parse_one_command(clean, &rec)) {
                    process_record(&rec);
                    add_record(records, rec);
                }
            }

            part = strtok(NULL, ";");
        }
    }
}
