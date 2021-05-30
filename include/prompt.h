/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Prompt commands and functions
*/

#ifndef __SHELL_PROMPT_H__
#define __SHELL_PROMPT_H__

typedef struct {
    char const flag;
    void (*run)(sh_ctx_t *);
} sh_prompt_t;

void print_wd(sh_ctx_t *ctx);
void print_t(sh_ctx_t *ctx);
void print_tt(sh_ctx_t *ctx);
void print_p(sh_ctx_t *ctx);
void print_pp(sh_ctx_t *ctx);
void print_name(sh_ctx_t *ctx);
void print_hostname(sh_ctx_t *ctx);
void print_d(sh_ctx_t *ctx);
void print_dd(sh_ctx_t *ctx);
void print_w(sh_ctx_t *ctx);
void print_ww(sh_ctx_t *ctx);
void print_y(sh_ctx_t *ctx);
void print_yy(sh_ctx_t *ctx);

#endif // !defined(__SHELL_PROMPT_H__)
