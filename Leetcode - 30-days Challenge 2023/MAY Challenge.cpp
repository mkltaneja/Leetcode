// DAY 1 (1491. Average Salary Excluding the Minimum and Maximum Salary)===================================================================

double average(vector<int>& salary) 
{
    int minSalary = INT_MAX, maxSalary = INT_MIN, sumSalary = 0;
    for(int x : salary)
    {
        minSalary = min(minSalary, x);
        maxSalary = max(maxSalary, x);
        sumSalary += x;
    }
    sumSalary -= (minSalary + maxSalary);

    return 1.0*sumSalary / (salary.size()-2);
}
