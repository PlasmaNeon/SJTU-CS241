# Homework1

## 注意事项
1. 注意小数不进行四舍五入操作。`to_string(<float>)` 生成的字符串一般保留至小数点后6位，可以用`str.erase(len - 2)` 进行截取操作。
2. 浮点数的比较应该使用 `fabs(a - b) <= some_small_number(e.g. 1e-6)`。

## 关键测试例
### Q1

- 0x^2+0x+0
- 0x^2+0x+1
- 0x+1
- 0x

- x-x
- -x+x
- x^2-x^2
- -x^2+x^2

- 1 
- -1

### Q2
- x^2+2x+1    x+1

- x   x^2

- x   x

- 0.9999x   0.1