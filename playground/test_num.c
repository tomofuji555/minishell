/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_num.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 14:38:30 by toshi             #+#    #+#             */
/*   Updated: 2024/04/07 12:07:06 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdio.h"
#include "stdlib.h"
#include "limits.h"

int main(int argc, char **argv)
{
	int num = atoi(argv[1]);
	char c_num = (char)num;
	unsigned char uc_num = (unsigned char)num;
	printf("int=%d; char=%d; uchar=%u\n", num, c_num, uc_num);
}