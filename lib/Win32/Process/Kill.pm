package Win32::Process::Kill;

require Exporter;
our @ISA = qw(Exporter);
our @EXPORT = qw(Terminate Resume Suspend CreateRemoteThread DebugActiveProcess Kill GetHandle);
our $VERSION = '2.68_01';
require XSLoader;
XSLoader::load('Win32::Process::Kill', $VERSION);
use Carp qw' croak carp ';

$::DEBUG = 0;

sub GetHandle { map Win32::Process::Kill::_GetHandle($_), @_ }

sub Suspend { map Win32::Process::Kill::_Suspend($_), @_ }

sub Resume { map Win32::Process::Kill::_Resume($_), @_ }

sub Terminate { map Win32::Process::Kill::_TerminateProcess($_), @_ }

sub CreateRemoteThread { map Win32::Process::Kill::_CreateRemoteThread($_), @_}

sub DebugActiveProcess { map Win32::Process::Kill::_DebugActiveProcess($_), @_ }

sub Kill {
    # return a list so that users can know which process is killed successfully
	map {

		return 0 unless $_;
		my ($handle) = GetHandle($_);
        my $ref = \$handle;
        bless($ref, 'Win32::Process::Kill::Handle');
        if ( ! Win32::Process::Kill::Suspend($handle)
            && $::DEBUG > 0 ) {
            carp "Failed to Suspend Process...\nBut still fine\n";
        }

		unless ( Win32::Process::Kill::_TerminateProcess($handle)
		      || Win32::Process::Kill::_CreateRemoteThread($handle)
		      || Win32::Process::Kill::_DebugActiveProcess($_) ) {
            croak "Failed to terminate the process.\n" if $::DEBUG > 0;
            return 0;
        }
		
		Win32::Process::Kill::_Resume($_);

		return 1;
	} @_ ? @_ : $_;

}

package Win32::Process::Kill::Handle;
sub DESTROY {
    die "CloseHandle failed" if !_CloseHandle(${$_[0]}) && $::DEBUG > 0;
}

1;
__END__

=head1 NAME

Win32::Process::Kill - Perl extension for Terminating Process in Win32 (R3)

=head1 SYNOPSIS

  use Win32::Process::Kill;
  Kill(@pids);   #Try all the method from this module to terminate the @pids
  Kill();	     #Take the values of default variable as pid
  
  #Methods
  DebugActiveProcess(@pids);
  @handles = GetHandle(@pids);
  CreateRemoteThread(@handles);
  Terminate(@handles);
  Suspend(@handles);
  Resume(@handles);

=head1 DESCRIPTION

	Try to kill Process in diverse ways.
	if you have any amazing ways to kill process in Win32,
	please contact me. MSN: lokchungk@hotmail.com<gt>
	I'll keep update the ways for killing process.  

=head2 EXPORT
	Kill()
	DebugActiveProcess()
	CreateRemoteThread()
	Terminate()
	Suspend()
	Resume()
	GetHandle()

=item Kill

	Kill(@pids);
or
	Kill($pid);
or
	Kill();		#from $_

=item DebugActiveProcess

	DebugActiveProcess(@pids);
or
	DebugActiveProcess($pid);

=item CreateRemoteThread

	CreateRemoteThread(@Handles);
or
	CreateRemoteThread($Handle);

=item Terminate

	Terminate(@Handles);
or
	Terminate($Handle);

=item Suspend

	Suspend(@Handles);
or
	Suspend($Handle);

=item Resume
	
	Resume(@Handles);
or
	Resume($Handle);

=item GetHandle

	@Handles = GetHandle(@pids);
or
	($handle) = GetHandle($pid);

=head1 SEE ALSO

	Demo/demo.pl
	Win32::Process::List (Find out ProcessId easily)
	my Email: rootkwok <AT> cpan <DOT> org
	
=head1 AUTHOR

Baggio, Kwok Lok Chung. <rootkwok <AT> cpan <DOT> org>

patches by Daniel Dragan <bulkdd <AT> cpan <DOT> org>

=head1 COPYRIGHT AND LICENSE

Copyright (C) 2009 by Baggio, Kwok Lok Chung

This library is free software; you can redistribute it and/or modify
it under the same terms as Perl itself, either Perl version 5.10.0 or,
at your option, any later version of Perl 5 you may have available.


=cut
