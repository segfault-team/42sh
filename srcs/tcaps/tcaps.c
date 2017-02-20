#include "shell.h"

int				dsh_putchar(int c)
{
	return (ft_putchar(c));
}

int 			tcaps(t_env *e)
{
	if (BUF[0] == CTRL_D) // ctrl + d
		ft_exit(e);
	else if (tcaps_is_printable(BUF) && NB_MOVE == NB_READ) // all printable char
		tcaps_insert(e);
	else if (tcaps_check_key(BUF, 12, 0, 0)) // Ctrl + L
		tcaps_clear(e);
	else if (tcaps_check_key(BUF, 27, 91, 65) || tcaps_check_key(BUF, 27, 91, 66))
		tcaps_history_first_step(e); // arrow up/down
	else if (tcaps_check_key(BUF, 27, 91, 67) && TCAPS.nb_move < TCAPS.nb_read)
		tcaps_right(e); // arrow right
	else if (tcaps_check_key(BUF, 27, 91, 68) && TCAPS.nb_move > 0)
		tcaps_left(e); // arrow left
	else if (BUF[0] == 127 && TCAPS.nb_read && TCAPS.nb_move > 0)
		tcaps_del_bkw(e); // backspace(delete) key
	else if (tcaps_check_key(BUF, 27, 91, 49))
		tcaps_ctrl_arrow(e); // ctrl + arrow
	else if (tcaps_check_key(BUF, 5, 0, 0) || tcaps_check_key(BUF, 27, 91, 70))
		tcaps_ctrl_end(e); // (ctrl + e)/end
	else if (tcaps_check_key(BUF, 1, 0, 0) || tcaps_check_key(BUF, 27, 91, 72))
		tcaps_ctrl_home(e); // (ctrl + a)/home
	else if (tcaps_check_key(BUF, 11, 0, 0) || tcaps_check_key(BUF, 16, 0, 0))
		tcaps_cut_paste(e); // ctrl + k / ctrl + p
	else if (tcaps_check_key(BUF, 27, 91, 51))
		tcaps_del_fwd(e); // delete key
	else if (is_paste(BUF))
		tcaps_paste(e, BUF); // Ctrl + v
	//	else if (BUF[0])
	//		printf("\n%d | %d | %d\n", BUF[0], BUF[1], BUF[2]);
	return (0);
}
