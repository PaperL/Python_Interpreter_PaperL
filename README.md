# Python Interpreter

## 题面

[acrazyczy/Python-Assignment-2020](https://github.com/acrazyczy/Python-Assignment-2020#python-interpreter)

## 类

### highPrecision

## 备忘

- 需要`WSL`进行编译

- Atom处判断是变量还是数字
如果是变量则返回一个`BasicVariable`对象
该对象标记为未初始化
返回至`Expr_stmt`
Expr层确认该句合法（左值是合法左值等）后创建所需变量并操作

- 除了赋值语句`Expr_stmt`都不能新建变量

- Factor层是正负号



