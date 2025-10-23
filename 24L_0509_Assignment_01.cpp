    // Muhammad Obaidullah (24L-0509) Assignment 01 

    #include<iostream> 
    #include<fstream> 
    #include<string> 
    using namespace std; 


    // Question 1 - Implementation of the Singly Linked List with all the necessary requirments 
    // Here we are going to use forward declaration 
    template <typename T>
    class LinkedList{
        private:
        class Node{     // Yahan par ham aik node class ko initialize kar rahe hain jo ke linked list ke andar data store karegi
            public:
            T data;
            Node* next; 

            Node(T value, Node*next = nullptr){   // The constructor to store the values into the Linked List 
                this->data = value; 
                this->next = next; 
            }

            //Destructor for the Node class to free up the memory 
            ~Node(){
                next = nullptr; 
            }
        }; 

        Node*head; 
        Node*tail; 
        int size; 

        public:
        //The default constructor for the Linked List to initialize the values accordingly 
        LinkedList(){
            head = nullptr; 
            tail = nullptr; 
            size = 0; 
        }
        
        //Destructor to free up the memory within the Linked List. This is not mandatory but as a good coding practice I am utilizing it. 
        ~LinkedList(){
            Node* current = head; 
            while(current){
                Node* temp = current; 
                current = current->next; 
                delete temp; 
            } 
            head = tail = nullptr; 
            size = 0; 

        }
        
        void insert(T val){                       //Inserting a value at the front (using for adding a follower)
            Node* newNode = new Node(val,head);
            head = newNode; 
            if(!tail){
                tail = head; 
            }
            size++; 
        }

        //Removing a specific value 
        bool remove(T val){
            Node* curr = head;
            Node*prev = nullptr;

            while(curr){
                if(curr->data == val){
                    if(prev){
                        prev->next = curr->next;
                        if(curr == tail) tail=prev; 
                    } else{   //We remove the head 
                        head = curr->next; 
                        if(!head) tail = nullptr; 
                    }
                    delete curr;
                    size--;
                    return true; 
                }
                prev = curr;
                curr= curr->next; 
            }
            return false; 
        }

        bool isEmpty() const{
            return head ==nullptr; 
        }

        class Iterator{    // The Iterator class is implemented inside  the Linked List to ensure the concept of the nested classes. 
            Node* current; 
            public:
            Iterator(Node*ptr = nullptr){   // Yahan par Iterator ke upar pointer ki initialization ho rahi hai. 
                current = ptr; 
            }

            Iterator&operator++(){                    // The increment operator for the Iterator Class  for the prefix ++ 
                if(current) current= current->next; 
                return *this; 
            }

            Iterator operator++(int){ 
                Iterator temp = *this;
                ++(*this); 
                return temp; 

            }

            bool operator==(const Iterator& other) const{
                return current == other.current;   //This is the operator for returning the value if one value equals the other value. 
            }

            bool operator!=(const Iterator& other) const{
                return current != other.current; 
            }

            T& operator*(){
                return current->data;   
            }

            friend class LinkedList; 
        };

        //Yeh hamaray linked lists ke starting and ending points hain. 
        Iterator begin() { return Iterator(head); } 
        Iterator end()  { return Iterator(nullptr);}
    }; 



    //Question 2 --> Implementation of the Stack With the help of a particular Linked List 
    //For a Linked List Implementation we only need to ensure that we are getting the values of the things properly. 
    template<typename T>
    class Stack{
        private: 

        class Node{                               // Initializing the Node Class within the stack to store the different types of the values. 
            public: 
            T data; 
            Node* next; 

            Node(T value,  Node*next = nullptr){
                this->data = value; 
                this->next = next; 
            }
        }; 

        Node* top;             // A temporary pointer that points to the start of the stack made with the help of the linked list. 
        int elementcount;      // Current number of the elements that are being stored in the stack. 
        int capacity;           // This is the maximum size of the stack. 

        public: 
        // We are making a default constructor for the stack 
        Stack(int size = 100 ){ 
            capacity = size;      // The maximum size the array can store  
            elementcount = 0;            // The element that is being pointed by the stack.  
            top = nullptr;        // Initially if there are no values in the stack, it means that the top will point to the null pointer. 
        } 

        ~Stack(){
            while(top !=nullptr){
                Node* temp = top;
                top = top->next;
                delete temp; 
            } 
        }

        void push(T val){     // Here we are going to be inserting the values at the head since the values are initially inserted at the head value 
        if(isFull()){ 
            cout << "Ooops... Stack Overflow, cannot add more values " << endl; 
            return; 
        }
        Node* newNode = new Node(val, top);    // Here the newNode points to the top of the node with the help of a parameter of the next node the new node points to. 
        top = newNode;                           // Updating the head value. 
        elementcount++;                                 //Incrementing the value as the value has been added to the stack. 
        }

        void pop(){ 
            if(isEmpty()){
                throw runtime_error("Stack is empty "); 
            }
            
            Node*temp = top;  // A temporary pointer now points to the start of the stack. 
            top = top->next;  // The top aka the stack is pointer is now incremented to the next element. 
            delete temp;      // The first element is now deleted with the help of the temp variable jo keh first element of the stack ko point kar raha hai 
            elementcount--;          // Kyunke value remove hogai hai, count decrement hojayega. 

        }

        T topElement(){
            if(isEmpty()){
                cout << "Bhaiya, Stack Khali hai! Kuch bhi nahi store top ke upar :( " << endl; 
                return T(); 
            }
            return top->data; 
        }
        
        bool isEmpty(){              // The stack will be empty only if the top pointer points to the null pointer of the stack. 
            return top == nullptr; 
        }

        bool isFull(){              // If the stack is going to be full, then we already know that the count is going to be equal to the maximum capacity of the Stack. 
            return capacity == elementcount;     
        }

    }; 


    //Question 3 --> Implementing the Class OnlinePlatform. 
    // Ham yahan par aik iteration kar rahe hain har user keh liye till the end of the user. 
    // Queue hamarey paas list of users to visit store kar rahi hai. 
    // Influence array idhar un users ka track rakh rahi hai jo keh news dekh chukay hain and we are not counting them twice. 
    // Hamaray paas direct influence keh liye aik visited loop hai. 
    // Algo sab se pehle direct followers dekhe ga aur us ko queue ke andar add kardega 
    // Now the main BFS loop will run the reachCount holds the number of people influenced. 
    
    

    template<typename T>
    class OnlinePlatform {
    private:
        int totalUsers;              // Number of users in the system
        LinkedList<T>* followList;   // Array of linked lists storing each user's followers

    public:

        // Default constructor
        OnlinePlatform() {
            totalUsers = 0;
        }

        void input(const string& path) {
            ifstream fin(path.c_str());

            if (!fin) {
                cout << "Unable to open the file: " << path << endl;
                return;
            }

            fin >> totalUsers;                    // Read number of users from the first line of the file. 
            followList = new LinkedList<T>[totalUsers + 1];

            cout << endl<<"Reading data from file: " << path << endl;

            int userID;
            char dash;
            string line;

            // Read line by line
            while (fin >> userID >> dash) {
                string restOfLine;
                getline(fin, restOfLine);         // Get the remaining line after '-'

                // Process each follower in that line
                int follower = 0;
                for (size_t i = 0; i < restOfLine.size(); i++) {
                    if (isdigit(restOfLine[i])) {
                        follower = follower * 10 + (restOfLine[i] - '0');
                    } else if (follower != 0) {
                        followList[userID].insert(follower);
                        follower = 0;
                    }
                }
                if (follower != 0)
                    followList[userID].insert(follower);
            }

            cout << "Data successfully loaded for " << totalUsers << " users.\n";
            fin.close();
        }

        void addFollower(T userID, T followerID) {
            if (userID <= 0 || userID > totalUsers || followerID <= 0 || followerID > totalUsers) {
                cout << "Invalid User or Follower ID!" << endl;
                return;
            }
            if (userID == followerID) {
                cout << "A user cannot follow themselves!" << endl;
                return;
            }

            followList[userID].insert(followerID);
            cout << "Follower " << followerID << " added to User " << userID << endl;
        }

        void removeFollower(T userID, T followerID) {
            if (userID <= 0 || userID > totalUsers) {
                cout << "Invalid User ID!" << endl;
                return;
            }
            bool removed = followList[userID].remove(followerID);
            if (!removed)
                cout << "No follower with ID " << followerID << " found for user " << userID << endl;
            else
                cout << "Follower " << followerID << " removed successfully." << endl;
        }

        
        void showAllFollowers() {
            cout <<endl<< "======= COMPLETE FOLLOWER DATABASE ======="<<endl;
            for (int i = 1; i <= totalUsers; i++) {
                cout << "User " << i << " → ";
                typename LinkedList<T>::Iterator it;  //
                for (it = followList[i].begin(); it != followList[i].end(); ++it)
                    cout << *it << " ";
                cout << endl;
            }
            cout << "==========================================" << endl;
        }

        void calculateFakeNewsSpread() {
            int mostInfluential = -1;
            int maxReach = -1;

            // Process every user in the network
            for (int u = 1; u <= totalUsers; u++) {
                cout << endl<<"Analyzing User " << u << "'s Fake News Spread..."<<endl;

                // Tracking array for influence status
                int influence[101] = {0};   // 0 = not reached, 1 = reached
                int queue[101];             // Manual queue
                int front = 0, rear = 0;    // Pointers for queue indices
                int reachCount = 0;

                // Step 1: Enqueue direct followers
                typename LinkedList<T>::Iterator it;   //  This is the class for the Iterator and allows us to put the direct followers in a queue. 
                cout << "Direct Followers: ";
                for (it = followList[u].begin(); it != followList[u].end(); ++it) {
                    int f = *it;
                    if (influence[f] == 0) {
                        queue[rear++] = f;
                        influence[f] = 1;
                        reachCount++;
                        cout << f << " ";
                    }
                }

                cout << endl<<"Indirect Spread Levels:"<<endl;

                // Step 2: Level-by-level spreading with the help of an algorithm that is similar to Breadth First Search. 
                int level = 1;
                while (front < rear) {
                    int currentSize = rear - front; // number of users in current wave
                    cout << "   Level " << level++ << ": ";

                    // Process all users of this level
                    for (int i = 0; i < currentSize; i++) {
                        int currUser = queue[front++];

                        // Spread to their followers
                        typename LinkedList<T>::Iterator it2;   
                        for (it2 = followList[currUser].begin(); it2 != followList[currUser].end(); ++it2) {
                            int follower = *it2;
                            if (influence[follower] == 0 && follower != u) {
                                queue[rear++] = follower;
                                influence[follower] = 1;
                                reachCount++;
                                cout << follower << " ";
                            }
                        }
                    }
                    cout << endl;
                }

                cout << "Total People Reached: " << reachCount << endl;
                cout << "--------------------------------------------\n";

                if (reachCount > maxReach) {
                    maxReach = reachCount;
                    mostInfluential = u;
                }
            }

            cout << endl<<"Most Influential User: " << mostInfluential
                << " (Reached " << maxReach << " users)" << endl;
        }

        // Destructor
        ~OnlinePlatform() {
            delete[] followList;
            followList = nullptr;
            totalUsers = 0;
        }
    };


    int main(){ 
        OnlinePlatform <int> SocialMedia;
        SocialMedia.input("data.txt");
        SocialMedia.calculateFakeNewsSpread();
        return 0; 
    }
