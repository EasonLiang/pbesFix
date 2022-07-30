因编译时，有2类错误提示，
(一？)libprotoc 与 protobuf版本不匹配。此类已记不清，或者方法不可行。
（二）make时提示Try installing package 'python3-protobuf' or similar。
    01)搜索ubuntu里软件包python3-protobuf_3.12.4，此版本转换为archlinux的安装包后，需要libprotobuf2=3.12.4，AUR编译安装libprotobuf2后不起作用。
    02)搜索ubuntu里软件包python3-protobuf_3.0.0，此版本转换为archlinux的安装包后，不可理喻的要求python<3.7，系统最新的版本是python3.10。
    03)于是aur里编译python36，降级后删除3.10的并新建指向3.6的/usr/bin/python软连接，
    04)把python3-protobuf_3.0.0的deb包转成archlinux的安装包，并解压其中的protobuf-3.0.0.egg-info到~/.local/lib/python3.6/site-packages下
    05)由于pip原先绑定了python3.10，此时pip无法工作，提示No module named ‘pip’”，于是按步骤06)修复pip
    06)先运行python -m ensurepip，后运行python -m pip install –upgrade pip；然后运行pip list测试修复成功。
    07)转回到错误提示No module named 'google.protobuf.text_format'，搜索后活马医死马，尝试当作缺乏安装包google进行修复，
    08）pip install google，会额外安装beautifulsoup4丑陋灵魂，soupsieve灵魂筛子包，编译后仍然提示同样的错误，于是再次活马医死马修复到步骤09）。
    09）pip uninstall protobuf ; pip uninstall google，更改步骤重新安装google和protobuf包到步骤10）。
    10）pip install google ; pip install protobuf 【最新版4.21.0】，重新编译后仍然失败，于是转到步骤11）。
    11）pip uninstall protobuf ; pip uninstall google ； pip uninstall beautifulsoup4 ;pip uninstall soupsieve; 重新安装到步骤12）。
    12）pip install google ; pip install protobuf ，再次编译后成功。

PS :: archlinux软件库里python-protobuf版本混乱，不要使用。
PS :: 不确定作用，但页安装了grpcio-tools
PS :: 运行命令pip list查看python generator/nanopb_generator.py simple.proto 正常工作时，需要的软件包如下：
        [eason@Arch tests]$ pip list
            Package        Version
            -------------- -----------
#            beautifulsoup4 4.11.1
#            google         3.0.0
#            pip            21.3.1
#            protobuf       4.21.0
#            setuptools     40.6.2
#            soupsieve      2.3.2.post1
        [eason@Arch tests]$ python --version
            Python 2.7.18
        [eason@Arch tests]$ python3 --version
            Python 3.6.15
        [eason@Arch tests]$ protoc --version
            libprotoc 3.21.2
        [eason@Arch tests]$ ls -l /usr/bin/python3
            lrwxrwxrwx 1 root root 18  7月30日 20:16 /usr/bin/python3 -> /usr/bin/python3.6
        [eason@Arch tests]$ ls -l /usr/bin/python
            lrwxrwxrwx 1 root root 18  7月30日 20:47 /usr/bin/python -> /usr/bin/python2.7
