public class Solution {
    public boolean containsNearbyAlmostDuplicate(int[] nums, int k, int t) {
        if (k <= 0 || t < 0) return false;
        Map<Long, Long> map = new java.util.LinkedHashMap<>();
        int lastSavedIndex = 0;
        for (int i = 0; i < nums.length; i++) {
            long key = t == 0? (long) nums[i] - Integer.MIN_VALUE : ((long) nums[i] - Integer.MIN_VALUE) / t;
            if (
                map.containsKey(key) || 
                (map.containsKey(key - 1) && (Math.abs(map.get(key - 1) - nums[i]) <= t)) ||
                (map.containsKey(key + 1) && (Math.abs(map.get(key + 1) - nums[i]) <= t))
                ){
                return true;
            }
            if (map.size() == k) {
                long lastKey = t == 0? 
                (long) nums[lastSavedIndex] - Integer.MIN_VALUE : 
                ((long) nums[lastSavedIndex] - Integer.MIN_VALUE) / t;
                map.remove(lastKey);
                lastSavedIndex += 1;
            }
            map.put(key, (long) nums[i]);
        }
        return false;
    }
}