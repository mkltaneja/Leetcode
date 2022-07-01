//  DAY 1 (1710. Maximum Units on a Truck)========================================================================================================

  int maximumUnits(vector<vector<int>>& boxTypes, int truckSize) 
  {
      sort(boxTypes.begin(), boxTypes.end(), [](auto const &a, auto const &b){
          return a[1] > b[1];
      });
      int ans = 0;
      for(vector<int> v : boxTypes)
      {
          ans += min(truckSize, v[0]) * v[1];
          truckSize -= min(truckSize, v[0]);
      }
      return ans;
  }
