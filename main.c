/********* main.c ********
    Dorian Bansoodeb 
*/

// Includes go here
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "a2_nodes.h"
#include "a2_functions.h"
#define USERNAME_LENGTH 30
#define PASSWORD_LENGTH 15

int main()
{
    char username[USERNAME_LENGTH];
    char password[PASSWORD_LENGTH];
    FILE *csv_file = fopen("user_details.csv", "r");
    if (csv_file == NULL)
    {
        perror("Error opening the CSV file");
        return 1;
    }
    // Parse CSV data and create users
    user_t *users = read_CSV_and_create_users(csv_file, 50);
    int choice = 1;
    fclose(csv_file);
    //keeps looping uptil choice is 6 (ends program)
    while(choice!=6){
        
    
        print_menu();
        printf("Enter a choice:");
        scanf("%d",&choice);
        //ensures the choice is between 1-6 inclusive
        while(choice<=0||choice>=7){
            printf("Incorrect input, enter a correct value:");
            scanf("%d",&choice);
        }

        if (choice==1){
            printf("Enter a username:");
            scanf("%s",username);
            printf("Enter an up to 15 character password:");
            scanf("%s",password);
            users = add_user(users, username,password);
            printf("***User Added!***\n");
            
            
        }
        if (choice == 2){
            _Bool in_list = 0;
            printf("Enter username to update their password:");
            scanf("%s",username);
            
            user_t *found = find_user(users,username);
            
            if (found==NULL){
                printf("User not found\n");
            }
            else{
                printf("Enter the old password:");
                scanf("%s",password);
                if(strcmp(found->password,password)==0){
                    printf("Enter new password:");
                    scanf("%s",password);
                    strcpy(found->password,password);
                }
                else{
                    printf("Incorrect Password\n");
                }
                

            }
        }
        if (choice == 3){
            printf("Enter a username to manage their posts: ");
            scanf("%s",username);
            user_t *found = find_user(users,username);
            if (found==NULL){
                printf("User not found, returning to main menu\n");
            }
            else{
                printf("Enter password:");
                scanf("%s",password);
                if(strcmp(found->password,password)==0){
                    int pick =1;
                    //keeps looping until they pick 3
                    while(pick!=3){
                        printf("%s's posts\n\n",found->username);
                        if(found->posts==NULL){
                            printf("No posts\n");
                        }
                        else{
                            display_all_user_posts(found);
                        }
                        printf("Please choose a number:\n");
                        printf("1- Add a new post\n");
                        printf("2- Remove a post\n");
                        printf("3- Return to main menu\n");
                        printf("Enter your choice:");
                        
                        scanf("%d",&pick);
                        //pick must be between 1-3 inclusive
                        while(pick<1||pick>3){
                            printf("Enter a valid choice:");
                            scanf("%d",pick);
                        }
                        if (pick==1){
                            printf("Enter your post content:");
                            char content[250];
                            scanf(" %[^\n]s",content);
                            add_post(found,content);
                        }
                        else if (pick==2){
                            _Bool delete = delete_post(found);
                            if(delete==1){
                                printf("Successfully Deleted Post");
                            }
                        }
                    }
                    
                }
                else{
                    printf("Incorrect Password\n");
                }
            }
        }
        if (choice == 4){
            printf("Enter the username to update their friends: ");
            scanf("%s",username);
            user_t *found = find_user(users,username);
            if(found==NULL){
                printf("Username not found");
            }
            else{
                int pick = 1;
                while(pick!=3){
                    printf("Managing %s's friends\n",found->username);
                    printf("1- Add a new friend\n");
                    printf("2- Remove a friend\n");
                    printf("3- Return to the main menu\n");
                    printf("Enter your choice");
                    
                    scanf("%d",&pick);
                    while(pick<1||pick>3){
                        printf("Please enter a vaid choice:");
                        scanf("%d",&pick);
                    }
                    if(pick == 1){
                        printf("Enter your new friend's name:");
                        scanf("%s",username);
                        add_friend(found,username);
                        printf("Friend successfully added\n");
                    }
                    else if(pick ==2){
                        printf("List of %s's friends:\n",found->username);
                        display_user_friends(found);
                        friend_t *temp2 = found->friends;
                        char delete_friends[30];
                        _Bool is_friend = 0;
                        int first =0;


                        printf("Enter a friend's name to delete: ");
                        scanf("%s",delete_friends);
                        
                        while(is_friend==0){
                            if(first!=0){
                                printf("Incorrect friend");
                                printf("Enter a friend's name to delete:");
                                scanf("%s",delete_friends);
                            }
                            first++;
                            while(temp2!=NULL){
                                if(strcmp(delete_friends,temp2->username)==0){
                                    is_friend = 1;
                                    if(delete_friend(found, delete_friends)==1){
                                        printf("Friend Deleted\n");
                                    }
                                }
                                temp2 = temp2->next;
                            }
                            temp2 = found->friends;

                        }
                    }
                    else if(pick == 3){
                        printf("Returning to Main Menu:\n");
                    }
                }
                
            }

        }
        if(choice == 5){
            display_posts_by_n(users,3);
        }
        if(choice == 6){
            //teardown all the memory allocated
            printf("Goobye!\n");
            teardown(users);
            users = NULL;
        }
    }    
}