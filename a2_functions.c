/********* functions.c ********
   Dorian Bansoodeb
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>
#include "a2_nodes.h"
#include "a2_functions.h"

// Your solution goes here
//adds a user given the username and password
user_t *add_user(user_t *users, const char *username, const char *password){
    user_t *new_user = malloc(sizeof(user_t));
    assert(new_user!=NULL);
    user_t *temp ;
    
    strcpy(new_user->username,username);
    strcpy(new_user->password,password);
    new_user->friends = NULL;
    new_user->posts = NULL;
    new_user->next = NULL;
    //if the user linked list is empty, the first user becomes the head
    if(users==NULL){
        users = new_user;
        return users;
    }
    else{
        //the new user should be the head in this case
        if(strcmp(new_user->username,users->username)<0){
            temp = users;
            users = new_user;
            users->next = temp;
            return users;
        }
        else{
            //iterates over the user linked list until the correct alphebetical ordering is achieved
            temp = users;
            while(temp->next!=NULL && strcmp(new_user->username,temp->next->username)>0){
                temp = temp->next;
            }
            
            new_user->next = temp->next;
            temp->next = new_user;
            return users;
        }
    }

    
}

user_t *find_user(user_t *users, const char *username){
    user_t *current ;
    current = users;
    //iterates over the users until the user is found
    while(current!=NULL){
        if(strcmp(current->username,username)==0){
            return current;
        }
        current = current->next;
    }
    //returns NULL if the user is not in the list
    return NULL;
}

friend_t *create_friend(const char *username){

    friend_t *friend = malloc(sizeof(friend_t));
    assert(friend!=NULL);
    strcpy(friend->username,username);
    friend->next = NULL;
    return friend;
}

void add_friend(user_t *user, const char *friend){
        friend_t *new_friend = create_friend(friend);
        friend_t *temp = user->friends;
        //if there are no users
        if(user->friends==NULL){
            user->friends= new_friend;
        }
        //if the user's placement should be the first one in the list
        else if((strcmp(friend,user->friends->username)<0)){
                new_friend->next = temp;
                user->friends = new_friend;
        }
        //iterate until the correct position has been achieved
        else{
            while(temp->next!=NULL && strcmp(friend,temp->next->username)>0){
                temp = temp->next;
            }
            //adds the user in its deisgnated spot, or at the end
            new_friend->next = temp->next;
            temp->next = new_friend;
        }

}

void display_user_friends(user_t *user){
    friend_t *temp = user->friends;
    //counter to display the friend and the number associated with it
    int counter = 1;
    //prints all the friends
    while(temp!=NULL){
        printf("%d- %s\n",counter, temp->username);
        counter++;
        temp = temp->next;
    }


}
_Bool delete_friend(user_t *user, char *friend_name){
    //does not delete the user as there aren't any users in the list
    if(user->friends==NULL){
        return 0;
    }
    //if there is only one friend in the list 
    if(user->friends->next==NULL&&strcmp(user->friends->username,friend_name)==0){
        friend_t *temp = user->friends;
        user->friends = NULL;
        free(temp);
        return 1;
    }
    //if the first user is the one to deleted in the list
    if(strcmp(user->friends->username,friend_name)==0){
        friend_t *temp = user->friends;
        user->friends = user->friends->next;
        free(temp);
        return 1;
    }
    friend_t *temp = user->friends;
    friend_t *to_delete;
    //iterates over the list until the next user is the one to delete
    while(temp->next->next!=NULL){
        temp = temp->next;
    }
    if (strcmp(temp->next->username,friend_name)==0){
        to_delete=temp->next;
        temp->next = NULL;
        free(to_delete);
        return 1;
    }
    
    friend_t *temp2 = user->friends;
    friend_t *found;
    //delete the last user
    while(temp2->next!=NULL){
        if(strcmp(temp2->next->username,friend_name)==0){
            found = temp2;
            to_delete = temp2->next;
        }
        temp2 = temp2->next;
    }
    found->next= to_delete->next;
    to_delete = NULL;
    free(to_delete);
    return 1;


}

post_t *create_post(const char *text){
    post_t *new_post = malloc(sizeof(post_t));
    assert(new_post!=NULL);
    strcpy(new_post->content,text);
    new_post->next = NULL;
    return new_post;


}

void add_post(user_t *user, const char *text){
    post_t *new_post = create_post(text);

    post_t *temp = user->posts;
    //if there are no posts
    if (user->posts==NULL){
        user->posts = new_post;
    }
    //adds post to the end of the list
    else{
        while (temp->next!=NULL){
            temp = temp->next;
        }
        temp->next =new_post;
    }
    


}

_Bool delete_post(user_t *user){
    //if there are no posts
    if (user->posts==NULL){
        return 0;
    }
    //if there only is one post
    else if(user->posts->next==NULL){
        post_t *temp = user->posts;
        user->posts=NULL;
        free(temp);
        return 1;
    }
    else{
        //iterates over the list until the next post is the user
        post_t *temp = user->posts;
        while(temp->next->next!=NULL){
            temp = temp->next;
        }
        post_t *delete = temp->next;
        
        temp->next = NULL;

        free(delete);
        return 1;
    }
}

void display_all_user_posts(user_t *user){
    post_t *temp = user->posts;
    int num = 1;
    //iterates and prints all users
    while(temp!=NULL){
        printf("%d- %s\n",num,temp->content);
        temp = temp->next;
        num++;
    }

}

void display_posts_by_n(user_t *users, int number){
    printf("Please input username to display their posts: ");
    char username[30];
    scanf("%s",username);
    user_t *found = find_user(users,username);
    char answer = 'y';
    //no users
    if(found==NULL){
        printf("Not in list, returning to main menu\n");
    }
    //no posts
    else if(found->posts==NULL){
        printf("No posts\n");
    }

    else{
        post_t *temp = found->posts;
        int counter = 1;
        int counter2 = 1;
        //prints the first n posts
        while(temp!=NULL&&counter<=number){
            printf("%d- %s\n",counter,temp->content);
            temp = temp->next;
            counter++;
        }
        //only applies when there are more than 3 posts for that user
        if(counter>number){
            //keeps looping while the answer is y
            while((answer=='Y'||answer=='y')){
                counter2 = 1;
                printf("Do you want to display the next %d posts? (Y/N): ",number);
                scanf(" %c",&answer);
                if(answer=='Y'||answer=='y'){
                    //prints the next n posts, as long as there are most posts
                    while(temp!=NULL&&(counter2<=number)){
                        printf("%d- %s\n",counter,temp->content);
                        counter2++;
                        counter++;
                        temp = temp->next;
                    }
                }
                //ends the loop when there are no more posts
                if(temp==NULL){
                    answer = 'n';
                    printf("No more posts, returning to main menu\n");
                }
            }
        }
    }

   



}

/*
   ******** DONT MODIFY THIS FUNCTION ********
   Function that reads users from the text file.
   IMPORTANT: This function shouldn't be modified and used as is
   ******** DONT MODIFY THIS FUNCTION ********
*/
user_t *read_CSV_and_create_users(FILE *file, int num_users)
{
    srand(time(NULL));
    user_t *users = NULL;
    char buffer[500];
    fgets(buffer, sizeof(buffer), file); // Read and discard the header line
    int count = 0;
    for (int i = 0; i < num_users; i++)
    {
        fgets(buffer, sizeof(buffer), file);
        buffer[strcspn(buffer, "\r\n")] = 0; // Remove newline characters

        char *token = strtok(buffer, ",");
        char *token2 = strtok(NULL, ",");
        users = add_user(users, token, token2);
        char *username = token;

        token = strtok(NULL, ",");

        user_t *current_user = users;
        for (; current_user != NULL && strcmp(current_user->username, username) != 0; current_user = current_user->next)
            ;

        while (token != NULL && strcmp(token, ",") != 0 && count < 3)
        {
            if (strcmp(token, " ") != 0)
            {
                add_friend(current_user, token);
            }
            token = strtok(NULL, ",");
            count++;
        }
        count = 0;

        // token = strtok(NULL, ",");
        while (token != NULL && strcmp(token, ",") != 0)
        {
            add_post(current_user, token);
            token = strtok(NULL, ",");
        }
    }
    return users;
}


void teardown(user_t *users){
    friend_t *temp_friend;
    post_t *temp_post;
    user_t *temp_user;
    while(users!=NULL){
        //points to the user to delete
        temp_user = users;
        while(users->friends!=NULL){
            //points to the friend to delete
            temp_friend = users->friends;
            users->friends = users->friends->next;
            free(temp_friend);

        }
        while(users->posts!=NULL){
            //points to the post to delete
            temp_post = users->posts;
            users->posts = users->posts->next;
            free(temp_post);
        }
        users = users->next;
        free(temp_user);

    }
    users = NULL;
}





void print_menu(){
    printf("***********************************************\n");
    printf("              MAIN MENU                        \n");
    printf("***********************************************\n");
    printf("1. Register a new user\n");
    printf("2. Manage a user's profile (change password)\n");
    printf("3. Manage a user's posts (add/remove)\n");
    printf("4. Manage a user's friends (add/remove)\n");
    printf("5. Display a user's posts\n");
    printf("6. Exit\n");

}