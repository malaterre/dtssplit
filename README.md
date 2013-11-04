dtssplit
========

Steps:
------

```
$ cmake .
$ make
```

XML-ZLIB:
---------

```
$ wget http://www.cs.cmu.edu/~pausch/medicalData/UPMC_Oct_2006/Stentor/Stack/1.2.392.200036.9123.100.14.12.1000001.20060907.1144203.dts
$ ./dtsplit 1.2.392.200036.9123.100.14.12.1000001.20060907.1144203.dts
$ cat *.xml
```
-> seems to work ok

Image stuff:
------------

```
$ wget http://www.cs.cmu.edu/~pausch/medicalData/UPMC_Oct_2006/Stentor/Stack/1.2.392.200036.9123.100.14.12.1000001.20060907.1144203
$ ./dtsplit 1.2.392.200036.9123.100.14.12.1000001.20060907.1144203
$ cat 1.2.392.200036.9123.100.14.12.162.32.20060907.1153205.22
```

-> ??
