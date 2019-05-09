
my @file = @ARGV;

if(! open dat, "@file[0]"){
	die "Unable to open file: ($!)\n";
}

while(<dat>){
	# redak odijeljen ";"
	chomp;
	my @info = split /;/, $_;

	my($jmbag, $prezime, $ime, $vrijeme_lab, $vrijeme_predano) = @info;

	my($datum_pocetak_lab, $vrijeme_pocetak_lab, $vrijeme_kraj_lab, $dvorana) = split / /, $vrijeme_lab;

	# pomocna varijabla gjde je razdvojen datum predaje labosa pomocu razmaka
	my @temp = split / /, $vrijeme_predano;
	# datum je prvi clan pomocne liste
	my $datum_predano_lab = @temp[0];

	# ako je dan odrzavanja labosa jedna danu predaje labosa 
	if($datum_pocetak_lab ne $datum_predano_lab){
		print "$jmbag $prezime $ime - PROBLEM: $datum_pocetak_lab $vrijeme_pocetak_lab --> $vrijeme_predano\n"
	}

	# vrijeme pocetka labosa je u boliku hh:mm, nama trebaju samo sati
	@temp = split /:/, $vrijeme_pocetak_lab;
	# sat pocetka labosa je na prvom mjestu liste
	my $sat_pocetak_lab = @temp[0];
	
	# vrijeme predaje labosa je u obliku godina-mjesec-dan hh-mm-ss
	@temp = split / /, $vrijeme_predano;
	# uzimamo drugi element liste sa satima, minutama i sekundama
	@temp = split /:/, @temp[1];
	# potrebni su opet samo sati
	my $sat_predan_lab = @temp[0];

	# ako se razlikuju sati odrzavanja i predaje labosa znaci da je zakasnjela predaja
	if($sat_pocetak_lab != $sat_predan_lab){
		print "$jmbag $prezime $ime - PROBLEM: $datum_pocetak_lab $vrijeme_pocetak_lab --> $vrijeme_predano\n"

	}
}
