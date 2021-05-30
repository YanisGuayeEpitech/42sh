/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Format functions
*/

#include <libmy/io.h>
#include <libmy/ascii.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>

#include "shell.h"
#include "token.h"
#include "util.h"

void print_wd(sh_ctx_t *ctx)
{
    char pwd[100];

    getwd(pwd);
    my_puts(pwd);
    (void)ctx;
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
    (void)ctx;
}

void print_tt(sh_ctx_t *ctx)
{
    time_t now;
    struct tm *local;

    time(&now);
    local = localtime(&now);
    my_printf("%d:%02d", local->tm_hour, local->tm_min);
    (void)ctx;
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
    (void)ctx;
}

void print_pp(sh_ctx_t *ctx)
{
    time_t now;
    struct tm *local;

    time(&now);
    local = localtime(&now);
    my_printf("%d:%02d:%02d", local->tm_hour,
    local->tm_min, local->tm_sec);
    (void)ctx;
}
