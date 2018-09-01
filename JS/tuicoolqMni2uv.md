## JS中最简单且最强大的数组去重

来源：[http://www.jianshu.com/p/94668f8ec1a1](http://www.jianshu.com/p/94668f8ec1a1)

时间 2018-05-15 20:38:46


数组去重的机制中必须要有2次循环，但，这并不意味着必须要有若干for循环的显性代码，通过数组的自身的方法，可以大大简化代码；下面就是我写的最简单且最强大的数组去重方法：

  
## 目录


* 一、最简单的数组去重
* 二、最简单且最强大的数组去重
    

  
## 内容

  
## 一、最简单的数组去重

  
#### 方案1:通过Set

```LANG
[...new Set(array)]
```

  
#### 方案2:通过数组

```LANG
let noRepeats = arr.filter((item,index)=>{index === arr.indexOf(item)});
```

简化后的箭头函数可能会让人不易懂，下面是等效的非箭头函数版：

```LANG
let noRepeats = arr.filter(function(item,index){
    return  index === arr.indexOf(item);
});
```

优点：与用 for 循环方式实现，这2种方式有以下优点：


* 更易读；
* 代码量小；
* 不用创建额外的临时变量；
* 性能稍微更快；
    

  
#### 注意:


* 该方法不改原数组，会返回一个新的数组；
* 该方法是通过 严格相等`===`运算符来判断 数组的元素是否重复的；      
    

  
#### 在数组原型上添加该方法

```LANG
/* 
获取去除重复项目后的数组

## 注意
- 该方法不改原数组，会返回一个新的数组；
- 该方法是通过 严格相等 `===` 运算符来判断 数组的元素是否重复的；
*/

Array.prototype.getNoRepeats = function (){

    return this.filter(function(currentItem,index,arr){
        return  index === arr.indexOf(currentItem);
    });
    
}
```

  
## 二、最简单且最强大的数组去重

上面的方法是通过 严格相等`===`运算符来判断 数组的元素是否重复的，在这种情况下，对于对象类型的数组元素，只有当2个元素的引用的是同一对象时，才会被认为是重复的； 然而，在很多时候，我们可能需要根据自己的规则来判断是否重复，如：对于联系人数据对象`{id:number,name:string}`，我们可以会根据`id`是否一致来判断是否重复；

下面的去复方法支持自定义的重复规则：

```LANG
/**
根据重复测试函数 `isRepeated` 来获取去除重复项目后的新数组

- @param isRepeated  : (item1,item2)=> boolean      重复油测试函数，传入被测试的2个项目，返回布尔值，表示这2个项目是否是重复的；
- @returns : Array  返回去除重复项目后的新数组

## 注意
- 该方法不改原数组，会返回一个新的数组；
- 该方法是通过 isRepeated 函数来判断 数组的元素是否重复的；
 */

Array.prototype.getNoRepeatsUseRepeatTest = function (isRepeated){

    return this.filter(function(currentItem,index,arr){
        return index === arr.findIndex(function(findItem){
            return isEquality(findItem,currentItem);
        });
    });

}
```

方法`getNoRepeatsUseRepeatTest(isRepeated)`是根据重复测试函数`isRepeated`来获取去除重复项目后的新数组； 测试函数`isRepeated`是`(item1,item2)=> boolean`类型的，即：`isRepeated(item1,item2)`会接收2个元素作为参数，返回一个表示这2个元素是否是重复的布尔值；

  
#### 注意:


* 该方法不改原数组，会返回一个新的数组；
* 该方法是通过 isRepeated 函数来判断 数组的元素是否重复的；
    

