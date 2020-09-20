
bool isTransformable(string s, string t) 
{
    int n = s.size(), m = t.size();
    if(n != m)
        return false;
    vector<char> a(n), b(m);
    for(int i=0; i<n; i++)
        a[i] = s[i];
    for(int i=0; i<m; i++)
        b[i] = t[i];
    
    for(char ch = '9'; ch >= '0'; ch--)
    {
        vector<int> aloc, bloc;
        for(int i=0; i<a.size(); i++)
            if(a[i] == ch)
                aloc.push_back(i);
        for(int i=0; i<b.size(); i++)
            if(b[i] == ch)
                bloc.push_back(i);

        if(aloc.size() != bloc.size())
            return false;
        for(int i=0; i<aloc.size(); i++)
            if(bloc[i] < aloc[i])
                return false;
        
        vector<char> na, nb;
        for(char c : a)
            if(c < ch)
                na.push_back(c);
        for(char c : b)
            if(c < ch)
                nb.push_back(c);
        a.swap(na);
        b.swap(nb);
    }
    return true;
}