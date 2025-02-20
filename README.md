Social Network Simulation

Overview

This project is a simple social network simulation implemented in C. It allows users to register, manage their profiles, add and remove friends, create and delete posts, and display posts in a structured manner.

Files

main.c - The main source file containing the core functionality of the program, including user management, friend connections, and post handling.

a2_nodes.h - Header file defining the data structures used in the program.

a2_functions.h - Header file declaring function prototypes for handling users, friends, and posts.

a2_functions.c - Source file implementing the functions declared in a2_functions.h.

users.csv - A sample data file containing predefined users, friends, and posts to initialize the system.

Features

User Management:

Register new users with a username and password.

Search for existing users.

Change user passwords.

Friend Management:

Add friends in alphabetical order.

Display a user's friend list.

Remove friends from the list.

Post Management:

Users can create posts.

Display a user's posts.

Delete a user's posts.

Display posts in a paginated manner.

Compilation and Execution

To compile the program, use the following command:

gcc -o social_network main.c a2_functions.c -I.

To run the program:

./social_network

CSV File Format (users.csv)

The CSV file contains predefined users along with their friends and posts. The format is as follows:

username,password,friend1,friend2,friend3,post1,post2,post3

Example:

john_doe,password123,jane_doe,bob_smith,alice_wonder,hello world,Happy coding!

Memory Management

The teardown function ensures proper deallocation of memory, preventing memory leaks by freeing dynamically allocated users, friends, and posts before the program exits.

Notes

The program ensures alphabetical ordering for users and friends.

Users can only add up to 3 friends initially from the CSV file.

Posts follow a stack-like structure, where the most recent post appears first.

If a user has many posts, the program displays them in a paginated format, prompting the user if they want to see more.

Author

Dorian Bansoodeb
