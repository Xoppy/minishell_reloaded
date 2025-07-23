#!/usr/bin/env bash

# Run your minishell under Valgrind with full leak checking,
# show all kinds of leaks, verbose output, origin tracking,
# and write the Valgrind report to valgrind_log.txt.
valgrind \
  --leak-check=full \
  --show-leak-kinds=all \
  --track-origins=yes \
  --verbose \
  --log-file=valgrind_log.txt \
  --suppressions=readline.supp \
  --trace-children=no \
  ./minishell <<'EOF'
echo Hello, world!
pwd
cd ..
pwd
export TESTVAR=42
echo $TESTVAR
unset TESTVAR
env
ls | grep minishell
echo redirected > out.txt
cat < out.txt
rm out.txt
cat <<EOD
line1
line2 /home/ituriel
EOD
echo quoted /usr/bin/zsh and literal \$SHELL
foobar_command
exit
EOF

# After this script finishes, inspect valgrind_log.txt for leaks.
