$exe = "invert.exe";
 
for ($i = 1; $i -lt 9; $i++)
{
	$command = "$i.txt";
	Write-Output "Running $command";
	Write-Output "Test OK";
	Invoke-Expression "& `"./$exe`" $command";
	Write-Output "";
}