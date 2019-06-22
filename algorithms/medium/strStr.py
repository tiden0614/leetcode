class Solution:
    """
    @param source:
    @param target:
    @return: return the index
    """
    def strStr(self, source, target):
        m = len(target)
        if m == 0:
            return 0

        n = len(source)
        if n == 0:
            return -1

        if n < m:
            return -1

        if n == m:
            if source == target:
                return 0
            else:
                return -1

        h0 = RollingHash()
        for c in target:
            h0.append(c)

        target_hash = h0.hash

        h = RollingHash()
        for c in source[:m]:
            h.append(c)


        if h.hash == target_hash:
            if self.sub_str_equal(source, 0, target):
                return 0

        for i in xrange(m, n):
            c = source[i]
            h.popleft()
            prev_h = h.hash
            h.append(c)
            if h.hash == target_hash:
                if self.sub_str_equal(source, i - m + 1, target):
                    return i - m + 1

        return -1

    def sub_str_equal(self, source, start, target):
        n = len(target)

        if start + n > len(source):
            return False

        for i in xrange(n):
            if source[start + i] != target[i]:
                return False

        return True


class RollingHash:
    def __init__(self):
        self.hash = int(0)
        self.base = 256
        self.prime = 257
        self.first = LinkedListNode(None, None, None)
        self.last = self.first
        self.n = 0

    def append(self, c):
        num = ord(c)
        self.hash = ((self.hash * self.base) % self.prime + num) % self.prime
        node = LinkedListNode(self.last, None, num)
        self.last.next = node
        self.last = node
        self.n += 1

    def popleft(self):
        if self.n <= 0:
            raise Exception()

        # pop a node from left
        left_node = self.first.next
        left_node_next = left_node.next
        self.first.next = left_node_next
        if left_node_next:
            left_node_next.prev = self.first
        if self.last == left_node:
            self.last = self.first

        num = left_node.val
        left_most_base = (int(pow(self.base, self.n - 1)) * num) % self.prime
        self.hash = (self.hash + self.prime - left_most_base) % self.prime
        self.n -= 1


class LinkedListNode:
    def __init__(self, prev, next, val):
        self.next = None
        self.prev = None
        self.val = val
