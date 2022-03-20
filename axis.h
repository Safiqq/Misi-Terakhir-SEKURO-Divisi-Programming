#ifndef axis_h
#define axis_h

typedef struct
{
    int x;
    int y;
} axis;

axis make_axis (int x, int y);

void move_axis (axis* a, char c);

#endif
