/*
Filip Maletic (250866829)
CS 3307A Individual Assignment
October 3, 2023
This file contains information about how to build and run the code on your end.
I just edited the provided README.txt file that was given to us in the hello example since it's so similar to execute.
*/

Building the Wordle Application:
-----------------------------------

Building things is fairly straightforward using the provided Makefile.  It is
configured to use the default Wt installation path, /usr/local.  If Wt has
been installed in a different folder, you must edit the Makefile and change
the WT_BASE variable to indicate where things are installed.  Otherwise, the
compiler will be unable to find Wt headers and libraries to build things.

When ready, things can be built simply be executing:

  >  make

When done, you will have the wordle application executable ready to run.


Running the Wordle Application Example:
----------------------------------

To run things, you can do so by executing:

  > ./wordle --docroot . --http-listen 0.0.0.0:8080

This runs the wordle executable in your current directory, giving it a couple
of parameters.  Specifying --docroot . tells the application to find files
it needs from the current directory.  (Specifically, it will search for 
things in the resources folder in the current directory.)  The remaining
parameters (--http-listen 0.0.0.0:8080) tells the server to listen for 
incoming HTTP requests on any network interface on the system at port number
8080. The port number can be changed to your unnique port number on gaul.

With the application running, you can then use any web browser to connect to 
http://127.0.0.1:8080 and access things from there.

If you would like to tailor things further, running:

  > ./wordle --help

will report a full set of command line options for the application.