#include <assert.h>
#include <sstream>
#include "qna_tool.h"

using namespace std;














//Write your code below this line
int maintainheights(SymNode* root)
{
    if (root == NULL)
    {
        return -1;
    }

    else
    {
        int h = 1 + max(maintainheights(root->left),maintainheights(root->right));
        root->height = h;
        return h;
    }
    
}

int balancefactor(SymNode* root)
{
    if (root == NULL)
    {
        return -1;
    }
    else
    {
        return ((root->right == NULL)?0:root->right->height) - ((root->left == NULL)?0:root->left->height)  ;      
    }
    
}

SymbolTable::SymbolTable()
{
    //cout << "inta" << endl;
}
SymbolTable::SymbolTable(const SymbolTable &source)
{
   // cout << "copy " << source.root << endl;
    root = copyNodes(source.root);
    size = source.size;
}

SymNode* SymbolTable::copyNodes(SymNode* node)
{
    if (node == nullptr)
        return nullptr;

    SymNode* newNode = new SymNode(*node);
    newNode->left = copyNodes(node->left);
    newNode->right = copyNodes(node->right);

    return newNode;
}
void SymbolTable::insert(string k)
{
    SymNode* newnode = new SymNode(k);

    if (size == 0)
    {
        root = newnode;
        size++;
    }

    else
    {
        SymNode* head = root;
        while (head != NULL)
        {
            if (head->key > k)
            {
                if (head->left == NULL)
                {
                    head->left = newnode;
                    newnode->par = head;
                    size++;
                    break;
                }
                else
                {
                    head = head->left;
                }
            }

            else if(head->key < k)
            {
                if(head->right == NULL)
                {
                    head->right = newnode;
                    newnode->par = head;
                    size++;
                    break;
                }
                else
                {
                    head = head->right;
                }
                
            }

            else{head->count++; return;}
            
        }
        
        maintainheights(root);
        SymNode* traversal = newnode;
        while (true)
        {
            int e = balancefactor(traversal);
            if (e == 2 or e == -2)
            {
                break;
            }
            else
            {
                if (traversal->par != NULL)
                {
                    traversal = traversal->par;
                }

                else
                {
                    traversal = traversal->par;
                    break;
                }
            }
            
        }
        

        if (traversal == NULL)
        {
            return;
        }

        SymNode* y;
        if (traversal->key > k)
        {
            y = traversal->left;
        }
        else{y = traversal->right;}

        SymNode* x;
        if (y->key > k)
        {
            x = y->left;
        }
        else{x = y->right;}

        if (traversal->left == y and y->left == x)
        {
            root = traversal->RightRightRotation();
        }
        
        else if (traversal->left == y and y->right == x)
        {
            root = traversal->LeftRightRotation();
        }

        else if (traversal->right == y and y->right == x)
        {
            root = traversal->LeftLeftRotation();
        }

        else{root = traversal->RightLeftRotation();}

        maintainheights(root);
    }
}

unsigned long long SymbolTable::search(string k)
{
    SymNode* head = root;
    while (head != NULL)
    {
        if (head->key == k)
        {
            break;
        }
        
        else if (head->key < k)
        {
            head = head->right;
        }

        else{head = head->left;}

        if (head == NULL)
        {
            break;
        }
    }

    if (head == NULL)
    {
        return 0;
    }

    else{return head->count;}
    return 0;
    

}

int SymbolTable::get_size()
{
    return size;

}

SymNode* SymbolTable::get_root()
{
    return root;

}

void destroy(SymNode* root)
{
    if (root != NULL)
    {
        destroy(root->left);
        destroy(root->right);
        //cout << "cleared "<< root->key <<endl;
        delete(root);
        root = nullptr;
    }
    
}

SymbolTable::~SymbolTable()
{
    //cout << "into destro" << endl;
    destroy(root);
    root = nullptr;
    //free(root);
}

// void print_AVL_Tree(SymNode* root, int depth = 0) {
    
//     for (int i = 0; i < depth; ++i) {
//         std::cout << "  ";
//     }
//     cout << root->key << endl;
    
//     if (root->left != nullptr) {
//         print_AVL_Tree(root->left, depth+1);
//     }
//     if (root->right != nullptr) {
//         print_AVL_Tree(root->right, depth + 1);
//     }
// }

// int main()
// {
//     SymbolTable a;
//     a.insert("a");
//     a.insert("b");
//     a.insert("c");
//     a.insert("e");
//     a.insert("d");
//     // a.insert("6");
//     // a.insert("7");
//     // a.insert("8");

//     // a.remove("6");
//     // a.remove("5");
//     // a.remove("4");
//     // a.remove("3");
//    // print_AVL_Tree(a.get_root());
//    a.remove("a");
//    a.remove("b");
//     cout << "done";
// }




vector<string> ppr(std::string pat) {

    vector<string> ret;
    string word = "";
    for (int i = 0; i < pat.size(); i++) {
        char s = pat[i];

        if( s == '!' || s == '\"' || s == '[' || s == '.' || s == ',' || s == '?' ||
            s == ']' || s == '(' || s == ')' || s == '@' || s == ';' || s == ':' || 
            s == '\'' || s == '-' || s == ' ')
            {
                if(word.size() != 0)
                {
                    ret.push_back(word);
                    word = "";

                }

            }
        
        else {
            if(s - 'A' >=0 and s - 'Z' <= 0) {
                word += (char)(s + 32);

            }

            else{word += s;}
        }
    }

   /* for (int i = 0; i < pat.size(); i++)
    {
        char s = pat[i];
        if (s - 'a' >= 0 and s -'z' <= 0 )
        {
            word+= s;
        }

        else if (s - 'A' >=0 and s- 'Z' <= 0)
        {
            word += (char)(s+32);
        }

        else
        {
            if (word.size() != 0 )
            {
                ret.push_back(word);
                word = "";
            }
            
        }
        
        
        
    }*/
    

    if(word.size() !=0) {
        ret.push_back(word);
        word = "";
    }

    return ret;
    
}




QNA_tool::QNA_tool()
{
    mainobj = vector<vector<vector<SymbolTable>>>(99); 
    // Implement your function here  
}

QNA_tool::~QNA_tool()
{
    // for (int i = 0; i < mainobj.size(); i++)
    // {
    //     for (int j = 0; j < mainobj[i].size(); j++)
    //     {
    //         for(int k = 0; k < mainobj[i][j].size(); k++)
    //         {
    //             delete mainobj[i][j][k];
    //             mainobj[i][j][k] = nullptr;
    //         }
    //     }
        
    // }
    
    // Implement your function here  
}


void QNA_tool::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence)
{
    if (book_code >= mainobj.size())
    {
        mainobj.resize(mainobj.size() + 10);
    }

    if (mainobj[book_code].size() <= page)
    {
        int c = (512>page)?512:page;
        mainobj[book_code].resize(c+3);
    }

    if (mainobj[book_code][page].size() <= paragraph )
    {
        int c = (16>paragraph)?16:paragraph;
        mainobj[book_code][page].resize(c+3);
    }

    // if (mainobj[book_code][page][paragraph] == nullptr)
    // {
    //     mainobj[book_code][page][paragraph] = getNode();
    // }
    

    vector<string> words = ppr(sentence);
    for(string k : words){
    mainobj[book_code][page][paragraph].insert(k);
    }
    
    // Implement your function here  
    return;
}



vector<pair<string, double>> QNA_tool::scoring(string sentence)
{
    vector<string> words = ppr(sentence);
    vector<pair<string, unsigned long long>> result;
    vector<pair<string,double>> resoto;
    
    for (int i = 0; i < words.size(); i++)
    {
        unsigned long long totalcount = 0;
        for (size_t j = 0; j < mainobj.size(); j++)
        {
            for (size_t k = 0; k < mainobj[j].size(); k++)
            {
                for (size_t l = 0; l < mainobj[j][k].size(); l++)
                {
                    totalcount += mainobj[j][k][l].search(words[i]);
                    
                }
                
            }
            
        }    
        result.push_back(make_pair(words[i],totalcount));        
    }



    
    for (int i = 0; i < result.size(); i++)
    {
        ifstream frequency_file("unigram_freq.csv");
        
        std::string word1;
        std::string countofword;

        getline(frequency_file,word1);

        while (getline(frequency_file,word1,','))
        {
            getline(frequency_file,countofword);

            if (word1 == result[i].first)
            {   
                
                double c = (double)(result[i].second)/(double)(stod(countofword));         
                resoto.push_back(make_pair(result[i].first,c));
            
                break;
            }
        }

        frequency_file.close();
    }

    return resoto;    
}

vector<QNA_tool::scored_para> QNA_tool::tity(string sentence)
{
    vector<scored_para> ret;

    vector<pair<string,double>> scores = scoring(sentence);

    for (size_t i = 0; i <mainobj.size(); i++)
    {
        for (size_t j = 0; j < mainobj[i].size(); j++)
        {
            for (size_t k = 0; k < mainobj[i][j].size(); k++)
            {
                double __score = 0;
                for (size_t w = 0; w <scores.size(); w++)
                {
                    __score += ((double)mainobj[i][j][k].search(scores[w].first))*scores[w].second;
                }

                scored_para qq;
                qq.book_no = i;
                qq.page_no = j;
                qq.para_no = k;
                qq.score = __score;

                ret.push_back(qq);
                
            }
            
        }
        
    }
    

    return ret;
}

Node* QNA_tool::get_top_k_para(string question, int k) 
{
    vector<scored_para> a = tity(question);

    heapSort(a,k);

    Node *root = new Node;
    root->right = nullptr;
    root->left = nullptr;

    Node* temp = root;

    while(temp->right != nullptr) {
        temp = temp->right;
    }

    int n = a.size();
    for (int i = n-1; i >= n-k; i--) {

        Node* newnode = new Node;
        newnode->left = temp;
        newnode->right = nullptr;
        newnode->book_code = a[i].book_no;
        newnode->page = a[i].page_no;
        newnode->paragraph = a[i].para_no;
        newnode->sentence_no = -1;
        temp->right = newnode;
        temp = temp->right;

    }

    Node* temp1 = root->right;
    root->right = nullptr;
    delete root;
    
    return temp1;

    // Implement your function here
    return nullptr;
}

void QNA_tool::query(string question, string filename){
    // Implement your function here  
    std::cout << "Q: " << question << std::endl;
    std::cout << "A: " << "Studying COL106 :)" << std::endl;
    return;
}

std::string QNA_tool::get_paragraph(int book_code, int page, int paragraph){

    cout << "Book_code: " << book_code << " Page: " << page << " Paragraph: " << paragraph << endl;
    
    std::string filename = "mahatma-gandhi-collected-works-volume-";
    filename += to_string(book_code);
    filename += ".txt";

    std::ifstream inputFile(filename);


    std::string tuple;
    std::string sentence;

    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open the input file " << filename << "." << std::endl;
        exit(1);
    }

    std::string res = "";

    while (std::getline(inputFile, tuple, ')') && std::getline(inputFile, sentence)) {
        // Get a line in the sentence
        tuple += ')';

        int metadata[5];
        std::istringstream iss(tuple);

        // Temporary variables for parsing
        std::string token;

        // Ignore the first character (the opening parenthesis)
        iss.ignore(1);

        // Parse and convert the elements to integers
        int idx = 0;
        while (std::getline(iss, token, ',')) {
            // Trim leading and trailing white spaces
            size_t start = token.find_first_not_of(" ");
            size_t end = token.find_last_not_of(" ");
            if (start != std::string::npos && end != std::string::npos) {
                token = token.substr(start, end - start + 1);
            }
            
            // Check if the element is a number or a string
            if (token[0] == '\'') {
                // Remove the single quotes and convert to integer
                int num = std::stoi(token.substr(1, token.length() - 2));
                metadata[idx] = num;
            } else {
                // Convert the element to integer
                int num = std::stoi(token);
                metadata[idx] = num;
            }
            idx++;
        }

        if(
            (metadata[0] == book_code) &&
            (metadata[1] == page) &&
            (metadata[2] == paragraph)
        ){
            res += sentence;
        }
    }

    inputFile.close();
    return res;
}

void QNA_tool::heapify(vector<QNA_tool::scored_para>& arr, int n, int i) {
    
    int largest = i; // Initialize the root as the largest
    int left = 2 * i + 1; // Index of the left child
    int right = 2 * i + 2; // Index of the right child

    // If the left child is smaller than the root
    if (left < n && arr[left].score > arr[largest].score)
        largest = left;

    // If the right child is smaller than the current largest
    if (right < n && arr[right].score > arr[largest].score)
        largest = right;

    // If the largest is not the root, swap and recursively heapify the affected sub-tree
    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void QNA_tool::heapSort(vector<QNA_tool::scored_para>& arr, int k) {
    
    int n = arr.size();

    // Build max heap
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Extract elements from the heap one by one
    for (int i = n - 1; i >= n-k-1; i--) {
        // Swap the root (maximum element) with the last element
        std::swap(arr[0], arr[i]);

        // Call max heapify on the reduced heap
        heapify(arr, i, 0);
    }
}



void QNA_tool::query_llm(string filename, Node* root, int k, string API_KEY, string question){

    // first write the k paragraphs into different files

    Node* traverse = root;
    int num_paragraph = 0;

    while(num_paragraph < k){
        assert(traverse != nullptr);
        string p_file = "paragraph_";
        p_file += to_string(num_paragraph);
        p_file += ".txt";
        // delete the file if it exists
        remove(p_file.c_str());
        ofstream outfile(p_file);
        string paragraph = get_paragraph(traverse->book_code, traverse->page, traverse->paragraph);
        assert(paragraph != "$I$N$V$A$L$I$D$");
        outfile << paragraph;
        outfile.close();
        traverse = traverse->right;
        num_paragraph++;
    }

    // write the query to query.txt
    ofstream outfile("query.txt");
    outfile << "These are the excerpts from Mahatma Gandhi's books.\nOn the basis of this, ";
    outfile << question;
    // You can add anything here - show all your creativity and skills of using ChatGPT
    outfile.close();
 
    // you do not need to necessarily provide k paragraphs - can configure yourself

    // python3 <filename> API_KEY num_paragraphs query.txt
    string command = "python3 ";
    command += filename;
    command += " ";
    command += API_KEY;
    command += " ";
    command += to_string(k);
    command += " ";
    command += "query.txt";

    system(command.c_str());
    return;
}
/*
int main()
{
    QNA_tool a;

    a.insert_sentence(1, 1, 1, 1, "the ");
    a.insert_sentence(1, 1, 1, 2, "the?");
    a.insert_sentence(1, 1, 1, 3, "the,");
    a.insert_sentence(1, 1, 1, 4, "the.");
    a.insert_sentence(1, 1, 1, 5, "the!");
    a.insert_sentence(1, 1, 2, 1, "fuck(");
    a.insert_sentence(1, 1, 2, 2, "fuck)");
    a.insert_sentence(1, 1, 2, 3, "fuck");
    a.insert_sentence(1, 1, 2, 4, "fuck");
    a.insert_sentence(1, 1, 2, 5, "fuck@");
    a.insert_sentence(1, 1, 3, 1, "is");
    a.insert_sentence(1, 1, 3, 2, "is");
    a.insert_sentence(1, 1, 3, 3, "is");
    a.insert_sentence(1, 1, 3, 4, "is");
    a.insert_sentence(1, 1, 3, 5, "is");
    a.insert_sentence(1, 2, 1, 1, "your");
    a.insert_sentence(1, 2, 1, 2, "your");
    a.insert_sentence(1, 2, 1, 3, "your");
    a.insert_sentence(1, 2, 1, 4, "your");
    a.insert_sentence(1, 2, 1, 5, "your");
    a.insert_sentence(1, 3, 1, 1, "name");
    a.insert_sentence(1, 3, 1, 2, "name");
    a.insert_sentence(1, 3, 1, 3, "name");
    a.insert_sentence(1, 3, 1, 4, "name");
    a.insert_sentence(1, 3, 1, 5, "name");

    //cout << hash_value("the") << endl << hash_value("fuck");

    string q = "the fuck is your name?";

    //auto n = a.tity(q);

    //cout << n[0].first << " " << n[0].second << endl;
   

    Node* ss = a.get_top_k_para(q,1);
    cout << "done" << endl;

}*/