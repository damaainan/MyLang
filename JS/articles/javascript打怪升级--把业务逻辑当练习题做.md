## javascript打怪升级--把业务逻辑当练习题做

来源：[https://segmentfault.com/a/1190000012499256](https://segmentfault.com/a/1190000012499256)


## 1.前言

开发项目和出没社区有一段时间了，会遇上一些比较有印象业务需求。这些业务需求，可能是自己开发项目遇上的，可能是在社区看到的业务需求，或者其他情况接触到的需求，但是这些业务需求的实现逻辑都值得一写。因为这些业务逻辑可以当做练习题一样，可以给大家练手。也希望大家从这些需求实现的逻辑里面可以能到javascript的相关知识，当然如果大家觉得代码需要怎样优化，或者有什么建议，更好的实现方案，觉得我哪里写错了，或者有觉得可以分享的需求，可以在评论提下！

## 2.月份坐标轴

这个需求是，看下图就懂了

![][0]

![][1]

实现方式其实很简单，我在代码打上注释，大家就懂了！

```js

var _date=[],dateData=["1月","2月","3月","4月","5月","6月","7月","8月","9月","10月","11月","12月"];
//准备一个月份反转的数组
var dateDataRet=Object.assign([],dateData).reverse();
//获取当前年份
var yearText=new Date().getFullYear();
//获取当前月份  调试的时候，大家可以通过调整now调试  3月-now=2,12月now=11...
var now=new Date().getMonth();
for(let i=0;i<6;i++){
    if(now-i<0){
        //如果now-i<0，从dateDataRet里面拿数据，下标=|now-i|-1。
        _date.push(yearText-1+'年'+dateDataRet[Math.abs(now-i)-1]);
    }
    else{
        //从dateData里面拿数据，下标=now-i
        _date.push(yearText+'年'+dateData[now-i]);
    }

}
_date.reverse();

```

可能大家看着会懵，直接看下面的循环图就懂了

![][2]

## 3.数值区间

如下图，就是几个数值区间，而且会有一个最小值和最大值

![][3]

```js

var _min=5,_max=50;
function checkArr(arr,min,max){
    //排序
    arr.sort(function(n1,n2){return n1.min-n2.min})
    //遍历
    for(var i=0;i<arr.length;i++){
        //区间的最小值不能大于等于区间最大值
        if(arr[i].min>=arr[i].max){
            console.log('区间的最小值不能大于等于区间最大值');
            return;
        }
        //区间的最小值不能小于默认最小值
        if(arr[i].min<min){
            console.log('区间的最小值不能小于默认最小值');
            return;
        }

        //区间的最大值不能大于默认最大值
        if(arr[i].max>max){
            console.log('区间的最大值不能大于默认最大值');
            return;
        }
        //元素对比，从第二个元素开始
        if(i>0){
            //minInclude，maxInclude，为false就是不包含，为true就是包含
            //{min:10,max:20,minInclude:false,maxInclude:false}
            //等同于(10,20)
            //{min:20,max:30,minInclude:true,maxInclude:false}
            //等同于[20,30);

            //如果前一个的最大值和当前的最小值都是包含情况，那么当前区间的最小值一定要比前一个区间的最大值大1
            if(arr[i].minInclude&&arr[i-1].maxInclude&&arr[i].min-arr[i-1].max!==1){
                console.log('取值范围错误-当前区间的最小值和前一个区间的最大值都是包含情况，当前区间的最小值一定要比前一个区间的最大值大1');
                   return;

            }
            //如果前一个的最大值和当前的最小值。一个是包含，一个是不包含，那么当前区间的的最小值一定要等于上一个区间的最大值
            else if(arr[i].minInclude!==arr[i-1].maxInclude&&arr[i].min!==arr[i-1].max){
                console.log('取值范围错误-当前区间的最小值和前一个区间的最大值其中一个是包含，一个是不包含情况，当前区间的最小值一定要等于前一个区间的最大值');
                return;
            }
            //如果前一个的最大值和当前的最小值都是不包含，肯定不满足
            else if((!arr[i].minInclude)&&(!arr[i-1].maxInclude)){
                console.log('取值范围错误-前一个的最大值和当前的最小值都是不包含情况，不满足收尾相连');
                return;
            }
        }
    }
}

```

测试用例

```js

var arr1=[{min:10,max:20,minInclude:false,maxInclude:true},{min:21,max:30,minInclude:true,maxInclude:true}],
arr2=[{min:10,max:20,minInclude:false,maxInclude:true},{min:20,max:30,minInclude:true,maxInclude:false}],
arr3=[{min:10,max:20,minInclude:false,maxInclude:true},{min:20,max:30,minInclude:false,maxInclude:false}],
arr4=[{min:10,max:20,minInclude:false,maxInclude:false},{min:20,max:30,minInclude:true,maxInclude:false}],
arr5=[{min:10,max:20,minInclude:false,maxInclude:false},{min:21,max:30,minInclude:true,maxInclude:false}],
arr6=[{min:10,max:20,minInclude:false,maxInclude:false},{min:15,max:30,minInclude:false,maxInclude:false}],
arr7=[{min:10,max:20,minInclude:false,maxInclude:false},{min:20,max:30,minInclude:false,maxInclude:false}],
arr8=[{min:1,max:20,minInclude:false,maxInclude:false},{min:20,max:30,minInclude:false,maxInclude:false}],
arr9=[{min:20,max:20,minInclude:false,maxInclude:false},{min:20,max:30,minInclude:false,maxInclude:false}], 
arr10=[{min:20,max:30,minInclude:false,maxInclude:false},{min:20,max:70,minInclude:false,maxInclude:false}];  

```

运行结果

![][4]

## 4.数组对比

这个基于我回答过的一个问题，现在化用，改写一下

JavaScript如何对比两个数组？数组B根据数组A来做出增删？ (不用jquery，原生js)

具体问题是这样的：

arryA

```js

var arrayA = ['a','b','c'];

```

arryB

```js

var arrayB = [{
    key:'a',
    num1:'1',
    num2:'2',
    num3:'3',
    tot:'6'
},{
    key:'b',
    num1:'11',
    num2:'22',
    num3:'33',
    tot:'66'
},{
    key: 'c',
    num1: '111',
    num2: '222',
    num3: '333',
    tot:666
}];

```

1、如果arryA中有a，arryB中没有，那么在arryB中增加一个key值为a的boj，且其他属性值可均为'0';如下： {key:'a',num1:'0',num2:'0',num3:'0',tot':0'}

2、如果arryA中有a，arryB中也有key值为a的obj,那么arryB则不改变，并且该obj里的其他属性和属性值均不变;

3、如果在arryA中删除了a，那么arryB中key值为a的obj整个删掉。

```js

//准备临时数组
function compareArr(arr1,arr2){
    var result=[],arr;
    //遍历
    for(var i=0;i<arr1.length;i++){
        //根据arr1[i]的值，查找arrayB，如果arr2中的有满足条件（arrayB中的对象，有key值等于arrayA[i]）的项，就会返回满足条件的项，否则返回underfind;
        arr=arr2.find(function(val){return val.key===arr1[i]});
        //如果arr不是undefind，就会添加arr，否则添加{key:arrayA[i],num1:'0',num2:'0',num3:'0',tot:'0'}。
        arr?result.push(arr):result.push({key:arrayA[i],num1:'0',num2:'0',num3:'0',tot:'0'});
    }
}

```

测试

```js

var arrayA = ['b','c'];
var arrayB = [{
    key:'a',
    num1:'1',
    num2:'2',
    num3:'3',
    tot:'6'
},{
    key:'b',
    num1:'11',
    num2:'22',
    num3:'33',
    tot:'66'
},{
    key: 'c',
    num1: '111',
    num2: '222',
    num3: '333',
    tot:666
}];
compareArr(arrayA,arrayB);

```

![][5]

## 5.学院获奖

统计学生申请优秀毕业生，并且符合条件的（成绩优秀，拿过奖学金，获得过三好学生）。前提是要申请

大概的流程图就是像下面这样！

![][6]

我在代码上写上注释，相信不难理解了

```js

//学生列表
//isApply：是否有申请优秀毕业生
let studentList = [
    {
        name: 'aa',
        isApply: false,
        id: 1
    },
    {
        name: 'bb',
        isApply: true,
        id: 2
    },
    {
        name: 'cc',
        isApply: true,
        id: 3
    }
];

//申请优秀毕业生的学生 isApply:true

let _student = studentList.filter(function (item) {
    return item.isApply;
});
//isExcellent:优秀学生的id列表
//isScholarship:获得过奖学金的学生的id列表
//isThreeGood:获得过三好学生的学生的id列表
//accord:集合
let isExcellent = [1, 2, 3, 4, 5], isScholarship = [4, 2, 5, 6, 2, 1, 2], isThreeGood = [2, 1, 4, 52, 36], accord = [];
//数组去重函数
function removeRepeatArr(arr) {
    return arr.filter(function (item, index, self) {
        return self.indexOf(item) === index;
    });
}

//统计数组中，一个遇上元素的出现次数
function getEleCount(obj, ele) {
    let num = 0;
    for (let i = 0, len = obj.length; i < len; i++) {
        if (ele === obj[i]) {
            num++;
        }
    }
    return num;
}

//添加学生记录，把获得成绩优秀的学生的id，获得过奖学金的学生的id，获得过三好学生的id添加进去。
//但是添加之前，要对获得成绩优秀的学生的id，获得过奖学金的学生的id，获得过三好学生的id。这个三个数组进行去重再添加进accord，因为一个学生可能不止一次成绩优秀，不止一次获得过奖学金，不止一次获得过三好学生
//这样就方便下面的判断，只要学生的id在accord里面出现两次及以上就符合条件
accord.push.apply(accord, removeRepeatArr(isExcellent));
accord.push.apply(accord, removeRepeatArr(isScholarship));
accord.push.apply(accord, removeRepeatArr(isThreeGood));
console.log(accord);
//符合条件的学生列表
let accordStudent = [];
for (let i = 0; i < _student.length; i++) {
    //只要学生的id在accord里面出现两次及以上
    if (getEleCount(accord, _student[i].id) >= 2) {
        //记录哪些学生符合条件
        accordStudent.push(_student[i]);
    }
}
console.log(accordStudent);

```

## 6.数组连续的最大长度

这个也是出于我回答过的问题：如下

```js

//假如有一个数组，下面这个数组最大的连续长度就是4——————8,9,10,11
var arr=[1,2,4,5,6,8,9,10,11];

//代码实现
function countLen(arr){
    //如果参数不是数组或者长度为0，直接返回0
    if(arr.constructor!==Array||arr.length===0){return 0;}
    //首先进入当前连续长度nowLen设初始化为1，最大连续长度maxLen初始化为0
    var nowLen=1,maxLen=0;

    for(var i=1,len=arr.length;i<len;i++){
        //当前数组元素是不是比上一个数组大1
        if(arr[i]-arr[i-1]===1){
            //如果是，当前连续长度nowLen+1    
            nowLen++;
        }
        else{
            //否则先判断，当前连续长度是否大于最大连续长度
            if(maxLen<nowLen){
                //如果是就赋值
                maxLen=nowLen
            }
            //当前连续长度初始化为1
            nowLen=1;
        }
    }
    //循环完再判断一次当前连续长度是否大于最大连续长度（避免最大连续长度是数组最后面几个数组时产生的bug）
    if(maxLen<nowLen){
        maxLen=nowLen
    }
    //返回最大连续长度
    return maxLen;
}

```

![][7]

![][8]

## 7.答题连对数

这个和上面的代码基本一样，只是判断条件毫厘之差，直接贴，大家看就好

```js

function countTrue(arr){debugger;
    //如果参数不是数组或者长度为0，直接返回0
    if(arr.constructor!==Array||arr.length===0){return 0;}
    //首先初始化连续答对长度nowLen为0，最大连续答对长度maxLen为0
    var nowLen=0,maxLen=0;
    for(var i=0,len=arr.length;i<len;i++){
        //当前数组元素是不是比上一个数组大1
        if(arr[i]){
            //如果是，当前连续长度nowLen+1
            nowLen++;
        }
        else{
            //否则先判断，当前连续长度是否大于最大连续长度
            if(maxLen<nowLen){
                //如果是就赋值
                maxLen=nowLen
            }
            //当前连续长度初始化为0
            nowLen=0;
        }
    }
    //循环完再判断一次当前连续长度是否大于最大连续长度（避免最大连续长度是数组最后面几个数组时产生的bug）
    if(maxLen<nowLen){
        maxLen=nowLen
    }
    //返回最大连续长度
    return maxLen;
}

```

![][9]

## 8.命名方式转换

比如驼峰命名方式转'-'命名方式。

```js

var str = "shouHou";
//$1-第一个括号匹配的内容
//这个实例，$1='H'
str = str.replace(/([A-Z])/g,"-$1").toLowerCase();

```

![][10]

比如'-'命名方式转驼峰命名方式

```js

var str="shou-hou";
//$0-匹配的结果   $1-第一个括号匹配的内容
//这个实例$0='-h'    $1='h'
str=str.replace(/-(\w)/g,function($0,$1){
    return $1.toUpperCase();
}); 

```

![][11]

## 9.格式化字符

这个最常见的就是在金额方面的显示需求上，比如后台返回10000。前端要显示成10,000或者其他格式等！

```js

//str
//size-每隔几个字符进行分割 默认3
//delimiter-分割符 默认','
function formatText(str,size,delimiter){
    var _str=str.toString();
    var _size=size||3,_delimiter=delimiter||',';
    /* 
     如果_size是3
     "\d{1,3}(?=(\d{3})+$)" 
     */
    var regText='\\d{1,'+_size+'}(?=(\\d{'+_size+'})+$)';
    /*   
    /\d{1,3}(?=(\d{3})+$)/g     这个正则的意思：匹配连续的三个数字，但是这些三个数字不能是字符串的开头1-3个字符  
     */
    var reg=new RegExp(regText,'g');
    /* 
    (-?) 匹配前面的-号   (\d+)匹配中间的数字   ((\.\d+)?)匹配小数点后面的数字
    //$0-匹配结果，$1-第一个括号返回的内容----(-?)    $2,$3如此类推  
    */
    return _str.replace(/^(-?)(\d+)((\.\d+)?)$/, function ($0, $1, $2, $3) {
          return $1 + $2.replace(reg, '$&,') + $3;
    })
}

```

![][12]

## 10.对象合并，并且记录异常数据

这个需求，可能大家有点懵。下面实例分析

比如有两个都地方记录了我的信息

```js

let info1={
        name:"守候",
        sex:"男",
        age:24,
        job:"web前端"
    },info2={
        name:"守候!",
        country:"china",
        interest:"basketball",
        phone:"12345678910",
        job:"web前端"
    }

```

现在要合并我的信息，并且记录可能有异常的信息。比如上面的name属性，在两个对象都有，而且两个对象的值不一样，那么就不知道到底是info1中的name属性是正确的，还是info2中的name属性是正确的。所以，就得把name这个属性记录起来，方便以后核对name这个属性。

如下图

![][13]

下面，一步一步来，先不管3721，直接合并属性

```js

let objAll={};
function assignObj(objArr) {
    let _obj={};
    for(let i=0;i<objArr.length;i++){
        _obj=Object.assign(_obj,objArr[i],{});
    }
    return JSON.parse(JSON.stringify(_obj));
}
objAll=assignObj([objA,objB]); 

```

然后先准备一个字段，记录哪些异常信息

```js

objAll.warnInfo=[];

```

最后检查对象，判断哪些信息有异常

```js

  function checkObj(_objAll,objList) {
        //获取所有属性
        let _keys=Object.keys(_objAll);
        for(let i=0;i<objList.length;i++){
            for(let j=0;j<_keys.length;j++){
                //如果_keys[j]这个属性，在objList[i]和_objAll里面都存在，而且这两个值是不一样的，那么就是一场数据，需要记录！
                if(objList[i][_keys[j]]!==undefined&&_objAll[_keys[j]]!==objList[i][_keys[j]]){
                    _objAll.isError.push(_keys[j]);
                }
            }
        }
        return _objAll;
    }
    console.log(checkObj(objAll,[objA,objB]));  

```

## 11.筛选标签

如下图，在下面渲染这个标签

![][14]

大家可能第一可能觉得压根没难度

就是一个对象数组：比如

```js

var searchTag=[
    {label:'产品编码',value:'100072236-8'},
    {label:'产品名称',value:'甘油'}
]

```

但是这样的数据，显然是要经过处理生成的

因为不可能这样发送请求

```js

http://example.com?产品编码=100072236-8   

```

发送过去的参数应该是这样的

```js

http://example.com?proId=100072236-8

var searchParam={proId:'100072236-8',proName:'甘油'}   

```

怎么进行数据的处理呢，其实很简单，代码不打注释，我想都看得懂

```js

var searchTag=[];
var searchText={proId:'产品编码',proName:'产品名称'};
var searchParam={proId:'100072236-8',proName:'甘油'};
Object.keys(searchParam).forEach(function (item) {
    searchTag.push({
        label:searchText[item],
        key:item,
        value:searchParam[item]
    })
})
console.log(searchTag)    

```

![][15]

有了这些数据，渲染到页面这个就简单了！

## 12.导入excel内容

就是excel上这样的内容

![][16]

转成下面的数据

![][17]

![][18]

目录如下

![][19]

下面开始写代码，我们利用node.js来写

```js

let path = require('path');
//使用ejsexcel读取excel文件  npm install ejsexcel --save
let ejsExcel=require('ejsexcel');
let fs=require('fs');
//读取excel
let exBuf=fs.readFileSync(__dirname+'/resource/userList.xlsx');
let _data=[];
//获取成功后
ejsExcel.getExcelArr(exBuf).then(exlJson=>{
    //获取excel数据
    let workBook=exlJson;
    //获取excel第一张表 sheet1
    let workSheets=workBook[0];
    //导出js的路径
    let newfilepath=path.join(__dirname,"/resource/test.js");
    //遍历第一张表的的每一行数据
    workSheets.forEach((item,index)=>{
        //从第二行开始插入，避免连表头也插入_data里面
        if(index>0){
            //往_data插入单元格个值，item[0]相当于excel中的姓名，item[1]就是excel中的联系电话
            _data.push({
                name:item[0],
                phone:item[1]
            })
        }
    });
    //写入js文件
    fs.writeFileSync(newfilepath, 'let _data='+JSON.stringify(_data)+';export {_data}');
}).catch(error=>{
    //打印获取失败信息
    console.log("读取错误!");
    console.log(error);
});

```

然后命令行执行该js

```

$ node importFile.js

```

然后就发现多了一个test.js文件

![][20]

excel的数据就这样导入成js的一个数组了，只要引入这个数组，就可以正常的使用了！

## 13.随机循环

当时接到的业务是实际显示客户的信息，感觉有点像音乐播放器的随机循环。

要求有两个：

1.一个提示列表里面，提示的信息每隔500ms随机展示。

2.同一轮循环里面，一个提示信息只能展示一次。

3.列表的提示信息全部展示完了，进行下一轮展示。

这个逻辑没什么，直接在代码打上注释，我想大家就明白了！

```js

var tipList=['提示1','提示2','提示3','提示4','提示5','提示6','提示7','提示8','提示9'];
var tipListShow=[];
tipListShow=Object.assign([],tipList);
var i=0,timer=null;
function play() {
    //随机显示一个，显示了之后，把这个项从tipListShow中删除掉，防止在同一轮重复出现！
    console.log(tipListShow.splice(Math.floor(Math.random() * tipListShow.length),1)[0]);
    //当循环完了之后，tipListShow的长度就会是0，然后就重新赋值，准备进行下一轮的随机循环
    if(tipListShow.length===0){
        tipListShow=Object.assign([],tipList);
        i=0;
    }
    //如果需要暂停或者停止的，清除这个定时器即可，下次执行就重新这样创建定时器，执行play();！
    timer=setTimeout(function () {
        play();
    },500);
}
play();

```

![][21]

## 14.小结

好了，关于我收集到的一些业务需求逻辑，以及实现的方式，就说到这里了！接触到的业务需求逻辑很多，但是值得写的，可以当做练习题的，就记录到这里了。我上面代码实现可能会有点粗糙，大家有更好的实现方案，欢迎建议一下。如果大家有什么可以当做练习题的需求，可以提下。让大家有多些练习题可以尝试下，学习下！

-------------------------华丽的分割线--------------------

想了解更多，关注关注我的微信公众号：守候书阁


[0]: ./img/bVZE5G.png
[1]: ./img/bVZE59.png
[2]: ./img/bVZFef.png
[3]: ./img/bVZqVP.png
[4]: ./img/bVZFwH.png
[5]: ./img/bVZFB6.png
[6]: ./img/bVZGtZ.png
[7]: ./img/bVVkoG.png
[8]: ./img/bVVkrT.png
[9]: ./img/bVZFHs.png
[10]: ./img/bVZFM3.png
[11]: ./img/bVZFND.png
[12]: ./img/bVZGem.png
[13]: ./img/bVZK5J.png
[14]: ./img/bVZRX5.png
[15]: ./img/bVZR7C.png
[16]: ./img/bV0cT9.png
[17]: ./img/bV0cV8.png
[18]: ./img/bV0cWa.png
[19]: ./img/bV0c7w.png
[20]: ./img/bV0c8J.png
[21]: ./img/bV0wv6.png
