#include "execute.h"

int is_valuable_token(enum e_token_kind kind)
{
	return (kind == TKN_TEXT || kind == TKN_S_QUOTE || kind == TKN_D_QUOTE || kind == TKN_ENV);
}