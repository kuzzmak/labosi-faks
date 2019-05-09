
@args = @ARGV;
# duljina podniza je zdanji argument
$length = @args[-1];
# mice se zadnji argument
pop @args;
# broj predanih datoteka
$noofargs = @args;

# asocijativno polje za rezultat
%array = ();

# ako su predane datoteke kao argmenti
if($noofargs > 0){
	# za svaki datoteku
	foreach(@args){
		# ako je nije moguce otvoriti
		if(! open dat, $_){
			die "Unable to open file: ($!)\n";
		}
		# za svaki redak datoteke
		while(<dat>){
			# brise se "\n"
			chomp;	
			# odvajaju se rijeci pomocu razmaka		
			my @words = split /[[:space:]]/, $_;
			# provjera sadrzi li rijec interpunkcijske znakove
			foreach(@words){
				# uklanjanje svih interpunkcijskih znakova
				s/[\.,;]//;
				# pretvaranje velikih slova u mala
				tr/A-Z/a-z/;
				# ako rijec ima barem toliko znakova koliko
				# je zadnji predani argument
				if(m/[a-z]{$length}/){
					print "|$_|\n";
					# uzima se dio rijeci duzine zadnjeg argumenta
					$var = substr $_, 0, $length;
					# povecava se vrijednost uz rijec ako je 
					# vec prije obradjena
					$array{$var} = $array{$var} += 1;
				}

			}
		}
	}
}else{ # ako nije niti jedna datoteka predana kao argument
       # cita se sa standardnog ulaza	
	print "nema dat\n";
}
#
#while(($key, $value) = each %array){
#	print "$key : $value\n";
#}
#

foreach my $key(sort {$a cmp $b} keys %array){
	my $value = $array{$key};
	print "$key : $value\n";
}
