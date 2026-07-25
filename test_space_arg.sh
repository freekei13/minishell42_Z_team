#!/bin/bash
cd /home/csamakka/42School/minishell42_Z_team
echo "--- minishell ---"
printf 'echo a " "\n' | ./minishell 2>&1 | cat -A
echo "--- bash ---"
printf 'echo a " "\n' | bash 2>&1 | cat -A
