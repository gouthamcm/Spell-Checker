#include <iostream>
#define MAX_SIZE 26

using namespace std;

class TrieData
{
private:
    TrieData *children_nodes[MAX_SIZE];
    bool end_of_word;

public:
TrieData *root = NULL;
    TrieData()
    {
        this->end_of_word = false;
        for (int i = 0; i < MAX_SIZE; i++)
        {
            this->children_nodes[i] = NULL;
        }
        
    }
    void insert_query(TrieData *root, string query)
    {
        TrieData *temp = root;
        //temporary variable to store the root node
        int index;
        if (temp == NULL && query.length() > 0)
        {
            index = query[0] - 'a';
            temp->children_nodes[index] = new TrieData();
        }
        else if (query.length() == 0)
        {
            cout << "No string to be inserted";
            return;
        }
        for (int i = 0; i < query.length(); i++)
        {
            index = query[i] - 'a';
            if (!temp->children_nodes[index])
            {
                temp->children_nodes[index] = new TrieData();
            }
            temp = temp->children_nodes[index];
        }
        temp->end_of_word = true;
    }
    bool search_query(TrieData *root, string query)
    {
        if (query.length() == 0 || !root)
        {
            return false;
        }
        TrieData *temp = root;
        int index;
        for (int i = 0; i < query.length(); i++)
        {
            index = query[i] - 'a';
            if (!temp->children_nodes[index])
            {
                return false;
            }
            else
            {
                temp = temp->children_nodes[index];
            }
        }
        return temp->end_of_word;
    }
    int auto_complete(TrieData *root, string query)
    {
        TrieData *temp = root;
        int index;
        for (int i = 0; i < query.length(); i++)
        {
            index = query[i] - 'a';
            if (!temp->children_nodes[index])
            {
                return -1;
            }
            else
            {
                temp = temp->children_nodes[index];
            }
        }
        return print(temp, query);
    }
    int print(TrieData *node, string query)
    {
        if (node->end_of_word)
        {
            cout << query << endl;
            if (no_children(node))
            {
                return 1;
            }
        }
        for(int i=0; i<MAX_SIZE; i++){
            if(node->children_nodes[i]){
                query.push_back(i+'a');
                print(node->children_nodes[i], query);
                query.pop_back();
            }
        }
    }
    bool no_children(TrieData *node)
    {
        for (int i = 0; i < MAX_SIZE; i++)
        {
            if (node->children_nodes[i])
                return false;
        }
        return true;
    }
    void insert(string query){
        insert_query(root, query);
    }
    bool search(string query){
        return search_query(root, query);
    }
    int comlete(string query){
        return auto_complete(root, query);
    }
};

int main()
{

    return 0;
}