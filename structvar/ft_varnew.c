/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_varnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmuni-re <jmuni-re@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 14:52:57 by jmuni-re          #+#    #+#             */
/*   Updated: 2023/02/20 14:52:59 by jmuni-re         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_var *ft_varnew() {
  t_var *var;

  var = malloc(sizeof(t_var));
  if (var == NULL)
    return (NULL);
  var->next = NULL;
  init_struct(&var);
  return (var);
}
