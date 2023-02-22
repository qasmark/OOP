set PROGRAM="%~1"

%PROGRAM% empty.txt "%TEMP%\empty_output.txt" as ass  goto err
echo first test run
fc.exe "%TEMP%\empty_output.txt" empty_output.txt  goto err
echo first test OK

%PROGRAM% nothing.txt "%TEMP%\nothing_output.txt" as ass  goto err
echo second test run
fc.exe "%TEMP%\nothing_output.txt" nothing_output.txt  goto err
echo second test OK

%PROGRAM% regular.txt "%TEMP%\regular_output.txt" as ass  goto err
echo third test run
fc.exe "%TEMP%\regular_output.txt" regular_output.txt  goto err
echo third test OK

%PROGRAM% invalid.txt "%TEMP%\invalid_output.txt" "" ass  goto err
echo fourth test run
fc.exe "%TEMP%\invalid_output.txt" invalid_output.txt  goto err
echo fourth test OK

%PROGRAM% big.txt "%TEMP%\big_output.txt" as ass  goto err
echo fith test run
fc.exe "%TEMP%\big_output.txt" big_output.txt  goto err
echo fiveth test OK

%PROGRAM% 1231234.txt "%TEMP%\1231234.txt" 1231234 AssWeCan  goto err
echo six test run
fc.exe "%TEMP%\1231234.txt" 1231234_output.txt  goto err
echo six test OK

echo OK
exit 0

:err
echo Program testing failed
exit 1