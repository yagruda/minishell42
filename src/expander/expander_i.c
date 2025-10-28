/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_i.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhruda <yhruda@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 16:37:04 by yhruda            #+#    #+#             */
/*   Updated: 2025/10/24 17:56:59 by yhruda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Join string with single character (helper function)
static char *ft_strjoin_char(char *s, char c)
{
    char *result;
    int len;
    int i;

    if (!s)
        return NULL;
    len = ft_strlen(s);
    result = malloc(len + 2);
    if (!result)
        return NULL;
    i = 0;
    while (s[i])
    {
        result[i] = s[i];
        i++;
    }
    result[i] = c;
    result[i + 1] = '\0';
    return result;
}

// Get env variable value
static char *get_env_value(char *var, t_shell *shell)
{
    int i = 0;
    int len = ft_strlen(var);

    while (shell->envp[i])
    {
        if (ft_strncmp(shell->envp[i], var, len) == 0 &&
            shell->envp[i][len] == '=')
            return shell->envp[i] + len + 1;
        i++;
    }
    return "";
}

// Extract variable name after $
static char *extract_var_name(char *str, int *len)
{
    int i = 0;

    if (str[0] == '?')  // Special case: $?
    {
        *len = 1;
        return ft_strdup("?");
    }

    while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
        i++;
    
    *len = i;
    return ft_substr(str, 0, i);
}

// Expand $VAR in string
static char *expand_vars(char *str, t_shell *shell)
{
    char *result = ft_strdup("");
    char *var_name;
    char *var_value;
    char *temp;
    int i = 0;
    int var_len;
    int in_squote = 0;

    while (str[i])
    {
        if (str[i] == '\'' && !in_squote)
            in_squote = 1;
        else if (str[i] == '\'' && in_squote)
            in_squote = 0;
        
        // Expand only outside single quotes
        if (str[i] == '$' && !in_squote && str[i + 1])
        {
            i++;
            var_name = extract_var_name(&str[i], &var_len);
            
            if (ft_strcmp(var_name, "?") == 0)
                var_value = ft_itoa(shell->exit_code);
            else
                var_value = ft_strdup(get_env_value(var_name, shell));
            
            temp = result;
            result = ft_strjoin(result, var_value);
            free(temp);
            free(var_name);
            free(var_value);
            i += var_len;
        }
        else
        {
            temp = result;
            result = ft_strjoin_char(result, str[i]);
            free(temp);
            i++;
        }
    }
    free(str);
    return result;
}

// Remove quotes from string
static char *remove_quotes(char *str)
{
    char *result = ft_strdup("");
    char *temp;
    int i = 0;
    char quote = 0;

    while (str[i])
    {
        if ((str[i] == '\'' || str[i] == '"') && quote == 0)
            quote = str[i];
        else if (str[i] == quote)
            quote = 0;
        else
        {
            temp = result;
            result = ft_strjoin_char(result, str[i]);
            free(temp);
        }
        i++;
    }
    free(str);
    return result;
}

// Main expander
void expander(t_shell *shell)
{
    t_cmd *cmd = shell->cmd_list;
    t_redir *redir;
    int i;

    while (cmd)
    {
        // Expand arguments
        i = 0;
        while (cmd->argv && cmd->argv[i])
        {
            cmd->argv[i] = expand_vars(cmd->argv[i], shell);
            cmd->argv[i] = remove_quotes(cmd->argv[i]);
            i++;
        }
        
        // Expand redirect filenames
        redir = cmd->redir;
        while (redir)
        {
            redir->file = expand_vars(redir->file, shell);
            redir->file = remove_quotes(redir->file);
            redir = redir->next;
        }
        
        cmd = cmd->next;
    }
}