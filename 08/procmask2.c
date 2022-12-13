void handler(int sig)
{
	int olderrno = errno;
	sigset_t mask_all. prev_all;
	pid_t pid;

	Sigfillset(&mask_all);
	while((pid = waitpid(-1, NULL, 0)) > 0)/* Reap a zombie child */
	{
		Sigprocmask(SIG_BLOCK, &mask_all, &prev_all);
		deletejob(pid);	/* Delete the child from the job list */
		Sigprocmask(SIG_SETMASK, &prev_all, NULL);
	}

	if(errno != ECHILD)
		Sio_error("waitpid error");
	errno = olderrno;
}

int main(int argc, char **argv)
{
	int pid;
	sigset_t mask_all, mask_one, prev_one;

	Sigfillset(&mask_all);
	Sigempty(&mask_one);
	Sigaddset(&mask_one, SIGCHLD);
	Signal(SIGCHLD, handler);
	initjobs();	/* Initialize the job list */

	while(1)
	{
		Sigprocmask(SIG_BLOCK, &mask_one, &prev_one)
		if((pid = Fork()) == 0)/* Child process */
		{
			Sigprocmask(SIG_SETMASK, &prev_one, NULL);
			Execve("/bin/date", argv, NULL);
		}

		Sigprocmask(SIG_BLOCK, &mask_all, NULL);	/* Parent process */
		addjob(pid);		/* Add the child to the job list */
		Sigprocmask(SIG_SETMASK, &prev_one, NULL);
	}
	exit(0);
}
