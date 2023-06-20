#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node{
	int key;
	struct node *left;
	struct node *right;
	int height;
};

int count = 0;
int Height(struct node *inNode){
	if(inNode == NULL)
		return 0;
	else{
		return inNode->height;
	}
}

int Max(int a, int b){
	if(a > b){
		return a;
	}
	else{
		return b;
	}
}

int checkBalance(struct node *inNode){
	if(inNode == NULL){
		return 0;
	}
	else{
		return Height(inNode->left) - Height(inNode->right);
	}
}

struct node *rightRotate(struct node *curr){
	struct node *newCurr = curr->right;
	struct node *rightNewCurr = curr->left;
	
	newCurr->right = curr;
	curr->left = rightNewCurr;
	
	curr->height = 1 + Max(Height(curr->left), Height(curr->right));
	newCurr->height = 1 + Max(Height(newCurr->left), Height(newCurr->right));
	
	return newCurr;
}

struct node *leftRotate(struct node *curr){
	struct node *newCurr = curr->left;
	struct node *leftNewCurr = curr->right;
	
	newCurr->left = curr;
	curr->right = leftNewCurr;
	
	curr->height = 1 + Max(Height(curr->left), Height(curr->right));
	newCurr->height = 1 + Max(Height(newCurr->left), Height(newCurr->right));
	
	return newCurr;
}

struct node *insert(struct node *root, int keyInput){
	if(root == NULL){
		struct node *newNode = (struct node*)malloc(sizeof(struct node));
		newNode->key = keyInput;
		newNode->left = NULL;
		newNode->right = NULL;
		newNode->height = 1;
		
		return newNode;
	}
	if(keyInput < root->key ){
		root->left = insert(root->left, keyInput);
	}else if(keyInput < root->key ){
		root->right = insert(root->right, keyInput);
	}else{
		return root;
	}
	
	root->height = 1 + Max(Height(root->left), Height(root->right));
	
	int balanceFactor = checkBalance(root);
	
	if(balanceFactor > 1 && keyInput < root->left->key){
		return rightRotate(root);
	}
	if(balanceFactor > 1 && keyInput > root->left->key){
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}
	if(balanceFactor <-1 && keyInput > root->right->key){
		return leftRotate(root);
	}
	if(balanceFactor <-1 && keyInput < root->right->key){
		root->right - rightRotate(root->right);
		return leftRotate(root);
	}
	return root;
}

struct node *minValue(struct node *root){
	
	struct node *curr = root;
	
	while(curr->left!=NULL){
		curr = curr->left;
	}
	
	return curr;
}

struct node *deleteNode (struct node *root, int inKey){
	
	if(root == NULL){
		return root;
	}
	
	if(inKey < root->key){
		root->left = deleteNode(root->left, inKey);
	}else if(inKey > root->key){
		root->right = deleteNode(root->right, inKey);
	}else{
		count++;
		if(count == 1){
			printf("Data found\n");
			printf("Value %d was deleted\n", inKey);
		}
		if(root->left == NULL){
			struct node *temp = root->right;
			free(root);
			return temp;
		}else if(root->right == NULL){
			struct node *temp = root->left;
			free(root);
			return temp;
		}else{
			struct node *temp = minValue(root->right);
			root->key = temp->key;
			root->right=deleteNode(root->right, temp->key);
		}	
	}
	root->height = 1 + Max(Height(root->left), Height(root->right));
	
	int balanceFactor = checkBalance(root);
	
	if(balanceFactor > 1 && checkBalance(root->left) >= 0){
		return rightRotate(root);
	}
	
	if(balanceFactor > 1 && checkBalance(root->right) < 0){
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}
	
	if(balanceFactor < -1 && checkBalance(root->right) <= 0){
		return leftRotate(root);
	}
	
	if(balanceFactor <-1 && checkBalance(root->left) > 0){
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}
	return root;
}

void printPreOrder(struct node *root){
	if(root != NULL){
		printf("%d ", root->key);
		printPreOrder(root->left);
		printPreOrder(root->right);
	}
}

void printInOrder(struct node *root){
	if(root != NULL){
		printInOrder(root->left);
		printf("%d ", root->key);
		printInOrder(root->right);
	}
}

void printPostOrder(struct node *root){
	if(root != NULL){
		printPostOrder(root->left);
		printPostOrder(root->right);
		printf("%d ", root->key);
	}
}

int main()
{
	struct node *root = NULL;
	int menu, data, deleteData;
	do{
		printf("1. Insertion\n");
		printf("2. Deletion\n");
		printf("3. Traversal\n");
		printf("4. Exit\n");
		printf("Choose : ");
		scanf("%d", &menu);
		
		switch(menu){
			case 1:
				printf("Insert: ");
				scanf("%d", &data);
				root = insert(root, data);
				system("pause");
				system("cls");
				break;
			case 2:
				printf("Delete : ");
				scanf("%d", &deleteData);
				count = 0;
				root = deleteNode(root, deleteData);
				system("pause");
				system("cls");
				break;
			case 3:
				printf("Preorder: ");
				printPreOrder(root);
				printf("\n");
				printf("Inorder: ");
				printInOrder(root);
				printf("\n");
				printf("Postorder: ");
				printPostOrder(root);
				printf("\n");
				system("pause");
				system("cls");
				break;
		}
	}while(menu != 4);
	printf("Thank you\n");
	
	return 0;
}
