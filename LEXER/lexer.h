#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../includes/malloc.h"

typedef enum e_token
{
	REDIRECTION,
	PIPE,
	WORD,
	VAR,
	SINGLE_QUOT,
	DOUBLE_QUOT,
	SPACE,
}	t_token;
typedef struct s_tokens
{
	t_token token;
	char *str;
	struct s_tokens *next;
}	t_tokens;


int		ft_strlen(char *str);
char	*ft_strndup(char *str, int size);
/*
iswhat (char c)
quot			(c) == (")			= return : 1;
quot			(c) == (')			= return : 2;
space			(c) == ( )			= return : 3;
pipe			(c) == (|)			= return : 4;
redirection		(c) == (>)			= return : 5;
redirection		(c) == (<)			= return : 6;
var				(c) == ($)			= return : 7;
*/ 
int		iswhat(char c);

#endif