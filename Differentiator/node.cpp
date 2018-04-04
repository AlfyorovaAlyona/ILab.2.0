//
// Created by alena on 06.03.18.
//

Node :: Node(int fl, int val)
{
    flag = fl;
    value = val;
    left = NULL;
    right = NULL;
}


Node* Node :: add_left(int fl, int val)
{
    left = new Node(fl, val);
}


Node* Node :: add_right(int fl, int val)
{
    right = new Node(fl, val);
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
                case PART:
                {
                    label = "/";
                    break;
                }
                case SIN:
                {
                    label = "sin";
                    break;
                }
                case COS:
                {
                    label = "cos";
                    break;
                }
                case LN:
                {
                    label = "ln";
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
            printf("Error flag %d\n", flag);
            break;
        }
    }
    return label;
}


void Node :: opt_const()
{
    _OPTIMIZATION_ = false;
    if (left)
    {
        left->opt_const();
    }
    if (right)
    {
        right->opt_const();
    }

    if (flag == FUNC && left && right && left->flag == NUM && right->flag == NUM)
    {
        switch(value)
        {
            case PLUS:
            {
                flag = NUM;
                value = left->value + right->value;
                delete left;
                delete right;
                left = NULL;
                right = NULL;
                _OPTIMIZATION_ = true;
                break;
            }
            case MINUS:
            {
                flag = NUM;
                value = left->value - right->value;
                delete left;
                delete right;
                left = NULL;
                right = NULL;
                _OPTIMIZATION_ = true;
                break;
            }
            case PROD:
            {
                flag = NUM;
                value = left->value * right->value;
                delete left;
                delete right;
                left = NULL;
                right = NULL;
                _OPTIMIZATION_ = true;
                break;
            }
            case PART:
            {
                if (left->value % right->value == 0)
                {
                    flag = NUM;
                    value = left->value/right->value;
                    delete left;
                    delete right;
                    left = NULL;
                    right = NULL;
                    _OPTIMIZATION_ = true;
                }
                break;
            }
            default:
            {
                printf("Error func %d in opt const\n", value);
                break;
            }
        }
    }
    if (flag == FUNC && value == LN)
    {
        if (right->value == 1)
        {
            flag = NUM;
            value = 0;
            delete left;
            delete right;
            left = NULL;
            right = NULL;
            _OPTIMIZATION_ = true;
        }
    }
    if (right && flag == FUNC && value == COS)
    {
        if (right->value == 0)
        {
            flag = NUM;
            value = 1;
            delete right;
            right = NULL;
            left = NULL;
            _OPTIMIZATION_ = true;
        }
    }
    if (flag == FUNC && value == SIN)
    {
        if (right->value == 0)
        {
            flag = NUM;
            value = 1;
            delete right;
            right = NULL;
            left = NULL;
            _OPTIMIZATION_ = true;
        }
    }
}


void Node :: opt_simple()
{
    if (left)
    {
        left->opt_simple();
    }
    if (right)
    {
        right->opt_simple();
    }

    if (left && right && flag == FUNC && value == PROD && left->flag == NUM && left->value == 1) //1*A +
    {
        flag = right->flag;
        value = right->value;
        Node* tmp = right;
        delete left;
        left = NULL;
        left = right->left;
        right = right->right;
        tmp->left = NULL;
        tmp->right = NULL;
        delete tmp;
        _OPTIMIZATION_ = true;
    }
    if (left && right && flag == FUNC && value == PROD && left->flag == NUM && left->value == 0) //0*A
    {
        flag = NUM;
        value = 0;
        delete left;
        left = NULL;
        delete right;
        right = NULL;
        _OPTIMIZATION_ = true;
    }
    if (left && right && flag == FUNC && value == PROD && right->flag == NUM && right->value == 0) //A*0
    {
        flag = NUM;
        value = 0;
        delete left;
        left = NULL;
        delete right;
        right = NULL;
        _OPTIMIZATION_ = true;
    }
    if (left && right && flag == FUNC && value == PROD && right->flag == NUM && right->value == 1) //A*1 ?
    {
        flag = left->flag;
        value = left->value;
        Node* tmp = left;
        delete right;
        right = NULL;
        right = left->right;
        left = left->left;
        tmp->left = NULL;
        tmp->right = NULL;
        delete tmp;
        _OPTIMIZATION_ = true;
    }
    if (left && right && flag == FUNC && value == PLUS && right->flag == NUM && right->value == 0) //A+0 +
    {
        flag = left->flag;
        value = left->value;
        Node* tmp = left;
        delete right;
        right = NULL;
        right = left->right;
        left = left->left;
        tmp->left = NULL;
        tmp->right = NULL;
        delete tmp;
        _OPTIMIZATION_ = true;
    }
    if (left && right && flag == FUNC && value == PLUS && left->flag == NUM && left->value == 0) //0+A +
    {
        flag = right->flag;
        value = right->value;
        Node* tmp = right;
        delete left;
        left = NULL;
        left = right->left;
        right = right->right;
        tmp->right = NULL;
        tmp->left = NULL;
        delete tmp;
        _OPTIMIZATION_ = true;
    }
    if (left && right && flag == FUNC && value == MINUS && right->flag == NUM && right->value == 0) //A-0 +
    {
        flag = left->flag;
        value = left->value;
        Node* tmp = left;
        delete right;
        right = NULL;
        right = left->right;
        left = left->left;
        tmp->right = NULL;
        tmp->left = NULL;
        delete tmp;
        _OPTIMIZATION_ = true;
    }
    if (left && right && flag == FUNC && value == MINUS && left->flag == NUM && left->value == 0) //0-A +
    {
        value = PROD;
        left->value = -1;
        _OPTIMIZATION_ = true;
    }
    if (left && right && flag == FUNC && value == PART && left->flag == NUM && left->value == 0) //0/A
    {
        flag = NUM;
        value = 0;
        delete left;
        left = NULL;
        delete right;
        right = NULL;
        _OPTIMIZATION_ = true;
    }
}


Node :: ~Node()
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

