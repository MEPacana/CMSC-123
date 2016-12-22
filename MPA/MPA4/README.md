# MPA4 - The General's Daughter, err, Tree
Implement a tree-structured directory. The following are the minimum requirements for the tree:

The class node that represents a node in a general tree.
The item for the node should be a file descriptor (it is best to have a separate class for this or you can also incorporate it in the node class). A file descriptor will contain information as to whether the node is a file or a directory, including the time and date it was created and modified if applicable.
The class general tree. It should have the following minimum operations:
an insert method that allows the user to add new directories or files (nodes)
a delete method that allows the user to delete files and directories
a search function that is able to determine whether a given file or directory exists
NOTE: DO NOT CONFUSE THE COMMANDS FROM THE AFOREMENTIONED OPERATIONS. TOO, ADDITION OF AUXILIARY FUNCTIONS/METHODS IS ALLOWED.

A separate class that will handle the simulation must be implemented as well. This simulation class shall contain at least a general tree object to represent the file system. For the simulation, the following commands must be implemented:

Creation and deletion of directories (mkdir, rmdir)
mkdir <directory name>, e.g. mkdir movies, mkdir /root/rcmdulaca/cmsc123 (optional)
rmdir <directory name>, e.g. rmdir movies, rmdir /root/rcmdulaca/cmsc123 (optional)
Navigation of the system (change directory, cd)
cd movies, cd /root/rcmdulaca/cmsc123 (optional)
cd.. - goes one level up the tree directory or goes to the parent directory
Creation of files
This can be best implemented as how the cat command in linux works when used together with ">" and ">>"
> myfile
creates the file myfile. If it exists, it overwrites it. Allow the user to enter contents into the file either via the console or by launching a text editor.
>> myfile
edits the file myfile (append only). If the file does not exist, create this file. Allow the user to enter contents in the file either via the console or by launching a text editor.
edit <filename>, e.g. edit file1.txt, edit /root/rcmdulaca/cmsc123/longexam3.doc (if does not exit, create file. If file exists, show the contents of the file and allow the file to be appended with additional texts.
Deletion of files (rm)
rm <filename>, rm file1.txt, /root/rcmdulaca/cmsc123/longexam3.doc, rm *.doc
Editing of files (append only)
check creation of files
Moving of files
Renaming of files (rn) - rn <filename> <new filename>, rn file1.txt file.txt
Transferring of files from one directory to another (mv) - mv file.txt /root/rcmdulaca/cmsc123
if the directory is non-existent, it simply renames the directory to that new one. But if the directory exists, it moves the directory/file there (the behavior is the same when an absolute/relative path is provided).
Copying of files and directories (cp) - cp <filename> <copy filename>, cp file1.txt file1copy.txt
Display of contents of the current directory or of any directory specified through an absolute path. Display the information in the file descriptor as well. Allow the use of wildcards (i.e. '*' and regex).
ls *.doc - displays all files that .doc in its filename
ls - displays all files in the current directory directory
(optional) ls /root/rcmdulaca/cmsc123 - displays all files in the specified directory
Display of the contents of a particular file.
show <filename>, e.g. show file1.txt
A search command that will tell the user the exact path of the file or directory where the input filename or directory name can be found. If there are multiple entries found, display all.
whereis <filename/directory>, e.g. whereis file1.txt, whereis cmsc123
NOTE 1: The moment the simulator is running, it should read the file "mp4.in" and perform the commands found in the file. Each command is found in one line. If the command will have a visible output (like ls), print that to a file named "mp4.out".  Do not exit from the program once this is done.

For those who will be developing a graphical user interface, make sure all commands will be implemented. To demonstrate absolute and relative paths, an "address bar" should be included. Also, provide a way to edit files (a simple text editor may be implemented). For searching, make sure that regular expressions are handled.

Absolute and relative path are optional.
