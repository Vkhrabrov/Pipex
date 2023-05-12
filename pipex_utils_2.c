/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhrabro <vkhrabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 22:47:05 by vkhrabro          #+#    #+#             */
/*   Updated: 2023/05/12 23:30:35 by vkhrabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char findFirstDelimiter(const char *str, const char *delimiters) {
    while (*str) {
        if (ft_strchr(delimiters, *str)) {
            return *str;
        }
        str++;
    }
    return '\0'; // Return null character if no delimiter found
}