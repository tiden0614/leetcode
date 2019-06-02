# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

import collections 

class Solution(object):
    def verticalTraversal(self, root):
        """
        :type root: TreeNode
        :rtype: List[List[int]]
        """
        
        queue = collections.deque([CNode(root, 0, 0)])
        m = dict()
        min_x, max_x, min_y = 0, 0, 0
        while len(queue) > 0:
            head = queue.popleft()
            
            if head.x not in m:
                m[head.x] = dict()
                
            if head.y not in m[head.x]:
                m[head.x][head.y] = []
                
            m[head.x][head.y].append(head)
            
            if head.x < min_x:
                min_x = head.x
                
            if head.x > max_x:
                max_x = head.x
                
            if head.y < min_y:
                min_y = head.y
            
            if head.node.left is not None:
                queue.append(CNode(head.node.left, head.x - 1, head.y - 1))
                
            if head.node.right is not None:
                queue.append(CNode(head.node.right, head.x + 1, head.y - 1))
        
        ret = []
        for x in xrange(min_x, max_x + 1):
            if x in m:
                report = []
                
                for y in xrange(0, min_y - 1, -1):
                    if y in m[x]:
                        vals = map(lambda cnode: cnode.node.val, m[x][y])
                        if len(vals) > 1:
                            vals.sort()
                        
                        report.extend(vals)
                
                ret.append(report)
                
        return ret
        
    
class CNode(object):
    def __init__(self, node, x, y):
        self.node = node
        self.x = x
        self.y = y
        