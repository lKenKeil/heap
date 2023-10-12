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

// ���ο� ��� ����
TreeNode* createNode(int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// ���� Ž�� Ʈ���� ��� �߰�
TreeNode* insert(TreeNode* node, int data) {
    if (node == NULL) {
        return createNode(data);
    }

    if (data > node->data) {
        printf("�̵�: %d -> %d\n", data, node->data);
        moves++;
        node->data = data;
    }
    else if (data < node->data) {
        node->left = insert(node->left, data);
    }

    return node;
}

// �ִ� ���� ��Ʈ ��� ����
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
        printf("�̵�: %d -> %d\n", temp, node->data);
        moves++;
        node->left = deleteRoot(node->left);
    }
    else if (node->right != NULL) {
        int temp = node->data;
        node->data = node->right->data;
        node->right->data = temp;
        printf("�̵�: %d -> %d\n", temp, node->data);
        moves++;
        node->right = deleteRoot(node->right);
    }

    return node;
}

// ���� ������ ���� Ʈ�� ���
void printLevelOrder(TreeNode* root) {
    if (root == NULL) {
        return;
    }

    // ť�� ����Ͽ� ���� ������ ��� ���
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
        printf("��� �߰� �� ��� �̵� Ƚ��: %d\n", moves);
        moves = 0;
    }

    while (1) {
        printf("�޴��� �����ϼ��� (i: �߰�, d: ����, P: ���, q: ����): ");
        char choice;
        scanf(" %c", &choice);

        if (choice == 'q') {
            break;
        }

        if (choice == 'i') {
            int item;
            printf("�߰��� ���� �Է��ϼ���: ");
            scanf("%d", &item);
            root = insert(root, item);
            printf("�߰� �� ��� �̵� Ƚ��: %d\n", moves);
            moves = 0;
        }
        else if (choice == 'd') {
            root = deleteRoot(root);
            if (root == NULL) {
                printf("Ʈ���� ��� �ֽ��ϴ�.\n");
            }
            else {
                printf("��Ʈ ��� ���� �� ��� �̵� Ƚ��: %d\n", moves);
                moves = 0;
            }
        }
        else if (choice == 'P') {
            printf("Ʈ�� ��� (���� ��): ");
            printLevelOrder(root);
        }
        else {
            printf("��ȿ���� ���� �޴��Դϴ�. �ٽ� �õ��ϼ���.\n");
        }
    }

    return 0;
}
