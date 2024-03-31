/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_num.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 14:38:30 by toshi             #+#    #+#             */
/*   Updated: 2024/03/31 16:58:31 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdio.h"
#include "stdlib.h"
#include "limits.h"

int main(int argc, char **argv)
{
	char num = (char)atoi(argv[1]);
	unsigned char subnum = (unsigned char)num;
	printf("%d %u\n", num, subnum);
}