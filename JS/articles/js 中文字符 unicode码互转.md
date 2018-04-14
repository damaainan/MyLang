## js 中文字符 unicode码互转

来源：[https://xiaozhuanlan.com/topic/4579023816](https://xiaozhuanlan.com/topic/4579023816)

时间 2018-03-14 20:00:12


  
最近在做一些项目，有些变量的值可能会含有汉字，画面引入js以后，有可能会因为字符集的原因，把里面的汉字都变成乱码。js可以使用”\u“开头的16进制编码表示汉字，所以我就想解决方案。

```js
function char2Unicode(data)
{
   if(data == '') {
     return;
   }
   var str =''; 
   for(var i=0;i<data.length;i++)
   {
      str+="\\u"+parseInt(data[i].charCodeAt(0),10).toString(16);
   }
   return str;
}
function unicode2Char(data)
{
    if(data == '') { return; }
    var s = data.split("\\u");
    var str ='';
    for(var i=0;i<s.length;i++)
    {
        str+=String.fromCharCode(parseInt(s[i],16).toString(10));
    }
    return str;
}
```

浏览器会对\u进行自动转换 所以要用\u

```js
console.log(char2Unicode("汉字"));
console.log(unicode2Char("\\u6c49\\u5b57"));
```

自己搜索网络 发现了更为巧妙地写法

```js
function toUnicode(s){ 
        return s.replace(/([\u4E00-\u9FA5])/g,function(){
          return "\\u" + RegExp["$1"].charCodeAt(0).toString(16);
        });
  }
```

另外中文字符集的范围

[http://www.qqxiuzi.cn/zh/hanzi-unicode-bianma.php][0]


[0]: http://www.qqxiuzi.cn/zh/hanzi-unicode-bianma.php