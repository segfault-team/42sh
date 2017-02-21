touch test00 test01
echo "ls\nexit" | ./21sh > test00
ls > test01
diff test00 test01
rm test00 test01
