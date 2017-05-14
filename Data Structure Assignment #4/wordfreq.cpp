//  Michael Alexander
//  wordfreq.cpp
//  DS Programming Assignment #4
#include <algorithm>
#include "wordscollection.h"
#include "bintree.h"
#include "frequency.h"
using namespace FREQPROJ;
using namespace std;

binary_tree_node<frequency<string>> * insert_alpha(binary_tree_node<frequency<string>> * root, frequency<string> val)
{
    if(root == NULL) //if tree is empty insert root node
    {
        root = new binary_tree_node<frequency<string>>(val);
        return root;
    }
  
    
    if(root->data().isDataInc(val.data())) //if words match increment frequency
        return root;
    
    if(root->data() < val.data()) 
        root->set_right(insert_alpha(root->right(), val)); //recurses through tree and adds val alphabetically
    else
        root->set_left(insert_alpha(root->left(), val));
    
    return root;
}

binary_tree_node<frequency<string>> * insert_count(binary_tree_node<frequency<string>> * root, frequency<string> val)
{
    if(root == NULL)
    {
        root = new binary_tree_node<frequency<string>>(val); //if tree is empty insert root node
        return root;
    }
    
    size_t root_count = root->data().count(); // frequency of roots data
    
    // if root freq less than val freq or if they are equal than sort from Z -> A
    if(root_count < val.count() || (root_count == val.count() && root->data().data() < val.data()))
        root->set_left(insert_count(root->left(), val));
    else
        root->set_right(insert_count(root->right(), val));
    
    return root;
}

binary_tree_node<frequency<string>> * traverse(binary_tree_node<frequency<string>> * root, binary_tree_node<frequency<string>> * new_root)
{
    if(root == NULL)
        return new_root;
    
    //traverse through root recursively while adding nodes by frequency to new root
    new_root = traverse(root->left(), new_root);
    new_root = insert_count(new_root, root->data());
    new_root = traverse(root->right(), new_root);
    
    return new_root;
}

void print_tree(frequency<string> temp)
{
    cout << temp << " ";
}

int main(int argc,char * argv[])
{
    if(argc != 2)
    {
        cout << "Error!! One filename should be given as argument" << endl;
        return 0;
    }
    cout << argv[1] << endl;
    wordscollection words(argv[1]); //reads file argument
    
    binary_tree_node<frequency<string>> * root = NULL;
    
    
    while(words.hasTokens() == true) //loop for each word in the file
    {
        frequency<string> f(words.getNextToken());
        root = insert_alpha(root, f);
    }
   
    cout << "WORD FREQUENCY - Alphabetical" << endl;
    inorder(print_tree, root); // left,root,right
    cout<<endl<<endl;
    
    binary_tree_node<frequency<string>> * new_root = NULL;
    new_root = traverse(root, new_root); // traverse new root to add nodes by frequency
   
    
    cout << "WORD FREQUENCY - Highest to Lowest" << endl;
    inorder(print_tree, new_root);
    cout<<endl;
}	
