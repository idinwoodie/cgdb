#ifndef __GLOBALS_H__
#define __GLOBALS_H__

/* This unit holds global data to tgdb. It helps keep track of obscure states */

/****************************************************
 Keeps track of what the user has typed at the prompt 
 ***************************************************/
void global_user_typed_char(char a);
/* This should be called at the post prompt */
void global_reset_command_line_data(void);

/* did_user_press_enter: Tells if the user has hit enter at the command prompt.
 *    Returns: 1 if the user hit enter since the last prompt annotation.
 *       otherwise 0.
 */
int global_did_user_press_enter(void);
/* global_did_user_press_special_control_char: 
 *  Tells if the user typed a special control char at the command prompt.
 *  The control chars of interest are.
 *  ^d -> 4
 *  ^j -> 10
 *  ^l -> 12
 *  ^m -> 13
 *    Returns: 1 if the user hit one since the last prompt annotation.
 *       otherwise 0.
 */
int global_did_user_press_special_control_char(void);

/* has_user_typed: Tells if the user has hit any char after the command prompt.
 *    Returns: 1 if the user hit a char since the last prompt annotation.
 *       otherwise 0.
 */
int global_has_user_typed(void);

/* This gets set when the a '\n' gets recieved and the user did not type it.
 * This can happen if the user hits something that sends a '\n' or if readline
 * sends a '\n' during command completion.
 */
unsigned int global_has_implicit_enter_benen_recieved(void);
void global_set_implicit_enter(unsigned short set);

/* This turns true if tgdb gets a misc prompt. This is so that we do not 
 * send commands to gdb at this point.
 */
int globals_is_internal_prompt(void);
void globals_set_internal_prompt_command(unsigned short set);



/* global_can_issue_command: Tells tgdb if it can issue a command to gdb.
 * Return: 1 if tgdb can issue a command, otherwise 0.
 */
int global_can_issue_command(void);
/* if 1, then tgdb can issue a command, 0 can not */
void global_set_can_issue_command(unsigned short set);

/* if a signal was recieved by library. Once, the user reaches the prompt,
 * the signal is cleared.
 */
int global_signal_recieved(void);
void global_set_signal_recieved(unsigned short set);

/* These check to see if the gui is working on getting the source files that 
 * make up the program being debugged.
 */
void global_set_start_info_sources(void);
int global_has_info_sources_started(void);
void global_reset_info_sources_started(void);

/* These check to see if the gui is working on getting an absolute path to
 * a source file in the debugged program.
 */
void global_set_start_info_source(void);
int global_has_info_source_started(void);
void global_reset_info_source_started(void);

 /* Lists a file */
void global_set_start_list(void);
int global_has_list_started(void);
void global_reset_list_started(void);

/* Keeps track of the users home directory */
/* The caller must present these functions with a long enough cstring to
 * contain the data. MAXLINE is guarentted to be enough.
 */
void global_set_config_dir(const char *filename);
void global_get_config_dir(char *filename);
void global_get_config_gdb_init_file(char *filename);
void global_get_config_gdb_debug_file(char *filename);

#endif
