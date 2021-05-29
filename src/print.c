/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Prints message if it's a tty
*/

#include <libmy/io.h>
#include <libmy/ascii.h>
#include <unistd.h>

#include "shell.h"
#include "token.h"

void cut_pwd(sh_ctx_t *ctx, char *pwd)
{
    char **home = sh_env_get_entry(ctx, SH_LSTR("HOME", 4));
    int cut = 0;

    if (my_strcmp(*home, pwd) == 0) {
        pwd = "~";
        return ;
    }
    for (int i = 0; pwd[i]; i++)
        if (pwd[i] == '/')
            cut = i + 1;
    for (int i = 0; i < cut; i++)
        pwd++;

}

void sh_print_all(sh_ctx_t *ctx, char const *pwd, char const *user,
char const *host)
{
    char **home = sh_env_get_entry(ctx, SH_LSTR("HOME", 4));
    int cut = 5;

    for (int i = 0; pwd[i]; i++)
        if (pwd[i] == '/')
            cut = i + 1;
    if (ctx->is_tty) {
        my_puts("[");
        my_puts(user+5);
        my_puts("@");
        my_puts(host+9);
        my_puts(" ");
        if (my_strcmp((*home)+5, pwd) == 0)
            my_puts("~");
        else
            my_puts(pwd+cut);
        my_puts("]$ ");
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
    char pwd[100];
    char **user = sh_env_get_entry(ctx, SH_LSTR("USER", 4));
    char **host = sh_env_get_entry(ctx, SH_LSTR("HOST", 4));

    getwd(pwd);
    sh_print_all(ctx, pwd, *user, *host);
}
