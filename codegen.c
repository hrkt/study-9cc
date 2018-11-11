#include "9cc.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// トークナイズした結果のトークン列はこの配列に保存する
// 100個以上のトークンは来ないものとする
Token tokens[100];

int pos = 0;

// エラーを報告するための関数
void error(char *msg, char *detail) {
  fprintf(stderr, msg, detail);
  exit(1);
}

void debug(char *msg) {
  if (DEBUG) {
    fprintf(stderr, "%s", msg);
  }
}

void dumpTokens(int maxPos) {
  if (DEBUG) {
    for (int i = 0; i < 100 && tokens[i].ty != TK_EOF; i++) {
      printf("TOKEN,I=%d,TY=%d,INPUT=%s\n", i, tokens[i].ty, tokens[i].input);
    }
  }
}

Node *new_node(int op, Node *lhs, Node *rhs) {
  Node *node = malloc(sizeof(Node));
  node->ty = op;
  node->lhs = lhs;
  node->rhs = rhs;
  return node;
}

Node *new_node_num(int val) {
  Node *node = malloc(sizeof(Node));
  node->ty = ND_NUM;
  node->val = val;
  return node;
}

Node *term() {
  if (tokens[pos].ty == TK_NUM) {
    if (DEBUG) {
      debug("数値ノードを生成\n");
    }
    return new_node_num(tokens[pos++].val);
  }
  if (tokens[pos].ty == '(') {
    pos++;
    Node *node = expr();
    if (tokens[pos].ty != ')') {
      error("開きカッコに対応する閉じカッコがありません: %s",
            tokens[pos].input);
    }
    pos++;
    return node;
  }
  error("数値でも開きカッコでもないトークンです: %s", tokens[pos].input);
}

Node *mul() {
  Node *lhs = term();
  if (tokens[pos].ty == TK_EOF) {
    return lhs;
  }
 if (tokens[pos].ty == '*') {
    pos++;
    return new_node('*', lhs, mul());
  }
  if (tokens[pos].ty == '/') {
    pos++;
    return new_node('/', lhs, mul());
  }
  if (lhs->ty == ND_NUM) {
    return lhs;
  }
  error("mul:想定しないトークンです: %s", tokens[pos].input);
}

Node *expr() {
  Node *lhs = mul();
  if (tokens[pos].ty == TK_EOF) {
    return lhs;
  }
  if (tokens[pos].ty == '+') {
    debug("accept: +\n");
    pos++;
    return new_node('+', lhs, expr());
  }
  if (tokens[pos].ty == '-') {
    debug("accept: -\n");
    pos++;
    return new_node('-', lhs, expr());
  }
/*
  if (tokens[pos].ty == '*') {
    debug("accept: *\n");
    pos++;
    return new_node('*', lhs, expr());
  }
  if (tokens[pos].ty == '/') {
    debug("accept: /\n");
    pos++;
    return new_node('/', lhs, expr());
  }
*/
  error("expr:想定しないトークンです: %s", tokens[pos].input);
}

void gen(Node *node) {
  if (node->ty == ND_NUM) {
    printf("  push %d\n", node->val);
    return;
  }

  if (node->lhs != NULL) {
    gen(node->lhs);
  }
  if (node->rhs != NULL) {
    gen(node->rhs);
  }

  printf("  pop rdi\n");
  printf("  pop rax\n");

  switch (node->ty) {
  case '+':
    printf("  add rax, rdi\n");
    break;
  case '-':
    printf("  sub rax, rdi\n");
    break;
  case '*':
    // printf("  mul rax, rdi\n");
    printf("  mul rdi\n");
    break;
  case '/':
    printf("  mov rdx, 0\n");
    printf("  div rdi\n");
  }

  printf("  push rax\n");
}
