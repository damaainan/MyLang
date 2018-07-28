## js数据结构与算法--单链表的实现与应用思考

来源：[https://www.cnblogs.com/weiqinl/p/9253044.html](https://www.cnblogs.com/weiqinl/p/9253044.html)

2018-07-02 15:22

[链表][100]是动态的数据结构，它的每个元素由一个存储元素本身的节点和一个指向下一个元素的引用（也称指针或链接）组成。

![][0]

现实中，有一些链表的例子。

第一个就是寻宝的游戏。你有一条线索，这条线索是指向寻找下一条线索的地点的指针。你顺着这条链接去下一个地点，得到另一条指向下一处的线索。得到列表中间的线索的唯一办法，就是从起点（第一条线索）顺着列表寻找。

第二个例子是火车。一列火车是由一些车厢组成的。每节车厢都是相互连接。你很容易分离一节车皮，改变它的位置，添加或移除它。每节车厢都是列表的元素，车厢间的连接就是指针。
## 链表的实现

链表有多种不同的类型，单链表，双向链表，循环链表等。

我们先实现单链表。单链表是一种链式存取的数据结构。

linkednode.js文件，里面包含了链表中节点的项

```js

/**

 * 链表节点，链表中的项，链表中的节点

 */

export class Node {

  constructor(element, next = null) {

    this.element = element // 链表中节点的值

    this.next = next // 指向列表中下一个节点项的指针

  }

}

```

linkedlist.js文件，链表各种方法的实现

```js

import { Node } from './linkednode'



/**

 * 链表类

 */

export default class LinkedList {

  constructor() {

    this.length = 0 // 存储链表中列表项的数量

    this.head = null // 存储链表中第一个节点的引用

  }



  /**

   * 向列表尾部添加一个新的项

   * @param {*} element 需要添加至链表中的节点项

   */

  append(element) {

    let node = new Node(element) // 将新项创建为符合链表结构的列表项

    if (this.head === null) {

      // 链表中的元素为空

      this.head = node

    } else {

      let current = this.head // 将第一个节点的引用赋值给当前项

      // 循环列表，直到找到最后一项

      while (current.next) {

        current = current.next

      }

      // 找到最后一项，将其next赋为node，建立链接

      current.next = node

    }

    this.length++ // 更新链表的长度

  }



  /**

   * 向列表的特定位置插入一个新的项

   * @param {*} position 插入链表中的位置

   * @param {*} element 需要添加的节点

   */

  insert(position, element) {

    let node = new Node(element)

    // 检查越界

    if (position > -1 && position <= this.length) {

      let current = this.head

      let previous

      let index = 0



      // 在第一个位子添加

      if (position === 0) {

        node.next = current

        this.head = node

      } else {

        // 需要找到特定的位子，将想要插入的元素放在previous节点和current节点之间

        while (index++ < position) {

          // previous 将是对想要插入新元素的位置之前一个元素的引用

          previous = current

          // current 对想要插入新元素的位置之后一个元素的引用

          current = current.next

        }

        node.next = current

        previous.next = node

      }

      this.length++

      return true

    } else {

      return false

    }

  }

  /**

   * 移除指定位置的节点元素,并返回移除的项

   * 如果超出了链表的范围，则返回null

   * @param {Int32Array} position 链表中的位置

   */

  removeAt(position) {

    // 检查越界

    if (position > -1 && position < this.length) {

      let current = this.head

      let previous // 先前一个节点

      let index = 0 // 当前节点的位子



      // 移除第一项

      if (position === 0) {

        this.head = current.next

      } else {

        while (index++ < position) {

          previous = current

          current = current.next

        }

        // 将previous 与 current 的下一项链接起来：跳过current，从而移除它

        // 当前元素会丢弃在计算机内存中，等待GC清除

        previous.next = current.next

      }

      this.length-- // 链表元素数量减1

      return current.element // 返回移除的项

    } else {

      return null // 如果超出了链表的范围，则返回null

    }

  }



  /**

   * 从列表中移除一项

   * 先找出元素的索引项，再根据索引移除元素

   * @param {*} element 列表中的元素

   */

  remove(element) {

    let index = this.indexOf(element)

    return this.removeAt(index)

  }



  /**

   * 返回元素在列表中的索引。如果列表中没有该元素则返回-1

   * @param {*} element 元素

   */

  indexOf(element) {

    let current = this.head

    let index = 0 // 计算位置数

    while (current) {

      if (element === current.element) {

        return index

      }

      index++

      current = current.next

    }

    return -1

  }



  /**

   * 判断是否为空链表

   * 空链表返回true，非空(链表长度大于0)返回false

   */

  isEmpty() {

    return this.size() === 0

  }



  /**

   * 返回链表包含的元素个数。与数组的length属性类似

   */

  size() {

    return this.length

  }



  /**

   * 获取链表的表头节点

   * head变量是LinkedList类的私有变量。

   * 但是，我们需要实现在类的外部循环访问列表。

   * 此时，就需要提供获取类的第一个元素的方法

   */

  getHead() {

    return this.head

  }



  /**

   * 由于列表项使用了Node类，需要重写toString方法，让其只输出元素的值。

   */

  toString() {

    let current = this.head

    let string = ''

    while (current) {

      string += current.element + (current.next ? '-->' : '')

      current = current.next

    }

    return string

  }

}

```

[查看源代码，使用JEST，进行单元测试][101]
## 链表的应用思考

我们先比较下JavaScript中[链表][100]与数组的区别：


* 链表中的元素是不连续的，而数组中的元素是连续的。

* 链表添加或移除元素的时候不需要移动其他元素，而数组需要。

* 链表需要指针，而数组不需要。

* 链表需要从表头开始迭代列表直到找到所需要的元素。数组则可以直接访问任何位置的任何元素。

* 两者都具有动态性。关于数组动态性。数组在js中是一个可以修改的对象，添加移除元素，它会动态的变化，但是成本很高，需要移动元素。在大多数语言中（比如C和Java），数组的大小是固定的，想添加元素就要创建一个全新的数组，不能简单地往其中添加所需的元素。



要存储多个元素，数组可能是最常用的数据结构。但是，如果要存储数据，并且会有移除或者添加大量数据时候，链表比数组更实用。

[更多实例，请查看源码][103]

[0]: https://images2018.cnblogs.com/blog/564792/201807/564792-20180702113140935-1469396239.png
[100]: https://github.com/weiqinl/javascript-datastructures-algorithms/tree/master/src/data-structures/linkedlist
[101]: https://github.com/weiqinl/javascript-datastructures-algorithms/tree/master/src/data-structures/linkedlist
[102]: https://github.com/weiqinl/javascript-datastructures-algorithms/tree/master/src/data-structures/linkedlist
[103]: https://github.com/weiqinl/javascript-datastructures-algorithms