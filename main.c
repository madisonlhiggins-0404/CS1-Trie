#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#DEFINE MAX_LETTERS 2000000
#DEFINE MAX_FREQ 1000000000

// INIT
struct trie* init() {
    struct trie* node = (struct trie*)malloc(sizeof(struct trie));
    node->isWord = 0;
    node->nodeFrequency = 0;
    node->prefixFrequency = 0;
    node->maxChildFrequency = 0;
    for (int i = 0; i < 26; i++) {
        node->next[i] = NULL;
    }
    return node;
}


// OG Insert 
void insert(struct trie* tree, char word[], int k) { //  cat

    // Down to the end, insert the word.
    if (k == strlen(word)) {
        tree->isWord = 1;
        return;
    }

    // See if the next place to go exists, if not, create it.
    int nextIndex = word[k] - 'a';
    if (tree->next[nextIndex] == NULL)
        tree->next[nextIndex] = init();

    insert(tree->next[nextIndex], word, k+1);
}

// MOD insert
//k = current index of the word
void insert(struct trie* tree, char word[], int k, int frequency) {
    // Base case: End of word
    if (k == strlen(word)) {
        tree->isWord = 1;
        tree->nodeFrequency += frequency;
        tree->prefixFrequency += frequency;
        return;
    }

    // Determine the index for the current character
    int index = word[k] - 'a';

    // If the child node doesn't exist, create it
    if (tree->children[index] == NULL) {
        tree->children[index] = init(); // Function to initialize a new trie node
    }

    // Update the prefix frequency at the current node
    tree->prefixFrequency += frequency;

    // Recursive call to the next character
    insert(tree->children[index], word, k + 1, frequency);

    // Update the maximum child frequency after returning from recursion
    if (tree->children[index]->prefixFrequency > tree->maximumChildFrequency) {
        tree->maximumChildFrequency = tree->children[index]->prefixFrequency;
    }
}

// QUERY
int query(struct trie* tree, char prefix[], char result[], int k, int* count){
  // Base case: processed entire word
  if (k == strlen(prefix)){
    int maxFrequency = tree->maxChildFreq;

    // Traverse all children to find most likely next letters
    for (int i = 0; i < 26; i++){
      
      if(tree->children[i] != NULL && tree->children[i]->prefixFreq == maxFrequency){
        // (char)('a' + 1) converts index i back into a character 
        result[(*count)] = (char)('a' + i); 
        // Increment count for next letter. 
        count++;
      }
    }

    return *count; 
    
  }

  // Recursive case: Go to next character in the prefix 
  int nextIndex = prefix[k] - 'a';
  if (tree->children[nextIndex] == NULL){ // Prefix does not exist
    *count = -1;// Unrecignized prefix
    return *count;
  }

  // Recursive call to the next character in the prefix
  query(tree->children[nextIndex], prefix, result, k + 1, count);
  
}

// QUERY WRAPPER
void queryWrapper(struct trie* tree, char prefix[]){
  char result[MAX_LETTERS];
  int count = 0;

  // Call recursive query function
  query(tree, prefix, result, 0, &count);

  // Print the result
  if(count == -1){
    printf("unerecognized prefix\n");
  } else if ( count > 0 ){
    result[count] = '\0';
    printf("%s\n", result);
  } else{
    printf("unrecognized prefix\n");
  }
  
}

void freeDictionary(struct trie* tree) {

    int i;
    for (i=0; i<26; i++)
        if (tree->children[i] != NULL)
            freeDictionary(tree->children[i]);

    free(tree);
}




// Input
 int main(){
   // initialize root of trie
   trie* dictionary = init();
   
   // n = number of commands
   int n, command, frequency; 
   char prefix[MAX_LETTERS];
   
   scanf("%d", &n);

   for(int i = 0; i < n; i++){
     // command
     scanf("%d", &command);
     if(command == 1){
       // word
       scanf("%s %d", prefix, &frequency);
       insert(dictionary, prefix, 0, frequency);
     }

     if(command == 2){
       // word
       scanf("%s", prefix);
       queryWrapper(dictionary, prefix);
     }
     
   }

   freeDictionary(dictionary);

   
 }