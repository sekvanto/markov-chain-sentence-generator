# Markov chain sentence generator
This console program takes a text file, trains based on the content, and produces a random string by a Markov chain ;D.

There are 2 modes:
1. Normal mode - Generates only one sentence
2. Shitposting mode - Generates many short sentences one by one

## Mechanism
The mechanism is simple, let's see an example. First, dictionary is generated from separate words of a text file.

E.g. we have a dictionary ["in", "the", "area", "of", "the", "south"] generated from source file

Next, ngrams are generated from the dictionary. An example of all possible 2-order ngrams:

in the
the area
area of
of the
the south

One ngram is randomly chosen. For example, let it be "in the"

Next, we choose "good" ngrams from the list - these, the first word of which starts with "the" (to continue current sentence):

the area
the south

We randomly choose one of them. Let it be "the south". Now we add it to the sentence, and get:

"in the south"

Unfortunately, there is no ngrams, which start with "south", so we add a dot and output a finished sentence. If we use long text, e.g. books, we got much more possible interesting combinations ;D

![test](images/example1.jpg)
