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
exit
EOF

# After this script finishes, inspect valgrind_log.txt for leaks.
