# Colors for output
CYAN		:=	\033[36m
BOLD		:=	\033[1m
GREEN		:=	\033[32m
MAGENTA		:=	\033[35m
END			:=	\033[0m

# Compiler and flags
CC = cc
CFLAGS = -Wall -Werror -Wextra -lreadline #-fsanitize=address -g3
# MAKEFLAGS += --no-print-directory
# Directories
OBJS_DIR = objs

# Source files
LEXER_SRCS = LEXER/lexer.c LEXER/node.c LEXER/utils.c
PARSER_SRCS = PARSER/ast.c PARSER/expand.c PARSER/expand_utils.c PARSER/parser.c PARSER/wildcard.c PARSER/wildcard_utils.c
SRCS = $(LEXER_SRCS) $(PARSER_SRCS)

# Object files
OBJS = $(patsubst %.c, $(OBJS_DIR)/%.o, $(SRCS))

# Output executable
NAME = minishell

# Libft
LIBFTPATH = libft
LIBFT = $(LIBFTPATH)/libft.a

# Targets
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(OBJS) $(CFLAGS) $(LIBFT) -o $@
	@printf "$(GREEN)$(BOLD)> $(NAME) made successfully.$(END)\n"

$(OBJS_DIR)/%.o: %.c Makefile includes/minishell.h
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(OBJS_DIR)/LEXER $(OBJS_DIR)/PARSER
	@$(CC) $(CFLAGS) -c $< -o $@ 
	@printf "$(CYAN) > Compilation :$(END) $<\r"

$(LIBFT): $(LIBFTPATH)
	@make -C $(LIBFTPATH)

clean:
	@make -C $(LIBFTPATH) clean 
	@rm -rf $(OBJS_DIR)
	@printf "$(CYAN)=> removed objs successfully.$(END)\n"

fclean: clean
	@rm -f $(NAME)
	@rm -f $(LIBFT)
	@printf "$(CYAN)=> removed $(LIBFT) successfully.$(END)\n"
	@printf "$(CYAN)=> removed $(NAME) successfully.$(END)\n"

re: fclean all

.PHONY: all libft clean fclean re
# .SILENT: