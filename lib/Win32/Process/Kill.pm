package Win32::Process::Kill;

require Exporter;
our @ISA = qw(Exporter);
our %EXPORT_TAGS = ( 'all' => [ qw(Terminate) ] );
our @EXPORT_OK = ( @{ $EXPORT_TAGS{'all'} } );
our @EXPORT = qw(Terminate);
our $VERSION = '2.62';
require XSLoader;
XSLoader::load('Win32::Process::Kill', $VERSION);
Win32::Process::Kill::Import();
__END__

=head1 NAME

Win32::Process::Kill - Perl extension for Terminating Process in Win32 (R3)

=head1 SYNOPSIS

  use Win32::Process::Kill;
  my $pid = blah blah blah;
  Terminate($pid);				#AdjustPrivileges and Kill Process

=head1 DESCRIPTION

	Try to kill Process in diverse ways.
	if you have any amazing ways to kill process in Win32,
	please contact me. MSN: lokchungk@hotmail.com<gt>
	I'll keep update the ways for killing process.  

=head2 EXPORT
	Terminate()
	
=item Terminate

	use Win32::Process::Kill;
	Terminate($pid); #Adjust Privileges than kill the process

=head1 SEE ALSO

	Win32::Process::List (Find out ProcessId easily)
	my Email: rootkwok <AT> cpan <DOT> org
	
=head1 AUTHOR

Baggio, Kwok Lok Chung. <rootkwok <AT> cpan <DOT> org>

=head1 COPYRIGHT AND LICENSE

Copyright (C) 2009 by Baggio, Kwok Lok Chung

This library is free software; you can redistribute it and/or modify
it under the same terms as Perl itself, either Perl version 5.10.0 or,
at your option, any later version of Perl 5 you may have available.


=cut
