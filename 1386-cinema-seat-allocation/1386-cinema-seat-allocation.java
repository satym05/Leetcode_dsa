import java.util.*;

class Solution {
    public int maxNumberOfFamilies(int n, int[][] reservedSeats) {
        // Store reserved seats for each affected row
        Map<Integer, Integer> reserved = new HashMap<>();

        for (int[] seat : reservedSeats) {
            int row = seat[0];
            int seatNum = seat[1];

            // Only seats 2 to 9 affect family placement
            if (seatNum >= 2 && seatNum <= 9) {
                int mask = reserved.getOrDefault(row, 0);
                mask |= (1 << (seatNum - 2));
                reserved.put(row, mask);
            }
        }

        // Every completely unreserved row can fit 2 families
        int ans = (n - reserved.size()) * 2;

        // Bit masks for possible family blocks
        int left = 0b00001111;    // seats 2,3,4,5
        int middle = 0b00111100;  // seats 4,5,6,7
        int right = 0b11110000;   // seats 6,7,8,9

        for (int mask : reserved.values()) {

            // Can place two families: left + right
            if ((mask & left) == 0 && (mask & right) == 0) {
                ans += 2;
            }
            // Otherwise, check if one family can fit
            else if ((mask & left) == 0 ||
                     (mask & middle) == 0 ||
                     (mask & right) == 0) {
                ans += 1;
            }
        }

        return ans;
    }
}