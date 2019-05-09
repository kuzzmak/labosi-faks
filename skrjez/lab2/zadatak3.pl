

# lista tatoteka
my(@dat) = @ARGV;

sub load{
	# acosijativno polje gdje je kljuc sat, a vrijednost broj pristupa
	%array = ();
	# ako je nemoguce otvoriti datoteku, ispise se greska
	if(! open dat, "$_[0]"){
		die "Unable to open file. ($!)";
	}
	# dijeljenje imena datoteke prema tocki
	my @date = split /\./, $_[0];
	
	# desno od tocke je datum nastanka datoteke
	print "Datum: @date[1]\n";
	print "sat : broj pristupa\n";
	print "------------------------------\n";

	# sve dok nije kraj datoteke
	while(<dat>){
		# redak datoteke se podijeli prema prazninama
		my @temp = split / /, $_;
		
		# temp[0] -> ip
		# temp[3] -> datum i vrijeme
	
		@temp_time = split  /:/, @temp[3];
	
		# temp_time[1] -> sat
			
		$array{@temp_time[1]} = $array{@temp_time[1]} += 1;
	}

	#	# ispis polja
	#	while(($key, $value) = each %array){
	#		print "\t$key : $value\n";
	#	}
	#	print "\n";
	#	
	# ispis polja
	foreach my $key(sort {$a <=> $b} keys %array){
		my $value = $array{$key};
		print "  $key : $value\n";
	}
	print "\n";

}

# za svaku predanu datoteku napravi se analiza
foreach (@dat){
	&load($_);
}


#
#while(<>){
#	my @temp = split / /, $_;
#	
#	# temp[0] -> ip
#	# temp[3] -> datum i vrijeme
#	
#	@temp_time = split  /:/, @temp[3];
#	
#	# temp_time[1] -> sat
#		
#	
#	$array{@temp_time[1]} = $array{@temp_time[1]} += 1;
#}
#
#while(($key, $value) = each %array){
#	print "$key => $value\n";
#}
