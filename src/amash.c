/*!
   \file amash.c
   \brief Contains implementations for core functions.
*/

#include "amash.h"
#include <string.h>

void strip_input(char * input)
{
        input[strlen(input)-1] = '\0';
}

bool startsWith(const char *pre, const char *str)
{
        return strncmp(pre, str, strlen(pre)) == 0;
}

int run_event_loop()
{
        char input[100];
        char login[100];
        char hostname[100];
        while(1)
        {
                char cwd[100];
                getcwd(cwd, sizeof(cwd));
                getlogin_r(login, sizeof(login));
                gethostname(hostname, sizeof(hostname));
                printf(KBLU "\n%s@%s",hostname,login);
                printf(KRED":");
                printf(KWHT"%s",cwd);
                printf(KRED"$");
                printf(KGRN "");
                fgets(input, 1000, stdin);

                strip_input(input);

                printf("\ninput : %s END\n",input);
                if(startsWith("quit",input))
                {
                        break;
                }
                Executable* e = parse_single(input);
                exec_program(e);

        }
        return 0;
}

//TODO add something cool here
/*
void print_intro_screen()
{

}
*/

int main()
{
        //print_intro_screen();
        run_event_loop();
}
