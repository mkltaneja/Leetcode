 void KahnsAlgo(vector<vector<int>> graph, vector<int> &ans)
{
    vector<int> InDegree(graph.size(),0);
    
    for(int i=0;i<graph.size();i++)
        for(int ele : graph[i])
            InDegree[ele]++;
    
    queue<int> que;
    for(int i=0;i<InDegree.size();i++)
        if(InDegree[i] == 0)
            que.push(i);
    
    while(!que.empty())
    {
        int rvtx = que.front();
        que.pop();
        ans.push_back(rvtx);

        for(int ele : graph[rvtx])
            if(--InDegree[ele] == 0)
                que.push(ele);
    }
}

bool canFinish(int numCourses, vector<vector<int>>& prerequisites) 
{
    if(prerequisites.size() == 0)
        return true;
    vector<vector<int>> graph(numCourses,vector<int>());
    for(vector<int> ar : prerequisites)
        graph[ar[1]].push_back(ar[0]);
    
    vector<int> ans;
    KahnsAlgo(graph,ans);
    
    return ans.size() == numCourses;
}