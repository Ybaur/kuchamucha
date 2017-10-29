#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char* argv[])
{
    int pid, compile_status, iterator, fd1[2], fd2[2], check_status, test_amount, score = 0;
    char ch;
    char path_to_problem[30];
    sprintf(path_to_problem, "data/%s/%s.c", argv[1], argv[2]);
    test_amount = atoi(argv[3]);
    for (iterator = 1; iterator <= test_amount; iterator++)
    {
		char number_of_test[30];
		char ans_for_test[15];
		sprintf(ans_for_test, "test/%s/%03d.ans", argv[2], iterator);
		sprintf(number_of_test, "test/%s/%03d.data", argv[2], iterator);
    	pid = fork();
    	if (!pid)
        	execlp("gcc", "gcc", "-o", "var/aa", path_to_problem, NULL);
    	else
       		wait(&compile_status);
    	if (compile_status != 0)
	    	return 0;
    	pipe(fd1);
    	pid = fork();
    	if (!pid)
		{
        	dup2(fd1[1], 1);
	    	close(fd1[0]);
        	execlp("cat", "cat", number_of_test, NULL);
    	}
    	wait(NULL);
    	pipe(fd2);
    	pid = fork();
        if (!pid)
		{
	        dup2(fd1[0], 0);
	        dup2(fd2[1], 1);
	        close(fd2[0]);
            close(fd1[1]);
	        execlp("./var/aa", "./var/aa", NULL);
        }
	    wait(NULL);
        close(fd1[1]);
        close(fd1[0]);
        pid = fork();
        if (!pid)
		{
            dup2(fd2[0], 0);
	        close(fd2[1]);
            execlp("./checker", "./checker", ans_for_test,  NULL);
        }
	    wait(&check_status);
        if (check_status == 0)
            score++;
        close(fd2[0]);
        close(fd2[1]);
    }
    puts(argv[1]);
    puts(argv[2]);
    printf("Total score: %d/%s\n", score, argv[3]);
    return score;
}
