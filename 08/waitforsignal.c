#include "csapp.h"

volatile sig_atomic_t pid;

void sigchld_handler(int s)
{
	int olderrno = errno;
	pid = waitpid(-1, NULL, 0);
	errno = olderrno;
}

void sigint_handler(int s)
{
}

int main(int argc, char **argv)
{
	sigset_t mask, prev;

	Signal(SIGCHLD, sigchld_handler);
	Signal(SIGINT, sigint_handler);
	Sigemptyset(&mask);
	Sigaddset(&mask, SIGCHLD);

	while(1)
	{
		Sigprocmask(SIG_BLOCK, &mask, &prev);	/* Block SIGCHLD */
		if(Fork() == 0)	/* Child */
		{
			printf("child pid is %d\n", getpid());
			Signal(SIGINT, SIG_DFL);
			//exit(0);
		}
		/* Parent */
		pid = 0;
		/* Wait for SIGCHLD to be received (wasteful) */
		while(!pid)
			sigsuspend(&prev);

		/* Optionally unblock SIGCHLD */
		Sigprocmask(SIG_SETMASK, &prev, NULL);

		/* Do some work after recviving SIGCHLD */
		printf("child %d is killed, fork a new one\n", pid);
	}

	exit(0);
}
