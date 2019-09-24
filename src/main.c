#include "buffer.h"
#include<stdio.h>

int main()
{
    buffer* buff = init(6);
    printf("%d %d %d %s\n", buff->size, buff->cursor_start, buff->cursor_end, buff->arr);
    insert_str(buff, "blah");
    printf("%d %d %d %s\n", buff->size, buff->cursor_start, buff->cursor_end, buff->arr);
    move_cursor_backward(buff);
    move_cursor_backward(buff);
    move_cursor_forward(buff);
    insert_str(buff, "...");

    move_cursor_backward(buff);
    move_cursor_backward(buff);
    move_cursor_forward(buff);

    delete_buffer(buff);
    return 0;
}
