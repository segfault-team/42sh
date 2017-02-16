srcs/builtins/ft_chdir.c:	ft_setenv(&e->env, "OLDPWD", oldpwd);
srcs/builtins/ft_chdir.c:	ft_setenv(&e->env, "PWD", pwd);
srcs/builtins/ft_chdir.c:	if (e->cmd_len > 2)
srcs/builtins/ft_chdir.c:	if (e->cmd_len == 1)
srcs/builtins/ft_chdir.c:		if (!ft_issetenv(e->env, "HOME") && e->home == NULL)
srcs/builtins/ft_chdir.c:		return (ft_chdir_env(e, e->home));
srcs/builtins/ft_chdir.c:	if (ft_strequ(e->cmd[1], "-"))
srcs/builtins/ft_chdir.c:		strfree(&e->cmd[1]);
srcs/builtins/ft_chdir.c:		if ((e->cmd[1] = ft_getenv(e->env, "OLDPWD")) == NULL)
srcs/builtins/ft_chdir.c:	return (ft_chdir_env(e, e->cmd[1]));
srcs/builtins/ft_echo.c:	if ((nl = ft_strequ(e->cmd[1], "-n")))
srcs/builtins/ft_echo.c:	while (e->cmd[++i])
srcs/builtins/ft_echo.c:		if ((!nl && i == 2) || (i > 2 && i < (int)e->cmd_len))
srcs/builtins/ft_echo.c:		ft_putstr_fd(e->cmd[i], 1);
srcs/builtins/ft_env.c:	while (++len < e->cmd_len && ft_strchr(e->cmd[len], '='))
srcs/builtins/ft_env.c:		if (e->cmd[i][0] == '=')
srcs/builtins/ft_env.c:			return (ft_error("env", "invalid argument", e->cmd[i]));
srcs/builtins/ft_env.c:		if (!ft_arg_isdouble(e->cmd, e->cmd[i], i))
srcs/builtins/ft_env.c:			ptr[j] = ft_strdup(e->cmd[i]);
srcs/builtins/ft_env.c:	if (len == e->cmd_len)
srcs/builtins/ft_env.c:	while (++i < (int)e->cmd_len && e->cmd[i] && e->cmd[i][0] == '-')
srcs/builtins/ft_env.c:		if (e->cmd[i][1] == 'u' && e->cmd[i + 1])
srcs/builtins/ft_env.c:			ft_unsetenv(env_cpy, e->cmd[i + 1]);
srcs/builtins/ft_env.c:		else if (e->cmd[i][1] == 'i')
srcs/builtins/ft_env.c:			ft_error("env", "illegal option --", &e->cmd[i][1]);
srcs/builtins/ft_env.c:	if (i == (int)e->cmd_len)
srcs/builtins/ft_env.c:	env_cpy = ft_tabdup(e->env);
srcs/builtins/ft_env.c:	if (e->cmd_len > 1)
srcs/builtins/ft_env.c:			ft_exec(&e->cmd[i], e);
srcs/builtins/ft_env.c:		ft_puttab(e->env);
srcs/builtins/ft_exit.c:	if (e->cmd && e->cmd[1])
srcs/builtins/ft_exit.c:		e->exit = ft_atoi(e->cmd[1]);
srcs/builtins/ft_exit.c:		e->exit = 0;
srcs/builtins/ft_exit.c://	if (e->cmd[1])
srcs/builtins/ft_exit.c:	e->x = 0;
srcs/builtins/ft_history.c:	ft_store_history(e->line);
srcs/builtins/ft_history.c:		i = ft_tablen(e->history);
srcs/builtins/ft_history.c:		if (!ft_strcmp(e->history[i], e->line))
srcs/builtins/ft_history.c:			tmp = e->history;
srcs/builtins/ft_history.c:			e->history = ft_tabcat(e->history, e->line);
srcs/builtins/ft_history.c:	else if (e->history)
srcs/builtins/ft_history.c:		ft_free_tab(e->history);
srcs/builtins/ft_history.c:		e->history = NULL;
srcs/builtins/ft_history.c:**		e->history TAB
srcs/builtins/ft_history.c:	if ((e->history = malloc(sizeof(e->history) * 4096)) == NULL)
srcs/builtins/ft_history.c:	while (get_next_line(fd, &e->history[i]) > 0)
srcs/builtins/ft_history.c:	e->history[i] = NULL;
srcs/builtins/ft_history.c:	if (e->history)
srcs/builtins/ft_history.c:		while (e->history[++i])
srcs/builtins/ft_history.c:			ft_printf("%d: %s\n", (i + 1), e->history[i]);
srcs/builtins/ft_reset.c:	if (e->line)
srcs/builtins/ft_reset.c:		strfree(&e->line);
srcs/builtins/ft_reset.c:	e->tcaps.nb_move = 0;
srcs/builtins/ft_reset.c:	e->tcaps.nb_read = 0;
srcs/builtins/ft_setenv.c:	if (e->cmd_len == 3)
srcs/builtins/ft_setenv.c:		if (ft_isalpha_str(e->cmd[1]))
srcs/builtins/ft_setenv.c:			if (!ft_issetenv(e->env, "HOME") && e->home == NULL && \
srcs/builtins/ft_setenv.c:					ft_strequ(e->cmd[1], "HOME"))
srcs/builtins/ft_setenv.c:				e->home = ft_strdup(e->cmd[2]);
srcs/builtins/ft_setenv.c:			return (ft_setenv(&e->env, e->cmd[1], e->cmd[2]));
srcs/builtins/ft_unsetenv.c:	if (e->cmd_len > 1)
srcs/builtins/ft_unsetenv.c:		while (++i < (int)e->cmd_len)
srcs/builtins/ft_unsetenv.c:			if (ft_strequ(e->cmd[i], "all"))
srcs/builtins/ft_unsetenv.c:				ft_free_tab(e->env);
srcs/builtins/ft_unsetenv.c:				e->env = NULL;
srcs/builtins/ft_unsetenv.c:				ft_unsetenv(&e->env, e->cmd[i]);
srcs/builtins/ft_where.c:	paths = ft_find_paths(e->env);
srcs/builtins/ft_where.c:	while (++i < (int)e->cmd_len)
srcs/builtins/ft_where.c:		if (ft_isbuiltin(e->cmd[i]))
srcs/builtins/ft_where.c:			ft_error(e->cmd[i], "is a shell built-in", NULL);
srcs/builtins/ft_where.c:		if ((path = ft_find_exec(paths, e->cmd[i])))
srcs/redirections/redir_file.c:	while (e->magic[RED_INDEX].cmd && ft_strcmp(e->magic[RED_INDEX].type, "red"))
srcs/redirections/redir_file.c:	if (!(e->magic[RED_INDEX].cmd))
srcs/redirections/redir_file.c:	while (e->magic[i].type)
srcs/redirections/redir_file.c:		if (!ft_strcmp(e->magic[i].type, "red"))
srcs/redirections/redir_file.c:		red_type = ft_strcmp(e->magic[RED_INDEX].cmd, ">>");
srcs/redirections/redir_file.c:		if ((fd_output = open(e->magic[++RED_INDEX].cmd, (!red_type ? TWO_RED_FLAGS : ONE_RED_FLAGS),\
srcs/redirections/redir_file.c:					e->magic[RED_INDEX].cmd ? e->magic[RED_INDEX].cmd : NULL);
srcs/redirections/redir_iteration.c:	while (e->magic[RED_INDEX].cmd && ft_strcmp(e->magic[RED_INDEX].type, "red"))
srcs/redirections/redir_iteration.c:	if (!(e->magic[RED_INDEX].cmd))
srcs/redirections/redir_iteration.c:	if (e->magic[RED_INDEX].cmd && red && !ft_strcmp(e->magic[RED_INDEX].cmd, red))
srcs/redirections/redir_iteration.c:**	CONTENUE DE L'ITERATION DE e->cat[i] (contient les cmds split par "red")
srcs/redirections/redir_iteration.c:	ret = ft_exec_cmd(e, e->cat[i]);
srcs/redirections/redir_iteration.c:		ret = ft_exec_cmd(e, e->cat[i]);
srcs/shell/ft_cmds_split.c:	while (e->magic[++i].cmd)
srcs/shell/ft_cmds_split.c:		if (!ft_strcmp(e->magic[i].cmd, "|") || !ft_strcmp(e->magic[i].cmd, "<") ||
srcs/shell/ft_cmds_split.c:			!ft_strcmp(e->magic[i].cmd, ">") || !ft_strcmp(e->magic[i].cmd, ">>"))
srcs/shell/ft_cmds_split.c:			if (!ft_strcmp(e->magic[i].cmd, ">") || !ft_strcmp(e->magic[i].cmd, ">>"))
srcs/shell/ft_cmds_split.c:		while (e->magic[++(*z)].cmd && ft_strcmp(e->magic[*z].cmd, "|" ))
srcs/shell/ft_cmds_split.c:			if (ft_strcmp(e->magic[*z].cmd, ">") || !ft_strcmp(e->magic[*z].cmd, ">>"))
srcs/shell/ft_cmds_split.c:		while (e->magic[++(*z)].cmd && ft_strcmp(e->magic[*z].cmd, "|") && ft_strcmp(e->magic[*z].cmd, ">")\
srcs/shell/ft_cmds_split.c:			&& ft_strcmp(e->magic[*z].cmd, ">>"))
srcs/shell/ft_cmds_split.c:		if (!ft_strcmp(e->magic[*z].cmd, ">") || !ft_strcmp(e->magic[*z].cmd, ">>"))
srcs/shell/ft_cmds_split.c:	while (j < len && e->magic[++k].cmd)
srcs/shell/ft_cmds_split.c:		if (ft_strcmp(e->magic[k].cmd, ">") && ft_strcmp(e->magic[k].cmd, ">>"))
srcs/shell/ft_cmds_split.c:			rtr[j++] = ft_strdup(e->magic[k].cmd);
srcs/shell/ft_cmds_split.c:	while (e->cat[++i])
srcs/shell/ft_cmds_split.c:		ft_free_tab(e->cat[i]);
srcs/shell/ft_cmds_split.c:	free(e->cat);
srcs/shell/ft_cmds_split.c:	e->cat = NULL;
srcs/shell/ft_exec.c:			execve(exec, &cmd[0], e->env);
srcs/shell/ft_exec.c:			execve(exec, &cmd[0], e->env);
srcs/shell/ft_exec.c:	paths = ft_find_paths(e->env);
srcs/shell/ft_exec.c:	e->cmd_len = ft_tablen(cmd);
srcs/shell/ft_exec.c:	if (e->cmd_len)
srcs/shell/ft_exec.c:	e->cmd_len = 0;
srcs/shell/ft_init.c:	e->prompt = ft_strdup("$> ");
srcs/shell/ft_init.c:	e->home = NULL;
srcs/shell/ft_init.c:	if ((tmp = ft_getenv(e->env, "HOME")))
srcs/shell/ft_init.c:		e->home = ft_strdup(tmp);
srcs/shell/ft_init.c:	if ((lvl = ft_getenv(e->env, "SHLVL")))
srcs/shell/ft_init.c:		ft_setenv(&e->env, "SHLVL", lvl);
srcs/shell/ft_init.c:		ft_setenv(&e->env, "SHLVL", "1");
srcs/shell/ft_init.c:	e->history = NULL;
srcs/shell/ft_init.c:		ft_free_tab(e->history);
srcs/shell/ft_init.c:		e->history = NULL;
srcs/shell/ft_init.c:	ft_bzero(e->buf, 3);
srcs/shell/ft_init.c:	e->x = 1;
srcs/shell/ft_init.c:	e->exit = 0;
srcs/shell/ft_init.c:	e->line = NULL;
srcs/shell/ft_init.c:	e->env = ft_tabdup(env);
srcs/shell/ft_init.c:	e->cmd = NULL;
srcs/shell/ft_init.c:	e->cut = NULL;
srcs/shell/ft_init.c:	e->cat = NULL;
srcs/shell/ft_init.c:	e->i_mag = 0;
srcs/shell/ft_init.c:	if (e->env == NULL || !ft_set_home(e))
srcs/shell/ft_init.c:	if ((TCAPS.term_name = ft_getenv(e->env, "TERM")) == NULL)
srcs/shell/ft_parse.c:	if (!(home = ft_getenv(e->env, "HOME")))
srcs/shell/ft_parse.c:	while (e->cmd[++k])
srcs/shell/ft_parse.c:		if (e->cmd[k][0] == '~')
srcs/shell/ft_parse.c:			tmp = ft_tilde(e, e->cmd[k]);
srcs/shell/ft_parse.c:			strfree(&e->cmd[k]);
srcs/shell/ft_parse.c:			e->cmd[k] = tmp;
srcs/shell/ft_parse.c:	trline = ft_strxtrim_quote(e->line, '\t');
srcs/shell/ft_parse.c:	if (ft_strequ(e->cmd[0], "exit") && ++ret)
srcs/shell/ft_parse.c:	else if (ft_strequ(e->cmd[0], "env") && ++ret)
srcs/shell/ft_parse.c:	else if (ft_strequ(e->cmd[0], "setenv") && ++ret)
srcs/shell/ft_parse.c:	else if (ft_strequ(e->cmd[0], "unsetenv") && ++ret)
srcs/shell/ft_parse.c:	else if (ft_strequ(e->cmd[0], "cd") && ++ret)
srcs/shell/ft_parse.c:	else if (ft_strequ(e->cmd[0], "echo") && ++ret)
srcs/shell/ft_parse.c:	else if (ft_strequ(e->cmd[0], "where") && ++ret)
srcs/shell/ft_parse.c:	else if (ft_strequ(e->cmd[0], "history") && ++ret)
srcs/shell/ft_parse.c:	e->cmd = ft_strsplit_quote(cmds_i, ' ');
srcs/shell/ft_parse.c:	e->magic = struct_strsplit_quote(cmds_i, ' ');
srcs/shell/ft_parse.c:	e->cat = ft_cmds_split(e);
srcs/shell/ft_parse.c:/*	for (int j = 0 ; e->cat[j]; j++)
srcs/shell/ft_parse.c:		for (int k = 0; e->cat[j][k]; k++)
srcs/shell/ft_parse.c:			ft_printf("cat[%d][%d] : %s\n", j, k, e->cat[j][k]);*/
srcs/shell/ft_parse.c:	while (e->cat[++i + 1] && ret != -1)
srcs/shell/ft_parse.c:	ft_free_tab(e->cmd);
srcs/shell/ft_parse.c:	e->cmd = NULL;
srcs/shell/main.c:	if (e->line && ft_parse_line(e))
srcs/shell/main.c:	if (e->x)
srcs/shell/main.c:		ft_putstr(e->prompt);
srcs/shell/main.c:	strfree(&e->line);
srcs/shell/main.c:	e->line = NULL;
srcs/shell/main.c:		e->line = ft_realloc_line(e, BUF[0]);
srcs/shell/main.c:		e->line = ft_realloc_insert_char(e, BUF[0]);
srcs/shell/main.c:		tcaps_putstr(e, e->line);
srcs/shell/main.c:	TCAPS.nb_read = ft_strlen(e->line);
srcs/shell/main.c:	if (e->line && e->buf[0] == 127 && TCAPS.nb_move > 0)
srcs/struct/struct_get_type.c:	if (i > 0 && e->magic[i - 1].cmd && !red_strstr(e->magic[i - 1].cmd) &&
srcs/struct/struct_get_type.c:		!red_strstr(e->magic[i].cmd))
srcs/struct/struct_get_type.c:	else if (i == 0 && !red_strstr(e->magic[i].cmd))
srcs/struct/struct_get_type.c:	if (e->magic[i - 1].cmd && !red_strstr(e->magic[i - 1].cmd) &&
srcs/struct/struct_get_type.c:		!red_strstr(e->magic[i].cmd))
srcs/struct/struct_get_type.c:	strfree(&e->magic[i - 1].type);
srcs/struct/struct_get_type.c:	if (ft_strcmp("red", e->magic[i - 1].type))
srcs/struct/struct_get_type.c:		e->magic[i - 1].type = ft_strdup("ignore");
srcs/struct/struct_get_type.c:	if (!ft_strcmp(e->magic[i].cmd, "<") ||
srcs/struct/struct_get_type.c:		!ft_strcmp(e->magic[i].cmd, "<<") ||
srcs/struct/struct_get_type.c:		ft_strstr(e->magic[i].cmd, "<&") ||
srcs/struct/struct_get_type.c:		!ft_strcmp("input", e->magic[i].type))
srcs/struct/struct_get_type.c:	if (!ft_strcmp(e->magic[i].cmd, ">") ||
srcs/struct/struct_get_type.c:		!ft_strcmp(e->magic[i].cmd, ">>") ||
srcs/struct/struct_get_type.c:		ft_strstr(e->magic[i].cmd, "&>") ||
srcs/struct/struct_get_type.c:		!ft_strcmp(e->magic[i].cmd, "|") ||
srcs/struct/struct_get_type.c:		!ft_strcmp("output", e->magic[i].type))
srcs/struct/struct_get_type.c:	if (i > 0 && (!ft_strcmp("|", e->magic[i - 1].cmd) ||
srcs/struct/struct_get_type.c:				  !ft_strcmp(e->magic[i - 1].type, "cmd")))
srcs/struct/struct_get_type.c: 		e->magic[i].type = ft_strdup("cmd");
srcs/struct/struct_get_type.c:		e->magic[i].type = ft_strdup("input");
srcs/struct/struct_get_type.c:		e->magic[i].type = ft_strdup("output");
srcs/struct/struct_get_type.c:	if (i > 0 && (!ft_strcmp(e->magic[i - 1].type, "input") ||
srcs/struct/struct_get_type.c:		 !ft_strcmp(e->magic[i - 1].type, "output")))
srcs/struct/struct_tools.c:	while (e->magic[++i].cmd)
srcs/struct/struct_tools.c:			e->magic[i].type = ft_strdup("cmd");
srcs/struct/struct_tools.c:		else if (red_strstr(e->magic[i].cmd))
srcs/struct/struct_tools.c:			e->magic[i].type = ft_strdup("red");
srcs/struct/struct_tools.c:	if (e->magic)
srcs/struct/struct_tools.c:		while (e->magic[++i].cmd)
srcs/struct/struct_tools.c:			if (e->magic[i].cmd)
srcs/struct/struct_tools.c:				free(e->magic[i].cmd);
srcs/struct/struct_tools.c:				e->magic[i].cmd = NULL;
srcs/struct/struct_tools.c:			if (e->magic[i].type)
srcs/struct/struct_tools.c:				free(e->magic[i].type);
srcs/struct/struct_tools.c:				e->magic[i].type = NULL;
srcs/struct/struct_tools.c:		free(e->magic);
srcs/struct/struct_tools.c:		e->magic = NULL;
srcs/tcaps/tcaps_arrow.c:	ft_putstr(e->prompt);
srcs/tcaps/tcaps_arrow.c:	tputs(e->line, 1, dsh_putchar);
srcs/tcaps/tcaps_arrow.c:**  WIN_WIDTH : e->tcaps.ws.ws_col
srcs/tcaps/tcaps_arrow.c:	if (TCAPS.nb_col > (int)ft_strlen(e->prompt) || TCAPS.nb_line > 1)
srcs/tcaps/tcaps_ctrl.c:	if (TCAPS.nb_line == 2 && TCAPS.nb_col < (int)ft_strlen(e->prompt))
srcs/tcaps/tcaps_ctrl.c:	strfree(&e->line);
srcs/tcaps/tcaps_ctrl.c:	i = ft_strlen(e->prompt);
srcs/tcaps/tcaps_ctrl.c:	while ((i > 0 && i != TCAPS.nb_read && e->line[i - 1] == ' ')
srcs/tcaps/tcaps_ctrl.c:	while (i > 0 && i != TCAPS.nb_read && e->line[i - 1] != ' ')
srcs/tcaps/tcaps_ctrl.c:	while (e->line[i] == '-' || e->line[i] == ' ')
srcs/tcaps/tcaps_ctrl.c:	while (i > 0 && (e->line[i - 1] == ' ' || e->line[i - 1] == '-'))
srcs/tcaps/tcaps_ctrl.c:	while ((i && e->line[i - 1] != ' '))
srcs/tcaps/tcaps_ctrl.c:	while (e->line[i] == '-')
srcs/tcaps/tcaps_ctrl.c:			while (line--)
srcs/tcaps/tcaps_ctrl.c:		while (line-- && TCAPS.nb_move < TCAPS.nb_read)
srcs/tcaps/tcaps_cut_paste.c:	strfree(&e->cut);
srcs/tcaps/tcaps_cut_paste.c:	e->cut = ft_strnew(TCAPS.nb_read - TCAPS.nb_move);
srcs/tcaps/tcaps_cut_paste.c:	while (e->line[i++])
srcs/tcaps/tcaps_cut_paste.c:		e->cut[++j] = e->line[i];
srcs/tcaps/tcaps_cut_paste.c:	tmp = ft_strsub(e->line, 0, TCAPS.nb_move);
srcs/tcaps/tcaps_cut_paste.c:	strfree(&e->line);
srcs/tcaps/tcaps_cut_paste.c:	e->line = tmp;
srcs/tcaps/tcaps_cut_paste.c:	TCAPS.nb_read -= (int)ft_strlen(e->cut);
srcs/tcaps/tcaps_cut_paste.c:	if (e->cut)
srcs/tcaps/tcaps_cut_paste.c:		cut_len = (int)ft_strlen(e->cut);
srcs/tcaps/tcaps_cut_paste.c:		ft_realloc_insert_str(e, e->cut);
srcs/tcaps/tcaps_cut_paste.c:		TCAPS.nb_read = (int)ft_strlen(e->line);
srcs/tcaps/tcaps_cut_paste.c:		if (TCAPS.nb_col > (int)ft_strlen(e->prompt))
srcs/tcaps/tcaps_cut_paste.c:			ft_putstr(e->prompt);
srcs/tcaps/tcaps_cut_paste.c:			move_nb_char_prompt(e->prompt);
srcs/tcaps/tcaps_cut_paste.c:		ft_putstr(e->line);
srcs/tcaps/tcaps_delete.c:		if (!TCAPS.nb_read && e->line)
srcs/tcaps/tcaps_delete.c:			free(e->line);
srcs/tcaps/tcaps_delete.c:			e->line = NULL;
srcs/tcaps/tcaps_delete.c:		if (!TCAPS.nb_read && e->line)
srcs/tcaps/tcaps_delete.c:			free(e->line);
srcs/tcaps/tcaps_delete.c:			e->line = NULL;
srcs/tcaps/tcaps_delete.c:		tcaps_putstr(e, e->line);
srcs/tcaps/tcaps_history.c:	while (--TCAPS.nb_read + ((int)ft_strlen(e->prompt) + 1) > 0)
srcs/tcaps/tcaps_history.c:	tputs(e->prompt, 1, dsh_putchar);
srcs/tcaps/tcaps_history.c:	ft_printf("%s", e->history[TCAPS.hist_move]);
srcs/tcaps/tcaps_history.c:	TCAPS.nb_read = (int)ft_strlen(e->history[TCAPS.hist_move]);
srcs/tcaps/tcaps_history.c:	if (!e->history || !e->history[0])
srcs/tcaps/tcaps_history.c:		TCAPS.hist_move = (int)ft_tablen(e->history);
srcs/tcaps/tcaps_history.c:		strfree(&e->line);
srcs/tcaps/tcaps_history.c:		e->line = ft_strdup(e->history[TCAPS.hist_move]);
srcs/tcaps/tcaps_history.c:	if (TCAPS.hist_move == -1 || !e->history || !e->history[0])
srcs/tcaps/tcaps_history.c:	hist_tab_len = (int)ft_tablen(e->history);
srcs/tcaps/tcaps_history.c:		strfree(&e->line);
srcs/tcaps/tcaps_history.c:		strfree(&e->line);
srcs/tcaps/tcaps_history.c:		e->line = ft_strdup(e->history[TCAPS.hist_move]);
srcs/tcaps/tcaps_paste.c:			e->line = ft_realloc_line(e, buf[i]);
srcs/tcaps/tcaps_positions.c:	tmp = TCAPS.nb_move + (int)ft_strlen(e->prompt);
srcs/tcaps/tcaps_positions.c:		TCAPS.nb_col = (tmp % (TCAPS.ws.ws_col + 1)) + ft_strlen(e->prompt) - 1;
srcs/tcaps/tcaps_putstr.c:	tputs(e->prompt, 1, dsh_putchar);
srcs/tools/ft_banner.c:	ft_putstr(e->prompt);
srcs/tools/ft_realloc_line.c:	if (e->line)
srcs/tools/ft_realloc_line.c:		while (e->line[i])
srcs/tools/ft_realloc_line.c:				new[++j] = e->line[i++];
srcs/tools/ft_realloc_line.c:	if (e->line)
srcs/tools/ft_realloc_line.c:		strfree(&e->line);
srcs/tools/ft_realloc_line.c:	if (e->line)
srcs/tools/ft_realloc_line.c:		len = ft_strlen(e->line) + 1;
srcs/tools/ft_realloc_line.c:		while (e->line[i])
srcs/tools/ft_realloc_line.c:				new[++j] = e->line[i++];
srcs/tools/ft_realloc_line.c:	strfree(&e->line);
srcs/tools/ft_realloc_line.c:	new = ft_strsub(e->line, 0, TCAPS.nb_move);
srcs/tools/ft_realloc_line.c:	new = ft_strsub(e->line, TCAPS.nb_move, TCAPS.nb_read - TCAPS.nb_move);
srcs/tools/ft_realloc_line.c:	free(e->line);
srcs/tools/ft_realloc_line.c:	e->line = ft_strjoin(tmp, new);
srcs/tools/ft_realloc_line.c:	if (e->line)
srcs/tools/ft_realloc_line.c:		len = ft_strlen(e->line) + 1;
srcs/tools/ft_realloc_line.c:		while (e->line[i])
srcs/tools/ft_realloc_line.c:			new[i] = e->line[i];
srcs/tools/ft_realloc_line.c:	if (e->line)
srcs/tools/ft_realloc_line.c:		strfree(&e->line);
srcs/tools/ft_realloc_tab.c:	while (e->magic[++i].type != NULL)
srcs/tools/ft_realloc_tab.c:		if (ft_strcmp("ignore", e->magic[i].type))
srcs/tools/ft_realloc_tab.c:	while (e->magic[++i].type != NULL)
srcs/tools/ft_realloc_tab.c:		if (ft_strcmp(e->magic[i].type, "ignore"))
srcs/tools/ft_realloc_tab.c:			new[++j].type = ft_strdup(e->magic[i].type);
srcs/tools/ft_realloc_tab.c:			new[j].cmd = ft_strdup(e->magic[i].cmd);
srcs/tools/ft_realloc_tab.c:	e->magic = new;
srcs/tools/ft_tools.c:	if (e->line)
srcs/tools/ft_tools.c:		strfree(&e->line);
srcs/tools/ft_tools.c:	if (e->home)
srcs/tools/ft_tools.c:		strfree(&e->home);
srcs/tools/ft_tools.c:	if (e->history)
srcs/tools/ft_tools.c:		ft_free_tab(e->history);
srcs/tools/ft_tools.c:	if (e->prompt)
srcs/tools/ft_tools.c:		strfree(&e->prompt);
srcs/tools/ft_tools.c:	if (e->env)
srcs/tools/ft_tools.c:		ft_free_tab(e->env);
srcs/tools/ft_tools.c:	if (e->magic)
