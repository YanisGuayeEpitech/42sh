/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Prints message if it's a tty
*/

#include <libmy/io.h>
#include <libmy/ascii.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>

#include "shell.h"
#include "token.h"
#include "util.h"
#include "prompt.h"

static const sh_prompt_t prompt_flags[] = {
    {'/', &print_wd},
    {'t', &print_t},
    {'T', &print_tt},
    {'p', &print_p},
    {'P', &print_pp},
    {'n', &print_name},
    {'m', &print_hostname},
    {'d', &print_d},
    {'D', &print_dd},
    {'w', &print_w},
    {'W', &print_ww},
    {'y', &print_y},
    {'Y', &print_yy},
};

void prompt_flag(char const *prompt, sh_ctx_t *ctx, int *i)
{
    *i = *i + 1;

    if (prompt[*i] == '%') {
        putchar('%');
        return;
    }
    for (int j = 0; j < 12; j++)
        if (prompt_flags[j].flag == prompt[*i]) {
            prompt_flags[j].run(ctx);
            return;
        }
}

void sh_print_all(sh_ctx_t *ctx, char const *prompt)
{
    for (int i = 0; prompt[i] != '\0'; i++) {
        if (prompt[i] == '%')
            prompt_flag(prompt, ctx, &i);
        else
            my_putchar(prompt[i]);
        my_flush_stdout();
    }
}

void sh_print(sh_ctx_t *ctx, char const *msg)
{
    if (ctx->is_tty) {
        my_puts(msg);
        my_flush_stdout();
    }
}

void sh_print_prompt(sh_ctx_t *ctx)
{
    sh_lstr_t key = (sh_lstr_t){"prompt", 6};
    sh_lstr_t value = sh_var_get(ctx, key);

    if (ctx->is_tty) {
        if (value.value)
            sh_print_all(ctx, value.value);
        else
            sh_print_all(ctx, "$> ");
    }
}
