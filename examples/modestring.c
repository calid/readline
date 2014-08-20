/* modestring.c -- Used for testing/debugging mode string functionality */

/* Copyright (C) 2014 Free Software Foundation, Inc.

   This file is part of the GNU Readline Library (Readline), a library for
   reading lines of text with interactive input and history editing.

   Readline is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   Readline is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with Readline.  If not, see <http://www.gnu.org/licenses/>.
*/

/*
    Switch between built in prompts or set custom one:
    prompt <1-7|custom_prompt>

    Set readline options:
    set <inputrc-option>

    Toggle on/off colored mode strings:
    ansi

    Toggle on/off unicode symbol/colored mode strings:
    uni

    Quit:
    exit

    Explicitly set mode strings:
    set vi-mode-str1 <new-insert-modestr>
    set vi-mode-str2 <new-command-modestr>
    set emacs-mode-str <new-emacs-modestr>
*/

#include <stdio.h>
#include <readline/readline.h>

#define ANSI_GRAY     "\001\033[30;1m\002"
#define ANSI_RED      "\001\033[31;1m\002"
#define ANSI_GREEN    "\001\033[32;1m\002"
#define ANSI_YELLOW   "\001\033[33;1m\002"
#define ANSI_BLUE     "\001\033[34;1m\002"
#define ANSI_MAGENTA  "\001\033[35;1m\002"
#define ANSI_END      "\001\033[0m\002"

static char *vi_ins = "(ins)";
static char *vi_cmd = "(cmd)";

static char *vi_uni_ins = ANSI_GREEN  "●●●" ANSI_END;
static char *vi_uni_cmd = ANSI_YELLOW "●●●" ANSI_END;

static char *vi_ansi_ins = ANSI_GREEN  "(ins)" ANSI_END;
static char *vi_ansi_cmd = ANSI_YELLOW "(cmd)" ANSI_END;

static void toggle_unimode()
{
    static int uni = 0;

    if (uni) {
        rl_variable_bind("vi-mode-str1", vi_ins);
        rl_variable_bind("vi-mode-str2", vi_cmd);
        uni = 0;
    }
    else {
        rl_variable_bind("vi-mode-str1", vi_uni_ins);
        rl_variable_bind("vi-mode-str2", vi_uni_cmd);
        uni = 1;
    }
}

static void toggle_ansimode()
{
    static int ansi = 0;

    if (ansi) {
        rl_variable_bind("vi-mode-str1", vi_ins);
        rl_variable_bind("vi-mode-str2", vi_cmd);
        ansi = 0;
    }
    else {
        rl_variable_bind("vi-mode-str1", vi_ansi_ins);
        rl_variable_bind("vi-mode-str2", vi_ansi_cmd);
        ansi = 1;
    }
}

int main(void)
{
    rl_variable_bind("editing-mode", "vi");
    rl_variable_bind("show-mode-in-prompt", "on");

    char *prompt1 = "> ";

    char *prompt2 = "foo@bar \\m > ";

    char *prompt3 = ANSI_RED "> " ANSI_END;

    char *prompt4 = ANSI_RED "foo@bar" ANSI_END
                    " \\m "
                    ANSI_RED "> " ANSI_END;

    char *prompt5 = "\n> ";

    char *prompt6 = "\nfoo@bar\n\\m > ";

    char *prompt7 =
        "\n" ANSI_RED "foo@bar" ANSI_END
        "\n" ANSI_RED "\\m " ANSI_RED "> "  ANSI_END;



    char *prompt = prompt4;
    toggle_ansimode();

    while (1) {
        char *line = readline(prompt);
        add_history(line);

        if ( strcmp(line, "exit") == 0 ) {
            break;
        }
        else if ( strstr(line, "set") ) {
            rl_parse_and_bind(line);
        }
        else if ( strstr(line, "prompt ") && strlen(line) > 7 ) {
            char next = line[7];
            switch (next) {
                case '1': prompt = prompt1; break;
                case '2': prompt = prompt2; break;
                case '3': prompt = prompt3; break;
                case '4': prompt = prompt4; break;
                case '5': prompt = prompt5; break;
                case '6': prompt = prompt6; break;
                case '7': prompt = prompt7; break;
                default: prompt = line+7; break;
            }
        }
        else if ( strstr(line, "uni") ) {
            toggle_unimode();
        }
        else if ( strstr(line, "ansi") ) {
            toggle_ansimode();
        }
        else {
            if ( strlen(line) ) {
                puts(line);
            }
        }
    }
}
