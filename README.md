# selfEnonyaval

This is a simple implementation of selfE(nonya)val.

And it's just for my personal convince, but if it brings you covince too, plz consider give me a star :yum:

Currenctly support Windows & Linux.

```
Usage: senyv <FILE> <EXT_IN> <EXT_OUT> <EXT_USR> <CHECKER>
         FILE: cpp source file, without extension name
         EXT_IN: extension of input file, default: in
         EXT_OUT: extension of output file (jury's out), default: out
         EXT_USR: extension of user's output file, default: usr
         CHECKER: file name of checker(cpp), without extension name, not inneed
  Possible formats:
         >$ eny <FILE>
         >$ eny <FILE> <CHECKER>
         >$ eny <FILE> <EXT_IN> <EXT_OUT> <EXT_USR>
         >$ eny <FILE> <EXT_IN> <EXT_OUT> <EXT_USR> <CHECKER>
```

You have to put it in your work directory like this:

(until I add support for automatically change work directory of selfEnonyaval)

```
./
../
workdict /
	senyv*
	solution.cpp
	checker.cpp
	test01.in
	test01.out
	test02.in
	test02.out
	testlib.h
```

Then you can use it like:

```
./senyv solution
./senyv solution checker
./senyv solution in out usr
./senyv solution in out usr checker
```

(or `senyv.exe` on Windows.)

It will gives you some result if conditions listed here were satisfied.

1. If your source file/checker cannot be compiled: `[Error] source file:fileName.cpp does not pass the compilation.`
2. If you got the right answer: `Ok, accepted, time = <time>ms/s.`
3. If your answer is not correct: `Wrong answer.`

selfEnonyaval will automatically **sort test cases with lexicographical order**, and it will **stop** when you got an incorrect answer.

(Maybe I'll consider to add an option which control this.)

selfEnonyaval has used `fc` command and `diff` command, so the preference of diffing is the same as this two command.

Executable file are included in release, or you can compile it by youself.
