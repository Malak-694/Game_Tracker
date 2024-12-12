/*
 * Salma Gamal Kamel : 20221073
 * 8/12/2024 updated 9/12/2024
 * Task 3: Skip List
 * a. Implement a Skip List data structure
 */
/*
 *updating implement task b 10/12/2024
 *Malak Ahmed 20221157
 *Salma Gamal 20221073
 *Aya Ehab Ramadan 20221209 implements point ii in b 
 */
#include <iostream>
#include <bits/stdc++.h>
#include <string>

using namespace std;
//struct player{
//    string name;
//    int score;
//    friend bool operator<(const player& p1, const player& p2) {
//        return p1.score < p2.score;
//    }
//};

const int maxLevel = 4; // Maximum Level of the skip list

struct  node {
public:
    int data;
    string name;
    vector<node*> next;     // To maintain the levels of the skip list
    node(int d,int l,string n):data(d),next(l+1,nullptr),name(n){}// declaring the data and the level of the node

};
// The skipList
// A skip list is a data structure that allows for efficient search,
// insertion and deletion of elements in a sorted list.It is a probabilistic data structure,
// skip lists provide a simple and efficient alternative to balanced trees for certain use cases, particularly when the average number of elements in the list is large.

class skipList
{
private:
    int level;
public:
    skipList();
    ~skipList();

    void insert(node player);
    bool remove(node player);
    void update_player( node player , int new_score);
    bool search(int data);
    int searchBYname(string name );
    void display();

    node* header;
};

//constructor of the skipList class
skipList::skipList()
{
    header=new node(0, maxLevel,"");
    level=0;
}

//destructor
skipList::~skipList() {
    delete header;
}


//                    **Insertion in skip list**
//The average time complexity of insertion in a skip list is O(log n)
void skipList::insert(node player)
{
    string name =player.name;
    int data =player.data;
    int newLevel = 0;
    // Deciding the level of inserting node on the basis of *coin toss*
    //rand() returns a random integer
    while (newLevel < maxLevel && rand() % 2 == 1) {  // Simulate coin toss
        newLevel++;
    }
    // Resizing the size of the levels .
    if (level< newLevel)
    {
        header->next.resize(newLevel + 1);
        level = newLevel;

    }

    node* curr = header; //pointer to the header to traverse through the skip list
    vector<node*> update(level+1,nullptr); // To store the update node at each level
    // Loop over the levels upto which we want the value to be inserted
    for (int i = level; i >= 0; i--)
    {
        // Finding the place for the inserting value
        while (curr->next[i]  && curr->next[i]->data < data)
        {
            curr = curr->next[i];
        }
        update[i] = curr;
    }
    curr = curr->next[0];   // Moves the current to the next node at level 0
    if(curr==nullptr|| curr->name != name) // if the current is null then it does not exist we need to insert the value
    {
        node* newNode = new node(data, level,std::move(name));
        for (int i=0; i <= newLevel; i++)
        {
            newNode->next[i] = update[i]->next[i]; // Make new node point to the next node
            update[i]->next[i] = newNode;  // Make the previous node point to the new node
        } cout <<name<< data << " joined successfully.\n";

    }
    else
    {
        cout<< name<<data << " already exists.\n";  // Incase if value already exists
    }
}

//                    **Deletion in skip list**
//The average time complexity of deletion in a skip list is O(log n)

bool skipList::remove(node player) {
    string name =player.name;
    int data =player.data;
    node* curr = header;  // start by setting a current pointer to the header node
    vector<node*> update(level+1); // Create an update vector to store the updated node at each level,

    for (int i = level; i >= 0; i--)
    {
        while (curr->next[i]  && curr->next[i]->data < data)
        {
            curr = curr->next[i];
        }
        update[i] = curr;
    }

    curr = curr->next[0]; // Set the current pointer to the next node at level 0.
    if(curr != nullptr && curr->data == data && curr->name==name)// If the value is present then delete the value
    {
        for (int i=0; i <= level; i++)  // Deleting the value from each level
        {
            //setting the pointers
            if(update[i]->next[i]!=curr)
                break;
            update[i]->next[i] = curr->next[i];
        }
        delete curr; // deleting the node

        while (level > 0 && header->next[level]==nullptr)// decrement the level variable incase there is not any value at that level
        {
            level--;//when a level becomes completely empty.
        }

        cout<< name << " deleted successfully.\n";
        return true;
    }
    else
    {
        cout << name << " not found.\n";
        return false;
    }
}


//                    **Searching in skip list**
//The efficient searching mechanism gives the skip list priority over the other data structure. While searching, it utilizes the advantage of skipping over large portions of the data from the upper layers
// This helps achieve a faster search time compared to a simple linked list, while still being simpler and more flexible than more complex balanced trees like AVL or Red-Black trees.
//he average time complexity of search in a skip list is O(log n)

bool skipList::search(int data)
{
    node* curr = header;

    for (int i = level; i >= 0; i--)// Begin traversing from the top level and iteratively approaching the bottom of the skip list
    {
        while (curr->next[i]  and curr->next[i]->data < data)// keep on moving forward if the value of the next node is less than the searching node otherwise  move downward (handled by outer for loop)
        {
            curr = curr->next[i];// moving forward
        }
    }
    curr = curr->next[0];// Move to the next of the node at level 0
    if (curr != nullptr && curr->data == data) //if value is found
    {
        cout << data << " found.\n";
        return true;
    }
    else // Incase value does not exist
    {
        cout << data << " not found.\n";
        return false;
    }
}

//**Display skip list**
void skipList::display()
{
    cout<<"Displaying the list:\n";
    for (int i = level; i >= 0; i--) {
        node* curr = header;
        cout<<"Level "<<i<<":- ";
        while (curr->next[i])
        {
            cout<<curr->next[i]->name<<" : "<<curr->next[i]->data<<"  /  ";
            curr = curr->next[i];
        }cout<<"\n";
    }
}
void skipList::update_player( node player , int new_score){
    bool removed;
    removed= remove(player);
    if(removed) {
        player.data = new_score;
        insert(player);
    }else cout<<"this player does not exist";
}
int skipList::searchBYname(string name ){

    node* curr = header;
    while (curr->next[0])
    {
       if(curr->next[0]->name==name){
           return curr->next[0]->data;
       }

        curr = curr->next[0];
    }return -1;
}
void GetTopNPlayers (node *head, int N){
    vector <pair<string,int>> LeaderBoard;
    node* Start = head ->next[0];
    while(Start){
      LeaderBoard.push_back({Start->name,Start->data});
      Start = Start->next[0];
    }
//    sort (LeaderBoard.begin(),LeaderBoard.end());
  sort(LeaderBoard.begin(), LeaderBoard.end(), [](const pair<string, int> &a, const pair<string, int> &b) {
      return a.second > b.second;
  });
    for(int i = 0 ;i<min(N,(int)LeaderBoard.size());i++){
      cout << LeaderBoard[i].first<<" : "<<LeaderBoard[i].second<<'\n';
}
}

int main()
{

    skipList SkipList;
    int x;
   // map <string , int > m;
    int round =0; // i assume that the level and the round are the same thing
    cout<<"welcome to the game \n press welcome to continue";
    while(true){
        string name;
        int score;
        node p(0,0,"");
        cout<<"what do you want to do : \n1. enter a new player "
              "\n2. remove an existing player "
              "\n3. update the score of a player "
              "\n4. show the current score of a player "
              "\n5. finish the round and show all scores "
              "\n6. show the top ten"
              "\n7. end\n"
              ;
        cin>>x;
        switch(x){
          case 1:
                cout<<"enter the player name and score\n";
                cin>>p.name>>p.data;
                SkipList.insert(p);
                break;
          case 2:
                cout<<"enter the player name \n";
                cin>>p.name;
                p.data=SkipList.searchBYname(p.name);
                SkipList.remove(p);
                break;
          case 3:
                cout<<"enter the name of the player and the new score\n";
                cin>>p.name>>score;
                p.data=SkipList.searchBYname(p.name);
                SkipList.update_player(p,score);
                break;
          case 4:
               cout<<"Enter the palyer's name to view their score : \n";
               cin>>p.name;
               p.data=SkipList.searchBYname(p.name);
               if(p.data!=-1) cout<<p.data<<"\n";
               else cout<<"Player not found\n";
               break;
          case 5:
              cout << "Round finished! Displaying all players and their scores:\n";
              SkipList.display();
              break;
          case 6:
              GetTopNPlayers(SkipList.header,10);
              break;
          default:
            cout << "Invalid choice. Please select a valid option.\n";
          break;
        }
        SkipList.display();
        if(x>6) break;




    }




    return 0;
}
