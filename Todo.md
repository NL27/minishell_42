## Todo
	- parse_quotes 
    	- check quotes are closed and return an error for unclosed quotes
  	- Check if cmd is unquoted in lexer
    	- if not move to the nect cmd word
  	- Build Exec Env
    	- Open files inherited upon invocation of the shell, plus open files controlled by exec
    	- Working directory as set by cd
    	- File creation mask set by umask
    	- [XSI] [Option Start] File size limit as set by ulimit [Option End]
    	- Current traps set by trap
    	- environment inherited by the shell when it begins (see the export special built-in)
    	- Process IDs of the last commands in asynchronous lists known to this shell environment; see Asynchronous Lists
  
## Cases to handle
	- nested parameters
    	- $PATH$ARG
    	- terminating chars
  	- feild splitting
  	- assigment before command
    	-  hello=world ls
    	-  hello=$(PATH)
 	-  echo hello >
 	- order of heredocs and dir
 	- when quoted string is a file name with spaces, and the filename is
     	- saved in a variable
## Done


## Notes
	- redirection fails for all if a file in the chain can't be opened


## Lexing Steps
	- Toeknization and delimiting keep quotes
    	- parameter expansion
	- Word expansiom
    	- field splitting
    	- Quote removal
	- Shell Grammer
