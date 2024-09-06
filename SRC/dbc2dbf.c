/* dbc2dbf.c
   Copyright (C) 2016 Daniela Petruzalek

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU Affero General Public License as published
   by the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU Affero General Public License for more details.

   You should have received a copy of the GNU Affero General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/*
    Author Notes
    ============

    This program decompresses .dbc files to .dbf. This code is based on the work
    of Mark Adler <madler@alumni.caltech.edu> (zlib/blast) and Pablo Fonseca
    (https://github.com/eaglebh/blast-dbf).
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdint.h>
#include "blast.h"

#define CHUNK 4096

/* Input file helper function */
static unsigned inf(void *how, unsigned char **buf) {
    static unsigned char hold[CHUNK];
    *buf = hold;
    return fread(hold, 1, CHUNK, (FILE *)how);
}

/* Output file helper function */
static int outf(void *how, unsigned char *buf, unsigned len) {
    return fwrite(buf, 1, len, (FILE *)how) != len;
}

/* Close open files */
void cleanup(FILE* input, FILE* output) {
    if (input) fclose(input);
    if (output) fclose(output);
}

/* Function to print error messages and return an error code instead of exiting directly */
int handle_error(const char* message, const char* file) {
    fprintf(stderr, "%s %s: %s\n", message, file, strerror(errno));
    return -1;
}

/* Main function to decompress .dbc to .dbf */
int dbc2dbf(const char* input_filename, const char* output_filename) {
    FILE *input = fopen(input_filename, "rb");
    if (!input) {
        return handle_error("Error reading input file", input_filename);
    }

    FILE *output = fopen(output_filename, "wb");
    if (!output) {
        cleanup(input, NULL);
        return handle_error("Error opening output file", output_filename);
    }

    // Skip 8 bytes (assumed header metadata)
    if (fseek(input, 8, SEEK_SET) != 0) {
        cleanup(input, output);
        return handle_error("Error skipping header in input file", input_filename);
    }

    unsigned char rawHeader[2];
    if (fread(rawHeader, 1, 2, input) != 2) {
        cleanup(input, output);
        return handle_error("Error reading header size from input file", input_filename);
    }

    uint16_t header = rawHeader[0] + (rawHeader[1] << 8);
    rewind(input);
    unsigned char buf[header];

    if (fread(buf, 1, header, input) != header) {
        cleanup(input, output);
        return handle_error("Error reading full header from input file", input_filename);
    }

    if (fwrite(buf, 1, header, output) != header) {
        cleanup(input, output);
        return handle_error("Error writing header to output file", output_filename);
    }

    if (fseek(input, header + 4, SEEK_SET) != 0) {
        cleanup(input, output);
        return handle_error("Error skipping to data section in input file", input_filename);
    }

    int ret = blast(inf, input, outf, output);
    if (ret) {
        cleanup(input, output);
        fprintf(stderr, "Error decompressing file: %d\n", ret);
        return -2;  // Return specific error code for decompression failure
    }

    cleanup(input, output);
    return 0; // Success
}

/* Entry point for the program */
int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input.dbc> <output.dbf>\n", argv[0]);
        return 1;
    }

    int result = dbc2dbf(argv[1], argv[2]);
    if (result == 0) {
        printf("Decompression successful: %s -> %s\n", argv[1], argv[2]);
    } else {
        fprintf(stderr, "Decompression failed for %s -> %s\n", argv[1], argv[2]);
    }

    return result;
}
