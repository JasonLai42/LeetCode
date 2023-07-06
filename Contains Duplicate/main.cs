public class Solution {
    public bool ContainsDuplicate(int[] nums) {
        Dictionary<int, int> lookup = new Dictionary<int, int>();

        for(int i = 0; i < nums.Length; i++) {
            if(!lookup.ContainsKey(nums[i])) {
                lookup.Add(nums[i], nums[i]);
            }
            else {
                return true;
            }
        }

        return false;
    }
}