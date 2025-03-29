#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>


using namespace std;

int minSwapsToColorful(int n, int k, vector<int>& a) {
    // Map to store the last occurrence of each element
    unordered_map<int, int> lastOccurrence;
    for (int i = 0; i < n; ++i) {
        lastOccurrence[a[i]] = i;
    }

    // Find the smallest window that contains all elements from 1 to k
    int left = 0, right = 0;
    int minWindowSize = n + 1;
    int count = 0;
    unordered_map<int, int> windowCount;

    while (right < n) {
        // Expand the window
        if (a[right] >= 1 && a[right] <= k) {
            windowCount[a[right]]++;
            if (windowCount[a[right]] == 1) {
                count++;
            }
        }

        // Contract the window when all elements are found
        while (count == k) {
            minWindowSize = min(minWindowSize, right - left + 1);

            // Move the left pointer
            if (a[left] >= 1 && a[left] <= k) {
                windowCount[a[left]]--;
                if (windowCount[a[left]] == 0) {
                    count--;
                }
            }
            left++;
        }

        right++;
    }

    // If no valid window is found, return 0 (already colorful)
    if (minWindowSize == n + 1) {
        return 0;
    }

    // Calculate the number of swaps required
    // The number of swaps is the number of elements outside the window
    return minWindowSize - k;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int n, k;
        cin >> n >> k;

        vector<int> a(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }

        // Compute the minimum number of swaps
        int result = minSwapsToColorful(n, k, a);

        // Output the result
        cout << result << "\n";
    }

    return 0;
}