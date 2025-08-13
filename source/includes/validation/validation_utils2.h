/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_utils2.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkraytem <mkraytem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 00:00:00 by 42student         #+#    #+#             */
/*   Updated: 2025/08/13 23:55:21 by mkraytem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VALIDATION_UTILS2_H
# define VALIDATION_UTILS2_H

int		is_valid_number(char *str);
void	validate_numeric_string(char *str, char **tokens);
void	validate_color_format(char *color_str, char **tokens);
void	validate_vector_format(char *vector_str, char **tokens);
void	validate_normalized_vector(char *vector_str, char **tokens);

#endif 