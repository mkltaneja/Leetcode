void KahnAlgo(vector<vector<int>> graph, vector<int> &ans)
{
    vector<int> Indegree(graph.size(),0);
    for(int i=0;i<graph.size();i++)
    {
        for(int ele : graph[i])
            Indegree[ele]++;
    }

    queue<int> que;
    for(int i=0;i<graph.size();i++)
        if(Indegree[i] == 0)
            que.push(i);

    while(!que.empty())
    {
        int rvtx = que.front();
        que.pop();
        ans.push_back(rvtx);

        for(int ele : graph[rvtx])
            if(--Indegree[ele] == 0)
                que.push(ele);
    }
}

vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) 
{
    vector<vector<int>> graph(numCourses,vector<int> ());
    for(vector<int> arr : prerequisites)
        graph[arr[0]].push_back(arr[1]);

    vector<int> ans;
    KahnAlgo(graph,ans);
    
    
    if(ans.size() != graph.size())
        return {};
    else
    {
        reverse(ans.begin(),ans.end());
        return ans;
    }
                
}