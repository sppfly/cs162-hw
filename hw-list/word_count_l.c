/*
 * Implementation of the word_count interface using Pintos lists.
 *
 * You may modify this file, and are expected to modify it.
 */

/*
 * Copyright © 2021 University of California, Berkeley
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef PINTOS_LIST
#error "PINTOS_LIST must be #define'd when compiling word_count_l.c"
#endif

#include "word_count.h"

void init_words(word_count_list_t* wclist) { /* TODO */
  list_init(wclist);
}

size_t len_words(word_count_list_t* wclist) {
  size_t i = 0;
  struct list_elem* e;
  for (e = list_begin(wclist); e != list_end(wclist); e = list_next(e)) {
    i++;
  }
  return i;
}

word_count_t* find_word(word_count_list_t* wclist, char* word) {
  struct list_elem* e;
  for (e = list_begin(wclist); e != list_end(wclist); e = list_next(e)) {
    word_count_t* word_count = list_entry(e, word_count_t, elem);
    if (strcmp(word_count->word, word) == 0) {
      return word_count;
    }
  }
  return NULL;
}

word_count_t* add_word(word_count_list_t* wclist, char* word) {

  word_count_t *word_count = NULL;
  if ((word_count = find_word(wclist, word)) != NULL) {
    word_count->count++;
    return word_count;
  } 
  word_count = malloc(sizeof(word_count_t));
  if (word_count == NULL) {
    perror("malloc failure");
    exit(EXIT_FAILURE);
  }
  char* string = malloc(strlen(word) + 1);
  if (string == NULL) {
    perror("malloc failure");
    exit(EXIT_FAILURE);
  }
  strcpy(string, word);
  word_count->count = 1;
  word_count->word = string;
  list_push_back(wclist, &word_count->elem);
  return word_count;
}

void fprint_words(word_count_list_t* wclist, FILE* outfile) { /* TODO */
  struct list_elem* e;
  for (e = list_begin(wclist); e != list_end(wclist); e = list_next(e)) {
    word_count_t* word_count = list_entry(e, word_count_t, elem);
    fprintf(outfile, "%*d%*s\n", 10, word_count->count, 20, word_count->word);
  }
}

static bool less_list(const struct list_elem* ewc1, const struct list_elem* ewc2, void* aux) {
  word_count_t* word_count1 = list_entry(ewc1, word_count_t, elem);
  word_count_t* word_count2 = list_entry(ewc2, word_count_t, elem);
  if (word_count1->count == word_count2->count) {
    return strcmp(word_count1->word, word_count2->word) <= 0;
  }
  return word_count1->count < word_count2->count;
}

void wordcount_sort(word_count_list_t* wclist,
                    bool less(const word_count_t*, const word_count_t*)) {
  list_sort(wclist, less_list, less);
}
