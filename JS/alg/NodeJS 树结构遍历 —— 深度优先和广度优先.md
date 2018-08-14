## NodeJS 树结构遍历 —— 深度优先和广度优先

来源：[https://juejin.im/post/5b579d0af265da0f98315c15](https://juejin.im/post/5b579d0af265da0f98315c15)

时间 2018-07-26 15:11:01

 
 ![][0]
 
## 树的基本概念
 
树（Tree）是`n`个结点的有限集，`n`为`0`时，称为空树，在任意一棵非空树中有且仅有一个特定的被称为根（Root）的结点，当`n`大于`1`时，其余结点可分为`m`个互不相交的有限集`T1`、`T2`、`......`、`Tm`，其中每一个集合本身又是一棵树，并且称为`SubTree`，即根的子树。
 
需要强调的是，`n>0`时根结点是唯一的，不可能存在多个根结点，`m>0`时，子树的个数没有限制，但它们一定是互不相交的。
 
从根开始定义起，根为第一层，根的孩子为第二层，若某结点在第`l`层，则其子树就在第`l+1`层，其双亲在同一层的结点互为 “堂兄弟”，树中结点的最大层级数称为树的深度（Depth）或高度。
 
 ![][1]
 
在对树结构进行遍历时，按顺序可分为先序、中序和后续，按遍历的方式可分为深度优先和广度优先，我们这篇文章就通过使用先序深度优先和先序广度优先来实现 NodeJS 中递归删除目录结构，体会对树结构的遍历，文章中会大量用到 NodeJS 核心模块`fs`的方法，可以通过 [NodeJS 文件操作 —— fs 基本使用][4] 来了解文中用到的`fs`模块的方法及用法。
 
## 先序深度优先实现递归删除文件目录
 
深度优先的意思就是在遍历当前文件目录的时候，如果子文件夹内还有内容，就继续遍历子文件夹，直到遍历到最深层不再有文件夹，则删除其中的文件，再删除这个文件夹，然后继续遍历它的 “兄弟”，直到内层文件目录都被删除，再删除上一级，最后根文件夹为空，删除根文件夹。
 
 ![][2]
 
### 1、同步的实现
 
我们要实现的函数参数为要删除的根文件夹的路径，执行函数后会删除这个根文件夹。
 
```js
// 引入依赖模块
let fs = require("fs");
let path = require("path");

// 先序深度优先同步删除文件夹
function rmDirDepSync(p) {
    // 获取根文件夹的 Stats 对象
    let statObj = fs.statSync(p);

    // 检查该文件夹的是否是文件夹
    if (statObj.isDirectory()) {
        // 查看文件夹内部
        let dirs = fs.readdirSync(p);

        // 将内部的文件和文件夹拼接成正确的路径
        dirs = dirs.map(dir => path.jion(p, dir));

        // 循环递归处理 dirs 内的每一个文件或文件夹
        for (let i = 0; i < dirs.length; i++) {
            rmDirDepSync(dirs[i]);
        }

        // 等待都处理完后删除该文件夹
        fs.rmdirSync(p);
    } else {
        // 若是文件则直接删除
        fs.unlinkSync(p);
    }
}

// 调用
rmDirDepSync("a");
```
 
上面代码在调用`rmDirDepSync`时传入`a`，先判断`a`是否是文件夹，不是则直接删除文件，是则查看文件目录，使用`map`将根文件路径拼接到每一个成员的名称前，并返回合法的路径集合，循环这个集合并对每一项进行递归，重复执行操作，最终实现删除根文件夹内所有的文件和文件夹，并删除根文件夹。
 
### 2、异步回调的实现
 
同步的实现会阻塞代码的执行，每次执行一个文件操作，必须在执行完毕之后才能执行下一行代码，相对于同步，异步的方式性能会更好一些，我们下面使用异步回调的方式来实现递归删除文件目录的函数。
 
函数有两个参数，第一个参数同样为根文件夹的路径，第二个参数为一个回调函数，在文件目录被全部删除后执行。
 
```js
// 引入依赖模块
let fs = require("fs");
let path = require("path");

// 先序深度优先异步（回调函数）删除文件夹
function rmDirDepCb(p, callback) {
    // 获取传入路径的 Stats 对象
    fs.stat(p, (err, statObj) => {
        // 判断路径下是否为文件夹
        if (statObj.isDirectory()) {
            // 是文件夹则查看内部成员
            fs.readdir(p, (err, dirs) => {
                // 将文件夹成员拼接成合法路径的集合
                dirs = dirs.map(dir => path.join(p, dir));

                // next 方法用来检查集合内每一个路径
                function next(index) {
                    // 如果所有成员检查并删除完成则删除上一级目录
                    if (index === dirs.length) return fs.rmdir(p, callback);

                    // 对路径下每一个文件或文件夹执行递归，回调为递归 next 检查路径集合中的下一项
                    rmDirDepCb(dirs[index], () => next(index + 1));
                }
                next(0);
            });
        } else {
            // 是文件则直接删除
            fs.unlink(p, callback);
        }
    });
}

// 调用
rmDirDepCb("a", () => {
    console.log("删除完成");
});

// 删除完成
```
 
上面方法也遵循深度优先，与同步相比较主要思路是相同的，异步回调的实现更为抽象，并不是通过循环去处理的文件夹下的每个成员的路径，而是通过调用`next`函数和在成功删除文件时递归执行`next`函数并维护`index`变量实现的。
 
### 3、异步 Promise 的实现
 
在异步回调函数的实现方式中，回调嵌套层级非常多，这在对代码的可读性和维护性上都造成困扰，在 ES6 规范中，Promise 的出现就是用来解决 “回调地狱” 的问题，所以我们也使用 Promise 来实现。
 
函数的参数为要删除的根文件夹的路径，这次之所以不需要传`callback`参数是因为`callback`中的逻辑可以在调用函数之后链式调用`then`方法来执行。
 
```js
// 引入依赖模块
let fs = require("fs");
let path = require("path");

// 先序深度优先异步（Promise）删除文件夹
function rmDirDepPromise(p) {
    return new Promise((resolve, reject) => {
        // 获取传入路径的 Stats 对象
        fs.stat(p, (err, statObj) => {
            // 判断路径下是否为文件夹
            if (statObj.isDirectory()) {
                // 是文件夹则查看内部成员
                fs.readdir(p, (err, dirs) => {
                    // 将文件夹成员拼接成合法路径的集合
                    dirs = dirs.map(dir => path.join(p, dir));

                    // 将所有的路径都转换成 Promise
                    dirs = dirs.map(dir => rmDirDepPromise(dir));

                    // 数组中路径下所有的 Promise 都执行了 resolve 时，删除上级目录
                    Promise.all(dirs).then(() => fs.rmdir(p, resolve));
                });
            } else {
                // 是文件则直接删除
                fs.unlink(p, resolve);
            }
        });
    });
}

// 调用
rmDirDepPromise("a").then(() => {
    console.log("删除完成");
});

// 删除完成
```
 
与异步回调函数的方式不同的是在调用`rmDirDepPromise`时直接返回了一个 Promise 实例，而在删除文件成功或在删除文件夹成功时直接调用了`resolve`，在一个子文件夹下直接将这些成员通过递归`rmDirDepPromise`都转换为 Promise 实例，则可以用`Primise.all`来监听这些成员删除的状态，如果都成功再调用`Primise.all`的`then`直接删除上一级目录。
 
### 4、异步 async/await 的实现
 
Promise 版本相对于异步回调版本从代码的可读性上有所提升，但是实现逻辑还是比较抽象，没有同步代码的可读性好，如果想要 “鱼” 和 “熊掌” 兼得，既要性能又要可读性，可以使用 ES7 标准中的`async/await`来实现。
 
由于`async`函数的返回值为一个 Promise 实例，所以参数只需要传被删除的根文件夹的路径即可。
 
```js
// 引入依赖模块
let fs = require("fs");
let path = require("path");
let { promisify } = require("util");

// 将用到 fs 模块的异步方法转换成 Primise
let stat = promisify(fs.stat);
let readdir = promisify(fs.readdir);
let rmdir = promisify(fs.rmdir);
let unlink = promisify(fs.unlink);

// 先序深度优先异步（async/await）删除文件夹
async function rmDirDepAsync(p) {
    // 获取传入路径的 Stats 对象
    let statObj = await stat(p);

    // 判断路径下是否为文件夹
    if (statObj.isDirectory()) {
        // 是文件夹则查看内部成员
        let dirs = await readdir(p);

        // 将文件夹成员拼接成合法路径的集合
        dirs = dirs.map(dir => path.join(p, dir));

        // 循环集合递归 rmDirDepAsync 处理所有的成员
        dirs = dirs.map(dir => rmDirDepAsync(dir));

        // 当所有的成员都成功
        await Promise.all(dirs);

        // 删除该文件夹
        await rmdir(p);
    } else {
        // 是文件则直接删除
        await unlink(p);
    }
}

// 调用
rmDirDepAsync("a").then(() => {
    console.log("删除完成");
});

// 删除完成
```
 
在递归`rmDirDepAsync`时，所有子文件夹内部的成员必须都删除成功，才删除这个子文件夹，在使用`unlink`删除文件时，必须等待文件删除结束才能让 Promise 执行完成，所以也需要`await`，所有递归之前的异步 Promise 都需要在递归内部的异步 Promise 执行完成后才能执行完成，所以涉及到异步的操作都使用了`await`进行等待。
 
## 先序广度优先实现递归删除文件目录
 
广度优先的意思是遍历文件夹目录的时候，先遍历根文件夹，将内部的成员路径一个一个的存入数组中，再继续遍历下一层，再将下一层的路径都存入数组中，直到遍历到最后一层，此时数组中的路径顺序为第一层的路径，第二层的路径，直到最后一层的路径，由于要删除的文件夹必须为空，所以删除时，倒序遍历这个数组取出路径进行文件目录的删除。
 
 ![][3]
 
在广度优先的实现方式中同样按照同步、异步回调、和 异步`async/await`这几种方式分别来实现，因为在拼接存储路径数组的时候没有异步操作，所以单纯使用 Promise 没有太大的意义。
 
### 1、同步的实现
 
参数为根文件夹的路径，内部的`fs`方法同样都使用同步方法。
 
```js
// 引入依赖模块
let fs = require("fs");
let path = require("path");

// 先序广度优先同步删除文件夹
function rmDirBreSync(p) {
    let pathArr = [p]; // 创建存储路径的数组，默认存入根路径
    let index = 0; // 用于存储取出数组成员的索引
    let current; // 用于存储取出的成员，即路径

    // 如果数组中能找到当前指定索引的项，则执行循环体，并将该项存入 current
    while ((current = arr[index++])) {
        // 获取当前从数组中取出的路径的 Stats 对象
        let statObj = fs.statSync(current);

        // 如果是文件夹，则读取内容
        if (statObj.isDirectory()) {
            let dirs = fs.readdir(current);

            // 将获取到的成员路径处理为合法路径
            dirs = dirs.map(dir => path.join(current, dir));

            // 将原数组的成员路径和处理后的成员路径重新解构在 pathArr 中
            pathArr = [...pathArr, ...dirs];
        }
    }

    // 逆序循环 pathArr
    for (let i = pathArr.length - 1; i >= 0; i--) {
        let pathItem = pathArr[i]; // 当前循环项
        let statObj = fs.statSync(pathItem); // 获取 Stats 对象

        // 如果是文件夹则删除文件夹，是文件则删除文件
        if (statObj.isDirectory()) {
            fs.rmdirSync(pathItem);
        } else {
            fs.unlinkSync(pathItem);
        }
    }
}

// 调用
rmDirBreSync("a");
```
 
通过`while`循环广度遍历，将所有的路径按层级顺序存入`pathArr`数组中，在通过`for`反向遍历数组，对遍历到的路径进行判断并调用对应的删除方法，`pathArr`后面的项存储的都是最后一层的路径，从后向前路径的层级逐渐减小，所以反向遍历不会导致删除非空文件夹的操作。
 
### 2、异步回调的实现
 
函数有两个参数，第一个参数为根文件夹的路径，第二个为`callback`，在删除结束后执行。
 
```js
// 引入依赖模块
let fs = require("fs");
let path = require("path");

// 先序广度优先异步（回调函数）删除文件夹
function rmDirBreCb(p, callback) {
    let pathArr = [p]; // 创建存储路径的数组，默认存入根路径

    function next(index) {
        // 如果已经都处理完，则调用删除的函数
        if (index === pathArr.length) return remove();

        // 取出数组中的文件路径
        let current = arr[index];

        // 获取取出路径的 Stats 对象
        fs.stat(currrent, (err, statObj) => {
            // 判断是否是文件夹
            if (statObj.isDirectory()) {
                // 是文件夹读取内部成员
                fs.readdir(current, (err, dirs) => {
                    // 将数组中成员名称修改为合法路径
                    dirs = dirs.map(dir => path.join(current, dir));

                    // 将原数组的成员路径和处理后的成员路径重新解构在 pathArr 中
                    pathArr = [...pathArr, ...dirs];

                    // 递归取出数组的下一项进行检测
                    next(index + 1);
                });
            } else {
                // 如果是文件则直接递归获取数组的下一项进行检测
                next(index + 1);
            }
        });
    }
    next(0);

    // 删除的函数
    function remove() {
        function next(index) {
            // 如果全部删除完成，执行回调函数
            if (index < 0) return callback();

            // 获取数组的最后一项
            let current = pathArr[index];

            // 获取该路径的 Stats 对象
            fs.stat(current, (err, statObj) => {
                // 不管是文件还是文件夹都直接删除
                if (statObj.isDirectory()) {
                    fs.rmdir(current, () => next(index - 1));
                } else {
                    fs.unlink(current, () => next(index - 1));
                }
            });
        }
        next(arr.length - 1);
    }
}

// 调用
rmDirBreCb("a", () => {
    console.log("删除完成");
});

// 删除完成
```
 
在调用`rmDirBreCb`时主要执行两个步骤，第一个步骤是构造存储路径的数组，第二个步骤是逆序删除数组中对应的文件或文件夹，为了保证性能，两个过程都是通过递归`next`函数并维护存储索引的变量来实现的，而非循环。
 
在构造数组的过程中如果构造数组完成后，调用的删除函数`remove`，在`remove`中在删除完成后，调用的`callback`，实现思路是相同的，都是在递归时设置判断条件，如果构造数组或删除结束以后不继续递归，而是直接执行对应的函数并跳出。
 
### 3、异步 async/await 的实现
 
参数为删除根文件夹的路径，因为`async`最后返回的是 Promise 实例，所以不需要`callback`，删除后的逻辑可以通过调用返回 Promise 实例的`then`来实现。
 
```js
// 引入依赖模块
let fs = require("fs");
let path = require("path");
let { promisify } = require("util");

// 将用到 fs 模块的异步方法转换成 Primise
let stat = promisify(fs.stat);
let readdir = promisify(fs.readdir);
let rmdir = promisify(fs.rmdir);
let unlink = promisify(fs.unlink);

// 先序广度优先异步（async/await）删除文件夹
async function rmDirBreAsync(p) {
    let pathArr = [p]; // 创建存储路径的数组，默认存入根路径
    let index = 0; // 去数组中取出路径的索引

    // 如果存在该项则继续循环
    while (index !== pathArr.length) {
        // 取出当前的路径
        let current = pathArr[index];

        // 获取 Stats 对象
        let statObj = await stat(current);

        // 判断是否是文件夹
        if (statObj.isDirectory()) {
            // 查看文件夹成员
            let dirs = await readdir(current);

            // 将路径集合更改为合法路径集合
            dirs = dirs.map(dir => path.join(current, dir));

            // 合并存储路径的数组
            pathArr = [...pathArr, ...dirs];
        }
        index++;
    }

    let current; // 删除的路径

    // 循环取出路径
    while ((current = pathArr.pop())) {
        // 获取 Stats 对象
        let statObj = await stat(current);

        // 不管是文件还是文件夹都直接删除
        if (statObj.isDirectory()) {
            await rmdir(current);
        } else {
            await unlink(current);
        }
    }
}

// 调用
rmDirBreAsync("a").then(() => {
    console.log("删除完成");
});

// 删除完成
```
 
上面的写法都是使用同步的写法，但对文件的操作都是异步的，并使用`await`进行等待，在创建路径集合的数组和倒序删除的过程都是通过`while`循环实现的。
 


[4]: https://link.juejin.im?target=https%3A%2F%2Fwww.pandashen.com%2F2018%2F06%2F30%2F20180630172601%2F
[0]: https://img0.tuicool.com/e6NFvuB.png 
[1]: https://img1.tuicool.com/Y3uyYff.png 
[2]: https://img1.tuicool.com/uy6FJv6.png 
[3]: https://img1.tuicool.com/bUZFZ3V.png 