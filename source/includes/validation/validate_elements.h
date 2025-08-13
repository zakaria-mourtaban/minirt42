/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_elements.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkraytem <mkraytem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 22:57:06 by mkraytem          #+#    #+#             */
/*   Updated: 2025/08/13 23:54:27 by mkraytem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VALIDATE_ELEMENTS_H
# define VALIDATE_ELEMENTS_H

void	validate_ambient(char **tokens, int count, int *a_flag);
void	validate_camera(char **tokens, int count, int *c_flag);
void	validate_light(char **tokens, int count, int *l_flag);

#endif