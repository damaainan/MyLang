## Javascript数组的5种迭代方法

来源：[http://www.cnblogs.com/hh1017/p/9452512.html](http://www.cnblogs.com/hh1017/p/9452512.html)

时间 2018-08-09 23:38:00



## #Javascript数组的5种迭代方法

数组当中定义了5个迭代方法，传入这些方法中的函数会接受三个参数，数组项的值，该项在数组的位置，和数组对象本身，以下是5个迭代方法的作用。


### 1、every方法：

对数组中的每一项运行给定函数，如果该函数对每一项都返回true，则返回true。

```js
let arr1 = [1,2,3,4,5,6];
let arr2 = [-1,-2,-3,-4,-5,-6];
let every1 = arr1.every((item,index,arr)=>{
    return item>0
})
let every2 = arr2.every((item,index,arr)=>{
    return item>0
})
console.log(every1,every2);//true,false
```


### 2、filter方法

对数组中的每一项运行给定函数，返回该函数返回true的项组成的数字

```js
let arr1 = [-1,-2,-3,4,5,6];
let arr2 = [1,2,3,-4,-5,-6];
let filter1 = arr1.filter(item=>{
    return item>0
})
let filter2 = arr2.filter((item)=>{
    return item<0
})
console.log(filter1,filter2);//[4,5,6],[-4,-5,-6]
```


### 3、some方法

对数组中的每一项运行给定函数，如果该函数对任一项返回true，则返回true。

```js
let arr1 = [1,2,3,4,5,6];
let arr2 = [1,2,3,-4,-5,-6];
let some1= arr1.some(item=>{
    return item>0
})
let some2 = arr2.some((item)=>{
    return item>0
})
console.log(some1,some2);//true,true
```


### 4、forEach方法


对数组中的每一项运行给定函数，这个方法没有返回值。

forEach无法遍历对象

forEach无法在IE中使用，只是在firefox和chrome中实现了该方法

```js
let arr1 = [1,2,3,4,5,6];
let arr2 = [1,2,3,-4,-5,-6];
let forEach1= arr1.forEach(item=>{
    return item++
})
let forEach2 = arr2.forEach((item)=>{
    return item++
})
console.log(forEach1,forEach2);//undefined,undefined
```


### 5、map方法

对数组中的每一项运行给定函数，返回每次调用的结果组成的数组。

```js
let arr1 = [1,2,3,4,5,6];
let arr2 = [-1,-2,-3,-4,-5,-6];
let map1 = arr1.map(item=>{
    return ++item
})
let map2 = arr2.map((item)=>{
    return ++item
})
console.log(map1,map2);//[2, 3, 4, 5, 6, 7] (6) [0, -1, -2, -3, -4, -5];
```


开发过程中用的比较常用到的就是map，forEach方法，他们是比较相似却也有不小的区别。

主要在于：

1、map方法是有返回值的，而forEach是没有的。

2、IE浏览器不支持forEach方法，所以要兼容IE浏览器的尽量不要使用forEach去遍历。

3、map方法的速度快于forEach。

  
