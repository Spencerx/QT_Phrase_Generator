# QT Phrase Generator

A goofy side project to model/test the idea of a Markov chain and apply it to phrase generation, as well as to test the waters with QT.
The program takes in a text file* and depending on the block size (or n-gram size) given, spits out a phrase based on what it just read.

# Credit

Dunno where to give credit, but here seems fitting.  The idea came from Daniel Shiffman (https://twitter.com/shiffman) and his YouTube
series, where he models a comparable program using JavaScript, but HIS idea for it came from the great Allison Parrish
(http://www.decontextualize.com/)

senate-bills.txt lovingly borrowed from
https://github.com/jsvine/markovify/tree/master/test/texts

## Getting Started

Use whatever text file appeals to you; included in the test folder are a series of bills from the senate in 2015, and a formatted
version of Shakespeare's A Midsummer Night's Dream.  If you don't like them, find or make a text file that appeals to you; I have
also (crudely) written a python script to slmost format a text file like the program truly wants to be happy.

The ideal text file is formatted so that each sentence (or phrase, as seen in my Shakespeare file; a pox upon the Bard
and his prose) is on a new line.

### Prerequisites

* QT 5.10 or newer (required for the brand-spankin' new random generator functions)
* A compatible C++ compiler
* Python 3 if you want to run my crappy text file formatter

### Installing

If you can compile with QT 5.10, then to quote Emperor Palpatine, "Do it."

## Running the tests

I wouldn't call them "test" cases so much as just "playing around with text files."

Output stops generating text upon reaching a period (full-stop), an n-gram with no matches, or a 500 char limit has been reached.

Since this program randomly selects a possible letter that comes after an n-gram (read: chunk of sequential characters of size n)
then it should be fairly obvious (especially after trying it for yourself!) that the lower the size of the n-gram, the less and less
the output will look like English.

Things I noticed on n-gram sizes here:
Size -> fun fact
* 1 -> gibberish
* 3 -> Middle English
* 4, 5 -> Readable English, but probably not grammatically correct
* 8+ -> Here it just starts ripping phrases directly out of the text file


## Built With

* C++
* QT Creator 4.5.2 Community using QT version 5.10
* A little TLC


## Contributing

HMU: tston529 (at) live (dot) kutztown (dot) edu

## Authors

* **Tyler Stoney** - *Initial work*

## License

No licensing as of yet, I doubt this is going anywhere.

Feel free to use, modify, fiddle around with it, go nuts.

## Final Words

* A tip of the hat to anyone who helps
* A wag of the finger to anyone who tries to pass off my garbage as their own garbage
* etc.


