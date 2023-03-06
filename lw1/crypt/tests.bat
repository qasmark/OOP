set PROGRAM="%~1"

rem Random crypt test 1
%PROGRAM% CRYPT large.txt "%TEMP%\large_output_1.txt" "30" goto err
echo first test run
fc.exe "%TEMP%\large_output_1.txt" large_output.txt  goto err
echo first test OK

rem Random decrypt test 1
%PROGRAM% DECRYPT large_output.txt "%TEMP%\large_output_dercypt.txt" 30  goto err
echo second test run
fc.exe "%TEMP%\large_output_dercypt.txt" large.txt goto err
echo second test OK

%PROGRAM% CRYPT invalid_count.txt "%TEMP%\invalid_count_output.txt" goto err
echo third test run
fc.exe "%TEMP%\invalid_count_output.txt" invalid_count.txt  goto err
echo third test OK

%PROGRAM% CRYPT input_error.txt "%TEMP%\input_error_output.txt"  12  goto err
echo fourth test run
fc.exe "%TEMP%\input_error_output.txt" input_error_output.txt  goto err
echo fourth test OK

%PROGRAM% SDLFRPF mode_error.txt "%TEMP%\mode_error_output.txt"  goto err
echo fith test run
fc.exe "%TEMP%\mode_error_output.txt" mode_error_output.txt  goto err
echo fiveth test OK

%PROGRAM% DECRYPT.txt large.txt "%TEMP%\large_output.txt" -124  goto err
echo six test run
fc.exe "%TEMP%\large_output.txt" large_output.txt  goto err
echo six test OK

%PROGRAM% CRYPT.txt large.txt "%TEMP%\large_output.txt" 1203  goto err
echo seven test run
fc.exe "%TEMP%\large_output.txt" large_output.txt  goto err
echo seven test OK

%PROGRAM% CRYPT this.txt "%TEMP%\this_output.txt" 64  goto err
echo eight test run
fc.exe "%TEMP%\this.txt" this_output.txt  goto err
echo eight test OK

%PROGRAM% DECRYPT this_output.txt "%TEMP%\this_decrypt_output.txt" 64  goto err
echo nine test run
fc.exe "%TEMP%\this.txt" this_decrypt_output.txt  goto err
echo nine test OK

%PROGRAM% CRYPT.txt "" "%TEMP%\this_output.txt" "1a" goto err
echo ten test run
fc.exe "%TEMP%\this.txt" this_output.txt  goto err
echo ten tesk OK


echo OK
exit 0

:err
echo Program testing failed
exit 1