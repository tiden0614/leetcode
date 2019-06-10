# Question
#
# Given 2 strings a and b with the same length. Strings are alligned one under the other. 
# We can choose an index and split both strings into 4 subtrings: a1 + a2 # and b1 + b2. Find out if it's possible to split a and b such that 
# a1 + b2 or a2 + b1 forms a palindrome.
# 
# Example 1:
# 
# Input: a = "abcbbbb", b = "xxxbcba"
# Output: true
# Explanation: 
# 
# abc|bbbb
# xxx|bcba
# 
# We can split the strings at index 3. We will get a1 = "abc", a2 = "bbbb" and b1 = "xxx", b2 = "bcba"
# a1 + b2 forms a palidnrome "abcbcba" so return true.
# Follow-up:
# Now it's allowed to split the strings independently:
# 
# a|bcbbbb
# xxxbcb|a
# So in the exampe above a can be splitted into a1 = "a" a2 = "bcbbbb" and b can be splitted b1 = "xxxbcb" b2 = "a". 
# As a result a1+ b2 forms a palindrome "aa". Find the longest palindrome.
#

def base_solution(a, b):
	return find_palindrome_index(a, b) || find_palindrome_index(b, a)

def find_palindrome_index(a, b):
	n = len(a)
	switched = False
	i, j = 0, n - 1
	while i < j:
		if not switched:
			if a[i] != b[j]:
				switched = True
				# don't modify the index and come back to the
				# switched branch in the next interation; we
				# will check b[i] and b[j] there
				continue
		else:
			if b[i] != b[j]:
				return False
		i += 1
		j -= 1

	return True

# I guess the candidate remember the follow up wrong?
def follow_up(a, b):
	return a[0] == b[-1]
