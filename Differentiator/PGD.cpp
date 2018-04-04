//
// Created by alena on 04.04.18.
//

Node* grammar :: GetG()
{
    p = 0;
    if (str[p] == '\0')
    {
        printf("Error string\n");
        return 0;
    }

    Node* val = GetE();

    if (str[p] != '\0')
    {
        printf("Error string of expression\n");
        return NULL;
    }
    return val;
}


Node* grammar :: GetE()
{
    Node* root = GetT();
    while (str[p] == '+' || str[p] == '-')
    {
        char oper = str[p];
        p++;
        Node* val2 = GetT();
        if (oper == '+')
        {
            Node* val = root;
            root = new Node(FUNC, PLUS);
            root->left = val;
            root->right = val2;
        }
        if (oper == '-')
        {
            Node* val = root;
            root = new Node(FUNC, MINUS);
            root->left = val;
            root->right = val2;
        }
    }
    return root;
}


Node* grammar :: GetT()
{
    Node* root = GetP();
    while (str[p] == '*' || str[p] == '/')
    {
        char oper = str[p];
        p++;
        Node* val1 = GetP();
        if (oper == '*')
        {
            Node* val = root;
            root = new Node(FUNC, PROD);
            root->left = val;
            root->right = val1;
        }
        if (oper == '/')
        {
            Node* val = root;
            root = new Node(FUNC, PART);
            root->left = val;
            root->right = val1;
        }
    }
    return root;
}


Node* grammar :: GetP()
{
    if (str[p] == '(')
    {
        p++;
        Node* val = GetE();
        if (str[p] == ')')
        {
            p++;
            return val;
        }
        else
        {
            printf("No )\n");
            return NULL;
        }
    }
    else
    {
        return GetN();
    }
}


Node* grammar :: GetN()
{
    int count = 0;
    int val = 0;
    int helpp = 0;
    Node* root = NULL;

    /*if (str[p] < '0' || str[p] > '9' || str[helpp] != 'x' || str[helpp] != 'y')
    {
        printf("ERROR EXPRESSION, only numbers and x, y\n");
        return NULL;
    }*/

    do
    {
        helpp = p;
        val = val * 10 + str[p] - '0';
        p++;
        count++;
    } while ('0' <= str[p] && str[p] <= '9');

    if ('0' <= str[helpp] && str[helpp] <= '9')
    {
        root = new Node(NUM, val);
    }
    if (str[helpp] == 'x')
    {
        root = new Node(VARS , X_FLAG);
    }
    if (str[helpp] == 'y')
    {
        root = new Node(VARS , Y_FLAG);
    }

    return root;
}





















