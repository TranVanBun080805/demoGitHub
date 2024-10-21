#include <stdio.h>
#include <stdlib.h>

struct Node {
  int key;
  char data;
  struct Node *left;
  struct Node *right;
};



/// @brief Khoi tao mot cay nhi phan rong
/// @return Con tro tro den goc cua cay nhi phan
struct Node *init(const int key, const char value) {
  struct Node *root = (struct Node *)malloc(sizeof(struct Node));
  root->key = key;
  root->data = value;
  root->left = root->right = NULL;
  return root;
}

/// @brief Tao node cho cay
/// @param parent Node me cua node can tao
/// @param value Gia tri cua node
/// @param c Nhan hai gia tri, 'r' : ben phai node me, 'l': ben trai node me
/// @return Con tro tro den node vua tao
struct Node *create_node(struct Node *parent, const int key,
                         const char value, const char c) {
  struct Node *node = (struct Node *)malloc(sizeof(struct Node));
  node->key = key;
  node->data = value;
  node->left = node->right = NULL;

  if (c == 'r')
    parent->right = node;
  if (c == 'l')
    parent->left = node;
  
  return node;
}

/// @brief Duyet truoc de in cac gia tri cua cay ra man hinh
/// @param root Con tro tro den goc cua cay
void preorder_print(struct Node *root) {
  if (root == NULL)
    return;

  // 1. xu ly root truoc
  printf("(%d, %c), ", root->key, root->data);
  // 2. duyet cay con trai
  preorder_print(root->left);
  // 3. duyet cay con phai
  preorder_print(root->right);
}

/// @brief Duyet giua de in cac gia tri cua cay ra man hinh
/// @param root Con tro tro den goc cua cay
void inorder_print(struct Node *root) {
  if (root == NULL)
    return;

  // 1. duyet cay con trai
  inorder_print(root->left);
  // 2. xu ly root
  printf("(%d, %c), ", root->key, root->data);
  // 3. duyet cay con phai
  inorder_print(root->right);
}

/// @brief Duyet sau de in cac gia tri cua cay ra man hinh
/// @param root Con tro tro den goc cua cay
void postorder_print(struct Node *root) {
  if (root == NULL)
    return;
  // 1. duyet cay con trai
  postorder_print(root->left);
  // 2. duyet cay con phai
  postorder_print(root->right);
  // 3. xu ly root
  printf("(%d, %c), ", root->key, root->data);
}

/// @brief Tim kiem trong BST
/// @param root Goc cua cay BST
/// @param key Khoa cua node can tim kiem
/// @return Dia chi cua node can tim (hoac node gan voi node can tim)
struct Node *search(struct Node *root, const int key) {
  // truong hop co so
  if (key == root->key)
    return root;
  if (root->left == NULL && key < root->key)
    return root;
  if (root->right == NULL && key > root->key)
    return root;

  // truong hop tong quat
  if (key < root->key) {
    return search(root->left, key);
  }
  if (key > root->key) {
    return search(root->right, key);
  }
}

struct Node *insert(struct Node *root, const int key, const int c) {
  // tim kiem den node co key gan voi key dau vao nhat
  struct Node *p;
  p = search(root, key);

  // kiem tra neu key da ton tai trong BST
  if (p->key == key)
    return NULL;

  // them node moi
  struct Node *ptr;
  if (key < p->key)
    return create_node(p, key, c, 'l');
  else if (key > p->key)
    return create_node(p, key, c, 'r');
}

/// @brief Xoa node trong cay BST
/// @param root Goc cua cay BST
/// @param key Khoa cua node can xoa
/// @return 0 neu that bai, 1 neu thanh cong
int delete(struct Node *root, const int key) {
  struct Node *parent, *p;
  p = root;
  parent = NULL;
  while (p != NULL) {
    if (p->key == key)
      break;
    parent = p;
    if (p->key < key) {
      p = p->right;
    } else if (p->key > key) {
      p = p->left;
    }
  }

  if (p == NULL) // key khong co trong cay BST
    return 0;

  // 1. Xoa node la
  if (p->left == NULL && p->right == NULL) {
    if (parent->left == p)
      parent->left = NULL;
    if (parent->right == p)
      parent->right = NULL;
    free(p);
    return 1;
  }

  // 2. Xoa node co 1 con
  if (p->right != NULL && p->left == NULL) {
    // p co node con ben phai
    if (parent->right == p)
      parent->right = p->right;
    if (parent->left == p)
      parent->left = p->right;
    free(p);
    return 1;
  }
  if (p->left != NULL && p->right == NULL) {
    // p co node con ben trai
    if (parent->right == p)
      parent->right = p->left;
    if (parent->left == p)
      parent->left = p->left;
    free(p);
    return 1;
  }

  // 3. Xoa node co 2 con 
  // tim lien truoc cua p
  struct Node *pred = get_pred(root, p);
  // sao luu du lieu cua lien truoc
  int pred_key = pred->key;
  char pred_data = pred->data;
  // xoa lien truoc
  delete(root, pred->key);
  // thay p bang lien truoc
  p->key = pred_key;
  p->data = pred_data;
  return 1;
}

/// @brief Tim lien truoc cua mot node trong cay BST
/// @param root Goc cua cay BST
/// @param node Con tro tro toi node can tim lien truoc
/// @return Node lien truoc
struct Node *get_pred(struct Node *root, struct Node *node) {
  struct Node *p = root;
  struct Node *parent;
  if (p == NULL)
    return NULL;

  while (p != NULL) {
    if (p->key > node->key)
      p = p->left;
    if (p->key < node->key) {
      parent = p;
      p = p->right;
    }
    if (p->key == node->key)
      break;
  }

  if (p->left == NULL)
    return parent;
  p = p->left;
  while (p->right != NULL)
    p = p->right;
  return p;
}

void delete_tree(struct Node *root) {
  if (root == NULL)
    return;
  // duyet sau de xoa cay
  delete_tree(root->left);
  delete_tree(root->right);
  free(root);
}
int key_min_max(struct Node *root, int min, int max)
{
    if(root==NULL)
    {
        return 0;
    }
    if(root->key>min && root->key<max)
    {
        printf("(%d,%c) ",root->key,root->data);
    }
    key_min_max(root->left, min, max);
    key_min_max(root->right, min, max);
}
struct Node *get_post(struct Node *root,struct Node *node)
{
    struct Node *p = root;
    struct Node *parent;
    if (p == NULL){
    return NULL;
    }
    while (p != NULL) 
    {
    if (p->key > node->key)
    {
        parent = p;
        p = p->left;
    }
    if (p->key < node->key) 
    {
        p = p->right;
    }
    if (p->key == node->key)
      break;
    }
    if (p == NULL || p->right == NULL) {
        return parent;
    }
    p = p->right;
    while (p->left != NULL) {
        p = p->left;
    }
    return p;
}
int main() {
  // tao cay theo hinh ve tren bang

  // goc cay
  struct Node *root;
  struct Node *p;

  root = init(100, 'U');
  p = create_node(root, 50,'Z', 'l');
  create_node(p,30,'M','l');
  create_node(p,75,'N','r');
  p=p->left;
  create_node(p,20,'V','l');
  p=root->left->right;
  create_node(p,60,'T','l');
  create_node(p,90,'U','r');
  p=create_node(root,200,'X','r');
  create_node(p,150,'O','l');
  p=create_node(p,250,'P','r');
  create_node(p,300,'R','r');
  p=create_node(p,220,'Q','l');
  create_node(p,230,'H','r');
  key_min_max(root,52,95);
p = get_post(root, ptr);
 printf("(%d, %c)\n", p->key, p->data);


// p tro den B
//   create_node(p, 120, 'E', 'r');
//   p = create_node(p, 90, 'D', 'l');  // p tro den D
//   create_node(p, 80, 'K', 'l');
//   create_node(p, 95, 'N', 'r');

//   p = create_node(root, 150, 'C', 'r'); // p tro den C
//   create_node(p, 145, 'F', 'l');
//   create_node(p, 160, 'G', 'r');

//   p = p->left; // F
//   create_node(p, 142, 'H', 'l');
//   create_node(p, 148, 'I', 'r');

//   p = root->right->right; // G
//   p = create_node(p, 170, 'L','r'); // p tro den L
//   p = create_node(p, 180, 'M','r');

//   p = insert(root, 165, 'Z');

//   inorder_print(root);
//   printf("\n");

//   delete(root, 100);

//   preorder_print(root);
//   printf("\n");

//   inorder_print(root);
//   printf("\n");

//   postorder_print(root);
//   printf("\n");

// //  struct Node *ptr;
// //  ptr = search(root, 160);
// //  printf("(%d, %c)\n", ptr->key, ptr->data);
// //
// //  p = get_pred(root, ptr);
// //  printf("(%d, %c)\n", p->key, p->data);


//   delete_tree(root);
//   return 0;
}