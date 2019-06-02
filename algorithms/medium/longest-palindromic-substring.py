class Solution(object):
    def longestPalindrome(self, s):
        """
        :type s: str
        :rtype: str
        """
        if len(s) == 1:
            return s[0]
        
        n = 2 * len(s) + 1
        s1 = ['#' if i % 2 == 0 else s[i / 2] for i in xrange(0, n)]
        d = [1] * n
        l, r = 0, -1
        max_k, max_c = 0, 0
        
        for i in xrange(0, n):
            if i > r:
                k = 1
            else:
                mirror = l + r - i
                d_mirror = d[mirror]
                k = min(d[mirror], r - i + 1)
                
            # naive way to find distance for center i
            while 0 <= i - k and i + k < n and s1[i - k] == s1[i + k]:
                k += 1
            
            # decrease k because the last iteration went beyond
            # the boundary or the left and right elements are not 
            # symmetrical
            k -= 1
            
            d[i] = k
            if k > max_k:
                max_k = k
                max_c = i
            
            if i + k > r:
                r = i + k
                l = i - k
            
        lb, rb = (max_c - max_k) / 2, (max_c + max_k + 1) / 2
        return s[lb : rb]
            
    