#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "buffer.h"

/*
* Gap Buffer is a simple character array with an empty space
* between two chunks of characters that acts as a cursor and
* allows for fast inserts and deletes. A Gap Buffer (say of size 6)
* when initialized will have the following structure:
*
* +---+---+---+---+---+---+
* | X | X | X | X | X | X |
* +---+---+---+---+---+---+
*
* X's represents the locations occupied by the cursor, which during
* initialization is the whole buffer.
*/
buffer* init(int size) {
    buffer* buf = malloc(sizeof(buffer));
    buf->size = size;
    buf->arr = (char*)calloc((size_t)buf->size, sizeof(char));
    buf->start = (int*)&buf->arr[0];
    buf->end = (int*)&buf->arr[buf->size - 1];
    // initially the cursor spreads over the entirity of the buffer
    buf->gap_size = size;
    buf->cursor_start = &buf->arr[0];
    buf->cursor_end = &buf->arr[buf->size - 1];

    return buf;
}

// moves the cursor one location forward and copies
// character at the beginning of the rear end to the
// end of the front end of the buffer.
void move_cursor_forward(buffer *buf) {
    printf("==========BEFORE MOVING FORWARD=========\n");
    printf("CS: %d\tCE: %d\n", buf->cursor_start, buf->cursor_end);

    char *pointer = buf->cursor_end +1;
    char temp = *buf->cursor_start;
    *buf->cursor_start = *pointer;
    *pointer = temp;
    buf->cursor_start++;
    buf->cursor_end++;

    printf("%c\t%d\t%s\n", (*buf->cursor_start), buf->cursor_start, buf->arr);
    buff_print(buf);
    printf("==========AFTER MOVING FORWARD=========\n");
    printf("CS: %d\tCE: %d\n", buf->cursor_start, buf->cursor_end);
}

// moves the cursor one location backward and copies
// character at the end of the front end to the
// beginning of the rear end of the buffer.
void move_cursor_backward(buffer *buf) {
    printf("==========BEFORE MOVING BACKWARD=========\n");
    printf("CS: %d\tCE: %d\n", buf->cursor_start, buf->cursor_end);

    char *pointer = buf->cursor_start -1;
    char temp = *buf->cursor_end;
    *buf->cursor_end = *pointer;
    *pointer = temp;
    buf->cursor_start--;
    buf->cursor_end--;

    printf("%c\t%d\t%s\n", (*buf->cursor_start), buf->cursor_start, buf->arr);
    buff_print(buf);
    printf("==========AFTER MOVING BACKWARD=========\n");
    printf("CS: %d\tCE: %d\n", buf->cursor_start, buf->cursor_end);
    printf("BACKWARD BUFF SIZE: %d GAP SIZE: %d\n", buf->size, buf->gap_size);
}


// inserts a string at the start pos of the cursor.
void insert_str(buffer *buf, char *str) {
    printf("==========AFTER INSERTING STRING=========\n");
    for(int i=0; i<strlen(str); i++) {
        printf("run #%d\n", i);
        *buf->cursor_start = str[i];
        printf("Start: %d\t CS: %d\tCE: %d\t character: %c\n", buf->start, buf->cursor_start, buf->cursor_end, *buf->cursor_start);
        buf->cursor_start++;
        if(buf->cursor_start > buf->cursor_end) {
            resize(buf);
        } else {
            printf("STILL NOT EQ; CS: %d\tCE: %d\n", buf->cursor_start, buf->cursor_end);
        }
    }
    printf("\nINSERT BUFF SIZE: %d GAP SIZE: %d\n", buf->size, buf->gap_size);
}

// insert a gap twice the size of the previous gap at the cursor.
void resize(buffer *buf) {
    printf("==========AFTER RESIZING=========\n");
    printf("BUFF SIZE: %d GAP SIZE: %d\n", buf->size, buf->gap_size);
    printf("CURSOR START: %d CURSOR END: %d\n", buf->cursor_start, buf->cursor_end);

    int *res = realloc(buf->arr, (buf->gap_size * 2) * sizeof(char));
    if(res) {
        buf->gap_size *= 2;
        buf->size += buf->gap_size;
        buf->end += buf->gap_size;
        buf->cursor_start++;
        buf->cursor_end = &buf->arr[(buf->size - 1)];
        printf("BUFF SIZE: %d GAP SIZE: %d\n", buf->size, buf->gap_size);
        printf("AFTER RESIZE  bufStart: %d\t cStart: %d\t cEnd: %d\t bufEnd: %d\n", buf->start, buf->cursor_start, buf->cursor_end, buf->end);
        buff_print(buf);
        return;
    } else {
        fprintf(stderr, "ERROR: realloc failed");
        return;
    }
}


void buff_print(buffer *buf) {
    for(int i=0; i<buf->size; i++) {
        if(buf->arr[i]=='\0') {
            printf("X\n");
        } else {
            printf("%c\n", buf->arr[i]);
        }
    }
    printf("\n");
}
