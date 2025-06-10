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
Usage: PrintHtml [-test] [-p printer] [-l left] [-t top] [-r right] [-b bottom] [-a paper] [-o orientation] [-pagefrom number] [-pageto number] [-json] <url> [url2]
       [-server port]

-test                     - Don't print, just show what would have printed.
-p printer                - Printer to print to. Use 'Default' for default printer.
-json                     - Optional. Output success and error lists as JSON to stdout (no message boxes).
-a paper                  - Paper type. Options:
                            • Standard sizes: [A4|A5|Letter]
                            • Custom size: width,height in millimeters (e.g., 77,77)
-l left                   - Optional left margin (default: 0.5 inches).
-t top                    - Optional top margin (default: 0.5 inches).
-r right                  - Optional right margin (default: 0.5 inches).
-b bottom                 - Optional bottom margin (default: 0.5 inches).
-o [Portrait|Landscape]   - Optional page orientation (default: Portrait).
-pagefrom [page number]   - Optional. Start page number for printing range.
-pageto [page number]     - Optional. End page number for printing range.
                            (Must be used together with -pagefrom)
 -server [port]           - Start REST server on the given port.
url                       - One or more URLs to print (space-separated).

Example (custom paper size 77x77 mm, no margins):

  PrintHtml -p "YourPrinterName" -a "77,77" -l 0 -r 0 -t 0 -b 0 "https://example.com"

REST server example (listen on port 9090):

  PrintHtml -server 9090

Custom size via REST:

  http://localhost:9090/print?url=https://example.com&a=77,77
~~~~

---

## 🛠️ Building from Source

To compile this project on Windows, follow these steps:

### 1. Download the required MinGW toolchain

Download and extract the following toolchain (compatible with Qt 4.8.6):

🔗 [i686-4.8.2-release-posix-dwarf-rt\_v3-rev3.7z](https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win32/Personal%20Builds/mingw-builds/4.8.2/threads-posix/dwarf/i686-4.8.2-release-posix-dwarf-rt_v3-rev3.7z)

📂 Extract it to a directory like:

```
E:/mingw32
```

---

### 2. Install Qt 4.8.6

Download and install Qt 4.8.6 built for MinGW 4.8.2:

🔗 [qt-opensource-windows-x86-mingw482-4.8.6-1.exe](https://download.qt.io/archive/qt/4.8/4.8.6/qt-opensource-windows-x86-mingw482-4.8.6-1.exe)

Make sure to install it to a path without spaces, such as:

```
E:/Qt/4.8.6
```

---

### 3. Build the Project

Open **Qt 4.8.6 Command Prompt**, then navigate to the project folder:

```sh
cd E:\PrintHtml-master\PrintHtml-master
```

Run the following commands:

```sh
qmake
mingw32-make release
```

After a successful build, the executable will be found in the `release` directory.


## 🔽 Precompiled Version (Download and run directly)

If you just want to use the tool without modifying or compiling the source code:

📦 A precompiled executable is available in:

```
release\release.zip
```

Simply extract it and run `PrintHtml.exe` as needed — no setup or installation required.

---



Since it has to spawn up an entire instance of the QtWebKit control in order to perform the printing
the program is written to accept multiple URL's on the command line, one after the other. So if you have
large batches of URL's to print, like we do simply pass them all on the command line. In our case we
print our pick sheets using this tool by passing in batches of 20 URL's at a time and it works very fast
without anything showing on the screen.

# Caveats

The biggest caveat at the moment is that the QtWebKit control has no support for renderin headers and
footers on the page. For us this is not a big problem, but for some it could be a deal breaker. There have
been quite a few discussion about this that I could find on the web, but no solutions that seemed to work.
If anyone has ideas about how to fix this it would be great to add some options to control the headers
and footers to this program.

# REST server mode

PrintHtml can also run as a lightweight REST service. Start the application with
`-server [port]` (default `8080`) and it will listen for HTTP requests. Send a
`GET /print` request using query parameters that match the command line options
(such as `url`, `printer`, `left`, `top`, etc.) or their short forms (`p`, `l`,
`t`, `r`, `b`, `o`, `a`). The server accepts either style of parameter and
always returns a JSON response. Custom paper sizes can be provided using
`width` and `height` query parameters or the shorthand `a=WIDTH,HEIGHT`.


<h4>🧾 REST Parameters</h4>

Parameter | Description
-- | --
url | Page URL to print (required)
p | Printer name
a | Paper size (e.g., A4, Letter, or custom WIDTH,HEIGHT in mm)
l, t, r, b | Margins (in inches, optional)
o | Orientation (Portrait or Landscape)
pagefrom, pageto | Print range
json | Return result as JSON (optional)


<h4>🧪 Example (REST + Custom Size)</h4>
<pre><code class="language-http">http://localhost:9090/print?url=https://example.com&amp;p=MyPrinter&amp;a=77,77&amp;l=0&amp;t=0&amp;r=0&amp;b=0
</code></pre>
<hr>
