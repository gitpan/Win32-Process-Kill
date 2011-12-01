use ExtUtils::MakeMaker;
WriteMakefile(
    NAME              => 'Win32::Process::Kill',
    VERSION_FROM      => 'lib/Win32/Process/Kill.pm',
    PREREQ_PM         => {},
    ($] >= 5.005 ?
      (ABSTRACT_FROM  => 'lib/Win32/Process/Kill.pm',
       AUTHOR         => 'Baggio, Kwok Lok Chung  <lokchungk@hotmail.com>') : ()),
    LIBS              => [''],
    DEFINE            => '',
    INC               => '-I.',
);
