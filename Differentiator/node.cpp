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


void Node :: print_in_tex(FILE* f)
{
    if (f)
    {
        fprintf(f,"\n");
        fprintf(f, "%s", " \\[ ");
        print_node_in_tex(f);
        fprintf(f, "%s\n", " \\] \\\\");
    }
    else
    {
        printf("file is not found\n");
    }
}


void Node :: print_node_in_tex(FILE* f)
{
    if (left)
        left->print_node_in_tex(f);
    switch(flag)
    {
        case FUNC:
            func_tex(f);
            break;
        case VARS:
            vars_tex(f);
            break;
        case NUM:
            num_tex(f);
            break;
        default:
            printf("Wrong flag\n");
    }
    if (right)
        right->print_node_in_tex(f);
}


void Node :: func_tex(FILE* f)
{
    switch(value)
    {
        case PLUS:
            fprintf(f," + ");
            break;
        case MINUS:
            fprintf(f, " - ");
            break;
        case PROD:
            fprintf(f, " \\cdot ");
            break;
        default:
            printf("Wrong func\n");
    }
}


void Node :: vars_tex(FILE* f)
{
    switch(value)
    {
        case X_FLAG:
            fprintf(f, " x ");
            break;
        case Y_FLAG:
            fprintf(f, " y ");
            break;
        default:
            printf("Wrong var\n");
    }
}


void Node :: num_tex(FILE* f)
{
    fprintf(f, "%d", value);
}


void Node :: dot(FILE* f)
{
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
    const char* label;
    if (flag == NUM)
    {
        fprintf(f,"e_%x[label=\"%d\"];\n", this, value);
    }
    else
    {
        label = inDot();
        fprintf(f,"e_%x[label=\"%s\"];\n", this, label);
    }

    if (left)
    {
        fprintf(f, "e_%x -> e_%x;\n", this, left);
        left->print_in_dot(f);
    }
    if (right)
    {
        fprintf(f, "e_%x -> e_%x;\n", this, right);
        right->print_in_dot(f);
    }
}


const char* Node :: inDot()
{
    const char* label;
    switch(flag)
    {
        case FUNC:
        {
            switch(value)
            {
                case PLUS:
                {
                    label = "+";
                    break;
                }
                case MINUS:
                {
                    label = "-";
                    break;
                }
                case PROD:
                {
                    label = "*";
                    break;
                }
                default: {
                    printf("unknown func\n");
                    break;
                }
            }
            break;
        }
        case VARS:
        {
            switch(value)
            {
                case X_FLAG:
                {
                    label = "x";
                    break;
                }
                case Y_FLAG:
                {
                    label = "y";
                    break;
                }
            }
            break;
        }
        default:
        {
            printf("Error flag%d\n", flag);
            break;
        }
    }
    return label;
}


Node::~Node()
{
    if (left)
    {
        delete left;
        left = NULL;
    }
    if (right)
    {
        delete right;
        right = NULL;
    }
}

