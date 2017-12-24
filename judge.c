#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <string.h>
int check_test(void){
    DIR *dir;
    FILE *stream;
    struct dirent *entry;
	FILE *info = fopen("test/info.txt", "w");
    int count_problems = 0, i;
	dir = opendir("test");
    if (!dir)
	{
        perror("diropen");
        exit(1);
    }
    while ((entry = readdir(dir)) != NULL)
		count_problems++;
    count_problems -= 3;
    closedir(dir);
    stream = fopen("test/info.txt", "w");
    fprintf(stream, "%d\n", count_problems);
    for (i = 0; i < count_problems; i++)
	{
		char index_of_test[10];
		sprintf(index_of_test, "test/%02d", i + 1);
        dir = opendir(index_of_test);
        int count2 = 0;
        while ((entry = readdir(dir)) != NULL)
    		count2++;
        closedir(dir);
        count2 -= 2;
        count2 /= 2;
        fprintf(stream, "%d %d\n", i + 1, count2);
    }
    fclose(stream);
	return count_problems;
}
int check_data(void){
	int i, count_users = 0;
	DIR *dir;
    FILE *stream;
    struct dirent *entry;
	FILE *info = fopen("data/info.txt", "w");
	dir = opendir("data");
    if (!dir)
	{
        perror("diropen");
        exit(1);
    }
	while ((entry = readdir(dir)) != NULL)
		count_users++;
    count_users -= 3;
    closedir(dir);
    stream = fopen("data/info.txt", "w");
    fprintf(stream, "%d\n", count_users);
	for (i = 1; i <= count_users; i++)
	{
		char index_of_user[15];
		int k;
		DIR *dir2 = opendir("data");
		struct dirent *qu;
 		for (k = 1; k <= i; k++){
            (qu = readdir(dir2));
            if (strcmp(qu -> d_name, "info.txt") == 0 || strcmp(qu -> d_name, ".") == 0 || strcmp(qu -> d_name, "..") == 0)
                k--;
		}
		dir = opendir(index_of_user);
        int count2 = 0;
        while ((entry = readdir(dir)) != NULL)
    		count2++;
        closedir(dir);
        count2 -= 2;
        fprintf(stream, "%d %d\n", i, count2);
    }
    fclose(stream);
	return count_users;
}
int main(void)
{
	int i;
    DIR *dir;
    FILE *stream;
    FILE *f3;
    struct dirent *entry;
    int count_users, count_problem_tests, count_problems = 0, j, count_user_problems, status3;
    char tch1, tch2,ch1, ch2;
    count_problems = check_test();
	count_users = check_data();
    f3 = fopen("output.txt", "w");
	for (i = 1; i <= count_users; i++)
	{
        FILE *f = fopen("data/info.txt", "r");
        ch1 = '^';
        int k, num;
		char chacha;
		fscanf(f, "%d\n", &num);
        for (k = 1; k <= i; k++)
			fscanf(f, "%d %d\n", &num, &count_user_problems);
		dir = opendir("data");
		for (k = 1; k <= i; k++){
			(entry = readdir(dir));
			if (strcmp(entry -> d_name, "info.txt") == 0 || strcmp(entry -> d_name, ".") == 0 || strcmp(entry -> d_name, "..") == 0)
				k--;
		}
        fprintf(f3, "%s ", entry->d_name);
		for (j = 1; j <= count_problems; j++)
		{
            FILE *f1 = fopen("test/info.txt", "r");
            tch1 = '^';
			fscanf(f1, "%d\n", &num);
            for (k = 1; k <= j; k++)
            	fscanf(f1, "%d %d\n", &num, &count_problem_tests);
			char name_of_user[10];
			sprintf(name_of_user, "%s", entry -> d_name);
			char number_of_tests[20];
			sprintf(number_of_tests, "%d", count_problem_tests);
			char problem_number[20];
			sprintf(problem_number, "%02d", j);
			char problem_path[20];
		    sprintf(problem_path, "data/%s/%02d.c",entry -> d_name, j);
			FILE *f2 = fopen(problem_path, "r");
		    if (f2 == 0)
			{
				fprintf(f3, "%d/%d ", 0, count_problem_tests);
	        	continue;
	    	}
            int pid;
            if ((pid = fork()) == 0)
                execlp("./judge_unit", "./judge_unit", name_of_user, problem_number, number_of_tests, NULL);
            else
                wait(&status3);
	    	fprintf(f3, "%d/%d ", status3 / 256, count_problem_tests);
		}
		fprintf(f3, "%c", '\n');
    }
    return 0;
}
