#include <sys/ioctl.h>
#include <unistd.h>
#include <termios.h>
#include "terminal.h"
#include "error.h"

/* The terminal attributes before calling tty_cbreak */
static struct termios save_termios;
static struct winsize size;
static enum { RESET, TCBREAK } ttystate = RESET;

/* tty_cbreak: Sets terminal to cbreak mode. Also known as noncanonical mode.
 *    1. Signal handling is still turned on, so the user can still type those.
 *    2. echo is off
 *    3. Read in one char at a time.
 *
 * fd    - The file descriptor of the terminal
 * 
 * Returns: 0 on sucess, -1 on error
 */
int tty_cbreak(int fd){
   struct termios buf;
    int ttysavefd = -1;
   
   if(tcgetattr(fd, &save_termios) < 0)
      return -1;
      
   buf = save_termios;
   buf.c_lflag &= ~(ECHO | ICANON);
   buf.c_cc[VMIN] = 1;
   buf.c_cc[VTIME] = 0;

   if(tcsetattr(fd, TCSAFLUSH, &buf) < 0)
      return -1;

   ttystate = TCBREAK;
   ttysavefd = fd;

   // set size
   if(ioctl(fd, TIOCGWINSZ, (char *)&size) < 0)
      return -1;

#ifdef DEBUG
   err_msg("%d rows and %d cols\n", size.ws_row, size.ws_col);   
#endif
   
   return (0);   
}

/* set the gdb's pseudo - terminal to not map NL to CR NL */
int tty_output_nl(int fd){
    struct termios buf;
    struct termios save_termios;

    /* get attributes */
    if(tcgetattr(fd, &save_termios) < 0){
        err_msg("%s:%d -> Could not get gdb's pseudo terminal's attributes ", __FILE__, __LINE__);
        return -1;
    }

    buf = save_termios;
    buf.c_oflag &= ~ONLCR; /* turn off NL -> CR NL mapping */

    if(tcsetattr(fd, TCSAFLUSH, &buf) < 0){
        err_msg("%s:%d -> Could not set gdb's pseudo terminal's attributes ", __FILE__, __LINE__);
        return -1;
    }
    
    return 0;
}

/* tty_reset: Sets the terminal attributes back to their previous state.
 * PRE: tty_cbreak must have already been called.
 * 
 * fd    - The file descrioptor of the terminal to reset.
 * 
 * Returns: 0 on success, -1 on error
 */
int tty_reset(int fd){
   if(ttystate != TCBREAK)
      return (0);

   if(tcsetattr(fd, TCSAFLUSH, &save_termios) < 0)
      return (-1);
      
   ttystate = RESET;
   
   return 0;   
}
