/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfusil <mfusil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 18:54:31 by mfusil            #+#    #+#             */
/*   Updated: 2023/01/26 17:27:32 by mfusil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// ctrl c = SIGINT
// ctrl d = SIGQUIT

void handler_sig(int signum) {
  if (signum == SIGINT) {
    printf("\n");
    rl_on_new_line();
    // rl_replace_line("", 0);
    rl_redisplay();
  } else if (signum == SIGQUIT) {
    rl_on_new_line();
    rl_redisplay();
    printf("  \b\b");
  }
}
