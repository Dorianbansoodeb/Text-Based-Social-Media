/********* nodes.h ********
    Dorian Bansoodeb
*/
#ifndef A2_NODES_H
#define A2_NODES_H
/********** DON'T MODIFY **********/
// Structure to represent a linked list of users
typedef struct user
{
    char username[30];
    char password[15];
    struct friend *friends;
    struct post *posts;
    struct user *next;
} user_t;

// Structure to represent linked list of a user's posts
typedef struct friend
{
    char username[30];
    struct friend *next;
}
friend_t;

// Structure to represent linked list of a user's posts
typedef struct post
{
    char content[250];
    struct post *next;
} post_t;

#endif