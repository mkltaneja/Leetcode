#include<bits/stdc++.h>
using namespace std;

// class ComponentNode
// {
//     public:
//     int value;
//     vector<ComponentNode*> comp;
//     ComponentNode(){}
//     ComponentNode(int n)
//     {
//         this->value = n;
//     }
// };

// int mx = 0;
// ComponentNode* ans;
// pair<int,int> dfs(ComponentNode* node)
// {
//     if(!node) return {0,0};

//     pair<int,int> curr = {0,0};
//     for(ComponentNode* v : node->comp)
//     {
//         pair<int,int> child = dfs(v);
//         curr.first += child.first;
//         curr.second += child.second;
//     }
//     if(curr.second)
//     {
//         int avg = (curr.first + node->value) / (curr.second + 1);
//         if(avg > mx)
//         {
//             mx = avg;
//             ans = node;
//         }
//     }

//     return {curr.first + node->value, curr.second + 1};
// }

// ComponentNode* getFasterComponent(ComponentNode* rootComponent)
// {
//     ans = rootComponent;
//     dfs(rootComponent);
//     return ans;
// }

// void dfss(ComponentNode* root)
// {
//     if(!root) return;

//     cout<<root->value<<": ";
//     cout<<root->comp.size()<<"\n";
//     for(ComponentNode* v : root->comp)
//         dfss(v);
// }

// int main()
// {
//     ComponentNode* root = new ComponentNode(200);
//     root->comp.resize(2);
//     root->comp[0] = new ComponentNode(120);
//     root->comp[1] = new ComponentNode(180);
//     ComponentNode* l = root->comp[0];
//     ComponentNode* r = root->comp[1];

//     l->comp.resize(3);
//     r->comp.resize(2);

//     l->comp[0] = new ComponentNode(110);
//     l->comp[1] = new ComponentNode(20);
//     l->comp[2] = new ComponentNode(30);
    
//     r->comp[0] = new ComponentNode(150);
//     r->comp[1] = new ComponentNode(80);

//     // dfss(root);
//     cout<<getFasterComponent(root)->value;
// }


int C(int n, int r)
{
    r = min(r, n-r);
    int a = 1, b = 1;
    for(int i = 0; i < r; i++)
        a *= n-i;
    for(int i = 0; i < r; i++)
        b *= r-i;
    return a/b;
}

int main()
{
    int n;
    cin>>n;
    vector<int> arr(n);
    for(int i = 0; i < n; i++)
        cin>>arr[i];
    int req;
    cin>>req;

    int mn, mx;
    cin>>mn>>mx;

    int tot = 0;
    for(int x : arr)
        if(x >= mn && x <= mx)
            tot++;
    
    int ans = 0;
    for(int i = req; i <= tot; i++)
    {
        int x = C(tot, i);
        ans += x;
        cout<<tot<<", "<<i<<": \n"<<x<<endl;
    }

    cout<<ans<<endl;
}