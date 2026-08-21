class Solution {
    public long findKthSmallest(int[] coins, int k) {
        int n = coins.length;

        // Remove redundant coins.
        // If a smaller coin divides a larger coin,
        // every multiple of the larger coin is already covered.
        Arrays.sort(coins);

        List<Integer> list = new ArrayList<>();

        for (int coin : coins) {
            boolean redundant = false;

            for (int prev : list) {
                if (coin % prev == 0) {
                    redundant = true;
                    break;
                }
            }

            if (!redundant) {
                list.add(coin);
            }
        }

        int m = list.size();
        int[] a = new int[m];

        for (int i = 0; i < m; i++) {
            a[i] = list.get(i);
        }

        long left = 1;
        long right = (long) a[0] * k;

        while (left < right) {
            long mid = left + (right - left) / 2;

            if (count(mid, a) >= k) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }

        return left;
    }

    private long count(long x, int[] coins) {
        int n = coins.length;
        long total = 0;

        // Inclusion-Exclusion over all non-empty subsets
        for (int mask = 1; mask < (1 << n); mask++) {
            long lcm = 1;
            int bits = 0;
            boolean valid = true;

            for (int i = 0; i < n; i++) {
                if ((mask & (1 << i)) != 0) {
                    bits++;

                    lcm = lcm(lcm, coins[i]);

                    // If LCM > x, this subset contributes nothing
                    if (lcm > x) {
                        valid = false;
                        break;
                    }
                }
            }

            if (!valid) continue;

            long multiples = x / lcm;

            if (bits % 2 == 1) {
                total += multiples;
            } else {
                total -= multiples;
            }
        }

        return total;
    }

    private long gcd(long a, long b) {
        while (b != 0) {
            long temp = a % b;
            a = b;
            b = temp;
        }
        return a;
    }

    private long lcm(long a, long b) {
        return a / gcd(a, b) * b;
    }
}