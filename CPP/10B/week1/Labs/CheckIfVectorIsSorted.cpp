#include <iostream>
#include <vector>
using namespace std;


bool inOrder(const vector<int> &nums);

int main() {

	vector<int> nums1(5);
	nums1.at(0) = 5;
	nums1.at(1) = 6;
	nums1.at(2) = 7;
	nums1.at(3) = 8;
	nums1.at(4) = 3;


	if (inOrder(nums1)) {
		cout << "First vector is in order" << endl;
	}
	else {
		cout << "First vector is not in order" << endl;
	}

	vector<int> nums2(5);

   // Fill second vector with 5 integers entered by the user
   size_t value = 0;
   for(size_t i = 0; i < 5; ++i){
       cin >> value;
       nums2.at(i) = value;
   }

	if (inOrder(nums2)) {
		cout << "Second vector is in order" << endl;
	}
	else {
		cout << "Second vector is not in order" << endl;
	}

   // Output whether second vector is in order or not in order


	return 0;
}

bool inOrder(const vector<int> &nums){
    size_t count = 0;
    int current = nums.at(0);
    for(size_t i = 0; i < nums.size();++i){
        if(nums.at(i) > current){
            ++count;
         } else if (nums.at(i) == current){
            ++count;
        }
        current = nums.at(i);
    }
//    cout << nums.size() << ' ' << count << endl;

    if (count == nums.size()){
        return true;
    } else{
        return false;
    }
}

// Define your inOrder function here


