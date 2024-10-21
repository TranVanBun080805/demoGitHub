#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 20
int hash_size =20;
char* hash_table[N];

int hash_function(const char *c)
{
    int sum=0;
    for(int i=0;c[i]!='\0';i++)
    {
        sum+=c[i]*(i+1);
    }
    return sum%N;
}

/// @brief Them phan tu (ky tu) vao bang bam
/// @param c Ky tu can them
/// @return Vi tri cua ma c duoc them vao. -1 neu that bai
int insert_hash(const char *c) {
    int index=hash_function(c);
    int count=0;
    while(hash_table[index]!=NULL)
    {
        index=(index+1)%hash_size;
        count++;
        if(count==N)
        {
            return 0;
        }
    }
    hash_table[index]=strdup(c);
    return 1;
}

/// @brief Xoa phan tu ra khoi bang bam. 
/// @param Neu bucket la DSLK thi xoa phan tu cuoi cua DSLK.
/// @param c Ky tu can them
/// @return -1 neu khong co phan tu. 0 neu khong the xoa. 1 la thanh cong.
int delete_hash(const int key) {
    if (key < 0 || key >= hash_size || hash_table[key] == NULL) {
        return -1;
    }
    free(hash_table[key]);
    hash_table[key] = NULL;
    return 1;
}
int delete_hash1(const char *c)
{
    int index=hash_function(c);
    if(hash_table[index]!=NULL)
    {
    if(strcmp(hash_table[index], c)==0)
    {
        free(hash_table[index]);
        hash_table[index] = NULL;
    }
    else{
        while (1)
        {
            index++;
            if(strcmp(hash_table[index], c)==0)
            {
                free(hash_table[index]);
                hash_table[index] = NULL;
                return 1;
            }
        }      
    }
    }
}
/// @brief In bang bam.
void print_hash_table() {
    for (int i = 0; i < N; i++) {
        if (hash_table[i] != NULL) 
        {
            printf("Ky tu tai vi tri %d: %s\n", i, hash_table[i]);
        } else 
        {
            printf("Ky tu tai vi tri %d: NULL\n", i);
        }
    }
}

/// @brief Tim kiem xem mot gia tri co trong bang bam hay khong.
/// @param c Gia tri (ky tu) can tim kiem.
/// @return -1: khong co. Neu co tra ve vi tri cua bucket.
int search(const char *c) {
    printf("ket qua tim kiem:\n");
  for(int i=0;i<hash_size;i++)
  {
    printf("aaaaa\n");
    if(hash_table[i]!=NULL && strcmp(hash_table[i], c)==0)
    {
        printf("Ky tu tai vi tri %d: %s\n", i, hash_table[i]);
    }
  }
//   return 1;
}
int main() {
    insert_hash("1");
    insert_hash("hello1");
    insert_hash("hello");
    print_hash_table(hash_table);
    delete_hash1("hello");
    print_hash_table(hash_table);
    return 0;
}