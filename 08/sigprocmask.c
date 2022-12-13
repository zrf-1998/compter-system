void my_sigprocmask()
{
	sigset_t mask, prev_mask;

	Sigemptyset(&mask);
	Sigaddset(&mask, SIGINT);

	/* Block SIGINT and save previous blocked set */
	Sigprocmask(SIG_BLOCK, &mask, &prev_mask);

	/* Code region that will not be interrupted by SIGINT */

	/* Restore previous blocked set, unblocking SIGINT */
	Sigprocmask(SIG_SETMASK, &prev_mask, NULL);
}
