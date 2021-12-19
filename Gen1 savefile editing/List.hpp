#ifndef LIST_CPP_I
#define LIST_CPP_I

struct ListEntry{
    unsigned char index;
    unsigned char amount;
};

struct List{
    unsigned char length;
    ListEntry *items;
};

#endif