# Brain Fuck

- 这是一个由c语言编写的Brain Fuck解释器
- 戳[这里](https://github.com/YouLanjie/Brain-Fuck/archive/refs/heads/main.zip)下载代码压缩包

## 终端代码格式

``` sh
brainfuck [文件]...
```

- 没有参数，可以执行多个文件
- 如果不指定文件，则会进入到程序菜单

## 编译安装

- 编译
  - 使用make直接编译

    ```sh
    make
    ```

  - 或者**进入brain-fuck/src/**目录，使用gcc编译所有c文件：
    
    ```sh
    gcc *.c */*.c -o main
    ```

- 安装程序（非必要操作）
  
  ```sh
  make && make install
  ```

