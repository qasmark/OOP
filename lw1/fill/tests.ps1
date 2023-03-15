$exe = "fill.exe";
 
for ($i = 1; $i -lt 9; $i++)
{
	$j = $i + 10;
	$secondcommand = "$j.txt";
	$command = "$i.txt";
	Write-Output "Running $command";

	Invoke-Expression "& `"./$exe`" $command $secondcommand";
	Write-Output "";
}