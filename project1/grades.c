/*Zachary Meyers
  UID 120279096
  zmeyers3
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX_ASSIGNMENTS 50


/*Prototypes: */
double calculate_score(int score[], int assignment_weight[], int days_late[], int points_penalty, int num_assignments_dropped, int num_assignments);
double calculate_mean(int score[], int num_assignments, int days_late[], int points_penalty);
double calculate_sd(int score[], int num_assignments, int days_late[], int points_penalty);

/********************************************************/
/* The program prompts the user for assignment scores */
/* and grading information, and computes numerical.   */
/* grades and statistics, if requested by the user.  */
/***************************************************/

int main() {
    int points_penalty, num_assignments_dropped, num_assignments, i = 0, assignment_number, score[MAX_ASSIGNMENTS], assignment_weight[MAX_ASSIGNMENTS], days_late[MAX_ASSIGNMENTS], weight_sum = 0;
    char stats_yn;
    
    /* Read in values for all variables */
    scanf("%d %d %c %d", &points_penalty, &num_assignments_dropped, &stats_yn, &num_assignments);
    for(i = 0; i < num_assignments; i++) {
        scanf("%d, ", &assignment_number);
        scanf("%d, %d, %d", &score[assignment_number - 1], &assignment_weight[assignment_number - 1], &days_late[assignment_number - 1]);
    }
    /* Check that valid assignment weights were entered */
    for(i = 0; i < num_assignments; i++) {
        weight_sum += assignment_weight[i];
    }
    if(weight_sum != 100) {
        printf("ERROR: Invalid values provided\n");
        return -1;
    }
    /* Print out score and statistical information using helper fns */
    printf("Numeric Score: %5.4f\n",calculate_score(score, assignment_weight, days_late, points_penalty, num_assignments_dropped, num_assignments));
    printf("Points Penalty Per Day Late: %d\n", points_penalty);
    printf("Number of Assignments Dropped: %d\n", num_assignments_dropped);
    /* Iterate through all assignments to print out each assignment's info */
    printf("Values Provided:\nAssignment, Score, Weight, Days Late\n");
    for(i = 0; i < num_assignments; i++) {
        printf("%d, %d, %d, %d\n", (i + 1), score[i], assignment_weight[i], days_late[i]);
    }
    /* Only compute mean and SD if requested by user */
    if(stats_yn == 'y' || stats_yn == 'Y') {
        printf("Mean: %5.4f, Standard Deviation: %5.4f\n", calculate_mean(score, num_assignments, days_late, points_penalty), calculate_sd(score, num_assignments, days_late, points_penalty));
    }
    return 0;
}

/*************************************************/
/* calculate_score determines a numerical score */
/* to return taking into consideration       */
/* scores, assignment weights, days late,   */
/* late penaltes, and the number of dropped assignments. */
/******************************************/
double calculate_score(int score[], int assignment_weight[], int days_late[], int points_penalty, int num_assignments_dropped, int num_assignments) {
    double assn_values[MAX_ASSIGNMENTS], min_value, final_score = 0;
    int i, min_value_i = -1, total_weight = 100, idx_dropped_assignments[MAX_ASSIGNMENTS] = {0}, score_after_penalty[MAX_ASSIGNMENTS];
    /* Compute values for all assignments */
    for(i = 0; i < num_assignments; i++) {
        assn_values[i] = assignment_weight[i] * 0.01 * score[i];
    }
    /* Iteratively determine which assignments to drop,
    until there are no dropped assignments remaining */
    while(num_assignments_dropped > 0) {
        min_value = 101;
        for(i = 0; i < num_assignments; i++) {
            if((assn_values[i] < min_value) && idx_dropped_assignments[i] == 0) {
                min_value = assn_values[i];
                min_value_i = i;
            }
        }
        total_weight -= assignment_weight[min_value_i];
        idx_dropped_assignments[min_value_i] = 1;
        num_assignments_dropped--;
    }
    /* Determine scores after considering late penalty */
    for(i = 0; i < num_assignments; i++) {
        score_after_penalty[i] = score[i] - points_penalty * days_late[i];
        if(score_after_penalty[i] < 0) {
            score_after_penalty[i] = 0;
        }
    }
    
    /* Finally, determine which assignments to include in final calculation */
    for(i = 0; i < num_assignments; i++) {
        if(idx_dropped_assignments[i] == 0) {
            final_score += score_after_penalty[i] * 0.01 * assignment_weight[i];
        }
    }
    /* Return the score, weighted according to which assignments were dropped */
    return final_score * (100.0 / total_weight);
}

/******************************************/
/* calculate_mean returns the mean score */
/* on all assignments, taking into consideration */
/* the penalty for late assignments */
/******************************************/
double calculate_mean(int score[], int num_assignments, int days_late[], int points_penalty) {
    double mean = 0;
    int i;
    
    /* Sum all the assignment scores, minus their late penalties */
    for(i = 0; i < num_assignments; i++) {
        if((score[i] - points_penalty * days_late[i]) >= 0) {
            mean += (score[i] - points_penalty * days_late[i]);
        }
    }
    return mean / num_assignments;
}

/******************************************/
/* calculate_sd returns the standard deviation */
/* on all assignments, taking into consideration */
/* the penalty for late assignments */
/******************************************/
double calculate_sd(int score[], int num_assignments, int days_late[], int points_penalty) {
    double mean = calculate_mean(score, num_assignments, days_late, points_penalty), differences[MAX_ASSIGNMENTS] = {0}, variance;
    int i;
    
    /* Sum all the assignment scores, minus their late penalties */
    for(i = 0; i < num_assignments; i++) {
        if((score[i] - (points_penalty * days_late[i])) >= 0) {
        differences[i] = ((score[i] - (points_penalty * days_late[i])) - mean) * ((score[i] - (points_penalty * days_late[i])) - mean);
        }
    }
    /* Compute the variance */
    for(i = 0; i < num_assignments; i++) {
        variance += differences[i];
    }
    /* Divide variance by number of assignments */
    variance = variance / num_assignments;
    return sqrt(variance);
}
