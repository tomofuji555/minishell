
<試し書き>
<1回目>
pipefd生成　//pipe_in pipe_out

一旦保存
tmp_in = dup(stdIN);
tmp_out = dup(stdOUT);

行き先を変える
dupe2(infile_fd, stdIN) 
close(infile_fd) 
dup2(pipe1_out, stdOUT) 
close(pipe1_out)

forkし、子プロセス　実行
pipe1_inはそのまま

<2回目> //IN= infile_fd OUT = pipe1_out　pipe1_inはそのまま
再度pipefd生成

dup2(pipe1_in, stdIN) 
close(pipe1_in)
dup2(pipe2_out, stdOUT) 
close(pipe_out);

pipe2_inはそのまま

<3回目>//IN= pipe1_fd OUT = pipe2_out　pipe2_inはそのまま
....



	
<case1>	//そもそも親で実行しない
//----------子プロセス----------
if (infile) //ファイルからread
	in_fd = open(infile)
	dup2(in_fd, stdIN)
	close(in_fd)
	close(prev_pipe_in)
else
	if(i != 1) //prev_pipe_in == -1 //パイプからread
		dup2(prev_pipe_in, stdIN)
		close(prev_pipe_in) 
	else
		close(prev_pipe_in) 

//書き込む側
if (outfile) //ファイルへwrite
	out_fd = open(outfile)
	dup2(out_fd, stdOUT)
	close(out_fd)
	close(pipe_out)
else
	if(i != last) //last_flag != true //パイプへwite
		dup2(pipe_out, stdOUT) 
		close(pipe_out) 
	else 
		close(pipe_out) 
//----------子プロセスで実行----------

//----------親プロセス----------
close(pipe_out)
close(prev_pipe_in)
prev_pipe_in = pipe_in
dup2(tmp_STDOUT, stdOUT)

	
	
<case2> //ダメ		
//----------子プロセス----------
	if (infile) //ファイルからread
		in_fd = open(infile);
	else
		if(i != 1) //パイプからread
			in_fd = prev_pipe_in;
	//書き込む側
	if (outfile) //ファイルへwrite
		out_fd = open(outfile);
	else
		if(i != last) //パイプへwite
			out_fd = pipe_out;
	//方向を変える
	dup2(in_fd, stdIN);
	close(in_fd);
	dup2(out_fd, stdIN);
	close(out_fd);

//----------親プロセス----------
	prev_pipe_in = pipe_in
	dup2(tmp_STDOUT, stdOUT)
}