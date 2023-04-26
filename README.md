# Brainfudge
Brainfudge is a powerful brainfuck interpreter written in C++.

***Note: if you have a better name feel free to suggest***

**Brainfuck** is a simple language written by Ürban Muller. it is a esoteric programming language, meaning it's very minimalistic. The language is really hard and not practical, hence the name brainfuck, but it is fun coding with it. 
I saw many interpreters like <a href="copy.sh/brainfuck">El Brainfuck</a> a really cool one and others. I will probably mention them under.

But these interpreters are useless when we don't have Internet access, but this interpreter you just need the internet once, and then it's useable everytime.

the language only contains 8 valid characters **[ ] > < + - . ,** other characters 
will be ignore as comments. I added new characters, more like control-characters, 
like halts & comments & snapshot tokens.


# Speical Features

Brainfudge has a complete syntax highlighter, the syntax highlighter reads a file and outputs the colored tokens, with highlight to error or other stuff.

for more information about **Brainfuck** go to <a href="https://esolangs.org/wiki/Brainfuck">Esolangs brainfuck</a>

# Online Brainfuck interpreters 

As i said, there are many interpreters online, one of which and my favourite. 
**<a href="copy.sh/brainfuck">El Brainfuck</a>**. 
But when trying to find the best interpreter, I encountered many. Like: 


# Usage 
Brainfudge is a simple interpreter to understand.
just put the file to interpreter next to the software name. 

I may add ways to hook the interpreter to GUI apps.

for additional help, type **./bfudge -h**

# License 
Brainfudge is under the GNU General Public license. 
meaning the project is open-source and free from warranty. you can fork 
or clone the project and add your own features to the language or interpreter.

for more licensing information type **./bfudge -license**.

# Compile it & Run it
I provided a shell-script that does the work for you. 
just type the name of the program as positional-argument.

I will probably provide a release, but not for all machines.


# Syntax 


<table>
   <tr>
      <th>Syntax</th>
      <th>Utility</th>
   </tr>

   <tr>
      <td>'>'</td>
      <td>Moves the pointer 1 cell to the right</td>
   </tr>

   <tr>
      <td>'<'</td>
      <td>Moves the pointer 1 cell to the left</td>
   </tr>

   <tr>
      <td>'+'</td>
      <td>Increments the current location by one (if the cell is 255 before incremenetation then it overflows and carries to 0)</td>
   </tr>

  <tr>
      <td>'-'</td>
      <td>Decrements the current location by one (if the cell is 0 before decrementation then it overflows and carries to 255)</td>
  </tr>

  <tr>
      <td>'['</td>
      <td>A loop starter, similar to 'while(memory[ptr]!=0){', the cell value is zero, then skip to then next ']' without executing instructions.</td>
  </tr>

  <tr>
      <td>']'</td>
      <td>A loop ender, similar to '}', if the current cell is not zero, then go back to the nearest '['</td>
  </tr>

  <tr>
     <td>'.'</td>
     <td>Converts the cell value to ASCII Character and sends it to the standard output.</td>
  </tr>


  <tr>
     <td>','</td>
     <td>Fetches input from the standard input, and converts it to a byte number.</td>
  </tr>



</table>