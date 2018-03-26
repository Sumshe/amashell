/*!
   \file amash.h
   \brief Contains definitions for all the structs and functions in the shell
 */
#ifndef AMASH_H
#define AMASH_H 1

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "log.h"

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

#define PATH_LENGTH 100
#define MAX_ARGUMENTS 10
#define ARG_LENGTH 100
//////////////
//structs.c //
//////////////
/*
 *  \union Target
 *  Represents the target of a redirection. Can be either a path or a file handle.
 */
typedef union Target
{
        char path[PATH_LENGTH];
        int fd;
} Target;

/**
 *  \struct Redirect
 *  \brief Represents one redirect directive. Holds the fd to redirect, and an
 *         object of union Target to define the actual target to redirect to.
 */
typedef struct Redirect
{
        bool is_used;       /*!< Is this redirect supposed to applied? */
        bool target_is_path; /*!< Is the target a path or file handle? */
        Target* target;     /*!< target of the redirection (a union) */
} Redirect;

Redirect* newRedirectFromPath(char* path);
Redirect* newRedirectFromFileHandle(int fd);

//TODO make sure argv is always null-terminated
/**
 *  \struct Executable
 *  \brief Represents one single executable to run, containing the path,
 *         arguments, and redirects.
 */
typedef struct Executable {
        char exec_path[PATH_LENGTH];/*!< string of the exectuable to run, may or may not be relative */
        Redirect* stdin;        /*!< What should stdin be set to? */
        Redirect* stdout;       /*!< What should stdout be set to? */
        Redirect* stderr;       /*!< What should stderr be set to? */
        char argv[MAX_ARGUMENTS][ARG_LENGTH]; /*!< Argument strings to pass */
        int argc;               /*!< Number of arguments being passed */
} Executable;

/**
 *  Create a new struct Executable object
 *  @return A blank struct Executable object
 */
Executable* newExecutable();

////////////
//parse.c //
////////////


/**
 *  Parse the input string for a single executable, and return an Executable object
 *  @return An Executable object
 */
Executable* parse_single();

/**
 *  Parse the received input, and produce a ParsedInput object
 *  @param  input input string
 *  @return       An object representing a breakdown of the given command
 */
// ParsedInput* parse(char* input);

///////////
//exec.c //
///////////

/**
 *  Executes parsed input, delegates most of the work to exec. Mostly concerned
 *  with pipes and stuff.
 *  @param i Parsed input
 */
// void exec_input(ParsedInput* i);

/**
 *  Executes a single program in a new process(after forking). Uses execp to search PATH, if necessary.
 *  @param e Details of the executable
 */



void exec_program(Executable* e);

/**
 *  Set the file handles of the current process according to the parameter.
 *  @param e Executable object, containing a list of redirects to apply.
 */
void set_redirects(Executable* e);

/**
 *  Starts the main event loop
 *  @return exit code
 */

void do_cd(Executable* e);
void do_pwd(Executable* e);
void do_quit(Executable* e);

////////////
//amash.c //
////////////


int run_event_loop();
int slice_count(char* input);
void printPrompt();

#endif
