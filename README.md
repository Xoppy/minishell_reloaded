TO DO LIST : 

• error messages to std2 

• minishell$ grep -r "lol" | ls CRASH QUAND LOL EXISTE PAS 

• ls | grep "gigalol" > test.txt print bien gigalol dans test mais ls | grep "gigalol" > test.txt | wc -l devrait print 1 et print 0 (compte de ligne)

• on bsh when doing ls -l > test.txt | wc -l it outputs 14, on ours outputs 0 

• cat << EOF > xptdr.txt mdr il crash 

• $USER quand l'env existe pas il pete un cable 

• <<EOF | echo crash 100 % DU TEMPS -------------- -> ça ne crash pas mais ça fait un saut de ligne avant d'afficher le heredoc

• touch "DAT FILE" me crée deux files au lieux de 'DAT FILE'

• minishell$ cat < echo  '"lol''lol"' ""lol"" '""'"lol"
    minishell: echo "lollol" lol ""lol: No such file or directory
     INSTEAD OF 
     % cat < echo  '"lol''lol"' ""lol"" '""'"lol"
    zsh: no such file or directory: echo


echo 'exit 42' > test.sh

 chmod +x test.sh./test.sh
 
 echo $? returns 126 instead of 42
 
 minishell$ echo 'exit 42' > test.sh
 
 minishell$ chmod +x test.sh
 
 minishell$ ./test.sh
 
 minishell: ./test.sh: Exec format error
 
ctrl-\ nopy nope

