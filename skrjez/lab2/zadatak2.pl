my(@list) = @ARGV;

$counter = 0;
$sum = 0;

foreach (@list){
	$sum += $_;
	$counter += 1;
}

print "Arithmetic mean of inputted numbers: ", $sum / $counter, "\n";