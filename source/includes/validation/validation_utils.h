/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_utils.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkraytem <mkraytem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 00:00:00 by 42student         #+#    #+#             */
/*   Updated: 2025/08/13 23:55:10 by mkraytem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VALIDATION_UTILS_H
# define VALIDATION_UTILS_H

void	validate_color_format(char *color_str, char **tokens);
void	validate_vector_format(char *vector_str, char **tokens);
void	validate_normalized_vector(char *vector_str, char **tokens);
void	validate_ratio(double ratio, char **tokens);
void	validate_fov(double fov, char **tokens);
void	validate_numeric_string(char *str, char **tokens);
void	validate_positive_double(char *str, char *element_name, char **tokens);

#endif 