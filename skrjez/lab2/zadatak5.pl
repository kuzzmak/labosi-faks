# lista s predanim argumentom
my @file = @ARGV;

# provjera je li moguce otvoriti datoteku
if(! open dat, @file[0]){
	die "Unable to open file: ($!)\n";
}

# lista koeficijenata
@koef = ();
# asocijativno polje za pohranu rezultata
%polje = ();

while(<dat>){

	chomp;	

	# regularni izraz za slucaj kada redak pocinje s koeficijentima
	if(m/^[0-9]\./){
		@koef = split /;/, $_;
	}
	# regularni izraz za slucaj retka s podatcima studenta
	if(m/^[0-9]{10}/){
		# redak odvojen ";"
		my @temp = split /;/, $_;

		my $jmbag = @temp[0];
		my $prezime = @temp[1];
		my $ime = @temp[2];

		# ukupan rezultat pojedinih studenata je suma 
		# umnozaka odgovarajuceg koeficijenta i
		# rezultata iz pojedinog predmeta
		my $suma = @koef[0] * @temp[3] + 
				@koef[1] * @temp[4] + 
				@koef[2] * @temp[5] + 
				@koef[3] * @temp[6] + 
				@koef[4] * @temp[7] + 
				@koef[5] * @temp[8] + 
				@koef[6] * @temp[9];

		# kljuc asocijativnog polja je prezime, ime jmbag,
		# a vrijednost je suma rezultata pojedinog studenta
		$key = "$prezime, $ime $jmbag";
		$polje{$key} = $suma;	

	}

	
}

# okretanje uloge kljuca i vrijednosti u svrhu lakseg sortiranja
# i ispisa polja
%reverse_polje = reverse %polje;

# ispis rezultata
print "Lista po rangu:\n";
print "------------------------\n";
# pomocna varijabla za redni broj pojedinog retka
my $i = 1;
# sortiranje i ispis polja
foreach my $key(sort {$b <=> $a} keys %reverse_polje){
	my $value = $reverse_polje{$key};
	printf "  %2d. %-30s : %g\n", $i, $value, $key;
	$i += 1;

}
