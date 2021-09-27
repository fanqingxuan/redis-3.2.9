## 研究学习redis源码，并添加必要的注释，不添加任何代码逻辑,使用版本是3.2.9


- 安装
```shell
    % make
```
- 启动服务端
```shell
    % cd src
    % ./redis-server /path/to/redis.conf
```
- 客户端使用
```shell
    % cd src
    % ./redis-cli
    redis> ping
    PONG
    redis> set foo bar
    OK
    redis> get foo
    "bar"
    redis> incr mycounter
    (integer) 1
    redis> incr mycounter
    (integer) 2
    redis>
```
更多命令参见 http://redis.io/commands