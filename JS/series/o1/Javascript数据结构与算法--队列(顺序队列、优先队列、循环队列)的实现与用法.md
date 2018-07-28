## Javascript数据结构与算法--队列(顺序队列、优先队列、循环队列)的实现与用法

来源：[https://www.cnblogs.com/weiqinl/p/9234891.html](https://www.cnblogs.com/weiqinl/p/9234891.html)

2018-06-27 17:09


## 前言

队列和栈非常类似，前面已经讲过了[栈的实现与用法][100]，现在我们来说说队列。
## 队列介绍

队列遵循FIFO（First In First Out，先进先出）原则的一组有序的项。

队列是一种特殊的线性表，特殊之处在于它只允许在表的前端（front）进行删除操作，而在表的后端（rear）进行插入操作，和栈一样，队列是一种操作受限制的线性表。进行插入操作的端称为队尾，进行删除操作的端称为队头。

队列有顺序队列，还有其他修改版本的队列，比如：优先队列、循环队列。
## 顺序队列

顺序队列是队列的顺序存储结构，它是运算受限制的顺序表(线性表)。建立顺序队列结构必须为其静态分配或动态申请一片连续的存储空间，并设置两个指针进行管理。一个是队头指针front，它指向队头元素；另一个是队尾指针rear，它指向下一个入队元素的存储位置，如图所示。

![][0]

生活中，各种排队现象。例如：排队买票，新来的人，排在队尾，相当于添加操作。队头的人先买票，买完票离开队列，相当于删除操作。而添加的操作却只能在队列的尾部进行，因此新来的人就只能排在队列的最后。
### 创建队列

队列中的元素，可以使用链表存储，也可以使用数组存储。我们使用数组来存储队列中的元素。

```js

/**
 * 队列
 * 我们使用数组来存储队列中的元素
 * 
 *=====队列的入队、出队示意图========
 *
 * 出队 ----------------- 入队
 * <--- A1,A2,A3,...,An <---
 * -----------------
 *
 *================================
*/
export default class Queue {
  constructor() {
    this.items = [];
  }
  /**
   * 向队尾添加一个（或多个）新的元素
   * @param {*} element 新元素
   */
  enqueue(element) {
    this.items.push(element)
  }
  /**
   * 移除队列的第一（即排在队列最前面的）项，并返回被移除的元素
   */
  dequeue() {
    // 根据队列的先进先出原则，使用shift方法
    // shift方法会从数组中移除存储在索引为0的元素
    return this.items.shift()
  }
  /**
   * 返回队列中的第一个元素--最先被添加，也将是最先被移除的元素。
   * 队列不做任何变动（不移除元素，只返回元素信息）
   */
  front() {
    return this.items[0]
  }


  /**
   * 清除队列中的所有元素
   */
  clear() {
    this.items = []
  }

  /**
   * 如果队列中不包含任何元素，返回true，否则返回false
   */
  isEmpty() {
    return this.items.length === 0
  }
  /**
   * 返回队列包含的元素个数，与数组length属性类似
   */
  size() {
    return this.items.length
  }
  /**
   * 队列内容字符串化
   */
  toString() {
    return this.items.toString()
  }
}

```
### 顺序队列应用

打印机，有一个打印队列，谁先进入队列，谁就先打印。

```js

/**
 * 打印队列的内容
 * @param {Array} queueArr 需要打印的数组
 */
function print(queueArr) {
  let queue = new Queue()
  let s = ''
  /**
   * 检查参数类型是否为数组
   */
  if (queueArr instanceof Array) {
    /**
     * 将需要打印内容添加到队列
     */
    for (let i = 0; i < queueArr.length; i++) {
      queue.enqueue(queueArr[i])
    }

    /**
     * 将队头的数据取出
     */
    while (!queue.isEmpty()) {
      s += queue.dequeue() + ', '
    }
    s = s.substr(0, s.length - 2)
  }
  return s;
}

```

[更多内容请查看源码][101]
## 优先队列

队列有顺序队列，还有其他修改版本的队列，比如：循环队列、优先队列

优先队列是顺序队列的修改版本，元素的添加和移除是基于优先级的。一个现实例子是，在银行排队办业务的顺序。VIP客户的优先级要高于普通客户的。另一个例子是医院的急诊科候诊室。医生会优先处理病情比较严重的患者。通常，护士会鉴别分类，根据患者病情的严重程度放号。

实现一个优先队列，有两种选项：

* 设置优先级，然后在正确的位置添加元素。（优先添加，正常出队）

* 用入列操作添加元素，然后按照优先级移除它们。（正常添加，优先出队）


### 优先队列的实现

我们在这里将会使用第一种方式，在正确的位置添加元素，因此可以对它们使用默认的出列操作。

queueElement.js 文件

```js

// queueElement.js

/**
 * 优先队列中的元素，包含元素和优先级
 */
export default class QueueElement {
  /**
   * 
   * @param {*} element 队列的元素
   * @param {*} priority 优先级
   */
  constructor(element, priority) {
    this.element = element
    this.priority = priority
  }
}

```

priorityQueue.js文件

```js

// priorityQueue.js

import QueueElement from "./queueElement";


/**
 * 最小优先队列
 */
export default class PriorityQueue {
  constructor() {
    this.items = []
  }
  /**
   * 在正确的位置添加元素
   * @param {*} element 要添加的元素
   * @param {Int32Array} priority 优先级
   */
  enqueue(element, priority) {
    let queueElement = new QueueElement(element, priority)
    let added = false
    for (let i = 0; i < this.items.length; i++) {
      // 当找到一个比要添加的元素的优先级更高的项时，将新元素插入到它之前。
      if (queueElement.priority < this.items[i].priority) {
        this.items.splice(i, 0, queueElement) // 插入新元素
        added = true
        break // 终止队列循环
      }
    }
    // 当需要添加的元素优先级大于队列中的任何一个元素的时候，把该元素添加到队尾。
    if (!added) {
      this.items.push(queueElement)
    }
  }

  /**
   * 打印队列中的元素（包含优先级）
   */
  print() {
    for (let i = 0; i < this.items.length; i++) {
      console.log(`${i + 1} - ${this.items[i].element} - ${this.items[i].priority}`)
    }
  }
  /**
   * 移除队列的第一（即排在队列最前面的）项，并返回被移除的元素
   */
  dequeue() {
    // 根据队列的先进先出原则，使用shift方法
    // shift方法会从数组中移除存储在索引为0的元素
    return this.items.shift()
  }

  /**
   * 返回队列中的第一个元素--最先被添加，也将是最先被移除的元素。
   * 队列不做任何变动（不移除元素，只返回元素信息）
   */
  front() {
    return this.items[0]
  }
  /**
   * 清除队列中的所有元素
   */
  clear() {
    this.items = []
  }
  /**
   * 如果队列中不包含任何元素，返回true，否则返回false
   */
  isEmpty() {
    return this.items.length === 0
  }


  /**
   * 返回队列包含的元素个数，与数组length属性类似
   */
  size() {
    return this.items.length
  }

  /**
   * 队列内容字符串化
   */
  toString() {
    return this.items.toString()
  }

}

```
### 优先队列的应用

```js

    let priorityQueue = new PriorityQueue()

    priorityQueue.enqueue('wei', 2)

    priorityQueue.enqueue('qin', 3)

    priorityQueue.enqueue('world', 1)

    priorityQueue.enqueue('china', 1)

    priorityQueue.print()

```

输出结果

```

1 - wei - 1

2 - world - 1

3 - china - 1

4 - qin - 2

```

[查看源码详情][102]
## 循环队列

循环队列的一个例子就是击鼓传花的游戏。在这个游戏中，孩子们围成一个圆圈，把花尽快的传递给旁边的人。某一时刻传花停止，这个时候花在谁手里，谁就退出圆圈结束游戏。重复这个过程，直到只剩一个孩子（胜者）。

另一个类似的案例是，[约瑟夫环问题][103]。

下面，我们以击鼓传花游戏来分析。

```js
import Queue from "./queue-array";

export default class CircleQueue {
  constructor() {}
  hotPotato(nameList, num) {
    // 利用顺序队列创建的队列，来完成循环队列
    let queue = new Queue()
    for (let i = 0; i < nameList.length; i++) {
      queue.enqueue(nameList[i])
    }
    let eliminated = '';
    while (queue.size() > 1) {
      // 此过程将队列变成循环队列
      for (let i = 0; i < num; i++) {
        queue.enqueue(queue.dequeue());
      }
      eliminated = queue.dequeue();
      console.log(eliminated + '在击鼓传花游戏中被淘汰')
    }
    // 返回最后胜利者
    return queue.dequeue()
  }

}
```

[查看源码详情][104]

以上所有的队列，都是在数组结构的基础上创建和应用的。

[完]

[0]: https://images2018.cnblogs.com/blog/564792/201806/564792-20180627165845995-1033405030.png
[100]: https://www.cnblogs.com/weiqinl/p/9173602.html
[101]: https://github.com/weiqinl/javascript-datastructures-algorithms/blob/master/src/algorithms/queue/print.js
[102]: https://github.com/weiqinl/javascript-datastructures-algorithms/blob/master/src/data-structures/queue/priorityQueue.js
[103]: https://baike.baidu.com/item/%E7%BA%A6%E7%91%9F%E5%A4%AB%E7%8E%AF/348830?fr=aladdin
[104]: https://github.com/weiqinl/javascript-datastructures-algorithms/blob/master/src/data-structures/queue/circleQueue.js