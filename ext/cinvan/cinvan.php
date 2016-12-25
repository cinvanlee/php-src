<?php
$br = (php_sapi_name() == "cli")? "":"<br>";

if(!extension_loaded('cinvan')) {
	dl('cinvan.' . PHP_SHLIB_SUFFIX);
}

goto two;

one:

$module = 'cinvan';
$functions = get_extension_funcs($module);
echo "Functions available in the test extension:$br\n";
foreach($functions as $func) {
    echo $func."$br\n";
}
echo "$br\n";
$function = 'confirm_' . $module . '_compiled';
if (extension_loaded($module)) {
	$str = $function($module);
} else {
	$str = "Module $module is not compiled into PHP";
}
echo "$str\n";
echo PHP_EOL;
echo cinvan_hello($user);
echo PHP_EOL;

array_shift($argv);
$users = $argv;
foreach ($users as $user) {
	echo cinvan_hello($user);
	echo PHP_EOL;
}
echo PHP_EOL;

echo 'create_foobar', PHP_EOL;
create_foobar();
echo 'print foobar via echo $foobar, and value is : ', $foobar;
echo PHP_EOL;
echo 'print foobar via printfoobar(), and value is : ';
print_foobar();
echo PHP_EOL;


two:
$a = 'hello';
$b = $a;

cinvan_get_refcount('a');
echo PHP_EOL;
cinvan_get_refcount('b');
echo PHP_EOL;
unset($a);

cinvan_get_refcount('a');
echo PHP_EOL;
cinvan_get_refcount('b');
echo PHP_EOL;

$b = $b+1;

cinvan_get_refcount('a');
echo PHP_EOL;
cinvan_get_refcount('b');
echo PHP_EOL;




echo PHP_EOL;






