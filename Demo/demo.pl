use Win32::Process::Kill;
do{
	chomp;
	if (/\D+/ || $_ % 4 > 0){
		print "please enter a valid pid!\n";
	}else{
		Kill($_);
	}
	print "pid> ";
}while(<STDIN>);
