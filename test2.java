
string mx = a[0];
for(int i = 1; i < n; i++)
{
    int j = 0;
    while(j < mx.size() && j < a[i].size() && mx[j] == a[j])
        j++;
    mx = a.substr(0,j);
}

return mx.size();
