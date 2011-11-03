Tesseract 2011-11-03

Tesseract is an QtOctave personal fork.

Changelog since 0.10-1

For users:
Design with stylesheets
Long term goal: fully integrate gnuplot

For developers:
Boost library dependency
Administration with visual studio 2008
Long term goal: cross plattform
new folder taxonomy (less anarchy)

Design goals:
Use STL. If no STL option is available use Boost.
If no Boost option is available use Qt. Yes this
means keep the Qt dependency as less as possible.

Function naming: use functionName instead of function_name
Dynamic allocation: use shared_ptr<abc>(new abc()) instead of only new abc

You want to help and have no idea where?
Try to solve the "work packages". Work packages are well documented
todos. (where to look, what is wrong, screenshots)

How to start developing?
Qt generates visual studio project with absolute path so everyone
must generate his own visual studio projects (buld/msw/vc9).
Use create.bat or import .pro files with Qt visual studio addin.