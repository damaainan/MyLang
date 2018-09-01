## 7种方法实现数组去重

来源：[https://juejin.im/post/5aed6110518825671b026bed](https://juejin.im/post/5aed6110518825671b026bed)

时间 2018-05-08 12:06:33


去重是开发中经常会碰到的一个热点问题，不过目前项目中碰到的情况都是后台接口使用SQL去重，简单高效，基本不会让前端处理去重。

那么前端处理去重会出现什么情况呢？假如每页显示10条不同的数据，如果数据重复比较严重，那么要显示10条数据，可能需要发送多个http请求才能够筛选出10条不同的数据，而如果在后台就去重了的话，只需一次http请求就能够获取到10条不同的数据。

当然，这并不是说前端去重就没有必要了，依然需要会熟练使用。本文主要介绍几种常见的数组去重的方法。


## 方法实现


### 双循环去重

双重for（或while）循环是比较笨拙的方法，它实现的原理很简单：先定义一个包含原始数组第一个元素的数组，然后遍历原始数组，将原始数组中的每个元素与新数组中的每个元素进行比对，如果不重复则添加到新数组中，最后返回新数组；因为它的时间复杂度是O(n^2)，如果数组长度很大，那么将会非常耗费内存

```LANG
function unique(arr) {
    if (!Array.isArray(arr)) {
        console.log('type error!')
        return
    }
    let res = [arr[0]]
    for (let i = 1; i < arr.length; i++) {
        let flag = true
        for (let j = 0; j < res.length; j++) {
            if (arr[i] === res[j]) {
                flag = false;
                break
            }
        }
        if (flag) {
            res.push(arr[i])
        }
    }
    return res
}
```


### indexOf方法去重1

数组的indexOf()方法可返回某个指定的元素在数组中首次出现的位置。该方法首先定义一个空数组res，然后调用indexOf方法对原来的数组进行遍历判断，如果元素不在res中，则将其push进res中，最后将res返回即可获得去重的数组

```LANG
function unique(arr) {
    if (!Array.isArray(arr)) {
        console.log('type error!')
        return
    }
    let res = []
    for (let i = 0; i < arr.length; i++) {
        if (res.indexOf(arr[i]) === -1) {
            res.push(arr[i])
        }
    }
    return res
}
```


### indexOf方法去重2

利用indexOf检测元素在数组中第一次出现的位置是否和元素现在的位置相等，如果不等则说明该元素是重复元素

```LANG
function unique(arr) {
    if (!Array.isArray(arr)) {
        console.log('type error!')
        return
    }
    return Array.prototype.filter.call(arr, function(item, index){
        return arr.indexOf(item) === index;
    });
}
```


### 相邻元素去重

这种方法首先调用了数组的排序方法sort()，然后根据排序后的结果进行遍历及相邻元素比对，如果相等则跳过改元素，直到遍历结束

```LANG
function unique(arr) {
    if (!Array.isArray(arr)) {
        console.log('type error!')
        return
    }
    arr = arr.sort()
    let res = [arr[0]]
    for (let i = 1; i < arr.length; i++) {
        if (arr[i] !== arr[i-1]) {
            res.push(arr[i])
        }
    }
    return res
}
```


### 利用对象属性去重

创建空对象，遍历数组，将数组中的值设为对象的属性，并给该属性赋初始值1，每出现一次，对应的属性值增加1，这样，属性值对应的就是该元素出现的次数了

```LANG
function unique(arr) {
    if (!Array.isArray(arr)) {
        console.log('type error!')
        return
    }
    let res = [],
        obj = {}
    for (let i = 0; i < arr.length; i++) {
        if (!obj[arr[i]]) {
            res.push(arr[i])
            obj[arr[i]] = 1
        } else {
            obj[arr[i]]++
        }
    }
    return res
}
```


### set与解构赋值去重

ES6中新增了数据类型set，set的一个最大的特点就是数据不重复。Set函数可以接受一个数组（或类数组对象）作为参数来初始化，利用该特性也能做到给数组去重

```LANG
function unique(arr) {
    if (!Array.isArray(arr)) {
        console.log('type error!')
        return
    }
    return [...new Set(arr)]
}
```


### Array.from与set去重

Array.from方法可以将Set结构转换为数组结果，而我们知道set结果是不重复的数据集，因此能够达到去重的目的

```LANG
function unique(arr) {
    if (!Array.isArray(arr)) {
        console.log('type error!')
        return
    }
    return Array.from(new Set(arr))
}
```


## 总结

数组去重是开发中经常会碰到的一个热点问题。我们可以根据不同的应用场景来选择不同的实现方式。

