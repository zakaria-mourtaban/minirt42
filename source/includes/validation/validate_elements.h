/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_elements.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkraytem <mkraytem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 20:22:07 by mkraytem          #+#    #+#             */
/*   Updated: 2025/07/20 20:24:44 by mkraytem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VALIDATION_ELEMENTS_H
# define VALIDATION_ELEMENTS_H

void	validate_ambient(char **tokens, int count, int *a_flag);
void	validate_camera(char **tokens, int count, int *c_flag);
void	validate_light(char **tokens, int count, int *l_flag);

#endif 