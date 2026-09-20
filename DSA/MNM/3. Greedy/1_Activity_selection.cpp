#include <iostream>
#include <vector>
using namespace std;

// maximum number of non-overlapping activities
//  if sorted then O(n) else O(nlog(n))
//  DP O(n^3)

// Activity Selection (activities are already sorted by finish time)
void activitySelection(vector<int> &s, vector<int> &f)
{
   int n = s.size();

   // pick the first activity
   cout << "Selected activities: 0 ";
   int k = 0; // index of last selected activity

   // check remaining activities
   for (int m = 1; m < n; m++)
   {
      // if current activity starts after or when last selected one finishes
      if (s[m] >= f[k])
      {
         cout << m << " ";
         k = m; // update last selected activity
      }
   }
}

int main()
{
   // start times and finish times
   // already sorted by finish time
   vector<int> s = {1, 3, 0, 5, 3, 5, 6, 8, 8, 2, 12};
   vector<int> f = {4, 5, 6, 7, 9, 9, 10, 11, 12, 14, 16};

   activitySelection(s, f);

   return 0;
}

/*
Key Notes:

1. Each activity has:
   s[i] → start time
   f[i] → finish time

2. Goal:
   Select maximum number of non-overlapping activities.

3. Compatibility condition:
   s[j] ≥ f[i]

4. Greedy idea:
   Always choose activity with earliest finish time.

5. Assumption:
   Activities are sorted by finish time:
   f1 ≤ f2 ≤ ... ≤ fn

6. After selecting activity k:
   Only consider activities with s[i] ≥ f[k]

7. Time Complexity:
   O(n) (if already sorted)
   O(n log n) (if sorting required)

8. Why greedy works:
   Choosing earliest finish leaves maximum room for future activities.
*/