#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

TreeNode* root = NULL;
int moves = 0;

// 새로운 노드 생성
TreeNode* createNode(int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// 이진 탐색 트리에 노드 추가
TreeNode* insert(TreeNode* node, int data) {
    if (node == NULL) {
        return createNode(data);
    }

    if (data > node->data) {
        printf("이동: %d -> %d\n", data, node->data);
        moves++;
        node->data = data;
    }
    else if (data < node->data) {
        node->left = insert(node->left, data);
    }

    return node;
}

// 최대 힙의 루트 노드 삭제
TreeNode* deleteRoot(TreeNode* node) {
    if (node == NULL) {
        return node;
    }

    if (node->left == NULL && node->right == NULL) {
        free(node);
        return NULL;
    }

    if (node->left != NULL) {
        int temp = node->data;
        node->data = node->left->data;
        node->left->data = temp;
        printf("이동: %d -> %d\n", temp, node->data);
        moves++;
        node->left = deleteRoot(node->left);
    }
    else if (node->right != NULL) {
        int temp = node->data;
        node->data = node->right->data;
        node->right->data = temp;
        printf("이동: %d -> %d\n", temp, node->data);
        moves++;
        node->right = deleteRoot(node->right);
    }

    return node;
}

// 레벨 순으로 이진 트리 출력
void printLevelOrder(TreeNode* root) {
    if (root == NULL) {
        return;
    }

    // 큐를 사용하여 레벨 순으로 노드 출력
    TreeNode* queue[1000];
    int front = 0, rear = 0;
    queue[rear++] = root;

    while (front < rear) {
        TreeNode* tempNode = queue[front++];
        printf("%d ", tempNode->data);

        if (tempNode->left) {
            queue[rear++] = tempNode->left;
        }
        if (tempNode->right) {
            queue[rear++] = tempNode->right;
        }
    }

    printf("\n");
}

int main() {
    int values[] = { 90, 89, 70, 36, 75, 63, 65, 21, 18, 15 };
    int numValues = sizeof(values) / sizeof(values[0]);

    for (int i = 0; i < numValues; i++) {
        root = insert(root, values[i]);
        printf("노드 추가 후 노드 이동 횟수: %d\n", moves);
        moves = 0;
    }

    while (1) {
        printf("메뉴를 선택하세요 (i: 추가, d: 삭제, P: 출력, q: 종료): ");
        char choice;
        scanf(" %c", &choice);

        if (choice == 'q') {
            break;
        }

        if (choice == 'i') {
            int item;
            printf("추가할 값을 입력하세요: ");
            scanf("%d", &item);
            root = insert(root, item);
            printf("추가 후 노드 이동 횟수: %d\n", moves);
            moves = 0;
        }
        else if (choice == 'd') {
            root = deleteRoot(root);
            if (root == NULL) {
                printf("트리가 비어 있습니다.\n");
            }
            else {
                printf("루트 노드 삭제 후 노드 이동 횟수: %d\n", moves);
                moves = 0;
            }
        }
        else if (choice == 'P') {
            printf("트리 출력 (레벨 순): ");
            printLevelOrder(root);
        }
        else {
            printf("유효하지 않은 메뉴입니다. 다시 시도하세요.\n");
        }
    }

    return 0;
}
