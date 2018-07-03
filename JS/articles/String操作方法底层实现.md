## String操作方法底层实现！！！

来源：[https://juejin.im/post/5aa13fcaf265da23766adcd5](https://juejin.im/post/5aa13fcaf265da23766adcd5)

时间 2018-03-12 10:59:29
 
以下代码纯属个人写着玩。为了加深理解和熟悉字符串提供的方法的思路。但是我发现我写完之后还是忘了。没啥鸟用。分享给大家指点。 
 
大家说如果面试的话,让面试者写一个字符串底层方法实现思路。是否能快速写出来。
 
### 1:charAt

```js
/*
* charAt()方法
* 功能  :  返回指定位置的字符
* 参数  :  传递一个下标
* 官方使用
* var str = "abcdefg";
* str.charAt(2);	        //c
* str.charAt("CCCC");		//输入其他字符都默认返回下标为0的字符   输出a
* str.charAt(-1);		//传递负值返回空字符串
*/

String.prototype.ycCharAt = function(){
	var parma = arguments[0];
	var returnStr = parma >= 0 ? this[parma] : !isNaN(parma) ?  "" : this[0];
	return returnStr;
}
```
 
### 2:concat

```js
/*
* concat()方法
* 功能  :  用于连接两个字符串
* 参数  :  传递一个字符串
* 官方使用
* var str = "abcdefg";
* str.concat(123);			//"abcdefg123"
* str.concat([1,2,3]);			//"abcdefg1,2,3"
* str.concat({name:"123"});		//"abcdefg[object Object]"
*/
String.prototype.ycConcat = function(){
	return this + arguments[0];
}
```
 
## 二：三个字符串截取方法实现
 
### 1：slice

```js
/*
* slice() 方法
* 功能  :  截取字符串。
* 参数  :  第一个参数是子字符串的开始位置，第二个参数是子字符串的结束位置（不含该位置）
* 注意  : 
* 	1:第一个参数不能大于第二个参数的值  否则返回空
* 	2:如果参数是负值。当参数是负数时候  字符串长度会默认加上负数 
* 官方使用
* var str = "abcdefg";
* str.slice(1);					//"bcdefg"
* str.slice(1,4);				//"bcd"
* str.slice(1,-4);				//结束位置就相当于 字符串长度7+-4 =  3 === slice(1,3)  = bc
* str.slice(-3,-4);				//""
*/
String.prototype.ycSlice = function(){
	var _str = "";
	//获取开始位置
	var _start = arguments[0] >= 0 ? arguments[0] : this.length+arguments[0] ;
	//获取结束位置
	var _end = arguments[1] >= 0 ? arguments[1] : this.length+arguments[1] ;
	for(var i=0;i<this.length;i++){
		if(i >= _start  && i < _end){
			_str += this[i];
		}
	}
	return _str;
}
```
 
### 2：substring

```js
/*
* substring() 方法
* 功能  :  截取字符串。如果参数是负值。当参数是负数或者时候  字符串长度会默认加上负数 
* 参数  :  第一个参数是子字符串的开始位置，第二个参数是子字符串的结束位置（不含该位置）
* 注意	: 
* 	1:第一个参数不能大于第二个参数的值  否则返回空
* 	2:当传递不是数字则默认转换为0
* 官方使用
* var str = "abcdefg";
* str.substring(1);					//"bcdefg"
* str.substring(1,4);				//"bcd"
* str.substring(1,-4);				//结束位置就相当于 字符串长度substring(1,0)  = b
* str.substring(-3,-4);				//""
*/
String.prototype.ycSubstring = function(){
	var _str = "";
	//获取开始位置
	var _start = arguments[0] >= 0 ? arguments[0] : 0 ;
	//获取结束位置
	var  _end  = arguments[1] >= 0 ? arguments[1] : 0 ;
	for(var i=0;i<this.length;i++){
		if(i >= _start  && i < _end){
			_str += this[i];
		}
	}
	return _str;
}
```
 
### 3:substr

```js
/*
* substr() 方法
* 功能  :  截取字符串。如果参数是负值。当参数是负数或者时候  字符串长度会默认加上负数 
* 参数  :  第一个参数是子字符串的开始位置，第二个参数是子字符串的长度
* 注意	: 
* 		1:第一个参数是负值。当参数是负数时候  字符串长度会默认加上负数 
* 		2:第二个参数当传递不是数字则默认转换为0
* 官方使用
* var str = "abcdefg";
* str.substr(1);					//"bcdefg"
* str.substr(1,4);					//"bcd"
* str.substr(1,-4);					//结束位置就相当于 字符串长度substring(1,0)  = b
* str.substr(-3,-4);				//""
*/
String.prototype.ycSubstr = function(){
	var _str = "";
	//获取开始位置
	var _start = arguments[0] >= 0 ? arguments[0] : this.length+arguments[0];
	//获取结束位置
	var  _end  = arguments[1] >= 0 ? arguments[1] : 0 ;
	for(var i=0;i<this.length;i++){
		if(i >= _start  && i < (_start+_end)){
			_str += this[i];
		}
	}
	return _str;
}
```
 
## 三：检索匹配字符串对应的下标
 
### 1:indexOf

```js
/*
* indexOf() 方法
* 功能  :  返回指定字符在当前字符串第一次出现的位置。
* 参数  :  第一个参数：匹配的字符串   第二个参数 ：从哪个位置开始匹配
* 官方使用
* var str = "abcdefga";
* str.indexOf("a");				//"0"
* str.indexOf("a",2);				//"7"
* str.indexOf(1);				//-1
*/

String.prototype.ycIndexOf = function(){
	var _parma = arguments[0];
	var _start = arguments[1] || 0;
	var _index = -1;
	for(var i=_start;i<this.length;i++){
		if(this[i] == _parma){
			_index = i;
			return _index;
		}
	}
}
```
 
### 2:lastIndexOf

```js
/*
* lastIndexOf() 方法
* 功能  :  返回当前字符串最后一个匹配的字符索引
* 参数  :  第一个参数：匹配的字符串   第二个参数 ：从哪个位置开始匹配
* 官方使用
* var str = "abcdefga";
* str.lastIndexOf("a");					//"7"
* str.lastIndexOf("a",2);				//"0"
* str.lastIndexOf(1);					//-1
*/

String.prototype.ycLastIndexOf = function(){
	var _parma = arguments[0];
	var _start = arguments[1] ||  this.length;
	var _index = -1;
	for(var i=_start;i >= 0;i--){
		if(this[i] == _parma){
			_index = i;
			return _index;
		}
	}
}
```
 
后续有时间了 可能会继续写下去。发现把字符串和数组的底层方法自己实现一遍的话。再去做什么数组去重 排序。。。思路自然而然就来了。
