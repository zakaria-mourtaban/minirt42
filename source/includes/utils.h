/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkraytem <mkraytem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 11:00:00 by zmourtab          #+#    #+#             */
/*   Updated: 2025/08/13 23:55:48 by mkraytem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

double	degrees_to_radians(double degrees);
double	ft_atof(const char *str);
int		ft_strarrlen(char **arr);
void	ft_free_split(char **arr);
void	error_exit(const char *msg, char **tokens);

#endif