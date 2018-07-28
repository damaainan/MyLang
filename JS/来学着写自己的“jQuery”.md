## 来学着写自己的“jQuery”

来源：[https://juejin.im/post/5b0648d7f265da0dc618e1b2](https://juejin.im/post/5b0648d7f265da0dc618e1b2)

时间 2018-05-24 18:11:11



jQuery是一套跨浏览器的JavaScript库，简化HTML与JavaScript之间的操作

jQuery是开源软件，使用MIT许可证授权。jQuery的语法设计使得许多操作变得容易，如操作文档对象（document）、选择文档对象模型（DOM）元素、创建动画效果、处理事件、以及开发Ajax程序。jQuery也提供了给开发人员在其上创建插件的能力。这使开发人员可以对底层交互与动画、高级效果和高级主题化的组件进行抽象化。模块化的方式使jQuery函数库能够创建功能强大的动态网页以及网络应用程序

实际上jQuery可以看做将原生JavaScript库组合优化，通过调用不同的原生API进行二次开发，以实现比原生JavaScript的API更为简单、强大的功能。如果jQuery的功能没攘括你的需求，那么你可以自己写个jQuery的函数来满足自己的需求哦，下面来学习下如何封装一个“jQuery”函数

  
## 1 怎样封装函数才好

当我们需要自己封装一个函数时，可以直接将函数写进Node.prototype里面，也可以重新创建一个新的接口，那么这两者有什么区别呢？



* 方法一：拓展Node接口
可以直接在Node.prototype上加我们所需要的函数，但是这种方法有个缺点，如果我们的函数名已经在Node库里面存在了，那么新函数就会覆盖已经存在的函数，会导致已有函数失效，这显然不是我们乐意看到的

    
* 方法二：写个新的接口
重新创建一个接口，在新的接口里面写函数，这种方法既不会覆盖已有函数，又可以满足我们的需求，所以我们采取这种方式来封装函数

    
  


## 2 来写一个jQuery


### 2.1 选择器

当我们传入一个筛选条件时，我们希望能获取满足筛选条件的所有节点，这里要分情况来讨论了

  

如果筛选条件是一个节点，那么直接返回这个节点即可

如果筛选条件是一个字符串，那么就调用JavaScript的选择器，筛选所有符合字符串的节点

    
这里有小细节要处理一下，通过JavaScript选择器获取的是一个由符合条件的节点组成的伪数组，里面不仅包含了节点信息，还有一些其他内容

且筛选条件是一个节点的话，那么返回的就不是个伪数组了

为了保证结果的统一性，需要将伪数组里面的其他信息清除，如果结果不是伪数组，就将它变成一个伪数组

      

代码实现如下

```js
let nodes = {};
  if(typeof nodeOrSelector === 'string'){
    let temp = document.querySelectorAll(nodeOrSelector);
    for(let i = 0; i < temp.length; i++){
      nodes[i]=temp[i];
    }
    nodes.length = temp.length;
  }else if(nodeOrSelector instanceof Node){
    nodes = {
      0 : nodeOrSelector,
      length : 1
    };
  }
```


### 2.2 写一个addClass()函数
`addClass()`函数的用途是将所选择的元素的`class`属性增加新内容

那么遍历所选择的元素，通过原生JavaScript里面的`classList.add()`函数即可是实现
代码实现如下

```js
nodes.addClass = function(classes){
      for(let i = 0; i < nodes.length; i++){
        nodes[i].classList.add(classes);
      }
  };
```


### 2.3 再写一个setText()函数

我们通过`setText()`函数需要实现将元素的`textContent`内容改写成指定内容

同样的思路，遍历元素，逐个将`textContent`改写

代码实现如下

```js
nodes.setText = function(texts){
      for(let i = 0; i < nodes.length; i++){
        nodes[i].textContent = texts;
      }
  };
```


### 2.4 组合一下吧

各个部分完成之后，就可以将其组合封装成jQuery函数了

代码如下

```js
window.jQuery = function(nodeOrSelector){
  //筛选元素
  let nodes = {};
  if(typeof nodeOrSelector === 'string'){
    let temp = document.querySelectorAll(nodeOrSelector);
    for(let i = 0; i < temp.length; i++){
      nodes[i]=temp[i];
    }
    nodes.length = temp.length;
  }else if(nodeOrSelector instanceof Node){
    nodes = {
      0 : nodeOrSelector,
      length : 1
    };
  }
  //增加class属性函数
  nodes.addClass = function(classes){
      for(let i = 0; i < nodes.length; i++){
        nodes[i].classList.add(classes);
      }
  };
  //改写textContent内容函数
  nodes.setText = function(texts){
      for(let i = 0; i < nodes.length; i++){
        nodes[i].textContent = texts;
      }
  };  
  //返回操作之后的内容
  return nodes;
}
```


## 3 总结

jQuery没想象中的那么遥不可及，通过封装函数，我们也可以写一个自己的“jQuery”来实现我们自己需求


