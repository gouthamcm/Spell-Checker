#include <iostream>
#include <vector>
#include <string>
#define MAX_SIZE 26

using namespace std;

class TrieData
{
private:
    TrieData *children_nodes[MAX_SIZE];
    bool end_of_word;

public:
    TrieData *root = NULL;
    TrieData *make_node()
    {
        TrieData *new_node = (TrieData *)malloc(sizeof(TrieData));

        for (int i = 0; i < MAX_SIZE; i++)
        {
            new_node->children_nodes[i] = NULL;
        }
        new_node->end_of_word = false;

        return new_node;
    }

    void insert_query(TrieData *root, string query)
    {
        TrieData *temp;
        //temporary variable to store the root node
        int index;

        if (query.length() == 0)
        {
            cout << "No string to be inserted";
            return;
        }
        temp = root;
        for (int i = 0; i < query.length(); i++)
        {
            index = query[i] - 'a';
            if (!temp->children_nodes[index])
            {
                temp->children_nodes[index] = make_node();
            }
            temp = temp->children_nodes[index];
        }
        temp->end_of_word = true;
    }
    bool search_query(TrieData *root, string query)
    {
        if (query.length() == 0)
        {
            return false;
        }
        if (!root)
        {
            cout << "hi\n";
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
    void auto_complete(TrieData *root, string query)
    {
        TrieData *temp = root;
        int index;
        for (int i = 0; i < query.length(); i++)
        {
            index = query[i] - 'a';
            if (!temp->children_nodes[index])
            {
                return ;
            }
            else
            {
                temp = temp->children_nodes[index];
            }
        }
        return print(temp, query);
    }
    void print(TrieData *node, string query)
    {
        if (node->end_of_word)
        {
            cout << query << endl;
            if (no_children(node))
            {
                return ;
            }
        }
        for (int i = 0; i < MAX_SIZE; i++)
        {
            if (node->children_nodes[i])
            {
                query.push_back(i + 'a');
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
    bool distance(string word, string query)
    {
        int N = word.length();
        int M = query.length();
        vector<vector<int>> mat(N + 1, vector<int>(M + 1));
        for (int i = 0; i <= N; i++)
        {
            mat[i][0] = i;
        }
        for (int i = 0; i <= M; i++)
        {
            mat[0][i] = i;
        }
        for (int i = 1; i <= N; i++)
        {
            for (int j = 1; j <= M; j++)
            {
                if (word[i - 1] == query[j - 1])
                {
                    mat[i][j] = mat[i - 1][j - 1];
                }
                else
                {
                    mat[i][j] = 1 + min(mat[i - 1][j], min(mat[i][j - 1], mat[i - 1][j - 1]));
                }
            }
        }
        return (mat[N][M] > 3);
    }
    void find_all_words(TrieData *root, string res, string query)
    {
        if (!root)
            return;
        TrieData *temp = root;
        if (temp->end_of_word)
        {
            if (!distance(res, query))
            {
                cout << res << "\n";
            }
        }
        for (int i = 0; i < MAX_SIZE; i++)
        {
            if (temp->children_nodes[i])
            {
                res.push_back(i + 97);
                find_all_words(temp->children_nodes[i], res, query);
                res.pop_back();
            }
        }
    }
    int min(int a, int b)
    {
        return a < b ? a : b;
    }
    void insert(string query)
    {
        if (!root)
        {
            root = make_node();
        }
        insert_query(root, query);
    }
    bool search(string query)
    {
        return search_query(root, query);
    }
    void complete(string query)
    {
        auto_complete(root, query);
    }
    void autocorrect(string query)
    {
        string res = "";
        find_all_words(root, res, query);
    }
};

int main()
{
    // TrieData ob;
    // ob.insert("hello");
    // ob.insert("bye");
    // ob.insert("dictionary");
    // ob.insert("dog");
    // ob.insert("cat");
    // ob.insert("bat");
    // ob.insert("google");
    // ob.insert("facebook");
    // ob.insert("develop");
    // ob.insert("stand");
    // ob.insert("jikod");
    // ob.insert("dmsjkc");
    // ob.insert("kaoinfa");

    // ob.autocorrect("h");
    int n; //no of words in the dict
    TrieData ob;
    string word;
    cin>>n;
    while(n--){
        cin>>word;
        ob.insert(word);
    }
    int ai;
    string ti;
    cin>>ai;
    cin>>ti;
    if(ai==1){
        int res = ob.search(ti);
        cout<<res<<endl;
    }
    else if(ai==2){
        ob.complete(ti);
    }
    else if(ai==3){
        ob.autocorrect(ti);
    }
    else{
        cout<<"Invaild query\n";
    }
    return 0;
}