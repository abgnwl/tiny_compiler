# 一个简单的编译器
为了理解编译器的工作原理，模仿C语言编译器，取其中的少部分关键字完成该编译器。

<br>
## 词法分析器

<br>
### 分类
KEYWORD,ID,INT,FLOAT,CHAR,STRING,OPERATOR,DELIMITER,OTHER
依次为关键字、标识符，整数常量、实数常量、字符常量、字符串常量、运算符、分隔符、其他

		选取的关键字为：
		"break","char","const","continue","else","float",
		"for","if","int","return","signed","typedef",
		"unsigned","void","include"

		支持的运算符为：
		+,-,*,/,%,
		^,~,|,&,
		++,--
		||,&&,!
		==,!=,<,>,<=,>=
