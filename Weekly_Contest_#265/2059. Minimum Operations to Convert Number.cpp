
int minimumOperations(vector<int> &nums, int start, int goal)
{
    vector<int> dis(1001, -1);
    dis[start] = 0;
    queue<int> que;
    que.push(start);

    while (!que.empty())
    {
        int x = que.front();
        que.pop();

        for (int y : nums)
        {
            int z = x + y;
            if (z == goal)
                return dis[x] + 1;
            if (z >= 0 && z <= 1000 && dis[z] == -1)
            {
                dis[z] = dis[x] + 1;
                que.push(z);
            }

            z = x - y;
            if (z == goal)
                return dis[x] + 1;
            if (z >= 0 && z <= 1000 && dis[z] == -1)
            {
                dis[z] = dis[x] + 1;
                que.push(z);
            }

            z = x ^ y;
            if (z == goal)
                return dis[x] + 1;
            if (z >= 0 && z <= 1000 && dis[z] == -1)
            {
                dis[z] = dis[x] + 1;
                que.push(z);
            }
        }
    }

    return -1;
}