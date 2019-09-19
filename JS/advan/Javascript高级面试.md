## Javascript高级面试

来源：[https://segmentfault.com/a/1190000017498782](https://segmentfault.com/a/1190000017498782)

//## 原型
## 异步
#### 一、什么是单线程，和异步有什么关系

单线程：只有一个线程，同一时间只能做一件事
原因：避免DOM渲染的冲突解决方案：异步

为什么js只有一个线程：避免DOM渲染冲突

* 浏览器需要渲染DOM
* JS可以修改DOM结构
* JS执行的时候，浏览器DOM渲染会暂停
* 两端JS也不能同时执行(都修改DOM就冲突了)
* webworker支持多线程，但是不能访问DOM



解决方案存在的问题

* 问题一：没按照书写方式执行，可读性差
* 问题二：callback中不容易模块化


#### 二、什么是event-loop


* 事件轮询，JS实现异步的具体解决方案
* 同步代码，直接执行
* 异步函数先放在异步队列中
* 待同步函数执行完毕，轮询执行异步队列的函数


```js
setTimeout(function(){
    console.log(1);
},100);              //100ms之后才放入异步队列中，目前异步队列是空的
setTimeout(function(){
    console.log(2);  //直接放入异步队列
})
console.log(3)       //直接执行

//执行3之后，异步队列中只有2，把2拿到主线程执行，2执行完之后，异步队列中并没有任务，所以一直轮询异步队列，直到100ms之后1放入异步队列，将1拿到主线程中执行
```

```js
$.ajax({
    url:'./data.json',
    success:function(){        //网络请求成功就把success放入异步队列
        console.log('a');
    }
})

setTimeout(function(){
    console.log('b')
},100)

setTimeout(function(){
    console.log('c');
})
console.log('d')

//打印结果：
//d    //d   
//c    //c  
//a    //b   
//b    //a   

//真实环境不会出现dacb
```
#### 三、是否用过jQuery的Deferred


* jQuery1.5的变化
* 使用jQuery Deferred
* 初步引入Promise概念



jQuery1.5之前
```js
var ajax = $.ajax({
    url:'./data.json',
    success:function(){
        console.log('success1');
        console.log('success2');
        console.log('success3');
    },
    error:function(){
        console.log('error');
    }
})
console.log(ajax); //返回一个XHR对象
```

jQuery1.5之后
```js
var ajax = $.ajax('./data.json');
ajax.done(function(){
    console.log('success1')
})
.fai(function(){
    console.log('fail')
})
.done(function(){
    console.log('success2');
})
console.log(ajax); //deferred对象
```

```js
var ajax = $.ajax('./data.json');
ajax.then(function(){
    console.log('success1')
},function(){
    console.log('error1');
})
.then(function(){
    console.log('success2');
},function(){
    console.log('error');
})

//使用
var w = waithandle()
w.then(function(){
    console.log('ok1');
},function(){
    console.log('err2');
})
.then(function(){
    console.log('ok2');
},function(){
    console.log('err2');
})
//还有w.wait w.fail
```


* 无法改变JS异步和单线程的本质
* 只能从写法上杜绝callback这种形式
* 它是一种语法糖，但是解耦了代码
* 很好的提现：开放封闭原则(对扩展开放对修改封闭)

##### 使用jQuery Deferred

```js
//给出一段非常简单的代码，使用setTimeout函数
var wait = function(){
    var task = function(){
        console.log('执行完成');
    }
    setTimeout(task,2000)
}

wait();

//新增需求：要在执行完成之后进行某些特别复杂的操作，代码可能会很多，而且分好几个步骤
```

```js
function waitHandle(){
    var dtd = $.Deferred();//创建一个deferred对象
    
    var wait = function(dtd){  // 要求传入一个deferred对象
        var task = function(){
            console.log("执行完成");
            dtd.resolve();  //表示异步任务已完成
            //dtd.reject() // 表示异步任务失败或者出错
        };
        setTimeout(task,2000);
        return dtd;
    }
    //注意，这里已经要有返回值
    return wait(dtd);
}
/*
*总结：dtd的API可分成两类，用意不同
*第一类：dtd.resolve  dtd.reject
*第二类：dtd.then  dtd.done  dtd.fail

*这两类应该分开，否则后果严重！
*可以在上面代码中最后执行dtd.reject()试一下后果
*/

```
##### 使用dtd.promise()

```js
function waitHandle(){
    var dtd = $.Deferred();
    var wait = function(){
        var task = function(){
            console.log('执行完成');
            dtd.resolve();
        }
        setTimeout(task,2000)
        return dtd.promise();  //注意这里返回的是promise，而不是直接返回deferred对象
    }
    return wait(dtd)
}


var w = waitHandle();   //promise对象
$.when(w).then(function(){
    console.log('ok1');
},function(){
    console.log('err1');
})
/*
只能被动监听，不能干预promise的成功和失败
*/
```


* 可以jQuery1.5对ajax的改变举例
* 说明如何简单的封装、使用deferred
* 说明promise和Defrred的区别

要想深入了解它，就需要知道它的前世今生
#### 四、Promise的基本使用和原理
##### 基本语法回顾

##### 异常捕获

//规定：then只接受一个函数，最后统一用catch捕获异常
##### 多个串联

```js
var scr1 = 'https://www.imooc.com/static/img/index/logo_new.png';
var result1 = loadImg(src1);
var src2 = 'https://www.imooc.com/static/img/index/logo_new.png';
var result2 = loadImg(src2);

result1.then(function(img1) {
    console.log('第一个图片加载完成', img1.width);
    return result2;
}).then(function(img2) {
    console.log('第二个图片加载完成', img2.width);
}).catch(function(ex) {
    console.log(ex);
})
```
##### Promise.all和Promise.race

```js
//Promise.all接收一个promise对象的数组
//待全部完成后，统一执行success
Promise.all([result1, result2]).then(datas => {
        //接收到的datas是一个数组，依次包含了多个promise返回的内容
        console.log(datas[0]);
        console.log(datas[1]);
})
   
//Promise.race接收一个包含多个promise对象的数组
//只要有一个完成，就执行success
Promise.race([result1, result2]).then(data => {
    //data即最先执行完成的promise的返回值
    console.log(data);
})
```
##### Promise标准


* 三种状态：pending,fulfilled,rejected
* 初始状态：pending
* pending变为fulfilled,或者pending变为rejected
* 状态变化不可逆

promise必须实现then这个方法
then()必须接收两个函数作为标准
then
#### 五、介绍一下async/await(和Promise的区别、联系)

#### 六、总结一下当前JS结局异步的方案

## 虚拟DOM
### vdom 是什么？为何会存在 vdom？

 **`什么是vdom`**

* virtual dom,虚拟DOM
* 用JS模拟DOM结构
* DOM变化的对比，放在JS层来做(图灵完备语言:能实现各种逻辑的语言)
* 提高重绘性能


 **`DOM`** 
```js

* Item 1
* Item 2


```

 **`虚拟DOM`** 
```js
{
    tag: 'ul',
    attrs: {
        id: 'list'
    },
    children: [{
            tag: 'li',
            attrs: { className: 'item' },
            children: ['item1']
        },
        {
            tag: 'li',
            attrs: { className: 'item' },
            children: ['item2']
        }
    ]
}

//className代替class,因为class是js的保留字
```

浏览器最耗费性能就是DOM操作，DOM操作非常昂贵
现在浏览器执行JS速度非常快
这就是vdom存在的原因

 **`一个需求场景`** 
```js
//将该数据展示成一个表格
//随便修改一个信息，表格也随着修改
[
    {
        name: 'zhangsan',
        age: 20,
        address: 'beijing'
    },
    {
        name: 'lisi',
        age: 21,
        address: 'shanghai'
    },
    {
        name: 'wangwu',
        age: 22,
        address: 'guangzhou'
    }
]
```

 **`用`jQery`实现`** 
```js
//渲染函数
funciton render(data) {
    //此处省略n行
}

//修改信息
$('#btn-change').click(function(){
    data[1].age = 30;
    data[2].address = 'shenzhen';
    render(data);
})


//初始化时渲染
render(data)
```

```js
//render函数具体写法
function render(data) {
    $container = $("#container");
    //清空现有内容
    $container.html('');
    //拼接table
    var $table = $('
')
    $table.append($('| name | age | address |'))
    data.forEach(item => {
        $table.append($('| ' + item.name + ' | ' + item.age + ' | ' + item.address + ' |'))
        $container.append($table)
    });

}

//只执行了一次渲染，相对来说还是比较高效的
//DOM渲染是最昂贵的，只能尽量避免渲染
```

 **`遇到的问题`**

* DOM操作是“昂贵”的，JS运行效率高
* 尽量减少DOM操作，而不是"推倒重来"(清空重置)
* 项目越复杂，影响就越严重
* vdom可解决这个问题


```js
var div = document.createElement('div');
var item,result = '';
for(item in div){
    result += '|' + item;
}
console.log(result);

//浏览器默认创建出来的DOM节点，属性是非常多的

//result
|align|title|lang|translate|dir|dataset|hidden|tabIndex|accessKey|draggable|spellcheck|autocapitalize|contentEditable|isContentEditable|inputMode|offsetParent|offsetTop|offsetLeft|offsetWidth|offsetHeight|style|innerText|outerText|onabort|onblur|oncancel|oncanplay|oncanplaythrough|onchange|onclick|onclose|oncontextmenu|oncuechange|ondblclick|ondrag|ondragend|ondragenter|ondragleave|ondragover|ondragstart|ondrop|ondurationchange|onemptied|onended|onerror|onfocus|oninput|oninvalid|onkeydown|onkeypress|onkeyup|onload|onloadeddata|onloadedmetadata|onloadstart|onmousedown|onmouseenter|onmouseleave|onmousemove|onmouseout|onmouseover|onmouseup|onmousewheel|onpause|onplay|onplaying|onprogress|onratechange|onreset|onresize|onscroll|onseeked|onseeking|onselect|onstalled|onsubmit|onsuspend|ontimeupdate|ontoggle|onvolumechange|onwaiting|onwheel|onauxclick|ongotpointercapture|onlostpointercapture|onpointerdown|onpointermove|onpointerup|onpointercancel|onpointerover|onpointerout|onpointerenter|onpointerleave|nonce|click|focus|blur|namespaceURI|prefix|localName|tagName|id|className|classList|slot|attributes|shadowRoot|assignedSlot|innerHTML|outerHTML|scrollTop|scrollLeft|scrollWidth|scrollHeight|clientTop|clientLeft|clientWidth|clientHeight|attributeStyleMap|onbeforecopy|onbeforecut|onbeforepaste|oncopy|oncut|onpaste|onsearch|onselectstart|previousElementSibling|nextElementSibling|children|firstElementChild|lastElementChild|childElementCount|onwebkitfullscreenchange|onwebkitfullscreenerror|setPointerCapture|releasePointerCapture|hasPointerCapture|hasAttributes|getAttributeNames|getAttribute|getAttributeNS|setAttribute|setAttributeNS|removeAttribute|removeAttributeNS|hasAttribute|hasAttributeNS|toggleAttribute|getAttributeNode|getAttributeNodeNS|setAttributeNode|setAttributeNodeNS|removeAttributeNode|closest|matches|webkitMatchesSelector|attachShadow|getElementsByTagName|getElementsByTagNameNS|getElementsByClassName|insertAdjacentElement|insertAdjacentText|insertAdjacentHTML|requestPointerLock|getClientRects|getBoundingClientRect|scrollIntoView|scrollIntoViewIfNeeded|animate|computedStyleMap|before|after|replaceWith|remove|prepend|append|querySelector|querySelectorAll|webkitRequestFullScreen|webkitRequestFullscreen|scroll|scrollTo|scrollBy|createShadowRoot|getDestinationInsertionPoints|ELEMENT_NODE|ATTRIBUTE_NODE|TEXT_NODE|CDATA_SECTION_NODE|ENTITY_REFERENCE_NODE|ENTITY_NODE|PROCESSING_INSTRUCTION_NODE|COMMENT_NODE|DOCUMENT_NODE|DOCUMENT_TYPE_NODE|DOCUMENT_FRAGMENT_NODE|NOTATION_NODE|DOCUMENT_POSITION_DISCONNECTED|DOCUMENT_POSITION_PRECEDING|DOCUMENT_POSITION_FOLLOWING|DOCUMENT_POSITION_CONTAINS|DOCUMENT_POSITION_CONTAINED_BY|DOCUMENT_POSITION_IMPLEMENTATION_SPECIFIC|nodeType|nodeName|baseURI|isConnected|ownerDocument|parentNode|parentElement|childNodes|firstChild|lastChild|previousSibling|nextSibling|nodeValue|textContent|hasChildNodes|getRootNode|normalize|cloneNode|isEqualNode|isSameNode|compareDocumentPosition|contains|lookupPrefix|lookupNamespaceURI|isDefaultNamespace|insertBefore|appendChild|replaceChild|removeChild|addEventListener|removeEventListener|dispatchEvent
```
### vdom如何应用，核心API是什么

 **`介绍`snabbdom``** 一个实现`vdom`的库,vue升级2.0借鉴了`snabbdom`的算法

```js
var container = document.getElementById('container')

var vnode = h('div#container.two.classes', { on: { click: someFn } }, [
    h('span', { style: { fontWeight: 'bold' }, 'This is bold' }),
    'and this is just normal text',
    h('a', { props: { href: '/foo' } }, 'I\'ll take you places')
])

//patch into empty DOM element - this modifies the DOM as a side effect
patch(container, vnode)

var newVnode = h('div#container.two.classes', { on: { click: anotherEventHandle } }, [
        h('span', { style: { fontWeight: 'normal', fontStyle: 'italic' } }, 'this is now italic type'),
        'and this is still just normal text',
        h('a', { props: { href: '/bar' } }, 'I\'ll take you places')
    ])
    //send `patch` invocation

patch(vnode, newVnode); //Snabbdom efficiently updates the old view to the new state
```

 **`h函数`** 
```js
{
    tar: 'ul',
    attrs: {
        id: 'list'
    },
    children: [
    {
        tag: 'li',
        attrs: {
            className: 'item',
            children: ['item1']
        }
    },
    {
        tag: 'li',
        attrs: {
            className: 'item'
        },
        children: ['item2']
        }
    ]
}
```

对应的vnode
```js
var vnode = h('ul#list', {}, [
    h('li.item', {}, 'Item1'),
    h('li.item', {}, 'Item')
])

```

 **`patch函数`** 
```js
var vnode = h('ul#list', {}, [
    h('li.item', {}, 'Item1'),
    h('li.item', {}, 'Item2')
])

var container = document.getElementById('container')
patch(container, vnode)

//模拟改变
var btnChange = document.getElementById('btn-change')
btnChange.addEventListener('click', function() {
    var newVnode = h('ul#list', {}, [
        h('li.item', {}, 'Item 111'),
        h('li.item', {}, 'Item 222'),
        h('li.item', {}, 'Item 333')
    ])
    patch(vnode, newVnode)
})
```

```html


<button id="btn-change">change</button>
<script src="https://cdn.bootcss.com/snabbdom/0.7.2/snabbdom.js"></script>
<script src="https://cdn.bootcss.com/snabbdom/0.7.2/snabbdom-class.js"></script>
<script src="https://cdn.bootcss.com/snabbdom/0.7.2/snabbdom-props.js"></script>
<script src="https://cdn.bootcss.com/snabbdom/0.7.2/snabbdom-style.js"></script>
<script src="https://cdn.bootcss.com/snabbdom/0.7.2/snabbdom-eventlisteners.js"></script>
<script src="https://cdn.bootcss.com/snabbdom/0.7.2/h.js"></script>

```

```html
  <script type="text/javascript">
    var snabbdom = window.snabbdom

    //定义patch
    var patch = snabbdom.init([
        snabbdom_class,
        snabbdom_props,
        snabbdom_style,
        snabbdom_eventlisteners
    ])
    //定义h函数
    var h = snabbdom.h

    var container = document.getElementById('container')

    //生成vnode
    var vnode = h('ul#list',{},[
        h('li.list',{},'Item1'),
        h('li.list',{},'Item2'),

    ])
    patch(container,vnode)


    document.getElementById('btn-change').addEventListener('click',function(){
        //生成newVode
        var newVnode = h('ul#list',{},[
            h('li.list',{},'Item1'),
            h('li.item',{},'Item B'),
            h('li.item',{},'Item 3')
        ])
        patch(vnode,newVnode)
    })


    </script>
```

 **`重新实现前面的demo(用`snabbdom`实现)`** 
```js
 var snabbdom = window.snabbdom
    var patch = snabbdom.init([
        snabbdom_class,
        snabbdom_props,
        snabbdom_style,
        snabbdom_eventlisteners
    ])
    var h = snabbdom.h
    var container = document.getElementById('container')
    var btnChange = document.getElementById('btn-change')
    var vnode
    var data = [{
            name: 'zhangsan',
            age: 20,
            address: 'beijing'
        },
        {
            name: 'zhangsan',
            age: 20,
            address: 'shanghai'
        },
        {
            name: 'zhangsan',
            age: 20,
            address: 'shenzhen'
        }
    ]
    
    data.unshift({
        name:'姓名：',
        age:'年龄：',
        address:'地址：'
    })


    render(data);

    function render(data){
        var newVnode = h('table',{},data.map(function(item){
            var tds = [],i
            for(i in item){
                if(item.hasOwnProperty(i)){
                    tds.push(h('td',{},item[i]+''))
                }
            }
            return h('tr',{},tds)
        }))
        if(vnode){
            patch(vnode,newVnode)
        }else{
            patch(container,newVnode)
        }
        vnode = newVnode  //存储当前vnode结果

    }

  
    btnChange.addEventListener('click',function(){
        data[1].age = 30
        data[2].address = '深圳'
        //re-render
        render(data)
    })
```

 **`核心API`**
* h函数的用法

```js
 h('<标签名>',{...属性...},[...子元素...])
 
 h('<标签名>',{...属性...},'...')
```

* patch函数用法

```js
patch(container,vnode) 

patch(vnode,newVnode)  //rerender

```
### 介绍一下diff算法

什么是diff算法`linux`中的diff：找出两个文件中的不同:

```js
diff log1.txt log2.txt
```
`git diff`:修改之前和修改之后版本的差异

```js
git diff xxxx.js
```

网上的一些在线差异化网站

```js
http://tool.oschina.net/diff/
```
`diff`算法并不是`vdom`提出的概念，一直存在
现在应用到`vdom`中，对比的是两个虚拟dom

去繁就简

* `diff`算法非常复杂，实现难度很大，源码量很大
* 去繁就简，讲明白核心流程，不关心细节
* 面试官大部分也不清楚细节，但是很关心核心流程
* 去繁就简之后，依然具有很大的挑战性


vdom为何要使用`diff`

* DOM操作是“昂贵”的，因此尽量减少DOM操作
* 找出本次DOM必须更新的节点来更新，其他的不更新
* “找出”的过程，就需要`diff`算法


`diff`算法实现
`diff`实现的过程
* patch(container,vnode)

如何用vnode生成真实的dom节点

```js
 {
    tag: 'ul',
    attrs: {
        id: 'list'
    },
    children: [
        {
            tag: 'li',
            attrs: {
                className: 'item'
            },
            children:['item 1']
        }
    ]
}
```

```js

* Item 1


```

简单实现算法
```js
function createElement(vnode) {
    var tag = vnode.tag;
    var attrs = vnode.attrs || {};
    var children = vnode.children || [];
    if (!tag) {
        return null
    }
    //创建元素
    var elem = document.createElement(tag);
        //属性
    var attrName;
    for (attrName in atts) {
        if (attrs.hasOwnProperty(attrName)) {
            elem.setAttribute(attrName, attrs[attrName])
        }
    }
    //子元素
    children.array.forEach(childVnode => {
        elem.appendChild(createElement(childVnode))
    });
    return elem;
}
 
```

* patch(vnode,newVnode)

```js
 {
    tag: 'ul',
    attrs: { id: 'list' },
    children: [{
            tag: 'li',
            attrs: { className: 'item' },
            children: ["Item 1"]
        },
        {
            tag: 'li',
            attrs: {
                className: 'item',
                children: ['Item 2']
            }
        }
    ]
}
```

对比：
```js
{
    tag: 'ul',
    attrs: { id: 'list' },
    children: [{
            tag: 'li',
            attrs: { className: 'item' },
            children: ["Item 1"]
        },
        {
            tag: 'li',
            attrs: {
                className: 'item',
                children: ['Item 222']
            }
        },
        {
            tag: 'li',
            attrs: {
                className: 'item',
                children: ['Item 3']
            }
        }
    ]
}
 
```

![][0]

简单实现
```js
 function updateChildren(vnode, newVnode) {
    var children = vnode.children || [];
    var newChildren = newVnode.children || [];

    //遍历现有的children
    children.forEach((child, index) => {
        var newChild = newChildren[index];
        if (newChild == null) {
            return;
        }
        if (child.tag === newChild.tag) {
            updateChildren(child, newChild)
        } else {
            replaceNode(child, newChild)
        }
    });
}
```


* 节点新增和删除
* 节点重新排序
* 节点属性、样式、事件绑定
* 如何积极压榨性能


## MVVM和Vue
### 使用jQuery和使用框架的区别

数据与视图的分离，解耦(封闭开放原则)

* `jquery`中数据与视图混合在一起了,不符合开放封闭原则
* `vue`:通过Vue对象将数据和View完全分离开来了


以数据驱动视图

* `jquery`完全违背了这种理念，`jquery`直接修改视图，直接操作`DOM`
* `vue`对数据进行操作不再需要引用相应的DOM对象，通过Vue对象这个vm实现相互的绑定
### 对MVVM的理解


MVC![][1] 

![][2]

MVVM

* Model:数据，模型
* View:视图、模板(视图和模型是分离的)
* ViewModel:连接Model和View


![][3]

![][4]

MVVM不算是创新，`ViewModel`算是一种微创新

是从mvc发展而来，结合前端场景的创新
### 如何实现MVVM

 **`Vue三要素`**

* **`响应式`** ：vue如何监听到data的每个属性变化
* **`模板引擎`** ：vue的模板如何被解析，指令如何处理
* **`渲染`** ：vue的模板如何渲染成html，以及渲染过程


#### vue中如何实现响应式

 **`什么是响应式`**

* 修改`data`属性之后，`vue`立刻监听到(然后立刻渲染页面)
* `data`属性被代理到vm上


 **``Object.defineProperty``** ES5中加入的API，所以Vue不支持低版本浏览器(因为低版本浏览器不支持这个属性)

```js
var obj = {};
    var _name = 'zhangsan';

    Object.defineProperty(obj,"_name",{
        get:function(){
            console.log("get");
            return _name;
        },
        set:function(newVal){
            console.log(newVal);
            _name = newVal;
        }
    });

    console.log(obj.name) //可以监听到
    obj.name = 'list'
```

 **`模拟实现`** 
```js
var vm = new Vue({
    el: '#app',
    data: {
        price: 100,
        name: 'zhangsan'
    }
})
```

```js
var vm = {}
var data = {
    name: 'zhangsan',
    price: 100
}

var key, value
for (key in data) {
    //命中闭包。新建一个函数，保证key的独立的作用域
    (function(key) {
        Object.defineProperty(vm, key, {
            get: function() {
                console.log('get')
                return data[key]
            },
            set: function(newVal) {
                console.log('set')
                data[key] = newVal
            }
        })
    })(key)
}

```
#### vue如何解析模板

模板是什么

* 本质：字符串；有逻辑,如v-if,if-if，嵌入JS变量...
* 与html格式很像，但有很大区别(静态)，最终还是要转化为html显示
* 模板最终必须转换成JS代码


* 1、因为有逻辑(v-for,v-if)，必须用JS才能实现(图灵完备)
* 2、转换为html渲染页面，必须用JS才能实现
* 因此，模板最重要转换成一个JS函数(render函数)



#### render函数

先了解with()的使用
```js
function fn1() {
    with(obj) {
        console.log(name);
        console.log(age);
        getAddress()
    }
}

```

最简单的一个示例
```js

{{price}}

```

```js
with(this) {    //this：vm
    return _c(
        'div', 
        {
            attrs: { "id": "app" }
        }, 
        [
            _c('p',[_v(_s(price))]     )  //price代理到了vm上
        ]
    )
}
```

```js
//vm._c
ƒ (a, b, c, d) { return createElement(vm, a, b, c, d, false); }

//vm._v
ƒ createTextVNode (val) {
  return new VNode(undefined, undefined, undefined, String(val))
}

//vm._s
ƒ toString (val) {
  return val == null? '': typeof val === 'object'? JSON.stringify(val, null,2): String(val)
}
```


* 模板中所有信息都包含在了render函数中
* `this`即`vm`
* `price`即`this.price`,即`data`中的`price`
* `_c`即`this._c`即`vm._c`


更复杂的一个例子
```html
    
        
            <input v-model="title">
            <button v-on:click="add">submit</button>
        


* {{item}}
            

```

如何寻找render函数：`code.render`模板如何生成render函数：

vue2.0开始就支持预编译，我们在开发环境下`写模板`，经过`编译打包`，产生生产环境的render函数(`JS`代码）

```js
with(this){  // this 就是 vm
            return _c(
                'div',
                {
                    attrs:{"id":"app"}
                },
                [
                    _c(
                        'div',
                        [
                            _c(
                                'input',
                                {
                                    directives:[
                                        {
                                            name:"model",
                                            rawName:"v-model",
                                            value:(title),
                                            expression:"title"
                                        }
                                    ],
                                    domProps:{
                                        "value":(title)
                                    },
                                    on:{
                                        "input":function($event){
                                          if($event.target.composing)return;
                                            title=$event.target.value
                                        }
                                    }
                                }
                            ),
                            _v(" "),
                            _c(
                                'button',
                                {
                                    on:{
                                        "click":add
                                    }
                                },
                                [_v("submit")]
                            )
                        ]
                    ),
                    _v(" "),
                    _c('div',
                        [
                            _c(
                                'ul',
                                _l((list),function(item){return _c('li',[_v(_s(item))])})
                            )
                        ]
                    )
                ]
            )
        }

```

```js
//vm._l
 function renderList(val,render) {
        var ret, i, l, keys, key;
        if (Array.isArray(val) || typeof val === 'string') {
            ret = new Array(val.length);
            for (i = 0, l = val.length; i < l; i++) {
                ret[i] = render(val[i], i);
            }
        } else if (typeof val === 'number') {
            ret = new Array(val);
            for (i = 0; i < val; i++) {
                ret[i] = render(i + 1, i);
            }
        } else if (isObject(val)) {
            keys = Object.keys(val);
            ret = new Array(keys.length);
            for (i = 0, l = keys.length; i < l; i++) {
                key = keys[i];
                ret[i] = render(val[key], key, i);
            }
        }
        if (isDef(ret)) {
            (ret)._isVList = true;
        }
        return ret
    }

```


* v-model是怎么实现的？
* v-on:click是怎么实现的
* v-for是怎么实现的


render函数与DOM

* 已经解决了模板中"逻辑"(`v-for`,`v-if`)的问题
* 还剩下模板生成html的问题
* 另外,vm_c是什么?`render`函数返回了什么


* vm._c其实就相当于`snabbdom`中的`h`函数
* `render`函数执行之后，返回的是`vnode`


```js
vm._update(vnode) {
    const prevVnode = vm._vnode
    vm._vnode = vnode
    if (!prevVnode) {
        vm.$sel = vm.__patch__(vm.$sel, vnode)    //与snabbdom中的patch函数差不多
    } else {
        vm.$sel = vm.__patch__(prevVnode, vnode)
    }
}

funciton updateComponent() {
    //vm._render即上面的render函数，返回vnode
    vm._update(vm._render())
}
```


* `updateComponent`中实现了`vdom`的`patch`
* 页面首次渲染执行`updateComponent`
* `data`中每次修改属性，执行`updataCommponent`


### vue的实现流程

第一步：解析模板成`render`函数

* with的用法
* 模板中所有的信息都被`render`函数包含
* 模板中用到的`data`中的属性，都变成了js变量
* 模板中的`v-model`、`v-if`、`v-on`都变成了js逻辑
* render函数返回vnode


第二步：响应式监听

* `Object.defineProperty`
* 将`data`属性代理到`vm`上


第三步：首次渲染，显示页面，且绑定依赖

* 初次渲染，执行`updateaComponent`，执行`vm._render()`
* 执行`render`函数，会访问到`vm.list`和`vm.title`
* 会被响应式的`get`方法监听到(为什么监听get？直接监听set不就行了吗？)


* `data`中有很多属性，有些会被用到，有些可能不会被用到
* 被用到的会走到`get`，不被用到的不会走`get`
* 未走到`get`中的属性，`set`的时候我们也无需关系
* 避免不必要的重复渲染



* 执行`updateComponent`,会走到`vdom`的`patch`方法
* `patch`将`vnode`渲染成`DOM`，初次渲染完成


第四步：`data`属性变化，触发`rerender`

* 属性修改，被响应式的`set`监听到
* `set`中执行`updateaComponetn`
* `updateComponent`重新执行`vm._render()`
* 生成的`vnode`和`prevVnode`，通过`patch`进行对比
* 渲染到`html`中


// ## 组件化和React
//## hybrid

未完待续，每日更新

[0]: ./img/1460000017514350.png
[1]: ./img/1460000017544485.png
[2]: ./img/1460000017544486.png
[3]: ./img/1460000017544487.png
[4]: ./img/1460000017544488.png