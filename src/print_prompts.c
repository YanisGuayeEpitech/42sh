/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Prompt format functions
*/

#include <libmy/io.h>
#include <libmy/ascii.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>

#include "shell.h"
#include "token.h"
#include "util.h"

void print_w(sh_ctx_t *ctx)
{
    time_t now;
    struct tm *local;
    char *month_name[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul",
        "Aug", "Sep", "Oct", "Nov", "Dec"};

    time(&now);
    local = localtime(&now);
    my_puts(month_name[local->tm_mon]);
    (void)ctx;
}

void print_ww(sh_ctx_t *ctx)
{
    time_t now;
    struct tm *local;

    time(&now);
    local = localtime(&now);
    my_printf("%d", local->tm_mon);
    (void)ctx;
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
    (void)ctx;
}

void print_yy(sh_ctx_t *ctx)
{
    time_t now;
    struct tm *local;

    time(&now);
    local = localtime(&now);
    my_printf("%d", local->tm_year);
    (void)ctx;
}
