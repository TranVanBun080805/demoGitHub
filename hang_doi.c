#include <stdio.h>
#include <stdlib.h>

struct Node {
  char data;
  struct Node *next; // con tro tro den node tiep theo
};

struct Queue {
  struct Node *front;
  struct Node *rear;
};

/// @brief Khoi tao hang doi rong
/// @return Cau truc Queue dai dien cho mot hang doi
struct Queue init() {
  struct Queue ret;
  ret.front = NULL;
  ret.rear = NULL;
  return ret;
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
  if (start == NULL)
    return;
    
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


/// @brief Them phan tu vao stack
/// @param front Vi tri dinh stack
/// @param c Gia tri can them
/// @return 0 neu that bai, 1 neu thanh cong
int push(struct Node **front, const char c) {
  return insert(front, c, 0);
}

/// @brief Xoa phan tu khoi stack
/// @param front Vi tri dinh stack
/// @param c Gia tri cua phan tu bi xoa
/// @return 0 neu that bai, 1 neu thanh cong
int pop(struct Node **front, char *c) {
  if (*front == NULL)
    return 0; // that bai
  *c = (*front)->data;
  return delete(front, 0);
}

/// @brief Cho biet kich thuoc cua hang doi
/// @param queue Hang doi
/// @return Kich thuoc cua hang doi
int size(struct Queue queue) {
  struct Node *front = queue.front;
  struct Node *p = front;
  int result = 0;

  if (front == NULL)
    return 0;

  do {
    result++;
    p = p->next;
  } while (p != front);
  return result;
}

/// @brief Xem gia tri phan tu dau hang doi
/// @param queue Hang doi
/// @param c Bien luu gia tri cua phan tu can xem
/// @return 0 neu that bai, 1 neu thanh cong
int front(struct Queue queue, char *c) {
  if (queue.front == NULL)
    return 0; // that bai
  *c = queue.front->data;
  return 1;
}

/// @brief Xem gia tri phan tu cuoi hang doi
/// @param queue Hang doi
/// @param c Bien luu gia tri cua phan tu can xem
/// @return 0 neu that bai, 1 neu thanh cong
int rear(struct Queue queue, char *c) {
  if (queue.rear == NULL)
    return 0; // that bai
  *c = queue.rear->data;
  return 1;
}

/// @brief Them phan tu vao hang doi
/// @param queue Cau truc hang doi
/// @param value Gia tri can them
/// @return 0 neu that bai, 1 neu thanh cong
int enqueue(struct Queue *queue, const char value) {
  struct Node *p = (struct Node *)malloc(sizeof(struct Node));
  p->data = value;
  p->next = queue->front;

  // hang doi rong
  if (queue->rear == NULL) {
    p->next = p;
    queue->front = queue->rear = p;
  } else { // hang doi khong rong
    queue->rear->next = p;
    queue->rear = p;
  }
  return 1;
}

/// @brief Xoa phan tu ra khoi hang doi
/// @param queue Cau truc hang doi
/// @param c Bien luu gia tri cua phan tu vua xoa
/// @return 0 neu that bai, 1 neu thanh cong
int dequeue(struct Queue *queue, char *c) {
    struct Node *p;
    if(queue->front==NULL)
    {
        return 0;
    }
    p=queue->front;
    queue->front=p->next;
    *c=p->data;
    queue->rear->next=queue->front;
    free(p);
    return 1;
}

int main() {
  struct Queue queue = init();
    char *c=(char *)malloc(sizeof(char));
    
  enqueue(&queue, 'h');
  enqueue(&queue, 'e');
  enqueue(&queue, 'l');
  enqueue(&queue, 'l');
  enqueue(&queue, 'o');

  print_list(queue.front);
  dequeue(&queue, c);
  print_list(queue.front);
  delete_list(queue.front);
}