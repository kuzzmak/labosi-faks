
my ($string, $num_of_times) = @ARGV;

while($num_of_times > 0){
	if($num_of_times == 1){
		print $string;
	}else{
		print $string, "\n";
	}
	$num_of_times -= 1;
}



