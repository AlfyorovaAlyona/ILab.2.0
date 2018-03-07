//
// Created by alena on 06.03.18.
//
Node :: Node(int fl, int val)
{
    flag = fl;
    value = val;
    left = nullptr;
    right = nullptr;
}


Node* Node :: add_left(int fl, int val)
{
    left = new Node(fl, val);
}


Node* Node :: add_right(int fl, int val)
{
    right = new Node(fl, val);
}


void Node :: print()
{
    FILE* f;
    f = fopen("Input.txt", "wt");
    if (f)
    {

        fprintf(f, "%s", " ");
        fprintf(f, "%s", "(");
        fprintf(f, "%s", " ");
        fprintf(f, "%d%d", flag, value);
        left->print();
        right->print();
        fprintf(f, "%s", " ");
        fprintf(f, "%s", ")");
        fclose(f);
    }
    else
    {
        printf("file is not found\n");
    }
}


void Node :: dot()
{
    FILE* f;
    f = fopen("tree-dot.txt", "wt");
    if (f)
    {
        fprintf(f, "%s\n", "digraph G {");
        fprintf(f, "%s\n", "node[color=\"red\",fontsize=14];\n"
                " edge[color=\"darkgreen\",fontcolor=\"blue\",fontsize=12];\n");
        print_in_dot(f);
        fprintf(f, "}");
    }
    else
    {
        printf("Not found\n");
    }
    fclose(f);
}


void Node :: print_in_dot(FILE *f)
{
    fprintf(f, "%d%d\n", flag, value);
    if (left)
    {
        fprintf(f, "%d%d%s%d%d\n", flag, value, "->", left->flag, left->value);
        left->print_in_dot(f);
    }
    if (right)
    {
        fprintf(f, "%d%d%s%d%d\n", flag, value, "->", right->flag, right->value);
        right->print_in_dot(f);
    }
}


void Node :: PRINT()
{
    printf("flag = %d, value = %d", flag, value);
}


Node::~Node()
{
    if (left)
    {
        delete left;
        left = nullptr;
    }
    if (right)
    {
        delete right;
        right = nullptr;
    }
}

