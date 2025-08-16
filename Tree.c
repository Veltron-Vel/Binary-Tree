#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *right;
    struct Node *left;
} Node;

Node *createNode(int data)
{
    Node *newNode = malloc(sizeof(Node));
    if(newNode==NULL)
    {
        printf("allocation falied\n");
        return NULL;
    } 
    newNode->data = data;
    newNode->right = NULL;
    newNode->left = NULL;

    return newNode;
}

void insertNode(Node **root,int value)
{
    Node *newNode = createNode(value);

    if(*root==NULL)
    {
        *root=newNode;
        return;
    }

    Node *temp;
    Node *queue[100];
    int front= -1; int rear = -1;

    queue[++rear] = *root;

    while(front!=rear)
    {
        temp = queue[++front];

        if(temp->left==NULL)
        {
            temp->left=newNode;
            return;
        }else 
        {
            queue[++rear] = temp->left;
        }
        if(temp->right==NULL)
        {
            temp->right=newNode;
            return;
        }else 
        {
            queue[++rear] = temp->right;
        }

    }
}

Node *bstInsertion(Node *root,int value){
    
    if(root==NULL)
    {
        return createNode(value);
    }

    if(root->data > value)
    {
        root->left = bstInsertion(root->left,value);
    } else if(root->data < value)
    {
        root->right = bstInsertion(root->right,value);
    }
    return root;
}


Node *getDeppestRightNode(Node **root)
{
    Node *queue[100];
    Node *temp; 
    int front = -1; int rear = -1;
    queue[++rear] = *root;

    while(front!=rear)
    {
        temp = queue[++front];

        if(temp->left!=NULL)
        {
            queue[++rear] = temp->left;
        }
        if(temp->right!=NULL)
        {
            queue[++rear] = temp->right;
        }
    }

     return temp;
}

void deleteNode(Node **root, int value)
{
    if (*root == NULL)
    {
        printf("The tree is empty\n");
        return;
    }

    Node *queue[100];
    Node *temp;
    Node *toDelete = NULL;
    int front = -1, rear = -1;

    // BFS to find node to delete
    queue[++rear] = *root;
    while (front != rear)
    {
        temp = queue[++front];
        if (temp->data == value)
        {
            toDelete = temp;
        }
        if (temp->left != NULL) queue[++rear] = temp->left;
        if (temp->right != NULL) queue[++rear] = temp->right;
    }

    if (toDelete != NULL)
    {
        Node *deepestNode = getDeppestRightNode(root);
        toDelete->data = deepestNode->data;

        // BFS again to delete deepestNode
        front = rear = -1;
        queue[++rear] = *root;

        while (front != rear)
        {
            temp = queue[++front];

            if (temp->left != NULL)
            {
                if (temp->left == deepestNode)
                {
                    temp->left = NULL;
                    free(deepestNode);
                    return;
                }
                queue[++rear] = temp->left;
            }

            if (temp->right != NULL)
            {
                if (temp->right == deepestNode)
                {
                    temp->right = NULL;
                    free(deepestNode);
                    return;
                }
                queue[++rear] = temp->right;
            }
        }
    }
    else
    {
        printf("Value was not found in the tree\n");
        return;
    }
}


Node *search(Node *root,int value)
{
    if(root==NULL)
    {
        printf("Tree is empty\n");
        return NULL;
    }

    Node *queue[100];
    Node *temp;
    int front=-1; int rear=-1;

    queue[++rear] = root;

    while(front!=rear)
    {
        temp = queue[++front];

        if(temp->data==value)
        {
            printf("Data found in the tree\n");
            return temp;
        }
        if(temp->left!=NULL)
        {
            queue[++rear]=temp->left;
        }
        if(temp->right!=NULL)
        {
            queue[++rear]=temp->right;
        }
    }

    printf("Data not found in the tree\n");
    return NULL;
    
}

void preOrder(Node *root)
{
    if(root==NULL){return;}

    printf("%d\n",root->data);
    preOrder(root->left);
    preOrder(root->right);
}

void postOrder(Node *root)
{
    if(root==NULL){return;}

    postOrder(root->left);
    postOrder(root->right);
    printf("%d\n",root->data);
}

void inOrder(Node *root)
{
    if(root==NULL){return;}

    inOrder(root->left);
    printf("%d\n",root->data);
    inOrder(root->right);
}


int  main()
{

    Node *root = NULL;

    insertNode(&root, 10);
    insertNode(&root, 20);
    insertNode(&root, 30);
    insertNode(&root, 40);
    insertNode(&root, 50);

    printf("Preorder Traversal:\n");
    preOrder(root);

    printf("\nInorder Traversal:\n");
    inOrder(root);

    printf("\nPostorder Traversal:\n");
    postOrder(root);

    Node *found = search(root, 30);
    if (found!=NULL)
        printf("Found node with data: %d\n", found->data);
    else
        printf("Node not found.\n");

    Node *deepest= getDeppestRightNode(&root);
    if (deepest!= NULL)
        printf("Deepest rightmost node: %d\n", deepest->data);
    return 0;


}

