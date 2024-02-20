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
#include "questions.h"

question questions[NUM_QUESTIONS][NUM_VALUES];

// Initializes the array of questions for the game
void initialize_game(void)
{
    // initialize each question struct and assign it to the questions array
    for (int i = 0; i < NUM_CATEGORIES; i++) {
        for (int j = 0; j < NUM_VALUES; j++) {
            question q;
            sprintf(q.category, "Category %d", i + 1);
            sprintf(q.question, "Question %d worth $%d what is %d + %d ?\n", i + 1, (j + 1) * 100, i, j);
            sprintf(q.answer, "%d" ,i + j);
            q.value = (j + 1) * 100;
            q.answered = false;
            questions[i][j] = q;
        }
    }
}

// Displays each of the remaining categories and question dollar values that have not been answered
void display_categories(void)
{
    // print categories and dollar values for each unanswered question in questions array
    printf("Remaining Categories and Question Dollar Values:\n");
    for (int i = 0; i < NUM_CATEGORIES; i++) {
        for (int j = 0; j < NUM_VALUES; j++) {
            if (!questions[i][j].answered) {
                printf("%s: $%d\t", questions[i][j].category, questions[i][j].value);
            }
        }
        printf("\n");
    }
}

// Displays the question for the category and dollar value
void display_question(char *category, int value)
{	
	value = value / 100 -1;
	int cat = atoi(category) - 1;
	printf("%s", questions[cat][value].question);
    printf("Answer: %s\n", questions[cat][value].answer);
}

// Returns true if the answer is correct for the question for that category and dollar value
bool valid_answer(char *category, int value, char *answer)
{
	value = value / 100 -1;
	int cat = atoi(category) - 1;
	if (strcmp(questions[cat][value].answer, answer) == 0) {
		questions[cat][value].answered = true;
		return true;
	} else {
		return false;
	}
}


// Returns true if the question has already been answered
bool already_answered(char *category, int value)
{	
	value = value / 100 -1;
	int cat = atoi(category) - 1;
    return questions[cat][value].answered;
}
