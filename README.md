TO DO LIST : 

• error messages to std2 


• <<EOF | echo crash 100 % DU TEMPS -------------- -> ça ne crash pas mais ça fait un saut de ligne avant d'afficher le heredoc

• minishell$ cat < echo  '"lol''lol"' ""lol"" '""'"lol"
    minishell: echo "lollol" lol ""lol: No such file or directory
     INSTEAD OF 
     % cat < echo  '"lol''lol"' ""lol"" '""'"lol"
    zsh: no such file or directory: echo

See discord for this one ().

echo 'exit 42' > test.sh

 chmod +x test.sh./test.sh
 
 echo $? returns 126 instead of 42
 
 minishell$ echo 'exit 42' > test.sh
 
 minishell$ chmod +x test.sh
 
 minishell$ ./test.sh
 
 minishell: ./test.sh: Exec format error
 
ctrl-\ nopy nope

