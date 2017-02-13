int test(char *rtr_cmd)
{
	int fd_files;

	while (--nb_red)
	{
		fd_files = open(file);
		ft_printf_fd(fd_files, "%s", rtr_cmd);
		close(fd_files);
	}
}
