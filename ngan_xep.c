#include <stdio.h>
#include <stdlib.h>

struct Node {
  char data;
  struct Node *next; // con tro tro den node tiep theo
};

/// @brief Khoi tao danh sach lien ket vong don
/// @return Con tro tro den node START cua DSLK
struct Node *init() {
  // khoi tao mot danh sach lien ket rong
  return NULL;
}

/// @brief Them node vao DSLK vong don
/// @param start Con tro cua con tro tro den node START
/// @param value Gia tri cua node can them
/// @param position Vi tri cua node can them tinh tu START
/// @return 0 neu that bai, 1 neu thanh cong
int insert(struct Node **start, const char value, const int position) {
  // TH1: DSLK rong
  if (*start == NULL) {
    if (position != 0)
      return 0; // that bai
    struct Node *p = (struct Node*)malloc(sizeof(struct Node));
    p->data = value;
    p->next = p;
    *start = p;
    return 1; // thanh cong
  }

  // TH2: DSLK khac rong
  // 1. Tim vi tri lien truoc cua node position 
  // Chu y: position=0, lien truoc la node cuoi cung cua DSLK vong
  // - position = 0
  // - position != 0
  struct Node *p = *start; // chua vi tri cua node lien truoc
  int pos = 0;
  if (position != 0) {
    while (pos < position-1) {
      pos++;
      p = p->next;
      if (p == *start)
        return 0; // that bai
    }
  } else { // TH position == 0
    while (p->next != *start)
      p = p->next;
  }
  
  // 2. Thuc hien chen phan tu sau mot node cho truoc p
  struct Node *p1;
  p1 = (struct Node *)malloc(sizeof(struct Node));
  p1->data = value;
  p1->next = p->next;
  p->next = p1;
  if (position == 0) // cap nhat lai start
    *start = p1;
  return 1;
}

/// @brief In danh sach lien ket ra man hinh
/// @param start Con tro tro den node START
void print_list(struct Node *start) {
  struct Node *p = start;
  do {
    printf("%c", p->data);
    p = p->next;
  } while (p != start);
  printf("\n");
}

/// @brief Xoa node khoi DSLK vong don
/// @param start Con tro cua con tro tro den node START
/// @param position Vi tri cua node can xoa tinh tu START
/// @return 0 neu that bai, 1 neu thanh cong
int delete(struct Node **start, const int position) {
  // 1. tim node lien truoc
  struct Node *p = *start; // chua vi tri cua node lien truoc
  int pos = 0;
  if (position != 0) {
    while (pos < position-1) {
      pos++;
      p = p->next;
      if (p == *start)
        return 0; // that bai
    }
  } else { // TH position == 0
    while (p->next != *start)
      p = p->next;
  }

  // 2. xoa node tai position
  struct Node *p1 = p->next;
  p->next = p1->next;
  if (p1 == *start) {
    *start = p1->next;
  }
  free(p1);
  return 1;
}

/// @brief Xoa toan bo danh sach lien ket
/// @param start Con tro tro den node START
/// @return 0 neu that bai, 1 neu thanh cong
int delete_list(struct Node *start) {
  if (start == NULL)
    return 1;
    
  struct Node *p, *p1;
  p = start;
  do {
    p1 = p;
    p = p->next;
    free(p1);
  } while (p != start);

  return 1;
}
int push(struct node **start,char *c)
{
  if(*start==NULL)
  {
    return 0
  }
  *c=(*start)->data;
  return delete(start)
}

int main() {
  struct Node *start;

  // khoi tao
  start = init();

  // thuc hien cac tac vu lien quan den DSLK
  insert(&start, 'o', 0);
  insert(&start, 'l', 0);
  insert(&start, 'l', 0);
  insert(&start, 'e', 0);
  insert(&start, 'h', 0);

  print_list(start);

  insert(&start, '*', 4);
  print_list(start);

  delete(&start, 5);
  print_list(start);

  delete_list(start);
}