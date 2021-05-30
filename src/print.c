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

void print_wd(sh_ctx_t *ctx)
{
    char pwd[100];

    getwd(pwd);
    my_puts(pwd);
}

void print_t(sh_ctx_t *ctx)
{
    time_t now;
    struct tm *local;

    time(&now);
    local = localtime(&now);
    if (local->tm_hour < 12)
        my_printf("%d:%02dam", local->tm_hour, local->tm_min);
    else
        my_printf("%d:%02dpm", local->tm_hour - 12, local->tm_min);
}

void print_tt(sh_ctx_t *ctx)
{
    time_t now;
    struct tm *local;

    time(&now);
    local = localtime(&now);
    my_printf("%d:%02d", local->tm_hour, local->tm_min);
}

void print_p(sh_ctx_t *ctx)
{
    time_t now;
    struct tm *local;

    time(&now);
    local = localtime(&now);
    if (local->tm_hour < 12)
        my_printf("%d:%02d:%02dam", local->tm_hour,
        local->tm_min, local->tm_sec);
    else
        my_printf("%d:%02d:%02dpm", local->tm_hour - 12,
        local->tm_min, local->tm_sec);
}

void print_pp(sh_ctx_t *ctx)
{
    time_t now;
    struct tm *local;

    time(&now);
    local = localtime(&now);
    my_printf("%d:%02d:%02d", local->tm_hour,
    local->tm_min, local->tm_sec);
}

void print_name(sh_ctx_t *ctx)
{
    char *username;

    username = getlogin();
    my_puts(username);
}

void print_hostname(sh_ctx_t *ctx)
{
    char **host = sh_env_get_entry(ctx, SH_LSTR("HOSTNAME", 8));

    if (*host) {
        my_puts(*host+9);
    }
}

void print_d(sh_ctx_t *ctx)
{
    time_t now;
    struct tm *local;
    char *week_day[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

    time(&now);
    local = localtime(&now);
    my_puts(week_day[local->tm_wday]);
}

void print_dd(sh_ctx_t *ctx)
{
    time_t now;
    struct tm *local;

    time(&now);
    local = localtime(&now);
    my_printf("%d", local->tm_mday);
}

void print_w(sh_ctx_t *ctx)
{
    time_t now;
    struct tm *local;
    char *month_name[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul",
    "Aug", "Sep", "Oct", "Nov", "Dec"};

    time(&now);
    local = localtime(&now);
    my_puts(month_name[local->tm_mon]);
}

void print_ww(sh_ctx_t *ctx)
{
    time_t now;
    struct tm *local;

    time(&now);
    local = localtime(&now);
    my_printf("%d", local->tm_mon);
}

void print_y(sh_ctx_t *ctx)
{
    time_t now;
    struct tm *local;
    int year = 0;

    time(&now);
    local = localtime(&now);
    year = local->tm_year%100;
    my_printf("%d", year);
}

void print_yy(sh_ctx_t *ctx)
{
    time_t now;
    struct tm *local;

    time(&now);
    local = localtime(&now);
    my_printf("%d", local->tm_year);
}

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
        return ;
    }
    for (int j = 0; j < 12; j++)
        if (prompt_flags[j].flag == prompt[*i]) {
            prompt_flags[j].run(ctx);
            return ;
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
    if (ctx->is_tty)
        sh_print_all(ctx, "%/ %d$> ");
}
