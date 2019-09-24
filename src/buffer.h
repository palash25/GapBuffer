#ifndef BUFFER_H
#define BUFFER_H

#include <stdio.h>
typedef struct {
    char *arr;
    size_t size; /* total size of the buffer */
    size_t gap_size; /* size of the gap */
    char *cursor_start; /* starting pos of the gap */
    char *cursor_end; /* ending pos of the gap */
} buffer;

buffer* init(int size);

void insert_str(buffer* buf, char *str);

void delete_buffer(buffer* buf);

void move_cursor_forward(buffer *buf);

void move_cursor_backward(buffer *buf);

#endif
