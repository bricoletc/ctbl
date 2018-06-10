TODOs
----

* Define vocab_size, the number of distinct taxon. groups encountered 
* 

Planning
----

###Unfolding:

1. Traverse the Newick string, adding each word to a binary tree. 
2. Generate an array of pointers to the sorted words
3. Parse the Newick string with a recursive function which generates one character group per '()' enclosure.

###Modules:

* Newick_binTree for step 1.
* Newick_parser and binsearch for step 3.
* Gen_sorting for step 2.
