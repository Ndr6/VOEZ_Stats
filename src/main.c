/*
** NDR PROJECT, 2018
** VOEZ Stats calcuator
*/

#include "my.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct stats_s {
	unsigned int songs_done;
	unsigned int songs_total;
	unsigned int songs_ap;
	unsigned int songs_fc;
	unsigned int total_score;
} stats_t;

typedef struct adv_stats_s {
	float compl_per;
	float fc_per;
	float ap_per;
	float tfc_per;
	float tap_per;
	unsigned int score_avg;
	char grade_avg;
	unsigned int played_max_score;
	unsigned int max_score;
} adv_stats_t;

char get_grade(unsigned int score)
{
	if (score > 1000000)
		return '0';
	else if (score >= 950000)
		return 'S';
	else if (score >= 880000)
		return 'A';
	else if (score >= 780000)
		return 'B';
	else
		return 'C';
}

adv_stats_t adv_stats_calc(stats_t *st)
{
	adv_stats_t ad_st;
	ad_st.compl_per = (st->songs_done * 10000.0) / (st->songs_total) / 100.0;
	ad_st.fc_per = (st->songs_fc * 10000.0) / (st->songs_done) / 100.0;
	ad_st.ap_per = (st->songs_ap * 10000.0) / (st->songs_done) / 100.0;
	ad_st.tfc_per = (st->songs_fc * 10000.0) / (st->songs_total) / 100.0;
	ad_st.tap_per = (st->songs_ap * 10000.0) / (st->songs_total) / 100.0;
	ad_st.score_avg = st->total_score / st->songs_done;
	ad_st.grade_avg = get_grade(ad_st.score_avg);
	ad_st.played_max_score = st->songs_done * 1000000;
	ad_st.max_score = st->songs_total * 1000000;
	return ad_st;
}

stats_t get_stats(void)
{
	stats_t stats;
	my_putstr("Enter the number of \x1B[32mfinished songs\x1B[0m : ");
	stats.songs_done = atoi(get_next_line(0));
	my_putstr("\nEnter the \x1B[32mtotal number of songs\x1B[0m : ");
	stats.songs_total = atoi(get_next_line(0));
	my_putstr("\nEnter the number of \x1B[33mAll Perfect songs\x1B[0m : ");
	stats.songs_ap = atoi(get_next_line(0));
	my_putstr("\nEnter the number of \x1B[36mFull Combo songs\x1B[0m : ");
	stats.songs_fc = atoi(get_next_line(0));
	my_putstr("\nEnter your \x1B[32mtotal score\x1B[0m : ");
	stats.total_score = atoi(get_next_line(0));
	return stats;
}

int test_stats(stats_t *st)
{
	if (st->songs_done == 0 || st->songs_total == 0 || st->total_score == 0){
		printf("\x1B[31mYou should play at least one song.\x1B[0m\n");
		return 0;
	}
	if (st->songs_done > st->songs_total){
		printf("\x1B[31mYou shouldn't be able to complete more songs than there is !\x1B[0m\n");
		return 0;
	}
	if (st->songs_ap > st->songs_done || st->songs_fc > st->songs_done){
		printf("\x1B[31mYou shouldn't be able to do more FC or AP than completed songs !\x1B[0m\n");
		return 0;
	}
	if (st->total_score > st->songs_done * 1000000){
		printf("\x1B[31mYou shouldn't be able do score that much !\x1B[0m\n");
		return 0;
	}
	return 1;
}

void print_stats(stats_t *st, adv_stats_t *ast)
{
	printf("\n\nHere are the results :\n\n");
	printf("Songs completed : %i/%i (%.2f%%)\n\n",
	       st->songs_done, st->songs_total, ast->compl_per);
	printf("All Perfect songs : %i (%.2f%% of played, %.2f%% of total)\n\n",
	       st->songs_ap, ast->ap_per, ast->tap_per);
	printf("Full Combo songs : %i (%.2f%% of played, %.2f%% of total)\n\n",
	       st->songs_fc, ast->fc_per, ast->tfc_per);
	printf("Total score : %i out of %i (played) or %i (total)\n\n",
	       st->total_score, ast->played_max_score, ast->max_score);
	printf("Average score : %i\tGrade : %c\n",
	       ast->score_avg, ast->grade_avg);
}

int main(int ac, char **av)
{
	stats_t stats = get_stats();
	while (test_stats(&stats) == 0)
		stats = get_stats();
	adv_stats_t adv_stats = adv_stats_calc(&stats);
	print_stats(&stats, &adv_stats);
}
