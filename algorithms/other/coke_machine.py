# Given a coke machine with a series of buttons. If you press a button it will get you a certain range of coke. 
# Find out if it's possible to get the target range of coke. You can press buttons any number of times.
# 
# Example 1:
# 
# Input: buttons = [[100, 120], [200, 240], [400, 410]], target = [100, 110]
# Output: false
# Explanation: if we press first button it might give us 120 volume of coke, not in the target range.
# Example 2:
# 
# Input: buttons = [[100, 120], [200, 240], [400, 410]], target = [90, 120]
# Output: true
# Explanation: press first button and you will always get amount of coke in the target range.
# Example 3:
# 
# Input: buttons = [[100, 120], [200, 240], [400, 410]], target = [300, 360]
# Output: true
# Explanation: press first and second button and you will always get amount of coke in the target range.
# Example 4:
# 
# Input: buttons = [[100, 120], [200, 240], [400, 410]], target = [310, 360]
# Output: false
# Explanation: we can press 1st button 3 times or 1st and 2nd button but it's possible to get only 300, not in the target range.
# Example 5:
# 
# Input: buttons = [[100, 120], [200, 240], [400, 410]], target = [1, 9999999999]
# Output: true
# Explanation: you can press any button.

def get_key(left, right):
		return "%d~%d" % (left, right)

def divide_and_conquer_solution(buttons, target_range, m, matrix):
	if target_range[0] <= 0 and target_range[0] <= target_range[1]:
		return True

	if target_range[0] > target_range[1]:
		return False

	if target_range[1] < 0:
		return False

	if target_range[0] > 0 and m <= 0:
		return False

	# exclude last button case
	key1 = get_key(target_range[0], target_range[1])
	cell1 = matrix[m - 1].get(key1, None)
	if cell1 is None:
		cell1 = divide_and_conquer_solution(buttons, target_range, m - 1, matrix)
		matrix[m - 1][key1] = cell1

	# include last button case
	range1 = [target_range[0] - button[0], target_range[1] - button[1]]
	key2 = get_key()
	cell2 = matrix[m].get(key2, None)
	if cell2 is None:
		cell2 = divide_and_conquer_solution(buttons, range1, m, matrix)
		matrix[m][key2] = cell2

	return cell1.doable or cell2.doable

def driver(buttons, target_range):
	matrix = [dict() for i in xrange(len(buttons) + 1)]
	return divide_and_conquer_solution(buttons, target_range, len(buttons), matrix)
