## Node.js 的 SQLite 教程

来源：[https://www.oschina.net/translate/a-sqlite-tutorial-with-node-js](https://www.oschina.net/translate/a-sqlite-tutorial-with-node-js)

时间 2018-06-04 14:17:16

 
  
![][0]
 
在本教程中，我将演示如何结合sqlite3 Node.js驱动程序在Node.js环境中使用SQLite。 对于那些不熟悉 [SQLite][1] 的人来说，它是一个简单的单文件关系数据库，在智能设备，嵌入式系统甚至小型Web应用程序中非常流行。
 

#### 设置和安装
 
我将首先在名为node-sqlite-tutorial的空目录中使用npm init创建一个新的npm包。
 
``` 
$ npm init
This utility will walk you through creating a package.json file.  
It only covers the most common items, and tries to guess sane defaults.

See `npm help json` for definitive documentation on these fields  
and exactly what they do.

Use `npm install--save` afterwards to install a package and   save it as a dependency in the package.json file.

Press ^C at any time to quit.   name: (app) node-sqlite   version: (0.0.0) 0.1.0  
description: Code for tutorial blog on node and sqlite  
entry point: (index.js) main.js   test command:  
git repository:  
keywords:  
author: Adam McQuistan  
license: (BSD) MIT  
About to write to /node-sqlite/app/package.json:

{
  "name": "node-sqlite",
  "version": "0.1.0",
  "description": "Code for tutorial blog on node and sqlite",
  "main": "main.js",
  "scripts": {
    "test": "echo \"Error: no test specified\" && exit 1"   },
  "repository": "",
  "author": "Adam McQuistan",
  "license": "MIT" } Is this ok? (yes)
```
 
接下来，我将需要通过npm安装 [sqlite3][2] 包，如下所示：
 
``` 
$ npm install --save sqlite3
```
 
除了sqlite3之外，我将安装 [Bluebird][3] ，以便在数据库编程中使用熟悉的promise功能。
 
``` 
$ npm install --save bluebird
```
 
现在我  将在package.json文件同级目录下创建一个空文件，  称为database.sqlite3，   SQLite会将数据存储进去  。
 
 
 
  

#### 设计数据库
 
与我的其他几篇文章中说的一样，我将使用一个编写好的应用程序来帮助描述使用Node.js和SQLite进行数据库编程的一些重点。 对于本文，我假设我正在为项目和任务跟踪应用程序构建数据访问层。 这个应用程序的数据访问层的基本业务规则如下：
 

 
* 该应用程序有一些项目
  
* 每个项目可以有一个或多个任务来完成
  
  
 
随着业务规则的陈述，我可以掌握这些信息，并开始设计必要的表格和他们的范围。 很显然，我需要一个 **`项目(projects)`**  表以及一个 **`任务(tasks)`**  表。 其余的只是我的一点直觉设计的，一些编写测试数据，并与它一起推进版本（大多数开发人员的共同工作特征）。
 
projects table 

| id | name | 
|-|-|
| 1 | Write Node.js - SQLite Tutorial | 
  
 
tasks table 

| id | name | description | isCompleted | projectId | 
|-|-|-|-|-|
| 1 | Outline | High level overview of sections | 1 | 1 | 
| 2 | Write | Write article contents and code examples | 0 | 1 | 
  
 
好吧，现在我知道我需要创建什么了，现在可以将它编写成代码。
 
 
 
  

#### 创建数据库
 
一开始，我需要在package.json文件所在的目录中创建一个main.js文件以及一个dao.js（或 [ 数据访问对象 ][4] ）文件。
 
在dao.js文件中，我将引入sqlite3和Bluebird的Promise对象。 之后，我将脚手架创建出一个名为AppDAO的数据访问类，它将在构造函数内建立与数据库的连接并将其分配给名为db的成员字段。
 
```js
// dao.js 
const sqlite3 = require('sqlite3')   
const Promise = require('bluebird') class AppDAO {  
  constructor(dbFilePath) {
    this.db = new sqlite3.Database(dbFilePath, (err) => {
      if (err) {
        console.log('Could not connect to database', err)
      } else {
        console.log('Connected to database')
      }
    })
  }
} module.exports = AppDAO
```
 
连接非常简单。 你可以通过传递SQLite数据库文件的路径来实例化sqlite3 Database类的构造函数，并且可以选择检查可能发生的错误。 如上所述，我将这个数据库连接对象存储在AppDAO类里的名为db的字段中。
 
 
 
  
我将通过解释如何使用连接对象来向数据库提交查询的方式进行。 sqlite3 Node.js包为执行查询提供了一些不同的方法，但是在本教程中需要关注的内容包括：
 

 
* run：用于创建或更改表格并插入或更新表格数据
  
* get：从一个或多个表中选择一行数据
  
* all：从一个或多个表中选择多行数据
  
  
 
首先，我想探索一下run方法。 它的一般语法如下所示：
 
```js
db.run('SOME SQL QUERY', [param1, param2], (err) => {  
  if (err) {
    console.log('ERROR!', err)
  }
})
```
 
传递给run(...)的第一个参数是一个要执行的SQL查询的字符串，并且是唯一必需的参数。 第二个是可选的参数数组，sqlite3库将替换任何'？' 查询中的占位符（我将稍微演示一下）。 最后是一个错误回调函数。
 
 
 
  
你可能会猜测我将使用run（...）函数来创建和更新我的项目和任务。 不过，我实际上会将它封装在我自己的AppDAOclass上的run方法版本中，因为我想将它封装在bluebird Promise中，以使事件明确是异步的并基于promise，如下所示：
 
```js
// dao.js

const sqlite3 = require('sqlite3')  
const Promise = require('bluebird')

class AppDAO {  
  // omitting constructor code

  run(sql, params = []) {
    return new Promise((resolve, reject) => {
      this.db.run(sql, params, function (err) {
        if (err) {
          console.log('Error running sql ' + sql)
          console.log(err)
          reject(err)
        } else {
          resolve({ id: this.lastID })
        }
      })
    })
  }
}
```
 
使用我自定义的AppDAO.run（...）方法，我现在可以将它用于创建产品和任务表。
 
首先，我在项目中添加两个名为projectrepository.js和taskrepository.js的文件。 在project_repository.js文件内部，我定义了一个名为ProjectRepository的类，它具有一个接受AppDAO对象实例的构造函数和一个用以执行如下DDL（数据定义语言）SQL的createTable方法：
 
```js
// project_repository.js

class ProjectRepository {  
  constructor(dao) {
    this.dao = dao
  }

  createTable() {
    const sql = `
    CREATE TABLE IF NOT EXISTS projects (
      id INTEGER PRIMARY KEY AUTOINCREMENT,
      name TEXT)`
    return this.dao.run(sql)
  }
}
```
 
然后，我又做了基本同样的事情，但这次是在task_repository.js文件中。
 
```js
// task_repository.js

class TaskRepository {  
  constructor(dao) {
    this.dao = dao
  }

  createTable() {
    const sql = `
      CREATE TABLE IF NOT EXISTS tasks (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        name TEXT,
        description TEXT,
        isComplete INTEGER DEFAULT 0,
        projectId INTEGER,
        CONSTRAINT tasks_fk_projectId FOREIGN KEY (projectId)
          REFERENCES projects(id) ON UPDATE CASCADE ON DELETE CASCADE)`
    return this.dao.run(sql)
  }
}
```
 
以上用于创建表的DDL SQL步骤已完成，因此接下来我将继续讨论如何将数据插入表的方法。
 
 
 
  

#### 插入数据
 
在ProjectRepository类中，我需要添加一个create方法，该方法接收要创建的项目名称，并使用AppDAO.run（...）方法执行相应的INSERT语句。 注意我是如何使用'？'来表示项目名称的值，然后将name参数放入可选的params数组参数中，传递给run（...）方法。 这被称为参数化查询语句，它将清除输入以尽量减少SQL注入风险。
 
```js
// project_repository.js

class ProjectRepository {  
  // omitting other methods

  create(name) {
    return this.dao.run(
      'INSERT INTO projects (name) VALUES (?)',
      [name])
  }
}
```
 
TaskRepository类需要如下类似的创建方法。
 
```js
// task_repository.js

class TaskRepository {  
  // omitting other methods

  create(name, description, isComplete, projectId) {
    return this.dao.run(
      `INSERT INTO tasks (name, description, isComplete, projectId)
        VALUES (?, ?, ?, ?)`,
      [name, description, isComplete, projectId])
  }
}
```
 
现在我可以将数据插入数据库了，然后我想添加更新功能。
 
 
 
  

#### 更新数据
 
在ProjectRepository类中，我将添加一个更新方法，该方法使用AppDAO.run（...）方法获取项目对象并再次更新该项目数据库记录的所有字段，如下所示：
 
```js
// project_repository.js

class ProjectRepository {  
  // omitting other methods

  update(project) {
    const { id, name } = project
    return this.dao.run(
      `UPDATE projects SET name = ? WHERE id = ?`,
      [name, id]
    )
  }
}
```
 
接下来是将相应的更新方法添加到TaskRepository类中。
 
```js
// task_repository.js

class TaskRepository {  
  // omitting other methods

  update(task) {
    const { id, name, description, isComplete, projectId } = task
    return this.dao.run(
      `UPDATE tasks
      SET name = ?,
        description = ?,
        isComplete = ?,
        projectId = ?
      WHERE id = ?`,
      [name, description, isComplete, projectId, id]
    )
  }
}
```
 

#### 删除数据
 
最后实现的功能是执行从数据库中删除记录的功能。 为此，我将再次将AppDAO.run（...）方法与ProjectRepository和TaskRepository类的新的delete方法结合使用。
 
ProjectRepository文件里是这样：
 
```js
// project_repository.js

class ProjectRepository {  
  // omitting other methods

  delete(id) {
    return this.dao.run(
      `DELETE FROM projects WHERE id = ?`,
      [id]
    )
  }
}
```
 
TaskRepository文件里是这样：
 
```js
// task_repository.js

class TaskRepository {  
  // omitting other methods

  delete(id) {
    return this.dao.run(
      `DELETE FROM tasks WHERE id = ?`,
      [id]
    )
  }
}
```
 
大功告成，这里包括我将使用run方法的所有方式。 接下来我将介绍其他两个相关的get和all sqlite3 Node.js包方法。
 
 
 
  

#### 读取数据
 
在本节中，我将介绍如何使用sqlite3 Node.js库的get和all方法。 如前所述，get用于检索单行数据，而all用于查询多行数据。
 
使用get的基本语法如下所示：
 
```js
db.get('SELECT ...', [param1, param2], (err, result) => {  
  if (err) {
    console.log(err)
  } else {
    // do something with result
  }
})
```
 
其中db是一个sqlite3连接对象。 您会注意到，语法与run方法基本相同，只是回调函数具有一个附加参数， 假设没有错误发生，    该参数将保存查询的结果对象。
 
所有的基本语法基本上都是相同的，除了回调的第二个参数是查询返回的结果数组，如下所示：
 
```js
db.all('SELECT ...', [param1, param2], (err, results) => {  
  if (err) {
    console.log(err)
  } else {
    // do something with results
  }
})
```
 
就像我对sqlite3 run方法所做的那样，我将在AppDAO类中实现使用bluebird Promise的get和all方法，如下所示：
 
```js
// dao.js

const sqlite3 = require('sqlite3').verbose()  
const Promise = require('bluebird')

class AppDAO {  
  // omitting other methods

  get(sql, params = []) {
    return new Promise((resolve, reject) => {
      this.db.get(sql, params, (err, result) => {
        if (err) {
          console.log('Error running sql: ' + sql)
          console.log(err)
          reject(err)
        } else {
          resolve(result)
        }
      })
    })
  }

  all(sql, params = []) {
    return new Promise((resolve, reject) => {
      this.db.all(sql, params, (err, rows) => {
        if (err) {
          console.log('Error running sql: ' + sql)
          console.log(err)
          reject(err)
        } else {
          resolve(rows)
        }
      })
    })
  }
}
```
 
 
 
  
现在可以在ProjectRepository和TaskRepository类中使用这些方法从SQLite数据库中检索数据。
 
一开始，我将为每个类添加getById方法，以通过id去选择他们的记录。
 
在ProjectRepository中添加这个类：
 
```js
// project_repository.js

class ProjectRepository {  
  // omitting other methods

  getById(id) {
    return this.dao.get(
      `SELECT * FROM projects WHERE id = ?`,
      [id])
  }
}
```
 
同样在TaskRepository中：
 
```js
// task_repository.js

class TaskRepository {  
  // omitting other methods

  getById(id) {
    return this.dao.get(
      `SELECT * FROM tasks WHERE id = ?`,
      [id])
  }
}
```
 
为了演示AppDAO.all（...）方法，我将添加选择所有项目以及给定项目所有任务的功能。
 
选择所有项目的代码如下所示：
 
```js
// project_repository.js

class ProjectRepository {  
  // omitting other methods

  getAll() {
    return this.dao.all(`SELECT * FROM projects`)
  }
}
```
 
然后，为项目选择所有任务，我将使用一个名为getTasks（projectId）的方法，该方法需要您希望执行任务的项目的ID。
 
```js
// project_repository.js
class ProjectRepository {  
  // omitting other methods

  getTasks(projectId) {
    return this.dao.all(
      `SELECT * FROM tasks WHERE projectId = ?`,
      [projectId])
  }
}
```

#### 使用数据访问代码
 
到目前为止，我基本上已经为这个虚构的项目和任务跟踪应用程序创建了一个数据访问库。 我现在想要做的就是使用它来加载我在 **`设计数据库`**  部分表格中显示的测试数据。
 
在main.js文件中，我希望通过require来引入AppDAO，ProjectRepository和TaskRepository类。 然后我将使用它们来创建表格，然后用数据填充它们，从数据库检索数据并显示到控制台。
 
```js
// main.js 
const Promise = require('bluebird')   
const AppDAO = require('./dao')   
const ProjectRepository = require('./project_repository')   
const TaskRepository = require('./task_repository') function main() {  
  const dao = new AppDAO('./database.sqlite3')
  const blogProjectData = { name: 'Write Node.js - SQLite Tutorial' }
  const projectRepo = new ProjectRepository(dao)
  const taskRepo = new TaskRepository(dao)
  let projectId

  projectRepo.createTable()
    .then(() => taskRepo.createTable())
    .then(() => projectRepo.create(blogProjectData))
    .then((data) => {
      projectId = data.id
      const tasks = [
        {
          name: 'Outline',
          description: 'High level overview of sections',
          isComplete: 1,
          projectId
        },
        {
          name: 'Write',
          description: 'Write article contents and code examples',
          isComplete: 0,
          projectId
        }
      ]
      return Promise.all(tasks.map((task) => {
        const { name, description, isComplete, projectId } = task
        return taskRepo.create(name, description, isComplete, projectId)
      }))
    })
    .then(() => projectRepo.getById(projectId))
    .then((project) => {
      console.log(`\nRetreived project from database`)
      console.log(`project id = ${project.id}`)
      console.log(`project name = ${project.name}`)
      return projectRepo.getTasks(project.id)
    })
    .then((tasks) => {
      console.log('\nRetrieved project tasks from database')
      return new Promise((resolve, reject) => {
        tasks.forEach((task) => {
          console.log(`task id = ${task.id}`)
          console.log(`task name = ${task.name}`)
          console.log(`task description = ${task.description}`)
          console.log(`task isComplete = ${task.isComplete}`)
          console.log(`task projectId = ${task.projectId}`)
        })
      })
      resolve('success')
    })
    .catch((err) => {
      console.log('Error: ')
      console.log(JSON.stringify(err))
    })
}

main()
```
 
使用node命令运行：
 
```
$ node main.js
```
 
你会看到如下所示的输出。
 
```
Connected to database  
Retreived project from database  
project id = 1  
project name = 1  
Retrieved project tasks from database  
task id = 1  
task name = Outline  
task description = High level overview of sections  
task isComplete = 1  
task projectId = 1  
task id = 2  
task name = Write  
task description = Write article contents and code examples  
task isComplete = 0  
task projectId = 1
```
 

#### 结论
 
在本教程中，我回顾了Node.js sqlite3包里API的基础知识，并演示了如何将该功能封装在面向对象的JavaScript  中，其中重点放在基于Promise的异步实现上。
 
 
 


[1]: https://en.wikipedia.org/wiki/SQLite
[2]: https://www.npmjs.com/package/sqlite3
[3]: http://bluebirdjs.com/docs/getting-started.html
[4]: https://en.wikipedia.org/wiki/Data_access_object
[0]: https://img2.tuicool.com/rEfYnir.png