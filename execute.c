

int change_input_fd(t_handler *handler)
{
	if (handler->infile_paths)
		change_input_infile(handler->infile_path);
		// if (infile) //ファイルからread
		// in_fd = open(infile)
		// dup2(in_fd, stdIN)
		// close(in_fd)
		// close(prev_pipe_in)
	else
	{
		if (handler->prev_pipe_in_fd != STDIN_FILENO)
			dup2(handler->prev_pipe_in_fd, STDIN_FILENO);
		close(handler->prev_pipe_in_fd);
	}
}


int change_output_fd(t_handler *handler, int pipe_out_fd)
{
	if (handler->outfile_paths)
		change_output_infile(handler->outfile_path, pipe_out_fd);
		// if (outfile) //ファイルへwrite
		// out_fd = open(outfile)
		// dup2(out_fd, stdOUT)
		// close(out_fd)
		// close(pipe_out)
	else
	{
		if (handler->last_cmd_flag != TRUE)
			dup2(pipe_out_fd, STDOUT_FILENO);
		close(pipe_out_fd);
	}
}

void update_prev_pipe_in_fd()
{
	
}


int execute(t_handler *handler)
{
	int		pipe_fd[2];
	pid_t	pid;

	if (pipe(pipe_fd) == -1)
		return (1);
	pid = fork();
	if (pid == -1)
		return (1);
	else if (pid == 0)
	{
		//----------子プロセスで実行----------
		printf("子プロセス\n");
	}
	else
	{
		printf("親プロセス\n");
		if (handler->prev_pipe_in_fd != STDIN_FILENO)
			close(handler->prev_pipe_in_fd)
		if (handler->last_cmd_flag != TRUE)
			handler->prev_pipe_in_fd = pipe_fd[IN];
		else
			close(pipe_fd[IN]);
		close(pipe_fd[OUT]);

	}
	

	close(pipe_out)
	close(prev_pipe_in)
	prev_pipe_in = pipe_in
	// dup2(tmp_STDOUT, stdOUT)
}