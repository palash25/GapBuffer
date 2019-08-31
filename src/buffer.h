#ifndef BUFFER_H
#define BUFFER_H

typedef struct {
    char *arr;
    int size; // total size of the buffer
    int *start; // starting pos of the buffer
    int *end; // ending pos of the buffer
    int gap_size; // size of the gap
    char *cursor_start; // starting pos of the gap
    char *cursor_end; // ending pos of the gap
} buffer;

buffer* init(int size);

void insert_str(buffer* buf, char *str);

void move_cursor_forward(buffer *buf);

void move_cursor_backward(buffer *buf);

#endif
