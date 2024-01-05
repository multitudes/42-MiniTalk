typedef void (*sighandler_t)(int);

void	handler(int sig)
{
	if (sig == SIGINT) {
	/* code */
		printf("SIGINT!! %d\n", sig);
	} 
	else if (sig == SIGQUIT)
	{
		printf("SIGQUIT!! %d\n", sig);
	}
}

int	main(void)
{
	
	printf("server\n");
	sleep(5);
	void(*oldHandler)(int);
	oldHandler = signal(SIGINT, handler);
	signal(SIGQUIT, handler);
	if (oldHandler == SIG_ERR)
		return(1);
	for (int i = 0; i < 5; i++)
	{
		printf("%d\n",i);
		sleep(2);
	}
	if (signal(SIGINT, oldHandler) == SIG_ERR) 
		return(1);
	if (signal(SIGQUIT, SIG_DFL) == SIG_ERR) 
		return(1);
	printf("done\n");
	sleep(5);
	
	return (0);
}