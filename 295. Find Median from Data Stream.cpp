class MedianFinder
{
public:
    priority_queue<int> mx;
    priority_queue<int, vector<int>, greater<int>> mn;
    MedianFinder()
    {
    }

    void addNum(int num)
    {
        if (mx.empty() || mx.top() >= num)
            mx.push(num);
        else
            mn.push(num);

        if (mx.size() > mn.size() + 1)
        {
            mn.push(mx.top());
            mx.pop();
        }
        else if (mn.size() > mx.size())
        {
            mx.push(mn.top());
            mn.pop();
        }
    }

    double findMedian()
    {
        return (mx.size() == mn.size()) ? ((mx.top() + mn.top()) / 2.0) : mx.top();
    }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */