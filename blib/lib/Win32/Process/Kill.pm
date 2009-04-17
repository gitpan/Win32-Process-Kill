package Win32::Process::Kill;

use 5.010000;
use strict;
use warnings;

require Exporter;

our @ISA = qw(Exporter);

# Items to export into callers namespace by default. Note: do not export
# names by default without a very good reason. Use EXPORT_OK instead.
# Do not simply export all your public functions/methods/constants.

# This allows declaration	use Win32::Process::Kill ':all';
# If you do not need this, moving things directly into @EXPORT or @EXPORT_OK
# will save memory.
our %EXPORT_TAGS = ( 'all' => [ qw(pTerminate AdjustPrivileges) ] );

our @EXPORT_OK = ( @{ $EXPORT_TAGS{'all'} } );

our @EXPORT = qw(pTerminate);

our $VERSION = '1.8';

require XSLoader;
XSLoader::load('Win32::Process::Kill', $VERSION);

1;
__END__

=head1 NAME

Win32::Process::Kill - Perl extension for Terminating Process in Win32 (R3)

=head1 SYNOPSIS

  use Win32::Process::Kill;
  my $pid = blah blah blah;
  pTerminate($pid);				#AdjustPrivileges and Kill Process

=head1 DESCRIPTION

	Try to kill Process in diverse ways.
	if you have any amazing ways to kill process in Win32,
	please contact me. MSN: lokchungk@hotmail.com<gt>
	I'll keep update the ways for killing process.  

=head2 EXPORT

=head1 SEE ALSO

	Win32::Process::List (Find out ProcessId easily)
	L<http://search.cpan.org/dist/Win32-Process-List/List.pm>

=item AdjustPrivileges

	use Win32::Process::Kill qw(AdjustPrivileges);
	AdjustPrivileges($_) for 2..30; #Enable all Privileges	

=item pTerminate

	use Win32::Process::Kill;
	pTerminate($pid); #Adjust Privileges than kill the process
	
=head1 AUTHOR

Baggio, Kwok Lok Chung. E<lt>lokchungk@hotmail.com<gt>

=head1 COPYRIGHT AND LICENSE

Copyright (C) 2009 by Baggio, Kwok Lok Chung

This library is free software; you can redistribute it and/or modify
it under the same terms as Perl itself, either Perl version 5.10.0 or,
at your option, any later version of Perl 5 you may have available.


=cut
