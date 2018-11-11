#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "9cc.h"

// pが指している文字列をトークンに分割してtokensに保存する
void tokenize(char *p) {
  int i = 0;
  while (*p) {
    if(DEBUG) {
      printf("tokenize char[%c]\n", *p);
    }
    // 空白文字をスキップ
    if (isspace(*p)) {
      p++;
      continue;
    }

    //if (*p == '+' || *p == '-') {
    if (*p == '+' || *p == '-' || *p == '*' || *p == '/') {
      tokens[i].ty = *p;
      tokens[i].input = p;
      i++;
      p++;
      continue;
    }

    if (isdigit(*p)) {
      tokens[i].ty = TK_NUM;
      tokens[i].input = p;
      tokens[i].val = strtol(p, &p, 10);
      i++;
      // 数字文スキップ
      while(isdigit(*p)) {
				p++;
      }
      continue;
    }

    fprintf(stderr, "トークナイズできません: %s\n", p);
    exit(1);
  }

  tokens[i].ty = TK_EOF;
  tokens[i].input = p;

  if(DEBUG) {
 		printf("%d 個のトークンを処理しました。\n", i);
    dumpTokens(i);
  }
}
