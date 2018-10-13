# Set solver
Given a representation of *m* sets in set theory, compute their equivalence classes.

### Basic example
```
INPUT:
SET (1) = A + (B * C)
SET (2) = (A + B) * C
SET (3) = (A + B) * (A + C)

OUTPUT:
(1) = (3)
(2)
```
Given that + is set union and * is set intersection.
We can see that (1) and (3) are members of the same equivalence class, that is, they equal, but (2) is not, and so does not.

### A little bit of math
For any logical expression *P* that depends on some variable *x* and denoted as *P(x)* we define a *truth set* as a set any element of which makes *P(x)* true. That is

![Truth set of P(x) = {x | P(x)}](https://latex.codecogs.com/gif.latex?%5Ctext%7BTruth%20set%20of%20P%28x%29%20%7D%20%3D%20%5Cleft%20%5C%7B%20x%20%5Ctext%7B%20%7D%20%7C%20%5Ctext%7B%20%7D%20P%28x%29%20%5Cright%20%5C%7D)

Then given that set *A = {x | P(x)}* and set *B = {x | Q(x)}*, we can define basic operations on sets as follows:

![](https://latex.codecogs.com/gif.latex?%5Ctext%7BUnion%3A%20%7D%20A%20%5Ccup%20B%20%3D%20%5C%7B%20x%20%5Ctext%7B%20%7D%20%7C%20%5Ctext%7B%20%7D%20P%28x%29%20%5Cvee%20Q%28x%29%20%5C%7D)

![](https://latex.codecogs.com/gif.latex?%5Ctext%7BIntersection%3A%20%7D%20A%20%5Ccap%20B%20%3D%20%5C%7B%20x%20%5Ctext%7B%20%7D%20%7C%20%5Ctext%7B%20%7D%20P%28x%29%20%5Cwedge%20Q%28x%29%20%5C%7D)
![](https://latex.codecogs.com/gif.latex?%5Ctext%7BDifference%3A%20%7D%20A%20%5Csetminus%20B%20%3D%20%5C%7B%20x%20%5Ctext%7B%20%7D%20%7C%20%5Ctext%7B%20%7D%20P%28x%29%20%5Cwedge%20%5Cneg%20Q%28x%29%20%5C%7D)

###

Now, using the definition of *set-builder* notation

![](https://latex.codecogs.com/gif.latex?%5Ctext%7B%20%7D%20e%20%5Cin%20%5C%7B%20x%20%5Ctext%7B%20%7D%20%7C%20%5Ctext%7B%20%7D%20P%28x%29%20%5C%7D%20%5Ctext%7B%20%7D%20%5CRightarrow%20%5Ctext%7B%20%7D%20P%28e%29%20%3D%20True)

We can transform an expression written in set theory to an expression written in Boolean algebra!

For example

![](https://latex.codecogs.com/png.latex?%5Cbegin%7Balign*%7D%20x%20%26%5Cin%20%28A%20%5Ccup%20B%29%20%5Cbackslash%20C%20%5C%5C%20%28x%20%26%5Cin%20%28A%20%5Ccup%20B%29%29%20%5Cwedge%20%5Cneg%20%28x%20%5Cin%20C%29%20%5C%5C%20%28x%20%26%5Cin%20A%20%5Cvee%20x%20%5Cin%20B%29%20%5Cwedge%20%5Cneg%20%28x%20%5Cin%20C%29%20%5Cend%7Balign*%7D)

If we replace set theory notation by equivalent notation of Boolean algebra, i.e., *x*∈*A*, *x*∈*B*, *x*∈*C* to *P(x)*, *Q(x)*, *R(x)* respectively, we will result in a valid Boolean expression or, more strictly, a Boolean function from variable x.

![](https://latex.codecogs.com/png.latex?%5Cbegin%7Balign*%7D%20%26%28x%20%5Cin%20A%20%5Cvee%20x%20%5Cin%20B%29%20%5Cwedge%20%5Cneg%20%28x%20%5Cin%20C%29%20%26%20%5C%5C%20%26%28P%28x%29%20%5Cvee%20Q%28x%29%29%20%5Cwedge%20%5Cneg%20R%28x%29%20%26%20%5C%5C%20%26%28P%20%5Cvee%20Q%29%20%5Cwedge%20%5Cneg%20R%20%26%20%5Ctext%7B%28compact%20notation%29%7D%20%5Cend%7Balign*%7D)

And we finally have all pieces together! 
The only last thing we yet have to cover is the *equivalence of Boolean functions*.

For any function *P(x)* we can build up a *truth table*, where for each possible value of x we would write a corresponding value of *P(x)*. And we will say that two Boolean functions *P(x)* and *Q(x)* are equivalent only if their *truth tables are the same*.

The idea of such *equivalence* can be easily generalized onto more that one variable *x*. We will just write the table for all possible tuples of values of variables and the corresponding value of P(x, y, z, w, ...).

And so, to check if two sets are equal, we will parse given expression in set theory and convert it to Boolean algebra. Then compute truth tables for both expressions and compare them. 

![](https://latex.codecogs.com/png.latex?%5Ctext%7BResulting%20in%20time%20complexity%20%7DO%282%5En%29%20%5Ctext%7B%2C%20for%20n%20is%20the%20number%20of%20sets%7D.)

### Design conventions
Surely, this project would be to easy to do **dirty**. So, I say `NO!`.
Here is what I tried to follow will writing this:
1. Total modularity of the code
2. Ease of augmenting parser possibilities
3. Ease of extending the functionality

If I didn't follow them somewhere, I would be happy for a new pull request! <3

### Program structure
The program reads a string of characters, which is then tokenized by lexer using an implementation of [prefix tree](https://en.wikipedia.org/wiki/Trie). This gives the opportunity to define operators of more that one symbol in length and results in higher flexibility and speed. The implementation is abstract and can be stripped off for any other usage.

Then using a linear stack-based algorithm (great part of which is described [here (in Russian)](http://www.e-maxx-ru.1gb.ru/algo/expressions_parsing) and fully in the source code), the program builds [abstract syntax tree](https://en.wikipedia.org/wiki/Abstract_syntax_tree) (or AST for short) in order then to bruteforce every possible combination of values for sets.

The truth table for an expression can be represented as a bitmask (limited to 64 bits), which can then be put into **hash table** for quick access and modification. **HashMap** class is an abstract implementation of such table and can be stripped out freely too.

So, all in all
1. Read string
2. Tokenize (using **TokenStrip** class)
3. Build AST (using **AST** class)
4. Bruteforce AST
5. Hash the solution (Using **HashMap** class)
6. Print out equivalence classes

### Deployment
In order to compile the code, you have to use *cmake* and your *favorite* type of makefiles. That is, in the root of the project run
```
mkdir build
cd build
cmake .. -g "Unix Makefiles"
make
```
Instead of `"Unix Makefiles"` you can write another type if you want. 

### Acknowledgements
The idea of this project is inspired by the book ``"How To Prove It: A Structured approach" (2nd Edition)`` by brilliant author Daniel J. Velleman, to whom I give my biggest thanks.
