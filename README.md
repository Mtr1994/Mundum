# `Mundum`
`OpenGL` 学习使用的 示例程序附带一些学习笔记。希望能成功入门~

#### 学习笔记

* `OpenGL` 是一个巨大的状态机，大概包括状态设置函数和状态应用函数。
* 目标小助理如果已经记录了需要回忆的状态，解除绑定；下次需要这个状态的时候，再次绑定该小助理。
* 函数 `glClearColor` 设置背景色，函数 `glColor` 应用清除缓冲区的颜色。
* 目标 `GL_ARRAY_BUFFER` 是顶点缓冲类型。
* `VBO` 解释为 `Vertex Buffer Objects`，`VAO` 解释为 `Vertex Array Objects`
* `Index Buffer` 可以让编程人员重复使用顶点，有利于节省内存
* 索引缓冲必须要是无符号整形，有符号就什么都看不到
* 可以通过 `gl get error` 获取错误，现代版本中可以通过 `glDebugMessageCallBack` 回调函数拿到错误信息
* 使用 `uniform` 可以通过和 `C++` 代码修改着色器中的值
* 使用 `Qt` 重载 `QOpenGLWidget` 时，只能在 固定的三个函数中写 `gl` 函数，其他自定义函数中调用 `gl` 函数是无效的
