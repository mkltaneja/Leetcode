class LRUCache {
public:

    class Node
    {
        public:
        int key, val;
        Node* next, *prev;
        Node(int key, int val)
        {
            this->key = key;
            this->val = val;
            this->next = nullptr;
            this->prev = nullptr;
        }
    };

    unordered_map<int,Node*> mp;
    Node* head, *tail;
    int cap;

    LRUCache(int capacity) 
    {
        head = nullptr;
        tail = nullptr;
        this->cap = capacity;
    }

    void changeHead(Node* node)
    {
        if(node->prev)
            node->prev->next = node->next;
        if(node->next)
            node->next->prev = node->prev;
        
        node->next = head;
        head->prev = node;
        node->prev = nullptr;

        head = node;
    }

    void changeTail()
    {
        if(mp.size() > 1)
            tail = tail->prev;
    }
    
    int get(int key) 
    {
        if(!mp.count(key)) return -1;
        
        Node* node = mp[key];
        if(node == tail)
            changeTail();
        if(node != head)
            changeHead(node);

        return node->val;
    }    

    void put(int key, int value) 
    {
        if(mp.count(key))
        {
            Node* node = mp[key];
            if(node == tail)
                changeTail();
            if(node != head)
                changeHead(node);
            node->key = key;
            node->val = value;
        }
        else 
        {
            Node* node = new Node(key, value);
            mp[key] = node;
            if(mp.size() > cap)
            {
                mp.erase(tail->key);
                if(tail->prev)
                    tail->prev->next = nullptr;
                changeTail();
            }
            if(head == nullptr)
            {
                head = node;
                tail = node;
            }
            else changeHead(node);
        }
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
