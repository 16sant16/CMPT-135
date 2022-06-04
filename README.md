# Assignment 1: Basic C++ Features

Your task in this assignment is to re-acquaint yourself with basic programming
features of C++. We'll do this using a simple game called Even Wins.

## Getting Started

A complete implementation of Even Wins is given in the file
[evenwins.cpp](evenwins.cpp). Please download it, along with
[makefile](makefile) and [cmpt_error.h](cmpt_error.h). Compile [evenwins.cpp](evenwins.cpp) like this:

```bash
$ make evenwins
g++  -std=c++17 -Wall -Wextra -Werror -Wfatal-errors -Wno-sign-compare -Wnon-virtual-dtor -g   evenwins.cpp   -o evenwins
```

Make sure [makefile](makefile) is in the same folder, and that you see `g++`
called will all the options shown in here.

After successfully compiling it, you run it like this:

```bash
$ ./evenwins
Welcome to Even Wins!
...
```

The instructions for playing the game are printed on the screen. Play it a few
times so you understand how it works, and have an idea of some winning
strategies.


## Questions

For each question, put your code in the corresponding file. Later files should
include answers to all previous questions, e.g. `evenwins3.cpp` should contain
your answer to question 1, 2, and 3.

### Question 1: A Better Title

When the program starts, the program title is written like this:

```
Welcome to Even Wins!
```

Modify [evenwins.cpp](evenwins.cpp) so the title is printed in a text box like
this:

```
+-----------------------+
| Welcome to Even Wins! |
+-----------------------+
```

Put your updated code in `evenwins1.cpp`.


### Question 2: An Enumerated Type for Turns

In [evenwins.cpp](evenwins.cpp), the variable `whose_turn` has type `string`.
However, we only care about two strings: `"human"` and `"computer"`. If we
mis-type these strings then errors will occur.

We can get the compiler to help catch these errors by using an **enumerated
type**. To do this, replace the declaration `string whose_turn` with this:

```
enum class Player {
    human,
    computer
};

Player whose_turn;
```

Now `whose_turn` is a variable of type `Player`, and it can only be assigned
values `Player::human` or `Player::computer`, e.g.:

```
whose_turn = Player::human;
```

If you try to assign it any other value, the compiler will stop with an error:

```
whose_turn = human; // compiler error!
```

You can also test if `whose_turn` has a particular value:

```
if (whose_turn == Player::computer) {
	// ...
}
```

Modify `evenwins1.cpp` to use `Player` for `whose_turn` instead
of `string`. Put your updated code in `evenwins2.cpp`.


### Question 3: Wins and Losses

Modify `evenwins2.cpp` so that at the end of every game it tells the user how
many games they and the computer have won, e.g.:

```
  Statistics
  ----------
   total games: 7
    human wins: 5
 computer wins: 2
```

Put your updated code in `evenwins3.cpp`.


### Question 4: Random Taunts

When the computer wins a game, it prints a *taunt* "tremble before it's mighty
brain!":

```
cout << "The computer wins: tremble before it's mighty brain!\n";
```

Modify `evenwins3.cpp` so that it prints a randomly chosen taunt each time the
computer wins a game. Choose at least 5 different taunts (one of them can be
the one already in the program), and make your taunts kid-friendly.

Put your updated code in `evenwins4.cpp`.


### Question 5: Removing Global Variables

In general, global variables are a *bad* idea in programming because it can be
very difficult to know when they change, and which part of a program changes
them. Global variables might not cause problems in *small* programs, but as
your programs get bigger and more complex, global variables are more and more
likely to be the reason for subtle and hard to fix problems.

Modify `evenwins4.cpp` so it has *no global variables*. To do this, implement
a struct called `Gamestate` that looks like this:

```
struct Gamestate {
    //
    // ... all variables needed for a game go here ...
    //
};
```

Then create one `Gamestate` struct inside `main`, and pass it to, and return
it from, functions as needed. To return values, you can use pass-by-reference.

Global *constants* are permitted, i.e. variables declared using `const` are
permitted since they can't be changed.

Put your updated code in `evenwins5.cpp`.


### Question 6: The ? : Operator

Modify `evenwins5.cpp` so that the `next_player` functions uses the `?` `:`
operator. The entire body of `next_player` should use a single
`;`!

The `?` `:` operator has the general form `cond ? true_val : false_val`.
`cond` is a `bool` expression that evaluates to `true` or `false`. If it
evaluates to `true`, then the entire expression evaluates to `true_val`.
Otherwise, if `cond` evaluates to `false`, then the entire expression
evaluates to `false_val`.

Put your updated code in `evenwins6.cpp`.


### Question 7: A Better Computer Player

Modify `evenwins6.cpp` so that computer plays better than random. Think of a
strategy of your own, and implement it in `computer_turn`.

As part of your answer, include a comment at the top of `computer_turn` that
uses full sentences of grammatical and correctly spelled English to:

- Explains how your strategy works.
- Explains if your strategy is *perfect*, i.e. does it always win when
  possible? Either explain *how* you know it's perfect, or describe a case
  where it doesn't play perfectly. Saying something like "I couldn't find any
  case where it played poorly" is no guarantee that the computer plays
  perfectly!

Put your updated code in `evenwins7.cpp`.


## Submit Your Work

Please submit only *one `.cpp` file*. If you answered all the questions, then
submit just `evenwins7.cpp`. If you didn't answer all questions, then submit
the evenwins file with the highest question you did answer. For example, if
you answered 5 questions, then submit just `evenwins5.cpp`.

**Don't** submit more than one `.cpp` file. If you do, then only the
highest-numbered evenwins file will be marked.

**Do not submit** [evenwins.cpp](evenwins.cpp), [makefile](makefile),
[cmpt_error.h](cmpt_error.h), **or any other files**. Copies of
[makefile](makefile) and [cmpt_error.h](cmpt_error.h) will be put in the same
folder as your `.cpp` file when the marker runs your program.

## Basic Requirements

Before we give your program any marks, it must meet the following basic
requirements:

- It must compile on Ubuntu Linux using [the standard course
  makefile](makefile), e.g.:

  ```console
  $ make evenwins7 
  g++  -std=c++17 -Wall -Wextra -Werror -Wfatal-errors -Wno-sign-compare -Wnon-virtual-dtor -g   evenwins7.cpp   -o evenwins7
  ```

  If your program fails to compile, your mark for this assignment will be 0.

  [cmpt_error.h](cmpt_error.h) will be put in the same folder, so your program
  can use `cmpt::error` if necessary.

- It must have no memory leaks, according to `valgrind`, e.g.:

  ```console
  $ valgrind ./evenwins7
    
  // ... lots of output ... 
  ```

  A program is considered to have no memory leaks if:

  - In the `LEAK SUMMARY`, `definitely lost`, `indirectly lost`, and
    `possibly lost` must all be 0.

  - `ERROR SUMMARY` reports 0 errors.

  - It is usually okay if **still reachable** reports a non-zero number of
    bytes.

  If `valgrind` reports any errors for your program, your mark for the
  assignment will be 0.

- **You must include the large comment section with student info and the
  statement of originality**. If your submitted file does not have this, then
  we will assume your work is not original, and it will not be marked.
  
If your program meets all these basic requirements, then it will graded using
the marking scheme below.


## Marking Scheme

### Source Code Readability (6 marks)

- All names of variables, functions, structs, classes, etc. are sensible,
  self-descriptive, and consistent.

- Indentation and spacing is perfectly consistent and matches the structure of
  the program. All blank lines, indents, and extra spaces have a reason.

- All lines are 100 characters in length, or less.

- Comments are used when appropriate, e.g. to describe code that is tricky or
  very important. There are no unnecessary comments, and no commented-out
  code.

- Appropriate features of C++ are used in an appropriate way. For example, do
  **not** use a feature of C (like C-style strings) when there is a better
  feature of C++ (e.g. the standard `string` class). Don't use any features
  you don't understand. Markers may ask you to explain any part of your code.

- Overall, the source code is easy to read and understand. All the
  instructions for naming and submitting it were followed.


### Questions (8 marks)

- Question 1: **1 mark** for a complete and correct implementation.
- Question 2: **1 mark** for a complete and correct implementation.
- Question 3: **1 mark** for a complete and correct implementation.
- Question 4: **1 mark** for a complete and correct implementation.
- Question 5: **1 mark** for a complete and correct implementation.
- Question 6: **1 mark** for a complete and correct implementation.
- Question 7: **2 marks** for a complete and correct implementation. The
  computer does *not* need to play perfectly, but it should use a non-trivial
  strategy of *at least 10 lines of code*. A comment (with complete sentences
  and perfect spelling and grammar) is provided as described in the question.
