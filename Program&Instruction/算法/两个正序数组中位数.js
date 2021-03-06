/**
 * nums1 和 nums2 为正序数组，找出这组数据的中位数
 * @param {number[]} nums1
 * @param {number[]} nums2
 * @return {number}
 * 
 * 普通的思路是O(m + n)  全部读一遍然后取中位数
 * 时间复杂度更好的方法：每次分别取到两个数组的中间
 * 比较大小，然后舍弃小的那一端左边的数据
 * 可以达到二分的时间复杂度
 * 
 * 时间复杂度？
 */
var findMedianSortedArrays = function(nums1, nums2) {
    let m = nums1.length
    let n = nums2.length
    
   
    //获取两个数组中第k大的数字
    function getK(k, index1, index2){


        if(index1 >= m){
            return nums2[index2 + k - 1]
        }
        else if(index2 >= n){
            return nums1[index1 + k - 1]
        }
        else if(k == 1){
            return Math.min(nums1[index1], nums2[index2])
        }
        else{
            let newi1 = Math.min(Math.floor(k / 2) - 1 + index1, m - 1)
            let newi2 = Math.min(Math.floor(k / 2) - 1 + index2, n - 1)
            
            let drop
            if(nums1[newi1] <= nums2[newi2]){
                drop = newi1 - index1 +1
                index1 = newi1 + 1
            }
            else if(nums1[newi1] > nums2[newi2]){
                drop = newi2 - index2 + 1
                index2 = newi2 + 1
            }

            return getK(k - drop, index1, index2)
        }

    }

    return (getK(Math.ceil((m + n) / 2), 0, 0) + getK(Math.ceil((m + n + 1) / 2), 0, 0)) / 2
};