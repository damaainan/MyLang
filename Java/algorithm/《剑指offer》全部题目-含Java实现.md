## 《剑指offer》全部题目-含Java实现

来源：[http://www.cnblogs.com/guoyaohua/p/8955372.html](http://www.cnblogs.com/guoyaohua/p/8955372.html)

时间 2018-04-26 22:24:00

 
陆续刷了好久，算是刷完了《剑指offer》，以下全部AC代码，不一定性能最优，如有错误或更好解答，请留言区指出，大家共同交流，谢谢~
 
### 1.二维数组中的查找
 
在一个二维数组中，每一行都按照从左到右递增的顺序排序，每一列都按照从上到下递增的顺序排序。请完成一个函数，输入这样的一个二维数组和一个整数，判断数组中是否含有该整数。
 
```java
public class Solution {
    public boolean Find(int target, int [][] array) {
        if(array == null||array.length==0) return false;
        int rowIdx = 0,colIdx = array[0].length-1;
        while(rowIdx<array.length&&colIdx>=0){
            if(array[rowIdx][colIdx] == target)
                return true;
            else if(target>array[rowIdx][colIdx])
                rowIdx++;
            else if(target<array[rowIdx][colIdx])
                colIdx--;
        }
        return false;
    }
}
```
 
### 2.替换空格
 
请实现一个函数，将一个字符串中的空格替换成“%20”。例如，当字符串为We Are Happy.则经过替换之后的字符串为We%20Are%20Happy。
 
```java
public class Solution {
    public String replaceSpace(StringBuffer str) {
        StringBuilder sb = new StringBuilder();
        for(int i = 0;i<str.length();i++){
            if(str.charAt(i)==' '){
                sb.append("%20");
            }
            else
                sb.append(str.charAt(i));
        }
        return sb.toString();
    }
}
```
 
### 3.从尾到头打印链表
 
输入一个链表，从尾到头打印链表每个节点的值。
 
```java
/**
*    public class ListNode {
*        int val;
*        ListNode next = null;
*
*        ListNode(int val) {
*            this.val = val;
*        }
*    }
*
*/
import java.util.ArrayList;
import java.util.Stack;
public class Solution {
    public ArrayList<Integer> printListFromTailToHead(ListNode listNode) {
        ArrayList<Integer> result = new ArrayList<>();
        Stack<Integer> stack = new Stack<>();
        if(listNode == null) return result;
        while(listNode != null){
            stack.push(listNode.val);
            listNode = listNode.next;
        }
        while(!stack.isEmpty())
            result.add(stack.pop());
        return result;
    }
}
```
 
### ==4.重建二叉树==
 
#### 使用递归
 
输入某二叉树的前序遍历和中序遍历的结果，请重建出该二叉树。假设输入的前序遍历和中序遍历的结果中都不含重复的数字。例如输入前序遍历序列{1,2,4,7,3,5,6,8}和中序遍历序列{4,7,2,1,5,3,8,6}，则重建二叉树并返回。
 
```java
/**
 * Definition for binary tree
 * public class TreeNode {
 *     int val;
 *     TreeNode left;
 *     TreeNode right;
 *     TreeNode(int x) { val = x; }
 * }
 */
public class Solution {
    public TreeNode reConstructBinaryTree(int[] pre, int[] in) {
        if (pre == null || in == null || pre.length != in.length) return null;
        return reConstructBinaryTreeCore(pre, 0, pre.length - 1, in, 0, in.length - 1);
    }

    public TreeNode reConstructBinaryTreeCore(int[] pre, int preStartIdx, int preEndIdx, int[] in, int inStartIdx, int inEndIdx) {
        TreeNode node = new TreeNode(pre[preStartIdx]);
        if (preStartIdx == preEndIdx)
            if (inStartIdx != inEndIdx || pre[preStartIdx] != in[inStartIdx])
                System.out.println("Invalid input.");
        int i = 0;
        while (pre[preStartIdx] != in[inStartIdx + i])
            i++;
        if (i == 0)//证明没有左子树
            node.left = null;
        else
            node.left = reConstructBinaryTreeCore(pre, preStartIdx + 1, preStartIdx + i, in, inStartIdx, inStartIdx + i - 1);
        if (inStartIdx + i == inEndIdx)//证明没有右子树
            node.right = null;
        else
            node.right = reConstructBinaryTreeCore(pre, preStartIdx + i + 1, preEndIdx, in, inStartIdx + i + 1, inEndIdx);
        return node;

    }
}
```
 
### 5.用两个栈实现队列
 
用两个栈来实现一个队列，完成队列的Push和Pop操作。 队列中的元素为int类型。
 
```java
import java.util.Stack;

public class Solution {
 Stack<Integer> stack1 = new Stack<Integer>();
    Stack<Integer> stack2 = new Stack<Integer>();

    public void push(int node) {
        stack1.push(node);
    }

    public int pop() throws Exception {
        if(stack1.isEmpty()&&stack2.isEmpty())
            throw new Exception("Queue is empty.");
        if(!stack2.isEmpty())
            return stack2.pop();
        while(!stack1.isEmpty())
            stack2.push(stack1.pop());
        return stack2.pop();
    }
}
```
 
### ==6.旋转数组的最小数字==
 
把一个数组最开始的若干个元素搬到数组的末尾，我们称之为数组的旋转。 输入一个非递减排序的数组的一个旋转，输出旋转数组的最小元素。 例如数组{3,4,5,1,2}为{1,2,3,4,5}的一个旋转，该数组的最小值为1。 NOTE：给出的所有元素都大于0，若数组大小为0，请返回0。
 
```java
public class Solution {
    public int minNumberInRotateArray(int [] array) {
        if(array == null||array.length == 0)return 0;
        int idx1 = 0,idx2 = array.length-1;
        //如果不能进入while循环，则证明第一个元素小于最后一个元素，而且数组为非递减排序，最小值即为首位。
        while(array[idx1]>=array[idx2]){
            //第一个指针指向前半段递增序列的末尾，第二个指针指向后半段递增序列的首位。
            if(idx2-idx1==1)return array[idx2];
            //二分法查找临界点
            int mid = (idx1+idx2)/2;
            //考虑特例：｛1,0,1,1,1｝
            if(array[idx1] == array[idx2]&& array[mid] == array[idx1]){
                for(int i = idx1;i<=idx2;i++)
                    if(array[i]<array[mid])
                        return array[i];
            //特例：｛1,1,1,1,1,1,1｝
            return array[mid];
            }
            //更新指针，直至idx2-idx1==1;
            if(array[mid]>=array[idx1])
                idx1 = mid;
            else if(array[mid]<=array[idx2])
                idx2 = mid;
        }
        //此时数组为递增排列，第一个元素最小
        return array[0];
    }
}
```
 
### 7.斐波那契数列
 
大家都知道斐波那契数列，现在要求输入一个整数n，请你输出斐波那契数列的第n项。
 
n<=39
 
```java
public class Solution {
    public int Fibonacci(int n) {
         if(n<1) return 0;
        int[] fibonacci = new int[2];
        fibonacci[0] = 1;
        fibonacci[1] = 1;
        n-=2;
        while(n>0){
            int temp = fibonacci[0]+fibonacci[1];
            fibonacci[0] = fibonacci[1];
            fibonacci[1] = temp;
            n--;
        }
        return fibonacci[1];
    }
}
```
 
### 8.跳台阶（动态规划）
 
一只青蛙一次可以跳上1级台阶，也可以跳上2级。求该青蛙跳上一个n级的台阶总共有多少种跳法。
 
```java
public class Solution {
    public int JumpFloor(int target) {
        if(target < 1) return 0;
        int[] DP = new int[3];
        DP[0] = 1;
        DP[1] = 2;
        DP[2] = DP[0]+DP[1];
        if(target<=3)
            return DP[target-1];
        for(int i =4;i<=target;i++){
            DP[0] = DP[1];
            DP[1] = DP[2];
            DP[2] = DP[0]+DP[1];
        }
        return DP[2];
    }
}
```
 
### 9.矩形覆盖
 
我们可以用2 1的小矩形横着或者竖着去覆盖更大的矩形。请问用n个2  1的小矩形无重叠地覆盖一个2*n的大矩形，总共有多少种方法？
 
```java
public class Solution {
    public int RectCover(int target) {
        if(target<1) return 0;
        int[] DP = new int[3];
        DP[0] = 1;
        DP[1] = 2;
        DP[2] = DP[1]+DP[0];
        if(target<4)
            return DP[target-1];
        for(int i = 4;i<=target;i++){
            int temp = DP[1]+DP[2];
            DP[0] = DP[1];
            DP[1] = DP[2];
            DP[2] = temp;
        }
        return DP[2];
    }
}
```
 
### 10.二进制中1的个数
 
输入一个整数，输出该数二进制表示中1的个数。其中负数用补码表示。
 
```java
public class Solution {
    public int NumberOf1(int n) {
        int count = 0;
        while(n!=0){
            count+=n&1;
            n=n>>>1;
        }
        return count;
    }
}
```
 
### 11.数值的整数次方
 
给定一个double类型的浮点数base和int类型的整数exponent。求base的exponent次方。
 
```java
public class Solution {
    public double Power(double base, int exponent) {
        if(base == 0 && exponent < 0)//输入不合法
            return 0.0;
        if(exponent < 0)
            return 1/PowerWithPositive(base,-1*exponent);
        else
            return PowerWithPositive(base,exponent);
  }
    public double PowerWithPositive(double base,int exponent){
        if(exponent == 0)
            return 1;
        if(exponent == 1)
            return base;
        double result = PowerWithPositive(base,exponent >> 1);
        result *= result;
        if((exponent & 1) == 1)
            result *= base;
        return result;
    }
}
```
 
### 12.调整数组顺序使奇数位于偶数前面
 
输入一个整数数组，实现一个函数来调整该数组中数字的顺序，使得所有的奇数位于数组的前半部分，所有的偶数位于位于数组的后半部分，并保证奇数和奇数，偶数和偶数之间的相对位置不变。
 
```java
import java.util.Stack;
public class Solution {
    public void reOrderArray(int [] array) {
        if(array == null||array.length == 0) return;
        Stack<Integer> odd = new Stack<>();
        Stack<Integer> even = new Stack<>();
        for(int i = 0;i<array.length;i++){
            if((array[i]&1) == 1)
                odd.push(array[i]);
            else
                even.push(array[i]);
        }
        int index = array.length-1;
        while(!even.isEmpty())
            array[index--] = even.pop();
        while(!odd.isEmpty())
            array[index--] = odd.pop();
    }
}
```
 
### 13.链表中倒数第K个结点
 
输入一个链表，输出该链表中倒数第k个结点。 **`（能用指针尽量不要使用辅助栈）`** 
 
#### 方法一：使用指针
 
```java
/*
public class ListNode {
    int val;
    ListNode next = null;
 
    ListNode(int val) {
        this.val = val;
    }
}*/
import java.util.Stack;
public class Solution {
    public ListNode FindKthToTail(ListNode head,int k) {
        if(head == null || k<=0)
            return null;
        ListNode node1 = head,node2 = head;
        for(int i=1;i<k;i++){
            if(node1==null)
                return null;
            node1 = node1.next;
        }
        if(node1 == null)
            return null;
        while(node1.next!=null){
            node1 = node1.next;
            node2 = node2.next;
        }
        return node2;
    }
         
}
```
 
#### 方法二：使用辅助栈
 
```java
/*
public class ListNode {
    int val;
    ListNode next = null;
 
    ListNode(int val) {
        this.val = val;
    }
}*/
import java.util.Stack;
public class Solution {
    public ListNode FindKthToTail(ListNode head,int k) {
        Stack<ListNode> stack = new Stack<>();
        ListNode node = head;
        while(node!=null){
            stack.push(node);
            node = node.next;
        }
        for(int i =0;i<k;i++){
            if(stack.empty())
                return null;
            node = stack.pop();
        }
        return node;
    }
}
```
 
### 14.反转链表
 
输入一个链表，反转链表后，输出链表的所有元素。
 
```java
/*
public class ListNode {
    int val;
    ListNode next = null;

    ListNode(int val) {
        this.val = val;
    }
}*/
public class Solution {
    public ListNode ReverseList(ListNode head) {
        if(head == null) return null;
        ListNode node1 = null,node2 = head,node3 = head.next;
        while(node3!=null){
            node2.next = node1;
            node1 = node2;
            node2 = node3;
            node3 = node3.next;
        }
        node2.next = node1;
        return node2;
    }
}
```
 
### 15.反转链表
 
输入一个链表，反转链表后，输出链表的所有元素。
 
#### 解法一：（使用栈）
 
```java
/*
public class ListNode {
    int val;
    ListNode next = null;

    ListNode(int val) {
        this.val = val;
    }
}*/
import java.util.Stack;
public class Solution {
    public ListNode ReverseList(ListNode head) {
        Stack<ListNode> stack = new Stack<>();
        if(head == null) return null;
        while(head != null){
            stack.push(head);
            head = head.next;
        }
        
        head = stack.pop();
        ListNode temp = head;
        while(!stack.empty()){
            temp.next = stack.pop();
            temp = temp.next;
        }
        temp.next = null;//一定要注意这里的这行代码
        //一定要将链表末位next置为null
        return head;
    }
}
```
 
#### 解法二：
 
```java
public class Solution{
    public ListNode ReverseList(ListNode head){
        ListNode reversedListHead;
        ListNode pre = null;
        ListNode node = null;
        ListNode next = null;
        if(head == null) return null;
        node = head;
        while(true){
            next = node.next;
            node.next = pre;
            pre = node;
            if(next == null){
                reversedListHead = node;
                break;
            }   
            node = next;
        }
        return reversedListHead;
    }
}
```
 
### 16.合并两个排序的链表
 
输入两个单调递增的链表，输出两个链表合成后的链表，当然我们需要合成后的链表满足单调不减规则。
 
#### 解法一：
 
```java
public class Solution {
    public ListNode Merge(ListNode list1,ListNode list2) {
        //if(list1 == null && list2 == null) return null;
        //这行代码可以不要，因为当list1 == null  return list2也等于null
        if(list1 == null) return list2;
        if(list2 == null) return list1;
        ListNode head,node;
        if(list1.val <= list2.val){
            node = list1;
            head = node;
            list1 = list1.next;
        }else{
            node = list2;
            head = node;
            list2 = list2.next;
        }
        while(list1 != null&&list2 != null){
            if(list1.val<=list2.val){
                node.next = list1;
                list1 = list1.next;
                node = node.next;
            }else{
                node.next = list2;
                list2 = list2.next;
                node = node.next;
            }
        }
        while(list1 != null){
            node.next = list1;
            list1 = list1.next;
            node = node.next;
        }
        while(list2 != null){
            node.next = list2;
            list2 = list2.next;
            node = node.next;
        }
        return head;
    }
}
```
 
#### 解法二：（使用递归）
 
```java
public class Solution {
    public ListNode Merge(ListNode list1,ListNode list2) {
        if(list1 == null) return list2;
        if(list2 == null) return list1;
        ListNode MergedHead = null;
        if(list1.val <= list2.val){
            MergedHead = list1;
            MergedHead.next = Merge(list1.next,list2);
        }else{
            MergedHead = list2;
            MergedHead.next = Merge(list1,list2.next);
        }
        return MergedHead;
    }
}
```
 
### 17.树的子结构
 
输入两棵二叉树A，B，判断B是不是A的子结构。（ps：我们约定空树不是任意一个树的子结构）
 
```java
/**
public class TreeNode {
    int val = 0;
    TreeNode left = null;
    TreeNode right = null;

    public TreeNode(int val) {
        this.val = val;

    }

}
*/
public class Solution {
    public boolean HasSubtree(TreeNode root1,TreeNode root2) {
        if(root1==null||root2==null) return false;
        boolean result = false;
        if(root1.val == root2.val){
            result = isEqualTree(root1,root2);
        }
        if(!result)
            result = HasSubtree(root1.left,root2);
        if(!result)
            result = HasSubtree(root1.right,root2);
        return result;
    }
    public boolean isEqualTree(TreeNode tree1,TreeNode tree2){
        //注意此处，只需判断tree2 == null即可返回true；
        //因为tree2为子树，此时tree1可以不为null，即tree1不为叶节点
        if(tree2 == null) return true; 
        if(tree1 == null) return false;
        if(tree1.val == tree2.val){
            return isEqualTree(tree1.left,tree2.left) && isEqualTree(tree1.right,tree2.right);
        }
        return false;
    }
}
```
 
### 18.二叉树的镜像
 
  
操作给定的二叉树，将其变换为源二叉树的镜像。
 
  
![][0]


 
```java
/**
public class TreeNode {
    int val = 0;
    TreeNode left = null;
    TreeNode right = null;

    public TreeNode(int val) {
        this.val = val;

    }

}
*/
public class Solution {
    public void Mirror(TreeNode root) {
        if(root != null){
            TreeNode temp = root.left;
            root.left = root.right;
            root.right = temp;
            if(root.left!=null) Mirror(root.left);
            if(root.right!=null) Mirror(root.right);
        }
    }
}
```
 
### ==19.顺时针打印矩阵（这道题有难度）==
 
==见书P161==
 
输入一个矩阵，按照从外向里以顺时针的顺序依次打印出每一个数字，例如，如果输入如下矩阵： 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 则依次打印出数字1,2,3,4,8,12,16,15,14,13,9,5,6,7,11,10.
 
#### 知识点：
 
关于值传递和引用传递可以得出这样的结论：
 

* 基本数据类型传值，对形参的修改不会影响实参； 
* 引用类型传引用，形参和实参指向同一个内存地址（同一个对象），所以对参数的修改会影响到实际的对象； 
* String, Integer, Double等immutable的类型特殊处理，可以理解为传值，最后的操作不会修改实参对象。 
 

#### 解法一：
 
```java
import java.util.ArrayList;
public class Solution {
    public ArrayList<Integer> printMatrix(int [][] matrix) {
        if(matrix == null) return null;
        ArrayList<Integer> result = new ArrayList<>();
        int start = 0;
        while(start*2<matrix.length&&start*2<matrix[0].length){
            printMatrixCircle(matrix,start,result);
            start++;
        }
       return result;
    }
    public void printMatrixCircle(int [][] matrix,int start,ArrayList<Integer> result){
        int endX = matrix[0].length - 1 - start;
        int endY = matrix.length - 1 - start;
        for(int i = start;i <= endX;i++){
            result.add(matrix[start][i]);
        }
        if(start < endY){
            for(int i = start +1;i <= endY;i++)
                result.add(matrix[i][endX]);
        }
        if(start<endX&&start<endY)
            for(int i = endX -1;i>=start;i--)
                result.add(matrix[endY][i]);
        if(start<endX&&start<endY-1)
            for(int i = endY -1;i>start;i--)
                result.add(matrix[i][start]);
    }
}
```
 
#### 解法二：
 
```java
import java.util.ArrayList;
public class Solution {
    public ArrayList<Integer> printMatrix(int [][] matrix) {
       if(matrix == null) return null;
        ArrayList<Integer> result = new ArrayList<>();
        int h = matrix.length,w = matrix[0].length,round = 0;
        while(result.size()<h*w){
            int c=round,r=round;
            while(c<w-round)
                result.add(matrix[r][c++]);
            c--;
            r++;
            if(r == h-round) continue;
            while(r<h-round)
                result.add(matrix[r++][c]);
            r--;
            c--;
            if(c == round-1) continue;
            while(c>=round)
                result.add(matrix[r][c--]);
            c++;
            r--;
            while(r>round)
                result.add(matrix[r--][c]);
            round++;
        }
        return result;
    }
}
```
 
### 20 包含min函数的栈
 
定义栈的数据结构，请在该类型中实现一个能够得到栈最小元素的min函数。
 
```java
import java.util.Stack;

public class Solution {

    Stack<Integer> stack = new Stack<Integer>();
    Stack<Integer> minStack = new Stack<Integer>();
    int min;
    public void push(int node) {
        stack.push(node);
        if(minStack.empty())
            min = node;
        else
            min = Math.min(minStack.peek(),node);
        minStack.push(min);
    }
    
    public int pop() {
        minStack.pop();
        return stack.pop();
    }
    
    public int top() {
        return stack.peek();
    }
    
    public int min() {
        return minStack.peek();
    }
}
```
 
### 21.栈的压入、弹出序列
 
输入两个整数序列，第一个序列表示栈的压入顺序，请判断第二个序列是否为该栈的弹出顺序。假设压入栈的所有数字均不相等。例如序列1,2,3,4,5是某栈的压入顺序，序列4，5,3,2,1是该压栈序列对应的一个弹出序列，但4,3,5,1,2就不可能是该压栈序列的弹出序列。（注意：这两个序列的长度是相等的）
 
#### 【解题思路】：设计一个辅助栈，如果下一个弹出的数字是辅助栈的栈顶，则弹出，如果不是栈顶，则继续将压入序列压入辅助栈，直到把下一个需要弹出的数字压入栈顶为止；如果所有数字都压入辅助站，栈顶仍然不是欲弹出的数字，则该序列不可能是一个弹出序列。
 
==注意：当stack为空的时候，调用peek()方法会抛出异常==
 
```java
import java.util.Stack;
public class Solution {
    public boolean IsPopOrder(int [] pushA,int [] popA) {
        if(pushA == null||popA == null||pushA.length!=popA.length) return false;
        Stack<Integer> stack = new Stack<>();
        int j = 0;
        for(int i = 0 ;i<popA.length;i++){
            //一定注意这里需要先判断一下栈是否为空，
            //如果为空，则调用peek()时会出现异常;
            if(stack.empty())
                stack.push(pushA[j++]);
            while(stack.peek()!=popA[i]&&j<pushA.length)
                stack.push(pushA[j++]);
            if(stack.peek()==popA[i])
                stack.pop();
            else
                return false;
        }
        return true;
    }
}
```
 
### 22.从上往下打印二叉树
 
从上往下打印出二叉树的每个节点，同层节点从左至右打印。
 
#### Java知识点：
 

* 返回长度： 
 

* String.length();String字符串用length()方法会返回其长度。 
* Array.length;数组有length属性，直接数组名点length就可以取到。 
* ArrayList.size()方法的会返回其长度。 
   

 
* ArrayList 操作： 
 **`get(),add(),remove()`**  
 You need to use the get() method to get the element at a particular index from an ArrayList. You can't use [] to get the element at a particular index, in an arraylist. Its possible only for arrays and your files is not an array, but an ArrayList.  
 

==一定要注意，Java中Queue为接口，如果使用队列需要使用LinkedList（双向队列）、PriorityQueue（优先队列）==
 
#### 解法一：
 
```java
import java.util.ArrayList;
import java.util.LinkedList;

/**
 * public class TreeNode {
 *  int val = 0;
 *  TreeNode left = null;
 *  TreeNode right = null;
 *
 *  public TreeNode(int val) {
 *      this.val = val;
 *  }
 * }
 */
public class Solution {
    public ArrayList<Integer> PrintFromTopToBottom( TreeNode root )
    {
        ArrayList<Integer> result = new ArrayList<>();
        if ( root == null )
            return(result);
        LinkedList<TreeNode> queue = new LinkedList<>();
        result.add( root.val );
        if ( root.left != null )
            queue.offer( root.left );
        if ( root.right != null )
            queue.offer( root.right );
        while ( !queue.isEmpty() )
        {
            TreeNode node = queue.poll();
            result.add( node.val );
            if ( node.left != null )
                queue.offer( node.left );
            if ( node.right != null )
                queue.offer( node.right );
        }
        return(result);
    }
}
```
 
#### 解法二：
 
```java
/**
public class TreeNode {
    int val = 0;
    TreeNode left = null;
    TreeNode right = null;

    public TreeNode(int val) {
        this.val = val;
    }
}
*/
import java.util.ArrayList;
/**
用arraylist模拟一个队列来存储相应的TreeNode
*/
public class Solution {
    ArrayList<Integer> result = new ArrayList<>();
    ArrayList<TreeNode> temp = new ArrayList<>();
    public ArrayList<Integer> PrintFromTopToBottom(TreeNode root) {
        if(root == null) return result;
        temp.add(root);
        while(temp.size() != 0){
            TreeNode node = temp.remove(0);
            result.add(node.val);
            if(node.left!=null)
                temp.add(node.left);
            if(node.right!=null)
                temp.add(node.right);
        }
        return result;
    }
}
```
 
### 23.二叉搜索树的后序遍历序列
 
输入一个整数数组，判断该数组是不是某二叉搜索树的后序遍历的结果。如果是则输出True,否则输出False。假设输入的数组的任意两个数字都互不相同。
 
```java
public class Solution {
    public boolean VerifySquenceOfBST(int [] sequence) {
        if(sequence == null || sequence.length == 0) return false;
        int start = 0,end = sequence.length-1;
        return isSearchTree(sequence,start,end);
    }
    public boolean isSearchTree(int [] sequence,int start,int end){
        if(end==start) return true;
        int root = sequence[end];
        int index = end;
        for(int i = start;i<end;i++){
            if(sequence[i] > root){
                index = i;
                break;
            }
        }
        for(int i = index;i<end;i++)
            if(sequence[i]< root)
                return false;
        if(index == end||index == start)// index = end 时没有右子树；index = start时没有左子树； 
            return isSearchTree(sequence,start,end-1);
        else
            return isSearchTree(sequence,start,index-1)&&isSearchTree(sequence,index,end-1);
    }
}
```
 
### 24.二叉树中和为某一值的路径
 
输入一颗二叉树和一个整数，打印出二叉树中结点值的和为输入整数的所有路径。路径定义为从树的根结点开始往下一直到叶结点所经过的结点形成一条路径。
 
【解题思路】：因为根结点和叶子结点一定在路径中，而且路径开始一定是跟结点，使用前序遍历遍历二叉树，每经过一个结点减小target的值，直至找到使target=0的叶子结点，即为路径，每次回退，需要删除路径中最后一个结点。
 
```java
import java.util.ArrayList;
/**
public class TreeNode {
    int val = 0;
    TreeNode left = null;
    TreeNode right = null;

    public TreeNode(int val) {
        this.val = val;

    }

}
*/
public class Solution {
    private ArrayList<ArrayList<Integer>> allPath = new ArrayList<>();
    private ArrayList<Integer> path = new ArrayList<>();
    public ArrayList<ArrayList<Integer>> FindPath(TreeNode root,int target) {
        if(root == null) return allPath;
        target -= root.val;
        path.add(root.val);
        if(target == 0&& root.left == null&&root.right == null)
            allPath.add(new ArrayList<Integer>(path));
        else{
            FindPath(root.left,target);
            FindPath(root.right,target);
        }
        path.remove(path.size()-1);
        return allPath;
        
    }
}
```
 
### 25.复杂链表的复制
 
输入一个复杂链表（每个节点中有节点值，以及两个指针，一个指向下一个节点，另一个特殊指针指向任意一个节点），返回结果为复制后复杂链表的head。（注意，输出结果中请不要返回参数中的节点引用，否则判题程序会直接返回空）
 
```java
/*
public class RandomListNode {
    int label;
    RandomListNode next = null;
    RandomListNode random = null;

    RandomListNode(int label) {
        this.label = label;
    }
}
*/
public class Solution {
    public RandomListNode Clone(RandomListNode pHead)
    {
        //一定注意考虑输入为空链表的情况
        if(pHead == null) return null;
        //第一步：克隆每个结点的值和next，并且将新节点放置在对应旧结点之后
        RandomListNode node = pHead;
        while(node != null){
            RandomListNode cloneNode = new RandomListNode(node.label);
            //cloneNode.label = node.label;
            cloneNode.next = node.next;
            node.next = cloneNode;
            node = cloneNode.next;
        }
        //第二步：克隆每个随机指针
        node = pHead;
        while(node != null){
            RandomListNode cloneNode = node.next;
            if(node.random != null)
                cloneNode.random = node.random.next;
            node = cloneNode.next;
        }
        //第三步：拆分拼接的链表
        node = pHead;
        RandomListNode cloneHead = pHead.next;
        while(node != null){
            RandomListNode cloneNode = node.next;
            node.next = cloneNode.next;
            node = node.next;
            if(node != null)
                cloneNode.next = node.next;
            else
                cloneNode.next = null;
        }
        return cloneHead;
    } 
}
```
 
### 26.二叉搜索树与双向链表
 
输入一棵二叉搜索树，将该二叉搜索树转换成一个排序的双向链表。要求不能创建任何新的结点，只能调整树中结点指针的指向。
 
```java
/**
public class TreeNode {
    int val = 0;
    TreeNode left = null;
    TreeNode right = null;

    public TreeNode(int val) {
        this.val = val;

    }

}
*/
public class Solution {
    public TreeNode Convert(TreeNode pRootOfTree) {
        if(pRootOfTree == null) return null;
        if(pRootOfTree.left == null && pRootOfTree.right == null) return pRootOfTree;
        TreeNode left = Convert(pRootOfTree.left);
        TreeNode node = left;
        
        if(node == null)
            pRootOfTree.left = null;
        else{
            while(node.right != null)
                node = node.right;
            pRootOfTree.left = node;
            node.right = pRootOfTree;
        }
        TreeNode right = Convert(pRootOfTree.right);
        pRootOfTree.right = right;
        if(right != null)
            right.left = pRootOfTree;
        return left != null ? left : pRootOfTree; 
    }
}
```
 
### 27.==字符串的排列==
 
题目描述
 
输入一个字符串,按字典序打印出该字符串中字符的所有排列。例如输入字符串abc,则打印出由字符a,b,c所能排列出来的所有字符串abc,acb,bac,bca,cab和cba。
 
输入描述:
 
输入一个字符串,长度不超过9(可能有字符重复),字符只包括大小写字母。
 
```java
import java.util.ArrayList;
import java.util.HashSet;
import java.util.Collections;
public class Solution {
    ArrayList<String> result = new ArrayList<String>();
    public ArrayList<String> Permutation(String str) {
        if(str == null) return null;
        char[] charArray = str.toCharArray();
        permutation(charArray,0);
        Collections.sort(result);
        return result;
    }
    public void permutation(char[] charArray,int beginIdx){
        if(beginIdx >= charArray.length) return;
        if(beginIdx == charArray.length-1){
            result.add(String.valueOf(charArray));
        }
        HashSet<Character> charSet = new HashSet<>();
        for(int i = beginIdx;i<charArray.length;i++){
            if(i == beginIdx){
                charSet.add(charArray[i]);
                permutation(charArray,beginIdx+1);
            }else if(i != beginIdx && !charSet.contains(charArray[i])){
                char temp = charArray[beginIdx];
                charArray[beginIdx] = charArray[i];
                charArray[i] = temp;
                permutation(charArray,beginIdx+1);
                temp = charArray[beginIdx];
                charArray[beginIdx] = charArray[i];
                charArray[i] = temp;
            }
        }
    }
}
```
 
### 28.数组中出现次数超过一半的数字
 
数组中有一个数字出现的次数超过数组长度的一半，请找出这个数字。例如输入一个长度为9的数组{1,2,3,2,2,2,5,4,2}。由于数字2在数组中出现了5次，超过数组长度的一半，因此输出2。如果不存在则输出0。
 
#### 解法一：利用HashMap
 
```java
import java.util.HashMap;
public class Solution {
    public int MoreThanHalfNum_Solution(int [] array) {
        HashMap<Integer,Integer> map = new HashMap<>();
        int length = array.length;
        if(length == 1) return array[0]; //此处用于当数组只有一个元素的时候，下面的代码对该情况无效
        for(int i : array){
           if(map.containsKey(i)){
               if(map.get(i) == length/2)
                   return i;
               map.put(i,map.get(i) + 1);
               
           }else{
               map.put(i,1);
           }
        }
        return 0;
    }
}
```
 
#### 解法二：利用数组特点，重复次数超过一半的数字一定大于其它数字出现次数之和
 
```java
public class Solution {
    public int MoreThanHalfNum_Solution(int [] array) {
        if(array == null || array.length == 0) return 0;
        int length = array.length;
        int result = array[0];
        int times = 1;
        for(int i =1;i<length;i++){
            if(result == array[i])
                times++;
            else if(times == 0){
                result = array[i];
                times =1;
            }else
                times--; 
        }
        if(times == 0) return 0;
        times = 0;
        for(int i =0;i<length;i++){
            if(array[i] == result)
                times++;
        }
        if(times <= length/2)
            result = 0;
        return result;
    }
}
```
 
### 29.最小的K个数
 
输入n个整数，找出其中最小的K个数。例如输入4,5,1,6,2,7,3,8这8个数字，则最小的4个数字是1,2,3,4。
 
#### 解法一
 
Partition思想
 
允许改变原始数组的情况，时间复杂度O(n)，不适合海量数据
 
```java
import java.util.ArrayList;
public class Solution {
    /*解法一：允许改变原始数组的情况，时间复杂度O(n)，不适合海量数据*/
    public ArrayList<Integer> GetLeastNumbers_Solution(int [] input, int k) {
        ArrayList<Integer> result = new ArrayList<>();
        //注意如果输入不合法，这里返回的是一个空集合，不是Null，与return null不同
        if(input == null || k<0 || k>input.length) return result;
        
        int start = 0;
        int end = input.length-1;
        int smallNums = partition(input,start,end);
        while(smallNums != k-1){
            if(smallNums > k-1)
                smallNums = partition(input,start,smallNums-1);
            else if(smallNums < k-1)
                smallNums = partition(input,smallNums+1,end);
        }
        for(int i =0;i<k;i++){
            result.add(input[i]);
        }
        return result;
    }
    //快排方法功能函数，在指定范围内随机选取一个数字，将数组中大与等于的放置其又，小于的放置其左；
    //返回值是在变换位置后，该元素的索引值
    public static int partition(int[] array,int start,int end){
        //边界检测
        if(array == null || array.length == 0 || start < 0 || end >= array.length || start > end) return -1;
        //在[start,end]范围内，随机选取一个数作为index
        int randomIdx = (int)(start + Math.random()*(end-start));
        //int length = array.length;
        int smallNums = start-1;
        swap(array,randomIdx,end);
        for(int i=start;i<end;i++){
            if(array[i] < array[end]){
                smallNums++;
                if(smallNums < i){
                    swap(array,smallNums,i);
                }
            }
        }
        
        smallNums++;
        swap(array,smallNums,end);
        return smallNums;
    }
    //交换元素
    public static void swap(int[] array,int i,int j){
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}
```
 
#### 解法二：
 
使用最大堆思想，通过优先队列的Conparator定制排序，实现指定大小的最大堆。这样做的目的是使空间复杂度最低O(k),时间复杂度最低O(nlogk)
 
```java
import java.util.ArrayList;
import java.util.Comparator;
import java.util.PriorityQueue;
public class Solution {
    //解法二：不改变原始数组，使用优先队列，时间复杂度O(nlogk)，适合海量数据
    public ArrayList<Integer> GetLeastNumbers_Solution(int [] input, int k) {
        ArrayList<Integer> result = new ArrayList<>();
        if(input == null || k > input.length || k<=0) return result;
        PriorityQueue<Integer> maxQueue = new PriorityQueue(k,new Comparator<Integer>(){
            @Override
            public int compare(Integer o1,Integer o2){
                return o2.compareTo(o1);//将先前Integer中的自然排序（从小到大）反过来，实现从大到小；
            }
        });
        for(int i =0;i<input.length;i++){
            if(maxQueue.size() != k ){
                maxQueue.offer(input[i]);
            }else if(maxQueue.peek() > input[i]){
                Integer temp = maxQueue.poll();//必须先去除队列头部的数据,以保证队列长度
                temp = null;
                maxQueue.offer(input[i]);
            }
        }
        for(Integer i : maxQueue){
            result.add(i);
        }
        return result;
    }
}
```
 
### 30.连续子数组的最大和
 
HZ偶尔会拿些专业问题来忽悠那些非计算机专业的同学。今天测试组开完会后,他又发话了:在古老的一维模式识别中,常常需要计算连续子向量的最大和,当向量全为正数的时候,问题很好解决。但是,如果向量中包含负数,是否应该包含某个负数,并期望旁边的正数会弥补它呢？例如:{6,-3,-2,7,-15,1,2,2},连续子向量的最大和为8(从第0个开始,到第3个为止)。你会不会被他忽悠住？(子向量的长度至少是1)
 
```java
public class Solution {
    public int FindGreatestSumOfSubArray(int[] array) {
        if (array == null || array.length == 0) return 0;
        int[] DP = new int[2];
        DP[0] = array[0];
        int max = DP[0];
        for (int i = 1; i < array.length; i++) {
            DP[i & 1] = Math.max(array[i], array[i] + DP[(i - 1) & 1]);
            max = Math.max(max, DP[i & 1]);
        }
        return max;
    }
}
```
 
### ==31.1~n整数中1出现的次数==
 
输入一个整数n，求1~ n个整数的十进制表示中1出现的次数，例如：输入13，1~13中包含1的数字有1、10、11、12、13因此共出现6次。
 
#### 解题思路：
 
思路：
 
n中每一位数字对整体“1”数量的影响包括一下两个方面：
 

* 若第i位大于1，则该位1的个数位，高于i的位组成的数字+1倍的10^i； 
* 若第i位等于1，则该位1的个数位，高于i的位组成的数字倍的10^i加上后面各位组成的数字加1； 
* 若第i位小于1，则该位1的个数位，高于i的位组成的数字倍的10^i；

```java
import java.util.ArrayList;
public class Solution {
public int NumberOf1Between1AndN_Solution(int n) {
    if(n<=0) return 0;
    //用于将int的每一位数字保存在int[]数组中
    ArrayList<Integer> number = new ArrayList<>();
    int totalNums = 0;
    //已分析过的高位数字组成的乘子
    int mult = 0;
    int temp = n;
    while(temp!=0){
        number.add(temp%10);
        temp = temp/10;
    }
    for(int i = number.size()-1;i>=0;i--){
        int nums = (int)(Math.pow(10,i));
        if(number.get(i) == 1){
            totalNums += (int)(n % Math.pow(10,i) + 1);
        }else if(number.get(i) > 1){
            totalNums += (int)(Math.pow(10,i));
        }else if(number.get(i) == 0){
        }
        totalNums += mult * nums;
        mult = mult * 10 + number.get(i);
    }
    return totalNums;
}
}
```
#### 解法二：找数字规律
  
 

```java
import java.util.ArrayList;

public class Solution {
    public int NumberOf1Between1AndN_Solution(int n) {
        if (n <= 0) return 0;
        int num = 0, k = 0, count = 0, i = 1;
        while (n != 0) {
            int x = n % 10;
            if (x == 1) {
                count += num + 1;
                count += x * k;
            } else if (x > 1) {
                count += x * k;
                count += (int) Math.pow(10, i - 1);
            }
            num += x * Math.pow(10, i - 1);
            k = 10 * k + (int) Math.pow(10, i - 1);
            n /= 10;
            i++;
        }

        return count;
    }
}
```
 
### 32.把数组排成最小的数
 
输入一个正整数数组，把数组里所有数字拼接起来排成一个数，打印能拼接出的所有数字中最小的一个。例如输入数组{3，32，321}，则打印出这三个数字能排成的最小数字为321323。
 
#### 解题思路：
 

* 实际是将数组元素进行排序的操作 
* 排序规则为，若MN组成的数字大于NM，则N在前M在后 
* 使用Comparatpr定制排序规则 
* 考虑到数字连接起来可能使int溢出，所以转换为使用String来操作。 
 

```java
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
public class Solution {
    public String PrintMinNumber(int[] numbers) {
        String result = "";
        if (numbers == null || numbers.length == 0) return result;
        ArrayList<String> list = new ArrayList<>();
        for (int i = 0; i < numbers.length; i++) {
            list.add(numbers[i] + "");
        }
        Collections.sort(list, new Comparator<String>() {
            @Override
            public int compare(String sNum1, String sNum2) {
                String num1 = sNum1 + sNum2;
                String num2 = sNum2 + sNum1;
                return num1.compareTo(num2);
            }
        });
        for (String str : list) {
            result += str;
        }
        return result;
    }
}
```
 
### 33.丑数
 
把只包含因子2、3和5的数称作丑数（Ugly Number）。例如6、8都是丑数，但14不是，因为它包含因子7。 习惯上我们把1当做是第一个丑数。求按从小到大的顺序的第N个丑数。
 
```java
public class Solution {
    public int GetUglyNumber_Solution(int index) {
        if(index <= 0 ) return 0;
        int mult2_Idx = 0,mult3_Idx = 0,mult5_Idx = 0;
        int[] uglyNumber = new int[index];
        uglyNumber[0] = 1;
        for(int i = 1;i<index;i++){
            int min = Math.min(Math.min(uglyNumber[mult2_Idx]*2,
                                        uglyNumber[mult3_Idx]*3),
                                        uglyNumber[mult5_Idx]*5);
            uglyNumber[i] = min;    
            while(uglyNumber[mult2_Idx]*2 <= uglyNumber[i])
                mult2_Idx++;
            while(uglyNumber[mult3_Idx]*3 <= uglyNumber[i])
                mult3_Idx++;
            while(uglyNumber[mult5_Idx]*5 <= uglyNumber[i])
                mult5_Idx++;
        }
        return uglyNumber[index-1];
    }
}
```
 
### 34.第一个只出现一次的字符
 
在一个字符串(1<=字符串长度<=10000，全部由字母组成)中找到第一个只出现一次的字符,并返回它的位置
 
```java
import java.util.HashMap;
public class Solution {
    public int FirstNotRepeatingChar(String str) {
        int result = Integer.MAX_VALUE;
        if(str.length() == 0) return -1;
        HashMap<Character,Integer> charIdx = new HashMap<>();
        for(int i = 0 ;i < str.length(); i++){
            Character c = str.charAt(i);
            if(charIdx.containsKey(c)){
                charIdx.put(c,-1);
            }else{
                charIdx.put(c,i);
            }
        }
        for(int index : charIdx.values()){
            if(index != -1){
                result = Math.min(result,index);
            }
        }
        return result;
    }
}
```
 
### 35.==数组中的逆序对==
 
在数组中的两个数字，如果前面一个数字大于后面的数字，则这两个数字组成一个逆序对。输入一个数组,求出这个数组中的逆序对的总数P。并将P对1000000007取模的结果输出。 即输出P%1000000007
 
输入描述:
 
题目保证输入的数组中没有的相同的数字
 
数据范围：
 
```java
对于%50的数据,size<=10^4
对于%75的数据,size<=10^5
对于%100的数据,size<=2*10^5
```
 
示例1
 
输入1,2,3,4,5,6,7,0 输出7
 
```java
public class Solution {
    public int InversePairs(int [] array) {
        if(array == null||array.length == 0) return 0;
        int length = array.length;
        int[] copy = new int[length];
        for(int i = 0;i < length ;i++){
            copy[i] = array[i];
        }
        int count = InversePairsCore(array,copy,0,array.length-1);
        return count;
    }
    
    public int InversePairsCore(int[] array,int[] copy,int start,int end){
        if(start == end){
            return 0;
        }
        int count = 0;
        int length = (end-start)/2;
        //注意：这里是故意将copy和array调换位置的，因为每次执行InversePairCore之后copy在[start,end]部分都是排好序的
        //随意使用data作为array输入，省去了来回复制的资源消耗。
        int left = InversePairsCore(copy,array,start,start+length);
        int right = InversePairsCore(copy,array,start+length+1,end);
        int p1 = start+length;
        int p2 = end;
        int copyIdx = end;
        while(p1 >= start && p2 >= start+length+1){
            if(array[p1]>array[p2]){
                count += p2-start-length;
                //此处先判断一下，以免超出运算范围。
                if(count > 1000000007)
                    count = count%1000000007;
                copy[copyIdx--] = array[p1--];
            }else{
                copy[copyIdx--] = array[p2--];
            }
        }
        while(p1 >= start){
            copy[copyIdx--] = array[p1--];
        }
        while(p2 >= start+length+1){
            copy[copyIdx--] = array[p2--];
        }
        return (count+left+right)%1000000007;
    } 
}
```
 
### 36.两个链表的第一个公共结点
 
输入两个链表，找出它们的第一个公共结点。 **`技巧：不使用辅助Stack`** 
 
```java
/*
public class ListNode {
    int val;
    ListNode next = null;

    ListNode(int val) {
        this.val = val;
    }
}*/
public class Solution {
    public ListNode FindFirstCommonNode(ListNode pHead1, ListNode pHead2) {
        if(pHead1 == null || pHead2 == null) return null;
        int L1 = getListLength(pHead1);
        int L2 = getListLength(pHead2);
        if(L1>L2)
            for(int i = 0 ;i<(L1-L2);i++)
                pHead1 = pHead1.next;
        else if(L2>L1)
            for(int i = 0 ;i<(L2-L1);i++)
                pHead2 = pHead2.next;
        
        while(pHead1!=null){
            if(pHead1 == pHead2)
                return pHead1;
            pHead1 = pHead1.next;
            pHead2 = pHead2.next;
        }
        return null;
    }
    public int getListLength(ListNode head){
        ListNode temp = head;
        int count = 1;
        while(temp.next != null){
            temp = temp.next;
            count++;
        }
        return count;
    }
}
```
 
### 37.数字在排序数组中出现的次数
 
统计一个数字在排序数组中出现的次数。
 
采用二分查找法
 
```java
/*
方法一：时间复杂度O（n），不可选
*/

public class Solution {
    public int GetNumberOfK(int [] array , int k) {
        if(array.length == 0) return 0;
        int count = 0;
        for(int i = 0 ; i < array.length ; i++){
            if(array[i] == k){
                count++;
            }else{
                if(count != 0)
                    break;
            }
        }
        return count;
    }
}

/*
方法二：首选！先采用二分查找法，在数组中查找到第一个K和第二个K，总时间复杂度O（logn）
*/
public class Solution {
    public int GetNumberOfK(int[] array,int k){
        if(array.length == 0) return 0;
        int first = getFirstK(array,k,0,array.length-1);
        int last = getLastK(array,k,0,array.length-1);
        if(first > -1 && last > -1)
            return last - first + 1;
        return 0;
    }
    public int getFirstK(int[] array,int k,int start,int end){
        if(start > end) return -1;
        int midIdx = (end + start)/2;
        if(array[midIdx] == k){
            if((midIdx > 0 && array[midIdx-1] != k) || midIdx == 0)
                return midIdx;
            else{
                end = midIdx - 1;
                return getFirstK(array,k,start,end);
            }
        }else if(array[midIdx] > k){
            end = midIdx - 1;
        }else if(array[midIdx] < k){
            start = midIdx +1;
        }
        return getFirstK(array,k,start,end);
    }
    public int getLastK(int[] array,int k ,int start,int end){
        if(start > end) return -1;
        int midIdx = (start + end)/2;
        if(array[midIdx] == k){
            if((midIdx < array.length-1 && array[midIdx+1] != k) || midIdx == array.length-1)
                return midIdx;
            else
                start = midIdx + 1;
        }else if(array[midIdx] > k){
            end = midIdx - 1;
        }else if(array[midIdx] < k){
            start = midIdx + 1;
        }
        return getLastK(array,k,start,end);
    }
}
```
 
### 38.二叉树的深度
 
输入一棵二叉树，求该树的深度。从根结点到叶结点依次经过的结点（含根、叶结点）形成树的一条路径，最长路径的长度为树的深度。
 
```java
/**
public class TreeNode {
    int val = 0;
    TreeNode left = null;
    TreeNode right = null;

    public TreeNode(int val) {
        this.val = val;

    }

}
*/
public class Solution {
    public int TreeDepth(TreeNode root) {
        if(root == null) return 0;
        int left = TreeDepth(root.left);
        int right = TreeDepth(root.right);
        if(left>right) return left+1;
        else return right+1;
    }
}
```
 
### 39.平衡二叉树
 
输入一棵二叉树，判断该二叉树是否是平衡二叉树。如果某二叉树中任意节点的左、右子树的深度相差不超过1，那么他就是一棵平衡二叉树。
 
解法一：不够简便
 
```java
public class Solution {
    public boolean IsBalanced_Solution(TreeNode root) {
        if(root == null) return true;
        int left = TreeDepth(root.left);
        int right = TreeDepth(root.right);
        if((left-right)>1||(left-right)<-1)
            return false;
        else
            return IsBalanced_Solution(root.left) && IsBalanced_Solution(root.right);
    }
    public int TreeDepth(TreeNode root){
        if(root == null) return 0;
        int left = TreeDepth(root.left);
        int right = TreeDepth(root.right);
        return left > right ? left+1 : right+1;
    }
}
```
 
#### 解法二：推荐！后序遍历二叉树，只需遍历一遍即可。
 
```java
public class Solution {
    public boolean IsBalanced_Solution(TreeNode root) {
        return getDepth(root) != -1;
    }
    public int getDepth(TreeNode root){
        if(root == null) return 0;
        int left = getDepth(root.left);
        if(left == -1)
            return -1;
        int right = getDepth(root.right);
        if(right == -1)
            return -1;
        return Math.abs(left-right) > 1 ? -1 : Math.max(left,right) + 1;
    }
}
```
 
### 40.数组中只出现一次的数字
 
一个整型数组里除了两个数字之外，其他的数字都出现了两次。请写程序找出这两个只出现一次的数字。
 
第一种：利用Set，空间复杂度为O(N)
 
```java
//num1,num2分别为长度为1的数组。传出参数
//将num1[0],num2[0]设置为返回结果
import java.util.HashSet;
import java.util.Iterator;
public class Solution {
    public void FindNumsAppearOnce(int [] array,int num1[] , int num2[]) {
        HashSet<Integer> set = new HashSet<Integer>();
        for(int i = 0;i<array.length;i++){
            if(set.contains(array[i])){
                set.remove(array[i]);
            }else{
                set.add(array[i]);
            }
        }
        boolean isFirst = true;
        Iterator iter = set.iterator();
        while(iter.hasNext()){
            if(isFirst){
                num1[0] = (int)iter.next();
                isFirst = false;
            }else
                num2[0] = (int)iter.next();
        }
    }
}
```
 
#### 第二种：按位运算：异或、位移
 
```java
//num1,num2分别为长度为1的数组。传出参数
//将num1[0],num2[0]设置为返回结果
public class Solution {
    public void FindNumsAppearOnce(int [] array,int num1[] , int num2[]) {
        int OR = 0;
        for(int i = 0;i<array.length;i++)
            OR ^= array[i];
        int idx = 0;//OR从后数第几位是1，从1开始
        while(OR != 0){
            OR = OR >> 1;
            idx++;
        }
        num1[0] = 0;
        num2[0] = 0;
        for(int i = 0;i<array.length;i++){
            if((array[i]&(1<<(idx-1))) == 0)
                num1[0] ^= array[i];
            else
                num2[0] ^= array[i];
        }
    }
}
```
 
### 41.和为S的连续正数序列
 
小明很喜欢数学,有一天他在做数学作业时,要求计算出9~16的和,他马上就写出了正确答案是100。但是他并不满足于此,他在想究竟有多少种连续的正数序列的和为100(至少包括两个数)。没多久,他就得到另一组连续正数和为100的序列:18,19,20,21,22。现在把问题交给你,你能不能也很快的找出所有和为S的连续正数序列? Good Luck!
 
输出描述:
 
输出所有和为S的连续正数序列。序列内按照从小至大的顺序，序列间按照开始数字从小到大的顺序
 
```java
import java.util.ArrayList;

public class Solution {
    public ArrayList<ArrayList<Integer>> FindContinuousSequence(int sum) {
        ArrayList<ArrayList<Integer>> result = new ArrayList<>();
        int small = 1, big = 2, s = 3, mid = sum / 2;
        while (small <= mid) {
            if (s == sum) {
                ArrayList<Integer> list = new ArrayList<>();
                for (int i = small; i <= big; i++)
                    list.add(i);
                result.add(list);
                s -= small;
                small++;
            } else if (s < sum) {
                big++;
                s += big;
            } else if (s > sum) {
                s -= small;
                small++;
            }
        }
        return result;
    }
}
```
 
### 42.和为S的两个数
 
输入一个递增排序的数组和一个数字S，在数组中查找两个数，是的他们的和正好是S，如果有多对数字的和等于S，输出两个数的乘积最小的。
 
解析：
 
其实找的就是数组最两侧满足和为S的数字，因为：
 
z=xy
 
x+y=s
 
z=x(s-x)=sx-x^2 函数图像为向下开口的抛物线，两段数值小中间大。所以取两边的值。
 
```java
import java.util.ArrayList;
public class Solution {
    public ArrayList<Integer> FindNumbersWithSum(int [] array,int sum) {
        ArrayList<Integer> result = new ArrayList<>();
        int p1 = 0,p2 = array.length-1;
        while(p1<p2){
            if(array[p1]+array[p2] == sum){
                result.add(array[p1]);
                result.add(array[p2]);
                return result;
            }else if(array[p1]+array[p2]>sum)
                p2--;
            else
                p1++;
        }
        return result;
    }
}
```
 
### 43.坐旋转字符串
 
汇编语言中有一种移位指令叫做循环左移（ROL），现在有个简单的任务，就是用字符串模拟这个指令的运算结果。对于一个给定的字符序列S，请你把其循环左移K位后的序列输出。例如，字符序列S=”abcXYZdef”,要求输出循环左移3位后的结果，即“XYZdefabc”。是不是很简单？OK，搞定它！
 
==该题有好多种做法==
 
方法一：虽然AC，但是不是最优解
 
```java
public class Solution {
    public String LeftRotateString(String str,int n) {
        if(n<0 || str==null || str.length() == 0) return "";
        n %= str.length();
        StringBuilder sb = new StringBuilder();
        for(int i = n;i<str.length();i++){
            sb.append(str.charAt(i));
        }
        for(int i = 0;i<n;i++){
            sb.append(str.charAt(i));
        }
        return sb.toString();
    }
}
```
 
#### 方法二：
 
```java
public class Solution {
    public String LeftRotateString(String str, int n) {
        if (str.length() == 0 || n < 0) return "";
        int length = str.length();
        n %= length;
        str += str;
        return str.substring(n, n + length);
    }
}
```
 
### 44.翻转字符串
 
牛客最近来了一个新员工Fish，每天早晨总是会拿着一本英文杂志，写些句子在本子上。同事Cat对Fish写的内容颇感兴趣，有一天他向Fish借来翻看，但却读不懂它的意思。例如，“student. a am I”。后来才意识到，这家伙原来把句子单词的顺序翻转了，正确的句子应该是“I am a student.”。Cat对一一的翻转这些单词顺序可不在行，你能帮助他么？
 
```java
public class Solution {
    public String ReverseSentence(String str) {
        if (str.length() == 0) return "";
        char[] charArray = str.toCharArray();
        Reverse(charArray, 0, str.length() - 1);
        int start = 0, end = 0;
        for (int i = 0; i < charArray.length; i++) {
            if (charArray[i] == ' ') {
                end = i - 1;
                Reverse(charArray, start, end);
                start = i + 1;
            }
        }
        //这句话是用于旋转最后一个单词的。
        Reverse(charArray, start, charArray.length - 1);
        return String.valueOf(charArray);
    }

    public char[] Reverse(char[] charArray, int start, int end) {
        while (start < end) {
            char temp = charArray[start];
            charArray[start] = charArray[end];
            charArray[end] = temp;
            start++;
            end--;
        }
        return charArray;
    }
}
```
 
### 45.扑克牌顺子
 
LL今天心情特别好,因为他去买了一副扑克牌,发现里面居然有2个大王,2个小王(一副牌原本是54张^_^)...他随机从中抽出了5张牌,想测测自己的手气,看看能不能抽到顺子,如果抽到的话,他决定去买体育彩票,嘿嘿！！“红心A,黑桃3,小王,大王,方片5”,“Oh My God!”不是顺子.....LL不高兴了,他想了想,决定大\小 王可以看成任何数字,并且A看作1,J为11,Q为12,K为13。上面的5张牌就可以变成“1,2,3,4,5”(大小王分别看作2和4),“So Lucky!”。LL决定去买体育彩票啦。 现在,要求你使用这幅牌模拟上面的过程,然后告诉我们LL的运气如何。为了方便起见,你可以认为大小王是0。
 
```java
import java.util.Arrays;
public class Solution {
    public boolean isContinuous(int [] numbers) {
        if(numbers.length < 5) return false;
        Arrays.sort(numbers);
        int zerosNum = 0;
        int needZeros = 0;
        for(int i = 0 ;i < 5;i++){
            if(numbers[i] == 0){
                zerosNum++;
            }else if(i+1<5){
                //如存在两数字相同，则一定不是顺子
                if(numbers[i+1] == numbers[i]) return false; 
                needZeros += numbers[i+1] - numbers[i] -1;
            }
        }
        //此时大王个数超过四个，不符合题目要求
        if(zerosNum > 4) return false; 
        if(zerosNum >= needZeros) return true;
        else return false;
    }
}
```
 
### 46.孩子们的游戏
 
n个人（编号0~(n-1))，从0开始报数，报到(m-1)的退出，剩下的人 继续从0开始报数。求胜利者的编号。（约瑟夫环问题）
 
解法一：使用数组模拟环
 
```java
public class Solution {
    public int LastRemaining_Solution(int n, int m) {
        if(n<0||m<1) return -1;
        int[] array = new int[n];
        int count=n,step=0,idx=-1;
        while(count>0){
            idx++;
            if(idx == n) idx=0;
            if(array[idx] == -1) continue;//如果是被标记过的则跳过
            step++;
            if(step == m){
                array[idx] = -1;
                count--; 
                step=0;
            } 
        }
        return idx;
    }
}
```
 
  
解法二：使用ArrayList模拟环
 
  
![][1]


 
```java
import java.util.ArrayList;
public class Solution {
    public int LastRemaining_Solution(int n, int m){
        if(n<0||m<1) return -1;
        ArrayList<Integer> list = new ArrayList<>();
        for(int i = 0;i<n;i++)
            list.add(i);
        int idx = (m-1)%n;
        while(list.size()>1){
            list.remove(idx);
            idx = (idx+m-1)%list.size();
        }
        return list.get(0);
    }
}
```
 
### 47.求1+2+3+...+n
 
求1+2+3+...+n，要求不能使用乘除法、for、while、if、else、switch、case等关键字及条件判断语句（A?B:C）。
 
解题思路： **`(短路求值)`** 
 

* 需利用 **`逻辑与`**  的 **`短路特性`**  实现递归终止。  
* 当n==0时，(n>0)&&((sum+=Sum_Solution(n-1))>0)只执行前面的判断，为false，然后直接返回0； 
* 当n>0时，执行sum+=Sum_Solution(n-1)，实现递归计算Sum_Solution(n)。 
 

```java
public class Solution {
    public int Sum_Solution(int n) {
        int sum = n;
        boolean isEnd = (sum != 0)&&((sum += Sum_Solution(n-1))>0);
        return sum;
    }
}
```
 
### 48.不用加减乘除做加法
 
写一个函数，求两个整数之和，要求在函数体内不得使用+、-、*、/四则运算符号。
 
#### 解析：按位运算
 

* step1:按位与是查看两个数哪些二进制位都为1，这些都是进位位，结果需左移一位，表示进位后的结果 
* step2:异或是查看两个数哪些二进制位只有一个为1，这些是非进位位，可以直接加、减，结果表示非进位位进行加操作后的结果 
* step3:n1&n2是查看有没有进位位了，如果有，需要重复step1、step2；如果没有，保留n1、n2上二进制为1的部分，用或将之合为一个数，即为最后结果 
 

```java
public class Solution {
    public int Add(int num1,int num2) {
        int n1,n2;
        n1 = num1 & num2;
        n1 = n1<<1;
        n2 = num1 ^ num2;
        if((n1 & n2) != 0) return Add(n1,n2);
        return n1 | n2;
    }
}
```
 
### 49.把字符串转换成整数
 
  
将一个字符串转换成一个整数，要求不能使用字符串转换整数的库函数。 数值为0或者字符串不是一个合法的数值则返回0
 
  
![][2]


 
```java
public class Solution {
    public int StrToInt(String str) {
        if(str.length() < 1) return 0;
        char[] nums = str.toCharArray();
        int result = 0;
        int flag = 1;
        for(int i = 0 ; i<nums.length ; i++){
            if(nums[i]-'0'>9 || nums[i]-'0'<0){
                if( i==0 && (nums[i] == '+' || nums[i] == '-'))
                    flag = nums[i] == '+' ? 1 : -1;
                else
                    return 0;
            }else{
                result*=10;
                result+=(nums[i]-'0');
            }  
        }
        return result*flag;
    }
}
```
 
不适用str.toCharArray()方法
 
```java
public class Solution {
    public int StrToInt(String str) {
        if(str.length() < 1) return 0;
        int result = 0;
        int flag = 1;
        for(int i = 0 ; i<str.length(); i++){
            if(str.charAt(i)-'0'>9 || str.charAt(i)-'0'<0){
                if( i==0 && (str.charAt(i) == '+' || str.charAt(i) == '-'))
                    flag = str.charAt(i) == '+' ? 1 : -1;
                else
                    return 0;
            }else{
                result*=10;
                result+=(str.charAt(i)-'0');
            }  
        }
        return result*flag;
    }
}
```
 
### 50.数组中重复的数字
 
在一个长度为n的数组里的所有数字都在0到n-1的范围内。 数组中某些数字是重复的，但不知道有几个数字是重复的。也不知道每个数字重复几次。请找出数组中任意一个重复的数字。 例如，如果输入长度为7的数组{2,3,1,0,2,5,3}，那么对应的输出是第一个重复的数字2。
 
```java
public class Solution {
    // Parameters:
    //    numbers:     an array of integers
    //    length:      the length of array numbers
    //    duplication: (Output) the duplicated number in the array number,length of duplication array is 1,so using duplication[0] = ? in implementation;
    //                  Here duplication like pointor in C/C++, duplication[0] equal *duplication in C/C++
    //    这里要特别注意~返回任意重复的一个，赋值duplication[0]
    // Return value:       true if the input is valid, and there are some duplications in the array number
    //                     otherwise false
    public boolean duplicate(int numbers[],int length,int [] duplication) {
        if(length<0) return false;
        boolean[] result = new boolean[length];
        for(int i = 0;i<length;i++){
            if(numbers[i]>length-1||numbers[i]<0) return false;
            if(result[numbers[i]]){
                duplication[0] = numbers[i];
                return true;
            }
            result[numbers[i]] = true;
        }
        return false;
    }
}
```
 
### 51.构建乘积数组
 
给定一个数组A[0,1,...,n-1],请构建一个数组B[0,1,...,n-1],其中B中的元素B[i]=A[0] A[1]  ... A[i-1]  A[i+1] ...  A[n-1]。不能使用除法。
 
![][3]
 
```java
import java.util.ArrayList;
public class Solution {
    public int[] multiply(int[] A) {
        int[] B = new int[A.length];
        if(A.length == 0) return B;
        B[0] = 1;
        for(int i = 1;i<A.length;i++){
            B[i] = B[i-1] * A[i-1];
        }
        int temp = 1;
        for(int i = A.length-1;i>=0;i--){
            B[i] *= temp;
            temp *= A[i];
        }
        return B;
    }
}
```
 
### ==52.正则表达式匹配==
 
请实现一个函数用来匹配包括'.'和' '的正则表达式。模式中的字符'.'表示任意一个字符，而'  '表示它前面的字符可以出现任意次（包含0次）。 在本题中，匹配是指字符串的所有字符匹配整个模式。例如，字符串"aaa"与模式"a.a"和"ab ac  a"匹配，但是与"aa.a"和"ab*a"均不匹配
 
#### 解题思路
 
 
   1.当patternIndex后一位为‘  
’时：
 
此时若strIndex == str.length时，直接将patternIndex+2，跳过两个；
 
如果strIndex!=str.length时，分为以下三种情况：
 
1.strIndex，patternIndex+2；（str != pattern时）
 
2.strIndex+1，patternIndex+2；（str = pattern 时 或者 此时pattern == ‘.’）
 
3.strIndex+1，patternIndex；(str == pattern 而且 str+1 也 == pattern)
 ’ 
 
 
此时如果strIndex = str.length return false；
 
如果 str = pattern 则 str+1，pattern+1
 
反之 return false；
 
```java
public class Solution {
    public boolean match(char[] str, char[] pattern)
    {
        //1.边缘检测
        if(str==null||pattern==null) return false;
        int strIndex=0,patternIndex=0;
        return matchCore(str,pattern,strIndex,patternIndex);
    } 
    public boolean matchCore(char[] str,char[] pattern,int strIndex,int patternIndex){
        if(strIndex == str.length && patternIndex == pattern.length) return true;
        if(strIndex != str.length && patternIndex == pattern.length) return false;
        //当模式中第二个字符是‘*’
        if(patternIndex+1 < pattern.length && pattern[patternIndex +1] == '*'){
            //一定注意这里strIndex有可能是str.length 需要把str[strIndex]放在后面，以免溢出
            if(strIndex != str.length && (pattern[patternIndex] == '.' || str[strIndex] == pattern[patternIndex])){
                return matchCore(str,pattern,strIndex+1,patternIndex) || matchCore(str,pattern,strIndex+1,patternIndex+2) || matchCore(str,pattern,strIndex,patternIndex+2);
            }else{
                return matchCore(str,pattern,strIndex,patternIndex+2);
            }     
        }else{//模式中第二个字符不是’*‘
            if(strIndex != str.length && (str[strIndex] == pattern[patternIndex] || pattern[patternIndex] == '.'))
                return matchCore(str,pattern,strIndex+1,patternIndex+1);
            else
                return false;
        }
    }
}
```
 
### ==53.表示数值的字符串==
 
请实现一个函数用来判断字符串是否表示数值（包括整数和小数）。例如，字符串"+100","5e2","-123","3.1416"和"-1E-16"都表示数值。 但是"12e","1a3.14","1.2.3","+-5"和"12e+4.3"都不是。
 
#### 题目分析：数值可以表示为"A+'.'+B+'E/e'+C"
 

* 其中A为带符号整数，可以为空 
* B为不带符号整数，可以为空 
* A和B不能同时为空 
* C为带符号整数，不能为空 
 

```java
public class Solution {
    //声明一个全局变量，记录小数点前是否有数字
    boolean hasInt = false;
    public boolean isNumeric(char[] str) {
        if(str == null || str.length == 0) return false;
        return scanA(str,0);
    }
    //第一部分：为带符号整数，后续字符串可包括'./e/E'
    public boolean scanA(char[] str,int index){
        //1.如果有符号则跳过。
        if(str[index] == '-' || str[index] == '+') index++;
        while(index < str.length && str[index]-'0' <= 9 && str[index]-'0' >= 0){
            hasInt = true;
            index++;
        }
        if(index == str.length) return hasInt;
        if(str[index] == '.')
            return scanB(str,index+1);
        else if(str[index] == 'e'||str[index]=='E')
            return scanC(str,index+1);
        else
            return false;
    }
    //第二部分:为不带符号整数,后续字符可带'e/E'
    public boolean scanB(char[] str,int index){
        boolean hasNum = false;
        //用于判断是否是“12.”这种数字
        if(index == str.length) return hasInt || hasNum;
        while(index < str.length && str[index]-'0' <= 9 && str[index]-'0' >= 0){
            index++;
            hasNum = true;
        }
        if(index == str.length) return hasInt || hasNum;
        if(str[index] == 'e' || str[index] == 'E')
            return (hasInt || hasNum) && scanC(str,index+1);
        else
            return false;
    }
    //第三部分：为带符号整数
    public boolean scanC(char[] str,int index){
        //用于判断是否为“12e”这样的数字，这种是不正确的，第三部分不能为空
        if(index == str.length) return false;
        boolean hasNum = false;
        //如果有符号，则跳过
        if(str[index]=='+'||str[index]=='-') index++;
        while(index < str.length && str[index]-'0' <= 9 && str[index]-'0' >= 0){
            hasNum=true;
            index++;
        }  
        if(index == str.length) return hasNum;
        else return false;
    }
}
```
 
### 54.字符流中第一个不重复的字符
 
请实现一个函数用来找出字符流中第一个只出现一次的字符。例如，当从字符流中只读出前两个字符"go"时，第一个只出现一次的字符是"g"。当从该字符流中读出前六个字符“google"时，第一个只出现一次的字符是"l"。
 
输出描述:
 
如果当前字符流没有存在出现一次的字符，返回#字符。
 
```java
import java.util.ArrayList;
import java.util.HashSet;
public class Solution {
    ArrayList<Character> list = new ArrayList<>();
    HashSet<Character> set = new HashSet<>();
    //Insert one char from stringstream
    public void Insert(char ch)
    {
        if(!set.contains(ch))
            if(list.contains(ch)){
                //注意这里之所以将char转换为Character对象，是因为，如果直接带入char
                //函数会将char转变成ASCII码int值作为索引，会导致溢出。
                list.remove((Character)ch);
                set.add(ch);
            }else{
                list.add(ch);
            }
    }
  //return the first appearence once char in current stringstream
    public char FirstAppearingOnce()
    {
        if(list.size() > 0)
            return list.get(0);
        else
            return '#';
    }
}
```
 
### 55.链表中的入口结点
 
一个链表中包含环，请找出该链表的环的入口结点。
 
方法一：使用辅助Set集合
 
```java
/*
 public class ListNode {
    int val;
    ListNode next = null;

    ListNode(int val) {
        this.val = val;
    }
}
*/
import java.util.HashSet;
public class Solution {

    public ListNode EntryNodeOfLoop(ListNode pHead)
    {
        if(pHead == null) return null;
        HashSet<ListNode> set = new HashSet<>();
        while(!set.contains(pHead)){
            if(pHead.next == null) return null;
            set.add(pHead);
            pHead = pHead.next;
        }
        return pHead;
            
    }
}
```
 
#### 方法二：单纯指针操作
 
```java
public class Solution {
    public ListNode EntryNodeOfLoop(ListNode pHead)
    {
        if(pHead == null) return null;
        ListNode p1=pHead,p2=pHead.next;
        //第一步：如果有环，则算出环的长度；
        while(p1 != p2 && p2 != null){
            p1 = p1.next;
            p2 = p2.next;
            if(p2 == null) return null;
            p2 = p2.next;
        }
        if(p2 == null) return null;
        int count = 1;
        while(p1.next != p2){
            p1 = p1.next;
            count++;
        }
        //第二步：找到环的入口
        p1 = pHead;
        p2 = pHead;
        while(count-- > 0)
            p2 = p2.next;
        while(p1!=p2){
            p1 = p1.next;
            p2 = p2.next;
        }
        return p1;     
    }
}
```
 
### 56.删除链表中重复的结点这道题纠结了很久！！！很简单的递归就能实现，有点类似于动态规划 
 
在一个排序的链表中，存在重复的结点，请删除该链表中重复的结点，重复的结点不保留，返回链表头指针。 例如，链表1->2->3->3->4->4->5 处理后为 1->2->5
 
```java
/*
 public class ListNode {
    int val;
    ListNode next = null;

    ListNode(int val) {
        this.val = val;
    }
}
*/
public class Solution {
    public ListNode deleteDuplication(ListNode pHead)
    {
        if(pHead == null || pHead.next == null)
            return pHead;
        if(pHead.val == pHead.next.val){
          while(pHead.next != null && pHead.val == pHead.next.val)
              pHead = pHead.next;
          return deleteDuplication(pHead.next);
        }
        pHead.next = deleteDuplication(pHead.next);
        return pHead;
    }
}
```
 
### 57.二叉树的下一个结点
 
给定一个二叉树和其中的一个结点，请找出中序遍历顺序的下一个结点并且返回。注意，树中的结点不仅包含左右子结点，同时包含指向父结点的指针。
 
```java
/*
public class TreeLinkNode {
    int val;
    TreeLinkNode left = null;
    TreeLinkNode right = null;
    TreeLinkNode next = null;

    TreeLinkNode(int val) {
        this.val = val;
    }
}
*/
public class Solution {
    public TreeLinkNode GetNext(TreeLinkNode pNode)
    {
        if(pNode == null) return null;
        if(pNode.right != null){
            TreeLinkNode node = pNode.right;
            while(node.left != null)
                node = node.left;
            return node;
        }
        while(pNode.next != null){
            if(pNode.next.right != pNode)
                return pNode.next;
            pNode = pNode.next;
        }
        return null;
    }
}
```
 
### 58.对称的二叉树
 
请实现一个函数，用来判断一颗二叉树是不是对称的。注意，如果一个二叉树同此二叉树的镜像是同样的，定义其为对称的。
 
```java
/*
public class TreeNode {
    int val = 0;
    TreeNode left = null;
    TreeNode right = null;

    public TreeNode(int val) {
        this.val = val;

    }

}
*/
public class Solution {
    boolean isSymmetrical(TreeNode pRoot)
    {
        return isSymmetrical(pRoot,pRoot);
    }
    public boolean isSymmetrical(TreeNode n1,TreeNode n2){
        if(n1 == null && n2 == null) return true;
        if(n1 == null || n2 == null) return false;
        if(n1.val != n2.val) return false;
        return isSymmetrical(n1.left,n2.right) && isSymmetrical(n1.right,n2.left);
    }
}
```
 
### 59.==之字形打印二叉树==
 
请实现一个函数按照之字形打印二叉树，即第一行按照从左到右的顺序打印，第二层按照从右至左的顺序打印，第三行按照从左到右的顺序打印，其他行以此类推。
 
解题思路：参见《剑指offer》p176，使用两个辅助栈进行操作
 
```java
import java.util.ArrayList;
import java.util.Stack;
public class Solution {
    public ArrayList<ArrayList<Integer> > Print(TreeNode pRoot) {
        ArrayList<ArrayList<Integer>> result = new ArrayList<>();
        if(pRoot == null) return result;
        int layer = 1;
        Stack<TreeNode> odd = new Stack<>();
        Stack<TreeNode> even = new Stack<>();
        odd.push(pRoot);
        while(!odd.empty()||!even.empty()){
            ArrayList<Integer> list = new ArrayList<>();
            if((layer & 1) == 1){//位运算，判断是否为奇数;等价于layer%2
                while(!odd.empty()){
                    TreeNode node = odd.pop();
                    list.add(node.val);
                    if(node.left != null) even.push(node.left);
                    if(node.right != null) even.push(node.right);
                }
            }else{
                while(!even.empty()){
                    TreeNode node = even.pop();
                    list.add(node.val);
                    if(node.right != null) odd.push(node.right);
                    if(node.left != null) odd.push(node.left);
                }
            }
            result.add(list);
            layer++;   
        }
        return result;
    } 
}
```
 
### 60.把二叉树打印成多行
 
从上到下按层打印二叉树，同一层结点从左至右输出。每一层输出一行。
 
注意要使用isEmpty()
 
```java
import java.util.ArrayList;
import java.util.LinkedList;
public class Solution {
    ArrayList<ArrayList<Integer>> Print(TreeNode pRoot) {
        ArrayList<ArrayList<Integer>> result = new ArrayList<>();
        if(pRoot == null) return result;
        LinkedList<TreeNode> queue = new LinkedList<>();
        ArrayList<Integer> list = new ArrayList<>();
        queue.offer(pRoot);//将根节点加入队列
        int elementsCount = 1;//用于记录每一层的元素个数
        while(!queue.isEmpty()){//注意LinkedList 是没有 enpty()方法的。
            TreeNode node = queue.poll();
            elementsCount--;
            list.add(node.val);
            if(node.left != null) queue.offer(node.left);
            if(node.right != null) queue.offer(node.right);
            if(elementsCount == 0){
                result.add(list);
                list = new ArrayList<>();
                elementsCount = queue.size();
            }
        }
        return result;
    }
}
```
 
### 61.序列化二叉树
 
请实现两个函数，分别用来序列化和反序列化二叉树
 
```java
/*
public class TreeNode {
    int val = 0;
    TreeNode left = null;
    TreeNode right = null;

    public TreeNode(int val) {
        this.val = val;

    }

}
*/
public class Solution {
    String Serialize(TreeNode root) {
        StringBuilder sb = new StringBuilder();
        if(root == null)
            sb.append("$,");
        else{
            sb.append(root.val+",");
            sb.append(Serialize(root.left));
            sb.append(Serialize(root.right));
        }
        return sb.toString();
  }
    int index = -1;
    TreeNode Deserialize(String str) {
        if(str == null || str == "") return null;
        String[] strArray = str.split(",");
        if(strArray.length == 0) return null;
        return DeserializeCore(strArray);
   }
    TreeNode DeserializeCore(String[] strArray){     
        TreeNode node = null;
        index++;
        if(!strArray[index].equals("$")){
            node = new TreeNode(Integer.parseInt(strArray[index]));
            node.left = DeserializeCore(strArray);
            node.right = DeserializeCore(strArray);
        }
        return node;
    }
}
```
 
### 62.二叉搜索树的第K个结点
 
给定一颗二叉搜索树，请找出其中的第k大的结点。例如， 5 /  3 7 / / 2 4 6 8 中，按结点数值大小顺序第三个结点的值为4。(换句话说，从小到大排列，第k个数字)
 
```java
import java.util.ArrayList;
public class Solution {
    ArrayList<TreeNode> list = new ArrayList<>();
    TreeNode KthNode(TreeNode pRoot, int k)
    {
        if(k < 1 || pRoot == null) return null;
        LDR(pRoot);
        if(list.size() < k) return null;
        return list.get(k-1);
    }
    
    void LDR(TreeNode pRoot){
        if(pRoot.left != null)
            LDR(pRoot.left);
        list.add(pRoot);
        if(pRoot.right!=null)
            LDR(pRoot.right);
    }
}
```
 
### 63.数据流中的中位数
 
如何得到一个数据流中的中位数？如果从数据流中读出奇数个数值，那么中位数就是所有数值排序之后位于中间的数值。如果从数据流中读出偶数个数值，那么中位数就是所有数值排序之后中间两个数的平均值。
 
#### 题目解析：如果直接使用ArrayList每次进行排序再选取中位数的话，时间复杂度为O(n^2logn),每一次排序O(nlogn)，共进行N次排序；而使用最大堆、最小堆操作，每次插入数据，取出数据均占用O（logn）的时间，所以总共占用时间复杂度为O(NlogN)
 
```java
import java.util.PriorityQueue;
import java.util.Comparator;
public class Solution {
    PriorityQueue<Integer> minHeap = new PriorityQueue<>();
    PriorityQueue<Integer> maxHeap = new PriorityQueue<>(new Comparator<Integer>(){
        @Override
        public int compare(Integer i1,Integer i2){
            return i2-i1;
        }
    });
    public void Insert(Integer num) {
        minHeap.offer(num);
        if(minHeap.size()>maxHeap.size()){
            maxHeap.offer(minHeap.poll());
        }else{
            maxHeap.offer(minHeap.poll());
            minHeap.offer(maxHeap.poll());
        }
    }
    public Double GetMedian() {
        if(minHeap.size()==0&&maxHeap.size()==0)
            return null;
        if(minHeap.size() == maxHeap.size())
            return (double)(minHeap.peek()+maxHeap.peek())/2.0;
        return (double)maxHeap.peek();
    }
}
```
 
### 64.滑动窗口的最大值
 
给定一个数组和滑动窗口的大小，找出所有滑动窗口里数值的最大值。例如，如果输入数组{2,3,4,2,6,2,5,1}及滑动窗口的大小3，那么一共存在6个滑动窗口，他们的最大值分别为{4,4,6,6,6,5}； 针对数组{2,3,4,2,6,2,5,1}的滑动窗口有以下6个： {[2,3,4],2,6,2,5,1}， {2,[3,4,2],6,2,5,1}， {2,3,[4,2,6],2,5,1}， {2,3,4,[2,6,2],5,1}， {2,3,4,2,[6,2,5],1}， {2,3,4,2,6,[2,5,1]}。
 
```java
import java.util.LinkedList; 
import java.util.ArrayList;
public class Solution {
    public ArrayList<Integer> maxInWindows(int [] num, int size)
    {
        ArrayList<Integer> result = new ArrayList<>();
        if(num.length<1||size<1||size>num.length)
            return result;
        LinkedList<Integer> deque = new LinkedList<>();
        for(int i = 0;i<num.length;i++){
            while(!deque.isEmpty() && num[deque.peekLast()] <= num[i])
                deque.pollLast();
            deque.offerLast(i);
            if(i>=size-1){
                while(i-deque.peekFirst()>size-1)
                    deque.pollFirst();
                result.add(num[deque.peekFirst()]);
            }
        }
        return result;
    }
}
```
 
### 65.矩阵中的路径
 
请设计一个函数，用来判断在一个矩阵中是否存在一条包含某字符串所有字符的路径。路径可以从矩阵中的任意一个格子开始，每一步可以在矩阵中向左，向右，向上，向下移动一个格子。如果一条路径经过了矩阵中的某一个格子，则该路径不能再进入该格子。 例如 a b c e s f c s a d e e 矩阵中包含一条字符串"bcced"的路径，但是矩阵中不包含"abcb"路径，因为字符串的第一个字符b占据了矩阵中的第一行第二个格子之后，路径不能再次进入该格子。
 
```java
public class Solution {
    public boolean hasPath(char[] matrix, int rows, int cols, char[] str)
    {    
        if(matrix == null || rows<1 || cols<1 || str == null) return false;
        boolean[][] visited = new boolean[rows][cols];
        int pathLength = 0;
        for(int row = 0;row<rows;row++)
            for(int col = 0 ;col<cols;col++){
                if(hasPathCore(matrix,rows,cols,row,col,str,visited,pathLength))
                    return true;
            }
        return false;
    }
    public boolean hasPathCore(char[] matrix,int rows,int cols,int row,int col,char[] str,boolean[][] visited,int pathLength){
        if(pathLength == str.length) return true;
        boolean hasPath = false;
        if(row>=0 && col>=0 && row<rows && col<cols && visited[row][col]==false && matrix[row*cols+col] == str[pathLength]){
            pathLength++;
            visited[row][col] = true;
            hasPath = hasPathCore(matrix,rows,cols,row+1,col,str,visited,pathLength)
                ||hasPathCore(matrix,rows,cols,row-1,col,str,visited,pathLength)
                ||hasPathCore(matrix,rows,cols,row,col+1,str,visited,pathLength)
                ||hasPathCore(matrix,rows,cols,row,col-1,str,visited,pathLength);
            if(!hasPath){
                pathLength--;
                visited[row][col] = false;
            }     
        }
        return hasPath;
    }
}
```
 
### 66.机器人的运动范围
 
地上有一个m行和n列的方格。一个机器人从坐标0,0的格子开始移动，每一次只能向左，右，上，下四个方向移动一格，但是不能进入行坐标和列坐标的数位之和大于k的格子。 例如，当k为18时，机器人能够进入方格（35,37），因为3+5+3+7 = 18。但是，它不能进入方格（35,38），因为3+5+3+8 = 19。请问该机器人能够达到多少个格子？
 
```java
public class Solution {
    public int movingCount(int threshold, int rows, int cols) {
        if (threshold < 1 || rows < 1 || cols < 1) return 0;
        boolean[][] visited = new boolean[rows][cols];
        return movingCountCore(threshold, 0, 0, rows, cols, visited);

    }

    public int movingCountCore(int threshold, int row, int col, int rows, int cols, boolean[][] visited) {
        int count = 0;
        if (check(threshold, row, col, rows, cols, visited)) {
            visited[row][col] = true;
            count = 1 + movingCountCore(threshold, row + 1, col, rows, cols, visited)
                    + movingCountCore(threshold, row - 1, col, rows, cols, visited)
                    + movingCountCore(threshold, row, col + 1, rows, cols, visited)
                    + movingCountCore(threshold, row, col - 1, rows, cols, visited);
        }
        return count;

    }

    public boolean check(int threshold, int row, int col, int rows, int cols, boolean[][] visited) {
        if (row < 0 || col < 0 || row >= rows || col >= cols || visited[row][col])
            return false;
        int num = 0;
        while (col != 0 || row != 0) {
            num += col % 10;
            num += row % 10;
            col /= 10;
            row /= 10;
        }
        if (num > threshold)
            return false;
        return true;
    }

}
```
 


[0]: https://img0.tuicool.com/BVFbYr2.png 
[1]: https://img1.tuicool.com/VzEruqa.png 
[2]: https://img1.tuicool.com/MVJNVre.png 
[3]: https://img0.tuicool.com/ZVFVRfR.png 