#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define ANSI_COLOR_GREY1 "\x1b[38;5;242m"
#define PINK "\x1b[38;5;204m"
#define ANSI_COLOR_RESET "\x1b[0m"
#define INFO "["ANSI_COLOR_GREY1"INFO"ANSI_COLOR_RESET"] "
#define ERROR "["PINK"ERROR"ANSI_COLOR_RESET"] "
#define FOUND "\x1b[38;5;115mFOUND"ANSI_COLOR_RESET

void thegame_f() {

    printf(INFO"Starting \"The Gameington\" setup process\n");
    /* Check /home/currentuser for a folder /thegameington */

    printf(INFO"Finding home directory...");
    char *home = getenv("HOME");
    if (home == NULL) {
        printf(ERROR"HOME environment variable not set, returning...\n");
        return;
    }
    printf(FOUND"\n");

    char *thegameington = "/thegameington";
    char *thegameington_path = malloc(strlen(home) + strlen(thegameington) + 1);
    if (thegameington_path == NULL) {
        printf(ERROR"str memory allocation failed somehow, returning...\n");
        return;
    }
    strcpy(thegameington_path, home);
    strcat(thegameington_path, thegameington);

    printf(INFO"Checking for The Gameington...");
    // Check if we have thegameington
    if (access(thegameington_path, F_OK) == -1) {
        // We don't have thegameington, clone it
        printf("\n"INFO"Repo not found in home directory\n");
        printf(INFO"Cloning latest version from Github\n");
        char clone_command[1024];
        sprintf(clone_command, "git clone https://github.com/jamesmorrisee/TheGameington.git %s", thegameington_path);
        int clone_status = system(clone_command);
        if (clone_status != 0) {
            printf(ERROR"Failed to clone repository, returning.\n");
            free(thegameington_path);
            return;
        }
        printf(INFO"Successfully cloned repository\n");
    }
    else {
        printf(FOUND"\n");
    }

    // Assuming the executable is named 'game' in the repository
    printf(INFO"Running The Gameington now...\n\n");
    int run_status = system(strcat(thegameington_path,"/game"));
    if (run_status != 0) {
        printf(ERROR"Process crashed (or executable not found)\n");
    }

    printf("\n"INFO"Finished running The Gameington\n\n");
    // Free allocated memory
    free(thegameington_path);
}
