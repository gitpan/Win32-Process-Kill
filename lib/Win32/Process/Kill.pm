package Win32::Process::Kill;

require Exporter;
our @ISA = qw(Exporter);
our @EXPORT = qw(Terminate Resume Suspend CreateRemoteThread DebugActiveProcess Kill GetHandle);
our $VERSION = '2.642';
require XSLoader;
XSLoader::load('Win32::Process::Kill', $VERSION);

sub GetHandle {map Win32::Process::Kill::_GetHandle($_),@_;}

sub Suspend {map Win32::Process::Kill::Suspend($_),@_;}

sub Resume {map Win32::Process::Kill::Resume($_),@_;}

sub Terminate {map Win32::Process::Kill::_TerminateProcess($_),@_;}

sub CreateRemoteThread {map Win32::Process::Kill::_CreateRemoteThread($_),@_;}

sub DebugActiveProcess {map Win32::Process::Kill::_DebugActiveProcess($_),@_;}

sub Kill {
	map{
		my ($handle) = GetHandle($_);
		return 0 unless $_;
		unless(Win32::Process::Kill::Suspend($handle)
			|| Win32::Process::Kill::_TerminateProcess($handle)
			|| Win32::Process::Kill::_CreateRemoteThread($handle)
			|| Win32::Process::Kill::_DebugActiveProcess($_)){
						return 0;
		}
		Win32::Process::Kill::Resume($_);
		close $handle;
		return 1;
	}@_ ? @_ : $_;
}

Win32::Process::Kill::Import();
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

=head1 COPYRIGHT AND LICENSE

Copyright (C) 2009 by Baggio, Kwok Lok Chung

This library is free software; you can redistribute it and/or modify
it under the same terms as Perl itself, either Perl version 5.10.0 or,
at your option, any later version of Perl 5 you may have available.


=cut
