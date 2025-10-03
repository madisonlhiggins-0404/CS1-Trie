// Trie Node Structure

type def struct trie{
  int wordFreq;
  int prefixFreq;
  int maxChildFreq;
  trie* next[26];
}

struct trie* init();
void insert(struct trie* tree, char word[], int k, int frequency);
int query(struct trie* tree, char prefix[], char result[], int k, int count);
void queryWrapper(struct trie* tree, char prefix[])
void freeDictionary(struct trie* tree);



