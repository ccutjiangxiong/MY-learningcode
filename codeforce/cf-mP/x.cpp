
#include <algorithm>
#include <iterator>
#include <set>
#include <vector>

using namespace std;

class Solution {
   public:
    long long goodTriplets(vector<int>& nums1, vector<int>& nums2) {
        multiset<int> s1, s2;
        int n = nums1.size();
        vector<int> a(n);
        for (int i = 0; i<n; i++) {
            a[i] = distance(s1.upper_bound(min(nums1[i], nums2[i])), s1.begin());
            s1.insert(max(nums1[i], nums2[i]));
        }
        int ans = 0;
        for (int i = n-1; i >= 0; i--) {
            ans += distance(s2.end(), s2.lower_bound(max(nums1[i], nums2[i]))) * a[i];
            s2.insert(min(nums1[i], nums2[i]));
        }
        return ans;
    }
};