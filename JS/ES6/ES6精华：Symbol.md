## ES6精华：Symbol

来源：[https://segmentfault.com/a/1190000015244917](https://segmentfault.com/a/1190000015244917)

它是`JS`的第七种类型，属于基本类型。  
它表示一个独一无二的值，行为类似字符串。  
它是直接通过`Symbol`函数生成的，可以传入字符作为该值的描述。

```js
const symbol1 = Symbol('unique');
const symbol2 = Symbol('unique');
console.log(symbol1 === symbol2); // false
```
### 应用举例
 **`替代用于识别的字符串常量`** 

```js
--- 之前
const MY_ONE = 'unique-one';
if (MY_ONE === 'unique-one') { ... }
虽然定义了保存值的常量，但直接使用值或再定义相同值的变量也是没有问题的。

--- 现在
const MY_ONE = Symbol('one');
if (MY_ONE === MY_ONE) { ... }
如果想使用该常量，必须直接使用该常量或其一个副本，因为 Symbol('one') 是绝对唯一的。
```
 **`防止全局模块被无意修改`** 

```js
--- 之前
直接使用字符串作为命名空间。
window.ModuleA = {};

--- 现在
使用 Symbol.for 注册唯一的值作为命名空间。
window[Symbol.for('Module_A')] = {};
虽然他人也能误操作对其修改，但这种可能性比较低。
```
 **`作为自定义接口或不同数据集合统一接口的名称`** 

```js
示例：为 Array 增加并集的计算方法，使用此方法可以避免未来可能的命名冲突。

const CusArrayAPIMap = {
  union: Symbol('cus-array-api-union')
};

Array[CusArrayAPIMap.union] = function() {
  return [...new Set([...arguments].reduce((a, b) => a.concat(b), []))];
};

Array[CusArrayAPIMap.union]([1, 3], [2, 3]); // [1, 3, 2]
```
### 转化规则
`symbol`值不可转化成数字（作为一个唯一值无对应的数值）。  
`symbol`值可以转化成布尔值（不管怎样，它是有值的，所以恒为`true`）。  
`symbol`值不可被隐式转化成字符串，但是可以显示转化（隐式即计算，拿一个唯一值计算没意义，但直接打印成字符串查看是可以的）。

```js
Symbol() + 2; // 报错
Number(Symbol()); // 报错

Boolean(Symbol()); // 恒为 true
if (Symbol()) { ... } // 恒执行

Symbol() + '-'; // 报错
String(Symbol()); // "Symbol()"
Symbol().toString(); // "Symbol()"
```
### Symbol.for()
`Symbol.for(key)`与`Symbol()`一样，用来返回一个唯一值。  
不过其传入的`key`与生成的值会形成映射存储在全局的`symbol`注册表中。  
即是说，`Symbol.for(key)`是先根据`key`在注册表中寻找，有直接返回，没有创建并返回。  
也即是说，在相同的全局空间中（包括不同的`iframe`或`service worker`）传入相同的`key`取出来的是同一值。

```js
Symbol('one') === Symbol('one'); // false
Symbol('one') === Symbol.for('one'); // false
Symbol.for('one') === Symbol.for('one'); // true
Symbol.for('one') === Symbol.for('two'); // false
```

相配套的还有方法`Symbol.keyFor()`。  
它会根据传入的`Symbol`值，去注册表中查找并返回对应的`key`。

```js
let o = Symbol.for('one');

Symbol.keyFor(o); // 'one'
Symbol.keyFor(Symbol('two')); // undefined
Symbol.keyFor(Symbol.for('two')); // 'two'
```
### 内置的 Symbol 值
`ES6`规定了11个内置接口的统一名称。  
可以将这些接口部署到自定义对象或构造函数上，同步原生操作。
 **`Symbol.toStringTag`**   
指向一个字符串，表示该对象的类型标签。  
通俗的说，就是使用`Object.prototype.toString.call(target)`获取到的`[object Name]`中的`Name`。

```js
let obj = {
  [Symbol.toStringTag]: 'MyTag'
};
console.log( Object.prototype.toString.call(target) ); // '[object MyTag]'
```
 **`Symbol.toPrimitive`**   
指向一个方法，当该对象被转化成`Number`或`String`型时会被调用。  
该方法会接受一个字符串参数，表示当前场合需要转化成什么类型，一共有三种模式：`number`，`string`和`default`（转化成两者都行）。

```js
let obj = {
  [Symbol.toPrimitive](type) {
    switch(type) {
      case 'number':
        return 3;
        break;
      case 'string':
        return 's';
        break;
      case 'default':
        return 'd';
        break;
    }
  }
};

console.log( Number(obj) ); // 3
console.log( String(obj) ); // 's'
console.log( obj + 1 );  // 'd1'
```
 **`Symbol.hasInstance`**   
指向一个方法，是`instanceof`命令实际调用的方法。

```js
[] instanceof Array; // true
实际是执行下面代码。
Array[Symbol.hasInstance]([]); // true

可自行为自定义对象添加此接口。
let OBJ = {
  [Symbol.hasInstance](arr) {
    return arr.length === 2 ? true : false;
  }
};
[1] instanceof OBJ; // false
[1, 2] instanceof OBJ; // true
```
 **`Symbol.iterator`**   
指向对象的默认遍历器方法（关于遍历器可看`Iterator`章节）。  
数组默认的遍历器方法为：`Array.prototype[Symbol.iterator]`。
 **`Symbol.species`**   
指向一个方法，该方法返回一个构造函数。当实例需要调用自身的构造函数时方法会被调用。  
有些类库是在基类的基础上修改的，当子类使用继承的方法时，作者希望返回基类的实例，而不是子类的实例。

```js
class MyArray extends Array {
  static get [Symbol.species]() { return Array }
}

let a = new MyArray(1, 2, 3);
let b = a.map(x => x);
console.log(b instanceof Array); // true
console.log(b instanceof MyArray); // false

b 是 a 的衍生对象，或称派生对象。
如果没有 [Symbol.species] ，b 原型链中第一个对象应为 MyArray 原型。
但现在第一个对象为 Array 的原型，即 b 直接为 Array 的实例。
```
 **`Symbol.split, Symbol.match, Symbol.search, Symbol.replace`**   
四者都是针对字符串与正则（对象）的关系，指向一个方法，具有相同行为。

```js
let reg = /m/g;
let str = 'Hi, I\'m programmer monkey';

str.replace(reg, 'M');
实际是执行下面的代码。
reg[Symbol.replace](str, 'M');
```
 **`Symbol.isConcatSpreadable`**   
指向一个布尔值，表示该对象用于`Array.prototype.concat()`时是否可以展开。  
默认没有该属性，即为`undefined`，等同于`true`。设置为`false`则不展开。

```js
let arr = [1, 2];
arr[Symbol.isConcatSpreadable] = false;
[3].concat(arr); // [3, [1, 2]]
```
 **`Symbol.unscopables`**   
指向一个对象，该对象指定了使用`with`关键字时，哪些属性会被`with`环境排除。

```js
let obj = {
  id: '123',
  name: 'limo',
  [Symbol.unscopables]: {
    id: true
  }
};

let id = 'id';
let name = 'name';

with (obj) {
  console.log(id); // 'id'
  console.log(name); // 'limo'
}
```
