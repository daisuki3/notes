'''
朴素思路O(N^2)暴力循环
分治？
归并排序，左右两区都排好序，处理左区元素L时，右区的下标ri - rstart就是该左区元素L贡献的逆序对个数。
'''

class Solution:
    def reversePairs(self, nums: List[int]) -> int:
        def merge(start, end):
            if end == start:
                return 0
            mid = start + (end - start) // 2
            
            lreverse = merge(start, mid)
            rreverse = merge(mid + 1, end)
            ans = 0

            tmp = [0] * (end - start + 1)
            
            left = start
            right = mid + 1
            i = 0

            while left <= mid and right <= end:
                if nums[left] <= nums[right]:
                    tmp[i] = nums[left]
                    left += 1
                    ans += right - (mid + 1)
                elif nums[left] > nums[right]:
                    tmp[i] = nums[right]        
                    right += 1

                i += 1
            
            while left <= mid:
                tmp[i] = nums[left]
                left += 1
                ans += right - (mid + 1)
                i += 1
            while right <= end:
                tmp[i] = nums[right]
                right += 1
                i += 1
            
            for j in range(start, end + 1):
                nums[j] = tmp[j - start]

            return lreverse + rreverse + ans
        
        if len(nums) == 0:
            return 0
            
        return merge(0, len(nums) - 1)

    