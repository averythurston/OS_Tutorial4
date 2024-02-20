/*
 * Tutorial 4 Jeopardy Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "questions.h"
#include "players.h"
#include "jeopardy.h"

// Put macros or constants here using #define
#define BUFFER_LEN 256
#define NUM_PLAYERS 4

// Put global environment variables here

// Processes the answer from the user containing what is or who is and tokenizes it to retrieve the answer.
void tokenize(char *input, char **tokens){
    int token_count = 0;

    char *token = strtok(input, " ");
    while (token != NULL) {
        tokens[token_count] = malloc(strlen(token) + 1);
        if (tokens[token_count] == NULL) {
            perror("Failed to allocate memory");
            exit(EXIT_FAILURE);
        }

        strcpy(tokens[token_count], token);

        token = strtok(NULL, " ");
        token_count++;
    }

    tokens[token_count] = NULL;
}


// Displays the game results for each player, their name and final score, ranked from first to last place
void show_results(player *players, int num_players){
    for (int i = 0; i < num_players - 1; i++) {
        for (int j = 0; j < num_players - i - 1; j++) {
            if (players[j].score < players[j + 1].score) {
                player temp = players[j];
                players[j] = players[j + 1];
                players[j + 1] = temp;
            }
        }
    }

    printf("\nScoreboard:\n");
    for (int i = 0; i < num_players; i++) {
        printf("Rank %d: %s - Score: %d\n", i + 1, players[i].name, players[i].score);
    }
    printf("\n");
}

bool is_game_over(void) {
    for (int i = 0; i < NUM_CATEGORIES; i++) {
        for (int j = 0; j < NUM_VALUES; j++) {
            if (!questions[i][j].answered) {
                return false;
            }
        }
    }
    return true;
}

int main(int argc, char *argv[])
{
    // An array of 4 players, may need to be a pointer if you want it set dynamically
    player players[NUM_PLAYERS];
    
    // Input buffer and and commands
    char buffer[BUFFER_LEN] = { 0 };

    // Display the game introduction and initialize the questions
    initialize_game();

    // Prompt for players names
    printf("Enter the names of the players:\n");
    for (int i = 0; i < NUM_PLAYERS; i++) {
        printf("Player %d: ", i + 1);
        scanf("%s", players[i].name);
        players[i].score = 0;
    }
    // initialize each of the players in the array

    // Perform an infinite loop getting command input from users until game ends
    while (fgets(buffer, BUFFER_LEN, stdin) != NULL)
    {
        // Call functions from the questions and players source files
        display_categories();

        // Execute the game until all questions are answered
        printf("Enter player name to select a question: ");
        char selected_player[50];
        scanf("%s", selected_player);
        getchar();

        if (!player_exists(players, NUM_PLAYERS, selected_player)) {
            printf("Invalid player!\n");
            continue;
        }

        char selected_category[50];
        int selected_value;
        printf("Enter category and dollar amount: ");
        scanf("%s %d", selected_category, &selected_value);
	

        display_question(selected_category, selected_value);

        char answer[BUFFER_LEN];
        
        if (already_answered(selected_category, selected_value) == true)
        	printf("This question been answered!\n");
        else {
        	printf("Enter your answer: ");
		    scanf("%s", answer);
		    strtok(answer, "\n");  
        	if (valid_answer(selected_category, selected_value, answer)) {
		        printf("Correct!\n");
		        update_score(players, NUM_PLAYERS, selected_player, selected_value);
        	} else {
            	printf("Incorrect!\n");
        	}
        }
        
        if (is_game_over()) {
        	printf("Congrats Player: %s Thanks for playing!", players[0].name);
        	show_results(players, NUM_PLAYERS);
            break;
        }
        show_results(players, NUM_PLAYERS);
    }

    return EXIT_SUCCESS;
}
