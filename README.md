# Simple Command Helper
Simple Command helper for not to write out multiple commands "every time"

And with "simple", it means very simple! So simple that it just contains some "for" loops and a basic file reading ifstream!
Please don't laugh at me while reading the code! ^_^

# Usage
Tired of typing multiple command while compiling some program? Or setting up some server like thing?
If yes, then Simple Command Helper is here to help you!
Just define your commands in a codefile(situated in the same directory in which you want to run commands).
Just type-
$ sch "yourFunctionName"
Replace "yourFunctionName" with the actual function name defined within codefile(and yeah without quotes!).
The syntax style for codefile is given in the next section!

# Syntax Style for codefile
Have you ever written HTML? If yes, then it is going to be familiar!
If not then its not that much hard!
Suppose this codefile-

<fun>echo sch is great!;<fun>
  
If this is saved to the codefile, sch will read it and extract function name, i.e fun, and the command for this function, i.e echo sch is great.
If you will type in terminal-
$ sch fun
It will push "echo sch is great!" to the shell, and we all know what echo does!
Each and every command inside a function should end with ";".
You can define as many functions you want!
To define variables add in codefile-

(var)echo(var)

Now to use this in a fucntion-
<fun>$var$ sch is great!<fun>
  
It will replace $var$ with "echo" and execute same as above.

Each variable name should be in () brackets and after defining variable, line should end with same name inside ().
To use variables write its name and surround it with '$' sign.

# Example codefile used in compiling sch 2.0 itself
(CC)g++(CC)
(flags)-o bin/sch(flags)
(cleaner)rm -rf(cleaner)

<build>$CC$ $flags$ main.cpp;echo Done!;<build>
<clean>$cleaner$ bin/;<clean>
  
  
And yeah that's it! You may think it as "make" program but very minimal and simple!
And it can be used for anything which requires manual entering of multiple commands.
