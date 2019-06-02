class TimeMap(object):

    def __init__(self):
        """
        Initialize your data structure here.
        """
        self.m = dict()
        

    def set(self, key, value, timestamp):
        """
        :type key: str
        :type value: str
        :type timestamp: int
        :rtype: None
        """
        image = Image(value, timestamp)
        if key not in self.m:
            self.m[key] = ImageStore(image)
        else:
            self.m[key].append(image)
        

    def get(self, key, timestamp):
        """
        :type key: str
        :type timestamp: int
        :rtype: str
        """
        if key not in self.m:
            return ""
        
        res = self.m[key].search(timestamp)
        if res is None:
            return ""
        
        return res.val
        
        
class Image(object):
    def __init__(self, val, ts):
        self.val = val
        self.ts = ts
        
    def __repr__(self):
        return "Image[val: %s, ts: %d]" % (self.val, self.ts)
        
class ImageStore(object):
    def __init__(self, initial_image):
        self.images = [initial_image]
        self.last_ts = initial_image.ts
        self.first_ts = initial_image.ts
        
    def append(self, image):
        if image.ts <= self.last_ts:
            raise Exception()
            
        self.images.append(image)
        self.last_ts = image.ts
        
    def search(self, ts):
        
        if len(self.images) == 0:
            return None
        
        if ts >= self.last_ts:
            return self.images[-1]
        
        if ts < self.first_ts:
            return None
        
        if ts == self.first_ts:
            return self.images[0]
        
        # binary search
        l, r = 0, len(self.images) - 1
        while l <= r:
            m = (l + r) / 2
            m_ts = self.images[m].ts
            
            if ts == m_ts:
                return self.images[m]
            
            if ts < m_ts:
                r = m - 1
            else:
                l = m + 1
    
        # didn't find an exact match; let's try
        # to get the value that's greatest but smaller 
        # than the given ts
        m_right = m + 1
        if m_right < len(self.images):
            m_right_image = self.images[m_right]
            if m_right_image.ts <= ts:
                return m_right_image

        m_image = self.images[m]
        if m_image.ts <= ts:
            return m_image
        
        m_left = m - 1
        if m_left >= 0:
            m_left_image = self.images[m_left]
            if m_left_image.ts <= ts:
                return m_left_image
            
        return None
        
    

        


# Your TimeMap object will be instantiated and called as such:
# obj = TimeMap()
# obj.set(key,value,timestamp)
# param_2 = obj.get(key,timestamp)