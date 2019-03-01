# PrintHtml

PrintHtml is a command line program to print HTML pages and more importantly allows you to
send the output to a specific printer. I was searching for a long time to find a solution
to this problem after we ran into more and more issues using the .net WebBrowser control.
Most recently the WebBrowser control kept failing and silently not printing until we
rebooted the computer and updating to Windows 10 made no difference. It worked flawlessly
for probably 4 years, but now it seems it has problems. On top of that we needed the
ability to print to different printers and the WebBrowser control always sends the output
to whatever printer is configured as the default for Internet Explorer.

Many years ago we wrote a version of our printing code for packing slips using C++ and
the QtWebKit library. But when we ported all our code to C# and .net, we moved to using the
.net WebBrowser control and it served us faithfully for many years. So to solve the problems
we had with the .net WebBrowser control I dug up the old C++ application that printed web pages
files and turned it into this project to print via the command line, and enabled it to print
to different printers.

The program is pretty simple and the command line usage is like this:

~~~~
Usage: PrintHtml [-test] [-p printer] [-l left] [-t top] [-r right] [-b bottom] <url> [url2]

-test         - Don't print, just show what would have printed.
-p printer    - Printer to print to. Use 'Default' for default printer.
-a page       - Paper type [A4|A3|US letter]
-l left       - Optional left margin for page.
-t top        - Optional top margin for page.
-r right      - Optional right margin for page.
-b bottom     - Optional bottom margin for page.
url           - Defines the list of URLs to print, one after the other.
~~~~

Since it has to spawn up an entire instance of the QtWebKit control in order to perform the printing
the program is written to accept multiple URL's on the command line, one after the other. So if you have
large batches of URL's to print, like we do simply pass them all on the command line. In our case we
print our pick sheets using this tool by passing in batches of 20 URL's at a time and it works very fast
without anything showing on the screen.

# Build environment

To build this you need to use a version of Qt that includes the QtWebKit control. This control was deprecated
and removed from the Qt 5.x releases, and although there is an external project that has ported the QtWebKit
control to the latest Qt releases, I was unable to find any pre-compiled libraries I could use out of the box
for this project. Hence for simplicity I decided to stick to using Qt 4.8 and as of today the code is written
to compile and link with Qt 4.8.6 using the Qt Creator that came with the Qt 5.7.1 release by installing
Qt 4.8.6 alongside it. The build in the deploy directory is built using MingW 5.3 as a 32-bit x86 application.

Theoretically the code is 100% portable so you could build it for Mac or Linux, but I have only done it on
Windows since that is what I needed it for :)

# Pre-built binaries

For those who just want the resulting app and do not want to compile the code yourselves, I have included a
pre-built Windows x86 version of the program in the deploy directory.

# Caveats

The biggest caveat at the moment is that the QtWebKit control has no support for renderin headers and
footers on the page. For us this is not a big problem, but for some it could be a deal breaker. There have
been quite a few discussion about this that I could find on the web, but no solutions that seemed to work.
If anyone has ideas about how to fix this it would be great to add some options to control the headers
and footers to this program.

# Potential improvements

Something that would cool to add, but I am not familar enough with Qt and C++ these days to implement, would be
to turn this application into a small REST server that would sit in the background and accept URL's and related
options to print them over the wire so it would be easy to use from other apps without having to resort to
executing it on the command line. If someone more familiar with Qt and REST services knows how to build a basic
REST server into the app that would be a pretty slick improvement.
