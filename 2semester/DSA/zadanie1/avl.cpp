#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

#include <chrono>
using namespace std::chrono;

using std::cout;
using std::endl;
using std::string;
using std::cin;

//define class node for binary search tree using AVL algorithm
class Node
{
    public:
        int value;
        int height;
        Node* left;
        Node* right;

        Node(int value) /*constructor*/
        {
            this->value = value;
            this->height = 1;
            this->left = nullptr;
            this->right = nullptr;
        }
};

//define class AVL tree
class AVL
{
    public:
        Node* root;
        AVL() /* constructor */
        {
            root = nullptr;
        }

        //function to check if the tree is empty
        bool isEmpty()
        {
            if (root == nullptr)
                return true;
            else
                return false;
        }

        //function to get the height of the tree
        int height(Node* node)
        {
            if (node == nullptr)
                return 0;
            else
                return node->height;
        }

        //function to get the balance factor of the tree
        int balanceFactor(Node* node)
        {
            if (node == nullptr)
                return 0;
            else
                return height(node->left) - height(node->right);
        }

        //function to update the height of the tree
        int updateHeight(Node* node)
        {
            if (node == nullptr)
                return 0;
            else
                return ((height(node->left) > height(node->right) ? height(node->left) : height(node->right)) + 1);
        }

        //function to rotate the tree to the right
        Node* rotateRight(Node* node)
        {
            Node* left = node->left;
            Node* leftRight = left->right;

            left->right = node;
            node->left = leftRight;

            node->height = updateHeight(node);
            left->height = updateHeight(left);

            return left;
        }

        //function to rotate the tree to the left
        Node* rotateLeft(Node* node)
        {
            Node* right = node->right;
            Node* rightLeft = right->left;

            right->left = node;
            node->right = rightLeft;

            node->height = updateHeight(node);
            right->height = updateHeight(right);

            return right;
        }

        //function to insert new node into the tree
        Node* insert(Node* node, int value)
        {
            if (node == nullptr)
            {
                return new Node(value);
            }

            if (value < node->value)
            {
                node->left = insert(node->left, value);
            }
            else if (value > node->value)
            {
                node->right = insert(node->right, value);
            }
//            else
//            {
                return node;
//            }
        }

/*_______________________________________OK________________________________________________________*/

        //function to delete node from the tree
        Node* deleteNode(Node* node, int value)
        {
            if (node == nullptr)
                return node;

            if (value < node->value)
                node->left = deleteNode(node->left, value);
            else if (value > node->value)
                node->right = deleteNode(node->right, value);
            else
            {
                if (node->left == nullptr || node->right == nullptr)
                {
                    Node* temp = node->left ? node->left : node->right;

                    if (temp == nullptr)
                    {
                        temp = node;
                        node = nullptr;
                    }
                    else
                        *node = *temp;
                    delete temp;
                }
                else
                {
                    Node* temp = minValueNode(node->right);

                    node->value = temp->value;

                    node->right = deleteNode(node->right, temp->value);
                }
            }

            if (node == nullptr)
                return node;

            node->height = updateHeight(node);

            int balance = balanceFactor(node);

            if (balance > 1 && balanceFactor(node->left) >= 0)
                return rotateRight(node);

            if (balance > 1 && balanceFactor(node->left) < 0)
            {
                node->left = rotateLeft(node->left);
                return rotateRight(node);
            }

            if (balance < -1 && balanceFactor(node->right) <= 0)
                return rotateLeft(node);

            if (balance < -1 && balanceFactor(node->right) > 0)
            {
                node->right = rotateRight(node->right);
                return rotateLeft(node);
            }

            return node;
        }

        //function to find the minimum value of the tree
        Node* minValueNode(Node* node)
        {
            Node* current = node;

            while (current->left != nullptr)
                current = current->left;

            return current;
        }

        //function to search for a node in the tree
        Node* search(Node* node, int value)
        {
            if (node == nullptr || node->value == value)
                return node;

            if (node->value < value)
                return search(node->right, value);

            return search(node->left, value);
        }
/*
        //function to print the tree
        void print(Node* node)
        {
            if (node != nullptr)
            {
                print(node->left);
                cout << node->value << " ";
                print(node->right);
            }
        }
*/
        void print(const string& prefix, Node* node, bool isLeft)
        {
            if( node != nullptr )
            {
                cout << prefix;

                cout << (isLeft ? "|--" : "L--" );

                // print the value of the node
                cout << node->value << endl;

                // enter the next tree level - left and right branch
                print( prefix + (isLeft ? "|   " : "    "), node->left, true);
                print( prefix + (isLeft ? "|   " : "    "), node->right, false);
            }
        }

};

int main()
{
    /*random number generator*/
    srand(time(0));

    int I;

    cout<<"Input number of random numbers:"<<endl;
    cin>>I;
    getchar();
    cout<<endl;

    int input_array[I];
    
    for (int x = 0; x<I ;x++) //loop generate I random numbers
	{
		input_array[x]=1+(rand()%1000001); // interval from 1 to 1,000,000 , there are 51 numbers in the range
        //cout<<"["<<x<<"]: "<<input_array[x]<<endl;
	}

    cout<<endl<<endl;
    



    auto start = high_resolution_clock::now();

    
    AVL tree;
    int k;
    
    for (int i = 0; i < I; i++)
    {
        tree.root = tree.insert(tree.root, input_array[i]);
    }



    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by function: "<< duration.count() << " microseconds" << endl;


/*
    cout << "Tree: "<<endl;
    tree.print("", tree.root, false);
    //tree.print(tree.root);
    cout << endl << endl;


    cout << "Time taken by function: "<< duration.count() << " microseconds" << endl;


    cout << "Search for number on \"k\" index: ";
    
    cin >> k;
    getchar();
    cout<<"number on k index="<<input_array[k]<<endl;

    if (tree.search(tree.root, input_array[k]) != nullptr)
        cout << "Found" << endl;
    else
        cout << "Not Found" << endl;

    cout << "Delete number on k index" << endl;
    tree.root = tree.deleteNode(tree.root, input_array[k]);

    cout << "Tree: "<<endl;
    tree.print("", tree.root, false);
    //tree.print(tree.root);
    cout << endl;
*/

    return 0;
}