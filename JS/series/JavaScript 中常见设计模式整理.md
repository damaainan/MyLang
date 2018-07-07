## JavaScript 中常见设计模式整理

来源：[http://muyunyun.cn/posts/ed7c4af7/](http://muyunyun.cn/posts/ed7c4af7/)

时间 2018-05-18 13:49:37

[https://github.com/MuYunyun/blog](https://github.com/MuYunyun/blog)

![][0]
 
开发中，我们或多或少地接触了设计模式，但是很多时候不知道自己使用了哪种设计模式或者说该使用何种设计模式。本文意在梳理常见设计模式的特点，从而对它们有比较清晰的认知。
 
### JavaScript 中常见设计模式 
 
 
* [单例模式][1]  
* [策略模式][2]  
* [代理模式][3]  
* [迭代器模式][4]  
* [发布-订阅模式][5]  
* [命令模式][6]  
* [组合模式][7]  
* [模板方法模式][8]  
* [享元模式][9]  
* [职责链模式][10]  
* [中介者模式][11]  
* [装饰者模式][12]  
* [状态模式][13]  
* [适配者模式][14]  
 
 
### 各设计模式关键词 
 
看完了上述设计模式后，把它们的关键词特点罗列出来，以后提到某种设计模式，进而联想相应的关键词和例子，从而心中有数。
 
| 设计模式 | 特点 | 案例 | 
|-|-|-|
| 单例模式 | 一个类只能构造出唯一实例 | [创建菜单对象][15] | 
| 策略模式 | 根据不同参数可以命中不同的策略 | [动画库里的算法函数][16] | 
| 代理模式 | 代理对象和本体对象具有一致的接口 | [图片预加载][17] | 
| 迭代器模式 | 能获取聚合对象的顺序和元素 | `each([1, 2, 3], cb)` | 
| 发布-订阅模式 | PubSub | [瀑布流库][18] | 
| 命令模式 | 不同对象间约定好相应的接口 | [按钮和命令的分离][19] | 
| 组合模式 | 组合模式在对象间形成一致对待的树形结构 | [扫描文件夹][20] | 
| 模板方法模式 | 父类中定好执行顺序 | [咖啡和茶][21] | 
| 享元模式 | 减少创建实例的个数 | [男女模具试装][22] | 
| 职责链模式 | 通过请求第一个条件，会持续执行后续的条件，直到返回结果为止 | [if else 优化][23] | 
| 中介者模式 | 对象和对象之间借助第三方中介者进行通信 | [测试结束告知结果][24] | 
| 装饰者模式 | 动态地给函数赋能 | [天冷了穿衣服，热了脱衣服][25] | 
| 状态模式 | 每个状态建立一个类，状态改变会产生不同行为 | [电灯换挡][26] | 
| 适配者模式 | 一种数据结构改成另一种数据结构 | [枚举值接口变更][27] | 
 
 


[1]: https://github.com/MuYunyun/blog/blob/master/Basic%20Skill/%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F/%E5%8D%95%E4%BE%8B%E6%A8%A1%E5%BC%8F.md
[2]: https://github.com/MuYunyun/blog/blob/master/Basic%20Skill/%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F/%E7%AD%96%E7%95%A5%E6%A8%A1%E5%BC%8F.md
[3]: https://github.com/MuYunyun/blog/blob/master/Basic%20Skill/%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F/%E4%BB%A3%E7%90%86%E6%A8%A1%E5%BC%8F.md
[4]: https://github.com/MuYunyun/blog/blob/master/Basic%20Skill/%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F/%E8%BF%AD%E4%BB%A3%E5%99%A8%E6%A8%A1%E5%BC%8F.md
[5]: https://github.com/MuYunyun/blog/blob/master/Basic%20Skill/%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F/%E5%8F%91%E5%B8%83%E8%AE%A2%E9%98%85%E6%A8%A1%E5%BC%8F.md
[6]: https://github.com/MuYunyun/blog/blob/master/Basic%20Skill/%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F/%E5%91%BD%E4%BB%A4%E6%A8%A1%E5%BC%8F.md
[7]: https://github.com/MuYunyun/blog/blob/master/Basic%20Skill/%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F/%E7%BB%84%E5%90%88%E6%A8%A1%E5%BC%8F.md
[8]: https://github.com/MuYunyun/blog/blob/master/Basic%20Skill/%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F/%E6%A8%A1%E6%9D%BF%E6%96%B9%E6%B3%95%E6%A8%A1%E5%BC%8F.md
[9]: https://github.com/MuYunyun/blog/blob/master/Basic%20Skill/%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F/%E4%BA%AB%E5%85%83%E6%A8%A1%E5%BC%8F.md
[10]: https://github.com/MuYunyun/blog/blob/master/Basic%20Skill/%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F/%E8%81%8C%E8%B4%A3%E9%93%BE%E6%A8%A1%E5%BC%8F.md
[11]: https://github.com/MuYunyun/blog/blob/master/Basic%20Skill/%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F/%E4%B8%AD%E4%BB%8B%E8%80%85%E6%A8%A1%E5%BC%8F.md
[12]: https://github.com/MuYunyun/blog/blob/master/Basic%20Skill/%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F/%E8%A3%85%E9%A5%B0%E8%80%85%E6%A8%A1%E5%BC%8F.md
[13]: https://github.com/MuYunyun/blog/blob/master/Basic%20Skill/%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F/%E7%8A%B6%E6%80%81%E6%A8%A1%E5%BC%8F.md
[14]: https://github.com/MuYunyun/blog/blob/master/Basic%20Skill/%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F/%E9%80%82%E9%85%8D%E8%80%85%E6%A8%A1%E5%BC%8F.md
[15]: https://github.com/MuYunyun/blog/blob/master/Basic%20Skill/%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F/%E5%8D%95%E4%BE%8B%E6%A8%A1%E5%BC%8F.md
[16]: https://github.com/MuYunyun/blog/blob/master/Basic%20Skill/%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F/%E7%AD%96%E7%95%A5%E6%A8%A1%E5%BC%8F.md
[17]: https://github.com/MuYunyun/blog/blob/master/Basic%20Skill/%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F/%E4%BB%A3%E7%90%86%E6%A8%A1%E5%BC%8F.md
[18]: https://github.com/MuYunyun/waterfall/blob/0f229c1a2881d26166b92aa746b7f892af59c28f/waterfall.js#L8
[19]: https://github.com/MuYunyun/blog/blob/master/Basic%20Skill/%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F/%E5%91%BD%E4%BB%A4%E6%A8%A1%E5%BC%8F.md
[20]: https://github.com/MuYunyun/blog/blob/master/Basic%20Skill/%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F/%E5%91%BD%E4%BB%A4%E6%A8%A1%E5%BC%8F.md
[21]: https://github.com/MuYunyun/blog/blob/master/Basic%20Skill/%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F/%E6%A8%A1%E6%9D%BF%E6%96%B9%E6%B3%95%E6%A8%A1%E5%BC%8F.md
[22]: https://github.com/MuYunyun/blog/blob/master/Basic%20Skill/%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F/%E4%BA%AB%E5%85%83%E6%A8%A1%E5%BC%8F.md
[23]: https://github.com/MuYunyun/blog/blob/master/Basic%20Skill/%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F/%E8%81%8C%E8%B4%A3%E9%93%BE%E6%A8%A1%E5%BC%8F.md
[24]: https://github.com/MuYunyun/blog/blob/master/Basic%20Skill/%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F/%E4%B8%AD%E4%BB%8B%E8%80%85%E6%A8%A1%E5%BC%8F.md
[25]: https://github.com/MuYunyun/blog/blob/master/Basic%20Skill/%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F/%E8%A3%85%E9%A5%B0%E8%80%85%E6%A8%A1%E5%BC%8F.md
[26]: https://github.com/MuYunyun/blog/blob/master/Basic%20Skill/%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F/%E7%8A%B6%E6%80%81%E6%A8%A1%E5%BC%8F.md
[27]: https://github.com/MuYunyun/blog/blob/master/Basic%20Skill/%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F/%E9%80%82%E9%85%8D%E8%80%85%E6%A8%A1%E5%BC%8F.md
[0]: https://img0.tuicool.com/ABfEraZ.jpg!web