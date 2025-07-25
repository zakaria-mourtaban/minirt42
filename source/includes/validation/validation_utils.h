/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_utils.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 42student <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 00:00:00 by 42student         #+#    #+#             */
/*   Updated: 2024/07/14 00:00:00 by 42student        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VALIDATION_UTILS_H
# define VALIDATION_UTILS_H

void	validate_color_format(char *color_str);
void	validate_vector_format(char *vector_str);
void	validate_normalized_vector(char *vector_str);
void	validate_ratio(double ratio);
void	validate_fov(double fov);
void	validate_numeric_string(char *str);
void	validate_positive_double(char *str, char *element_name);

#endif 