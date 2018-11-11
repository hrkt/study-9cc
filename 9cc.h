#ifndef NINE_CC_H
#define NINE_CC_H

// トークンの型を表す値
enum {
  TK_NUM = 256, // 整数トークン
  TK_EOF = 0,       // 入力の終わりを表すトークン
};

enum {
  ND_NUM = 256,     // 整数のノードの型
};

// トークンの型
typedef struct {
  int ty;      // トークンの型
  int val;     // tyがTK_NUMの場合、その数値
  char *input; // トークン文字列（エラーメッセージ用）
} Token;

typedef struct Node {
  int ty;           // 演算子かND_NUM
  int op;
  struct Node *lhs; // 左辺
  struct Node *rhs; // 右辺
  int val;          // tyがND_NUMの場合のみ使う
} Node;


Node *expr();
void error(char *msg, char *detail);
void debug(char *msg);
Node *new_node_num(int val);
Node *new_node(int op, Node *lhs, Node *rhs);
Node *term();
Node *mul();
void gen(Node *node);
void tokenize(char *p);
void dumpTokens(int i);


// トークナイズした結果のトークン列はこの配列に保存する
// 100個以上のトークンは来ないものとする
extern Token tokens[];

extern int pos;
//int DEBUG = 1;
extern int DEBUG;

#endif
