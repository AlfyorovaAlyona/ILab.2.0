#include "aki.h"


const int MAX_SIZE = 10;

int main()
{
	char* Roo = "Is it a human";
    Node* root = create_node_dynamic(Roo);
    add_left(root, "Is it an animal");
    add_right(root, "Is it a teacher");
    add_left(root->left, "Math");
    add_right(root->left, "deer");
    add_right(root->right, "Bek");
    add_left(root->right, "Lesha");
    
   //dotTree(root);
	akinator(root);
	print_node(root);
	
	delete_subtree(root);
    return 0;
}


void akinator(Node* root)
{
	char ans;
	int i = 1;
	while (isQuestion(root))
	{
		printf("%s?(y/n)\n", root->value);
		scanf("%s", &ans);
		if (ans == 'y')
		{
			root = root->right;
		}
		else
		{
			root = root->left;
		}
	}
	printf("%s?\n", root->value);
	scanf("%s", &ans);
	
	if (ans == 'y')
	{
		printf("I was right!\n");
		return;
	}
	else
	{
		printf("Who is it?\n");
		char* buffer = (char*)calloc(MAX_SIZE, sizeof(char));
		char* buffer2 = (char*)calloc(MAX_SIZE, sizeof(char));
		scanf("%s", buffer);
		add_right(root, buffer);
		add_left(root, root->value);
		printf("What is the difference %s from %s\n", buffer, root->value);
		scanf("%s",buffer2);
		root->value = buffer2;
	}
}


int isQuestion(Node* root)
{
	assert(root->left && root->right || !root->left && !root->right);
	return root->left && root->right;
}









