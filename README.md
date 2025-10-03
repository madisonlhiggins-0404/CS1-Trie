Trie Project 

Features: 

Insert words with frequencies: Each word has a frequency that updates node, prefix, and max-child frequencies.

Prefix query: Given a prefix, the program returns the most likely next characters based on stored frequencies.

Each node tracks:

wordFreq → frequency of a complete word ending at this node.

prefixFreq → total frequency of words with this prefix.

maxChildFreq → frequency of the most common child path.

Wrapper functions: queryWrapper() handles prefix lookups and user-friendly output.

Memory management: freeDictionary() cleans up all dynamically allocated trie nodes.


Usage

The program accepts commands via standard input:

Insert a word with frequency.

Query a prefix.


Functions

init() → create a new trie node.

insert(struct trie* tree, char word[], int k, int frequency) → insert a word with frequency.

query() → recursive helper to find likely continuations.

queryWrapper() → wrapper for user-friendly queries.

freeDictionary() → deallocate all trie nodes.


What I Learned

How Tries efficiently represent dictionaries of words.

Using frequencies to enhance predictions (like autocomplete).

Recursive vs. iterative design for inserts and queries.

Managing dynamic memory in C for tree structures.
