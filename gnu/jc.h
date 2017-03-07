
/* A process is a single process.  */
typedef struct		s_process
{
	struct process	*next;			/* next process in pipeline */
	char			**argv;			/* for exec */
	pid_t			pid;			/* process ID */
	char			completed;		/* true if process has completed */
	char			stopped;		/* true if process has stopped */
	int				status;			/* reported status value */
}					t_process;

/* A job is a pipeline of processes.  */
typedef struct		s_job
{
	struct job		*next;			/* next active job */
	char			*command;		/* command line, used for messages */
	process			*first_process;	/* list of processes in this job */
	pid_t			pgid;			/* process group ID */
	char			notified;		/* true if user told about stopped job */
	struct termios	tmodes;			/* saved terminal modes */
	int				stdin, stdout, stderr;  /* standard i/o channels */
}					t_job;

/* The active jobs are linked into a list.  This is its head.   */
job *first_job = NULL;
